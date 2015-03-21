#ifndef _GPU_H
#define _GPU_H
#include "GenericTypeDefs.h"

#define GPU_CHR 0x5
#define GPU_RCC 0x06

//#define HB_FRONT 16
//#define HB_SYNC 96
//#define HB_BACK 48
//#define HB_DISPLAY 640
//// 640
//
//#define VB_FRONT (10)
//#define VB_SYNC 2
//#define VB_BACK (33)
//#define VB_DISPLAY 480

#define GFX_DISPLAY_BUFFER_START_ADDRESS 0x00005C00ul
//#define GFX_DISPLAY_BUFFER_START_ADDRESS 0x00004B00ul
#define GFX_BUFFER_SIZE 76800UL

#define GFX_SetDisplayArea(a)             { G1DPADRL = ((DWORD_VAL)((DWORD)(a))).word.LW; G1DPADRH = ((DWORD_VAL)((DWORD)(a))).word.HW; }
#define GFX_SetWorkArea1(a)               { G1W1ADRL = ((DWORD_VAL)((DWORD)(a))).word.LW; G1W1ADRH = ((DWORD_VAL)((DWORD)(a))).word.HW; }
#define GFX_SetWorkArea2(a)               { G1W2ADRL = ((DWORD_VAL)((DWORD)(a))).word.LW; G1W2ADRH = ((DWORD_VAL)((DWORD)(a))).word.HW; }

extern __eds__ BYTE GFXDisplayBuffer[GFX_BUFFER_SIZE] __attribute__((eds, address(GFX_DISPLAY_BUFFER_START_ADDRESS), noload, section("Graphics_Display_Buffer")));
extern volatile unsigned int copperbars0[480];
extern volatile unsigned int copperbars1[480];
extern volatile unsigned int copperbars2[480];
extern volatile unsigned int copperbars3[480];
extern volatile unsigned int defBG;
extern volatile unsigned char copper;


struct GPU_SETTINGS {
    unsigned short width;
    unsigned short height;
    unsigned char bpp;
    unsigned char colors;
    unsigned char clock;
    unsigned short hb_front;
    unsigned short hb_sync;
    unsigned short hb_back;
    unsigned short hb_total;
    unsigned short vb_front;
    unsigned short vb_sync;
    unsigned short vb_back;
    unsigned short vb_total;
    unsigned char doublebuffer;
    unsigned char stretch;
};

struct GPU_GENERIC {
    union {
        struct {
            unsigned long data:24;
            unsigned command:4;
            unsigned gpu:4;
        } __attribute__((packed));
        unsigned long value;
        struct {
            unsigned short low;
            unsigned short high;
        } __attribute__((packed));
    } __attribute__((packed));
} __attribute__((packed));

struct CHR_COLOR {
    union {
        struct {
            unsigned short color;
            unsigned char reserved;
            unsigned command:4;
            unsigned gpu:4;
        } __attribute__((packed));
        unsigned long value;
        struct {
            unsigned short low;
            unsigned short high;
        } __attribute__((packed));
    } __attribute__((packed));
} __attribute__((packed));

struct CHR_FONTBASE {
    union {
        struct {
            unsigned long address:24;
            unsigned command:4;
            unsigned gpu:4;
        } __attribute__((packed));
        unsigned long value;
        struct {
            unsigned short low;
            unsigned short high;
        } __attribute__((packed));
    } __attribute__((packed));
} __attribute__((packed));

struct CHR_PRINTCHAR {
    union {
        struct {
            unsigned short character;
            unsigned reserved:7;
            unsigned trans:1;
            unsigned command:4;
            unsigned gpu:4;
        } __attribute__((packed));
        unsigned long value;
        struct {
            unsigned short low;
            unsigned short high;
        } __attribute__((packed));
    } __attribute__((packed));
} __attribute__((packed));

struct CHR_COORD {
    union {
        struct {
            unsigned y:12;
            unsigned x:12;
            unsigned command:4;
            unsigned gpu:4;
        } __attribute__((packed));
        unsigned long value;
        struct {
            unsigned short low;
            unsigned short high;
        } __attribute__((packed));
    } __attribute__((packed));
} __attribute__((packed));



// RCC GPU Commands

struct RCC_OFFSET {
    union {
        struct {
            unsigned long offset:24;
            unsigned command:4;
            unsigned gpu:4;
        } __attribute__((packed));
        unsigned long value;
        struct {
            unsigned short low;
            unsigned short high;
        } __attribute__((packed));
    } __attribute__((packed));
} __attribute__((packed));

