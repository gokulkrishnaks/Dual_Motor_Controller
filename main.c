/*
 * File:   main.c
 * Project: 
 * Author: 
 */

#include <xc.h>                    // Include XC compiler header for PIC microcontrollers
#define _XTAL_FREQ 20000000        // Define the crystal oscillator frequency as 20 MHz

//================ MOTOR PIN DEFINITIONS =================//
#define IN1 PORTBbits.RB3          // Motor driver input 1
#define IN2 PORTBbits.RB2          // Motor driver input 2
#define IN3 PORTBbits.RB1          // Motor driver input 3
#define IN4 PORTBbits.RB0          // Motor driver input 4

//================ LCD PIN DEFINITIONS =================//
#define LCDRS PORTBbits.RB4        // LCD Register Select pin (RS)
#define LCDEN PORTBbits.RB5        // LCD Enable pin (EN)

//================ BUTTON PIN DEFINITIONS =================//
#define BTN1 PORTBbits.RB6         // Push button 1 input
#define BTN2 PORTBbits.RB7         // Push button 2 input
#define REST PORTDbits.RD7         // Push button to reset the operation 

//================ FUNCTION PROTOTYPES =================//
void cmd(unsigned char cmd);       // Send command to LCD
void data(unsigned char data);     // Send data (character) to LCD
void print(const char *a);         // Print string on LCD
void init();                       // Initialize LCD

void pull();                       // Motor pull operation
void push();                       // Motor push operation
void stop();                       // Motor stop operation

void count();


//================ MAIN PROGRAM =================//
void main(void) {
    TRISB = 0xC0;                  /* Configure RB6 & RB7 (buttons) as INPUT (1), rest as OUTPUT (0) Binary: 11000000 -> RB7=1, RB6=1, others 0*/
    TRISC = 0x00;                  // Set all PORTC pins as OUTPUT (for LCD data lines)
    TRISD = 0x08;                  // Configure RD7 as INPUT for reset button
    PORTB = 0x00;                  // Clear PORTB output latch (initialize to 0)
    PORTC = 0x00;                  // Clear PORTC output latch (initialize to 0)
    PORTD = 0x00;
    

    init();                        // Initialize the LCD display
    __delay_ms(10);                // Small delay for LCD stabilization
    cmd(0x01);                     // Clear LCD display
    cmd(0x80);                     // Move cursor to first line, first position
    print("System Ready");         // Display "System On" on LCD

    //==== Infinite loop to continuously check button inputs ====//
    while (1) {
        if (REST == 1){
            cmd(0x01);                     // Clear LCD
            cmd(0x83);                     // Position cursor at line 1, column 3
            print("Reset");
            __delay_ms(500);               // Small delay for LCD stabilization
            cmd(0x01);                     // Clear LCD display
            cmd(0x80);                     // Move cursor to first line, first position
            print("System Ready"); 
            
        } 
        // Condition 1: BTN1 pressed, BTN2 not pressed -> Motor PULL mode
        if (BTN1 == 1 && BTN2 == 0) {
            pull();                // Run motor in pull direction
            cmd(0x01);             // Clear LCD
            cmd(0x83);             // Position cursor at line 1, column 3
            print("Motor");        // Display "Motor"
            cmd(0xC3);             // Move to line 2, column 3
            print("Pulling");      // Display "Pulling"
            count();               // Keep motor running for 10 seconds
            cmd(0x01);             // Clear LCD
            cmd(0x83);             // Position cursor at line 1, column 3
            print("Done..!");      // Display "Done..!"
            cmd(0x01);             // Clear LCD
            cmd(0x80);             // Move cursor to first line, first position
            print("System Ready"); // Display "System Ready"
        } 
        // Condition 2: BTN2 pressed, BTN1 not pressed -> Motor PUSH mode
        else if (BTN1 == 0 && BTN2 == 1) {
            push();                // Run motor in push direction
            cmd(0x01);             // Clear LCD
            cmd(0x83);             // Position cursor at line 1, column 3
            print("Motor");        // Display "Motor"
            cmd(0xC3);             // Move to line 2, column 3
            print("Pushing");      // Display "Pushing"
            count();               // Keep motor running for 10 seconds
            cmd(0x01);             // Clear LCD
            cmd(0x83);             // Position cursor at line 1, column 3
            print("Done..!");      // Display "Done..!"
            cmd(0x01);             // Clear LCD
            cmd(0x80);             // Move cursor to first line, first position
            print("System Ready"); // Display "System Ready"
        } 
        // Condition 3: No button pressed -> Stop motor
        else {
            stop();                // Stop all motor movements
        }
    }
}


