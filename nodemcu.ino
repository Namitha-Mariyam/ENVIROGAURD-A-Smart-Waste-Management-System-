#define BLYNK_TEMPLATE_ID "TMPL3JbtwuVjf"

#define BLYNK_TEMPLATE_NAME "ENVIRO GUARD MONITOR"

#define BLYNK_AUTH_TOKEN "upOlM1m39eQtL96TH7Mb2tWT7mKPa5KD" 

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h> 

#include <BlynkSimpleEsp8266.h> 

#include <SoftwareSerial.h> 

#include <TinyGPS++.h>

char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "GNXS-2.4G-55E9F0"; // Replace with your WiFi name
char pass[] = "8547122440@"; // Replace with your WiFi password

// Pins for Dry Waste 

const int trigDry = 12; 

const int echoDry = 14;

// Wet Waste

//const int trigWet = 15;

//const int echoWet = 13;

// Metal Waste

const int trigMetal = 0; 

const int echoMetal = 2;

#define GPS_RX 13

#define GPS_TX 15

#define GPS_BAUD 9600

//define sound velocity in cm/uS 

#define SOUND_VELOCITY 0.034

#define CM_TO_INCH 0.393701 

#define BIN_HEIGHT 15.0 // in cm 

#define FULL_THRESHOLD 5.0

long durationDry, durationMetal; 

float distanceDry, distanceMetal;

//float distanceInch;

TinyGPSPlus gps;

SoftwareSerial gpsSerial(GPS_RX, GPS_TX); // GPS TX → D7 (RX)

BlynkTimer timer;

float latitude, longitude;

void setup() {
  Serial.begin(115200); 

Blynk.begin(auth, ssid, pass);

// Call sendSensor() every 2 seconds 

timer.setInterval(2000L, sendData); 

pinMode(trigDry, OUTPUT); 

pinMode(echoDry, INPUT);

//pinMode(trigWet, OUTPUT);

//pinMode(echoWet, INPUT);

gpsSerial.begin(GPS_BAUD); 

Serial.println("System ready");

pinMode(trigMetal, OUTPUT); 

pinMode(echoMetal, INPUT);

}

int getDistance(int trigPin, int echoPin) { 

digitalWrite(trigPin, LOW); 

delayMicroseconds(2); 

digitalWrite(trigPin, HIGH); 

delayMicroseconds(10); 

digitalWrite(trigPin, LOW);

long duration = pulseIn(echoPin, HIGH); 

return duration * SOUND_VELOCITY / 2;

}

void sendData() {

distanceDry = getDistance(trigDry, echoDry); 

distanceMetal = getDistance(trigMetal, echoMetal);

Blynk.virtualWrite(V2, distanceDry);
Blynk.virtualWrite(V3, distanceMetal);

Serial.print("Dry Bin Distance (cm): "); 

Serial.println(distanceDry); 

Serial.print("Metal Bin Distance (cm): "); 

Serial.println(distanceMetal);

// --- GPS LOCATION ---

while (gpsSerial.available()) { 

gps.encode(gpsSerial.read());

}

if (gps.location.isValid()) { 

latitude = gps.location.lat(); 

longitude = gps.location.lng();

} else {

latitude = 8.549058;

longitude = 76.938528;

Serial.println("Using hardcoded coordinates...");

}

Blynk.virtualWrite(V0, String(latitude, 6)); // Latitude 

Blynk.virtualWrite(V1, String(longitude, 6)); // Longitude

Serial.print("Latitude: "); 

Serial.println(latitude, 6); 

Serial.print("Longitude: "); 

Serial.println(longitude, 6);

// Alert logic

bool dryFull = distanceDry <= 8;

bool metalFull = (distanceMetal > 5.0 && distanceMetal < 14.0);
if (dryFull || metalFull) {

String alertMsg = "Full Bin Alert: "; 

if (dryFull) alertMsg += "Dry ";

if (metalFull) alertMsg += "Metal ";

// Append location info 

alertMsg += "| Location: "; 

alertMsg += String(latitude, 6); 

alertMsg += ", ";

alertMsg += String(longitude, 6);

//Blynk.logEvent("alert", alertMsg); 

Serial.println("Alert Sent: " + alertMsg);

}

Serial.println(" ");

}

void loop() { 

Blynk.run();

timer.run();

}
