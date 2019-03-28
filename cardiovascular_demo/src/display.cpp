#include "display.h"
#include "heart.h"


Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
Adafruit_STMPE610 ts = Adafruit_STMPE610(STMPE_CS);
screenStateEnum screen_state;
screenStateEnum last_screen_state;
quadrantEnum touch_quadrant;
quadrantEnum last_touch_quadrant;
int last_x_touch;
int last_y_touch;

void handleTouch(){
    if (ts.bufferEmpty()){
        return;
    }
    tft.setRotation(1);
    TS_Point p = ts.getPoint();
    delay(50);

    while (!ts.bufferEmpty()){
        TS_Point p2 = ts.getPoint();
        delay(50);
    }

    // Scale from ~0->4000 to tft.width using the calibration #'s
    // note X is vertical and y is horizontal in config used in this project
    p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
    p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());

    int vertical_middle = tft.width()/2;
    int horizontal_middle = tft.height()/2;

    if (p.x > 0 && p.y > 0 && p.x != last_x_touch && p.y != last_y_touch){
        if (p.x > vertical_middle)
        {
            if (p.y < horizontal_middle)
            {
                touch_quadrant = top_left;
                Serial.println("top left touch");
            }
            else
            {
                touch_quadrant = top_right;
                Serial.println("top right touch");
            }
        }
        else
        {
            if (p.y < horizontal_middle)
            {
                touch_quadrant = bottom_left;
                Serial.println("bottom left touch");
            }
            else
            {
                touch_quadrant = bottom_right;
                Serial.println("bottom right touch");
            }
        }
    }
}

void handleDisplay(){
    if(screen_state != last_screen_state || screen_state != home){
        last_screen_state = screen_state;
        switch(screen_state){
            case home:
                displayHome();
                break;
            case pumping:
                displayPumping();
                break;
            case slow_pumping:
                displaySlowPumping();
                break;
            default:
                displayHome();
                break;
        }
    }
}

void displayGrid(){
    tft.setRotation(1);
    uint16_t x_width = tft.width() / 2;
    uint16_t y_height = tft.height() / 2;

    //clear screen
    tft.fillScreen(ILI9341_BLACK);

    // draw borders
    tft.drawRect(0, 0, x_width, y_height, ILI9341_RED);
    tft.drawRect(x_width, 0, x_width, y_height, ILI9341_RED);
    tft.drawRect(0, y_height, x_width, y_height, ILI9341_RED);
    tft.drawRect(x_width, y_height, x_width, y_height, ILI9341_RED);
}

void displayHome(){
    uint16_t border = 10;
    uint16_t line = 20;
    uint16_t x_width = tft.width() / 2;
    uint16_t y_height = tft.height() / 2;

    displayGrid();
    // top left button
    tft.setCursor(border, border);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(2);
    tft.println("Single beat\n full speed");

    // bottom left button
    tft.setCursor(border, y_height+border);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(2);
    tft.println("Single beat\n slow speed");

    // Top right button
    tft.setCursor(x_width + border, border);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(2);
    tft.print("Continuous");
    tft.setCursor(x_width + border, border + 1 * line);
    tft.print("beating at");
    tft.setCursor(x_width + border, border + 2 * line);
    tft.println("full speed");

    // bottom right button
    tft.setCursor(x_width + border, y_height + border);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(2);
    tft.print("Continuous");
    tft.setCursor(x_width + border, y_height + border + 1 * line);
    tft.print("beating at");
    tft.setCursor(x_width + border, y_height + border + 2 * line);
    tft.println("slow speed");
}

