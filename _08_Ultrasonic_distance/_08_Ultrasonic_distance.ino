#define trigger 4
#define ecco 3

void setup() {
  pinMode(trigger, OUTPUT);
  pinMode(ecco, INPUT);
  Serial.begin(9600);       
}

void loop() {
  long duration, distance ; 
  digitalWrite(trigger, LOW);
  delayMicroseconds(30);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  duration = pulseIn(ecco, HIGH);
  distance = 0.034*duration/2;
  Serial.print("Distance between object and Sensor = ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(2000); 

}

