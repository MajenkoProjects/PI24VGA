#ifndef _EVENTS_H
#define _EVENTS_H

#define EV_SPI  0x0001

extern volatile unsigned int event;

extern void process_events();

#endif
