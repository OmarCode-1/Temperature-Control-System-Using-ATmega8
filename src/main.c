/*
 * Atmega_8_Project.c
 *
 * Created: 3/4/2025 12:54:59 PM
 * Author : Omar Ibrahim
 */ 

#include <avr/io.h>
#include "config.h"
#include "LCD.h"
#include "GPIO.h"
#include "Mux.h"
#include "ADC_driver.h"

void init_mux_pins();
void set_state_lcd(unsigned char old_value, uint16_t new_value, char* fan_statues, char* heater_statues);
int temp_input_value = 0;
uint16_t temp_sensor = 0;

int main(void)
{   
    
    init_mux_pins();
    init_lcd();
    initADC();

    MY_SB(DDRB, 3); // FAN .
    MY_SB(DDRD, 3); // HEATER .

    MY_CB(DDRD, 4); // submit degree .

    while (1) 
    {
        temp_sensor = readADC(0);
        temp_sensor = (temp_sensor * 500) / 1023;

        if(MY_BV(PIND, 4))
        {
            temp_input_value = readMux();
            lcd_clear();
            lcd_set_cursor(0, 1);
            lcd_write_string("New Temp Value");
            lcd_set_cursor(1, 2);
            lcd_write_string("Value : ");
            lcd_write_number(temp_input_value);
            _delay_ms(250);
            lcd_clear();
        }

        if(temp_input_value <= temp_sensor)
        {
            MY_CB(PORTD, 3);
            MY_SB(PORTB, 3);
            set_state_lcd(temp_input_value, temp_sensor, "ON", "OFF");
        }else
        {
            MY_CB(PORTB, 3);
            MY_SB(PORTD, 3);
            set_state_lcd(temp_input_value, temp_sensor, "OFF", "ON");
        }
        
        _delay_ms(1000);
    }
}

void init_mux_pins()
{
    MY_SB(DDRD, 0);
    MY_SB(DDRD, 1);
    MY_SB(DDRD, 2);
    MY_CB(DDRB, 2);
}

void set_state_lcd(unsigned char old_value, uint16_t new_value, char* fan_statues, char* heater_statues)
{
    lcd_clear();
    lcd_write_string("E-T: ");
    lcd_write_number(old_value);
    lcd_write_string(" N-T: ");
    lcd_print_uint16(new_value);
    lcd_set_cursor(1, 0);
    lcd_write_string("Fan: ");
    lcd_write_string(fan_statues);
    lcd_write_string("Heat: ");
    lcd_write_string(heater_statues);

} 