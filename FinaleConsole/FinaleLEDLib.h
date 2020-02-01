/*
Column is a row and row is a column because my matrix is rotated verticaly
*/
#include <LedControl.h>

LedControl lcBottom = LedControl(10, 12, 11, 4); // LedControl(DataIn, CLK, LOAD, #devices)
LedControl lcTop = LedControl(9, 7, 8, 4);  // LedControl(DataIn, CLK, LOAD, #devices)

void StartUpAnimation () {
    char animationDelay = 25;


    for (char x = 0; x < 8; x++) {
        lcTop.setLed(0, x, 7, true);
        lcBottom.setLed(0, 8-x, 7, true);
        delay(animationDelay);
    }

    for (char address = 0; address < 4; address ++) {
        for (int x = 0; x < 8; x++) {
            lcTop.setLed(address, 7, 7-x, true);
            lcBottom.setLed(address, 0, 7-x, true);
            delay(animationDelay);
        }
    }    

    for (char x = 7; x >= 0; x--) {
        lcTop.setLed(3, x, 0, true);
        lcBottom.setLed(3, 8-x, 0, true);
        delay(animationDelay);
    }

    //Spell "Finale"
    byte FinaleAddress0[] = {
        B01110101,
        B00000001,
        B00010101,
        B00010101,
        B00010101,
        B01111101
    };
    for (char x = 5; x >= 0; x--) {
        lcTop.setColumn(0, x, FinaleAddress0[x]);
        delay(animationDelay);
    }
    byte FinaleAddress1[] ={
        B01111101,
        B00100001,
        B00010001,
        B00001001,
        B01111101,
        B00000001,
        B01110101
    };
    for (char x = 7; x >= 1; x--) {
        lcTop.setColumn(1, x, FinaleAddress1[x-1]);
        delay(animationDelay);
    }
    byte FinaleAddress2[] = {
        B01000001,
        B01000001,
        B01111101,
        B00000001,
        B01111001,
        B00010101,
        B00010101,
        B01111001
    }; 
    for (char x = 7; x >= 0; x--) {
        lcTop.setColumn(2, x, FinaleAddress2[x]);
        delay(animationDelay);
    }
    byte FinaleAddress3[] = {
        B01010101,
        B01010101,
        B01010101,
        B01111101,
        B00000001,
        B01000001
    }; 
    for (char x = 7; x >= 2; x--) {
        lcTop.setColumn(3, x, FinaleAddress3[x-2]);
        delay(animationDelay);
    }

    //Spell "Games"
    byte GamesAddress0[] = {
        B10111110,
        B10100010,
        B10101010,
        B10111010,
    };
    for (char x = 4; x >= 1; x--) {
        lcBottom.setColumn(0, x, GamesAddress0[4-x]);
        delay(animationDelay);
    }
    byte GamesAddress1[] ={
        B10111100,
        B10001010,
        B10001010,
        B10111100,
        B10000000,
        B10111110,
        B10000100,
        B10001000
        
    };
    for (char x = 7; x >= 0; x--) {
        lcBottom.setColumn(1, x, GamesAddress1[7-x]);
        delay(animationDelay);
    }
    byte GamesAddress2[] = {
        B10001000,
        B10000100,
        B10111110,
        B10000000,
        B10111110,
        B10101010,
        B10101010,
        B10101010
    }; 
    for (char x = 7; x >= 0; x--) {
        lcBottom.setColumn(2, x, GamesAddress2[7-x]);
        delay(animationDelay);
    }
    byte GamesAddress3[] = {
        B10101110,
        B10101010,
        B10101010,
        B10111010
    }; 
    for (char x = 6; x >= 3; x--) {
        lcBottom.setColumn(3, x, GamesAddress3[6-x]);
        delay(animationDelay);
    }
    delay (3000);
}

void SetFullColumnOn (int screen, int address, int column) { //screen 0 = bottom, 1 = top
    if (screen == 0) {
        lcBottom.setColumn(address, column, B11111111);
    } else {
        lcTop.setColumn(address, column, B11111111);
    }
}
void SetFullColumnOff (int screen, int address, int column) { //screen 0 = bottom, 1 = top
    if (screen == 0) {
        lcBottom.setColumn(address, column, B00000000);
    } else {
        lcTop.setColumn(address, column, B00000000);
    }
}

