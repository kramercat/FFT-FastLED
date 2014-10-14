FFT-FastLED
===========

This is documentation for the FFT/FHT audio-reactive library for FastLED.
FFT/FHT library from TJC.

HARDWARE/INTERFACING
====================

Use non-powered audio signal (laptop, phone, mp3 player, mixer, etc.)
Use a stereo to mono summer (http://www.rane.com/n109fig2.gif), feed mono line into an arduino analog in. Example code uses A1.

INCLUDES/LIBRARIES
==================

Import the FFT library (fix_fft folder) into your arduino libraries database.

EXAMPLE CODE
============

Runs off of FastLED library. Adjust basic settings to fit your setup (grey commented fields).
Remember to include fix_fft.h

void get() is the function to run FFT

The weighting bins I have set (low, mid, hi)

  value[0] = 0.75*data_avgs[0] + data_avgs[1] + 0.75*data_avgs[2];
  value[1] = data_avgs[3] + 2*data_avgs[4] + 3*data_avgs[5] + 3*data_avgs[6] + 3*data_avgs[7] + 2*data_avgs[8] + data_avgs[9];
  value[2] = data_avgs[8] + 2*data_avgs[9] + 3*data_avgs[10] + 3*data_avgs[11] + 2*data_avgs[12] + data_avgs[13];

VARIABLES & FUNCTIONS (example.ino)
=======================

baseline - threshold for triggering the pattern effect. Set lower for more sensitivity and higher for less.
ledTimer - how often the LEDs can be triggered (can be used to limit false detection at high sensitivity)
fadeTimer - how fast the LEDs fade (can be used in conjunction with the fade multiplier)
hue(x) - function to change the global variable ihue by x
