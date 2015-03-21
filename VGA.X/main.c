#include <p24Fxxxx.h>
#include <stdio.h>
#include <stdlib.h>
#include "GenericTypeDefs.h"
#include "gpu.h"
#include "fonts.h"
#include "spi.h"
#include "events.h"

_CONFIG2(0x19EF);
_CONFIG1(0x3F7F);

unsigned int clut[] = {
    0b00000000,
    0b11111111,
    0b00000111,
    0b11000000,
};

int main(void)
{
    unsigned long i;
    
    CLKDIVbits.RCDIV=0b000;
    CLKDIVbits.CPDIV=0b00;
    CLKDIVbits.G1CLKSEL=1;
    CLKDIV2bits.GCLKDIV=8;
    while(OSCCONbits.LOCK==0)
        continue;
    
    GPU_Init(&vga);

    GPU_TestCard();
    while(1);
    init_spi();

    while(1)
        process_events();

}

