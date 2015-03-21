#include <p24Fxxxx.h>
#include <string.h>
#include <stdio.h>
#include "GenericTypeDefs.h"
#include "gpu.h"
#include "fonts.h"

__eds__ BYTE GFXDisplayBuffer[GFX_BUFFER_SIZE] __attribute__((eds, address(GFX_DISPLAY_BUFFER_START_ADDRESS), noload, section("Graphics_Display_Buffer")));
volatile unsigned int scanline = 0;

volatile unsigned int copperbars0[480];
volatile unsigned int copperbars1[480];
volatile unsigned int copperbars2[480];
volatile unsigned int copperbars3[480];

volatile unsigned int currentCLUT[16];
volatile unsigned char copper = 0;
volatile BOOL vsync = FALSE;

const struct GPU_SETTINGS vga = {
    640,480,            // Width,Height
    0b001, 4,           // 2bpp, 4 colours
    11,                  // GPUCLK Div 8
    16, 96, 48, 800-640,    // Horizontal sync
    10, 2, 33, 525-480,      // Vertical sync
    0,                   // No double buffering
    1                   // No pixel stretching
};

const struct GPU_SETTINGS nqvga = {
    160,480,            // Width,Height
    0b010, 16,           // 2bpp, 4 colours
    48,                 // GPUCLK Div 8
    4, 24, 12, 4 + 24 + 12,      // Horizontal sync
    10, 2, 33, 10+10 + 2+2 + 33+33,      // Vertical sync
    0,                   // No double buffering
    4                   // Pixels are 4 times wider than normal
};

const struct GPU_SETTINGS wvga = {
    720,480,            // Width,Height
    0b000, 2,            // 1bpp, 2 colours
    7,                  // GPUCLK Div 8
    45, 128, 52, 45+128+52,       // Horizontal sync
    10, 2, 33, 90,       // Vertical sync
    0,                    // No double buffering
    1                   // No pixel stretching
};

struct GPU_SETTINGS *gpu = NULL;

void GPU_Command(void * c)
{
    struct GPU_GENERIC *cmd = (struct GPU_GENERIC *)c;

    // If the FIFO is full, then wait for a spare slot.
    while(G1STATbits.CMDFUL==1)
        continue;

    G1CMDL=cmd->low;
    G1CMDH=cmd->high;
    Nop();
}

void GPU_Init(const struct GPU_SETTINGS *agpu)
{

    G1CON1bits.G1EN     = 0;
    CLKDIV2bits.GCLKDIV = agpu->clock;

    G1CON2bits.DPMODE   = 0b001;
    G1DBENbits.GDBEN    = 0b11111111;

    G1DPWTbits.DPWT     = agpu->hb_total + agpu->width; //HB_DISPLAY+HB_FRONT+HB_SYNC+HB_BACK;
    G1HSYNCbits.HSST    = agpu->hb_front; //HB_FRONT;
    G1HSYNCbits.HSLEN   = agpu->hb_sync; // HB_SYNC;
    G1DBLCONbits.HENST  = agpu->hb_total; //HB_FRONT+HB_SYNC+HB_BACK;
    G1ACTDAbits.ACTPIX  = agpu->hb_total; //HB_FRONT+HB_SYNC+HB_BACK;
    G1DPWbits.DPW       = agpu->width; //HB_DISPLAY;

    G1DPHTbits.DPHT     = agpu->vb_total + agpu->height; //VB_DISPLAY+VB_FRONT+VB_SYNC+VB_BACK+45;
    G1VSYNCbits.VSST    = agpu->vb_front; //VB_FRONT;
    G1VSYNCbits.VSLEN   = agpu->vb_sync; //VB_SYNC;
    G1DBLCONbits.VENST  = agpu->vb_total;
    G1ACTDAbits.ACTLINE = agpu->vb_total - 1;
    G1DPHbits.DPH       = agpu->height; //VB_DISPLAY;

    G1CON3bits.DPCLKPOL = 0;
    G1CON3bits.DPVSOE   = 1;
    G1CON3bits.DPHSOE   = 1;
    G1CON3bits.DPHSPOL  = 0;
    G1CON3bits.DPVSPOL  = 0;

    G1CON3bits.DPPINOE  = 1;
    G1CON3bits.DPPOWER  = 1;
    G1CON3bits.DPPWROE  = 1;
    G1CON3bits.DPENOE   = 1;
    G1CON3bits.DPENPOL  = 1;

//    G1CON2bits.DPTEST=0b10;

    G1CON1bits.PUBPP    = agpu->bpp; //0b001;
    G1CON2bits.DPBPP    = agpu->bpp; //0b001;


    GFX_SetDisplayArea(GFX_DISPLAY_BUFFER_START_ADDRESS);
    GFX_SetWorkArea1(GFX_DISPLAY_BUFFER_START_ADDRESS);
    GFX_SetWorkArea2(GFX_DISPLAY_BUFFER_START_ADDRESS);

    G1PUW = agpu->width;
    G1PUH = agpu->height;

    G1CON1bits.G1EN  = 1;

    G1IRbits.VMRGNIF = 0;
    G1IEbits.VMRGNIE = 1;
    G1IRbits.HMRGNIF = 0;
    G1IEbits.HMRGNIE = 1;

    IFS6bits.GFX1IF  = 0;
    IEC6bits.GFX1IE  = 1;
    IPC25bits.GFX1IP = 0b111;


    CHR_SetFontBase(coreFont);
    CHR_TextArea(0, 0, agpu->width-1, agpu->height + agpu->vb_back + agpu->vb_front + agpu->vb_sync - 1);
    CHR_SetFGColor(1);
    CHR_SetBGColor(0);
    gpu = (struct GPU_SETTINGS *)agpu;
}

