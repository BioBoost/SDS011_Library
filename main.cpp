#include <iostream>
#include <mbed.h>
#include "./src/SDS011_Library.h"
using namespace std;
using namespace SDS011;

int main(){
    cout << "this is an example of how to use the library" << endl ;

    SDS011 sensor(D0,D1);
    sensor.read();
    cout << "The sensor ID is: " << sensor.getIDByte() << endl;
    cout << "The air contains: " << sensor.getPM25Value() << " µg/m³ perticles of 2.5 " << endl;
    cout << "The air contains: " << sensor.getPM10Value() << " µg/m³ perticles of 10 " << endl;
    if (sensor.correctChecksum()){
        cout << "The data is correct" << endl;
    } else {
        cout << "The data is false" << endl;
    }

    /* or you can send it to serial */
    sensor.sendDataToPc();

    return 0;
}