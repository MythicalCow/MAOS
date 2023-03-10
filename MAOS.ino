//Libraries
#include <ArduinoBLE.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>


//Setting Up IMU
#define BNO055_SAMPLERATE_DELAY_MS (100)
Adafruit_BNO055 bno = Adafruit_BNO055(-1, 0x28);

//Setting Up Bluetooth
BLEService imuService("95ff7bf8-aa6f-4671-82d9-22a8931c5387");
BLEFloatCharacteristic AX("95ff7bf8-aa6f-4671-82d9-22a8931c5387", BLERead);
BLEFloatCharacteristic AY("f49caa00-17f8-4e92-b5fd-d27137ca4515", BLERead);
BLEFloatCharacteristic AZ("84f9b003-6d14-44d7-8db1-d574d29c10c3", BLERead);

void setup() {
  Serial.begin(115200);
  Serial.println("");
  //Waits until BLE Begins and Prints Error Message
  if(!BLE.begin()) {
    Serial.println("Bluetooth Low Energy Not Working");
  }
  else{
    Serial.println("Bluetooth Ready");
  }
  //Setting Up Bluetooth ID Information
  BLE.setDeviceName("MAOS Device");
  BLE.setLocalName("MAOS Local");

  //Setting Up Bluetooth ID Information
  BLE.setDeviceName("MAOS Device");
  BLE.setLocalName("MAOS Local");

  //Setting up the IMU Service
  imuService.addCharacteristic(AX);
  imuService.addCharacteristic(AY);
  imuService.addCharacteristic(AZ);
  BLE.addService(imuService);
  
  //Starting IMU Values at 0
  AX.writeValue((float) 0.0);
  AY.writeValue((float) 0.0);
  AZ.writeValue((float) 0.0);

  BLE.advertise();

  delay(10000);

  //Waits until IMU Begins and Prints Error Message
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  bno.setExtCrystalUse(true);

}

void loop() {

 //Getting euler vector from IMU for position data 
 imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);

  /* Display the floating point data */
  //Serial.print("X: ");
  Serial.print(euler.x());
  Serial.print(" ");
  Serial.print(euler.y());
  Serial.print(" ");
  Serial.print(euler.z());
  Serial.print(" ");
  AX.writeValue((float) euler.x());
  AY.writeValue((float) euler.y());
  AZ.writeValue((float) euler.z());
  sensors_event_t linearAccelData;
  bno.getEvent(&linearAccelData, Adafruit_BNO055::VECTOR_LINEARACCEL);
  Serial.println(linearAccelData.acceleration.x);

  delay(250);

}
