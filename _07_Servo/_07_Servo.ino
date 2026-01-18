#include <Servo.h>
Servo myservo;
#define sensor A0
#define servo_pin 9
int x, angle;

void setup() {
  Serial.begin(9600);
  myservo.attach(servo_pin);
  pinMode(sensor, INPUT);  
}

void loop() {
 x = analogRead(sensor);
 angle = map(x, 0, 1023, 0, 180);
  
 Serial.print("Sensor Value = ");
 Serial.print(x);
 Serial.print("    Angle Rotation = ");
 Serial.println(angle);
 myservo.write(angle);  
 delay(1000);
}
