#include <LEDMatrixDriver.hpp>

/**
ATTENTION
This is pretty much a copy-paste of the LEDMatrixDriver "SetPixel" code example,
modified to take input from 2 potentiometers
*/

// As LEDMatrixDriver uses the SPI library, the CS pin must not be
// one of the reserved pins by SPI (from 10 to 13 included)
const uint8_t LEDMATRIX_CS_PIN = 8;

// Define LED Matrix dimensions (0-n) - eg: 32x8 = 31x7
const int LEDMATRIX_WIDTH = 7;
const int LEDMATRIX_HEIGHT = 7;
const int LEDMATRIX_SEGMENTS = 1;

// The LEDMatrixDriver class instance
LEDMatrixDriver lmd(LEDMATRIX_SEGMENTS, LEDMATRIX_CS_PIN);

// Flushing column display must be delayed 
// with the same value as row, or else blinking happens!
#define DELAY 10

int x = 0, y = 0;
bool s = true;  // start with led on

const int colSensorPin = A0;
const int rowSensorPin = A2;

int sensorValueX = 0;
int sensorValueY = 0;



void setup() {
  // init the display
  lmd.setEnabled(true);
  lmd.setIntensity(2);   // 0 = low, 10 = high
}


void loop() {
    // the value for X (columns) is negated so that
    // the column goes right when turning the potentiometer
    // clockwise, and left when counterclockwise. 
    // It's more intuitive the way I wired it, that's all :)
    // c.f my video
  sensorValueX = -analogRead(colSensorPin); 
  sensorValueY = -analogRead(rowSensorPin);
  
  // for x, not sure why, but with upper bound to 7 
  // it never reached the last row, hence the 8
  x = map(sensorValueX, -1023, 0, 0, 8); 
  y = map(sensorValueY, -1023, 0, 0, 7);
  
  // Since the driver can't light all 64 LEDs at once
  // first we prepare the rows, flush them to the driver... 
  for(int i =0; i <8; i++) {
    lmd.setPixel(i,y,s);
    }
    lmd.display();
    delay(DELAY);
    
    //... and then do the same for the columns.    
    lmd.setColumn(x,0xff); // 0xFF = set all LEDs in column
  lmd.display();
  delay(DELAY);
  
  lmd.clear();
}