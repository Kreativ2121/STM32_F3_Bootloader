#ifndef __M_STM32Fxx_H
#define __M_STM32Fxx_H

#include <cstdio>
#include "main.h"

//########################################################################################
// Unie
//########################################################################################

typedef union { 
	uint16_t  w;
        struct{
		unsigned char l;
                unsigned char h;

	}c;
	struct{
		unsigned char b0:1;
                unsigned char b1:1;
                unsigned char b2:1;
                unsigned char b3:1;
		unsigned char b4:1;
                unsigned char b5:1;
		unsigned char b6:1;
                unsigned char b7:1;
                unsigned char b8:1;
                unsigned char b9:1;
                unsigned char b10:1;
                unsigned char b11:1;
                unsigned char b12:1;
                unsigned char b13:1;
                unsigned char b14:1;
                unsigned char b15:1;
	}b;
}M_bit16;

typedef union { 
	uint32_t  l;
        struct{
		unsigned char ll;
                unsigned char lh;
		unsigned char hl;
                unsigned char hh;

	}c;
        struct{
		unsigned short l;
                unsigned short h;
	}w;
	struct{
		unsigned char b0:1;
                unsigned char b1:1;
                unsigned char b2:1;
                unsigned char b3:1;
		unsigned char b4:1;
                unsigned char b5:1;
		unsigned char b6:1;
                unsigned char b7:1;
                unsigned char b8:1;
                unsigned char b9:1;
                unsigned char b10:1;
                unsigned char b11:1;
                unsigned char b12:1;
                unsigned char b13:1;
                unsigned char b14:1;
                unsigned char b15:1;
                unsigned char b16:1;
                unsigned char b17:1;
                unsigned char b18:1;
                unsigned char b19:1;
                unsigned char b20:1;
                unsigned char b21:1;
                unsigned char b22:1;
                unsigned char b23:1;
                unsigned char b24:1;
                unsigned char b25:1;
                unsigned char b26:1;
                unsigned char b27:1;
                unsigned char b28:1;
                unsigned char b29:1;
                unsigned char b30:1;
                unsigned char b31:1;
	}b;
}M_bit32;






typedef union { 
	uint64_t  l64;
        struct{
		unsigned char lll;
                unsigned char llh;
		unsigned char lhl;
                unsigned char lhh;
		unsigned char hll;
                unsigned char hlh;
		unsigned char hhl;
                unsigned char hhh;
	}c;
        struct{
		unsigned short ll;
                unsigned short lh;
      		unsigned short hl;
                unsigned short hh;
	}w;
        struct{
		unsigned short l;
                unsigned short h;
        }l;
	struct{
		unsigned char b0:1;
                unsigned char b1:1;
                unsigned char b2:1;
                unsigned char b3:1;
		unsigned char b4:1;
                unsigned char b5:1;
		unsigned char b6:1;
                unsigned char b7:1;
                unsigned char b8:1;
                unsigned char b9:1;
                unsigned char b10:1;
                unsigned char b11:1;
                unsigned char b12:1;
                unsigned char b13:1;
                unsigned char b14:1;
                unsigned char b15:1;
                unsigned char b16:1;
                unsigned char b17:1;
                unsigned char b18:1;
                unsigned char b19:1;
                unsigned char b20:1;
                unsigned char b21:1;
                unsigned char b22:1;
                unsigned char b23:1;
                unsigned char b24:1;
                unsigned char b25:1;
                unsigned char b26:1;
                unsigned char b27:1;
                unsigned char b28:1;
                unsigned char b29:1;
                unsigned char b30:1;
                unsigned char b31:1;
                unsigned char b32:1;
                unsigned char b33:1;
                unsigned char b34:1;
                unsigned char b35:1;
		unsigned char b36:1;
                unsigned char b37:1;
		unsigned char b38:1;
                unsigned char b39:1;
                unsigned char b40:1;
                unsigned char b41:1;
                unsigned char b42:1;
                unsigned char b43:1;
                unsigned char b44:1;
                unsigned char b45:1;
                unsigned char b46:1;
                unsigned char b47:1;
                unsigned char b48:1;
                unsigned char b49:1;
                unsigned char b50:1;
                unsigned char b51:1;
                unsigned char b52:1;
                unsigned char b53:1;
                unsigned char b54:1;
                unsigned char b55:1;
                unsigned char b56:1;
                unsigned char b57:1;
                unsigned char b58:1;
                unsigned char b59:1;
                unsigned char b60:1;
                unsigned char b61:1;
                unsigned char b62:1;
                unsigned char b63:1;
	}b;
}M_bit64;



// stworzone do mode, gdzie 2-bitowe wlasnoci na jeden pin
typedef union { 
	uint32_t  l;
        struct{
		unsigned char ll;
                unsigned char lh;
		unsigned char hl;
                unsigned char hh;

	}c;
        struct{
		unsigned short l;
                unsigned short h;
	}w;
	struct{
		unsigned char p0:2;
                unsigned char p1:2;
                unsigned char p2:2;
                unsigned char p3:2;
		unsigned char p4:2;
                unsigned char p5:2;
		unsigned char p6:2;
                unsigned char p7:2;
                unsigned char p8:2;
                unsigned char p9:2;
                unsigned char p10:2;
                unsigned char p11:2;
                unsigned char p12:2;
                unsigned char p13:2;
                unsigned char p14:2;
                unsigned char p15:2;
	}p;
}M_bit32_PAIR;



//########################################################################################
// GPIO
//########################################################################################

typedef struct
{
  __IO M_bit32_PAIR MODER;        /*!< GPIO port mode register,                                  Address offset: 0x00 */
  __IO uint16_t OTYPER;       /*!< GPIO port output type register,                           Address offset: 0x04 */
  uint16_t RESERVED0;         /*!< Reserved,                                                                 0x06 */
  __IO uint32_t OSPEEDR;      /*!< GPIO port output speed register,                          Address offset: 0x08 */
  __IO uint32_t PUPDR;        /*!< GPIO port pull-up/pull-down register,                     Address offset: 0x0C */
  __IO M_bit16 IDR;              /*!< GPIO port input data register,                            Address offset: 0x10 */
  uint16_t RESERVED1;         /*!< Reserved,                                                                 0x12 */
  __IO M_bit16 ODR;          /*!< GPIO port output data register,                           Address offset: 0x14 */
  uint16_t RESERVED2;         /*!< Reserved,                                                                 0x16 */
  __IO M_bit32 BSRR;         /*!< GPIO port bit set/reset registerBSRR,                     Address offset: 0x18 */
  __IO M_bit32 LCKR;         /*!< GPIO port configuration lock register,                    Address offset: 0x1C */
  __IO uint32_t AFR[2];       /*!< GPIO alternate function low register,                Address offset: 0x20-0x24 */
  __IO M_bit16 BRR;          /*!< GPIO bit reset register,                                  Address offset: 0x28 */
  uint16_t RESERVED3;         /*!< Reserved,                                                                 0x2A */
}M_GPIO_TypeDef;




#define gIOA               ((M_GPIO_TypeDef *) GPIOA_BASE)
#define gIOB               ((M_GPIO_TypeDef *) GPIOB_BASE)
#define gIOC               ((M_GPIO_TypeDef *) GPIOC_BASE)
#define gIOD               ((M_GPIO_TypeDef *) GPIOD_BASE)
#define gIOE               ((M_GPIO_TypeDef *) GPIOE_BASE)
#define gIOF               ((M_GPIO_TypeDef *) GPIOF_BASE)

      
#endif
/*########################################################################################*/


