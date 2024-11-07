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

#define APDS9960_ADDR 0x39                   
#define DEFAULT_ITIME 50                    
#define DEFAULT_GAIN APDS9960_AGAIN_4X 

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define OLED_SDA_PIN 16
#define OLED_SCL_PIN 17
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Adafruit_APDS9960 apds;
#define GESTURE_SDA_PIN 25
#define GESTURE_SCL_PIN 26
#define INT_PIN 12 


const char* ssid = "MERCUSYS_B0F7"; 
const char* password = "Pipik2024"; 

const char* openWeatherApiKey = "1a09557c5a10aafc954a32da8e544f11";

Screen* screens[2]; // Pole pro různé obrazovky
int currentScreenIndex = 0; // Aktuální index obrazovky

WeatherData* weatherData;
DateData* dateData;


void IRAM_ATTR gestureISR() {
  // Obsluha přerušení - necháme prázdné, jen signalizujeme dostupnost dat
}

// Funkce pro zobrazení zprávy na OLED displeji
void displayMessage(String message) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println(message);
  display.display();
}

void connectToWiFi() {
  WiFi.begin(ssid, password);
  Serial.print("Připojování k Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Připojeno k Wi-Fi");
}

WeatherData* parseWeatherData(String payload) {
  DynamicJsonDocument doc(1024);  // Použití DynamicJsonDocument
  DeserializationError error = deserializeJson(doc, payload);

  if (error) {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.f_str());
    return nullptr;
  }

  float temperature = doc["main"]["temp"]; // Extrakce teploty
  String condition = doc["weather"][0]["main"].as<String>(); // Extrakce stavu počasí
  String icon = doc["weather"][0]["icon"].as<String>(); // Extrakce ikony
  Serial.println(icon);
  // Vytvoříme a naplníme objekt WeatherData
  WeatherData* weatherData = new WeatherData();
  weatherData->updateWeather(temperature, condition, icon);

  return weatherData; // Vrátíme ukazatel na WeatherData
}


String getWeatherData() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String weatherApiUrl = String("https://api.openweathermap.org/data/2.5/weather?q=PRAGUE&appid=") + openWeatherApiKey + "&units=metric";
    http.begin(weatherApiUrl);
    int httpCode = http.GET();

    if (httpCode > 0) {
      String payload = http.getString();
      Serial.println(payload);
      return payload;
    } else {
      Serial.println("Chyba při volání API");
      return "";
    }
    http.end();
  } else {
    Serial.println("Wi-Fi není připojena");
    return "";
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

  return nameDayData; // Vrátíme ukazatel na NameDayData
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
      Serial.println("Chyba při volání API svátků");
      return "";
    }
    http.end();
  } else {
    Serial.println("Wi-Fi není připojena");
    return "";
  }
}



void setup() {
  Serial.begin(115200);
  // Inicializace I2C pro OLED displej
  Wire.begin(OLED_SDA_PIN, OLED_SCL_PIN);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Nepodařilo se inicializovat OLED displej");
    while (true);
  }

  WelcomeScreen *welcomeScreen = new WelcomeScreen(display);
  welcomeScreen->render();

  connectToWiFi();
  getWeatherData();

  screens[0] = new WeatherScreen(display);
  screens[1] = new DateScreen(display);

  // Inicializace I2C pro senzor gest na GPIO 25 a 26 pomocí existující instance Wire1
  Wire1.begin(GESTURE_SDA_PIN, GESTURE_SCL_PIN);

  // Nastavení pinu INT
  pinMode(INT_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(INT_PIN), gestureISR, FALLING);

  // Inicializace senzoru APDS-9960 s použitím Wire1
  if (!apds.begin(DEFAULT_ITIME, DEFAULT_GAIN, APDS9960_ADDR, &Wire1)) {
    Serial.println("Nepodarilo se inicializovat APDS-9960");
    display.println("Chyba inicializace!");
    display.display();
    while (1);
  } else {
    Serial.println("APDS-9960 inicializovan.");
  }

  apds.enableGesture(true);
  Serial.println("Detekce gest aktivována.");

  String payloadWeather = getWeatherData();
  weatherData = parseWeatherData(payloadWeather);

  if (weatherData) {
    screens[0]->updateData(weatherData);
    screens[0]->render(); // default screen
  }

  String payloadDate = getDateData();
  dateData = parseDateData(payloadDate);

  if (dateData) {
    screens[1]->updateData(dateData);
  }

  //menuScreen = new MenuScreen(display);

  delay(2000);
  display.clearDisplay();
  display.display();
}

void loop() {

  if (apds.gestureValid()) {
    uint8_t gesture = apds.readGesture();
    switch (gesture) {
      case APDS9960_UP:
        Serial.println("Gesto: Nahoru");
        break;
      case APDS9960_DOWN:
        Serial.println("Gesto: Dolu");
        break;
      case APDS9960_LEFT:
        Serial.println("Gesto: Vlevo");
        currentScreenIndex = (currentScreenIndex + 1) % 2;
        break;
      case APDS9960_RIGHT:
        Serial.println("Gesto: VpVlravo");
        currentScreenIndex = (currentScreenIndex - 1 + 2) % 2; 
        break;
    }

    screens[currentScreenIndex]->render();
    delay(500);
  }
}
