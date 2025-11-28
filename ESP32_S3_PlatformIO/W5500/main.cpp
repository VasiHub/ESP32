//A simple web server for testing the W5500 board.
#include <WebServer_ESP32_SC_W5500.h>
#include <SPI.h>

// Define SPI pins for ESP32-S3 Gen4 R8N16
  #define ETH_CLOCK  12
	#define ETH_MISO   13
	#define ETH_MOSI   11
	#define ETH_SCK    12
	#define ETH_CS     10
  #define ETH_RST     5
  #define ETH_INT     4

IPAddress EmyIP(192, 168, 1, 87); //Please specify your network.
IPAddress EmyGW(192, 168, 1, 1);
IPAddress EmySN(255, 255, 255, 0);
IPAddress EmyDNS(8, 8, 8, 8); // Hello, Google :))) 

WebServer server(80);

void handleRoot() {
  server.send(200, "text/html", "<h1>Hello from ESP32-S3 Gen4 R8N16 + W5500! </h1>");
}

void handleTest() {
  server.send(200, "text/html", "<h1>Hello from Test Page ESP32-S3 Gen4 R8N16 + W5500! </h1>");
}

void setup() {
  delay(2000);
  Serial.begin(115200);
  while (!Serial); delay(200);
  
  // Initialize Ethernet string
  //.begin(int MISO, int MOSI, int SCLK, int CS, int INT, int SPICLOCK_MHZ = 25, int SPIHOST = 2, uint8_t *W5500_Mac = W5500_Default_Mac)
      if (!ETH.begin(ETH_MISO, ETH_MOSI, ETH_SCK, ETH_CS, ETH_INT,ETH_CLOCK)) {
    Serial.println("W5500 network failed");
    for (;;);  // Don't proceed, loop forever
  }
  ETH.config(EmyIP, EmyGW, EmySN, EmyDNS);

  // Start server
  server.on("/", handleRoot);
  server.on("/test", handleTest);
  server.begin();
  delay(200);
  Serial.println(F("WebServer started.  Access via Ethernet IP."));
  Serial.println(SHIELD_TYPE);
  Serial.println(ETH.macAddress());
  Serial.println(ETH.localIP());
  Serial.println(ETH.localIPv6());
  Serial.println(ETH.dnsIP());
  Serial.println(ETH.gatewayIP());
  Serial.println(ETH.linkSpeed());
}

void loop() {
  server.handleClient();
}
