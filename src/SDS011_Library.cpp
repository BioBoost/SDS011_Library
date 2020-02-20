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
        if (sensor.readable()){
            sensor.gets((char*) buffer, PACKET_SIZE);   
            if(buffer[0] != 170){
                while(buffer[0] !=170){
                    reshuffleData();
                }
            }
            if(buffer[9] != 171){
                dataError = true;
            }
        }
        //PM25Value = buffer[3] * 256 + buffer[2]/10.0;
        //PM10Value = buffer[5] *256 + buffer[4]/10.0;
        //idByte = buffer[6] + buffer[7]*256;
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
    }

    void reshuffleData(){
        while(buffer[0] != "C0"){
            /* schuif de hele array met een naar links */
            int hulp = buffer[0];       //anders verlies van data
            for(int t=0; t<PACKET_SIZE-1; t++){
                buffer[t] = buffer[t-1];
            }
            buffer[PACKET_SIZE] = hulp;
        }
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
        if(0){
            return true;
        }

        return false;
    }

}








void SDS011::

void SDS011::

double SDS011::

