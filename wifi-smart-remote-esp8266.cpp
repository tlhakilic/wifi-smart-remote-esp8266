#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

// WiFi Bilgileri
const char* ssid = "WIFI ADRESINIZ";
const char* password = "WIFI SIFRENIZ";

const uint16_t kIrLedPin = 4; // D2 Pini
IRsend irsend(kIrLedPin);
ESP8266WebServer server(80);

// RC5 Paketleme (TV için)
uint16_t rc5Paketle(uint8_t komut) {
  return 0x800 | (1 << 6) | (komut & 0x3F);
}

void handleRoot() {
  String html = "<!DOCTYPE html><html><head><meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  html += "<style>body{background:#121212;color:#e0e0e0;font-family:sans-serif;text-align:center;margin:0;padding:20px;}";
  html += ".grid{display:grid;grid-template-columns:repeat(3,1fr);gap:10px;max-width:350px;margin:auto;margin-bottom:30px;padding:15px;background:#1e1e1e;border-radius:20px;}";
  html += ".btn{background:#333;color:#fff;padding:15px;border-radius:10px;text-decoration:none;font-weight:bold;font-size:13px;border:1px solid #444;display:flex;align-items:center;justify-content:center;}";
  html += ".btn:active{background:#BB86FC;color:#000;}";
  html += ".pwr{background:#CF6679;grid-column: span 3;} .mute{background:#03DAC6;color:#000;}";
  html += ".nav{background:#BB86FC;color:#000;} .ok{background:#fff;color:#000;}";
  html += ".light-btn{background:#FFD700;color:#000;} .night{background:#3700B3;color:#fff;}";
  html += "h1{color:#BB86FC;margin-bottom:5px;text-transform:uppercase;} h2{font-size:18px;margin-bottom:10px;border-bottom:1px solid #333;padding-bottom:5px;} p{font-size:12px;opacity:0.6;}</style></head><body>";
  
  html += "<h1>UZAKTAN KUMANDA</h1><p>kumanda.local</p>";
  
  // --- TV KUMANDASI ---
  html += "<h2>📺 TV KONTROLÜ</h2><div class='grid'>";
  html += "<a href='/tv?v=12' class='btn pwr'>AÇ / KAPAT</a>";
  html += "<a href='/tv?v=16' class='btn'>SES +</a><a href='/tv?v=13' class='btn mute'>SESSİZ</a><a href='/tv?v=32' class='btn'>KANAL +</a>";
  html += "<a href='/tv?v=17' class='btn'>SES -</a><a href='/tv?v=107' class='btn'>HIZLI MENÜ</a><a href='/tv?v=33' class='btn'>KANAL -</a>";
  html += "<div></div><a href='/tv?v=20' class='btn nav'>▲</a><div></div>";
  html += "<a href='/tv?v=21' class='btn nav'>◀</a><a href='/tv?v=53' class='btn ok'>TAMAM</a><a href='/tv?v=22' class='btn nav'>▶</a>";
  html += "<div></div><a href='/tv?v=19' class='btn nav'>▼</a><div></div>";
  for(int i=1; i<=9; i++) html += "<a href='/tv?v=" + String(i) + "' class='btn'>" + String(i) + "</a>";
  html += "<div></div><a href='/tv?v=0' class='btn'>0</a><div></div>";
  html += "</div>";

  // --- SALON IŞIĞI ---
  html += "<h2>💡 SALON IŞIĞI</h2><div class='grid'>";
  html += "<a href='/light?v=0x1FE807F' class='btn light-btn'>IŞIK AÇ / KAPAT</a>";
  html += "<a href='/light?v=0x1FEA05F' class='btn night'>GECE MODU</a><a href='/light?v=0x1FE609F' class='btn'>BÖLÜM</a><a href='/light?v=0x1FE58A7' class='btn'>YARDIMCI</a>";
  html += "<a href='/light?v=0x1FE48B7' class='btn nav'>▲ PARLAKLIK +</a><a href='/light?v=0x1FE40BF' class='btn'>RENK SIC. +</a><a href='/light?v=0x1FE48B7' class='btn nav'>▶</a>";
  html += "<a href='/light?v=0x1FE7887' class='btn nav'>◀</a><a href='/light?v=0x1FEC03F' class='btn'>RENK SIC. -</a><a href='/light?v=0x1FE7887' class='btn nav'>▼ PARLAKLIK -</a>";
  html += "</div>";
  
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);
  irsend.begin();
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); }

  if (MDNS.begin("kumanda")) {
    Serial.println("Adres: http://kumanda.local");
  }

  server.on("/", handleRoot);
  
  // TV Endpoint (RC5)
  server.on("/tv", []() {
    if (server.hasArg("v")) {
      uint8_t val = server.arg("v").toInt();
      irsend.sendRC5(rc5Paketle(val), 12);
      Serial.printf("TV Sinyali Yollandı: 0x%02X\n", val);
    }
    server.sendHeader("Location", "/");
    server.send(303);
  });

  // Işık Endpoint (NEC)
  server.on("/light", []() {
    if (server.hasArg("v")) {
      String hexVal = server.arg("v");
      uint32_t code = strtoul(hexVal.c_str(), NULL, 16);
      irsend.sendNEC(code, 32);
      Serial.printf("Işık Sinyali Yollandı: 0x%08X\n", code);
    }
    server.sendHeader("Location", "/");
    server.send(303);
  });

  server.begin();
  MDNS.addService("http", "tcp", 80);
}

void loop() {
  MDNS.update();
  server.handleClient();
}