void AllLEDOff () {
    for (char i = 0; i < 4; i++ ) {
        lcTop.clearDisplay(i);
        lcBottom.clearDisplay(i);
    }
}

#pragma region Menu

byte animationDelay = 25;


void Draw_Menu_Arrows () {    
    
   byte leftTop[] = {
            B10000001,
            B11000001,
            B10100001,
            B10000001,
            B10000001,
            B10000001,
        };
    byte leftBottom[] = {
            B10000001,
            B10000011,
            B10000101,
            B10000001,
            B10000001,
            B10000001,
        };
    for (char x = 5; x >= 0; x--) {
        lcTop.setColumn(0, x, leftTop[5-x]);
        lcBottom.setColumn(0, x, leftBottom[5-x]);
    }

    byte rightTop[] = {
        B10000001,
        B10000001,
        B10000001,
        B10100001,
        B11000001,
        B10000001
    };
    byte rightBottom[] = {
        B10000001,
        B10000001,
        B10000001,
        B10000101,
        B10000011,
        B10000001
    };
    for (char x = 7; x >= 2; x--) {
        lcTop.setColumn(3, x, rightTop[7-x]);
        lcBottom.setColumn(3, x, rightBottom[7-x]);
    }
}    

void Draw_Menu_QT() {
    byte Q_top[]= {
        B00000001,
        B00000001,
        B11110001,
        B00010001,
        B00010001,
        B00010001,
        B11110001,
        B00000001
    };
    byte Q_bottom[] = {
        B10000000,
        B10000000,
        B10001111,
        B10001000,
        B10001000,
        B10001000,
        B10011111,
        B10011000
    };
    for (char x = 7; x >= 0; x--) {
        lcTop.setColumn(1, x, Q_top[7-x]);
        lcBottom.setColumn(1, x, Q_bottom[7-x]);
    }
    
    byte T_top[] = {
        B00110001,
        B00110001,
        B11110001,
        B11110001,
        B00110001,
        B00110001,
        B00000001,
        B00000001
    };
    byte T_bottom[] = {
        B10000000,
        B10000000,
        B10001111,
        B10001111,
        B10000000,
        B10000000,
        B10000000,
        B10000000
    };
    for (char x = 7; x >= 0; x--) {
        lcTop.setColumn(2, x, T_top[7-x]);
        lcBottom.setColumn(2, x, T_bottom[7-x]);
    }

    delay(200);
}

void Draw_Menu_Snake() {
    byte S1_Top[] = {
        B00000001,
        B00000001,
        B11110001,
        B11110001,
        B00110001,
        B00110001,
        B00110001,
        B00110001
    };
    byte S1_Bottom[] = {
        B10000000,
        B10000000,
        B10001111,
        B10001111,
        B10001100,
        B10001100,
        B10001100,
        B10001100
    };
    for (char x = 7; x >= 0; x--){
        lcTop.setColumn(1, x, S1_Top[7-x]);
        lcBottom.setColumn(1, x, S1_Bottom[7-x]);
    }

    byte S2_top[] = {
        B00110001,
        B00110001,
        B00110001,
        B00110001,
        B00110001,
        B00110001,
        B00000001,
        B00000001
    };
    byte S2_bottom[] = {
        B10001100,
        B10000000,
        B10000000,
        B10000000,
        B10001100,
        B10001100,
        B10000000,
        B10000000
    };
    for (char x = 7; x >= 0; x--){
        lcTop.setColumn(2, x, S2_top[7-x]);
        lcBottom.setColumn(2, x, S2_bottom[7-x]);
    }

    delay(200);
}

void Draw_ExitToMenu() {   
    for (char address = 1; address >= 0; address--) {
        for (char row = 7; row >= 0; row --) {
            lcTop.setColumn(address, 7-row, B00000001);
            lcTop.setColumn(3-address, row, B00000001);
            lcBottom.setColumn(address, 7-row, B10000000);
            lcBottom.setColumn(3-address, row, B10000000);
            delay(animationDelay); 
        }
    }
    for (char i = 6; i >= 0; i--) {
        lcTop.setLed(0, i, 7, true);
        lcTop.setLed(3, i, 0, true);
        lcBottom.setLed(0, 7-i, 7, true);
        lcBottom.setLed(3, 7-i, 0, true);
        delay(animationDelay*2); 
    }
}

