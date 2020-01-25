/*
Column is a row and row is a column because my matrix is rotated verticaly
*/
#include <LedControl.h>

LedControl lc = LedControl(10, 12, 11, 4);
int ledDelay = 50;

void StartUpAnimation () {
    for (int address = 0; address < 4; address ++) {
        for (int x = 0; x < 8; x ++) {
        lc.setColumn(address, x, B11111111);
        delay(ledDelay);
        }
    }
    
    
    for (int address = 0; address < 4; address ++) {
        lc.clearDisplay(address);
    }
    delay(300);
    for (int address = 0; address < 4; address ++) {
        for(int row = 0; row < 8; row ++) {
            lc.setRow(address, row, B11111111);
        }
    }
    delay(300);
    for (int address = 0; address < 4; address ++) {
        lc.clearDisplay(address);
    }
    delay(300);
    for (int address = 0; address < 4; address ++) {
        for(int row = 0; row < 8; row ++) {
            lc.setRow(address, row, B11111111);
        }
    }
    delay(300);
    for (int address = 0; address < 4; address ++) {
        lc.clearDisplay(address);
    }
    delay(300);
    for (int address = 0; address < 4; address ++) {
        for(int row = 0; row < 8; row ++) {
            lc.setRow(address, row, B11111111);
        }
    }
    delay(300);
    for (int address = 0; address < 4; address ++) {
        lc.clearDisplay(address);
    }
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

#pragma region QuadrumTug

void QuadrumTug_WinnerBottom () {
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

void QuadrumTug_WinnerTop () {
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

void QuadrumTug_DisplayScore (int bottom, int top) {
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

void QuadrumTug_ClearBottom() {
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

void QuadrumTug_ClearTop() {
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
