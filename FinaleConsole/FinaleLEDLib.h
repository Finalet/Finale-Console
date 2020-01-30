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
        lcBottom.setLed(0, x, 0, true);
        delay(animationDelay);
    }

    for (char address = 0; address < 4; address ++) {
        for (int x = 0; x < 8; x++) {
            lcTop.setLed(address, 7, 7-x, true);
            lcBottom.setLed(address, 7, x, true);
            delay(animationDelay);
        }
    }    

    for (char x = 7; x >= 0; x--) {
        lcTop.setLed(3, x, 0, true);
        lcBottom.setLed(3, x, 7, true);
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
        B01111101,
        B01000101,
        B01010101,
        B01011101
    };
    for (char x = 3; x < 7; x++) {
        lcBottom.setColumn(0, x, GamesAddress0[x-3]);
        delay(animationDelay);
    }
    byte GamesAddress1[] ={
        B01111101,
        B01010001,
        B01010001,
        B01111101,
        B00000001,
        B01111101,
        B00100001,
        B00010001
        
    };
    for (char x = 0; x < 8; x++) {
        lcBottom.setColumn(1, x, GamesAddress1[x]);
        delay(animationDelay);
    }
    byte GamesAddress2[] = {
        B00010001,
        B00100001,
        B01111101,
        B00000001,
        B01111101,
        B01010101,
        B01010101,
        B01010101
    }; 
    for (char x = 0; x < 8; x++) {
        lcBottom.setColumn(2, x, GamesAddress2[x]);
        delay(animationDelay);
    }
    byte GamesAddress3[] = {
        B01110101,
        B01010101,
        B01010101,
        B01011101
    }; 
    for (char x = 1; x < 5; x++) {
        lcBottom.setColumn(3, x, GamesAddress3[x-1]);
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
    
    byte left[] = {
            B10000001,
            B11000001,
            B10100001,
            B10000001,
            B10000001,
            B10000001,
        };
    for (char x = 5; x >= 0; x--) {
        lcTop.setColumn(0, x, left[5-x]);
        lcBottom.setColumn(0, 7-x, left[5-x]);
    }

    byte right[] = {
        B10000001,
        B10000001,
        B10000001,
        B10100001,
        B11000001,
        B10000001
    };
    for (char x = 7; x >= 2; x--) {
        lcTop.setColumn(3, x, right[7-x]);
        lcBottom.setColumn(3, 7-x, right[7-x]);
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
        B00000001,
        B00000001,
        B11110001,
        B00010001,
        B00010001,
        B00010001,
        B11111001,
        B00011001
    };
    for (char x = 7; x >= 0; x--) {
        lcTop.setColumn(1, x, Q_top[7-x]);
        lcBottom.setColumn(1, 7-x, Q_bottom[7-x]);
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
        B00000001,
        B00000001,
        B11110001,
        B11110001,
        B00000001,
        B00000001,
        B00000001,
        B00000001
    };
    for (char x = 7; x >= 0; x--) {
        lcTop.setColumn(2, x, T_top[7-x]);
        lcBottom.setColumn(2, 7-x, T_bottom[7-x]);
    }

    delay(200);
}

void Draw_Menu_Snake() {
    byte S1[] = {
        B00000001,
        B00000001,
        B11110001,
        B11110001,
        B00110001,
        B00110001,
        B00110001,
        B00110001
    };
    for (char x = 7; x >= 0; x--){
        lcTop.setColumn(1, x, S1[7-x]);
        lcBottom.setColumn(1, 7-x, S1[7-x]);
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
        B00110001,
        B00000001,
        B00000001,
        B00000001,
        B00110001,
        B00110001,
        B00000001,
        B00000001
    };
    for (char x = 7; x >= 0; x--){
        lcTop.setColumn(2, x, S2_top[7-x]);
        lcBottom.setColumn(2, 7-x, S2_bottom[7-x]);
    }

    delay(200);
}

