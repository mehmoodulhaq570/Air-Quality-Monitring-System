// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID "TMPLbFfUzosl"
#define BLYNK_DEVICE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "Ol4vEuzoK7MkD12sTWpVHuqcrn2fW9gq"

// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Malik";
char pass[] = "00000000";

#define DHTPIN D2          // What digital pin we're connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11     // DHT 11
int mq135 = A0; // smoke sensor is connected with the analog pin A0 
int data = 0;
#define pirPin D0

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;



void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  data = analogRead(mq135); 
  Blynk.virtualWrite(V2, data); //virtual pin V3

  if (data > 600 )
  {
    Blynk.notify("Smoke Detected!!!"); 
  }
  int pirValue = digitalRead(pirPin);
  if (pirValue) 
  { 
    Serial.println("==> Motion detected");
    Blynk.notify("T==> Motion detected");  
  }
  Blynk.virtualWrite(V1, h);
  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V3, data);
  Blynk.virtualWrite(V4, pirValue);
}

void setup()
{
  // Debug console
  Serial.begin(115200);

  Blynk.begin(auth, ssid, pass);


  dht.begin();
  pinMode(pirPin, INPUT);

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}
