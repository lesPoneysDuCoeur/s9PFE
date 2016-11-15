#include <pebble.h>
#include "integration.h"
#include "Accelero.h"

void integration(Tuplet acceleration[], Tuplet velocity[], Tuplet position[]){
  
  // Declaration of necessary variables for buffering of previous data
  
  int coordinateVelX = 0;
  int coordinateVelY = 0;
  int coordinateVelZ = 0;
  
  int coordinatePosX = 0;
  int coordinatePosY = 0;
  int coordinatePosZ = 0;
  
  int sampleAccX = 0; // Position
  int sampleAccY = 0;
  int sampleAccZ = 0;
  
  int sampleVelX = 0; // Velocity
  int sampleVelY = 0;
  int sampleVelZ = 0;
  
  int samplePosX = 0; // Position
  int samplePosY = 0;
  int samplePosZ = 0;
  
  /*
  
  //first integration
  velocity.x[1] = velocity.x[0] + acceleration.x[0] + ((accelerationx[1] - accelerationx[0])>>1)
  //second integration
  positionX[1] = positionX[0] + velocityx[0] + ((velocityx[1] - velocityx[0])>>1);
  
  */
  
  // Calculation for X
  
  coordinateVelX = sampleVelX + sampleAccX + ((coordinateAccX - sampleAccX)>>1);
  coordinatePosX = samplePosX + sampleVelX + ((coordinateVelX - sampleVelX)>>1);
  
  // Calculation for Y
  
  coordinateVelY = sampleVelY + sampleAccY + ((coordinateAccY - sampleAccY)>>1);
  coordinatePosY = samplePosY + sampleVelX + ((coordinateVelY - sampleVelY)>>1);
  
  // Calculation for Z
  
  coordinateVelZ = sampleVelZ + sampleAccZ + ((coordinateAccZ - sampleAccZ)>>1);
  coordinatePosZ = samplePosZ + sampleVelZ + ((coordinateVelZ - sampleVelZ)>>1);
  
  // Change sample value for next calculation
  
  sampleAccX = coordinateAccX;
  sampleAccY = coordinateAccY;
  sampleAccZ = coordinateAccZ;
  
  sampleVelX = coordinateVelX;
  sampleVelY = coordinateVelY;
  sampleVelZ = coordinateVelZ;
  
  samplePosX = coordinatePosX;
  samplePosY = coordinatePosY;
  samplePosZ = coordinatePosZ;
  
}