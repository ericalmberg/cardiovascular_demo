#ifndef DISPLAY_HANDLER
#define DISPLAY_HANDLER

// display requirements
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

// touch requirements
#include <Adafruit_GFX.h>     // Core graphics library
#include <Adafruit_ILI9341.h> // Hardware-specific library
#include <Adafruit_STMPE610.h>

// define pins for the display to use
#define TFT_DC 33
#define TFT_CS 15
#define STMPE_CS 32
#define SD_CS 14

// This is calibration data for the raw touch data to the screen coordinates
#define TS_MINX 3800
#define TS_MAXX 100
#define TS_MINY 100
#define TS_MAXY 3750

enum screenStateEnum
{
    home,
    pumping,
    slow_pumping,
    unknown
};

enum quadrantEnum
{
    bottom_left,
    bottom_right,
    top_right,
    top_left,
    clear,
};

extern Adafruit_ILI9341 tft;
extern Adafruit_STMPE610 ts;
extern screenStateEnum screen_state;
extern screenStateEnum last_screen_state;
extern quadrantEnum touch_quadrant;
extern quadrantEnum last_touch_quadrant;

extern int last_x_touch;
extern int last_y_touch;

void handleTouch();

void handleDisplay();

void displayHome();

void displayPumping();

void displaySlowPumping();

#endif