void GPU_LoadCLUT(unsigned int *clut)
{
    register unsigned char i;

    G1CLUTbits.CLUTEN=1;
    G1CLUTbits.CLUTRWEN = 1;
    for(i = 0; i < gpu->colors; i++)
    {
        G1CLUTbits.CLUTADR = i;
        G1CLUTWR  = clut[i];
        currentCLUT[i] = clut[i];
        while(G1CLUTbits.CLUTBUSY)
        {
            Nop();
        }
    }
    G1CLUTbits.CLUTRWEN = 0;
}

void GPU_SetCLUT(unsigned int val, unsigned int color)
{
    if(val>=gpu->colors)
    {
        printf("CLUT too high: %d\n",val);
        return;
    }

    G1CLUTbits.CLUTEN=1;
    G1CLUTbits.CLUTRWEN = 1;
    G1CLUTbits.CLUTADR = val;
    G1CLUTWR  = color;
    currentCLUT[val] = color;
    while(G1CLUTbits.CLUTBUSY)
    {
        Nop();
    }
    G1CLUTbits.CLUTRWEN = 0;

}

void GPU_CLS()
{
    RCC_SetColor(0);
    RCC_FilledRectangle(0,0,gpu->width-1,gpu->height-1);
    CHR_PrintPos(0,0);
}

void __attribute__((interrupt, no_auto_psv))_GFX1Interrupt(void)
{
    register unsigned int cl;
    if(G1IRbits.VMRGNIF==1)
    {
        vsync = TRUE;
        G1CLUTbits.CLUTRWEN = 1;
        G1CLUTbits.CLUTADR = 0;
        G1CLUTWR  = copper & 0x01 ? copperbars0[0] : currentCLUT[0];
        G1CLUTbits.CLUTADR = 1;
        G1CLUTWR  = copper & 0x02 ? copperbars1[0] : currentCLUT[1];
        G1CLUTbits.CLUTADR = 2;
        G1CLUTWR  = copper & 0x04 ? copperbars2[0] : currentCLUT[2];
        G1CLUTbits.CLUTADR = 3;
        G1CLUTWR  = copper & 0x08 ? copperbars3[0] : currentCLUT[3];
        G1CLUTbits.CLUTRWEN = 0;
        scanline = 0;
        G1IRbits.VMRGNIF=0;
    }

    if(G1IRbits.HMRGNIF==1)
    {
        if(copper)
        {
            if(scanline > gpu->vb_total)
            {
                cl = scanline-gpu->vb_total;
                G1CLUTbits.CLUTRWEN = 1;
                if(copper & 0x01)
                {
                    G1CLUTbits.CLUTADR = 0;
                    G1CLUTWR  = copperbars0[cl];
                }
                if(copper & 0x02)
                {
                    G1CLUTbits.CLUTADR = 1;
                    G1CLUTWR  = copperbars1[cl];
                }
                if(copper & 0x04)
                {
                    G1CLUTbits.CLUTADR = 2;
                    G1CLUTWR  = copperbars2[cl];
                }
                if(copper & 0x08)
                {
                    G1CLUTbits.CLUTADR = 3;
                    G1CLUTWR  = copperbars3[cl];
                }
                G1CLUTbits.CLUTRWEN = 0;
            }
        }
        scanline++;
        G1IRbits.HMRGNIF=0;
    }
    IFS6bits.GFX1IF=0;
}

void GPU_EnableCopper(unsigned char c)
{
    copper |= c;
}

void GPU_DisableCopper(unsigned char c)
{
    copper &= ~c;
}

