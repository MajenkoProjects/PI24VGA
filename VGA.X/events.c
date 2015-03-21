#include <p24Fxxxx.h>
#include <stdio.h>
#include <stdlib.h>
#include "events.h"
#include "spi.h"

volatile unsigned int event;

void process_events()
{

    if(event & EV_SPI)
    {
        event &= ~EV_SPI;
        run_spi();
    }

}
