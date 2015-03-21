#include <p24Fxxxx.h>
#include <string.h>
#include <stdio.h>
#include "GenericTypeDefs.h"
#include "gpu.h"
#include "fonts.h"

unsigned int CHR_x = 0;
unsigned int CHR_y = 0;

void CHR_SetFGColor(unsigned short color)
{
    struct CHR_COLOR col;
    col.color = color;
    col.gpu = GPU_CHR;
    col.command = 0;
    GPU_Command(&col);
}

void CHR_SetBGColor(unsigned short color)
{
    struct CHR_COLOR col;
    col.color = color;
    col.gpu = GPU_CHR;
    col.command = 1;
    GPU_Command(&col);
}

void CHR_SetFontBase(void *base)
{
    struct CHR_FONTBASE b;
    b.address = (unsigned int)base;
    b.gpu = GPU_CHR;
    b.command = 2;
    GPU_Command(&b);
}

void CHR_PrintChar(unsigned short c, unsigned char trans)
{
    struct CHR_PRINTCHAR cmd;
    cmd.character = c;
    cmd.trans = trans;
    cmd.gpu = GPU_CHR;
    cmd.command = 3;
    GPU_Command(&cmd);
}

void CHR_TextArea(unsigned short x1, unsigned short y1, unsigned short x2, unsigned short y2)
{
    struct CHR_COORD tl;
    struct CHR_COORD br;
    tl.x = x1;
    tl.y = y1;
    tl.command = 8;
    tl.gpu = GPU_CHR;
    br.x = x2;
    br.y = y2;
    br.command = 9;
    br.gpu = GPU_CHR;
    GPU_Command(&tl);
    GPU_Command(&br);
}

void CHR_PrintPos(unsigned short x, unsigned short y)
{
    struct CHR_COORD loc;
    loc.x = x;
    loc.y = y;
    loc.command = 0xa;
    loc.gpu = GPU_CHR;
    GPU_Command(&loc);
    CHR_x = x;
    CHR_y = y;
}

void CHR_LoadFont(const unsigned char *font)
{
    memcpy(&coreFont[0x0408],font,256*8);
}

int write(int handle, char *buffer, unsigned int len)
{
    unsigned int i;

    for(i=0; i<len; i++)
    {
        switch(*(buffer+i))
        {
            case '\r':
                CHR_x = 0;
                break;
            case '\n':
                CHR_x = 0;
                CHR_y += 8;
                if(CHR_y >= gpu->height)
                {
                    GPU_ScrollUp(8);
                    CHR_y -= 8;
                }
                break;
            default:
                CHR_PrintPos(CHR_x,CHR_y);
                CHR_PrintChar((int)*(buffer+i),0);
                CHR_x+=8;
                if(CHR_x >= gpu->width)
                {
                    CHR_x = 0;
                    CHR_y += 8;
                    if(CHR_y >= gpu->height)
                    {
                        GPU_ScrollUp(8);
                        CHR_y -= 8;
                    }
                }
            break;
        }
    }

    return len;
}
