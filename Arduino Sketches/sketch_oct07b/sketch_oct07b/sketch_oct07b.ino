void setup() 
{
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
}

void loop() 
{
  if(digitalRead(2) == LOW)
  {
      Serial.write("It's on!!! :)");
  }
  else
  {
      Serial.write("Off"); 
  }
}
