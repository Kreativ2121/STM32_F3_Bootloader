#ifndef BOOTLOADER_BOOTLOADER_H
#define BOOTLOADER_BOOTLOADER_H

#include "stm32f3xx_hal.h"

/*Address of programme start (the place
to jump to after bootloader finishes working)*/
#define APP_ADDRESS (uint32_t)0x08010000

void JumpToApplication();

#endif //BOOTLOADER_BOOTLOADER_H
