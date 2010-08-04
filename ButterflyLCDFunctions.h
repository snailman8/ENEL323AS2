/*
 *  University Of Canterbury - Department of Electrical and Computer Engineering
 *
 *  ENEL323 - Software Engineering 1
 *  Assignment 2: Atmel AVR Butterfly LCD Control Library
 *  File: ButterflyLCDFunctions.h
 *
 *  Header file for an Atmel AVR Butterfly LCD Control Library.
 *
 *  Blair Bonnett (bcb22) and Oliver Krenek (ofk10)
 *  Last Updated: 2 July 2006
 *
 */

#ifndef ButterflyLCDFunctions_h
#define ButterflyLCDFunctions_h

/*
initDisplay

Initialises the LCD display. This function should be run before using any of the other functions in the library.

Inputs: None
Returns: void
*/
void LCD_initDisplay(void);

/*
showCharacter

Shows a character at a particular position on the display.

Inputs: position - the position (0 to 5 inclusive) to display the character at. 0 is the left-hand character and
                   5 is the right-hand character.
        character - the character to display.
Returns: void
*/
void LCD_showCharacter(int position, char character);

/*
togglePosition

Toggles the visibility of the character at a particular position on the LCD. If it is hidden, then this function
will display it and vice-versa.

Inputs: position - the position (0 to 5 inclusive) to toggle. 0 is the left-hand character and 5 is the right-hand
                   character.
Returns: 0 if the character is hidden after the toggle.
         1 if it is displayed after the toggle.
        -1 if the position is invalid.
*/
int LCD_togglePosition(int position);

/*
showString

Displays a string on the display. Only the first six characters will be visible initially; to show the rest use the
scrollDisplay function.

Inputs: string - a pointer to the string to display.
Returns: void
*/
void LCD_showString(char *string);

/*
loadTwoStrings

Loads two strings ready for display. The first six characters of the first string is shown on the display. To
change which string is shown, use the switchStrings function, and to show the rest of the strings use the
scrollDisplay function.

Inputs: string1 - a pointer to the first string.
        string2 - a pointer to the second string.
Returns: void
*/
void LCD_loadTwoStrings(char *string1, char *string2);

/*
switchStrings

Switches which of the two strings loaded in the loadTwoStrings function is currently shown on the display.
The first six characters of the new string will be shown; to show the rest use the scrollDisplay function. If
the loadTwoStrings function has not previously been used to load two strings, this function will do nothing.

Inputs: None
Returns: -1 if no action was taken.
1 if the first string is currently displayed.
2 if the second string is currently displayed.
*/
int LCD_switchStrings(void);

/*
scrollDisplay

Scrolls the display. If no string has been loaded, then whatever characters are on the screen are moved as
directed, and blank characters are inserted to fill the space. If a string is being displayed, it will be moved
as directed. If the end of a string is reached, then blank characters will be inserted unless the value of the
wrap input is 1, in which case the string will wrap around (with three blank characters in between).

Inputs: direction - which direction to scroll in. Use a value from the LCDScrollDirection enumeration.
        wrap - 0 if blank characters should be inserted at the end of strings
               1 if strings should wrap around when being scrolled.
Returns: void
*/
void LCD_scrollDisplay(int direction, int wrap);

/*
changeContrast

Adjusts the contrast of the display.

Inputs: contrast - what level (0 - 15 inclusive) to set the contrast to. 0 is the least contrast and 15 is the most.
Returns: void
*/
void LCD_changeContrast(int contrast);

/*
clearDisplay

Clears the display and any loaded strings.

Inputs: None
Returns: void
*/
void LCD_clearDisplay(void);

/*
LCDScrollDirection

Used to control which direction the scrollDisplay function scolls the text in.

Values: LCDScrollLeft - scroll the text to the left
        LCDScrollRight - scroll the text to the right
*/
enum LCDScrollDirection{LCDScrollLeft = 0, LCDScrollRight = 1};

#endif