void Draw_ExitToMenu() {   
    for (char address = 1; address >= 0; address--) {
        for (char row = 7; row >= 0; row --) {
            lcTop.setColumn(address, 7-row, B00000001);
            lcTop.setColumn(3-address, row, B00000001);
            lcBottom.setColumn(address, row, B00000001);
            lcBottom.setColumn(3-address, 7-row, B00000001);
            delay(animationDelay); 
        }
    }
    for (char i = 6; i >= 0; i--) {
        lcTop.setLed(0, i, 7, true);
        lcTop.setLed(3, i, 0, true);
        lcBottom.setLed(0, i, 0, true);
        lcBottom.setLed(3, i, 7, true);
        delay(animationDelay); 
    }
}

#pragma endregion

#pragma region QuadrumTug

void Draw_QuadrumTug_WinnerBottom () {
    for (char count = 0; count < 3; count++) {
        lcBottom.setColumn(1, 6, B00000000);
        lcBottom.setColumn(1, 5, B00000000);
        lcBottom.setColumn(1, 4, B00000000);
        lcBottom.setColumn(1, 3, B00000000);
        lcBottom.setColumn(1, 2, B00000000);
        lcBottom.setColumn(1, 1, B00000000);
        lcBottom.setColumn(1, 0, B00000000);
        lcBottom.setColumn(0, 7, B00000000);
        lcBottom.setColumn(0, 6, B00000000);
        lcBottom.setColumn(0, 5, B00000000);
        lcBottom.setColumn(0, 4, B00000000);
        lcBottom.setColumn(0, 3, B00000000);
        delay(400);
        lcBottom.setColumn(1, 6, B01111110);
        lcBottom.setColumn(1, 5, B01111110);
        lcBottom.setColumn(1, 4, B01111110);
        lcBottom.setColumn(1, 3, B01111110);
        lcBottom.setColumn(1, 2, B01111110);
        lcBottom.setColumn(1, 1, B01111110);
        lcBottom.setColumn(1, 0, B01111110);
        lcBottom.setColumn(0, 7, B01111110);
        lcBottom.setColumn(0, 6, B01111110);
        lcBottom.setColumn(0, 5, B01111110);
        lcBottom.setColumn(0, 4, B01111110);
        lcBottom.setColumn(0, 3, B01111110);
        delay(400);
    }
}

void Draw_QuadrumTug_WinnerTop () {
    for (char count = 0; count < 3; count ++) {
        lcBottom.setColumn(2, 1, B00000000);
        lcBottom.setColumn(2, 2, B00000000);
        lcBottom.setColumn(2, 3, B00000000);
        lcBottom.setColumn(2, 4, B00000000);
        lcBottom.setColumn(2, 5, B00000000);
        lcBottom.setColumn(2, 6, B00000000);
        lcBottom.setColumn(2, 7, B00000000);
        lcBottom.setColumn(3, 0, B00000000);
        lcBottom.setColumn(3, 1, B00000000);
        lcBottom.setColumn(3, 2, B00000000);
        lcBottom.setColumn(3, 3, B00000000);
        lcBottom.setColumn(3, 4, B00000000);
        delay(400);
        lcBottom.setColumn(2, 1, B01111110);
        lcBottom.setColumn(2, 2, B01111110);
        lcBottom.setColumn(2, 3, B01111110);
        lcBottom.setColumn(2, 4, B01111110);
        lcBottom.setColumn(2, 5, B01111110);
        lcBottom.setColumn(2, 6, B01111110);
        lcBottom.setColumn(2, 7, B01111110);
        lcBottom.setColumn(3, 0, B01111110);
        lcBottom.setColumn(3, 1, B01111110);
        lcBottom.setColumn(3, 2, B01111110);
        lcBottom.setColumn(3, 3, B01111110);
        lcBottom.setColumn(3, 4, B01111110);
        delay(400);
    }
}