#pragma endregion

#pragma region QuadrumTug

void Draw_QuadrumTug_WinnerBottom () {
    for (char count = 0; count < 3; count++) {
        for (char i = 0; i < 12; i++) {
            if (i < 7) {
                lcTop.setColumn(1, i+1, B00000000);
                lcBottom.setColumn(1, i+1, B00000000);
            } else {
                lcTop.setColumn(0, i-7, B00000000);
                lcBottom.setColumn(0, i-7, B00000000);
            }
        }
        delay(400);
        for (char i = 0; i < 12; i++) {
            if (i < 7) {
                lcTop.setColumn(1, i+1, B11111110);
                lcBottom.setColumn(1, i+1, B01111111);
            } else {
                lcTop.setColumn(0, i-7, B11111110);
                lcBottom.setColumn(0, i-7, B01111111);
            }
        }
        delay(400);
    }
}

void Draw_QuadrumTug_WinnerTop () {
    for (char count = 0; count < 3; count++) {
        for (char i = 0; i < 12; i++) {
            if (i < 7) {
                lcTop.setColumn(2, 6-i, B00000000);
                lcBottom.setColumn(2, 6-i, B00000000);
            } else {
                lcTop.setColumn(3, 14-i, B00000000);
                lcBottom.setColumn(3, 14-i, B00000000);
            }
        }
        delay(400);
        for (char i = 0; i < 12; i++) {
            if (i < 7) {
                lcTop.setColumn(2, 6-i, B11111110);
                lcBottom.setColumn(2, 6-i, B01111111);
            } else {
                lcTop.setColumn(3, 14-i, B11111110);
                lcBottom.setColumn(3, 14-i, B01111111);
            }
        }
        delay(400);
    }
}

