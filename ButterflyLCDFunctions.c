/*
 *  University Of Canterbury - Department of Electrical and Computer Engineering
 *
 *  ENEL323 - Software Engineering 1
 *  Assignment 2: Atmel AVR Butterfly LCD Control Library
 *  File: ButterflyLCDFunctions.c
 *
 *  Implements the functions detailed in ButterflyLCDFunctions.h
 *
 *  Blair Bonnett (bcb22) and Oliver Krenek (ofk10)
 *  Last Updated: 12 July 2006
 *
 */

#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include "ButterflyLCDFunctions.h"

// First LCD register (LCDDR0)
#define FirstLCDRegister ((unsigned char *)(0xEC))

// Global variables
static int LCD_currentStates[6];            // 0 = character off, 1 = character on
static char LCD_currentChars[6];            // Holds the characters at each point on the display
static int LCD_currentString;               // The current string (1 or 2)
static int LCD_stringPosition;              // What character of the current string is at the LH edge of the LCD
static char *LCD_stringOne;                 // Pointer to the first string
static char *LCD_stringTwo;                 // Pointer to the second string

// Internal functions
void LCD_character(int position);
void LCD_blank(int position);
unsigned int LCD_segmentPattern(char character);

// Initialises display
void LCD_initDisplay(void){
    // Use external asychronous clock (32.768kHz), 1/3 bias, 1/4 duty, 4 common pins, 25 segments max
    LCDCRB = 0xB7; // 10110111

    // LCD Prescaler = 16, LCD Clock Divide = 8 ==> frame rate = 32Hz
    LCDFRR = 0x07; // 00000111

    // LCD enabled, low power waveform, start-of-frame interrupt disabled
    LCDCRA = 0xC0; // 11000000

    // All positions on at start, and all characters blank
    for(int i = 0; i < 6; i++){
        LCD_currentStates[i] = 1;
        LCD_currentChars[i] = ' ';
    }

    // Initialise other variables
    LCD_currentString = 0;
    LCD_stringPosition = 0;
}

// Shows a character at a given position
void LCD_showCharacter(int position, char character){
    // Only continue if position is legal
    if ((position < 0) || (position > 5)) return;

    // Store character
    LCD_currentChars[position] = character;

    // Only continue if this position is displayed
    if(LCD_currentStates[position] == 1) LCD_character(position);
}

// Toggles the visibility of a particular position
int LCD_togglePosition(int position){
    // Only continue if position is legal
    if ((position < 0) || (position > 5)) return -1;

    // If off, turn on and return 1
    if(LCD_currentStates[position] == 0){
        LCD_currentStates[position] = 1;
        LCD_character(position);
        return 1;
    }
    
    // Turn off and return 0
    LCD_currentStates[position] = 0;
    LCD_blank(position);
    return 0;
}

// Loads and displays a string
void LCD_showString(char *string){
    // Clear any previously saved string
    if(LCD_stringOne != NULL){
        free(LCD_stringOne);
        LCD_stringOne = NULL;
    }

    // See if we have enough room for this string
    LCD_stringOne = (char *)malloc(strlen(string + 1) * sizeof(char));
    if(LCD_stringOne == NULL) return;

    // Save a copy of the string
    strcpy(LCD_stringOne, string);
    LCD_currentString = 1;
    LCD_stringPosition = 0;

    // Show the string
    int loopCount;
    for(loopCount = 0; (loopCount < 6) && (LCD_stringOne[loopCount] != '\0'); loopCount++){
        LCD_currentChars[loopCount] = LCD_stringOne[loopCount];
        LCD_character(loopCount);
    }

    // Blank out any remaining characters
    for(; loopCount < 6; loopCount++){
        LCD_currentChars[loopCount] = ' ';
        LCD_blank(loopCount);
    }
}

// Loads two strings and displays the first
void LCD_loadTwoStrings(char *string1, char *string2){
    // Clear any previously saved strings
    if(LCD_stringTwo != NULL){
        free(LCD_stringTwo);
        LCD_stringTwo = NULL;
    }
    if(LCD_stringOne != NULL){
        free(LCD_stringOne);
        LCD_stringOne = NULL;
    }


    // See if we have enough room for the strings
    LCD_stringOne = (char *)malloc(strlen(string1 + 1) * sizeof(char));
    if(LCD_stringOne == NULL) return;
    LCD_stringTwo = (char *)malloc(strlen(string2 + 1) * sizeof(char));
    if(LCD_stringTwo == NULL){
        free(LCD_stringOne);
        return;
    }

    // Save a copy of the strings
    strcpy(LCD_stringOne, string1);
    strcpy(LCD_stringTwo, string2);
    LCD_currentString = 1;
    LCD_stringPosition = 0;

    // Show the first string
    int loopCount;
    for(loopCount = 0; (loopCount < 6) && (LCD_stringOne[loopCount] != '\0'); loopCount++){
        LCD_currentChars[loopCount] = LCD_stringOne[loopCount];
        LCD_character(loopCount);
    }

    // Blank out any remaining characters
    for(; loopCount < 6; loopCount++){
        LCD_currentChars[loopCount] = ' ';
        LCD_blank(loopCount);
    }
}

