#include "bootloader.h"

typedef void (*pFunction)(void);

//Zapisywanie aplikacji użytkownika do FLASH
uint8_t WriteUserApplication(uint32_t* data, uint32_t dataSize, uint32_t offset) {
    if (HAL_FLASH_Unlock() == HAL_OK) {
        for (int i = 0; i < dataSize; i++) {
            HAL_StatusTypeDef success = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, APP_ADDRESS + offset + (i * 4), data[i]);

            if (success != HAL_OK) {
                HAL_FLASH_Lock();
                return 0;
            }
        }
        HAL_FLASH_Lock();
    } else {
        return 0;
    }

    return 1;//zmiana testowa
}

//Usuwanie aplikacji użytkownika z pamięci FLASH
uint8_t EraseUserApplication() {
    HAL_StatusTypeDef success = HAL_ERROR;
    uint32_t errorSector = 0;

    if (HAL_FLASH_Unlock() == HAL_OK) {
        FLASH_EraseInitTypeDef eraseInit = {0};
        eraseInit.NbPages = 96; // Count of pages to erase
        eraseInit.PageAddress = 0x08010000; // Start address of the first page to erase
        eraseInit.TypeErase = FLASH_TYPEERASE_PAGES;

        success = HAL_FLASHEx_Erase(&eraseInit, &errorSector);

        HAL_FLASH_Lock();
    }

    return success == HAL_OK ? 1 : 0;
}

//Funkcja wysyłająca dane do odczytu poprzez COM
void SendBackup() {
    uint8_t* app = (uint8_t *) (APP_ADDRESS);

    // Send 192 kB of user application
    for (int i = 0; i < 192 * 1024; i++) {
        //SendByte(app[i]); //TUTAJ WYWOLAC FUNKCJE DO WYSYLANIA JEDNEGO BAJTU
    }
}

//Funkcja do sprawdzania czy aplikacja użytkownika jest w bootloaderze
uint8_t UserApplicationExists() {
    uint32_t bootloaderMspValue = *(uint32_t *) (FLASH_BASE);
    uint32_t appMspValue = *(uint32_t *) (APP_ADDRESS);

    return appMspValue == bootloaderMspValue ? 1 : 0;
}

//Funkcja do przeskoczenia z bootloadera do aplikacji użytkownika
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
