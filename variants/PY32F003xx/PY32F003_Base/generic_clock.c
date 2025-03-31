/*
 *******************************************************************************
 * Copyright (c) 2023, AirM2M
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#if defined (PY32F003x4) || defined(PY32F003x6) || defined (PY32F003x8)
#include "pins_arduino.h"

/**
 * @brief  System Clock Configuration
 * @param  None
 * @retval None
 */
WEAK void SystemClock_Config(void)
{
    uint32_t tmp;
    uint32_t hsidiv;
    uint32_t hsifs;

    /* Get SYSCLK source -------------------------------------------------------*/
    switch (RCC->CFGR & RCC_CFGR_SWS)
    {
    case RCC_CFGR_SWS_0:  /* HSE used as system clock */
      SystemCoreClock = HSE_VALUE;
      break;

    case (RCC_CFGR_SWS_1 | RCC_CFGR_SWS_0):  /* LSI used as system clock */
      SystemCoreClock = LSI_VALUE;
      break;
  #if defined(RCC_LSE_SUPPORT)
    case RCC_CFGR_SWS_2:  /* LSE used as system clock */
      SystemCoreClock = LSE_VALUE;
      break;
  #endif /* RCC_LSE_SUPPORT */
  #if defined(RCC_PLL_SUPPORT)
    case RCC_CFGR_SWS_1:  /* PLL used as system clock */
      if ((RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC) == RCC_PLLCFGR_PLLSRC_HSI) /* HSI used as PLL clock source */
      {
        hsifs = ((READ_BIT(RCC->ICSCR, RCC_ICSCR_HSI_FS)) >> RCC_ICSCR_HSI_FS_Pos);
        SystemCoreClock = 2 * (HSIFreqTable[hsifs]);
      }
      else   /* HSE used as PLL clock source */
      {
        SystemCoreClock = 2 * HSE_VALUE;
      }
      break;
  #endif /* RCC_PLL_SUPPORT */
    case 0x00000000U:  /* HSI used as system clock */
    default:                /* HSI used as system clock */
      hsifs = ((READ_BIT(RCC->ICSCR, RCC_ICSCR_HSI_FS)) >> RCC_ICSCR_HSI_FS_Pos);
      hsidiv = (1UL << ((READ_BIT(RCC->CR, RCC_CR_HSIDIV)) >> RCC_CR_HSIDIV_Pos));
      SystemCoreClock = (HSIFreqTable[hsifs] / hsidiv);
      break;
    }
    /* Compute HCLK clock frequency --------------------------------------------*/
    /* Get HCLK prescaler */
    tmp = AHBPrescTable[((RCC->CFGR & RCC_CFGR_HPRE) >> RCC_CFGR_HPRE_Pos)];
    /* HCLK clock frequency */
    SystemCoreClock >>= tmp;
}

#endif /* ARDUINO_GENERIC_* */
