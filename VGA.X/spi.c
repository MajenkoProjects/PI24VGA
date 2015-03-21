#include <p24Fxxxx.h>
#include <stdio.h>
#include <string.h>

#include "gpu.h"
#include "spi.h"
#include "events.h"
#include "fonts.h"

volatile struct spi_packet spi;
volatile unsigned char slaveSelect;
volatile unsigned int spi_pos;

unsigned long htonl(unsigned long y)
{
    return y; //(y>>24) | (y>>16)<<8 | (y>>8) << 16 | (y<<24);
}

void init_spi()
{
    // SS = pin 68
    RPINR20bits.SDI1R = 35;  // pin 67
    RPINR20bits.SCK1R = 36;  // pin 66

    SPI1BUF = 0;
    IFS0bits.SPI1IF = 0;
    IEC0bits.SPI1IE = 0;
    SPI1CON1bits.DISSCK = 0;
    SPI1CON1bits.DISSDO = 1;
    SPI1CON1bits.MODE16 = 0;
    SPI1CON1bits.SMP = 0;
    SPI1CON1bits.CKE = 0;
    SPI1CON1bits.CKP = 0;
    SPI1CON1bits.MSTEN = 0;
    SPI1CON1bits.SSEN = 0;
    SPI1STATbits.SPIROV = 0;
    SPI1STATbits.SPIEN = 0;

    IPC2bits.SPI1IP = 6;

    CNEN4bits.CN53IE=1; // SS#
    CNPU4bits.CN53PUE=1;

    IPC4bits.CNIP = 6;
    IFS1bits.CNIF = 0;
    IEC1bits.CNIE = 1;

    TRISDbits.TRISD8 = 1;
    slaveSelect = PORTDbits.RD8;

    spi.command = 0;
    spi.len = 0;
    spi.cs = 0;
//    spi.rxlen = 0;
//    spi.rxcs = 0;
//    spi.phase = SP_CMD;
}

struct coord2 {
    unsigned short x;
    unsigned short y;
}__attribute__((packed));

struct coord4 {
    unsigned short x1;
    unsigned short y1;
    unsigned short x2;
    unsigned short y2;
}__attribute__((packed));

struct coord6 {
    unsigned short x1;
    unsigned short y1;
    unsigned short x2;
    unsigned short y2;
    unsigned short x3;
    unsigned short y3;
}__attribute__((packed));

struct intval {
    unsigned short value;
}__attribute__((packed));

struct rectangle {
    unsigned short x1;
    unsigned short y1;
    unsigned short x2;
    unsigned short y2;
    unsigned fill:1;
    unsigned char dither;
}__attribute__((packed));

struct circle {
    unsigned short x;
    unsigned short y;
    unsigned short radius;
    unsigned fill:1;
}__attribute__((packed));

struct charval {
    unsigned char value;
}__attribute__((packed));

