# SDS011_Library
The SDS011_Library is a library to communicate with the SDS011 particle sensor

## Functions
### Functional
read() : reads the values from the sensor;

sleep() : puts the sensor in sleep mode; 

wakeUp() :  wakes up the sensor from sleep mode;

sendDataToPc() : prints al the read data in a string to the pc;

setWorkingPeriode() : is an experimantel function the lets the sensor sleep and wake up on a predetermined periode;

### Getters
getPM25Value() : gives the pm2.5 value that was read at the time from the last read();

getPM10Value() : gives the pm10 value that was read at the time from the last read();

getIdByte() : gives the id Byte from the sensor; 


## Example

```cpp 
#include "mbed.h"
#include "SDS011.h"

//using namespace std;
using namespace SDS011_Particle;
Serial pc(USBTX,USBRX);

int main(){
    printf("\r\n--------------------------------------------\n");
    printf("\r\nThis is an example of how to use the library\n");
    printf("\r\n--------------------------------------------\n");
    SDS011 sensor(D1,D0);               // uses D1 as TX and D0 as RX
    
    while(true){
        sensor.wakeUp();                // wakes the sensor
        while(!sensor.read());          // loops the read if unsuccesfull
        sensor.sendDataToPc();          // sends the data in string format to the pc
        sensor.sleep();                 // puts the sensor to sleep
        ThisThread::sleep_for(3000);    // waites for 3 secondes
    }       

}
```