void Draw_QuadrumTug_Score (int bottom, int top) {
    if (bottom == 0) {
        lcTop.setColumn(0, 2, B11100000);
        lcTop.setLed(0, 2, 1, true);
        lcTop.setLed(0, 2, 0, true);
        lcTop.setLed(1, 2, 7, true);
        lcTop.setLed(1, 2, 6, true);
        lcTop.setLed(1, 2, 5, true);
        lcTop.setLed(1, 2, 4, true);
        lcTop.setColumn(1, 3, B11100000);

        lcBottom.setColumn(0, 2, B00000111);
        lcBottom.setLed(0, 5, 1, true);
        lcBottom.setLed(0, 5, 0, true);
        lcBottom.setLed(1, 5, 7, true);
        lcBottom.setLed(1, 5, 6, true);
        lcBottom.setLed(1, 5, 5, true);
        lcBottom.setLed(1, 5, 4, true);
        lcBottom.setColumn(1, 3, B00000111);
    } else if (bottom == 1) {
        lcTop.setLed(1, 0, 4, true);
        lcTop.setLed(1, 1, 5, true);

        lcBottom.setLed(1, 7, 3, true);
        lcBottom.setLed(1, 7, 4, true);
        lcBottom.setLed(1, 7, 5, true);
        lcBottom.setLed(1, 7, 6, true);
        lcBottom.setLed(1, 7, 7, true);
        lcBottom.setLed(0, 7, 0, true);
        lcBottom.setLed(0, 7, 1, true);
        lcBottom.setLed(0, 7, 2, true);
    } else if (bottom == 2) {
        lcTop.setColumn(0, 2, B11100000);
        lcTop.setColumn(0, 1, B01000000);
        lcTop.setColumn(0, 0, B10000000);
        lcTop.setColumn(1, 4, B00100000);
        lcTop.setColumn(1, 3, B11000000);

        lcBottom.setColumn(0, 2, B00000111);
        lcBottom.setColumn(1, 7, B00000001);
        lcBottom.setColumn(1, 6, B00000010);
        lcBottom.setColumn(1, 5, B00000100);
        lcBottom.setColumn(1, 4, B00000100);
        lcBottom.setColumn(1, 3, B00000011);
    } else if (bottom == 3) {
        lcTop.setColumn(0, 2, B11100000);
        lcTop.setColumn(1, 6, B11100000);
        lcTop.setColumn(1, 3, B11100000);

        lcBottom.setColumn(0, 2, B00000011);
        lcBottom.setColumn(0, 1, B00000100);
        lcBottom.setColumn(0, 0, B00000100);
        lcBottom.setColumn(1, 7, B00000100);
        lcBottom.setColumn(1, 6, B00000011);
        lcBottom.setColumn(1, 5, B00000100);
        lcBottom.setColumn(1, 4, B00000100);
        lcBottom.setColumn(1, 3, B00000011);
    } else if (bottom == 4) {
        lcTop.setColumn(1, 7, B11000000);
        lcTop.setLed(1, 2, 6, true);
        lcTop.setLed(1, 2, 5, true);
        lcTop.setLed(1, 2, 4, true);
        lcTop.setLed(1, 2, 3, true);

        lcBottom.setLed(0, 5, 2, true);
        lcBottom.setLed(0, 5, 1, true);
        lcBottom.setLed(0, 5, 0, true);
        lcBottom.setColumn(1, 7, B00000111);
        lcBottom.setLed(1, 5, 6, true);
        lcBottom.setLed(1, 5, 5, true);
        lcBottom.setLed(1, 5, 4, true);
        lcBottom.setLed(1, 5, 3, true);
    } else if (bottom == 5) {
        lcTop.setColumn(0, 2, B11100000);
        lcTop.setColumn(1, 6, B11000000);
        lcTop.setLed(1, 2, 5, true);
        lcTop.setLed(1, 2, 4, true);
        lcTop.setColumn(1, 3, B11100000);

        lcBottom.setColumn(0, 2, B00000011);
        lcBottom.setLed(0, 5, 1, true);
        lcBottom.setLed(0, 5, 0, true);
        lcBottom.setLed(1, 5, 7, true);
        lcBottom.setColumn(1, 6, B00000011);
        lcBottom.setColumn(1, 3, B00000111);
    }

    if (top == 0) {
        lcTop.setColumn(2, 4, B11100000);
        lcTop.setLed(2, 2, 3, true);
        lcTop.setLed(2, 2, 2, true);
        lcTop.setLed(2, 2, 1, true);
        lcTop.setLed(2, 2, 0, true);
        lcTop.setLed(3, 2, 7, true);
        lcTop.setLed(3, 2, 6, true);
        lcTop.setColumn(3, 5, B11100000);

        lcBottom.setColumn(2, 4, B00000111);
        lcBottom.setLed(2, 5, 3, true);
        lcBottom.setLed(2, 5, 2, true);
        lcBottom.setLed(2, 5, 1, true);
        lcBottom.setLed(2, 5, 0, true);
        lcBottom.setLed(3, 5, 7, true);
        lcBottom.setLed(3, 5, 6, true);
        lcBottom.setColumn(3, 5, B00000111);
    } else if (top == 1) {
        lcTop.setLed(2, 0, 0, true);
        lcTop.setLed(2, 0, 1, true);
        lcTop.setLed(2, 0, 2, true);
        lcTop.setLed(2, 0, 3, true);
        lcTop.setLed(2, 0, 4, true);
        lcTop.setLed(3, 0, 7, true);
        lcTop.setLed(3, 0, 6, true);
        lcTop.setLed(3, 0, 5, true);

        lcBottom.setLed(2, 6, 2, true);
        lcBottom.setLed(2, 7, 3, true);
    } else if (top == 2) {
        lcTop.setColumn(2, 4, B11000000);
        lcTop.setLed(2, 2, 3, true);
        lcTop.setLed(2, 2, 2, true);
        lcTop.setLed(2, 1, 1, true);
        lcTop.setLed(2, 0, 0, true);
        lcTop.setColumn(3, 5, B11100000);

        lcBottom.setColumn(2, 4, B00000011);
        lcBottom.setLed(2, 5, 3, true);
        lcBottom.setLed(3, 7, 7, true);
        lcBottom.setLed(3, 6, 6, true);
        lcBottom.setColumn(3, 5, B00000111);
    } else if (top == 3) {
        lcTop.setColumn(2, 4, B11000000);
        lcTop.setLed(2, 2, 3, true);
        lcTop.setLed(2, 2, 2, true);
        lcTop.setColumn(2, 1, B11000000);
        lcTop.setLed(2, 2, 0, true);
        lcTop.setLed(3, 2, 7, true);
        lcTop.setLed(3, 2, 6, true);
        lcTop.setColumn(3, 5, B11000000);

        lcBottom.setColumn(2, 4, B00000111);
        lcBottom.setColumn(2, 1, B00000111);
        lcBottom.setColumn(3, 5, B00000111);
    } else if (top == 4) {
        lcTop.setLed(2, 2, 4, true);
        lcTop.setLed(2, 2, 3, true);
        lcTop.setLed(2, 2, 2, true);
        lcTop.setLed(2, 2, 1, true);
        lcTop.setColumn(2, 0, B11100000);
        lcTop.setLed(3, 2, 7, true);
        lcTop.setLed(3, 2, 6, true);
        lcTop.setLed(3, 2, 5, true);

        lcBottom.setLed(2, 5, 4, true);
        lcBottom.setLed(2, 5, 3, true);
        lcBottom.setLed(2, 5, 2, true);
        lcBottom.setLed(2, 5, 1, true);
        lcBottom.setColumn(2, 0, B00000011);
    } else if (top == 5) {
        lcTop.setColumn(2, 4, B11100000);
        lcTop.setColumn(2, 1, B11000000);
        lcTop.setLed(2, 2, 0, true);
        lcTop.setLed(3, 2, 7, true);
        lcTop.setLed(3, 2, 6, true);
        lcTop.setColumn(3, 5, B11000000);

        lcBottom.setColumn(2, 4, B00000111);
        lcBottom.setLed(2, 5, 3, true);
        lcBottom.setLed(2, 5, 2, true);
        lcBottom.setColumn(2, 1, B00000011);
        lcBottom.setColumn(3, 5, B00000111);
    }
}

