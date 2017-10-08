int prevState = HIGH;

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, OUTPUT);
  pinMode(13, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(2), PressedDown, CHANGE);
}

void loop() 
{
  
}

void PressedDown()
{
  if(digitalRead(2) == LOW)
  {
    digitalWrite(3, HIGH);
    digitalWrite(13, HIGH);
  }
  else
  {
    digitalWrite(3, LOW);
    digitalWrite(13, LOW);
  }
}
