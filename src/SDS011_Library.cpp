#include SDS011_Library.h
#include "mbed.h"


void SDS011::SDS011(PinName pinTXdevice, PinName pinRXdevice){
    _pintTXdevice = pintTXdevice;
    _pintRXdevice = pintRXdevice;
    Serial sensor(_pinTXdevice,_pinTXdevice);
    sensor.baud(9600);
}

void SDS011::read(){

    if (sensor.readable()){
        sensor.gets((char*) buffer, PACKET_SIZE);

        if(buffer[0] != 170)
            while(buffer[0] !=170){
                reshuffleData();
            }
        if(buffer[9] != 171)
            dataError = true;
            


    }

    //PM25Value = buffer[3] * 256 + buffer[2]/10.0;
    //PM10Value = buffer[5] *256 + buffer[4]/10.0;
    //idByte = buffer[6] + buffer[7]*256;

}

void SDS011::sendDataToPc(){
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

void SDS011::sleep(){
    /* TODO */
}

void SDS011::reshuffleData(){

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

}