void Draw_QuadrumTug_Score (int bottom, int top) {
    if (bottom == 0) {
        lcTop.setColumn(0, 2, B11100000);
        lcTop.setColumn(0, 1, B00100000);
        lcTop.setColumn(0, 0, B00100000);
        lcTop.setColumn(1, 7, B00100000);
        lcTop.setColumn(1, 6, B00100000);
        lcTop.setColumn(1, 5, B00100000);
        lcTop.setColumn(1, 4, B00100000);
        lcTop.setColumn(1, 3, B11100000);

        lcBottom.setColumn(0, 5, B11100000);
        lcBottom.setColumn(0, 6, B00100000);
        lcBottom.setColumn(0, 7, B00100000);
        lcBottom.setColumn(1, 0, B00100000);
        lcBottom.setColumn(1, 1, B00100000);
        lcBottom.setColumn(1, 2, B00100000);
        lcBottom.setColumn(1, 3, B00100000);
        lcBottom.setColumn(1, 4, B11100000);
    } else if (bottom == 1) {
        lcTop.setLed(1, 0, 4, true);
        lcTop.setLed(1, 1, 5, true);

        lcBottom.setLed(1, 0, 4, true);
        lcBottom.setLed(1, 0, 3, true);
        lcBottom.setLed(1, 0, 2, true);
        lcBottom.setLed(1, 0, 1, true);
        lcBottom.setLed(1, 0, 0, true);
        lcBottom.setLed(0, 0, 7, true);
        lcBottom.setLed(0, 0, 6, true);
        lcBottom.setLed(0, 0, 5, true);
    } else if (bottom == 2) {
        lcBottom.setColumn(1, 4, B00111100);
        lcBottom.setColumn(1, 3, B01000010);
        lcBottom.setColumn(1, 2, B00000010);
        lcBottom.setColumn(1, 1, B00000100);
        lcBottom.setColumn(1, 0, B00001000);
        lcBottom.setColumn(0, 7, B00010000);
        lcBottom.setColumn(0, 6, B00100000);
        lcBottom.setColumn(0, 5, B01111110);
    } else if (bottom == 3) {
        lcBottom.setColumn(1, 4, B01111100);
        lcBottom.setColumn(1, 3, B00000010);
        lcBottom.setColumn(1, 2, B00000010);
        lcBottom.setColumn(1, 1, B01111100);
        lcBottom.setColumn(1, 0, B00000010);
        lcBottom.setColumn(0, 7, B00000010);
        lcBottom.setColumn(0, 6, B00000010);
        lcBottom.setColumn(0, 5, B01111100);
    } else if (bottom == 4) {
        lcBottom.setColumn(1, 4, B01000010);
        lcBottom.setColumn(1, 3, B01000010);
        lcBottom.setColumn(1, 2, B01000010);
        lcBottom.setColumn(1, 1, B01000010);
        lcBottom.setColumn(1, 0, B00111110);
        lcBottom.setColumn(0, 7, B00000010);
        lcBottom.setColumn(0, 6, B00000010);
        lcBottom.setColumn(0, 5, B00000010);
    } else if (bottom == 5) {
        lcBottom.setColumn(1, 4, B01111110);
        lcBottom.setColumn(1, 3, B01000000);
        lcBottom.setColumn(1, 2, B01000000);
        lcBottom.setColumn(1, 1, B00111100);
        lcBottom.setColumn(1, 0, B00000010);
        lcBottom.setColumn(0, 7, B00000010);
        lcBottom.setColumn(0, 6, B00000010);
        lcBottom.setColumn(0, 5, B01111100);
    }

    if (top == 0) {
        lcTop.setColumn(2, 4, B11100000);
        lcTop.setColumn(2, 3, B00100000);
        lcTop.setColumn(2, 2, B00100000);
        lcTop.setColumn(2, 1, B00100000);
        lcTop.setColumn(2, 0, B00100000);
        lcTop.setColumn(3, 7, B00100000);
        lcTop.setColumn(3, 6, B00100000);
        lcTop.setColumn(3, 5, B11100000);

        lcBottom.setColumn(2, 3, B11100000);
        lcBottom.setColumn(2, 4, B00100000);
        lcBottom.setColumn(2, 5, B00100000);
        lcBottom.setColumn(2, 6, B00100000);
        lcBottom.setColumn(2, 7, B00100000);
        lcBottom.setColumn(3, 0, B00100000);
        lcBottom.setColumn(3, 1, B00100000);
        lcBottom.setColumn(3, 2, B11100000);
    } else if (top == 1) {
        lcTop.setLed(2, 0, 0, true);
        lcTop.setLed(2, 0, 1, true);
        lcTop.setLed(2, 0, 2, true);
        lcTop.setLed(2, 0, 3, true);
        lcTop.setLed(2, 0, 4, true);
        lcTop.setLed(3, 0, 7, true);
        lcTop.setLed(3, 0, 6, true);
        lcTop.setLed(3, 0, 5, true);

        lcBottom.setLed(2, 0, 4, true);
        lcBottom.setLed(2, 1, 5, true);
    } else if (top == 2) {
        lcBottom.setColumn(2, 3, B00111100);
        lcBottom.setColumn(2, 4, B01000010);
        lcBottom.setColumn(2, 5, B01000000);
        lcBottom.setColumn(2, 6, B00100000);
        lcBottom.setColumn(2, 7, B00010000);
        lcBottom.setColumn(3, 0, B00001000);
        lcBottom.setColumn(3, 1, B00000100);
        lcBottom.setColumn(3, 2, B01111110);
    } else if (top == 3) {
        lcBottom.setColumn(2, 3, B00111110);
        lcBottom.setColumn(2, 4, B01000000);
        lcBottom.setColumn(2, 5, B01000000);
        lcBottom.setColumn(2, 6, B00111110);
        lcBottom.setColumn(2, 7, B01000000);
        lcBottom.setColumn(3, 0, B01000000);
        lcBottom.setColumn(3, 1, B01000000);
        lcBottom.setColumn(3, 2, B00111110);
    } else if (top == 4) {
        lcBottom.setColumn(2, 3, B01000010);
        lcBottom.setColumn(2, 4, B01000010);
        lcBottom.setColumn(2, 5, B01000010);
        lcBottom.setColumn(2, 6, B01000010);
        lcBottom.setColumn(2, 7, B01111100);
        lcBottom.setColumn(3, 0, B01000000);
        lcBottom.setColumn(3, 1, B01000000);
        lcBottom.setColumn(3, 2, B01000000);
    } else if (top == 5) {
        lcBottom.setColumn(2, 3, B01111110);
        lcBottom.setColumn(2, 4, B00000010);
        lcBottom.setColumn(2, 5, B00000010);
        lcBottom.setColumn(2, 6, B00111100);
        lcBottom.setColumn(2, 7, B01000000);
        lcBottom.setColumn(3, 0, B01000000);
        lcBottom.setColumn(3, 1, B01000000);
        lcBottom.setColumn(3, 2, B00111110);
    }
}

