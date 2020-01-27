/*
Column is a row and row is a column because my matrix is rotated verticaly
*/
#include <LedControl.h>

LedControl lc = LedControl(10, 12, 11, 4); // LedControl(DataIn, CLK, LOAD, #devices)

void StartUpAnimation () {
    int animationDelay = 25;

    lc.setColumn(0, 0, B00011000);
    delay(animationDelay);
    lc.setColumn(0, 0, B00111100);
    delay(animationDelay);
    lc.setColumn(0, 0, B01111110);
    delay(animationDelay);
    lc.setColumn(0, 0, B11111111);
    delay(animationDelay);
    for (int address = 0; address < 4; address++) {
        for (int row = 0; row < 8; row ++) {
            if (address == 3 && row == 7) {
                break;
            } else if (row == 0 && address == 0) {
                lc.setColumn(address, row, B11111111);
            } else {
                lc.setColumn(address, row, B10000001);
                delay(animationDelay);
            }   
        }
    }
    lc.setColumn(3, 7, B10000001);
    delay(animationDelay);
    lc.setColumn(3, 7, B11000011);
    delay(animationDelay);
    lc.setColumn(3, 7, B11100111);
    delay(animationDelay);
    lc.setColumn(3, 7, B11111111);
    delay(animationDelay);

    //Spell "Finale"
    byte FinaleAddress0[] = {
        B10111101,
        B10101001,
        B10101001,
        B10000001,
        B10000001,
        B10101101
    };
    for (int x = 2; x < 8; x++) {
        lc.setColumn(0, x, FinaleAddress0[x-2]);
        delay(animationDelay);
    }
    byte FinaleAddress1[] ={
        B10111101,
        B10010001,
        B10001001,
        B10111101
    };
    for (int x = 2; x < 6; x++) {
        lc.setColumn(1, x, FinaleAddress1[x-2]);
        delay(animationDelay);
    }
    byte FinaleAddress2[] = {
        B10111101,
        B10101001,
        B10111101,
        B10000001,
        B10000001,
        B10111101,
        B10000101,
        B10000101
    };
    for (int x = 0; x < 8; x++) {
        lc.setColumn(2, x, FinaleAddress2[x]);
        delay(animationDelay);
    }
    byte FinaleAddress3[] = {
        B10111101,
        B10101101,
        B10101101
    };
    for (int x = 2; x < 5; x++) {
        lc.setColumn(3, x, FinaleAddress3[x-2]);
        delay(animationDelay);
    }
    delay(3000);
}

void SetFullColumnOn (int address, int column) {
    lc.setColumn(address, column, B11111111);
}
void SetFullColumnOff (int address, int column) {
    lc.setColumn(address, column, B00000000);
}

void AllLEDOff () {
    for (int i = 0; i < 4; i++ ) {
        lc.clearDisplay(i);
    }
}

#pragma region Menu

int animationDelay = 25;

void Draw_Menu_Arrows () {    
    byte leftArrow[] = {
        B10011001,
        B10111101,
        B10011001,
        B10011001,
        B10011001,
        B10011001
    };
    for (int x = 2; x < 8; x++) {
        lc.setColumn(0, x, leftArrow[x-2]);
    }
    byte rightArrow[] ={
        B10011001,
        B10011001,
        B10011001,
        B10011001,
        B10111101,
        B10011001
    };
    for (int x = 0; x < 6; x++) {
        lc.setColumn(3, x, rightArrow[x]);
    }
}    

void Draw_Menu_QT() {
    byte Q[] = {
        B10000001,
        B10000001,
        B10000001,
        B10111101,
        B10100101,
        B10100101,
        B10111101,
        B10000011
    };
    for (int x = 0; x < 8; x++) {
        lc.setColumn(1, x, Q[x]);
    }
    byte T[] = {
        B10100001,
        B10100001,
        B10111101,
        B10100001,
        B10100001,
        B10000001,
        B10000001,
        B10000001
    };
    for (int x = 0; x < 8; x++) {
        lc.setColumn(2, x, T[x]);
    }
    delay(200);
}

void Draw_Menu_Dummy() {
    byte D[] = {
        B10000001,
        B10000001,
        B10000001,
        B10111101,
        B10100101,
        B10100101,
        B10011001,
        B10000001
    };
    for (int x = 0; x < 8; x++) {
        lc.setColumn(1, x, D[x]);
    }
    byte M[] = {
        B10111101,
        B10100001,
        B10010001,
        B10100001,
        B10111101,
        B10000001,
        B10000001,
        B10000001
    };
    for (int x = 0; x < 8; x++) {
        lc.setColumn(2, x, M[x]);
    }
    delay(200);
}

