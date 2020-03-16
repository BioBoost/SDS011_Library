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
getIdByte() : gives the id Byte from the sensor 


## Example
