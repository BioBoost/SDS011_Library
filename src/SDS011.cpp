#include "SDS011.h"

using namespace std;


/* Functions */
namespace SDS011_Particle{
    SDS011::SDS011(PinName pinTXdevice, PinName pinRXdevice)
        :device(pinTXdevice,pinRXdevice,9600)
    {

    }

    void SDS011::read(void){
        bool succesfulRead = false;
        int headData;
        while(succesfulRead != true){
            headData = device.getc();
            if(headData == 0xAA){            
                buffer[0] = headData;            
                for( int t = 1; t<PACKET_SIZE; t++){
                    buffer[t] = device.getc();
                }
                succesfulRead = true;
            } else {
                printf(" \r\n flushing \r\n");
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
        
        printf("the sensorID is %X \r\n", idByte);
        printf("The air contains %.1lf µg/m³ of PM2.5 \r\n", PM25Value);
        printf("The air contains %.1lf µg/m³ of PM10 \r\n", PM10Value);
        if(correctChecksum() == true){
            printf("The checksum is true, data is correct");
        } else {
            printf("The checksum is false, data is corrupt");
        }
    }    

}

