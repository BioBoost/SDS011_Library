#pragma once

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
            void calculateChecksum();
    };
};