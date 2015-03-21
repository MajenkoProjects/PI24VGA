#include <p24Fxxxx.h>
#include <string.h>
#include <stdio.h>
#include "GenericTypeDefs.h"
#include "gpu.h"
#include "fonts.h"

unsigned short RCC_CurrentColor = 0;

void RCC_SetColor(unsigned short color)
{
    struct RCC_COLOR col;
    col.color = color;
    col.gpu = GPU_RCC;
    col.command = 0x6;

    GPU_Command(&col);
    RCC_CurrentColor = color;
}

void RCC_DestAddr(unsigned short x, unsigned short y)
{
    struct RCC_OFFSET offset;
    offset.offset = (unsigned long)x + ((unsigned long)y*(unsigned long)gpu->width);
    offset.command = 0x3;
    offset.gpu = GPU_RCC;
    GPU_Command(&offset);
}

void RCC_SrcAddr(unsigned short x, unsigned short y)
{
    struct RCC_OFFSET offset;
    offset.offset = (unsigned long)x + ((unsigned long)y*(unsigned long)gpu->width);
    offset.command = 0x2;
    offset.gpu = GPU_RCC;
    GPU_Command(&offset);
}

void RCC_RectSize(unsigned short x, unsigned short y)
{
    struct RCC_SIZE size;
    size.height = y;
    size.width = x;
    size.gpu = GPU_RCC;
    size.command = 0x4;
    GPU_Command(&size);
}

void RCC_StartCopy(unsigned char oper, unsigned char rop, unsigned char dt, unsigned char st)
{
    struct RCC_STARTCOPY go;
    go.DT = dt;
    go.OPER = oper;
    go.ROP = rop;
    go.ST = st;
    go.gpu = GPU_RCC;
    go.command = 0x7;
    GPU_Command(&go);
}

void RCC_SetPixel(unsigned short x, unsigned short y)
{
    RCC_DestAddr(x,y);
    RCC_RectSize(1,1);
    RCC_StartCopy(OPER_FILL,0xC,0,0);
}

void RCC_FilledRectangle(unsigned short x1, unsigned short y1, unsigned short x2, unsigned short y2)
{
    unsigned short s;

    if(x1 > x2)
    {
        s = x1;
        x1 = x2;
        x2 = s;
    }

    if(y1 > y2)
    {
        s = y1;
        y1 = y2;
        y2 = s;
    }

    RCC_DestAddr(x1,y1);
    RCC_RectSize((x2-x1)+1,(y2-y1)+1);
    RCC_StartCopy(OPER_FILL,0xC,0,0);
}

void RCC_Rectangle(unsigned short x1, unsigned short y1, unsigned short x2, unsigned short y2)
{
    RCC_Draw(x1,y1,x2,y1);
    RCC_Draw(x1,y1,x1,y2);
    RCC_Draw(x2,y2,x2,y1);
    RCC_Draw(x2,y2,x1,y2);
}

#define abs(x) (x>0?x:(0-x))

void RCC_Draw(unsigned short x1, unsigned short y1, unsigned short x2, unsigned short y2)
{
    int w, h;
    int dx1=0, dy1=0, dx2=0, dy2=0;
    int longest, shortest;
    int numerator;
    int i;

    // For vertical and horizontal lines, use the FilledRectangle OPER.
    if((x1==x2) || (y1==y2))
    {
        RCC_FilledRectangle(x1,y1,x2,y2);
        return;
    }

    w = x2 - x1;
    h = y2 - y1;

    if(w<0)
    {
        dx1 = -1;
        dx2 = -1;
    }
    else if(w>0)
    {
        dx1 = 1;
        dx2 = 1;
    }

    if(h<0)
        dy1 = -1;
    else if(h>0)
        dy1 = 1;

    longest = abs(w);
    shortest = abs(h);
    if(!(longest>shortest))
    {
        longest = abs(h);
        shortest = abs(w);
        if(h<0)
            dy2 = -1;
        else if(h>0)
            dy2 = 1;
        dx2=0;
    }
    numerator = longest >> 1;
    for(i=0; i<=longest; i++)
    {
        RCC_SetPixel(x1,y1);
        numerator += shortest;
        if(!(numerator<longest))
        {
            numerator -= longest;
            x1 += dx1;
            y1 += dy1;
        } else {
            x1 += dx2;
            y1 += dy2;
        }
    }
}

void RCC_Circle(unsigned short x, unsigned short y, unsigned short rad)
{

    SHORT       xLimit, xPos, yPos, error, xStretch;
    DWORD_VAL   temp;

    temp.Val = SIN45 * rad;
    xLimit = temp.w[1] + 1;
    temp.Val = (DWORD) (ONEP25 - ((LONG) rad << 16));
    error = (SHORT) (temp.w[1]);
    yPos = rad;

    for(xPos = 0; xPos <= xLimit; xPos++)
    {
        RCC_SetPixel(x + xPos, y - yPos);         // 1st quadrant
        RCC_SetPixel(x + yPos, y - xPos);
        RCC_SetPixel(x + xPos, y + yPos);         // 2nd quadrant
        RCC_SetPixel(x + yPos, y + xPos);
        RCC_SetPixel(x - xPos, y + yPos);         // 3rd quadrant
        RCC_SetPixel(x - yPos, y + xPos);
        RCC_SetPixel(x - yPos, y - xPos);         // 4th quadrant
        RCC_SetPixel(x - xPos, y - yPos);

        if(error > 0)
        {
            yPos--;
            error += 5 + ((xPos - yPos) << 1);
        } else {
            error += 3 + (xPos << 1);
        }
    }
}

void RCC_FilledCircle(unsigned short x, unsigned short y, unsigned short rad)
{

    SHORT       xLimit, xPos, yPos, error;
    DWORD_VAL   temp;

    temp.Val = SIN45 * rad;
    xLimit = temp.w[1] + 1;
    temp.Val = (DWORD) (ONEP25 - ((LONG) rad << 16));
    error = (SHORT) (temp.w[1]);
    yPos = rad;

    for(xPos = 0; xPos <= xLimit; xPos++)
    {
        RCC_Draw(x+xPos,y-yPos,x+xPos,y+yPos);
        RCC_Draw(x+yPos,y-xPos,x+yPos,y+xPos);
        RCC_Draw(x-xPos,y+yPos,x-xPos,y-yPos);
        RCC_Draw(x-yPos,y+xPos,x-yPos,y-xPos);

        if(error > 0)
        {
            yPos--;
            error += 5 + ((xPos - yPos) << 1);
        } else {
            error += 3 + (xPos << 1);
        }
    }
}

void RCC_DitheredRectangle(unsigned short x1, unsigned short y1, unsigned short x2, unsigned short y2, unsigned char pct)
{
    unsigned short x,y;
    unsigned short s;

    if(x1 > x2)
    {
        s = x1;
        x1 = x2;
        x2 = s;
    }

    if(y1 > y2)
    {
        s = y1;
        y1 = y2;
        y2 = s;
    }

    for(y = y1; y <= y2; y++)
    {
        for(x = x1; x <= x2; x++)
        {
            if((rand() & 0xFF) <= pct)
            {
                RCC_SetPixel(x,y);
            }
        }
    }
}

void RCC_Copy(unsigned short sx, unsigned short sy, unsigned short sw, unsigned short sh, unsigned short dx, unsigned short dy)
{
    RCC_SrcAddr(sx,sy);
    RCC_DestAddr(dx,dy);
    RCC_RectSize(sw,sh);
    RCC_StartCopy(OPER_COPY,0xC,0,0);
}