void displayPumping(){
    uint16_t border = 10;
    uint16_t line = 20;
    uint16_t x_width = tft.width() / 2;
    uint16_t y_height = tft.height() / 2;

    displayGrid();
    // top left button
    tft.setCursor(border, border);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(3);
    tft.println("Back");

    // bottom left button
    tft.setCursor(border, y_height + border);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(3);
    tft.print("BPM: ");
    if (pump_delay > 0){
        int bpm = 60 / (0.9 + (float(pump_delay / 1000.0)));
        tft.println(bpm);
    }
    else
    {
        int bpm = 60 / 0.9;
        tft.print(bpm);
        tft.setCursor(border, y_height + border + 2 * line);
        tft.print("MAX BPM");
    } 

    // Top right button
    tft.setCursor(x_width + border, border);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(3);
    tft.print("Faster");

    // bottom left button
    tft.setCursor(x_width + border, y_height + border);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(3);
    tft.print("Slower");
}

void displaySlowPumping(){
    uint16_t border = 10;
    uint16_t line = 20;
    uint16_t x_width = tft.width() / 2;
    uint16_t y_height = tft.height() / 2;

    displayGrid();
    // top left button
    tft.setCursor(border, border);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(3);
    tft.println("Back");

    // bottom left button
    tft.setCursor(border, y_height + border);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(3);
    tft.print("BPM: ");
    if (pump_delay > 0)
    {
        int bpm = 60 / (3.6 + (float(pump_delay * 4 / 1000.0)));
        tft.println(bpm);
    }
    else
    {
        int bpm = 60 / 3.6;
        tft.print(bpm);
        tft.setCursor(border, y_height + border + 2 * line);
        tft.print("MAX BPM");
    }

    // Top right button
    tft.setCursor(x_width + border, border);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(3);
    tft.print("Faster");

    // bottom left button
    tft.setCursor(x_width + border, y_height + border);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(3);
    tft.print("Slower");
}


