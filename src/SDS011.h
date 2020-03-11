#pragma once
#include "PinNames.h"

const unsigned int PACKET_SIZE = 10;

namespace SDS011_Particle
{
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
            int calculateChecksum(int,int,uint8_t[]);
            uint8_t buffer[PACKET_SIZE];
            double PM25Value;
            double PM10Value;
            int idByte;
            int receivedCheckSum;
            bool dataError = false;
            PinName TX;
            PinName RX;
    };
};