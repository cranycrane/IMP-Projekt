import paho.mqtt.client as mqtt
import requests
import json
import time
from datetime import datetime

# Nastavení MQTT brokeru
BROKER_ADDRESS = "test.mosquitto.org"
REQUEST_TOPIC = "home/request/weather"
RESPONSE_TOPIC = "home/response/weather"

# Nastavení API
openWeatherApiKey = "APIKEY"  
weatherApiUrl = f"https://api.openweathermap.org/data/2.5/weather?q=PRAGUE&appid={openWeatherApiKey}&units=metric"


def get_weather_data():
    try:
        response = requests.get(weatherApiUrl)
        response.raise_for_status()
        data = response.json()

        temperature = data["main"]["temp"]
        condition = data["weather"][0]["main"]
        icon = data["weather"][0]["icon"]
        humidity = data["main"].get("humidity", None)
        wind_speed = data["wind"].get("speed", None)

        # Převod časů východu a západu slunce
        sunrise_unix = data["sys"].get("sunrise", None)
        sunset_unix = data["sys"].get("sunset", None)
        sunrise = datetime.fromtimestamp(sunrise_unix).strftime("%H:%M") if sunrise_unix else None
        sunset = datetime.fromtimestamp(sunset_unix).strftime("%H:%M") if sunset_unix else None

        # Vrátíme všechna data jako slovník
        return {
            "temperature": temperature,
            "condition": condition,
            "icon": icon,
            "humidity": humidity,
            "wind_speed": wind_speed,
            "sunrise": sunrise,
            "sunset": sunset
        }
    except requests.exceptions.RequestException as e:
        print(f"Chyba při získávání dat o počasí: {e}")
        return {"error": "Chyba při získávání dat o počasí"}

# Funkce pro příjem zpráv
def simplify_icon(icon_code):
    if icon_code in ["01d", "01n"]:
        return "sun"
    elif icon_code in ["02d", "02n", "03d", "03n"]:
        return "cloud"
    elif icon_code in ["10d", "10n"]:
        return "rain"
    elif icon_code in ["50d", "50n"]:
        return "fog"
    else:
        return "sun"  # Pro případ neznámého kódu ikony

# Funkce pro příjem zpráv
def on_message(client, userdata, message):
    print(f"Přijat požadavek: {message.payload.decode()} na tématu {message.topic}")

    # Načtení uživatelského nastavení z příchozí zprávy
    user_settings = json.loads(message.payload.decode())

    # Získání všech dat o počasí
    full_weather_data = get_weather_data()

    # Filtrovaný výstup na základě uživatelských požadavků
    filtered_weather_data = {}

    # Zahrnutí pouze požadovaných položek
    if user_settings.get("showTemperature") and "temperature" in full_weather_data:
        filtered_weather_data["temperature"] = full_weather_data["temperature"]
    if user_settings.get("showHumidity") and "humidity" in full_weather_data:
        filtered_weather_data["humidity"] = full_weather_data["humidity"]
    if user_settings.get("showWindSpeed") and "wind_speed" in full_weather_data:
        filtered_weather_data["wind_speed"] = full_weather_data["wind_speed"]
    if user_settings.get("showSunrise") and "sunrise" in full_weather_data:
        filtered_weather_data["sunrise"] = full_weather_data["sunrise"]
    if user_settings.get("showSunset") and "sunset" in full_weather_data:
        filtered_weather_data["sunset"] = full_weather_data["sunset"]

    # Zjednodušení ikony a přidání do filtrovaných dat
    if "icon" in full_weather_data:
        filtered_weather_data["icon"] = simplify_icon(full_weather_data["icon"])

    # Převod filtrovaných dat do JSON a odeslání na MQTT
    response_message = json.dumps(filtered_weather_data)
    client.publish(RESPONSE_TOPIC, response_message)
    print(f"Odeslána odpověď: {response_message} na téma {RESPONSE_TOPIC}")

# Funkce pro pravidelné odesílání aktualizací
def publish_regular_updates(client, interval_minutes=10):
    while True:
        full_weather_data = get_weather_data()
        if "error" not in full_weather_data:  # Ověříme, zda nedošlo k chybě
            response_message = json.dumps(full_weather_data)
            client.publish(RESPONSE_TOPIC, response_message)
            print(f"Pravidelná aktualizace: {response_message} na téma {RESPONSE_TOPIC}")
        else:
            print("Při získávání dat došlo k chybě, čekám na další pokus.")
        
        # Interval mezi aktualizacemi
        time.sleep(interval_minutes * 60)

# Inicializace MQTT klienta
client = mqtt.Client()
client.on_message = on_message

# Připojení k MQTT brokeru a přihlášení k odběru
client.connect(BROKER_ADDRESS)
client.subscribe(REQUEST_TOPIC)
print(f"Poslouchám na tématu {REQUEST_TOPIC} a čekám na požadavky...")

# Spuštění zpracování zpráv na pozadí
client.loop_start()

# Spuštění pravidelného odesílání aktualizací o počasí
try:
    publish_regular_updates(client)
except KeyboardInterrupt:
    print("Server byl ukončen.")
finally:
    client.loop_stop()
    client.disconnect()