void run_spi()
{
    // Different ways of looking at the SPI buffer:
    struct coord2 *coord2 = (struct coord2 *)spi.buffer;
    struct coord4 *coord4 = (struct coord4 *)spi.buffer;
    struct coord6 *coord6 = (struct coord6 *)spi.buffer;
    struct intval *intval = (struct intval *)spi.buffer;
    struct rectangle *rectangle = (struct rectangle *)spi.buffer;
    struct circle *circle = (struct circle *)spi.buffer;
    struct charval *charval = (struct charval *)spi.buffer;
    char *string = (char *)spi.buffer;

//    if(spi.cs != spi.rxcs)
//        return;

    switch(spi.command)
    {
        case SPI_CLS:
            GPU_CLS();
            break;
        case SPI_CLUT:
            GPU_SetCLUT(coord2->x,coord2->y);
            break;
        case SPI_ENCOPPER:
            GPU_EnableCopper(intval->value);
            break;
        case SPI_DISCOPPER:
            GPU_EnableCopper(intval->value);
            break;
        case SPI_COPPERFILL:
            GPU_CopperFill(coord4->x1,coord4->y1,coord4->x2,coord4->y2);
            break;
        case SPI_SCROLL:
            switch(coord2->x)
            {
                case UP: // Scroll up
                    GPU_ScrollUp(coord2->y);
                    break;
                case LEFT:
                    GPU_ScrollLeft(coord2->y);
                    break;
            }
            break;
        case SPI_COPY:
            RCC_Copy(coord6->x1,coord6->y1,coord6->x2,coord6->y2,coord6->x3,coord6->y3);
            break;
        case SPI_PLOT:
            RCC_SetPixel(coord2->x, coord2->y);
            break;
        case SPI_DRAW:
            RCC_Draw(coord4->x1,coord4->y1,coord4->x2,coord4->y2);
            break;
        case SPI_COLOR:
            RCC_SetColor(intval->value);
            break;
        case SPI_RECTANGLE:

            if(rectangle->fill)
            {
                if(rectangle->dither != 255)
                {
                    RCC_DitheredRectangle(rectangle->x1,rectangle->y1,rectangle->x2,rectangle->y2,rectangle->dither);
                } else {
                    RCC_FilledRectangle(rectangle->x1,rectangle->y1,rectangle->x2,rectangle->y2);
                }
            } else {
                RCC_Rectangle(rectangle->x1,rectangle->y1,rectangle->x2,rectangle->y2);
            }
            break;
        case SPI_CIRCLE:
            if(circle->fill)
            {
                RCC_FilledCircle(circle->x,circle->y,circle->radius);
            } else {
                RCC_Circle(circle->x,circle->y,circle->radius);
            }

        case SPI_LOCATE:
            CHR_PrintPos(coord2->x,coord2->y);
            break;
        case SPI_FONT:
            switch(intval->value)
            {
                case FONT_SINCLAIR:
                    CHR_LoadFont(sinclair);
                    break;
                case FONT_TOPAZ:
                    CHR_LoadFont(topaz);
                    break;
            }
            break;
        case SPI_PRINT:
            printf(string);
            break;
        case SPI_PUTCH:
            printf("%c",charval->value);
            break;
        case SPI_FGCOLOR:
            CHR_SetFGColor(intval->value);
            break;
        case SPI_BGCOLOR:
            CHR_SetBGColor(intval->value);
            break;
        default:
            break;
    }
}

void __attribute__((interrupt, auto_psv)) _SPI1Interrupt(void)
{
    unsigned char *c = (unsigned char *)&spi;

    *(c+spi_pos) = SPI1BUF;
    spi_pos++;
    *(c+spi_pos) = 0;
//
//    switch(spi.phase)
//    {
//        case SP_CMD:
//            spi.rxcs += SPI1BUF;
//            spi.command = SPI1BUF;
//            SPI1BUF=SPI_IDLE;
//            spi.phase++;
//            break;
//        case SP_LEN:
//            spi.rxcs += SPI1BUF;
//            spi.len = SPI1BUF;
//            spi.phase++;
//            SPI1BUF=SPI_IDLE;
//            break;
//        case SP_DATA:
//            if(spi.rxlen < spi.len)
//            {
//                spi.rxcs += SPI1BUF;
//                spi.buffer[spi.rxlen] = SPI1BUF;
//                spi.rxlen++;
//                spi.buffer[spi.rxlen] = 0;
//            } else {
//                spi.cs = SPI1BUF;
//                if(spi.cs == spi.rxcs)
//                {
//                    SPI1BUF=0;
//                    event |= EV_SPI;
//                    spi.phase++;
//                }
//                SPI1BUF=0;
//            }
//            break;
//    }
    IFS0bits.SPI1IF = 0;
}

void __attribute__((__interrupt__,auto_psv)) _CNInterrupt(void)
{
    if(PORTDbits.RD8 != slaveSelect)
    {
        slaveSelect = PORTDbits.RD8;
        if(slaveSelect == 0)
        {
            SPI1STATbits.SPIEN = 1;
            IFS0bits.SPI1IF = 0;
            IEC0bits.SPI1IE = 1;
            spi_pos = 0;
//            spi.phase = SP_CMD;
//            spi.rxcs = 0;
//            spi.rxlen = 0;
        } else {
            SPI1STATbits.SPIEN = 0;
            IEC0bits.SPI1IE = 0;

            event |= EV_SPI;
        }
    }
    IFS1bits.CNIF = 0;
}
