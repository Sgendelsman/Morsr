#include <TimerOne.h>
#include "Wire.h"
#include <rgb_lcd.h>

// LCD Screen constants
rgb_lcd lcd;
const int colorR = 0;
const int colorG = 255;
const int colorB = 0;

// button that sends Telegraph signal
const int buttonPin = 2;

/* NUMBERS FOR TIME FOR DOTS/DASHES */
double time_passed = 0.0000000;

double dot_length = 0.050;
int num_dots = 1;
double dash_length = 0.500;
int num_dashes = 1;

double space_between_dots = 0.050;
int num_space_dots = 1;
double space_between_words = 1.000;
int num_space_words = 1;
/* -------------------------------- */

int character[5];
int char_counter = 0;

int morse_code_alphabet[36][5];
char corresponding_letter[36];

void setup() {
  //we hardcoded in the translation for each letter of the alphabet, with room for expansion into numbers.
  morse_code_alphabet[0][0] = 0;
  morse_code_alphabet[0][1] = 1;
  morse_code_alphabet[0][2] = -1;
  morse_code_alphabet[0][3] = -1;
  morse_code_alphabet[0][4] = -1;
  corresponding_letter[0] = 'a';

  morse_code_alphabet[1][0] = 1;
  morse_code_alphabet[1][1] = 0;
  morse_code_alphabet[1][2] = 0;
  morse_code_alphabet[1][3] = 0;
  morse_code_alphabet[1][4] = -1;
  corresponding_letter[1] = 'b';

  morse_code_alphabet[2][0] = 1;
  morse_code_alphabet[2][1] = 0;
  morse_code_alphabet[2][2] = 1;
  morse_code_alphabet[2][3] = 0;
  morse_code_alphabet[2][4] = -1;
  corresponding_letter[2] = 'c';

  morse_code_alphabet[3][0] = 1;
  morse_code_alphabet[3][1] = 0;
  morse_code_alphabet[3][2] = 0;
  morse_code_alphabet[3][3] = -1;
  morse_code_alphabet[3][4] = -1;
  corresponding_letter[3] = 'd';

  morse_code_alphabet[4][0] = 0;
  morse_code_alphabet[4][1] = -1;
  morse_code_alphabet[4][2] = -1;
  morse_code_alphabet[4][3] = -1;
  morse_code_alphabet[4][4] = -1;
  corresponding_letter[4] = 'e';

  morse_code_alphabet[5][0] = 0;
  morse_code_alphabet[5][1] = 0;
  morse_code_alphabet[5][2] = 1;
  morse_code_alphabet[5][3] = 0;
  morse_code_alphabet[5][4] = -1;
  corresponding_letter[5] = 'f';

  morse_code_alphabet[6][0] = 1;
  morse_code_alphabet[6][1] = 1;
  morse_code_alphabet[6][2] = 0;
  morse_code_alphabet[6][3] = -1;
  morse_code_alphabet[6][4] = -1;
  corresponding_letter[6] = 'g';

  morse_code_alphabet[7][0] = 0;
  morse_code_alphabet[7][1] = 0;
  morse_code_alphabet[7][2] = 0;
  morse_code_alphabet[7][3] = 0;
  morse_code_alphabet[7][4] = -1;
  corresponding_letter[7] = 'h';

  morse_code_alphabet[8][0] = 0;
  morse_code_alphabet[8][1] = 0;
  morse_code_alphabet[8][2] = -1;
  morse_code_alphabet[8][3] = -1;
  morse_code_alphabet[8][4] = -1;
  corresponding_letter[8] = 'i';

  morse_code_alphabet[9][0] = 0;
  morse_code_alphabet[9][1] = 1;
  morse_code_alphabet[9][2] = 1;
  morse_code_alphabet[9][3] = 1;
  morse_code_alphabet[9][4] = -1;
  corresponding_letter[9] = 'j';

  morse_code_alphabet[10][0] = 1;
  morse_code_alphabet[10][1] = 0;
  morse_code_alphabet[10][2] = 1;
  morse_code_alphabet[10][3] = -1;
  morse_code_alphabet[10][4] = -1;
  corresponding_letter[10] = 'k';

  morse_code_alphabet[11][0] = 0;
  morse_code_alphabet[11][1] = 1;
  morse_code_alphabet[11][2] = 0;
  morse_code_alphabet[11][3] = 0;
  morse_code_alphabet[11][4] = -1;
  corresponding_letter[11] = 'l';

  morse_code_alphabet[12][0] = 1;
  morse_code_alphabet[12][1] = 1;
  morse_code_alphabet[12][2] = -1;
  morse_code_alphabet[12][3] = -1;
  morse_code_alphabet[12][4] = -1;
  corresponding_letter[12] = 'm';

  morse_code_alphabet[13][0] = 1;
  morse_code_alphabet[13][1] = 0;
  morse_code_alphabet[13][2] = -1;
  morse_code_alphabet[13][3] = -1;
  morse_code_alphabet[13][4] = -1;
  corresponding_letter[13] = 'n';

  morse_code_alphabet[14][0] = 1;
  morse_code_alphabet[14][1] = 1;
  morse_code_alphabet[14][2] = 1;
  morse_code_alphabet[14][3] = -1;
  morse_code_alphabet[14][4] = -1;
  corresponding_letter[14] = 'o';

  morse_code_alphabet[15][0] = 0;
  morse_code_alphabet[15][1] = 1;
  morse_code_alphabet[15][2] = 1;
  morse_code_alphabet[15][3] = 0;
  morse_code_alphabet[15][4] = -1;
  corresponding_letter[15] = 'p';

  morse_code_alphabet[16][0] = 1;
  morse_code_alphabet[16][1] = 1;
  morse_code_alphabet[16][2] = 0;
  morse_code_alphabet[16][3] = 1;
  morse_code_alphabet[16][4] = -1;
  corresponding_letter[16] = 'q';

  morse_code_alphabet[17][0] = 0;
  morse_code_alphabet[17][1] = 1;
  morse_code_alphabet[17][2] = 0;
  morse_code_alphabet[17][3] = -1;
  morse_code_alphabet[17][4] = -1;
  corresponding_letter[17] = 'r';

  morse_code_alphabet[18][0] = 0;
  morse_code_alphabet[18][1] = 0;
  morse_code_alphabet[18][2] = 0;
  morse_code_alphabet[18][3] = -1;
  morse_code_alphabet[18][4] = -1;
  corresponding_letter[18] = 's';

  morse_code_alphabet[19][0] = 1;
  morse_code_alphabet[19][1] = -1;
  morse_code_alphabet[19][2] = -1;
  morse_code_alphabet[19][3] = -1;
  morse_code_alphabet[19][4] = -1;
  corresponding_letter[19] = 't';

  morse_code_alphabet[20][0] = 0;
  morse_code_alphabet[20][1] = 0;
  morse_code_alphabet[20][2] = 1;
  morse_code_alphabet[20][3] = -1;
  morse_code_alphabet[20][4] = -1;
  corresponding_letter[20] = 'u';

  morse_code_alphabet[21][0] = 0;
  morse_code_alphabet[21][1] = 0;
  morse_code_alphabet[21][2] = 0;
  morse_code_alphabet[21][3] = 1;
  morse_code_alphabet[21][4] = -1;
  corresponding_letter[21] = 'v';

  morse_code_alphabet[22][0] = 0;
  morse_code_alphabet[22][1] = 1;
  morse_code_alphabet[22][2] = 1;
  morse_code_alphabet[22][3] = -1;
  morse_code_alphabet[22][4] = -1;
  corresponding_letter[22] = 'w';

  morse_code_alphabet[23][0] = 1;
  morse_code_alphabet[23][1] = 0;
  morse_code_alphabet[23][2] = 0;
  morse_code_alphabet[23][3] = 1;
  morse_code_alphabet[23][4] = -1;
  corresponding_letter[23] = 'x';

  morse_code_alphabet[24][0] = 1;
  morse_code_alphabet[24][1] = 0;
  morse_code_alphabet[24][2] = 1;
  morse_code_alphabet[24][3] = 1;
  morse_code_alphabet[24][4] = -1;
  corresponding_letter[24] = 'y';

  morse_code_alphabet[25][0] = 1;
  morse_code_alphabet[25][1] = 1;
  morse_code_alphabet[25][2] = 0;
  morse_code_alphabet[25][3] = 0;
  morse_code_alphabet[25][4] = -1;
  corresponding_letter[25] = 'z';
  
  pinMode(2, INPUT_PULLUP);
  pinMode(3, OUTPUT);
  pinMode(13, OUTPUT);
  
  for(int i = 0; i < 5; i++)
    character[i] = -1;
    
  attachInterrupt(digitalPinToInterrupt(2), PressedDown, CHANGE);
  Timer1.initialize(10000);
  Timer1.attachInterrupt(incrementTime);
  
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setRGB(colorR, colorG, colorB);
  lcd.print("The TeleGraph!");
}

