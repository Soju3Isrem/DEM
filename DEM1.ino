/*
 * 03-10-2019
 * Example de SER COM with the sensor CC811 by Josue Isem using Samd21 PRO RF
 * 
*/

#include <Wire.h>
#include "wiring_private.h"
#include "SparkFunCCS811.h"
#define CCS811_ADDR 0x5A 

TwoWire myWire(&sercom2,4,3);
CCS811 mySensor(CCS811_ADDR);

void setup()
{
  SerialUSB.begin(9600);
  myWire.begin();  
  pinPeripheral(4,PIO_SERCOM_ALT);
  pinPeripheral(3,PIO_SERCOM_ALT);

  CCS811Core::status returnCode = mySensor.begin(myWire);
  if (returnCode != CCS811Core::SENSOR_SUCCESS)
  {
    SerialUSB.println(".begin() returned with an error.");
    while (1); //Hang if there was a problem.
  }
}

void loop()
{
  if (mySensor.dataAvailable())
  {
    mySensor.readAlgorithmResults();
    SerialUSB.print("CO2 ");
    SerialUSB.print(mySensor.getCO2());
    SerialUSB.print("  tVOC  ");
    SerialUSB.println(mySensor.getTVOC());
  }

  delay(10);
}
