/*
 *   Basic OLEDC SSD1351 display driver
 */
#include "oled_spi_hal.h"
#include "oled.h"
#include "logo.h"
#include "fonts.h"

static uint8_t SSD1351_DEFAULT_REMAP = SSD1351_RMP_INC_HOR | SSD1351_RMP_COLOR_REV |
                                        SSD1351_RMP_SEQ_RGB | SSD1351_RMP_SCAN_REV |
                                        SSD1351_RMP_SPLIT_ENABLE | SSD1351_COLOR_65K;

static void oledc_send_byte(uint8_t temp)
{
    OLED_spi_byteWrite(temp);
}

static void oledc_set_dc_send_data_byte(uint8_t temp)
{
    OLED_dc_high();
    OLED_delay_ms(1);
    OLED_spi_byteWrite(temp);
    OLED_dc_low();
}

static void oledc_set_dc_send_data(uint8_t *temp, size_t len)
{
    OLED_dc_high();
    OLED_delay_ms(1);
    OLED_spi_Write(temp, len);
    OLED_dc_low();
}

static void oledc_send_bulk(uint8_t *temp, size_t len)
{
    // This functions sends a bulk of data through SPI
    // If DC is set to high before calling it, it will be considered DATA information.
    OLED_spi_Write(temp, len);
}

static void oledc_set_command(void)
{
    OLED_cs_low();
    OLED_delay_ms(1); // Give enough time for the pin to go to LOW before using SPI
}

static void oledc_set_data(void)
{
    OLED_dc_high();
}

static void oledc_clear_command(void)
{
    while (OLED_spi_is_transmitter_busy()) ; 
    OLED_cs_high();
}

static void oledc_clear_data(void)
{   
    while (OLED_spi_is_transmitter_busy()) ;
    OLED_dc_low();
}

/* --------------------------------------------------------- PUBLIC FUNCTIONS */
void oledc_initialize( void)
{
    OLED_comm_open();
    OLED_rw_low();
    OLED_enable_high();
    OLED_reset_high();
    OLED_delay_ms(1);
    OLED_reset_low();
    OLED_delay_ms(10);
    OLED_reset_high();
    OLED_delay_ms(200);
    OLED_dc_low();

    oledc_set_command();
    oledc_send_byte(SSD1351_COMMAND_LOCK);
    oledc_set_dc_send_data_byte(SSD1351_DEFAULT_OLED_LOCK);
    oledc_send_byte(SSD1351_COMMAND_LOCK);
    oledc_set_dc_send_data_byte(SSD1351_DEFAULT_CMD_LOCK);    
    oledc_send_byte(SSD1351_SLEEP_ON);

    oledc_send_byte(SSD1351_SET_REMAP);
    oledc_set_dc_send_data_byte(SSD1351_DEFAULT_REMAP);    
    oledc_send_byte(SSD1351_MUX_RATIO);
    oledc_set_dc_send_data_byte(SSD1351_DEFAULT_MUX_RATIO);
    oledc_send_byte(SSD1351_SET_START_LINE);
    oledc_set_dc_send_data_byte(SSD1351_DEFAULT_START_LINE);
    oledc_send_byte(SSD1351_SET_OFFSET);
    oledc_set_dc_send_data_byte(SSD1351_DEFAULT_OFFSET);

    oledc_send_byte(SSD1351_MODE_NORMAL);
    oledc_send_byte(SSD1351_SLEEP_OFF);
    oledc_clear_command();

    oledc_print_curiosity_logo();
    OLED_delay_ms(1000);
    oledc_fill_screen(0x0000);
}

void oledc_print_curiosity_logo(void)
{
    oledc_draw_image(0, 0, 95, 95, curiosity_logo_color);
}

void oledc_fill_screen(uint16_t color)
{
    oledc_draw_rectangle(0, 0, 95, 95, color);
}

