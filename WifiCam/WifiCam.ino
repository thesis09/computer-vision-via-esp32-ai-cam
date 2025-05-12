// #include "WifiCam.hpp"
// #include <WiFi.h>

// static const char* WIFI_SSID = "AirFiber";
// static const char* WIFI_PASS = "*#662q1qbi$";

// esp32cam::Resolution initialResolution;

// WebServer server(80);

// void
// setup() {
//   Serial.begin(115200);
//   Serial.println();
//   esp32cam::setLogger(Serial);
//   delay(1000);

//   WiFi.persistent(false);
//   WiFi.mode(WIFI_STA);
//   WiFi.begin(WIFI_SSID, WIFI_PASS);
//   if (WiFi.waitForConnectResult() != WL_CONNECTED) {
//     Serial.printf("WiFi failure %d\n", WiFi.status());
//     delay(5000);
//     ESP.restart();
//   }
//   Serial.println("WiFi connected");
//   delay(1000);

//   {
//     using namespace esp32cam;

//     initialResolution = Resolution::find(640, 480); // Higher resolution for better detection

//     Config cfg;
//     cfg.setPins(pins::AiThinker);
//     cfg.setResolution(initialResolution);
//     cfg.setJpeg(60);
    
    
//     // Change camera resolution setup

//     bool ok = Camera.begin(cfg);
//     if (!ok) {
//       Serial.println("camera initialize failure");
//       delay(5000);
//       ESP.restart();
//     }
//     Serial.println("camera initialize success");
//   }

//   Serial.println("camera starting");
//   Serial.print("http://");
//   Serial.println(WiFi.localIP());

//   addRequestHandlers();
//   server.begin();
// }

// void
// loop() {
//   server.handleClient();
// }

// // #include "WifiCam.hpp"
// // #include <WiFi.h>

// // // Network Configuration
// // static const char* WIFI_SSID = "AirFiber";
// // static const char* WIFI_PASS = "*#662q1qbi$";

// // // Static IP Configuration
// // IPAddress local_IP(192, 168, 1, 184);
// // IPAddress gateway(192, 168, 1, 1);
// // IPAddress subnet(255, 255, 255, 0);

// // // Hardware Configuration
// // #define STATUS_LED 33  // AI Thinker built-in LED

// // esp32cam::Resolution initialResolution;
// // WebServer server(80);

// // void setup() {
// //   Serial.begin(115200);
// //   pinMode(STATUS_LED, OUTPUT);
// //   digitalWrite(STATUS_LED, LOW);
  
// //   esp32cam::setLogger(Serial);
// //   delay(1000);

// //   // WiFi Configuration
// //   WiFi.persistent(false);
// //   WiFi.mode(WIFI_STA);
  
// //   if (!WiFi.config(local_IP, gateway, subnet)) {
// //     Serial.println("STA Failed to configure");
// //     while (true) {
// //       digitalWrite(STATUS_LED, !digitalRead(STATUS_LED));
// //       delay(500);
// //     }
// //   }

// //   WiFi.begin(WIFI_SSID, WIFI_PASS);
  
// //   // Connection attempt with visual feedback
// //   unsigned long startAttemptTime = millis();
// //   while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 20000) {
// //     digitalWrite(STATUS_LED, !digitalRead(STATUS_LED));
// //     delay(250);
// //   }
  
// //   if (WiFi.status() != WL_CONNECTED) {
// //     Serial.println("Connection Failed!");
// //     ESP.restart();
// //   }
  
// //   digitalWrite(STATUS_LED, HIGH);
// //   Serial.println("WiFi connected");
// //   delay(1000);

// //   // Camera Initialization
// //   {
// //     using namespace esp32cam;
    
// //     initialResolution = Resolution::find(640, 480);  // YOLO-optimized resolution
    
// //     Config cfg;
// //     cfg.setPins(pins::AiThinker);
// //     cfg.setResolution(initialResolution);
// //     cfg.setJpeg(80);  // Quality (1-100)

