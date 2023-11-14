#include <dummy.h>
#include <Arduino.h>
#include <stdint.h>
#include "SCMD.h"
#include "SCMD_config.h" //Contains #defines for common SCMD register names and values
#include "Wire.h"

SCMD myMotorDriver;

int a;
int x_1 = 12, b;
int y_1 = 15, c;// Pin connected to the right limit switch home
int x_2 = 27, d; // Pin connected to the left limit switch extreme
int y_2 = 15, e; // Pin connected to the right limit switch extreme

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(x_1, INPUT);
pinMode(x_2, INPUT);
pinMode(y_1, INPUT);
pinMode(y_2, INPUT);
Serial.println("Starting sketch.");
//** Configure the Motor Driver's Settings **//
// .commInter face is I2C_MODE
myMotorDriver.settings.commInterface = I2C_MODE;
// set address if I2C configuration selected with the config jumpers
myMotorDriver.settings.I2CAddress = 0x5D; //config pattern is "1000" (default) on board for address 0x5D
// set chip select if SPI selected with the config jumpers
myMotorDriver.settings.chipSelectPin = 10;
//*initialize the driver get wait for idle*//
while ( myMotorDriver.begin() != 0xA9 ) //Wait until a valid ID word is returned
{
Serial.println( "ID mismatch, trying again" );
delay(500);
}
Serial.println( "ID matches 0xA9" );
// Check to make sure the driver is done looking for peripherals before beginning
Serial.print("Waiting for enumeration...");
while ( myMotorDriver.ready() == false );
Serial.println("Done.");
Serial.println();
//*Set application settings and enable driver*//
//Uncomment code for motor 0 inversion
//while( myMotorDriver.busy() );
//myMotorDriver.inversionMode(0, 1); //invert motor 0
//Uncomment code for motor 1 inversion
while ( myMotorDriver.busy() ); //Waits until the SCMD is available.
myMotorDriver.inversionMode(1, 1); //invert motor 1
while ( myMotorDriver.busy() );
myMotorDriver.enable(); //Enables the output driver hardware
}
#define LEFT_MOTOR 0
#define RIGHT_MOTOR 1

void wait()
{
  myMotorDriver.setDrive( LEFT_MOTOR, 0, 0);
  myMotorDriver.setDrive( RIGHT_MOTOR, 0, 0);
  delay(2000);
}

void loop() {
/*a= digitalRead(14); // Pin connected to the emergency stop button
if (a == HIGH) {
    b= digitalRead(15); 
    c= digitalRead(33);
    d= digitalRead(13);
    e= digitalRead(27);
      myMotorDriver.setDrive( LEFT_MOTOR, 0 , 230);
      if(e == HIGH)
      {
        Serial.println("X Limit is Hit");
        myMotorDriver.setDrive( LEFT_MOTOR, 0 , 0);
        Serial.println("X Motor is zero");
        myMotorDriver.setDrive( RIGHT_MOTOR, 0 , 230);
        Serial.println("Right Motor Is gOing Backward");
      if(d == HIGH)
        {
          Serial.println("Y Limit is Hit");
          myMotorDriver.setDrive( RIGHT_MOTOR, 0, 0);
          delay(2000);
          myMotorDriver.setDrive( RIGHT_MOTOR, 0, 0);
          myMotorDriver.setDrive( LEFT_MOTOR, 0 , 0); */
//step1
myMotorDriver.setDrive( LEFT_MOTOR, 0 , 230);
myMotorDriver.setDrive( RIGHT_MOTOR, 0, 0);
delay(1000);
serial.println("Step 1");
wait();

//step2
myMotorDriver.setDrive( LEFT_MOTOR, 0 , 0);
myMotorDriver.setDrive( RIGHT_MOTOR, 1, 230);
delay(1000);
serial.println("Step 2");
wait();

//step3
myMotorDriver.setDrive( LEFT_MOTOR, 0 , 230);
myMotorDriver.setDrive( RIGHT_MOTOR, 1, 230);
delay(500);
serial.println("Step 3");
wait();

//step4
myMotorDriver.setDrive( LEFT_MOTOR, 0, 230);
myMotorDriver.setDrive( RIGHT_MOTOR, 0, 230);
delay(500);
serial.println("Step 4");
wait();

//step5
myMotorDriver.setDrive( LEFT_MOTOR, 0 , 0);
myMotorDriver.setDrive( RIGHT_MOTOR, 0, 230);
delay(1000);
serial.println("Step 5");
wait();

//step6
myMotorDriver.setDrive( LEFT_MOTOR, 1, 230);
myMotorDriver.setDrive( RIGHT_MOTOR, 1, 230);
delay(500);
serial.println("Step 6");
wait();

//step7
myMotorDriver.setDrive( LEFT_MOTOR, 0, 230);
myMotorDriver.setDrive( RIGHT_MOTOR, 0, 0);
delay(1000);
serial.println("Step 7");
wait();

//step8
myMotorDriver.setDrive( LEFT_MOTOR, 1, 230);
myMotorDriver.setDrive( RIGHT_MOTOR, 0, 230);
delay(500);
serial.println("Step 8");
wait();
delay(10000);  /*
        }
      }
    }
if (a == LOW) 
 {
    Serial.println("Emergency Stop Activated!");
    myMotorDriver.setDrive(LEFT_MOTOR, 0, 0);
    myMotorDriver.setDrive(RIGHT_MOTOR, 0, 0);
 } */
}