// Switches display between two loaded strings
int LCD_switchStrings(void){
    // Only continue if both strings have been loaded
    if((LCD_stringOne == NULL) || (LCD_stringTwo == NULL)) return -1;
    
    char *currentString;
    int loopCount;

    LCD_stringPosition = 0;
    if(LCD_currentString == 1){
        LCD_currentString = 2;
        currentString = LCD_stringTwo;
    }
    else{
        LCD_currentString = 1;
        currentString = LCD_stringOne;
    }
    
    // Show the string
    for(loopCount = 0; (loopCount < 6) && (currentString[loopCount] != '\0'); loopCount++){
        LCD_currentChars[loopCount] = currentString[loopCount];
        LCD_character(loopCount);
    }

    // Blank out any remaining characters
    for(; loopCount < 6; loopCount++){
        LCD_currentChars[loopCount] = ' ';
        LCD_blank(loopCount);
    }

    return LCD_currentString;
}

// Scrolls the display in a given direction
void LCD_scrollDisplay(int direction, int wrap){
    // Only continue for valid directions
    if((direction != LCDScrollLeft) && (direction != LCDScrollRight)) return;

    int loopCount, newChar;

    // Shift the five characters that will remain on screen in all cases
    if(direction == LCDScrollLeft){
        newChar = 5;
        for(loopCount = 0; loopCount < 5; loopCount++){
            LCD_currentChars[loopCount] = LCD_currentChars[loopCount + 1];
            LCD_character(loopCount);
        }
    }
    else{
        newChar = 0;
        for(loopCount = 5; loopCount > 0; loopCount--){
            LCD_currentChars[loopCount] = LCD_currentChars[loopCount - 1];
            LCD_character(loopCount);
        }
    }

    // If no strings loaded, insert blank character and return
    if((LCD_stringOne == NULL) && (LCD_stringTwo == NULL)){
        LCD_currentChars[newChar] = ' ';
        LCD_blank(newChar);
        return;
    }

    // Get the current string and its length
    char *currentString = (LCD_currentString == 2) ? LCD_stringTwo : LCD_stringOne;
    int currentLength = strlen(currentString);

    if (direction == LCDScrollLeft){
        // Increase string position marker
        LCD_stringPosition++;

        // If the RH edge is still within the string, just show the next character
        if(LCD_stringPosition + 5 < currentLength){
            LCD_currentChars[5] = currentString[LCD_stringPosition + 5];
            LCD_character(5);
        }
        else{
            // If not wrapping, or within the 3 blank chars before wrapping
            if((wrap == 0) || (LCD_stringPosition + 2 < currentLength)){
                LCD_currentChars[5] = ' ';
                LCD_blank(5);
            }
            else{
                // Wrap back the start of the string again
                LCD_currentChars[5] = currentString[LCD_stringPosition + 2 - currentLength];
                LCD_character(5);

                // If we are back to the start of the string, reset the position marker
                if(LCD_stringPosition - 3 == currentLength) LCD_stringPosition = 0;
            }
        }
    }

    else{
        // Decrease string position marker
        LCD_stringPosition--;

        // If LH edge still within string, just show the next character
        if(LCD_stringPosition >= 0){
            LCD_currentChars[0] = currentString[LCD_stringPosition];
            LCD_character(0);
        }
        else{
            // If not wrapping, or within the 3 blank chars before wrapping
            if((wrap == 0) || (LCD_stringPosition > -3)){
                LCD_currentChars[0] = ' ';
                LCD_blank(0);
            }
            else{
                // Wrap back to the start of the string again
                LCD_currentChars[0] = currentString[LCD_stringPosition + currentLength + 3];
                LCD_character(0);

                // If we are back to the start of the string, reset the string position marker
                if(-LCD_stringPosition - 3 == currentLength) LCD_stringPosition = 0;
            }
        }
    }
}

// Changes the contrast of the display
void LCD_changeContrast(int contrast){
    // Only continue for valid inputs
    if((contrast < 0) || (contrast > 15)) return;

    // Update the contrast control register
    LCDCCR = 0x0F & contrast;
}

// Clears the display and resets variables
void LCD_clearDisplay(void){
    // Clear the states, characters and display
    for(int loopCount = 0; loopCount < 6; loopCount++){
        LCD_currentStates[loopCount] = 1;
        LCD_currentChars[loopCount] = ' ';
        LCD_blank(loopCount);
    }

    // Free memory reserved for strings
    if(LCD_stringTwo != NULL){
        free(LCD_stringTwo);
        LCD_stringTwo = NULL;
    }
    if(LCD_stringOne != NULL){
        free(LCD_stringOne);
        LCD_stringOne = NULL;
    }

    // Reset other variables
    LCD_currentString = 0;
    LCD_stringPosition = 0;  
}