void incrementTime()
{
  time_passed += .01;
}

void loop() {
  // No loop code needed!
} 

void addCharInput()
{ 
  for(int i = 0; i < 26; i++)
  {
    int found_letter = 1;
    for(int j = 0; j < 5; j++)
    {
      if(morse_code_alphabet[i][j] == character[j])
        found_letter = 1 && found_letter;
      else
        found_letter = 0;
    }
    if(found_letter == 1)
    {
       Serial.print(corresponding_letter[i]);
       break;
    }
  }

  for(int i = 0; i < 5; i++)
  {
    /*if(character[i] == 1)
      Serial.write("-");
    else if(character[i] == 0)
      Serial.write(".");*/
    character[i] = -1;
  }
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
  if(digitalRead(2) == HIGH) // OFF -> ON, space between dot/dash, space between words
  {
    double space_error = abs(space_between_dots - time_passed);
    double word_error = abs(space_between_words - time_passed);

    if(char_counter != 0 && space_error < word_error) // Space between dot/dash
    {
      if(abs(space_between_dots - time_passed) / space_between_dots < 0.4)
      {
        space_between_dots = (space_between_dots * num_space_dots + time_passed / 2) / (num_space_dots + 1);
        num_space_dots++;
      }
      
      justAdded = 0;
    }
    else // Space between word
    {
      if(abs(space_between_words - time_passed) / space_between_words < 0.4)
      {
        space_between_words = (space_between_words * num_space_words + time_passed / 2) / (num_space_words + 1);
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
        dot_length = (dot_length * num_dots + time_passed / 2) / (num_dots + 1);
        num_dots++;
      }
      
      character[char_counter++] = 0;
      
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
        dash_length = (dash_length * num_dashes + time_passed / 2) / (num_dashes + 1);
        num_dashes++;
      }
      
      character[char_counter++] = 1;

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
  delay(10);
}
