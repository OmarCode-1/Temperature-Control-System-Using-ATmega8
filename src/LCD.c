
#include <avr/io.h>
#include <stdlib.h>
#include "LCD.h"
#include "GPIO.h"
#include "config.h"

#define RS 0
#define EN 1
#define D0 4
#define D1 5
#define D2 6
#define D3 7

volatile unsigned char *LCD_DDR = &DDRB;
volatile unsigned char *LCD_PORT = &PORTB;

void init_lcd()
{
    _delay_ms(25);
    (*LCD_DDR) |= (1 << EN) | (1 << RS) | (1 << D0) | (1 << D1) | (1 << D2) | (1 << D3);
    lcd_write_cmd(_4_BIT_MODE);
    lcd_write_cmd(_4_BITS_2_LINE);
    lcd_write_cmd(DESPLAY_ON_CURSOR_OFF);
    lcd_write_cmd(MOVE_CURSOR_RIGHT_BY_ONE);
    lcd_write_cmd(CLEAR_LCD);
    lcd_write_cmd(RETURN_HOME);
}

void lcd_write_character(unsigned char data)
{
    *LCD_PORT = ((*LCD_PORT) & 0x0F) | (data & 0xF0);
    MY_SB(*LCD_PORT, RS);
    MY_SB(*LCD_PORT, EN);
    _delay_ms(1);
    MY_CB(*LCD_PORT, EN);
    _delay_ms(2);

    *LCD_PORT = ((*LCD_PORT) & 0x0F) | (data << 4);
    MY_SB(*LCD_PORT, EN);
    _delay_ms(1);
    MY_CB(*LCD_PORT, EN);
    _delay_ms(2);
}
void lcd_write_cmd(unsigned char command)
{
    *LCD_PORT = ((*LCD_PORT) & 0x0F) | (command & 0xF0);
    MY_CB(*LCD_PORT, RS);
    MY_SB(*LCD_PORT, EN);
    _delay_ms(1);
    MY_CB(*LCD_PORT, EN);
    _delay_ms(2);

    *LCD_PORT = ((*LCD_PORT) & 0x0F) | (command << 4);
    MY_SB(*LCD_PORT, EN);
    _delay_ms(1);
    MY_CB(*LCD_PORT, EN);
    _delay_ms(2);
}


void lcd_set_cursor(unsigned char row, unsigned char col) {
    unsigned char address;
    if (row == 0) {
        address = 0x80 + col; 
    } else {
        address = 0xC0 + col; 
    }
    lcd_write_cmd(address); 
}


void lcd_write_string(const char *str) {
    while (*str) {
        lcd_write_character(*str++); 
    }
}
void lcd_write_number(int number) {
    char buffer[16]; 
    itoa(number, buffer, 10); 
    lcd_write_string(buffer);
}

void lcd_clear()
{
    lcd_write_cmd(CLEAR_LCD);
}


void uint16_to_string(uint16_t number, char *buffer) {
    int i = 0;

    if (number == 0) {
        buffer[i++] = '0';
    }

    while (number > 0) {
        buffer[i++] = (number % 10) + '0'; 
        number /= 10;
    }

    int j = 0;
    char temp;
    for (j = 0; j < i / 2; j++) {
        temp = buffer[j];
        buffer[j] = buffer[i - j - 1];
        buffer[i - j - 1] = temp;
    }

    buffer[i] = '\0';
}

void lcd_print_uint16(uint16_t number) {
    char buffer[6]; 
    uint16_to_string(number, buffer); 
    lcd_write_string(buffer); 
}