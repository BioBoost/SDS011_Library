#include SDS011_Library.h
#include "mbed.h"

namespace SDS011{
    SDS011(PinName pinTXdevice, PinName pinRXdevice){
        _pintTXdevice = pintTXdevice;
        _pintRXdevice = pintRXdevice;
        Serial sensor(_pinTXdevice,_pinTXdevice);
        sensor.baud(9600);
    }

    void read(void){
        bool succesfulRead = false;
        int headData;

        while(succesfulRead != true){
            headData = sensor.getc()
            if(headData == 0xAA){            
                buffer[0] = headData;            
                for( int t = 1; t<PACKET_SIZE; t++){
                    buffer[t] = sensor.getc();
                }
                succesfulRead = true;
            } else {
                pc.printf(" \r\n flushing \r\n");
            }
        }
        PM25Value = buffer[3] * 256 + buffer[2]/10.0;
        PM10Value = buffer[5] *256 + buffer[4]/10.0;
        idByte = buffer[6] + buffer[7]*256;
    }

    void sendDataToPc(){
        Serial pc(USBTX,USBRX);
        pc.printf("the sensorID is %X %X \r\n", idByte);
        pc.printf("The air contains %.1lf µg/m³ of PM2.5 \r\n", PM25Value);
        pc.printf("The air contains %.1lf µg/m³ of PM10 \r\n", PM10Value);
        if(correctChecksum == true){
            pc.printf("The checksum is true, data is correct");
        } else {
            pc.printf("The checksum is false, data is corrupt")
        }
    }

    void sleep(void){
    /* TODO */
    // found a arduino library where you send a command to the sensor and it puts itself in low power modes
    }

    int calculateChecksum(int beginData, int endData,uint8_t Package[]){
        int checksum=0;
        for(int t=beginData; t<=endData; t++ ){
            checksum += Package[t];
        }
        return checksum%256;  
    }

    double getPM25Value(){
        return PM25Value;
    }

    double getPM10Value(){
        return PM10Value;
    }

    int getIdByte(){
        return idByte;
    }

    bool correctChecksum(){       
        if(calculateChecksum(2,7,buffer) == buffer[8]){
            return true;
        }
        return false;
    }

}








void SDS011::

void SDS011::

double SDS011::

