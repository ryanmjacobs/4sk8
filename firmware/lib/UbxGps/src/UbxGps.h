#ifndef UBXGPS_H_
#define UBXGPS_H_

#include "Arduino.h"
#include <SoftwareSerial.h>

const unsigned char UBXGPS_HEADER[] = {0xB5, 0x62};

class UbxGps
{
  public:
    void begin(long);
    boolean ready();

  protected:
    UbxGps(SoftwareSerial &);
    void setLength(unsigned char);

  private:
    int available();
    byte read();
    void calculateChecksum();

    // Class properties
    SoftwareSerial &serial;
    unsigned char offsetClassProperties = 8;
    unsigned char offsetHeaders = 4;
    unsigned char size;
    unsigned char carriagePosition;
    unsigned char checksum[2];

    // Headers (common)
    unsigned char headerClass;
    unsigned char headerId;
    unsigned short headerLength;
};

#endif
