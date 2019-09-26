
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"


Adafruit_AlphaNum4 alpha4 = Adafruit_AlphaNum4();
Adafruit_8x16minimatrix matrix = Adafruit_8x16minimatrix();

char scrollingtext[] = "Oh, fuck off Boris. ";
char displaybuffer[4] = {' ', ' ', ' ', ' '};
int i = 0;
int j = 20;
int textlen;

void setup() {
  // put your setup code here, to run once:

  matrix.begin(0x71);  // pass in the address
  alpha4.begin(0x70);  // pass in the address

  textlen = strlen(scrollingtext);
}

void loop() {
  // put your main code here, to run repeatedly:

  displaybuffer[0] = scrollingtext[i];
  displaybuffer[1] = scrollingtext[(i + 1) % textlen];
  displaybuffer[2] = scrollingtext[(i + 2) % textlen];
  displaybuffer[3] = scrollingtext[(i + 3) % textlen];

  alpha4.writeDigitAscii(0, displaybuffer[0]);
  alpha4.writeDigitAscii(1, displaybuffer[1]);
  alpha4.writeDigitAscii(2, displaybuffer[2]);
  alpha4.writeDigitAscii(3, displaybuffer[3]);
  alpha4.writeDisplay();
  
  i++;
  if (i == textlen) {
    i = 0;
  }

  j--;
  matrix.clear();
  /* 0,0 is the centre? of the 16x8 */
  matrix.drawCircle(3 + (j % 2), j, 3, LED_ON);
  matrix.writeDisplay();  // write the changes we just made to the display

  if (j == -4) {
    j = 20;
  }
  
  delay(500);
}
