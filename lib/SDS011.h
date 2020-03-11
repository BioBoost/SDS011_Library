#pragma once

#include "mbed.h"

namespace SDS011_Particle
{
    class SDS011
    {    

        public:
            SDS011(PinName pinTXDevice, PinName pinRXDevice);
            
        public:    
            double getPM25Value();
            double getPM10Value();
            int getIdByte();        
            void sendDataToPc();           
            void sleep();
            void wakeUp();
            bool read();
            bool correctChecksum();
                
        private:
            int calculateChecksum(int,int,uint8_t[]);
           
        private:
            static const unsigned int PACKET_SIZE = 10;
            uint8_t buffer[PACKET_SIZE];
            uint8_t sleep_command[20] = {0xAA, 0xB4, 0x06, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x05, 0xAB};
     
            double PM25Value;
            double PM10Value;
            int idByte;
            int receivedCheckSum;
            bool dataError = false;
            Serial device;
    };
};