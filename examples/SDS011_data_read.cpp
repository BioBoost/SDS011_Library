#include "mbed.h"
#include "SDS011.h"

using namespace SDS011_Particle;
Serial pc(USBTX,USBRX);

int main(){
    printf("\r\n--------------------------------------------\n");
    printf("\r\nThis is an example of how to use the library\n");
    printf("\r\n--------------------------------------------\n");

    SDS011 sensor(D1,D0);

    /* manualy */
    // while(true){
    //     if(sensor.read()){
    //         printf("The sensor ID is: %d \n", sensor.getIdByte() );
    //         printf("The air contains: %.2f µg/m³ perticles of 2.5 \n", sensor.getPM25Value());
    //         printf("The air contains: %.2f µg/m³ perticles of 10 \n",  sensor.getPM10Value());  
    //         printf("The data is correct\n");
    //     }
    // }

    /* or you can send it to serial */
    while(true){
        if(sensor.read()){
            sensor.sendDataToPc();
        }         
        ThisThread::sleep_for(3000);
    };
    return 0;
}