void Draw_QuadrumTug_ClearBottom() {
    SetFullColumnOff(0, 1, 6);
    SetFullColumnOff(0, 1, 5);
    SetFullColumnOff(0, 1, 4);
    SetFullColumnOff(0, 1, 3);
    SetFullColumnOff(0, 1, 2);
    SetFullColumnOff(0, 1, 1);
    SetFullColumnOff(0, 1, 0);
    SetFullColumnOff(1, 1, 1);
    SetFullColumnOff(1, 1, 2);
    SetFullColumnOff(1, 1, 3);
    SetFullColumnOff(1, 1, 4);
    SetFullColumnOff(1, 1, 5);
    SetFullColumnOff(1, 1, 6);
    SetFullColumnOff(1, 1, 7);

    SetFullColumnOff(0, 0, 7);
    SetFullColumnOff(0, 0, 6);
    SetFullColumnOff(0, 0, 5);
    SetFullColumnOff(0, 0, 4);
    SetFullColumnOff(0, 0, 3);
    SetFullColumnOff(1, 0, 0);
    SetFullColumnOff(1, 0, 1);
    SetFullColumnOff(1, 0, 2);
    SetFullColumnOff(1, 0, 3);
    SetFullColumnOff(1, 0, 4);
}

void Draw_QuadrumTug_ClearTop() {
    SetFullColumnOff(0, 2, 1);
    SetFullColumnOff(0, 2, 2);
    SetFullColumnOff(0, 2, 3);
    SetFullColumnOff(0, 2, 4);
    SetFullColumnOff(0, 2, 5);
    SetFullColumnOff(0, 2, 6);
    SetFullColumnOff(0, 2, 7);
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
    SetFullColumnOff(0, 3, 0);
    SetFullColumnOff(0, 3, 1);
    SetFullColumnOff(0, 3, 2);
    SetFullColumnOff(0, 3, 3);
    SetFullColumnOff(0, 3, 4);
}

#pragma endregion
