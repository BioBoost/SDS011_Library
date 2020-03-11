#include <iostream>
#include "SDS011_Library.h"
#include "mbed.h"

using namespace std;

/* Local Variables */

Serial pc(USBTX, USBRX, 9600);

/* Functions */
namespace SDS011_Particle{
    SDS011::SDS011(PinName pinTXdevice, PinName pinRXdevice){
        TX = pinTXdevice;
        RX = pinRXdevice;
    }

    void SDS011::read(void){
        bool succesfulRead = false;
        int headData;
        Serial sensor(TX, RX, 9600);
        while(succesfulRead != true){
            headData = sensor.getc();
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

    void SDS011::sleep(void){
    /* TODO */
    // found a arduino library where you send a command to the sensor and it puts itself in low power modes
    }

    int SDS011::calculateChecksum(int beginData, int endData,uint8_t Package[]){
        int checksum=0;
        for(int t=beginData; t<=endData; t++ ){
            checksum += Package[t];
        }
        return checksum%256;  
    }

    double SDS011::getPM25Value(){
        return PM25Value;
    }

    double SDS011::getPM10Value(){
        return PM10Value;
    }

    int SDS011::getIdByte(){
        return idByte;
    }

    bool SDS011::correctChecksum(){       
        if(calculateChecksum(2,7,buffer) == buffer[8]){
            return true;
        }
        return false;
    }

    void SDS011::sendDataToPc(){
        
        pc.printf("the sensorID is %X \r\n", idByte);
        pc.printf("The air contains %.1lf µg/m³ of PM2.5 \r\n", PM25Value);
        pc.printf("The air contains %.1lf µg/m³ of PM10 \r\n", PM10Value);
        if(correctChecksum() == true){
            pc.printf("The checksum is true, data is correct");
        } else {
           pc.printf("The checksum is false, data is corrupt");
        }
    }    

}