// //     if (!Camera.begin(cfg)) {
// //       Serial.println("Camera initialize failure");
// //       ESP.restart();
// //     }
// //     Serial.println("Camera initialize success");
// //   }

// //   // Server Setup
// //   Serial.print("Stream URL: http://");
// //   Serial.print(WiFi.localIP());
// //   Serial.println("/stream");
  
// //   addRequestHandlers();
// //   server.begin();
// // }

// // void loop() {
// //   server.handleClient();
  
// //   // Periodic status check
// //   static unsigned long lastCheck = 0;
// //   if (millis() - lastCheck > 10000) {
// //     Serial.printf("Status: IP=%s, RSSI=%ddBm, Heap=%dB\n",
// //                   WiFi.localIP().toString().c_str(),
// //                   WiFi.RSSI(),
// //                   ESP.getFreeHeap());
// //     lastCheck = millis();
// //   }
// // }





#include "WifiCam.hpp"
#include <WiFi.h>

// Network Configuration
static const char* WIFI_SSID = "AirFiber";
static const char* WIFI_PASS = "*#662q1qbi$";

// Static IP Configuration (prevents IP changes)
// IPAddress local_IP(192, 168, 1, 184);
// IPAddress gateway(192, 168, 1, 1);
// IPAddress subnet(255, 255, 255, 0);

// Hardware Configuration
#define STATUS_LED 33  // AI Thinker built-in LED

// Camera Configuration
esp32cam::Resolution initialResolution;
WebServer server(80);

void setup() {
  Serial.begin(115200);
  pinMode(STATUS_LED, OUTPUT);
  digitalWrite(STATUS_LED, LOW);
  
  esp32cam::setLogger(Serial);
  delay(1000);

  // ========== Enhanced WiFi Setup ==========
  WiFi.persistent(false);
  WiFi.mode(WIFI_STA);
  
  // Configure static IP
  // if (!WiFi.config(local_IP, gateway, subnet)) {
  //   Serial.println("STA Failed to configure");
  //   while (true) {
  //     digitalWrite(STATUS_LED, !digitalRead(STATUS_LED));
  //     delay(500);
  //   }
  // }

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  
  // Connection attempt with visual feedback
  unsigned long startAttemptTime = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 20000) {
    digitalWrite(STATUS_LED, !digitalRead(STATUS_LED));
    delay(250);
  }
  
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Connection Failed!");
    ESP.restart();
  }
  
  digitalWrite(STATUS_LED, HIGH);
  Serial.println("WiFi connected");
  delay(1000);

  // ========== Optimized Camera Setup ==========
  {
    using namespace esp32cam;
    
    // AI-optimized settings (balance between quality and performance)
    initialResolution = Resolution::find(1024, 768);  // QVGA resolution1024x768
    Config cfg;
    cfg.setPins(pins::AiThinker);
    cfg.setResolution(initialResolution);
    cfg.setJpeg(80);       // Reduced quality for faster transmission

    if (!Camera.begin(cfg)) {
      Serial.println("Camera initialize failure");
      ESP.restart();
    }
    Serial.println("Camera initialize success");
  }

  // ========== Server Configuration ==========
  Serial.print("Stream URL: http://");
  Serial.print(WiFi.localIP());
  Serial.println("/stream");
  
  addRequestHandlers();
  server.begin();

  // Enable frame buffer control
  server.setContentLength(CONTENT_LENGTH_UNKNOWN);
}

void loop() {
  server.handleClient();
  
  // Periodic status check
  static unsigned long lastCheck = 0;
  if (millis() - lastCheck > 10000) {
    Serial.printf("[Status] IP: %s | RSSI: %ddBm | Free Heap: %dB\n",
                  WiFi.localIP().toString().c_str(),
                  WiFi.RSSI(),
                  ESP.getFreeHeap());
    lastCheck = millis();
    
    // Blink LED to indicate activity
    digitalWrite(STATUS_LED, LOW);
    delay(50);
    digitalWrite(STATUS_LED, HIGH);
  }
}