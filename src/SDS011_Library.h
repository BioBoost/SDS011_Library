#pragma once
#include "mbed.h"

using namespace SDS011{
    class SDS011
    {
        public:
            SDS011(PinName pinTXDevice, PinName pinRXDevice);
            double getPM25Value();
            double getPM10Value();
            int getIdByte();
            bool correctChecksum();
            void sendDataToPc();
            void read();
            void sleep();
    
        private:
            const unsigned int PACKET_SIZE = 11;

            uint8_t buffer[PACKET_SIZE];
            double PM25Value;
            double PM10Value;
            int idByte;
            int receivedCheckSum;
            bool dataError = false;
            DigitalIn _pinRXDevice;
            DigitalOut _pinTXDevice;
            void reshuffleData();
    }
}