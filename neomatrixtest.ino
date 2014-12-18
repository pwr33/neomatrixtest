// Test some adafruit functions
// Paul Rogers, December 2014.

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include <Metro.h>

#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif

#define PIN 6
#define ROWS 8
#define COLS 32 
#define MINDELAY 20
#define MAXDELAY 255

// MATRIX DECLARATION:
// Parameter 1 = width of NeoPixel matrix
// Parameter 2 = height of matrix
// Parameter 3 = pin number (most are valid)
// Parameter 4 = matrix layout flags, add together as needed:
//   NEO_MATRIX_TOP, NEO_MATRIX_BOTTOM, NEO_MATRIX_LEFT, NEO_MATRIX_RIGHT:
//     Position of the FIRST LED in the matrix; pick two, e.g.
//     NEO_MATRIX_TOP + NEO_MATRIX_LEFT for the top-left corner.
//   NEO_MATRIX_ROWS, NEO_MATRIX_COLUMNS: LEDs are arranged in horizontal
//     rows or in vertical columns, respectively; pick one or the other.
//   NEO_MATRIX_PROGRESSIVE, NEO_MATRIX_ZIGZAG: all rows/columns proceed
//     in the same order, or alternate lines reverse direction; pick one.
//   See example below for these values in action.
// Parameter 5 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)


// Example for NeoPixel Shield.  In this application we'd like to use it
// as a 5x8 tall matrix, with the USB port positioned at the top of the
// Arduino.  When held that way, the first pixel is at the top right, and
// lines are arranged in columns, progressive order.  The shield uses
// 800 KHz (v2) pixels that expect GRB color data.
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(COLS, ROWS, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);

const int numcolors = 7;
const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255), matrix.Color(255, 255, 255),
  matrix.Color(255, 255, 0), matrix.Color(0, 255, 255), matrix.Color(255, 0, 255) };

// some test colours
#define ACID_GREEN matrix.Color(176,191,26)
#define ATOMIC_TANGERINE matrix.Color(255,153,102)
#define BRILLIANT_LAVENDER matrix.Color(244,187,255)
#define BRINK_PINK matrix.Color(251,96,127)
#define BRITISH_RACING_GREEN matrix.Color(0,66,37)
#define BATTLESHIP_GREY matrix.Color(132,132,130)
#define CANARY_YELLOW matrix.Color(255,239,0)
#define CARIBBEAN_GREEN matrix.Color(0,204,153)

#define CAFE_AU_LAIT matrix.Color(166,123,91)
#define CAMOUFLAGE_GREEN matrix.Color(120,134,107)


Metro TmrMetro = Metro(20000);  

void setup() {
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(40);
  //matrix.setTextColor(colors[0]);
  matrix.fillScreen(0);
  randomSeed(analogRead(0));
  TmrMetro.reset();
  Serial.begin(9600);
}

unsigned int col_delay[COLS];
  
void randomisecoldelays()
{ for (int i=0; i<COLS; i++)
    col_delay[i] = random(MINDELAY,MAXDELAY);
}

void sweeprandom()
{ int x,y = 0;
  for (x=0; x <COLS; x++)
  { for (y=0; y < ROWS; y++)
    { matrix.drawPixel(x, y, colors[random(7)]);
    }
    matrix.show();
    delay(20);
  }
  delay(300);
  for (x=COLS; x >= 0; x--)
  { for (y=0; y < ROWS; y++)
    { matrix.drawPixel(x, y, colors[random(7)]);
    }
    matrix.show();
    delay(20);
  }
  delay(300);
}

void text()
{ int x    = matrix.width(); 
  matrix.setTextColor(colors[random(7)],matrix.Color(0,0,0));
  while (1)
  { matrix.setCursor(x, 0);    
    matrix.print(F("Merry Christmas and a Happy New Year"));
                    
    if(--x < -216) 
    { break;
    }
    matrix.show();
    delay(50);
  }
}  

void fill()
{ int16_t x[4], y[4], w, h, r;
  int i;
  for (i=0; i<numcolors; i++)
  { matrix.fillScreen(colors[i]);
    matrix.show();
    delay(1000);
  }
  for (i=0; i<numcolors; i++)
  { matrix.fillScreen(colors[i]);
    matrix.show();
    delay(200);
  }
  matrix.fillScreen(0);
}

void bright()
{ int x,y,c,b = 0;
  for (x=0; x <COLS; x++)
  { c = random(7);
    for (y=0; y < ROWS; y++)
    { b = (1<<(y+1))-2;
      matrix.drawPixel(x, y, colors[c],b);
      //Serial.println(b);
    }    
    matrix.show();
    delay(20);
  } 
}

void colourtest()
{  int x,y = 0;
   for (x=0; x<4; x++)
   { for (y=0; y<ROWS; y++)
       matrix.drawPixel(x,y,ACID_GREEN,0);
   }  
   for (x=4; x<8; x++)
   { for (y=0; y<ROWS; y++)
       matrix.drawPixel(x,y,ATOMIC_TANGERINE,0);
   }
   for (x=8; x<12; x++)
   { for (y=0; y<ROWS; y++)
       matrix.drawPixel(x,y,BRILLIANT_LAVENDER,0);
   }
   for (x=12; x<16; x++)
   { for (y=0; y<ROWS; y++)
       matrix.drawPixel(x,y,BRITISH_RACING_GREEN,0);
   }
   for (x=16; x<20; x++)
   { for (y=0; y<ROWS; y++)
       matrix.drawPixel(x,y,BRINK_PINK,0);
   }
   for (x=20; x<24; x++)
   { for (y=0; y<ROWS; y++)
       matrix.drawPixel(x,y,BATTLESHIP_GREY,0);
   }

   for (x=24; x<28; x++)
   { for (y=0; y<ROWS; y++)
       matrix.drawPixel(x,y,CANARY_YELLOW,0);
   }

   for (x=28; x<32; x++)
   { for (y=0; y<ROWS; y++)
       matrix.drawPixel(x,y,CARIBBEAN_GREEN,0);
   }
   matrix.show();   
   delay(5000);
}

void sweepfade()
{ 
}

byte stage = 0, maxstage=4;

void loop() 
{  
   if (TmrMetro.check()==1) 
   { if (++stage > maxstage) stage=0;
     matrix.fillScreen(0);
     TmrMetro.reset();
   }
    
   switch (stage)
   { case 0: text(); break;
     case 1: sweeprandom(); break;
     case 2: fill(); break;
     case 3: bright(); break;
     case 4: colourtest(); break;
   }
}
