#include <FastLED.h>

#define LED_COUNT 12 //CHANGE TO FIT YOUR SETUP (# of LED pixels)

#include <fix_fft.h>

int x = 0;
char im[128], data[128];
char data_avgs[14];
int value[3];
int i=0,audioVal;

#define AUDIOPIN A1 //CHANGE TO FIT YOUR SETUP (Where the sound goes in on the Arduino)
 
float spectrumBright;
unsigned long fadeTimer; unsigned long ledTimer;
float trigger;
  
uint8_t BOTTOM_INDEX = 0;
uint8_t TOP_INDEX = int(LED_COUNT/2);
uint8_t EVENODD = LED_COUNT%2;
struct CRGB leds[LED_COUNT];
int ledsX[LED_COUNT][3];    
uint8_t ledMode = 3;          
uint8_t maxHue = 255;

#define SERIAL_BAUDRATE 9600
byte inbyte;                
int thisarg;                

//---LED FX VARS
uint8_t max_bright = 255;
uint8_t idex = 0;
int idx_offset = 0;
float ihue = 0.00;
float sat = 0.00;
float val = 0.00;
float sHue = 0.00;


//------------------SETUP------------------
void setup()  
{
  LEDS.addLeds<WS2811, 2, BRG>(leds, 0, LED_COUNT);        //CHANGE TO FIT YOUR SETUP
  LEDS.show();
}

  float hueStep = 5;
  unsigned long fadeWait = 5;
  unsigned long ledWait = 10;
  uint8_t reactive_wait = 25;
  int baseline = 8;
  int maxTrigger = 15;

//------------------MAIN LOOP------------------
void loop(){
    glow();
}



void glow(){
  get();
  trigger = value[0];
    if (trigger > baseline && spectrumBright < 100){
      spectrumBright = min(trigger*max_bright/maxTrigger, max_bright);
      hue(hueStep);
      fadeTimer = millis();
    }
   else if (spectrumBright > 4.0){
     if (millis()-fadeTimer > fadeWait*2){
       spectrumBright = spectrumBright*0.95;
       fadeTimer = millis();
     }
   }
   else{  spectrumBright = 0.0; }
  for (uint8_t i=0; i<LED_COUNT; i++){
    leds[i] = CHSV(ihue, 255, spectrumBright);
  }
  LEDS.show();
}

void get(){
  for (i=0; i < 128; i++){                                   
    audioVal = analogRead(AUDIOPIN);                                  
    data[i] = audioVal;                                     
    im[i] = 0;                                                   
  };
  fix_fft(data,im,7,0);
  for (i=0; i< 64;i++){                                    
    data[i] = sqrt(data[i] * data[i] + im[i] * im[i]); 
  };   
  for (i=0; i<14; i++) {
    data_avgs[i] = data[i*4] + data[i*4 + 1] + data[i*4 + 2] + data[i*4 + 3];
    data_avgs[i] = map(data_avgs[i], 0, 30, 0, 9);
  }
  value[0] = 0.75*data_avgs[0] + data_avgs[1] + 0.75*data_avgs[2];
  value[1] = data_avgs[3] + 2*data_avgs[4] + 3*data_avgs[5] + 3*data_avgs[6] + 3*data_avgs[7] + 2*data_avgs[8] + data_avgs[9];
  value[2] = data_avgs[8] + 2*data_avgs[9] + 3*data_avgs[10] + 3*data_avgs[11] + 2*data_avgs[12] + data_avgs[13];
}

void hue(float istep){
  ihue = ihue + istep;
  if (ihue > 255) {ihue=ihue-256;}
}
