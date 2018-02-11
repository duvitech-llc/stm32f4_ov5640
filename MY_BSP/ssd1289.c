/**
  ******************************************************************************
  * @file    ssd1289.c
  * @author  MCD Application Team
  * @version V1.2.2
  * @date    02-December-2014
  * @brief   This file includes the LCD driver for ILI9325 LCD.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "ssd1289.h"

/** @addtogroup BSP
  * @{
  */ 

/** @addtogroup Components
  * @{
  */ 
  
/** @addtogroup ssd1289
  * @brief     This file provides a set of functions needed to drive the 
  *            SSD1289 LCD.
  * @{
  */

/** @defgroup SSD1289_Private_TypesDefinitions
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup SSD1289_Private_Defines
  * @{
  */

//#define DISP_ORIENTATION					0
#define DISP_ORIENTATION					90
//#define DISP_ORIENTATION					180
//#define DISP_ORIENTATION					270

#if  ( DISP_ORIENTATION == 90 ) || ( DISP_ORIENTATION == 270 )

#define  MAX_X  320
#define  MAX_Y  240   

#elif  ( DISP_ORIENTATION == 0 ) || ( DISP_ORIENTATION == 180 )

#define  MAX_X  240
#define  MAX_Y  320   

#endif

/**
  * @}
  */ 
  
/** @defgroup SSD1289_Private_Macros
  * @{
  */
     
/**
  * @}
  */  

/** @defgroup SSD1289_Private_Variables
  * @{
  */ 
LCD_DrvTypeDef   ssd1289_drv = 
{
  ssd1289_Init,
  ssd1289_ReadID,
  ssd1289_DisplayOn,
  ssd1289_DisplayOff,
  ssd1289_SetCursor,
  ssd1289_WritePixel,
  ssd1289_ReadPixel,
  ssd1289_SetDisplayWindow,
  ssd1289_DrawHLine,
  ssd1289_DrawVLine,
  ssd1289_GetLcdPixelWidth,
  ssd1289_GetLcdPixelHeight,
  ssd1289_DrawBitmap,
  ssd1289_DrawRGBImage, 
  ssd1289_Clear,
};

static uint16_t ArrayRGB[320] = {0};
/**
  * @}
  */ 
  
/** @defgroup SSD1289_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */ 
  
/** @defgroup SSD1289_Private_Functions
  * @{
  */   
/********************************* LINK LCD ***********************************/

/**
  * @brief  Configures the LCD_SPI interface.
  * @retval None
  */
void LCD_IO_Init(void)
{
//  HAL_GPIO_WritePin(BL_PWM_GPIO_Port, BL_PWM_Pin, GPIO_PIN_SET);
//  HAL_GPIO_WritePin(LCD_RESET_GPIO_Port, LCD_RESET_Pin, GPIO_PIN_RESET);
//  HAL_Delay(100);
//  HAL_GPIO_WritePin(LCD_RESET_GPIO_Port, LCD_RESET_Pin, GPIO_PIN_SET);
//  HAL_Delay(300);

}

/**
  * @brief  Write register value.
  * @param  pData Pointer on the register value
  * @param  Size Size of byte to transmit to the register
  * @retval None
  */
void LCD_IO_WriteMultipleData(uint8_t *pData, uint32_t Size)
{
  uint32_t counter = 0;

  for (counter = Size; counter != 0; counter--)
  {
    /* Write 16-bit Data */
    LCD_RAM = *(uint16_t *)pData;
    counter--;
    pData += 2;
  }
}

/**
  * @brief  register address.
  * @param  Reg
  * @retval None
  */
void LCD_IO_WriteReg(uint8_t Reg) 
{
  /* Write 16-bit Data */
  LCD_REG  = (uint16_t)Reg;

}

/**
  * @brief  Read register value.
  * @param  Reg
  * @retval None
  */
uint16_t LCD_IO_ReadData(void) 
{
  /* Read 16-bit Reg */
  return (uint16_t)LCD_RAM;
  
}
/**
  * @brief  Initialize the SSD1289 LCD Component.
  * @param  None
  * @retval None
  */
