# 1 "/tmp/tmpmnKiZm"
#include <Arduino.h>
# 1 "/home/ryan/4sk8/firmware/src/sketch.ino"
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

#include <TinyGPS.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include "FastLED.h"

#define DATA_PIN D5
#define NUM_LEDS 51
CRGB leds[NUM_LEDS];

#include "gps.h"

TinyGPS gps;
SoftwareSerial ss(3, 4);

const char *ssid = "Triangle";
const char *pass = "brothersdeltat";
const char *host = "192.168.0.184";
const int port = 4848;

double lat, lon;
void setup();
void get_coords();
void loop();
static void smartdelay(unsigned long ms);
String getValue(String data, char separator, int index);
void updateLEDs(double dir, double dist);
double getDir(double lat1, double lat2, double lon1, double lon2);
double calcRelDir(double abs_dir, double board_dir);
#line 25 "/home/ryan/4sk8/firmware/src/sketch.ino"
void setup() {
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
    leds[3] = CRGB::Blue;
    FastLED.show();

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


    WiFiClient client;
    if (!client.connect(host, port)) {
      Serial.println("connection failed");
      return;
    }

    String url = "/aquery";
    Serial.print("Requesting URL: ");
    Serial.println(url);


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

double dir = 0;
double offset = 245;

void loop() {
  float flat, flon;
  unsigned long age;

  gps.f_get_position(&flat, &flon, &age);
  Serial.println(flat);
  Serial.println(flon);

  if (flat == 1000) {

      updateLEDs(dir+offset,100);
      dir+=10;
  } else {
      double dir = direction(lat, lon, flat, flon);
      Serial.print("direction: ");
      Serial.println(dir);
      updateLEDs(dir, 1000);
  }

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

void updateLEDs(double dir, double dist) {

    dir = (dir >=0 && dir <= 360) ? dir : ((int) dir) % 360;
    int cLED = (int) floor((dir/360.0)*NUM_LEDS);
    int spread =log10f(1000/dist);
    int sLED = (cLED - spread) % NUM_LEDS;

    int range = (spread*2)+1;
    int j;

    for(int i = 0; i <= range; i++) {
        j = (i+sLED)%NUM_LEDS;
        leds[j] = CRGB::Red;
    }

    for (int i = 0; i < NUM_LEDS - range; i++) {

        leds[(j++)%NUM_LEDS] = CRGB::Blue;
    }
    FastLED.show();
    FastLED.delay(100);
}

double getDir(double lat1, double lat2, double lon1, double lon2) {
    double radians = atan2((lon2 - lon1), (lat2 - lat1));
    double compassReading = radians * (180/PI);
    return compassReading;
}

double calcRelDir(double abs_dir, double board_dir) {
    return abs_dir - board_dir;
}