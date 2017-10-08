#include <TimerOne.h>
#include "Wire.h"
#include "Lewis.h"
#include <rgb_lcd.h>

rgb_lcd lcd;
Lewis Morse;

const int colorR = 255;
const int colorG = 176;
const int colorB = 0;
const int buttonPin = 2;

/* NUMBERS FOR TIME FOR DOTS/DASHES */
double time_passed = 0.0000000;

double dot_length = 0.050;
int num_dots = 1;
double dash_length = 0.350;
int num_dashes = 1;

double space_between_dots = 0.050;
int num_space_dots = 1;
double space_between_words = 1.000;
int num_space_words = 1;
/* -------------------------------- */

char character[5];
int char_counter = 0;

const char morse_code_alphabet[36][5];
char corresponding_letter[36];

void setup() {
  morse_code_alphabet[0] = ".-///";
  corresponding_letter[0] = { 'a' };
  
  pinMode(2, INPUT_PULLUP);
  pinMode(3, OUTPUT);
  pinMode(13, OUTPUT);

  for(int i = 0; i < 5; i++)
    character[i] = '/';
    
  attachInterrupt(digitalPinToInterrupt(2), PressedDown, CHANGE);
  Timer1.initialize(10000);
  Timer1.attachInterrupt(incrementTime);
  
  Serial.begin(9600);
  //lcd.begin(16, 2);
  //lcd.setRGB(colorR, colorG, colorB);
  //Morse.begin(9);
}

void incrementTime()
{
  time_passed += .01;
}

void loop() {
  /*float secondsHeld = 0;
  int isHeld = 1;
  while(digitalRead(buttonPin)==HIGH){
        secondsHeld+=1;
        delay(200);
    }
  if (secondsHeld >=2) {
    lcd.print("-");
    tone(4);
    delay(1000);
    digitalWrite(4, LOW);
  }
  else if (secondsHeld >0){
    lcd.print(". ");
    digitalWrite(4, HIGH);
    delay(30);
    digitalWrite(4, LOW);
    
  }*/
} 

void addCharInput()
{
  for(int i = 0; i < 36; i++)
  {
    int found_letter = 0;
    for(int j = 0; j < 5 && character[j] != -1; j++)
    {
      if(morse_code_alphabet[i][j] == character[j])
        found_letter = 1;
      else
        found_letter = 0;
      /*if(character[i] == 1)
        Serial.write("-");
      else if(character[i] == 0)
        Serial.write(".");
      character[i] = -1;*/
    }
    if(found_letter == 1)
    {
       Serial.write(corresponding_letter[i]);
       break;
    }
  }
  Serial.write(" ");
  char_counter = 0;
}


void print(double value) 
{
  char outstr[15];
  dtostrf(value,7, 3, outstr);

  Serial.println(outstr);
}

int justAdded = 0;

void PressedDown()
{
  if(digitalRead(2) == LOW) // OFF -> ON, space between dot/dash, space between words
  {
    double space_error = abs(space_between_dots - time_passed);
    double word_error = abs(space_between_words - time_passed);

    if(char_counter != 0 && space_error < word_error) // Space between dot/dash
    {
      if(abs(space_between_dots - time_passed) / space_between_dots < 0.4)
      {
        space_between_dots = (space_between_dots * num_space_dots + time_passed) / (num_space_dots + 1);
        num_space_dots++;
      }
      
      justAdded = 0;
    }
    else // Space between word
    {
      if(abs(space_between_words - time_passed) / space_between_words < 0.4)
      {
        space_between_words = (space_between_words * num_space_words + time_passed) / (num_space_words + 1);
        num_space_words++;
      }
      
      if(!justAdded)
        addCharInput();
    }
    
    digitalWrite(3, HIGH);
    digitalWrite(13, HIGH);
  }
  else // ON -> OFF, dot/dash
  {
    double dot_error = abs(dot_length - time_passed);
    double dash_error = abs(dash_length - time_passed);
    
    if(dot_error < dash_error) // Dot
    {
      if(abs(dot_length - time_passed) / dot_length < 0.4)
      {
        dot_length = (dot_length * num_dots + time_passed) / (num_dots + 1);
        num_dots++;
      }
      
      character[char_counter++] = '.';
      
      justAdded = 0;
      if(char_counter == 5)
      {
        addCharInput();
        justAdded = 1;
      }
    }
    else // Dash
    {
      if(abs(dash_length - time_passed) / dash_length < 0.4)
      {
        dash_length = (dash_length * num_dashes + time_passed) / (num_dashes + 1);
        num_dashes++;
      }
      
      character[char_counter++] = '-';

      justAdded = 0;
      if(char_counter == 5)
      {
        addCharInput();
        justAdded = 1;
      }
    }
    digitalWrite(3, LOW);
    digitalWrite(13, LOW);
  }

  time_passed = 0.000000;
  delay(20);
}