void oledc_draw_character(uint8_t x, uint8_t y, uint8_t sx, uint8_t sy, char ch, uint16_t color) 
{
    const uint8_t *f = &font[(ch - ' ') * OLED_FONT_WIDTH];
    uint8_t i_x, i_y, j_x, j_y;
    uint8_t cols[2], rows[2], clr[2] = {0};

    clr[0] |= color >> 8;
    clr[1] |= color & 0x00FF;

    for (i_x = 0; i_x < OLED_FONT_WIDTH * sx; i_x += sx) 
    { // For each COLUMN of our text
        uint8_t curr_char_byte = *f++;
        for (i_y = 0; i_y < OLED_FONT_HEIGHT * sy; i_y += sy) 
        {
            if (curr_char_byte & 0x01) 
            {
                cols[0] = SSD1351_COL_OFF + x + i_x;
                cols[1] = SSD1351_COL_OFF + x + i_x + sx - 1;
                rows[0] = SSD1351_ROW_OFF + y + i_y;
                rows[1] = SSD1351_ROW_OFF + y + i_y + sy - 1;

                oledc_send_byte(SSD1351_SET_COL_ADDRESS);
                oledc_set_dc_send_data(cols, 2);
                oledc_send_byte(SSD1351_SET_ROW_ADDRESS);
                oledc_set_dc_send_data(rows, 2);
                
                oledc_send_byte(SSD1351_WRITE_RAM);
                oledc_set_data();
                for (j_x = x + i_x; j_x < x + i_x + sx; j_x++) 
                {
                    for (j_y = y + i_y; j_y < y + i_y + sy; j_y++)
                    {
                        oledc_send_bulk(clr, 2);
                    }
                }
                oledc_clear_data();
            }
            curr_char_byte >>= 1;
        }
    }
}

void oledc_draw_character_on_bg(uint8_t x, uint8_t y, uint8_t sx, uint8_t sy, char ch, uint16_t color, uint16_t bg_color) 
{
    const uint8_t *f = &font[(ch - ' ') * OLED_FONT_WIDTH];
    uint8_t i_x, i_y, j_x, j_y;
    uint8_t cols[2], rows[2], clr[2] = {0}, bg_clr[2] = {0};

    clr[0] |= color >> 8;
    clr[1] |= color & 0x00FF;
    bg_clr[0] |= bg_color >> 8;
    bg_clr[1] |= bg_color & 0x00FF;

    for (i_x = 0; i_x < OLED_FONT_WIDTH * sx; i_x += sx) 
    { // For each COLUMN of our text
        uint8_t curr_char_byte = *f++;
        cols[0] = SSD1351_COL_OFF + x + i_x;
        cols[1] = SSD1351_COL_OFF + x + i_x + sx - 1;
        rows[0] = SSD1351_ROW_OFF + y;
        rows[1] = SSD1351_ROW_OFF + y + OLED_FONT_HEIGHT * sy - 1;
        oledc_send_byte(SSD1351_SET_COL_ADDRESS);
        oledc_set_dc_send_data(cols, 2);
        oledc_send_byte(SSD1351_SET_ROW_ADDRESS);
        oledc_set_dc_send_data(rows, 2);

        oledc_send_byte(SSD1351_WRITE_RAM);
        oledc_set_data();
        for (i_y = 0; i_y < OLED_FONT_HEIGHT * sy; i_y += sy) 
        {
            if (curr_char_byte & 0x01) 
            {
                for (j_x = x + i_x; j_x < x + i_x + sx; j_x++) 
                {
                    for (j_y = y + i_y; j_y < y + i_y + sy; j_y++)
                    {
                        oledc_send_bulk(clr, 2);
                    }
                }
            }
            else 
            {
                for (j_x = x + i_x; j_x < x + i_x + sx; j_x++) 
                {
                    for (j_y = y + i_y; j_y < y + i_y + sy; j_y++)
                    {
                        oledc_send_bulk(bg_clr, 2);
                    }
                }
            }
            curr_char_byte >>= 1;
        }
        oledc_clear_data();
    }
}