void GPU_CopperScroll(unsigned char c, char d)
{
    register unsigned int i;
    unsigned int pass;
    if(d==1)
    {
        if(c & 0x01)
        {
            pass = copperbars0[0];
            for(i=0; i<479; i++)
                copperbars0[i] = copperbars0[i+1];
            copperbars0[479]=pass;
        }
        if(c & 0x02)
        {
            pass = copperbars1[0];
            for(i=0; i<479; i++)
                copperbars1[i] = copperbars1[i+1];
            copperbars1[479]=pass;
        }
        if(c & 0x04)
        {
            pass = copperbars2[0];
            for(i=0; i<479; i++)
                copperbars2[i] = copperbars2[i+1];
            copperbars2[479]=pass;
        }
        if(c & 0x08)
        {
            pass = copperbars3[0];
            for(i=0; i<479; i++)
                copperbars3[i] = copperbars3[i+1];
            copperbars3[479]=pass;
        }
    }

    if(d==-1)
    {
        if(c & 0x01)
        {
            pass = copperbars0[479];
            for(i=479; i>0; i--)
                copperbars0[i] = copperbars0[i-1];
            copperbars0[0] = pass;
        }
        if(c & 0x02)
        {
            pass = copperbars1[479];
            for(i=479; i>0; i--)
                copperbars1[i] = copperbars1[i-1];
            copperbars1[0] = pass;
        }
        if(c & 0x04)
        {
            pass = copperbars2[479];
            for(i=479; i>0; i--)
                copperbars2[i] = copperbars2[i-1];
            copperbars2[0] = pass;
        }
        if(c & 0x08)
        {
            pass = copperbars3[479];
            for(i=479; i>0; i--)
                copperbars3[i] = copperbars3[i-1];
            copperbars3[0] = pass;
        }
    }
}

void GPU_VSync()
{
    while(vsync==FALSE)
        continue;
    vsync = FALSE;
}

void GPU_CopperFill(unsigned char copper, unsigned int start, unsigned int end, unsigned int color)
{
    while(start <= end)
    {
        if(copper & 0b0001)
            copperbars0[start] = color;
        if(copper & 0b0010)
            copperbars1[start] = color;
        if(copper & 0b0100)
            copperbars2[start] = color;
        if(copper & 0b1000)
            copperbars3[start] = color;
        start++;
    }
}




