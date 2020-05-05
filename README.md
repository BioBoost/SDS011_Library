# SDS011_Library
The SDS011_Library is a library to communicate with the SDS011 particle sensor

## Getting started

For using this particle sensor you have to have the following software installed:

* Visual studio code
* Mbed CLI
* Putty (to test the code)

```bash
    -   'git clone https://github.com/vives-projectwerk-2-2020/SDS011_Library.git'
    -   'mbed new .' 
    -   'mbed deploy'
    -   'mbed toolchain GCC_ARM'
    -   'mbed target detect'
    -   'mbed compile'
    or 'mbed compile -f' (to directly flash the program to the device)
```

## How to use the example

Paste the example sketch in your 'main.cpp' file. After compiling it should work.


## Functions

### UML DIAGRAM
---------------------------------------------
|                   SDS011                  |
---------------------------------------------
| -PACKET_SIZE : const unsigned int         |
| -MAX_TRIES : const int                    |
| -MAX_TIMOUT : const double                |
| -buffer : uint8_t[]                       |
| -sleep_command : const uint8_t[]          |
| -wakeup_command : const uint8_t[]         |
| -periode_command : uint8_t[]              |
| -PM25Value : double                       |
| -PM10Value : double                       |
| -idByte : int                             |
|-------------------------------------------|
| +getPM25Value : double                    |
| +getPM10Value : double                    | 
| +getIdByte : int                          |
| +sendDataToPc : void                      |
| +sleep : ErrorCodes                       |
| +wakeUp : ErrorCodes                      |
| +read : ErrorCodes                        |
| +setWorkingPeriode(uint8_t): ErrorCodes   |
| +printfbuffer : void                      |
| -calculateChecksum(int,int,uint8_t) : int |
| -correctChecksum : bool                   |
---------------------------------------------


### Functional
read() : reads the values from the sensor, it returns an error code that secures the correctness of the data

sleep() : puts the sensor in sleep mode, it returns an error code that secures a correct sleep

wakeUp() :  wakes up the sensor from sleep mode, it returns an error code that secures a correct wake up

sendDataToPc() : prints al the read data in a string to the pc

setWorkingPeriode() : is an experimantel function the lets the sensor sleep and wake up on a predetermined periode, it returns an error code that secures a correct set of the working periode


### Getters
getPM25Value() : gives the pm2.5 value that was read at the time from the last read()

getPM10Value() : gives the pm10 value that was read at the time from the last read()

getIdByte() : gives the id Byte from the sensor that was last read from


### Error Codes
NO_HEADER : is returned from read() if the microcontroller doesn't read the header after MAX_TRIES

DEVICE_NOT_READABLE: is returned from read() if the sensor is not readable MAX_TIMOUT seconds after calling the function

READ_SUCCESSFULL: is returned from read() if the microcontroller has received data and when the checksum of that data is correct

READ_NOT_SUCCESSFULL: is returned from read() if the microcontroller has received data and when the checksum of that data isn't correct

SLEEP_SUCCESSFULL: is returned from sleep() if the particle sensor has been correctfully put to sleep

SLEEP_NOT_SUCCESFULL: is returned from sleep() if the particle sensor hasn't been correctfully put to sleep

WAKEUP_SUCCESFULL: is returned from wakeUp() if the particle sensor has been correctfully woken up

WAKEUP_NOT_SUCCESFULL: is returned from wakeUp() if the particle sensor hasn't been correctfully woken up

WORKING_PERIODE_SET: is returned from setWorkingPeriode(uint8_t) if the periode of the particle sensor has been correctfully set

WORKING_PERIODE_NOT_SET:is returned from setWorkingPeriode(uint8_t) if the periode of the particle sensor hasn't been correctfully set


## Example

```cpp 
#include "mbed.h"
#include "SDS011.h"

//using namespace std;
using namespace Particula;
Serial pc(USBTX,USBRX);

int main(){
    printf("\r\n--------------------------------------------\n");
    printf("\r\nThis is an example of how to use the library\n");
    printf("\r\n--------------------------------------------\n");
    SDS011 sensor(D1,D0);               // uses D1 as TX and D0 as RX
    
    while(true){                                            // endless loop
        if(part_sensor.wakeUp() == WAKEUP_SUCCESFULL){      // wakes the sensor
            printf("sensor woke up \r\n");
        } else {
            printf("sensor didn't wake up \r\n");
        }                
        ThisThread::sleep_for(15000);                       // waites for 15 secondes

        if(sensor.read() == READ_SUCCESSFULL){              // reads from the sensor
            printf("sensor succesfully read \r\n");
        } else {   
            printf("sensor not succesfully read \r\n"); 
        }                                     

        sensor.sendDataToPc();                              // sends the data in string format to the pc

        if(part_sensor.sleep() == SLEEP_SUCCESSFULL){       // puts the sensor to sleep
            printf("sensor succesfully slept \r\n");
        } else {
            printf("sensor unsuccesfully slept \r\n");
        }                

        ThisThread::sleep_for(45000);                       // waites for 45 secondes
    }       

}


