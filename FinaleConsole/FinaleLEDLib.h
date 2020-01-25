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

void QuadrumTug_ResetGameLED() {

}

#pragma endregion
