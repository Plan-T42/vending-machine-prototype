#define SWITCHPin 7
#define LEDPin    13

void setup() {
  // put your setup code here, to run once:
  pinMode(SWITCHPin, INPUT);
  pinMode(LEDPin, OUTPUT);
  digitalWrite(SWITCHPin, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(SWITCHPin) == LOW)
  {
    digitalWrite(LEDPin, HIGH);
  }
  else
  {
    digitalWrite(LEDPin, LOW);
  }

}
