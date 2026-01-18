#define button 3
#define led 4


void setup() {
  pinMode(button, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {

  if(digitalread(button) == LOW){
    Serial.println("Button is pressed.");
    digitalWrite(led, HIGH);
  }
  else{
    Serial.println("Button is Open.");
    digitalWrite(led, LOW);
  }
  delay(2000);
}