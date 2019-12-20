#pragma once
#include <stdint.h>

class Etna {
    uint8_t prom[0x80] = {};
    uint16_t promReadAddress = 0, promReadValue = 0;
    bool promReadActive = false;
    int promAddressBitsReceived = 0;

    uint8_t wake1 = 0, wake2 = 0;

public:
    Etna();

    uint32_t readReg8(uint32_t reg);
    uint32_t readReg32(uint32_t reg);
    void writeReg8(uint32_t reg, uint8_t value);
    void writeReg32(uint32_t reg, uint32_t value);

    // PROM
    void setPromBit0High(); // port B, bit 0
    void setPromBit0Low(); // port B, bit 0
    void setPromBit1High(); // port B, bit 1
};