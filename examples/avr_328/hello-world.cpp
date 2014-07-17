/**
 * A Mirf example to test the latency between two Ardunio.
 *
 * Pins:
 * Hardware SPI:
 * MISO -> 12
 * MOSI -> 11
 * SCK -> 13
 *
 * Configurable:
 * CE -> 8
 * CSN -> 7
 *
 * Note: To see best case latency comment out all Serial.println
 * statements not displaying the result and load 
 * 'ping_server_interupt' on the server.
 */

#include "Arduino.h"
#include <iterator>
#include <vector>

std::vector<float> F;
void setup(){
  Serial.begin(9600);
  F.push_back(28);
}

void loop(){
} 
  
  
  