void GPU_TestCard()
{
    unsigned int i;
    char temp[20];
    unsigned int tcClut[16] = {
        0b00000000,
        0b11111111,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
    };

    if(!gpu)
        GPU_Init(&vga);
    GPU_LoadCLUT(tcClut);
    GPU_CLS();

    RCC_SetColor(1);
    RCC_Circle(gpu->width/2,gpu->height/2,80);
    RCC_Circle(gpu->width/2,gpu->height/2,20);


    RCC_Draw(0,0,100/gpu->stretch,0);
    RCC_Draw(0,0,0,100);
    RCC_Draw(0,0,80/gpu->stretch,80);

    RCC_Draw(gpu->width-1,0,gpu->width-101/gpu->stretch,0);
    RCC_Draw(gpu->width-1,0,gpu->width-1,100);
    RCC_Draw(gpu->width-1,0,gpu->width-81/gpu->stretch,80);
    RCC_Draw(0,gpu->height-1,100/gpu->stretch,gpu->height-1);
    RCC_Draw(0,gpu->height-1,0,gpu->height-101);
    RCC_Draw(0,gpu->height-1,80/gpu->stretch,gpu->height-81);
    RCC_Draw(gpu->width-1,gpu->height-1,gpu->width-101/gpu->stretch,gpu->height-1);
    RCC_Draw(gpu->width-1,gpu->height-1,gpu->width-1,gpu->height-101);
    RCC_Draw(gpu->width-1,gpu->height-1,gpu->width-81/gpu->stretch,gpu->height-81);

    int sz = 70;

    RCC_Draw(gpu->width/2-sz,gpu->height/2-sz,gpu->width/2+sz,gpu->height/2+sz);
    RCC_Draw(gpu->width/2,   gpu->height/2-sz,gpu->width/2,   gpu->height/2+sz);
    RCC_Draw(gpu->width/2+sz,gpu->height/2-sz,gpu->width/2-sz,gpu->height/2+sz);
    RCC_Draw(gpu->width/2+sz,gpu->height/2,   gpu->width/2-sz,gpu->height/2);

    RCC_Rectangle(gpu->width/2-sz,gpu->height/2-sz,gpu->width/2+sz,gpu->height/2+sz);

    int top = 64;
    int bottom = (gpu->height-1) - 64;

    RCC_SetColor(2);
    RCC_FilledRectangle(gpu->width/10,top,gpu->width/6,bottom);
    RCC_SetColor(1);
    RCC_Rectangle(gpu->width/10,top,gpu->width/6,bottom);

    RCC_SetColor(3);
    RCC_FilledRectangle(gpu->width-(gpu->width/10),top,gpu->width-(gpu->width/6),bottom);
    RCC_SetColor(1);
    RCC_Rectangle(gpu->width-(gpu->width/10),top,gpu->width-(gpu->width/6),bottom);



    int shades = 4;
    int shade[4] = {
        0b00000000,
        0b01011011,
        0b10101101,
        0b11111111
    };
    int h = bottom - top;
    for(i=0; i<h; i++)
    {
        int s = i * shades / h;
        GPU_CopperFill(0b0100,top+i,top+i,shade[s]);
    }
    GPU_EnableCopper(0b0100);

    shades = 24;
    int shade1[24] = {
        0b00000000,
        0b00000001,
        0b00000010,
        0b00000011,
        0b00000100,
        0b00000101,
        0b00000110,
        0b00000111,
        0b00000000,
        0b00001000,
        0b00010000,
        0b00011000,
        0b00100000,
        0b00101000,
        0b00110000,
        0b00111000,
        0b00000000,
        0b00000000,
        0b01000000,
        0b01000000,
        0b10000000,
        0b10000000,
        0b11000000,
        0b11000000,
    };

    for(i=0; i<h; i++)
    {
        int s = i * shades / h;
        GPU_CopperFill(0b1000,top+i,top+i,shade1[s]);
    }
    GPU_EnableCopper(0b1000);

    CHR_LoadFont(topaz);
    CHR_SetFGColor(1);
    CHR_PrintPos((gpu->width/2) - ((17*8)/2),gpu->height/2 + 110);
    printf("www.majenko.co.uk");

    CHR_LoadFont(sinclair);

    sprintf(temp,"Resolution: %dx%d",gpu->width,gpu->height);
    CHR_PrintPos((gpu->width/2) - ((strlen(temp)*8)/2),gpu->height/2 - 118);
    printf("%s",temp);

    GPU_CopperFill(0b0100,31,40,0b11111000);
    GPU_CopperFill(0b0100,41,50,0b11000111);
    GPU_CopperFill(0b0100,51,60,0b00111111);

    GPU_CopperFill(0b1000,31,40,0b00000111);
    GPU_CopperFill(0b1000,41,50,0b00111000);
    GPU_CopperFill(0b1000,51,60,0b11000000);

    RCC_SetColor(3);
    RCC_FilledRectangle(gpu->width/2 - gpu->width/4, 31, gpu->width/2 + gpu->width/4, 60);

    int dither = 16;
    int num = 16;
    int db = (gpu->width/(num*2));
    int step = 224/num;
    for(i=0; i<num; i++)
    {
        RCC_SetColor(2);

        RCC_DitheredRectangle(
                gpu->width/2 - gpu->width/4 + i*db, 31,
                gpu->width/2 - gpu->width/4 + (i+1)*db, 60,
                dither
                );

        dither += step;
        if(dither>255) dither=255;
    }

    RCC_SetColor(1);
    RCC_Rectangle(gpu->width/2 - gpu->width/4, 30, gpu->width/2 + gpu->width/4, 61);

    RCC_SetColor(2);
    RCC_FilledRectangle(gpu->width/2 - gpu->width/4, gpu->height - 30, gpu->width/2 + gpu->width/4, gpu->height - 60);
    RCC_SetColor(3);
    for(i=0; i<gpu->width/2; i+=2)
    {
        RCC_Draw(gpu->width/2 - gpu->width/4 + i, gpu->height - 30, gpu->width/2 - gpu->width/4 + i, gpu->height - 60);
    }

    RCC_SetColor(1);
    RCC_Rectangle(gpu->width/2 - gpu->width/4, gpu->height - 30, gpu->width/2 + gpu->width/4, gpu->height - 60);

    GPU_CopperFill(0b0100,gpu->height-60,gpu->height-45,0b11111111);
    GPU_CopperFill(0b0100,gpu->height-44,gpu->height-30,0b00000000);
    GPU_CopperFill(0b1000,gpu->height-60,gpu->height-45,0b00000000);
    GPU_CopperFill(0b1000,gpu->height-44,gpu->height-30,0b11111111);
}

void GPU_ScrollUp(unsigned short num)
{
    register unsigned int i;
    unsigned int oc;
    RCC_Copy(0,num,gpu->width,gpu->height-num,0,0);
    oc = RCC_CurrentColor;
    RCC_SetColor(0);
    RCC_FilledRectangle(0,(gpu->height-num)-1,gpu->width-1,gpu->height-1);
    RCC_SetColor(oc);
}

void GPU_ScrollLeft(unsigned short num)
{
    register unsigned int i;
    unsigned int oc;
    RCC_Copy(num,0,(gpu->width-num),gpu->height-1,0,0);
    oc = RCC_CurrentColor;
    RCC_SetColor(0);
    RCC_FilledRectangle((gpu->width-num),0,gpu->width-1,gpu->height-1);
    RCC_SetColor(oc);
}
