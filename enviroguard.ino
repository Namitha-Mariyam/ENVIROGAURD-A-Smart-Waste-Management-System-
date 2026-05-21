#include <Servo.h>

// Servo objects 

Servo capServo; 

Servo bottomServo; 

Servo gateServo;

// Pin Definitions

const int capServoPin = 11; 

const int bottomServoPin = 10; 

const int gateServoPin = 9;

const int trigPin = 7; 

const int echoPin = 8;

const int moisturePin = A0; 

const int metalPin = 2; 

const int irpin = 4;

// Thresholds

const int distanceThreshold = 10; 

const int moistureThreshold = 750; 

bool waste_flag = false;

long duration; 

int distance; 

void setup() {

Serial.begin(9600);

capServo.attach(capServoPin); 

bottomServo.attach(bottomServoPin); 

gateServo.attach(gateServoPin);
pinMode(trigPin, OUTPUT); 

pinMode(echoPin, INPUT); 

pinMode(metalPin, INPUT); 

pinMode(irpin, INPUT);

capServo.write(0); // Cap closed 

bottomServo.write(90); // Default bin 

gateServo.write(0); // Gate closed

Serial.println("System ready...");

}

void loop() {

distance = getDistance();

Serial.print("Distance: "); 

Serial.println(distance);

if (distance <= distanceThreshold) { 

Serial.println("Human detected!");

capServo.write(180); 

delay(4000);

//capServo.write(0);

//delay(1000);

int irVal = digitalRead(irpin);

int moistureVal = analogRead(moisturePin); 

int metalVal = digitalRead(metalPin);
Serial.print("Moisture: "); 

Serial.println(moistureVal); 

Serial.print("Metal: "); 

Serial.println(metalVal);

String wasteType = "none"; 

bool waste_flag = false;

if (irVal == LOW) { // IR detected waste (assuming active LOW) 

if (moistureVal < moistureThreshold) {

wasteType = "wet"; 

rotateBottomServo(0); 

waste_flag = true;

} else if (metalVal == 1) { 

wasteType = "metal"; 

rotateBottomServo(180); 

waste_flag = true;

} else {

wasteType = "dry"; 

rotateBottomServo(90); 

waste_flag = true;

}

} else {

Serial.println("IR: No waste detected.");

}

Serial.print("Detected Waste Type: "); 

Serial.println(wasteType);

if (waste_flag == true) { 

delay(5000); 

rotateGateServo(90); 

delay(5000); 

rotateGateServo(0);

//waste_flag = false;
//delay(3000);

}

delay(2000);

} else {

Serial.println("No Human detected!"); 

capServo.write(0);

delay(500);

}

}

// Get distance from ultrasonic sensor 

int getDistance() { 

digitalWrite(trigPin, LOW); 

delayMicroseconds(2); 

digitalWrite(trigPin, HIGH); 

delayMicroseconds(10); 

digitalWrite(trigPin, LOW);

duration = pulseIn(echoPin, HIGH); 

return duration * 0.034 / 2;

}

// Smooth servo movement for platform 

void rotateBottomServo(int targetPos) { 

int currentPos = bottomServo.read();

if (currentPos < targetPos) {

for (int pos = currentPos; pos <= targetPos; pos++) { 

bottomServo.write(pos);

delay(10);

}

} else {

for (int pos = currentPos; pos >= targetPos; pos--) { 

bottomServo.write(pos);

delay(10);
}

}

}

// Smooth servo movement for gate 

void rotateGateServo(int targetPos) { 

int currentPos = gateServo.read();

if (currentPos < targetPos) {

for (int pos = currentPos; pos <= targetPos; pos++) { 

gateServo.write(pos);

delay(10);

}

} else {

for (int pos = currentPos; pos >= targetPos; pos--) { 

gateServo.write(pos);

delay(10);

}

}

}
