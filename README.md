📱 ESP8266 ile Telefonunuzu Akıllı Kumandaya Dönüştürün

Transform your smartphone into a universal web-based smart remote control! This project uses an ESP8266 board and an Infrared (IR) emitter LED to trigger your TV and Smart Lighting commands right from your mobile browser—no extra mobile app required.

📑 English
📱 Features

Zero App Required: Runs a lightweight web server accessible via any browser at http://kumanda.local.

Responsive Dark UI: Modern CSS Grid layout designed for mobile screen sizes.

Multi-Device Support: Integrated control for RC5 Protocol TVs and NEC Protocol Smart Lights.

mDNS Hostname Support: Access the device using a custom URL without remembering IP addresses.

🛠️ Hardware Requirements

ESP8266 NodeMCU / D1 Mini board

5mm IR LED Transmitter (Connected to GPIO4 / D2)

PNP Transistor or NPN Transistor (NPN 2N2222 / BC337 recommended) + $220\ \Omega$ resistor to amplify the IR signal distance

🔌 Pin Configuration
Component	ESP8266 Pin	GPIO Pin
IR LED Transmitter	D2	GPIO4
🚀 Getting Started
Install Arduino Libraries

Ensure you have the following library installed via Arduino IDE's Library Manager:

IRremoteESP8266

Configure Wi-Fi Credentials

Open the C++ sketch and replace the placeholder credentials with your home network details:

const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

Upload & Test

Upload the sketch to your ESP8266.

Connect your phone to the same Wi-Fi network.

Open your browser and navigate to http://kumanda.local.

⚙️ How the Code Works

mDNS & Web Server (ESP8266mDNS, ESP8266WebServer):
Hosts a dark-mode web dashboard and binds it to kumanda.local on port 80.

RC5 Protocol Helper (rc5Paketle):
Packs 6-bit button commands into a 12-bit payload required by Philips/LG RC5 TV systems.

HTTP Endpoints (/tv and /light):

Sends TV commands using irsend.sendRC5() on the /tv route.

Converts hexadecimal strings into 32-bit values to control RGB lights via irsend.sendNEC() on the /light route.

📑 Türkçe
📱 Özellikler

Uygulamasız Kullanım: Herhangi bir mobil tarayıcıdan http://kumanda.local adresiyle erişilebilen hafif bir web sunucusu çalıştırır.

Kullanıcı Dostu Karanlık Tema: Mobil ekranlara tam uyumlu modern CSS Grid arayüzü.

Çoklu Cihaz Desteği: RC5 protokolü kullanan TV'ler ve NEC protokolü kullanan Akıllı Aydınlatmalar için hazır altyapı.

mDNS Desteği: IP adresi ezberlemeye gerek kalmadan özel alan adı ile erişim.

🛠️ Donanım Gereksinimleri

ESP8266 NodeMCU / D1 Mini geliştirme kartı

5mm Kızılötesi (IR) Verici LED (GPIO4 / D2 pinine bağlı)

NPN Tranzistör (Örn: 2N2222 / BC337) + $220\ \Omega$ Direnç (IR LED sinyal menzilini güçlendirmek için önerilir)

🔌 Pin Bağlantı Tablosu
Bileşen	ESP8266 Pini	GPIO Pini
IR LED Verici	D2	GPIO4
🚀 Kurulum Adımları
Kütüphane Kurulumu

Arduino IDE üzerindeki Kütüphane Yöneticisi aracılığıyla şu kütüphaneyi yükleyin:

IRremoteESP8266

Wi-Fi Bilgilerini Düzenleme

Kod içerisindeki Wi-Fi alanlarını kendi ağ bilgilerinize göre güncelleyin:

const char* ssid = "WIFI_ADINIZ";
const char* password = "WIFI_SIFRENIZ";

Yükleme ve Çalıştırma

Kodu ESP8266 kartınıza yükleyin.

Telefonunuzun aynı Wi-Fi ağına bağlı olduğundan emin olun.

Tarayıcınızdan http://kumanda.local adresine girin.

⚙️ Kod Mantığı ve Mimarisi

mDNS ve Web Sunucusu (ESP8266mDNS, ESP8266WebServer):
Mobil uyumlu kontrol panelini Port 80 üzerinden yayınlar ve cihaza kumanda.local ismiyle erişilmesini sağlar.

RC5 Paketleyici (rc5Paketle):
TV komutlarını Philips/LG standartlarındaki 12-bit RC5 sinyal paketine dönüştürür.

HTTP Endpoint İşleyicileri (/tv ve /light):

/tv rotasından gelen isteklerde irsend.sendRC5() fonksiyonu ile TV sinyalleri fırlatılır.

/light rotasında Hexadecimal (16'lık) sistemdeki kodlar 32-bit sayılara çevrilerek irsend.sendNEC() ile ışık sistemine iletilir.
