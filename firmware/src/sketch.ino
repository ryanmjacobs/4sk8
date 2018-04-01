#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

#include <TinyGPS.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include "FastLED.h"

#define DATA_PIN 5
#define NUM_LEDS 51

#include "gps.h"

TinyGPS gps;
SoftwareSerial ss(3, 4);

const char *ssid = "Triangle";
const char *pass = "brothersdeltat";
const char *host = "192.168.0.184";
const int   port = 4848;

double lat, lon;

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

    ss.begin(9600);
    get_coords();
}

void get_coords() {
    Serial.print("connecting to ");
    Serial.println(host);
    
    // Use WiFiClient class to create TCP connections
    WiFiClient client;
    if (!client.connect(host, port)) {
      Serial.println("connection failed");
      return;
    }
    
    String url = "/aquery";
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
      Serial.print("pre,");
      Serial.print(line);

      StaticJsonBuffer<200> buf;
      JsonObject& root = buf.parseObject(line);

      lat = root["lat"];
      lon = root["lon"];

      Serial.println(lat, 10000);
      Serial.println(lon, 10000);
    }
    
    Serial.println();
    Serial.println("closing connection");
}

void loop() {
  float flat, flon;
  unsigned long age;
  
  gps.f_get_position(&flat, &flon, &age);
  Serial.println(flat);
  Serial.println(flon);

  double dir = direction(lat, lon, flat, flon);
  Serial.print("direction: ");
  Serial.println(dir);

  smartdelay(1000);
}

static void smartdelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}

String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
