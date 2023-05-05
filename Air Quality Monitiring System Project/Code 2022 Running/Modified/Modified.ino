#include "DHT.h"
#include <LiquidCrystal.h>

#define DHTPIN 10     // Digital pin connected to the DHT sensor

#define DHTTYPE DHT11   // DHT 11


const int mq135_aqi_sensor = A0;
const int green_led = 9;
const int buzzer = 8;
int PIR= 13; // Define PIR pin
int val= 0;
int aqi_ppm = 0;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);

  lcd.clear();
  lcd.begin (16, 2);

  Serial.println("AQI Alert System");
  lcd.setCursor(0, 0);
  lcd.print("AQI Alert System");

  pinMode (mq135_aqi_sensor, INPUT);
  pinMode (green_led, OUTPUT);
  pinMode (buzzer, OUTPUT);
  pinMode(PIR, INPUT);

  digitalWrite(green_led, LOW);
  digitalWrite(buzzer, LOW);

  dht.begin();
  delay(2000);
}

void loop() {
  aqi_ppm = analogRead(mq135_aqi_sensor);

  Serial.print("Air Quality: ");
  Serial.println(aqi_ppm);

  lcd.setCursor(0, 0);
  lcd.print("Air Quality: ");
  lcd.print(aqi_ppm);


  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  val = digitalRead(PIR);


  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F(" Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("C "));
  Serial.print(f);
  Serial.print(F("F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("C "));
  Serial.print(hif);
  Serial.println(F("F"));

  if(val == HIGH){
  digitalWrite(green_led, HIGH);
  digitalWrite(buzzer, LOW);
  Serial.println("Movement Detected"); // Print this text in Serial Monitor
  }
  else 
  {
    digitalWrite(green_led, HIGH);
    digitalWrite(buzzer, LOW);
    Serial.println("Movement not Detected");
  }

  if ((aqi_ppm >= 0) && (aqi_ppm <= 50))
  {
    lcd.setCursor(0, 1);
    lcd.print("AQI Good");
    Serial.println("AQI Good");
    digitalWrite(green_led, HIGH);
    digitalWrite(buzzer, LOW);
  }
  else if ((aqi_ppm >= 51) && (aqi_ppm <= 100))
  {
    lcd.setCursor(0, 1);
    lcd.print("AQI Moderate");
    Serial.println("AQI Moderate");
    tone(green_led, 1000, 200);
    digitalWrite(buzzer, LOW);
  }

  else if ((aqi_ppm >= 101) && (aqi_ppm <= 200))
  {
    lcd.setCursor(0, 1);
    lcd.print("AQI Unhealthy");
    Serial.println("AQI Unhealthy");
    digitalWrite(green_led, LOW);
    digitalWrite(buzzer, LOW);
  }
  else if ((aqi_ppm >= 201) && (aqi_ppm <= 600))
  {
    lcd.setCursor(0, 1);
    lcd.print("AQI V. Unhealthy");
    Serial.println("AQI V. Unhealthy");
    digitalWrite(green_led, LOW);
    digitalWrite(buzzer, LOW);
  }
  else if (aqi_ppm >= 600)
  {
    lcd.setCursor(0, 1);
    lcd.print("AQI Hazardous");
    Serial.println("AQI Hazardous");
    digitalWrite(green_led, HIGH);
    digitalWrite(buzzer, HIGH);
  }
  delay (2000);
}