void oledc_draw_string(uint8_t x, uint8_t y, uint8_t sx, uint8_t sy, char *string, uint16_t color)
{
    oledc_set_command();
    while (*string) {
        oledc_draw_character(x, y, sx, sy, *string++, color);
        x += OLED_FONT_WIDTH * sx + 1;
    }
    oledc_clear_command();
}

void oledc_draw_string_on_bg(uint8_t x, uint8_t y, uint8_t sx, uint8_t sy, char *string, uint16_t color, uint16_t bg_color)
{
    oledc_set_command();
    while (*string) {
        oledc_draw_character_on_bg(x, y, sx, sy, *string++, color, bg_color);
        x += OLED_FONT_WIDTH * sx + 1;
    }
    oledc_clear_command();
}

void oledc_draw_rectangle(uint8_t start_x, uint8_t start_y, uint8_t end_x, uint8_t end_y, uint16_t color)
{
    uint8_t cols[2], rows[2], clr[2] = {0};
    uint8_t x, y;

    start_x = start_x > 95 ? 95 : start_x;
    end_x = end_x > 95 ? 95 : end_x;
    start_y = start_y > 95 ? 95 : start_y;
    end_y = end_y > 95 ? 95 : end_y;
    if((end_x < start_x) || (end_y < start_y))
        return;

    cols[0] = SSD1351_COL_OFF + start_x;
    cols[1] = SSD1351_COL_OFF + end_x;
    rows[0] = SSD1351_ROW_OFF + start_y;
    rows[1] = SSD1351_ROW_OFF + end_y;
    clr[0] |= color >> 8;
    clr[1] |= color & 0x00FF;

    oledc_set_command();
    oledc_send_byte(SSD1351_SET_COL_ADDRESS);
    oledc_set_dc_send_data(cols, 2);
    oledc_send_byte(SSD1351_SET_ROW_ADDRESS);
    oledc_set_dc_send_data(rows, 2);
    oledc_send_byte(SSD1351_WRITE_RAM);
    oledc_set_data();

    for (x = start_x; x < end_x + 1; x++) 
    {
        for (y = start_y; y < end_y + 1; y++)
        {
            oledc_send_bulk(clr, 2);
        }
    }
    oledc_clear_data();
    oledc_clear_command();
}

void oledc_draw_image(uint8_t start_x, uint8_t start_y, uint8_t end_x, uint8_t end_y, const uint8_t *img)
{
    uint8_t cols[2],rows[2];
    uint16_t pos = 0;
    uint16_t pixels_total = (end_x - start_x + 1) * (end_y - start_y + 1);
    
    start_x = start_x > 95 ? 95 : start_x;
    end_x = end_x > 95 ? 95 : end_x;
    start_y = start_y > 95 ? 95 : start_y;
    end_y = end_y > 95 ? 95 : end_y;

    if((end_x < start_x) || (end_y < start_y))
        return;
    
    cols[0] = SSD1351_COL_OFF + start_x;
    cols[1] = SSD1351_COL_OFF + end_x;
    rows[0] = SSD1351_ROW_OFF + start_y;
    rows[1] = SSD1351_ROW_OFF + end_y;
    
    oledc_set_command();
    oledc_send_byte(SSD1351_SET_COL_ADDRESS);
    oledc_set_dc_send_data(cols, 2);
    oledc_send_byte(SSD1351_SET_ROW_ADDRESS);
    oledc_set_dc_send_data(rows, 2);
    oledc_send_byte(SSD1351_WRITE_RAM);
    oledc_set_data();
    
    while(pixels_total--)
    {
        oledc_send_byte(img[pos + 1]);
        oledc_send_byte(img[pos]);
        pos += 2;
    }
    oledc_clear_data();
    oledc_clear_command();
}