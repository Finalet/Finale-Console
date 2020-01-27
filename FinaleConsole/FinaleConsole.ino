#include "FinaleLEDLib.h"
#include <TimedAction.h>
#include "Variables.h"

#define buttonBottomLeft 2
#define buttonBottomRight 3
#define buttonTopLeft 4
#define buttonTopRight 5

#define potentiomentr1 A0

int gameNumber = 0; //Menu = 0, QuadrumTug = 1
int menuNumber = 0; //QuadrumTug = 0; Dummy = 1

void setup () {
    Serial.begin(9600);

    pinMode(buttonBottomLeft, INPUT);
    pinMode(buttonBottomRight, INPUT);

    //LED Matrix setup
    for (int address = 0; address < 4; address ++) {
        lc.shutdown(address, false);
        lc.setIntensity(address, 1);
        lc.clearDisplay(address);
    }
    StartUpAnimation();
}

#pragma region Menu

bool isArrowsDrawn = false;
bool isMenuUpdated = false;
void Menu_Display() {
    if (isArrowsDrawn == false) {
        Draw_Menu_Arrows();
        isArrowsDrawn = true;
    } 
    if (isMenuUpdated == false) {
        if (menuNumber == 0) {
            Draw_Menu_QT();
            isMenuUpdated = true;
        } else {
            Draw_Menu_Dummy();
            isMenuUpdated = true;
        }
    } 
}

void Menu() {
    if (menuNumber == 0) {
        if (digitalRead(buttonTopLeft) == HIGH) {
            menuNumber ++; 
            isMenuUpdated = false;
        } else if (digitalRead(buttonTopRight) == HIGH) {
            menuNumber ++;
            isMenuUpdated = false;
        } else if (digitalRead(buttonBottomLeft) == HIGH || digitalRead(buttonBottomRight) == HIGH) { //QuadrumTug
            gameNumber = 1;
        }
    } else if (menuNumber == 1) {
        if (digitalRead(buttonTopLeft) == HIGH) {
            menuNumber --; 
            isMenuUpdated = false;
        } else if (digitalRead(buttonTopRight) == HIGH) {
            menuNumber --;
            isMenuUpdated = false;
        } else if (digitalRead(buttonBottomLeft) == HIGH || digitalRead(buttonBottomRight) == HIGH) { //DUMMY

        }
    }
    Menu_Display();
}

#pragma endregion

#pragma region QuadrumTug   //QuadrumTug game

int sideBottom = 0;
int sideTop = 0;
int winningScale = 0;
bool quadrumTug_Launched = false;
bool isScoreDisplayed = false;
bool PVEMode = false;
int AIDifficulty = 1; // 1-8

int topScore = 0;
int bottomScore = 0;

TimedAction reduceScl = TimedAction(1000, QuadrumTug_ReduceScale);
TimedAction AI = TimedAction (9000, QuadrumTug_PVEAI);

void QuadrumTug_PVPButtons(button btn) {
    if (btn == BottomLeft) {
        if (sideBottom == 0) {
            winningScale += 3;
        } else {
            winningScale -= 3;
        }
        QuadrumTug_AssignPVPBottom();
    } else if (btn == BottomRight) {
        if (sideBottom == 1) {
            winningScale += 3;
        } else {
            winningScale -= 3;
        }
        QuadrumTug_AssignPVPBottom();
    } else if (btn == TopLeft) {
        if (sideTop == 0) {
            winningScale -= 3;
        } else {
            winningScale += 3;
        }
        QuadrumTug_AssignPVPTop();
    } else if (btn == TopRight) {
        if (sideTop == 1){
            winningScale -= 3;
        } else {
            winningScale += 3;
        }
        QuadrumTug_AssignPVPTop();
    }

    QuadrumTug_UpdateLED();

    if (winningScale >= 12) {
        delay(400);
        bottomScore++;
        Draw_QuadrumTug_WinnerBottom();
        QuadrumTug_Reset();
    } else if (winningScale <= -12) {
        delay(400);
        topScore++;
        Draw_QuadrumTug_WinnerTop();
        QuadrumTug_Reset();
    }

} 

void QuadrumTug_ReduceScale() {
    if (winningScale > 0) {
        winningScale--;
        QuadrumTug_UpdateLED();
    } else if (winningScale < 0 && PVEMode == false) {
        winningScale ++;
        QuadrumTug_UpdateLED();
    }
}
void QuadrumTug_CheckButtonPress() {
    if (digitalRead(buttonBottomLeft) == HIGH) {
        QuadrumTug_PVPButtons(BottomLeft);
        reduceScl.reset();
    } else if (digitalRead(buttonBottomRight) == HIGH) {
        QuadrumTug_PVPButtons(BottomRight);
        reduceScl.reset();
    } else if (digitalRead(buttonTopLeft) == HIGH && PVEMode == false) {
        QuadrumTug_PVPButtons(TopLeft);
        reduceScl.reset();
    } else if (digitalRead(buttonTopRight) == HIGH && PVEMode == false) {
        QuadrumTug_PVPButtons(TopRight);
        reduceScl.reset();
    } else {
        reduceScl.check();
    }
}

void QuadrumTug_AssignPVPBottom () {
    int x = random(2);  
    if (x == 0) { //Left
        lc.setColumn(0, 0, B11110000);
        lc.setColumn(0, 1, B11110000);
        sideBottom = 0;
    } else { //Right
        lc.setColumn(0, 0, B00001111);
        lc.setColumn(0, 1, B00001111);
        sideBottom = 1;
    }
}