/*
Internal function: Outputs the character at the given position.
*/
void LCD_character(int position){
    char character;             // Character at this position
    unsigned int seg = 0x0000;  // Holds the segment pattern for the character
    char *currentRegister;      // The LCD control register to be written to next
    char mask;                  // Used so we only write to the correct half of the register
    char registerValue;         // The value to write into the LCD control register
    int i;

    // Only continue if position is legal and not hidden
    if ((position < 0) || (position > 5)) return;
    if(LCD_currentStates[position] == 0) return;

    //Lookup character table for segment data
    character = LCD_currentChars[position];

    // If it is a space, use the blank function
    if(character == ' '){
        LCD_blank(position);
        return;
    }

    // Convert character to uppercase if neccessary
    if ((character >= 'a') && (character <= 'z')) character &= ~0x20;

    // Get segment pattern
    seg = LCD_segmentPattern(character);

    // Adjust mask according to LCD segment mapping
    if (position & 0x01) mask = 0x0F;        // Digit 1, 3, 5 are LH half of register ==> keep RH intact
    else mask = 0xF0;                        // Digit 0, 2, 4 are RH half of register ==> keep LH intact

    // The lowest memory value register for this position
    // (position >> 1) = {0, 0, 1, 1, 2, 2)
    currentRegister = FirstLCDRegister + (position >> 1);

    // Four different registers need to be written for a character
    for(i = 0; i < 4; i++){
        // Get lowest 4 bits of pattern  
        registerValue = seg & 0x000F;
        
        // If left-hand part of register, shift pattern to correct position
        if (position & 0x01) registerValue <<= 4;

        // Write the data, using the mask to keep existing data in other half the same
        *currentRegister = (*currentRegister & mask) | registerValue;
        
        // Move to next 4 bits of pattern and next highest register
        seg >>= 4;
        currentRegister += 5;
    }
}

/*
Internal function: Blanks the character at the given position.
*/
void LCD_blank(int position){
    char *currentRegister;      // The LCD control register to be written to next
    char mask;                  // Used so we only write to the correct half of the register
    int i;

    // Only continue if position is legal
    if ((position < 0) || (position > 5)) return;

    // Adjust mask according to LCD segment mapping
    if (position & 0x01)
        mask = 0x0F;        // Digit 1, 3, 5 are left-hand half of register
    else
        mask = 0xF0;        // Digit 0, 2, 4 are right-hand half of register

    // The lowest memory value register for this position
    currentRegister = FirstLCDRegister + (position >> 1);

    // Four different registers need to be written for a character
    for(i = 0; i < 4; i++){
        // Clear the bits, using the mask to keep existing data in other half the same
        *currentRegister = (*currentRegister & mask) | 0x0000;
        
        // Move to next highest register
        currentRegister += 5;
    }
}

/*
Internal function: Returns the segment pattern for a character, or 0x0000 if it is not available.
                   Note that all alphabetical characters should be converted to uppercase before using this function.
                   The pattern (in binary form) is {MPND LEGC JFHB K--A}, where the segments are as defined in fig 2-7
                   of Atmel's Application Note AVR065 - LCD Driver for the STK502 and AVR Butterfly. 1 indicates a
                   segment is on and 0 indicates it is off.
*/
unsigned int LCD_segmentPattern(char character){
    switch(character){
        // Alphabetical characters
        case 'A': return 0x0F51;
        case 'B': return 0x3991;
        case 'C': return 0x1441;     
        case 'D': return 0x3191;     
        case 'E': return 0x1E41;     
        case 'F': return 0x0E41;     
        case 'G': return 0x1D41;     
        case 'H': return 0x0F50;     
        case 'I': return 0x2080;     
        case 'J': return 0x1510;     
        case 'K': return 0x8648;     
        case 'L': return 0x1440;     
        case 'M': return 0x0578;     
        case 'N': return 0x8570;     
        case 'O': return 0x1551;     
        case 'P': return 0x0E51;     
        case 'Q': return 0x9551;     
        case 'R': return 0x8E51;     
        case 'S': return 0x9021;     
        case 'T': return 0x2081;     
        case 'U': return 0x1550;     
        case 'V': return 0x4448;     
        case 'W': return 0xC550;     
        case 'X': return 0xC028;     
        case 'Y': return 0x2028;     
        case 'Z': return 0x5009;

        // Numbers
        case '0': return 0x5559;
        case '1': return 0x0118;
        case '2': return 0x1E11;
        case '3': return 0x1B11;
        case '4': return 0x0B50;
        case '5': return 0x1B41;
        case '6': return 0x1F41;
        case '7': return 0x0111;
        case '8': return 0x1F51;
        case '9': return 0x1B51;

        // Other characters
        case '-': return 0x0A00;
        case '+': return 0x2A80;
        case '/': return 0x4008;
        case '\\': return 0x8020;
        case '_': return 0x1000;
        case '[': return 0x1441;
        case ']': return 0x1111;
        case '<': return 0x8008;
        case '>': return 0x4020;
        case '*': return 0xEAA8;

	// Special character: equals sign shows as underbar and overbar
	case '=': return 0x1001;

        // Not available
        default:  return 0x0000;
    }
}

