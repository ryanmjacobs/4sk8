#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

const char *ssid = "Triangle";
const char *pass = "brothersdeltat";

void setup() {
    Serial.begin(9600);
    Serial.println();
    Serial.print("connecting to ");
    Serial.println(ssid);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

const char *host = "192.168.0.149";

void loop() {
    delay(5000);
    Serial.print("connecting to ");
    Serial.println(host);
    
    // Use WiFiClient class to create TCP connections
    WiFiClient client;
    const int httpPort = 4848;
    if (!client.connect(host, httpPort)) {
      Serial.println("connection failed");
      return;
    }
    
    // We now create a URI for the request
  //String url = "/input/";
  //url += streamId;
  //url += "?private_key=";
  //url += privateKey;
    
    String url = "/query/ramen";
    Serial.print("Requesting URL: ");
    Serial.println(url);
    
    // This will send the request to the server
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
      if (millis() - timeout > 5000) {
        Serial.println(">>> Client Timeout !");
        client.stop();
        return;
      }
    }
    
    // Read all the lines of the reply from server and print them to Serial
    while (client.available()) {
      String line = client.readStringUntil('\r');
      Serial.print(line);
    }
    
    Serial.println();
    Serial.println("closing connection");
}
