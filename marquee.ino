/*
Library examples for TM1638.

Copyright (C) 2011 Ricardo Batista <rjbatista at gmail dot com>

This program is free software: you can redistribute it and/or modify
it under the terms of the version 3 GNU General Public License as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <TM1638.h>

// define a module on data pin 8, clock pin 9 and strobe pin 7
TM1638 module(8, 9, 7);
int delayTime = 70;

void setup() {
  Serial.begin(19200);
  // display a hexadecimal number and set the left 4 dots
  Serial.println("Setup complete");
  module.setDisplayToString("        ");
  Marquee("PLEASE PRESS A BUTTON TO CONTINUE");
  
}

void loop() {
  byte keys = module.getButtons();


  // light the first 4 red LEDs and the last 4 green LEDs as the buttons are pressed
  module.setLEDs(((keys & 0xF0) << 8) | (keys & 0xF));
  
  if ( (int)keys == 1)
    Marquee("HELLO HELLO HELLO. THIS IS A TEST. PLEASE DEPOSIT LULZ HERE ");
  if ( (int)keys == 2)
    Count(1500);
  if ( (int)keys == 4)
    LightLeds();
  if ( (int)keys > 4)
    Marquee("PRESS 1-3 ");
}

void LightLeds()
{
  for ( int i = 0; i < 8 ; i++ )  
  {
   module.setLED(TM1638_COLOR_RED, i);
   delay(delayTime);
  }

  for ( int i = 7; i > -1 ; i-- )  
  {
     module.setLED(TM1638_COLOR_NONE, i);
     delay(delayTime);
  }
   
  for ( int i = 0; i < 8 ; i++ ) 
 { 
   module.setLED(TM1638_COLOR_GREEN, i);
   delay(delayTime);
 }

  for ( int i = 7; i > -1 ; i-- )  
  {
     module.setLED(TM1638_COLOR_NONE, i);
     delay(delayTime);
  }
}

void Count(int value)
{
  for( int i = 0; i <= value; i++)
  {
      module.setDisplayToDecNumber(i,0);
  }
  
  module.clearDisplay();  
}
void Marquee(String text)
{
   int strLen = text.length();
   int j = 8;
   String marquee = "";
   
   for ( int i = 0; i < strLen + 8; i++ )
   { 
       if ( strLen > i ) 
         marquee += text.substring(constrain(i,0,strLen),constrain(i+1,0,strLen));  
        
       if ( strLen <= i ||  marquee.length() >= 9)
       {  
           marquee = marquee.substring(1,marquee.length());
           if ( strLen <= i  )
               marquee += " ";
       }
     
      module.setDisplayToString(marquee,0,j);
      
      if (j > 0 )
            j--;
            
  
      delay(delayTime);
   }
   
    module.clearDisplay();
}
