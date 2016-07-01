#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>
#include <SPI.h>
#include <SD.h>


#define sclk 13
#define mosi 11
#define miso 12
#define cs   5
#define rst  6
#define dc   4

const int numOfPoints = 25;

int point[numOfPoints][3];
uint16_t col[numOfPoints];

Adafruit_SSD1351 tft = Adafruit_SSD1351(cs, dc, rst);

void setup() {
  tft.begin();
  tft.quickFill(0x0000);
}

int getClosest(int x, int y){
  int squares[numOfPoints];
  int index = 0;
  int sorted[numOfPoints];
  for (int i=0; i < (numOfPoints); i++){
    squares[i] = ( (x - point[i][0]) * (x - point[i][0]) ) + ( (y - point[i][1]) * (y - point[i][1]) ) ;
  }

  int smallest = squares[0];
  for (int i=0; i < (numOfPoints); i++){
    if (squares[i] < smallest){
      smallest = squares[i];
    }
  }
  
  for (int i=0; i < (numOfPoints); i++){
    if (squares[i] == smallest){
      index = i;
      break;
    }
  }
  
  return index;
}

void loop() {
  tft.quickFill(0x0000);
  for (int i=0; i < (numOfPoints); i++){
    point[i][0] = (int) random(tft.width());
    point[i][1] = (int) random(tft.height());
    
    col[i] = ((random(256) / 8) << 11) | ((random(256) / 4) << 5) | (random(256) / 8);
  }

  for (int y=0; y < tft.height(); y++){
    for (int x=0; x < tft.width(); x++){
      int i = getClosest(x,y);
      tft.drawPixel(x,y,col[i]);
    }
  }
  
  delay(5000);
}
