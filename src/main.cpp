#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_APDS9960.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "Screen.h"
#include "WeatherScreen.h"
#include "DateScreen.h"
#include "WelcomeScreen.h"
#include "MenuScreen.h"
#include <PubSubClient.h>

#define APDS9960_ADDR 0x39                   
#define DEFAULT_ITIME 50                    
#define DEFAULT_GAIN APDS9960_AGAIN_4X
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define OLED_SDA_PIN 16
#define OLED_SCL_PIN 17
#define GESTURE_SDA_PIN 25
#define GESTURE_SCL_PIN 26
#define INT_PIN 12 


const char* ssid = "MERCUSYS_B0F7"; 
const char* password = "Pipik2024"; 

const char* mqtt_server = "test.mosquitto.org";

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_APDS9960 apds;

WiFiClient espClient;
PubSubClient client(espClient);

WeatherData* weatherData;
DateData* dateData;

MenuScreen* menuScreen; 
WeatherScreen* weatherScreen;
DateScreen* dateScreen;
SettingsScreen* settingsScreen;

void IRAM_ATTR gestureISR() {
  
}

void initDisplay() {
    Wire.begin(OLED_SDA_PIN, OLED_SCL_PIN);
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println("Could not initialize OLED displej");
        while (true);
    }
}

void initScreens() {
    WelcomeScreen *welcomeScreen = new WelcomeScreen(display);
    weatherScreen = new WeatherScreen(display);
    dateScreen = new DateScreen(display);
    settingsScreen = new SettingsScreen(display);
    menuScreen = new MenuScreen(display);

    menuScreen->weatherScreen = weatherScreen;
    menuScreen->dateScreen = dateScreen;
    menuScreen->settingsScreen = settingsScreen;

    weatherData = new WeatherData();
    weatherScreen->updateData(weatherData);

    welcomeScreen->render();
}

void waitForWeatherData() {
    settingsScreen->sendSettings();

    while (!weatherData->hasData) {
        client.loop();
        delay(100);
    }
}

void initGestureSensor() {
    Wire1.begin(GESTURE_SDA_PIN, GESTURE_SCL_PIN);
    pinMode(INT_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(INT_PIN), gestureISR, FALLING);

    if (!apds.begin(DEFAULT_ITIME, DEFAULT_GAIN, APDS9960_ADDR, &Wire1)) {
        Serial.println("Could not initialize APDS-9960");
        display.println("Error initializing!");
        display.display();
        while (1);
    } else {
        Serial.println("APDS-9960 initialized.");
    }
    apds.enableGesture(true);
    Serial.println("Detection gestures activated.");
}

void displayMessage(String message) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println(message);
  display.display();
}

void connectToWiFi() {
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi");
}

void connectToMQTT() {
  while (!client.connected()) {
    Serial.print("Connecting MQTT broker...");
    String clientId = "ESP32Client-" + String(random(0xffff), HEX);

    if (client.connect(clientId.c_str())) {
      if (client.subscribe("home/response/weather")) {
        Serial.println("Subscribing: home/response/weather");
      } else {
        Serial.println("Could not subscribe: home/response/weather");
      }
    } else {
      Serial.print("Could not connect to MQTT, error code=");
      Serial.print(client.state());
      Serial.println(" Retrying in 5 seconds...");
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
    String message;
    for (int i = 0; i < length; i++) {
        message += (char)payload[i];
    }

    if (String(topic) == "home/response/weather") {
        Serial.println("Got weather data: " + message);

        DynamicJsonDocument doc(512);
        DeserializationError error = deserializeJson(doc, message);

        if (error) {
            Serial.print("Error parsing JSON JSON: ");
            Serial.println(error.c_str());
            return;
        }

        float temperature = doc.containsKey("temperature") ? doc["temperature"].as<float>() : NAN;
        String condition = doc.containsKey("condition") ? doc["condition"].as<String>() : "";
        String icon = doc.containsKey("icon") ? doc["icon"].as<String>() : "";
        float humidity = doc.containsKey("humidity") ? doc["humidity"].as<float>() : NAN;
        float windSpeed = doc.containsKey("wind_speed") ? doc["wind_speed"].as<float>() : NAN;
        String sunrise = doc.containsKey("sunrise") ? doc["sunrise"].as<String>() : "";
        String sunset = doc.containsKey("sunset") ? doc["sunset"].as<String>() : "";

        weatherData->update(temperature, condition, icon, humidity, windSpeed, sunrise, sunset);
        weatherData->hasData = true;
    }
}

DateData* parseDateData(String payload) {
  DynamicJsonDocument doc(1024);
  DeserializationError error = deserializeJson(doc, payload);

  if (error) {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.f_str());
    return nullptr;
  }

  String date = doc["date"].as<String>(); 
  String dayInWeek = doc["dayInWeek"].as<String>(); 
  String name = doc["name"].as<String>();

  DateData* nameDayData = new DateData();
  nameDayData->updateDate(name, date);

  return nameDayData;
}


String getDateData() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String nameDayApiUrl = "https://svatkyapi.cz/api/day";
    http.begin(nameDayApiUrl);
    int httpCode = http.GET();

    if (httpCode > 0) {
      String payload = http.getString();
      Serial.println(payload);
      return payload;
    } else {
      Serial.println("Error calling on API");
      return "";
    }
    http.end();
  } else {
    Serial.println("Wi-Fi not connected");
    return "";
  }
}

void updateDateData() {
    String payloadDate = getDateData();
    dateData = parseDateData(payloadDate);
    dateScreen->updateData(dateData);
}

void initMQTT() {
    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);
    connectToMQTT();
    settingsScreen->client = client;
}

void setup() {
    Serial.begin(115200);

    initDisplay();
    initScreens();
    connectToWiFi();
    updateDateData();
    initMQTT();
    waitForWeatherData();
    initGestureSensor();

    delay(2000);
    menuScreen->render();
}


void loop() {
  if (!client.connected()) {
    connectToMQTT();
  }
  client.loop();
  if (apds.gestureValid()) {
    uint8_t gesture = apds.readGesture();
    menuScreen->handleGesture(gesture);  
    delay(500);
  }
}
