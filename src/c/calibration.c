#include <pebble.h>
#include "calibration.h"
#include "Accelero.h"

void Calibrate()
{
unsigned int count = 0;
  
int sampleX = 0;
int sampleY = 0;
  
 do{
   coordinateAccX = coordinateAccX + sampleX; // Accumulate Samples
   coordinateAccY = coordinateAccY + sampleY;
   sampleX = coordinateAccX; //Previous value of data gets stored for next calculation
   sampleY = coordinateAccY;
   count++;
   }while(count!=0x0400); // 1024 times
   coordinateAccX = coordinateAccX>>10; // division between 1024
   coordinateAccY = coordinateAccY>>10;
}