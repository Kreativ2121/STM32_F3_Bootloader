#include "bootloader.h"

typedef void (*pFunction)(void);

void JumpToAddress(uint32_t addr) {
    uint32_t JumpAddress = *(uint32_t *) (addr + 4); //Definitions for jump
    pFunction Jump = (pFunction) JumpAddress; //Definitions for jump

    HAL_RCC_DeInit(); //Peripherials deinitialization
    HAL_DeInit();
    SysTick->CTRL = 0;	//SysTick Reset
    SysTick->LOAD = 0;	//SysTick Reset
    SysTick->VAL = 0; 	//SysTick Reset

    /* Ustawić offset tablicy wektorów przerwań (SCB→VTOR). */
    SCB->VTOR = addr;
    /*Ustawić wskaźnik stosu (odczytany z tablicy przerwań
    z adresu 0x0000 [względnego do początku programu aplikacji
     użytkownika]).*/
    __set_MSP(*(uint32_t *) addr);

    Jump(); //Jump to begin of the program -> start_of_program + 0x0004
}

void JumpToApplication() {
    JumpToAddress(APP_ADDRESS);
}
