#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char* ssid = "Universitas Mulawarman";
const char* password = "";

ESP8266WebServer server(80); // Port untuk web server


// Define pins
const int BUZZER_PIN = D8;
const int LED_PIN = D4;
const int ONOFF_BUZZER = D7;
const int ADD_BUZZER = D5;
const int MIN_BUZZER = D6;
const int ONOFF_LED = D3;
const int ADD_LED = D1;
const int MIN_LED = D2;

// Define variables
int kecerahan = 0;
int bunyi = 0;
int LED_ONOFF;
int BUZZER_ONOFF;
int ONOFFBUZZER = 0;
int ONOFFLED = 0;

void setup() {
  Serial.begin(9600);
  // Initialize pins
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(ONOFF_BUZZER, INPUT_PULLUP);
  pinMode(ADD_BUZZER, INPUT_PULLUP);
  pinMode(MIN_BUZZER, INPUT_PULLUP);
  pinMode(ONOFF_LED, INPUT_PULLUP);
  pinMode(ADD_LED, INPUT_PULLUP);
  pinMode(MIN_LED, INPUT_PULLUP);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi.");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot); // Halaman utama
  server.on("/kecerahan", handleKecerahan); // Halaman untuk menampilkan kecerahan
  server.on("/bunyi", handleBunyi); // Halaman untuk menampilkan bunyi
  server.begin(); // Memulai web server
}

void loop() {
  server.handleClient();
  delay(150);
  analogWrite(LED_PIN,kecerahan);
  analogWrite(BUZZER_PIN,bunyi);
  
  // Check button state
  int LED_ADD = digitalRead(ADD_LED);
  int LED_MIN = digitalRead(MIN_LED);
  int BUZZER_ADD = digitalRead(ADD_BUZZER);
  int BUZZER_MIN = digitalRead(MIN_BUZZER);
  LED_ONOFF = digitalRead(ONOFF_LED);
  BUZZER_ONOFF = digitalRead(ONOFF_BUZZER);

 
  if ( LED_ONOFF == LOW && ONOFFLED==0) {
    ONOFFLED=1;
    kecerahan=250;
    Serial.println(ONOFFLED);
    
  } else if(LED_ONOFF==LOW && ONOFFLED==1) {
    ONOFFLED=0;
    kecerahan=0;
    Serial.println(ONOFFLED);
  }
  
 
  if ( LED_ADD == LOW && kecerahan<250 && ONOFFLED==1) {
    kecerahan+=5;
    Serial.println(kecerahan);
    
  } else if(LED_MIN==LOW && kecerahan>0 && ONOFFLED==1) {
    kecerahan-=5;
    Serial.println(kecerahan);
  }

    if ( BUZZER_ONOFF == LOW && ONOFFBUZZER==0) {
    ONOFFBUZZER=1;
    bunyi=100;
    Serial.println(ONOFFBUZZER);
    
  } else if(BUZZER_ONOFF==LOW && ONOFFBUZZER==1) {
    ONOFFBUZZER=0;
    bunyi=0;
    Serial.println(ONOFFBUZZER);
  }
  
 
  if ( BUZZER_ADD == LOW && bunyi<2500 && ONOFFBUZZER==1) {
    bunyi+=5;
    Serial.println(bunyi);
    
  } else if(BUZZER_MIN==LOW && bunyi>100 &&  ONOFFBUZZER==1) {
    bunyi-=5;
    Serial.println(bunyi);
  }
}


//Tampilan Website
void handleRoot() {
  server.send(200, "text/html", "<html><body><h1>Monitoring Kecerahan LED dan bunyi Buzzer </h1><p><a href=\"/kecerahan\">Atur kecerahan</a></p><p><a href=\"/bunyi\">Atur bunyi</a></p></body></html>"); // Menampilkan halaman utama
}

//Monitoring Kecerahan
void handleKecerahan() {
  String content = "<html><body><h1>Kecerahan</h1><p>" + String(kecerahan) + " </p><p><a href=\"/\">Kembali ke halaman utama</a></p></body></html>"; 
  server.send(200, "text/html", content);
}

void handleBunyi() {
 // Monitoring Frekuensi suara
  String content = "<html><body><h1>bunyi</h1><p>" + String(bunyi) + " Hz</p><p><a href=\"/\">Kembali ke halaman utama</a></p></body></html>"; 
  server.send(200, "text/html", content);
}