void ssd1289_Init(void)
{  
  /* Initialize SSD1289 low level bus layer ----------------------------------*/
  LCD_IO_Init();
  
  /* Start Initial Sequence --------------------------------------------------*/
		    ssd1289_WriteReg(0x0000,0x0001);    HAL_Delay(50);   /* Enable LCD Oscillator */
	    ssd1289_WriteReg(0x0003,0xA8A4);    HAL_Delay(50);   
	    ssd1289_WriteReg(0x000C,0x0000);    HAL_Delay(50);   
	    ssd1289_WriteReg(0x000D,0x080C);    HAL_Delay(50);   
	    ssd1289_WriteReg(0x000E,0x2B00);    HAL_Delay(50);   
	    ssd1289_WriteReg(0x001E,0x00B0);    HAL_Delay(50);   
	    ssd1289_WriteReg(0x0001,0x2B3F);    HAL_Delay(50);   /* 320*240 0x2B3F */
	    ssd1289_WriteReg(0x0002,0x0600);    HAL_Delay(50);
	    ssd1289_WriteReg(0x0010,0x0000);    HAL_Delay(50);
	    ssd1289_WriteReg(0x0011,0x6070);    HAL_Delay(50);
	    ssd1289_WriteReg(0x0005,0x0000);    HAL_Delay(50);
	    ssd1289_WriteReg(0x0006,0x0000);    HAL_Delay(50);
	    ssd1289_WriteReg(0x0016,0xEF1C);    HAL_Delay(50);
	    ssd1289_WriteReg(0x0017,0x0003);    HAL_Delay(50);
	    ssd1289_WriteReg(0x0007,0x0133);    HAL_Delay(50);         
	    ssd1289_WriteReg(0x000B,0x0000);    HAL_Delay(50);
	    ssd1289_WriteReg(0x000F,0x0000);    HAL_Delay(50);
	    ssd1289_WriteReg(0x0041,0x0000);    HAL_Delay(50);
	    ssd1289_WriteReg(0x0042,0x0000);    HAL_Delay(50);
	    ssd1289_WriteReg(0x0048,0x0000);    HAL_Delay(50);
	    ssd1289_WriteReg(0x0049,0x013F);    HAL_Delay(50);
	    ssd1289_WriteReg(0x004A,0x0000);    HAL_Delay(50);
	    ssd1289_WriteReg(0x004B,0x0000);    HAL_Delay(50);
	    ssd1289_WriteReg(0x0044,0xEF00);    HAL_Delay(50);
	    ssd1289_WriteReg(0x0045,0x0000);    HAL_Delay(50);
	    ssd1289_WriteReg(0x0046,0x013F);    HAL_Delay(50);
	    ssd1289_WriteReg(0x0030,0x0707);    HAL_Delay(50);
	    ssd1289_WriteReg(0x0031,0x0204);    HAL_Delay(50);
	    ssd1289_WriteReg(0x0032,0x0204);    HAL_Delay(50);
	    ssd1289_WriteReg(0x0033,0x0502);    HAL_Delay(50);
	    ssd1289_WriteReg(0x0034,0x0507);    HAL_Delay(50);
	    ssd1289_WriteReg(0x0035,0x0204);    HAL_Delay(50);
	    ssd1289_WriteReg(0x0036,0x0204);    HAL_Delay(50);
	    ssd1289_WriteReg(0x0037,0x0502);    HAL_Delay(50);
	    ssd1289_WriteReg(0x003A,0x0302);    HAL_Delay(50);
	    ssd1289_WriteReg(0x003B,0x0302);    HAL_Delay(50);
	    ssd1289_WriteReg(0x0023,0x0000);    HAL_Delay(50);
	    ssd1289_WriteReg(0x0024,0x0000);    HAL_Delay(50);
	    ssd1289_WriteReg(0x0025,0x8000);    HAL_Delay(50);
	    ssd1289_WriteReg(0x004f,0);
	    ssd1289_WriteReg(0x004e,0);
	#if (DISP_ORIENTATION == 0)
		ssd1289_WriteReg(0x0011,0x6070);
	#elif (DISP_ORIENTATION == 90)
		ssd1289_WriteReg(0x0011,0x6058);
	#elif (DISP_ORIENTATION == 180)
		ssd1289_WriteReg(0x0011,0x6040);
	#elif (DISP_ORIENTATION == 270)
   ssd1289_WriteReg(0x0011,0x6068);
	#endif
  
}

/**
  * @brief  Enables the Display.
  * @param  None
  * @retval None
  */
void ssd1289_DisplayOn(void)
{
	
}

/**
  * @brief  Disables the Display.
  * @param  None
  * @retval None
  */
void ssd1289_DisplayOff(void)
{
	
}

/**
  * @brief  Get the LCD pixel Width.
  * @param  None
  * @retval The Lcd Pixel Width
  */
uint16_t ssd1289_GetLcdPixelWidth(void)
{
 return (uint16_t)320;
}

