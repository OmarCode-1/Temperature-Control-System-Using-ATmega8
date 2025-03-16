/*
 * LCD.h
 *
 * Created: 3/4/2025 1:01:07 PM
 *  Author: Omar Ibrahim
 */ 


#ifndef LCD_H_
#define LCD_H_

/*************************************************************************
 *                              Commands For LCD .                       *
 *************************************************************************/
#define CLEAR_LCD 0x01

#define RETURN_HOME 0x80


#define MOVE_CURSOR_LEFT_BY_ONE 0x04
#define MOVE_CURSOR_RIGHT_BY_ONE 0x06

#define SHEFT_DISPLAY_RIGHT 0x05
#define SHEFT_DISPLAY_LEFT 0x07

#define SHIFT_ENTIRE_LEFT 0x18
#define SHIFT_ENTIRE_RIGHT 0x1C
#define MOVE_CURSOR_1ST_ROW 0x80
#define MOVE_CURSOR_2ST_ROW 0xC0

#define DESPLAY_OFF_CURSOR_OFF 0x08
#define DESPLAY_ON_CURSOR_OFF 0x0C
#define DESPLAY_ON_CURSOR_BLINKING 0x0E

#define _8_BITS_1_LINE 0x30
#define _8_BITS_2_LINE 0x38
#define _4_BIT_MODE 0x02
#define _4_BITS_1_LINE 0x20
#define _4_BITS_2_LINE 0x28
/*************************************************************************** */
/**
 *                              Pins Used in LCD.                            *
 *****************************************************************************/
// #define LCD_PORT PORTB
// #define LCD_DDR DDRB



/*************************************************************************** */
/*****************************************************************************
 *                              Function Declartions                         *
 *****************************************************************************/
void init_lcd();
void lcd_write_character(unsigned char data);
void lcd_write_cmd(unsigned char command);
void lcd_set_cursor(unsigned char row, unsigned char col);
void lcd_write_string(const char *str);
void lcd_write_number(int number);
void uint16_to_string(uint16_t number, char *buffer);
void lcd_print_uint16(uint16_t number);
void lcd_clear();
#endif /* LCD_H_ */