void Draw_ExitToMenu() {   
    for (int address = 1; address >= 0; address--) {
        for (int row = 7; row >= 0; row --) {
            lc.setColumn(address, row, B10000001);
            lc.setColumn(abs(address-3), abs(row-7), B10000001);
            delay(animationDelay); 
        }
    }
    lc.setColumn(0, 0, B11000011);
    lc.setColumn(3, 7, B11000011);
    delay(animationDelay);
    lc.setColumn(0, 0, B11100111);
    lc.setColumn(3, 7, B11100111);
    delay(animationDelay);
    lc.setColumn(0, 0, B11100111);
    lc.setColumn(3, 7, B11100111);
    delay(animationDelay);
    lc.setColumn(0, 0, B11111111);
    lc.setColumn(3, 7, B11111111);
    delay(500);
}

#pragma endregion

#pragma region QuadrumTug

void Draw_QuadrumTug_WinnerBottom () {
    for (int count = 0; count < 3; count++) {
        lc.setColumn(1, 6, B00000000);
        lc.setColumn(1, 5, B00000000);
        lc.setColumn(1, 4, B00000000);
        lc.setColumn(1, 3, B00000000);
        lc.setColumn(1, 2, B00000000);
        lc.setColumn(1, 1, B00000000);
        lc.setColumn(1, 0, B00000000);
        lc.setColumn(0, 7, B00000000);
        lc.setColumn(0, 6, B00000000);
        lc.setColumn(0, 5, B00000000);
        lc.setColumn(0, 4, B00000000);
        lc.setColumn(0, 3, B00000000);
        delay(400);
        lc.setColumn(1, 6, B01111110);
        lc.setColumn(1, 5, B01111110);
        lc.setColumn(1, 4, B01111110);
        lc.setColumn(1, 3, B01111110);
        lc.setColumn(1, 2, B01111110);
        lc.setColumn(1, 1, B01111110);
        lc.setColumn(1, 0, B01111110);
        lc.setColumn(0, 7, B01111110);
        lc.setColumn(0, 6, B01111110);
        lc.setColumn(0, 5, B01111110);
        lc.setColumn(0, 4, B01111110);
        lc.setColumn(0, 3, B01111110);
        delay(400);
    }
}

void Draw_QuadrumTug_WinnerTop () {
    for (int count = 0; count < 3; count ++) {
        lc.setColumn(2, 1, B00000000);
        lc.setColumn(2, 2, B00000000);
        lc.setColumn(2, 3, B00000000);
        lc.setColumn(2, 4, B00000000);
        lc.setColumn(2, 5, B00000000);
        lc.setColumn(2, 6, B00000000);
        lc.setColumn(2, 7, B00000000);
        lc.setColumn(3, 0, B00000000);
        lc.setColumn(3, 1, B00000000);
        lc.setColumn(3, 2, B00000000);
        lc.setColumn(3, 3, B00000000);
        lc.setColumn(3, 4, B00000000);
        delay(400);
        lc.setColumn(2, 1, B01111110);
        lc.setColumn(2, 2, B01111110);
        lc.setColumn(2, 3, B01111110);
        lc.setColumn(2, 4, B01111110);
        lc.setColumn(2, 5, B01111110);
        lc.setColumn(2, 6, B01111110);
        lc.setColumn(2, 7, B01111110);
        lc.setColumn(3, 0, B01111110);
        lc.setColumn(3, 1, B01111110);
        lc.setColumn(3, 2, B01111110);
        lc.setColumn(3, 3, B01111110);
        lc.setColumn(3, 4, B01111110);
        delay(400);
    }
}