/**
  * @brief  Get the LCD pixel Height.
  * @param  None
  * @retval The Lcd Pixel Height
  */
uint16_t ssd1289_GetLcdPixelHeight(void)
{
 return (uint16_t)240;
}

/**
  * @brief  Get the SSD1289 ID.
  * @param  None
  * @retval The SSD1289 ID 
  */
uint16_t ssd1289_ReadID(void)
{
  LCD_IO_Init(); 
  return (ssd1289_ReadReg(0x00));
}

/**
  * @brief  Set Cursor position.
  * @param  Xpos: specifies the X position.
  * @param  Ypos: specifies the Y position.
  * @retval None
  */
void ssd1289_SetCursor(uint16_t Xpos, uint16_t Ypos)
{
  	uint16_t temp;	

	#if (DISP_ORIENTATION == 0)
		
	#elif (DISP_ORIENTATION == 90)
		temp = Xpos;
		Xpos = Ypos;
		Ypos = MAX_X - 1 - temp;				
	#elif (DISP_ORIENTATION == 180)
		Xpos = MAX_X - 1 - Xpos; 
		Ypos = MAX_Y - 1 - Ypos; 
	#elif (DISP_ORIENTATION == 270)
		temp = Ypos;
		Ypos = Xpos;
		Xpos = MAX_Y - 1 - temp;
	#endif


	ssd1289_WriteReg(0x004e, Xpos);      
  ssd1289_WriteReg(0x004f, Ypos);  
		
}

/**
  * @brief  Write pixel.   
  * @param  Xpos: specifies the X position.
  * @param  Ypos: specifies the Y position.
  * @param  RGBCode: the RGB pixel color
  * @retval None
  */
void ssd1289_WritePixel(uint16_t Xpos, uint16_t Ypos, uint16_t RGBCode)
{
  /* Set Cursor */
  ssd1289_SetCursor(Xpos, Ypos);
  
  /* Prepare to write GRAM */
	ssd1289_WriteReg(0x0022,RGBCode);
}

/**
  * @brief  Read pixel.
  * @param  None
  * @retval The RGB pixel color
  */
uint16_t ssd1289_ReadPixel(uint16_t Xpos, uint16_t Ypos)
{
  /* Set Cursor */
  ssd1289_SetCursor(Xpos, Ypos);
  
  /* Prepare to write GRAM */
  LCD_IO_WriteReg(LCD_REG_34);
  
  /* Dummy read */
  LCD_IO_ReadData();
  
  /* Read 16-bit Reg */
  return (LCD_IO_ReadData());
}

/**
  * @brief  Writes to the selected LCD register.
  * @param  LCDReg: Address of the selected register.
  * @param  LCDRegValue: Value to write to the selected register.
  * @retval None
  */
void ssd1289_WriteReg(uint8_t LCDReg, uint16_t LCDRegValue)
{
  LCD_IO_WriteReg(LCDReg);
  
  /* Write 16-bit GRAM Reg */
  LCD_IO_WriteMultipleData((uint8_t*)&LCDRegValue, 2);
}

/**
  * @brief  Reads the selected LCD Register.
  * @param  LCDReg: address of the selected register.
  * @retval LCD Register Value.
  */
uint16_t ssd1289_ReadReg(uint8_t LCDReg)
{
  /* Write 16-bit Index (then Read Reg) */
  LCD_IO_WriteReg(LCDReg);

  /* Read 16-bit Reg */
  return (LCD_IO_ReadData());
}

/**
  * @brief  Sets a display window
  * @param  Xpos:   specifies the X bottom left position.
  * @param  Ypos:   specifies the Y bottom left position.
  * @param  Height: display window height.
  * @param  Width:  display window width.
  * @retval None
  */
void ssd1289_SetDisplayWindow(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height)
{
  /* Horizontal GRAM Start Address */
  ssd1289_WriteReg(LCD_REG_80, (SSD1289_LCD_PIXEL_HEIGHT - Ypos - Height));
  /* Horizontal GRAM End Address */
  ssd1289_WriteReg(LCD_REG_81, (SSD1289_LCD_PIXEL_HEIGHT - Ypos - 1));
  
  /* Vertical GRAM Start Address */
  ssd1289_WriteReg(LCD_REG_82,  Xpos);
  /* Vertical GRAM End Address */
  ssd1289_WriteReg(LCD_REG_83, (Xpos + Width - 1));
  
}

/**
  * @brief  Draw vertical line.
  * @param  RGBCode: Specifies the RGB color   
  * @param  Xpos:     specifies the X position.
  * @param  Ypos:     specifies the Y position.
  * @param  Length:   specifies the Line length.  
  * @retval None
  */
