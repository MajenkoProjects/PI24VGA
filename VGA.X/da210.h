#ifndef _DA210_H
#define _DA210_H

#include "GenericTypeDefs.h"

extern const char __GOLFontDefault[] __attribute__((space(prog), aligned(2)));
#define GFX_FONT_SPACE __prog__

typedef enum
{
    FLASH         = 0x0000,                 // internal flash
    EXTERNAL      = 0x0001,                 // external memory
    FLASH_JPEG    = 0x0002,                 // internal flash
    EXTERNAL_JPEG = 0x0003,                 // external memory
    RAM           = 0x0004,                 // RAM
    EDS_EPMP      = 0x0005,                 // memory in EPMP, base addresses are
                                            // are set in the hardware profile

    IMAGE_MBITMAP = 0x0000,                 // data resource is type Microchip bitmap
    IMAGE_JPEG    = 0x0100,                 // data resource is type JPEG

    COMP_NONE     = 0x0000,                 // no compression
    COMP_RLE      = 0x1000,                 // compressed with RLE
    COMP_IPU      = 0x2000,                 // compressed with DEFLATE (for IPU)
} GFX_RESOURCE;


typedef struct
{
    GFX_RESOURCE  type;                     // must be FLASH
    GFX_FONT_SPACE char    *address;                 // font image address in FLASH
} FONT_FLASH;
#define BLACK 0x0000
#define RED 0x0001
#define GREEN 0x0002
#define YELLOW 0x0003
#define BLUE 0x0004
#define MAGENTA 0x0005
#define CYAN 0x0006
#define WHITE 0x0007

typedef struct
{
    GFX_RESOURCE type;                      // Resource type. Valid types are:
                                            // - EXTERNAL
                                            // - EDS_EPMP
    WORD         ID;                        // Memory ID, user defined value to differentiate
                                            // between graphics resources of the same type.
                                            // When using EDS_EPMP the following ID values are
                                            // reserved and used by the Microchip display driver
                                            //   - 0 - reserved (do not use)
                                            //   - 1 - reserved for base address of EPMP CS1
                                            //   - 2 - reserved for base address of EPMP CS2
    DWORD        address;                   // Data image address (user data, bitmap or font)
} GFX_EXTDATA;


typedef GFX_EXTDATA FONT_EXTERNAL;

extern const FONT_FLASH GOLFontDefault;

#endif