//================ LCD COMMAND FUNCTION =================//
void cmd(unsigned char cmd) {
    LCDRS = 0;                     // RS = 0 ? command mode
    PORTC = cmd;                   // Send command to LCD data pins
    LCDEN = 1;                     // Set Enable high to latch command
    __delay_ms(2);                 // Short delay for LCD to process
    LCDEN = 0;                     // Set Enable low
    __delay_ms(2);                 // Additional delay to complete command execution
}


//================ LCD DATA FUNCTION =================//
void data(unsigned char data) {
    LCDRS = 1;                     // RS = 1 ? data mode
    PORTC = data;                  // Send character to LCD
    LCDEN = 1;                     // Enable high to latch data
    __delay_ms(2);                 // Short delay for LCD
    LCDEN = 0;                     // Enable low
    __delay_ms(2);                 // Allow LCD time to display character
}


//================ LCD PRINT FUNCTION =================//
void print(const char *str) {
    while (*str) {                 // Loop until string ends ('\0')
        data(*str++);              // Send each character to LCD
    }
}


//================ LCD INITIALIZATION FUNCTION =================//
void init() {
    __delay_ms(20);                // Wait for LCD power-up
    cmd(0x38);                     // Function set: 8-bit, 2-line, 5x7 dot matrix
    cmd(0x0C);                     // Display ON, cursor OFF
    cmd(0x06);                     // Entry mode set: Increment cursor automatically
    cmd(0x01);                     // Clear display
    __delay_ms(2);                 // Short delay for clear command
}


//================ MOTOR CONTROL FUNCTIONS =================//

// Push Function: Motor-1 will rotate clockwise 
//                Motor-2 will rotate anticlockwise
void push() {
    IN1 = 1;                       // Motor coil A1 = ON
    IN2 = 0;                       // Motor coil A2 = OFF
    IN3 = 0;                       // Motor coil B1 = OFF
    IN4 = 1;                       // Motor coil B2 = ON
}

// Pull Function: Motor-1 will rotate anticlockwise 
//                Motor-2 will rotate clockwise
void pull() {
    IN1 = 0;                       // Motor coil A1 = OFF
    IN2 = 1;                       // Motor coil A2 = ON
    IN3 = 1;                       // Motor coil B1 = ON
    IN4 = 0;                       // Motor coil B2 = OFF
}

// Stop Function: Turn off all motor outputs
void stop() {
    IN1 = 0;
    IN2 = 0;
    IN3 = 0;
    IN4 = 0;
}
// 7 segment 10 second counter
void count(){
    TRISD = 0x00;
    
    PORTD = 0x6F;       // 9
    __delay_ms(1000);
    PORTD = 0x7F;       // 8
    __delay_ms(1000);
    PORTD = 0x07;       // 7
    __delay_ms(1000);
    PORTD = 0x7D;       // 6
    __delay_ms(1000);
    PORTD = 0x6D;       // 5
    __delay_ms(1000);
    PORTD = 0x66;       // 4
    __delay_ms(1000);
    PORTD = 0x4F;       // 3
    __delay_ms(1000);
    PORTD = 0x5B;       // 2
    __delay_ms(1000);
    PORTD = 0x06;       // 1
    __delay_ms(1000);
    PORTD = 0x3F;       // 0
    __delay_ms(1000);
    TRISD = 0x08;
}


