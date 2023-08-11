#ifndef OLED_H
#define	OLED_H

#include "oled_spi_hal.h"

// OLED REMAMP SET
#define SSD1351_RMP_INC_HOR         0x00
#define SSD1351_RMP_INC_VER         0x01
#define SSD1351_RMP_COLOR_NOR       0x00
#define SSD1351_RMP_COLOR_REV       0x02
#define SSD1351_RMP_SEQ_RGB         0x00
#define SSD1351_RMP_SEQ_BGR         0x04
#define SSD1351_RMP_SCAN_NOR        0x00
#define SSD1351_RMP_SCAN_REV        0x10
#define SSD1351_RMP_SPLIT_DISABLE   0x00
#define SSD1351_RMP_SPLIT_ENABLE    0x20
#define SSD1351_COLOR_65K           0x00
#define SSD1351_COLOR_262K          0x80

// SSD1355 Commands
#define SSD1351_SET_COL_ADDRESS    0x15
#define SSD1351_SET_ROW_ADDRESS    0x75
#define SSD1351_WRITE_RAM          0x5C
#define SSD1351_READ_RAM           0x5D
#define SSD1351_SET_REMAP          0xA0
#define SSD1351_SET_START_LINE     0xA1
#define SSD1351_SET_OFFSET         0xA2
#define SSD1351_MODE_OFF           0xA4
#define SSD1351_MODE_ON            0xA5
#define SSD1351_MODE_NORMAL        0xA6
#define SSD1351_MODE_INVERSE       0xA7
#define SSD1351_FUNCTION           0xAB
#define SSD1351_SLEEP_ON           0xAE
#define SSD1351_SLEEP_OFF          0xAF
#define SSD1351_MUX_RATIO          0xCA
#define SSD1351_COMMAND_LOCK       0xFD

// Device Properties
#define SSD1351_SCREEN_WIDTH       96
#define SSD1351_SCREEN_HEIGHT      96
#define SSD1351_ROW_OFF            0x00
#define SSD1351_COL_OFF            0x10  //collumn offset due to OLED display having only 96 visible pixels.

#define SSD1351_DEFAULT_MUX_RATIO      0x5f //95
#define SSD1351_DEFAULT_START_LINE     0x80 //128
#define SSD1351_DEFAULT_OFFSET         0x20 //32
//
#define SSD1351_DEFAULT_OLED_LOCK      0x12
#define SSD1351_DEFAULT_CMD_LOCK       0xB1

#define OLED_FONT_WIDTH   0x5
#define OLED_FONT_HEIGHT  0x8

#define RED     0xe962
#define GREEN   0x1762
#define BLUE    0x10dd
#define BLACK   0x0000

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */   

/*!
 *  @brief This API is the device initialization.
 */
void oledc_initialize(void);

/*!
 *  @brief This API displays the Microchip logo
 */
void oledc_print_curiosity_logo(void);

/*!
 *  @brief This API fills the screen with the selected color
 *
 *  @param[in] color : Color of the screen.
 */
void oledc_fill_screen(uint16_t color);

/*!
 *  @brief This API draws a character on the display.
 *
 *  @param[in] start_x : Start X coordinate
 *  @param[in] start_y : Start Y coordinate
 *  @param[in] sx : The multiplication order on the character on the X axis
 *  @param[in] sy : The multiplication order on the character on the Y axis
 *  @param[in] ch : Character to be displayed
 *  @param[in] color : Color of the text
 */
void oledc_draw_character(uint8_t x, uint8_t y, uint8_t sx, uint8_t sy, char ch, uint16_t color);

/*!
 *  @brief This API draws a character on a specified background color.
 *
 *  @param[in] start_x : Start X coordinate
 *  @param[in] start_y : Start Y coordinate
 *  @param[in] sx : The multiplication order on the character on the X axis
 *  @param[in] sy : The multiplication order on the character on the Y axis
 *  @param[in] ch : Character to be displayed
 *  @param[in] color : Color of the text
 *  @param[in] bg_color : Color of the background
 */
void oledc_draw_character_on_bg(uint8_t x, uint8_t y, uint8_t sx, uint8_t sy, char ch, uint16_t color, uint16_t bg_color);

/*!
 *  @brief This API draws a string on the display.
 *
 *  @param[in] start_x : Start X coordinate
 *  @param[in] start_y : Start Y coordinate
 *  @param[in] sx : The multiplication order on the character on the X axis
 *  @param[in] sy : The multiplication order on the character on the Y axis
 *  @param[in] *string : Pointer towards the string
 *  @param[in] color : Color of the text
 */
void oledc_draw_string(uint8_t x, uint8_t y, uint8_t sx, uint8_t sy, char* string, uint16_t color);

/*!
 *  @brief This API draws a string on a specified background.
 *
 *  @param[in] start_x : Start X coordinate
 *  @param[in] start_y : Start Y coordinate
 *  @param[in] sx : The multiplication order on the character on the X axis
 *  @param[in] sy : The multiplication order on the character on the Y axis
 *  @param[in] *string : Pointer towards the string
 *  @param[in] color : Color of the text
 *  @param[in] bg_color : Color of the background
 */
void oledc_draw_string_on_bg(uint8_t x, uint8_t y, uint8_t sx, uint8_t sy, char* string, uint16_t color, uint16_t bg_color);

/*!
 *  @brief This API draws a rectangle of the selected color.
 *
 *  @param[in] start_x : Start X coordinate
 *  @param[in] start_y : Start Y coordinate
 *  @param[in] end_x : End X coordinate
 *  @param[in] end_y : End Y coordinate
 *  @param[in] color : Color of the screen
 */
void oledc_draw_rectangle(uint8_t start_x, uint8_t start_y, uint8_t end_x, uint8_t end_y, uint16_t color);

/*!
 *  @brief This API draws an image.
 *  The image should be of RGB565 format.
 *
 *  @param[in] start_x : Start X coordinate
 *  @param[in] start_y : Start Y coordinate
 *  @param[in] end_x : End X coordinate
 *  @param[in] end_y : End Y coordinate
 *  @param[in] *img : Pointer towards the image
 */
void oledc_draw_image(uint8_t start_x, uint8_t start_y, uint8_t end_x, uint8_t end_y, const uint8_t *img);

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* OLED_H */