void Draw_QuadrumTug_Score (int bottom, int top) {
    if (bottom == 0) {
        lc.setColumn(0, 5, B01111110);
        lc.setColumn(0, 6, B01000010);
        lc.setColumn(0, 7, B01000010);
        lc.setColumn(1, 0, B01000010);
        lc.setColumn(1, 1, B01000010);
        lc.setColumn(1, 2, B01000010);
        lc.setColumn(1, 3, B01000010);
        lc.setColumn(1, 4, B01111110);
    } else if (bottom == 1) {
        lc.setColumn(1, 4, B00001000);
        lc.setColumn(1, 3, B00011000);
        lc.setColumn(1, 2, B00101000);
        lc.setColumn(1, 1, B00001000);
        lc.setColumn(1, 0, B00001000);
        lc.setColumn(0, 7, B00001000);
        lc.setColumn(0, 6, B00001000);
        lc.setColumn(0, 5, B00001000);
    } else if (bottom == 2) {
        lc.setColumn(1, 4, B00111100);
        lc.setColumn(1, 3, B01000010);
        lc.setColumn(1, 2, B00000010);
        lc.setColumn(1, 1, B00000100);
        lc.setColumn(1, 0, B00001000);
        lc.setColumn(0, 7, B00010000);
        lc.setColumn(0, 6, B00100000);
        lc.setColumn(0, 5, B01111110);
    } else if (bottom == 3) {
        lc.setColumn(1, 4, B01111100);
        lc.setColumn(1, 3, B00000010);
        lc.setColumn(1, 2, B00000010);
        lc.setColumn(1, 1, B01111100);
        lc.setColumn(1, 0, B00000010);
        lc.setColumn(0, 7, B00000010);
        lc.setColumn(0, 6, B00000010);
        lc.setColumn(0, 5, B01111100);
    } else if (bottom == 4) {
        lc.setColumn(1, 4, B01000010);
        lc.setColumn(1, 3, B01000010);
        lc.setColumn(1, 2, B01000010);
        lc.setColumn(1, 1, B01000010);
        lc.setColumn(1, 0, B00111110);
        lc.setColumn(0, 7, B00000010);
        lc.setColumn(0, 6, B00000010);
        lc.setColumn(0, 5, B00000010);
    } else if (bottom == 5) {
        lc.setColumn(1, 4, B01111110);
        lc.setColumn(1, 3, B01000000);
        lc.setColumn(1, 2, B01000000);
        lc.setColumn(1, 1, B00111100);
        lc.setColumn(1, 0, B00000010);
        lc.setColumn(0, 7, B00000010);
        lc.setColumn(0, 6, B00000010);
        lc.setColumn(0, 5, B01111100);
    }

    if (top == 0) {
        lc.setColumn(2, 3, B01111110);
        lc.setColumn(2, 4, B01000010);
        lc.setColumn(2, 5, B01000010);
        lc.setColumn(2, 6, B01000010);
        lc.setColumn(2, 7, B01000010);
        lc.setColumn(3, 0, B01000010);
        lc.setColumn(3, 1, B01000010);
        lc.setColumn(3, 2, B01111110);
    } else if (top == 1) {
        lc.setColumn(2, 3, B00010000);
        lc.setColumn(2, 4, B00011000);
        lc.setColumn(2, 5, B00010100);
        lc.setColumn(2, 6, B00010000);
        lc.setColumn(2, 7, B00010000);
        lc.setColumn(3, 0, B00010000);
        lc.setColumn(3, 1, B00010000);
        lc.setColumn(3, 2, B00010000);
    } else if (top == 2) {
        lc.setColumn(2, 3, B00111100);
        lc.setColumn(2, 4, B01000010);
        lc.setColumn(2, 5, B01000000);
        lc.setColumn(2, 6, B00100000);
        lc.setColumn(2, 7, B00010000);
        lc.setColumn(3, 0, B00001000);
        lc.setColumn(3, 1, B00000100);
        lc.setColumn(3, 2, B01111110);
    } else if (top == 3) {
        lc.setColumn(2, 3, B00111110);
        lc.setColumn(2, 4, B01000000);
        lc.setColumn(2, 5, B01000000);
        lc.setColumn(2, 6, B00111110);
        lc.setColumn(2, 7, B01000000);
        lc.setColumn(3, 0, B01000000);
        lc.setColumn(3, 1, B01000000);
        lc.setColumn(3, 2, B00111110);
    } else if (top == 4) {
        lc.setColumn(2, 3, B01000010);
        lc.setColumn(2, 4, B01000010);
        lc.setColumn(2, 5, B01000010);
        lc.setColumn(2, 6, B01000010);
        lc.setColumn(2, 7, B01111100);
        lc.setColumn(3, 0, B01000000);
        lc.setColumn(3, 1, B01000000);
        lc.setColumn(3, 2, B01000000);
    } else if (top == 5) {
        lc.setColumn(2, 3, B01111110);
        lc.setColumn(2, 4, B00000010);
        lc.setColumn(2, 5, B00000010);
        lc.setColumn(2, 6, B00111100);
        lc.setColumn(2, 7, B01000000);
        lc.setColumn(3, 0, B01000000);
        lc.setColumn(3, 1, B01000000);
        lc.setColumn(3, 2, B00111110);
    }
}

void Draw_QuadrumTug_ClearBottom() {
    SetFullColumnOff(1, 6);
    SetFullColumnOff(1, 5);
    SetFullColumnOff(1, 4);
    SetFullColumnOff(1, 3);
    SetFullColumnOff(1, 2);
    SetFullColumnOff(1, 1);
    SetFullColumnOff(1, 0);
    SetFullColumnOff(0, 7);
    SetFullColumnOff(0, 6);
    SetFullColumnOff(0, 5);
    SetFullColumnOff(0, 4);
    SetFullColumnOff(0, 3);
}

void Draw_QuadrumTug_ClearTop() {
    SetFullColumnOff(2, 1);
    SetFullColumnOff(2, 2);
    SetFullColumnOff(2, 3);
    SetFullColumnOff(2, 4);
    SetFullColumnOff(2, 5);
    SetFullColumnOff(2, 6);
    SetFullColumnOff(2, 7);
    SetFullColumnOff(3, 0);
    SetFullColumnOff(3, 1);
    SetFullColumnOff(3, 2);
    SetFullColumnOff(3, 3);
    SetFullColumnOff(3, 4);
}

#pragma endregion