struct RCC_SIZE {
    union {
        struct {
            unsigned height:11;
            unsigned res1:1;
            unsigned width:11;
            unsigned res2:1;
            unsigned command:4;
            unsigned gpu:4;
        } __attribute__((packed));
        unsigned long value;
        struct {
            unsigned short low;
            unsigned short high;
        } __attribute__((packed));
    } __attribute__((packed));
} __attribute__((packed));

struct RCC_COLOR {
    union {
        struct {
            unsigned color:16;
            unsigned reserved:8;
            unsigned command:4;
            unsigned gpu:4;
        } __attribute__((packed));
        unsigned long value;
        struct {
            unsigned short low;
            unsigned short high;
        } __attribute__((packed));
    } __attribute__((packed));
} __attribute__((packed));

struct RCC_STARTCOPY {
    union {
        struct {
            unsigned res1:1;
            unsigned ST:1;
            unsigned DT:1;
            unsigned ROP:4;
            unsigned OPER:3;
            unsigned res2:14;
            unsigned command:4;
            unsigned gpu:4;
        } __attribute__((packed));
        unsigned long value;
        struct {
            unsigned short low;
            unsigned short high;
        } __attribute__((packed));
    } __attribute__((packed));
} __attribute__((packed));

typedef struct _RGB {
    unsigned red:3;
    unsigned green:3;
    unsigned blue:2;
} __attribute__((packed)) rgb;

#define OPER_FILL 0b000
#define OPER_COPY 0b001
#define OPER_COPY_TRANS 0b110

#define SIN45   	46341   // sin(45) * 2^16)
#define ONEP25  	81920   // 1.25 * 2^16

const extern struct GPU_SETTINGS vga;
const extern struct GPU_SETTINGS wvga;
const extern struct GPU_SETTINGS nqvga;

extern struct GPU_SETTINGS *gpu;

extern unsigned int CHR_x;
extern unsigned int CHR_y;
extern unsigned short RCC_CurrentColor;

extern void GPU_Init(const struct GPU_SETTINGS *agpu);
extern void GPU_Command(void * c);
extern void GPU_LoadClut(unsigned int *clut);
extern void GPU_CLS();
extern void GPU_EnableCopper(unsigned char c);
extern void GPU_DisableCopper(unsigned char c);
extern void GPU_CopperScroll(unsigned char c, char d);
extern void GPU_CopperFill(unsigned char copper, unsigned int start, unsigned int end, unsigned int color);
extern void GPU_VSync();
extern void GPU_TestCard();
extern void GPU_SetCLUT(unsigned int val, unsigned int color);
extern void GPU_ScrollUp(unsigned short num);
extern void GPU_ScrollLeft(unsigned short num);

extern void CHR_SetFGColor(unsigned short color);
extern void CHR_SetBGColor(unsigned short color);
extern void CHR_SetFontBase(void *base);
extern void CHR_PrintChar(unsigned short c, unsigned char trans);
extern void CHR_TextArea(unsigned short x1, unsigned short y1, unsigned short x2, unsigned short y2);
extern void CHR_PrintPos(unsigned short x, unsigned short y);
extern void CHR_LoadFont(const unsigned char *font);

extern void RCC_SetColor(unsigned short color);
extern void RCC_DestAddr(unsigned short x, unsigned short y);
extern void RCC_RectSize(unsigned short x, unsigned short y);
extern void RCC_StartCopy(unsigned char oper, unsigned char rop, unsigned char dt, unsigned char st);
extern void RCC_SetPixel(unsigned short x, unsigned short y);
extern void RCC_FilledRectangle(unsigned short x1, unsigned short y1, unsigned short x2, unsigned short y2);
extern void RCC_DitheredRectangle(unsigned short x1, unsigned short y1, unsigned short x2, unsigned short y2, unsigned char pct);
extern void RCC_Rectangle(unsigned short x1, unsigned short y1, unsigned short x2, unsigned short y2);
extern void RCC_Draw(unsigned short x1, unsigned short y1, unsigned short x2, unsigned short y2);
extern void RCC_Circle(unsigned short x, unsigned short y, unsigned short rad);
extern void RCC_FilledCircle(unsigned short x, unsigned short y, unsigned short rad);
extern void RCC_Copy(unsigned short sx, unsigned short sy, unsigned short sw, unsigned short sh, unsigned short dx, unsigned short dy);

#endif