/*
unsigned long testFillScreen()
{
    unsigned long start = micros();
    tft.fillScreen(ILI9341_BLACK);
    yield();
    tft.fillScreen(ILI9341_RED);
    yield();
    tft.fillScreen(ILI9341_GREEN);
    yield();
    tft.fillScreen(ILI9341_BLUE);
    yield();
    tft.fillScreen(ILI9341_BLACK);
    yield();
    return micros() - start;
    }

    unsigned long testText()
    {
        tft.fillScreen(ILI9341_BLACK);
        unsigned long start = micros();
        tft.setCursor(0, 0);
        tft.setTextColor(ILI9341_WHITE);
        tft.setTextSize(1);
        tft.println("Hello World!");
        tft.setTextColor(ILI9341_YELLOW);
        tft.setTextSize(2);
        tft.println(1234.56);
        tft.setTextColor(ILI9341_RED);
        tft.setTextSize(3);
        tft.println(0xDEADBEEF, HEX);
        tft.println();
        tft.setTextColor(ILI9341_GREEN);
        tft.setTextSize(5);
        tft.println("Groop");
        tft.setTextSize(2);
        tft.println("I implore thee,");
        tft.setTextSize(1);
        tft.println("my foonting turlingdromes.");
        tft.println("And hooptiously drangle me");
        tft.println("with crinkly bindlewurdles,");
        tft.println("Or I will rend thee");
        tft.println("in the gobberwarts");
        tft.println("with my blurglecruncheon,");
        tft.println("see if I don't!");
        return micros() - start;
    }



    /***************************************************
  This is our touchscreen painting example for the Adafruit TFT FeatherWing
  ----> http://www.adafruit.com/products/3315

  Check out the links above for our tutorials and wiring diagrams

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/
/*

#include <SPI.h>
#include <Wire.h>      // this is needed even tho we aren't using it

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ILI9341.h> // Hardware-specific library
#include <Adafruit_STMPE610.h>


void setup(void) {
  Serial.begin(115200);

  delay(10);
  Serial.println("FeatherWing TFT");
  if (!ts.begin()) {
    Serial.println("Couldn't start touchscreen controller");
    while (1);
  }
  Serial.println("Touchscreen started");
  
  tft.begin();
  tft.fillScreen(ILI9341_BLACK);
  
  // make the color selection boxes
  tft.fillRect(0, 0, BOXSIZE, BOXSIZE, ILI9341_RED);
  tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, ILI9341_YELLOW);
  tft.fillRect(BOXSIZE*2, 0, BOXSIZE, BOXSIZE, ILI9341_GREEN);
  tft.fillRect(BOXSIZE*3, 0, BOXSIZE, BOXSIZE, ILI9341_CYAN);
  tft.fillRect(BOXSIZE*4, 0, BOXSIZE, BOXSIZE, ILI9341_BLUE);
  tft.fillRect(BOXSIZE*5, 0, BOXSIZE, BOXSIZE, ILI9341_MAGENTA);
 
  // select the current color 'red'
  tft.drawRect(0, 0, BOXSIZE, BOXSIZE, ILI9341_WHITE);
  currentcolor = ILI9341_RED;
}

void loop() {
  // Retrieve a point  
  TS_Point p = ts.getPoint();
  
  Serial.print("X = "); Serial.print(p.x);
  Serial.print("\tY = "); Serial.print(p.y);
  Serial.print("\tPressure = "); Serial.println(p.z);  
 
 
  // Scale from ~0->4000 to tft.width using the calibration #'s
  p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
  p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());

  if (p.y < BOXSIZE) {
     oldcolor = currentcolor;

     if (p.x < BOXSIZE) { 
       currentcolor = ILI9341_RED; 
       tft.drawRect(0, 0, BOXSIZE, BOXSIZE, ILI9341_WHITE);
     } else if (p.x < BOXSIZE*2) {
       currentcolor = ILI9341_YELLOW;
       tft.drawRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, ILI9341_WHITE);
     } else if (p.x < BOXSIZE*3) {
       currentcolor = ILI9341_GREEN;
       tft.drawRect(BOXSIZE*2, 0, BOXSIZE, BOXSIZE, ILI9341_WHITE);
     } else if (p.x < BOXSIZE*4) {
       currentcolor = ILI9341_CYAN;
       tft.drawRect(BOXSIZE*3, 0, BOXSIZE, BOXSIZE, ILI9341_WHITE);
     } else if (p.x < BOXSIZE*5) {
       currentcolor = ILI9341_BLUE;
       tft.drawRect(BOXSIZE*4, 0, BOXSIZE, BOXSIZE, ILI9341_WHITE);
     } else if (p.x < BOXSIZE*6) {
       currentcolor = ILI9341_MAGENTA;
       tft.drawRect(BOXSIZE*5, 0, BOXSIZE, BOXSIZE, ILI9341_WHITE);
     }

     if (oldcolor != currentcolor) {
        if (oldcolor == ILI9341_RED) 
          tft.fillRect(0, 0, BOXSIZE, BOXSIZE, ILI9341_RED);
        if (oldcolor == ILI9341_YELLOW) 
          tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, ILI9341_YELLOW);
        if (oldcolor == ILI9341_GREEN) 
          tft.fillRect(BOXSIZE*2, 0, BOXSIZE, BOXSIZE, ILI9341_GREEN);
        if (oldcolor == ILI9341_CYAN) 
          tft.fillRect(BOXSIZE*3, 0, BOXSIZE, BOXSIZE, ILI9341_CYAN);
        if (oldcolor == ILI9341_BLUE) 
          tft.fillRect(BOXSIZE*4, 0, BOXSIZE, BOXSIZE, ILI9341_BLUE);
        if (oldcolor == ILI9341_MAGENTA) 
          tft.fillRect(BOXSIZE*5, 0, BOXSIZE, BOXSIZE, ILI9341_MAGENTA);
     }
  }

  if (((p.y-PENRADIUS) > 0) && ((p.y+PENRADIUS) < tft.height())) {
    tft.fillCircle(p.x, p.y, PENRADIUS, currentcolor);
  }
}

*/