void QuadrumTug_AssignPVPTop () {
    if (PVEMode == false) {
        int x = random(2);  
        if (x == 0) { //Left
            lc.setColumn(3, 6, B11110000);
            lc.setColumn(3, 7, B11110000);
            sideTop = 0;
        } else { //Right
            lc.setColumn(3, 6, B00001111);
            lc.setColumn(3, 7, B00001111);
            sideTop = 1;
        }
    } else {
        lc.setColumn(3, 5, B11111111);
        lc.setColumn(3, 6, B00000000);
        lc.setColumn(3, 7, B00000000);
    }
    
}

void QuadrumTug_PVEAI() {
    winningScale -= 3;

    QuadrumTug_UpdateLED();

    if (winningScale <= -12) {
        AI.disable();
        delay(400);
        topScore++;
        Draw_QuadrumTug_WinnerTop();
        QuadrumTug_Reset();
    }
}

void QuadrumTug_UpdateLED () {
    int address = 0;
    int count = winningScale;
    for (int i = 0; i < 12; i++)
    {
        if (winningScale <= 7 && winningScale > 0) {
            SetFullColumnOff(2, 1);
            SetFullColumnOff(2, 2);
            if (count > 0) {
                address = 1;
                lc.setColumn(address, 6-i, B01111110);
                count --;
            } else {
                SetFullColumnOff(address, 6-i);
                SetFullColumnOff(0, 14-i);
                if (isScoreDisplayed == true) { Draw_QuadrumTug_ClearTop(); isScoreDisplayed = false; }
            }
        } else if (winningScale >7) {
            lc.setColumn(1, 0, B01111110);
            lc.setColumn(1, 1, B01111110);
            if (count > 0) {
                address = 0;
                lc.setColumn(address, 14-i, B01111110);
                count --;
            } else {
                SetFullColumnOff(address, 14-i);
            }
        } else if (winningScale == 0) {
            SetFullColumnOff(1, 4);
            SetFullColumnOff(1, 5);
            SetFullColumnOff(1, 6);

            SetFullColumnOff(2, 1);
            SetFullColumnOff(2, 2);
            SetFullColumnOff(2, 3);
        } else if (winningScale >= -7 && winningScale < 0) {
            SetFullColumnOff(1, 6);
            SetFullColumnOff(1, 5);
            if  (count < 0) {
                address = 2;
                lc.setColumn(address, i+1, B01111110);
                count ++;
            } else {
                SetFullColumnOff(address, i+1);
                SetFullColumnOff(3, i-7);
                if (isScoreDisplayed == true) { Draw_QuadrumTug_ClearBottom(); isScoreDisplayed = false; }
            }
        } else if (winningScale < -7) {
            lc.setColumn(2, 7, B01111110);
            lc.setColumn(2, 6, B01111110);
            if (count < 0) {
                address = 3;
                lc.setColumn(address, i-7, B01111110);
                count ++;
            } else {
                SetFullColumnOff(address, i-7);
            }
        }
    }
    
}

void QuadrumTug_Reset() {
    quadrumTug_Launched = false;
}

void QuadrumTug_ReadPotentiometr1 () {
    AIDifficulty = analogRead(potentiomentr1) * 10/1023;
    if (AIDifficulty > 2) {
        PVEMode = true;
    } else {
        PVEMode = false;
    }
}
bool assignedAfterPVE = false;
void QuadrumTug_Launch () {
    if (quadrumTug_Launched == false){
        AllLEDOff();
        Draw_QuadrumTug_Score(bottomScore, topScore);
        isScoreDisplayed = true;
        winningScale = 0;
        winningScale = constrain(winningScale, -12, 12);

        SetFullColumnOn(1, 7);
        SetFullColumnOn(2, 0);
        SetFullColumnOn(0, 2); //Bottom playarea edge
        SetFullColumnOn(3, 5); //Top playarea edge
        //Start PVP
        QuadrumTug_AssignPVPBottom();
        QuadrumTug_AssignPVPTop();

        delay (1000); 

        if (bottomScore == 5 || topScore == 5) {
            delay (2000);
            bottomScore = 0;
            topScore = 0;
            QuadrumTug_Reset();
        } else {
            quadrumTug_Launched = true;
        }
    } else {
        QuadrumTug_CheckButtonPress();
        QuadrumTug_ReadPotentiometr1();
        if (PVEMode == true) {
            QuadrumTug_AssignPVPTop();
            AI.setInterval(7000/AIDifficulty); //Change difficulty
            AI.enable();
            AI.check();
            assignedAfterPVE = false;
        } else {
            if (assignedAfterPVE == false) {
                QuadrumTug_AssignPVPTop();
                assignedAfterPVE = true;
            }
            AI.disable();
        }
    }
    
}

#pragma endregion 

#pragma region Background 

TimedAction backgroundTimer = TimedAction(3000, Background_ExitToMenu);

void Background_ExitToMenu () {
    if (gameNumber == 1) {
        quadrumTug_Launched = false;
    }
    gameNumber = 0;
    isMenuUpdated = false;
    isArrowsDrawn = false;
    Draw_ExitToMenu();
}
bool enalbed = false;

void Background_CheckHomeButton () {
    if (digitalRead(buttonBottomLeft) == HIGH && digitalRead(buttonBottomRight) == HIGH && gameNumber != 0) {
        if(enalbed == false) {
            backgroundTimer.enable();
            enalbed = true;
        } 
        backgroundTimer.check();
    } else {
        enalbed = false;
        backgroundTimer.reset();
        backgroundTimer.disable();
    }
}

#pragma endregion

void loop() {
    if (gameNumber == 0) {
        Menu();
    } else if (gameNumber == 1) {
        QuadrumTug_Launch();
    }
    Serial.println(gameNumber);

    Background_CheckHomeButton();
}