void ssd1289_DrawHLine(uint16_t RGBCode, uint16_t Xpos, uint16_t Ypos, uint16_t Length)
{
  uint16_t counter = 0;
    
	ssd1289_WriteReg(0x0011,0x6030 | (0<<3)); // AM=0 hline
  
  /* Set Cursor */
  ssd1289_SetCursor(Xpos, Ypos); 
  
  /* Prepare to write GRAM */
  LCD_IO_WriteReg(LCD_REG_34);

  /* Sent a complete line */
  for(counter = 0; counter < Length; counter++)
  {
    ArrayRGB[counter] = RGBCode;
  }  

  LCD_IO_WriteMultipleData((uint8_t*)&ArrayRGB[0], Length * 2);
}

/**
  * @brief  Draw vertical line.
  * @param  RGBCode: Specifies the RGB color    
  * @param  Xpos:     specifies the X position.
  * @param  Ypos:     specifies the Y position.
  * @param  Length:   specifies the Line length.  
  * @retval None
  */
void ssd1289_DrawVLine(uint16_t RGBCode, uint16_t Xpos, uint16_t Ypos, uint16_t Length)
{
  uint16_t counter = 0;


	ssd1289_WriteReg(0x0011,0x6070 | (1<<3)); // AM=0 vline
  
  /* Set Cursor */
  ssd1289_SetCursor(Xpos, Ypos);
  
  /* Prepare to write GRAM */
  LCD_IO_WriteReg(LCD_REG_34);

  /* Fill a complete vertical line */
  for(counter = 0; counter < Length; counter++)
  {
    ArrayRGB[counter] = RGBCode;
  }
  
  /* Write 16-bit GRAM Reg */
  LCD_IO_WriteMultipleData((uint8_t*)&ArrayRGB[0], Length * 2);
  
}

/**
  * @brief  Displays a bitmap picture.
  * @param  BmpAddress: Bmp picture address.
  * @param  Xpos: Bmp X position in the LCD
  * @param  Ypos: Bmp Y position in the LCD    
  * @retval None
  */
void ssd1289_DrawBitmap(uint16_t Xpos, uint16_t Ypos, uint8_t *pbmp)
{
  uint32_t index = 0, size = 0;
  /* Read bitmap size */
  size = *(volatile uint16_t *) (pbmp + 2);
  size |= (*(volatile uint16_t *) (pbmp + 4)) << 16;
  /* Get bitmap data address offset */
  index = *(volatile uint16_t *) (pbmp + 10);
  index |= (*(volatile uint16_t *) (pbmp + 12)) << 16;
  size = (size - index)/2;
  pbmp += index;
	
  /* Set Cursor */
  ssd1289_SetCursor(Xpos, Ypos);  
  
  /* Prepare to write GRAM */
  LCD_IO_WriteReg(LCD_REG_34);
 
  LCD_IO_WriteMultipleData((uint8_t*)pbmp, size*2);
	
}

/**
  * @brief  Displays picture.
  * @param  pdata: picture address.
  * @param  Xpos: Image X position in the LCD
  * @param  Ypos: Image Y position in the LCD
  * @param  Xsize: Image X size in the LCD
  * @param  Ysize: Image Y size in the LCD
  * @retval None
  */
void ssd1289_DrawRGBImage(uint16_t Xpos, uint16_t Ypos, uint16_t Xsize, uint16_t Ysize, uint8_t *pdata)
{
  uint32_t size = 0;

  size = (Xsize * Ysize);

  /* Set Cursor */
  ssd1289_SetCursor(Xpos, Ypos);  
  
  /* Prepare to write GRAM */
  LCD_IO_WriteReg(LCD_REG_34);
 
  LCD_IO_WriteMultipleData((uint8_t*)pdata, size*2);
}

/**
  * @brief  Clears the hole LCD.
  * @param  Color: Color of the background
  * @retval None
  */
void ssd1289_Clear(uint16_t Color)
{
  uint32_t size = SSD1289_LCD_PIXEL_HEIGHT * SSD1289_LCD_PIXEL_WIDTH;
  
  /* Set Cursor */
  ssd1289_SetCursor(0, 0);  
  
  /* Prepare to write GRAM */
  LCD_IO_WriteReg(0x0022);
  
  while((size--) != 0)
  {
    /* Write 16-bit Data */
    LCD_RAM = Color;
  }
}

/**
  * @}
  */ 

/**
  * @}
  */ 
  
/**
  * @}
  */ 

/**
  * @}
  */
  
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