void Draw_QuadrumTug_ClearBottom() {
    SetFullColumnOff(0, 1, 1);
    SetFullColumnOff(0, 1, 2);
    SetFullColumnOff(0, 1, 3);
    SetFullColumnOff(0, 1, 4);
    SetFullColumnOff(0, 1, 5);
    SetFullColumnOff(0, 1, 6);
    SetFullColumnOff(0, 1, 7);
    SetFullColumnOff(1, 1, 1);
    SetFullColumnOff(1, 1, 2);
    SetFullColumnOff(1, 1, 3);
    SetFullColumnOff(1, 1, 4);
    SetFullColumnOff(1, 1, 5);
    SetFullColumnOff(1, 1, 6);
    SetFullColumnOff(1, 1, 7);

    SetFullColumnOff(0, 0, 0);
    SetFullColumnOff(0, 0, 1);
    SetFullColumnOff(0, 0, 2);
    SetFullColumnOff(0, 0, 3);
    SetFullColumnOff(0, 0, 4);
    SetFullColumnOff(1, 0, 0);
    SetFullColumnOff(1, 0, 1);
    SetFullColumnOff(1, 0, 2);
    SetFullColumnOff(1, 0, 3);
    SetFullColumnOff(1, 0, 4);
}

void Draw_QuadrumTug_ClearTop() {
    SetFullColumnOff(0, 2, 6);
    SetFullColumnOff(0, 2, 5);
    SetFullColumnOff(0, 2, 4);
    SetFullColumnOff(0, 2, 3);
    SetFullColumnOff(0, 2, 2);
    SetFullColumnOff(0, 2, 1);
    SetFullColumnOff(0, 2, 0);
    SetFullColumnOff(1, 2, 6);
    SetFullColumnOff(1, 2, 5);
    SetFullColumnOff(1, 2, 4);
    SetFullColumnOff(1, 2, 3);
    SetFullColumnOff(1, 2, 2);
    SetFullColumnOff(1, 2, 1);
    SetFullColumnOff(1, 2, 0);

    SetFullColumnOff(1, 3, 7);
    SetFullColumnOff(1, 3, 6);
    SetFullColumnOff(1, 3, 5);
    SetFullColumnOff(1, 3, 4);
    SetFullColumnOff(1, 3, 3);
    SetFullColumnOff(0, 3, 7);
    SetFullColumnOff(0, 3, 6);
    SetFullColumnOff(0, 3, 5);
    SetFullColumnOff(0, 3, 4);
    SetFullColumnOff(0, 3, 3);
}

#pragma endregion
