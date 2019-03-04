#include <xc.h>
#include "lcd.h"


#define FCY 40000000
#include <libpic30.h>

/* 
   For Explorer 16 board, here are the data and control signal definitions
   RS -> RB15
   E  -> RD4
   RW -> RD5
   DATA -> RE0 - RE7   
 */

// Control signal data pins 
#define  RW  LATDbits.LATD5       // LCD R/W signal
#define  RS  LATBbits.LATB15      // LCD RS signal
#define  E   LATDbits.LATD4       // LCD E signal 

// Control signal pin direction 
#define  RW_TRIS	TRISDbits.TRISD5 
#define  RS_TRIS	TRISBbits.TRISB15
#define  E_TRIS		TRISDbits.TRISD4

// Data signals and pin direction
#define  DATA      LATE           // Port for LCD data
#define  DATAPORT  PORTE
#define  TRISDATA  TRISE          // I/O setup for data Port

/****************************************************************************/

/*****	LCD SUBROUTINE  *****/

void lcd_cmd(char cmd) { // subroutiune for lcd commands
    TRISD &= 0xFFCF; // ensure RD0 - RD7 are outputs
    DATA &= 0xFF00; // prepare RD0 - RD7
    DATA |= cmd; // command byte to lcd
    RW = 0; // ensure RW is 0
    RS = 0;
    E = 1; // toggle E line
    Nop();
    Nop();
    Nop();
    Nop();
    E = 0;
    __delay_ms(5); // 5ms delay
}

void Init_LCD(void) { // initialize LCD display
    // 15mS delay after Vdd reaches nnVdc before proceeding with LCD initialization
    // not always required and is based on system Vdd rise rate
    __delay_ms(15); // 15ms delay

    /* set initial states for the data and control pins */
    LATE &= 0xFF00;
    RW = 0; // R/W state set low
    RS = 0; // RS state set low
    E = 0; // E state set low

    /* set data and control pins to outputs */
    TRISE &= 0xFF00;
    RW_TRIS = 0; // RW pin set as output
    RS_TRIS = 0; // RS pin set as output
    E_TRIS = 0; // E pin set as output

    /* 1st LCD initialization sequence */
    DATA &= 0xFF00;
    DATA |= 0x0038;
    E = 1;
    Nop();
    Nop();
    Nop();
    Nop();
    E = 0; // toggle E signal
    __delay_ms(5); // 5ms delay

    /* 2nd LCD initialization sequence */
    DATA &= 0xFF00;
    DATA |= 0x0038;
    E = 1;
    Nop();
    Nop();
    Nop();
    Nop();
    E = 0; // toggle E signal
    __delay_us(200); // 200uS delay

    /* 3rd LCD initialization sequence */
    DATA &= 0xFF00;
    DATA |= 0x0038;
    E = 1;
    Nop();
    Nop();
    Nop();
    Nop();
    E = 0; // toggle E signal
    __delay_us(200); // 200uS delay

    lcd_cmd(0x38); // function set
    lcd_cmd(0x0C); // Display on/off control, cursor blink off (0x0C)
    lcd_cmd(0x06); // entry mode set (0x06)
    lcd_cmd(0x01);
}

void LCD_Car(char c) {
    TRISD &= 0xFFCF; // ensure RD0 - RD7 are outputs
    RW = 0; // ensure RW is 0
    RS = 1; // assert register select to 1
    DATA &= 0xFF00; // prepare RD0 - RD7
    DATA |= c; // c byte to lcd
    E = 1;
    Nop();
    Nop();
    Nop();
    Nop();
    E = 0; // toggle E signal
    RS = 0; // negate register select to 0
    __delay_us(400); // 400uS delay
}

void LCD_Print(char *str) {
    while (*str != 0) {
        LCD_Car(*str);
        str++;
    }
}

void LCD_Pos(unsigned char c) {
    lcd_cmd(c | 0x80);
}

void LCD_Back(void) {
    lcd_cmd(0x10);
}

void LCD_Clr(void) {
    lcd_cmd(0x01);
}

void LCD_Line1(void) {
    lcd_cmd(0x02);
}

void LCD_Line2(void) {
    lcd_cmd(0xC0);
}

void LCD_Curs(unsigned char b) {
    lcd_cmd((b & 0x03) | 0x0C);
}

void LCD_Shift(unsigned char b) {
    if (b) lcd_cmd(0x1C);
    else lcd_cmd(0x18);
}

