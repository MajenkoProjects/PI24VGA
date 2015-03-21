/*****************
  $Header: /home/amb/cxref/RCS/README.c 1.4 1997/05/26 11:23:40 amb Exp $

  A comment for the file, RCS header comments are treated specially when first.
  *****************/

#ifndef _SPI_H
#define _SPI_H

#define SPI_IDLE    	0x00

// System control
#define SPI_CLS         0x01
#define SPI_CLUT        0x02
#define SPI_ENCOPPER    0x03
#define SPI_DISCOPPER   0x04
#define SPI_COPPERFILL  0x05
#define SPI_SCROLL      0x06
#define SPI_COPY        0x07

// Basic drawing
#define SPI_PLOT        0x11
#define SPI_DRAW        0x12
#define SPI_COLOR       0x13
#define SPI_RECTANGLE   0x14
#define SPI_CIRCLE      0x15

// Text commands
#define SPI_LOCATE      0x80
#define SPI_FONT        0x81
#define SPI_PRINT       0x82
#define SPI_PRINTAT     0x83
#define SPI_PUTCH       0x84
#define SPI_PUTCHAT     0x85
#define SPI_FGCOLOR     0x86
#define SPI_BGCOLOR     0x87

//@DEFINE SPI State Machine Phase Constants
#define SP_CMD 0
#define SP_LEN 1
#define SP_DATA 2
#define SP_END 3
//@END

#define FONT_SINCLAIR 0x00
#define FONT_TOPAZ 0x01

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

struct spi_packet {
    volatile unsigned char command;
    volatile unsigned char len;
    volatile unsigned char cs;
    unsigned char buffer[256];
//    volatile unsigned char rxlen;
//    volatile unsigned char phase;
//    volatile unsigned char rxcs;
}__attribute__((packed));

extern volatile struct spi_packet spi;
extern volatile unsigned char slaveSelect;

extern void init_spi();
extern void run_spi();

#endif
