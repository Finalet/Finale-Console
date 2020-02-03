#include "FinaleLEDLib.h"
#include <TimedAction.h>
#include "Variables.h"

#define buttonBottomLeft 2
#define buttonBottomRight 3
#define buttonTopLeft 4
#define buttonTopRight 5

#define potentiomentr1 A0

char gameNumber = 0; //Menu = 0, QuadrumTug = 1, Snake = 2, Stack up = 3
char menuNumber; //QuadrumTug = 0, Snake = 1, Stack up = 2

void setup () {
    Serial.begin(9600);

    pinMode(buttonBottomLeft, INPUT_PULLUP);
    pinMode(buttonBottomRight, INPUT_PULLUP);
    pinMode(buttonTopLeft, INPUT_PULLUP);
    pinMode(buttonTopRight, INPUT_PULLUP);

    //LED Matrix setup
    for (int address = 0; address < 4; address ++) {
        lcBottom.shutdown(address, false);
        lcBottom.setIntensity(address, 8);
        lcBottom.clearDisplay(address);

        lcTop.shutdown(address, false);
        lcTop.setIntensity(address, 8);
        lcTop.clearDisplay(address);
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
        } else if (menuNumber == 1) {
            Draw_Menu_Snake();
            isMenuUpdated = true;
        } else if (menuNumber == 2){
            Draw_Menu_SU();
            isMenuUpdated = true;
        }
    } 
}

void Menu() {
    if (menuNumber == 0) {
        if (digitalRead(buttonTopLeft) == LOW) {
            menuNumber = 2; 
            isMenuUpdated = false;
        } else if (digitalRead(buttonTopRight) == LOW) {
            menuNumber ++;
            isMenuUpdated = false;
        } else if (digitalRead(buttonBottomLeft) == LOW || digitalRead(buttonBottomRight) == LOW) { //QuadrumTug
            gameNumber = 1;
        }
    } else if (menuNumber == 1) {
        if (digitalRead(buttonTopLeft) == LOW) {
            menuNumber --; 
            isMenuUpdated = false;
        } else if (digitalRead(buttonTopRight) == LOW) {
            menuNumber ++;
            isMenuUpdated = false;
        } else if (digitalRead(buttonBottomLeft) == LOW || digitalRead(buttonBottomRight) == LOW) { //Snake
            gameNumber = 2;
        }
    } else if (menuNumber == 2) {
        if (digitalRead(buttonTopLeft) == LOW) {
            menuNumber--; 
            isMenuUpdated = false;
        } else if (digitalRead(buttonTopRight) == LOW) {
            menuNumber = 0;
            isMenuUpdated = false;
        } else if (digitalRead(buttonBottomLeft) == LOW || digitalRead(buttonBottomRight) == LOW) { //Snake
            gameNumber = 3;
        }
    }
    Menu_Display();
}

#pragma endregion

#pragma region QuadrumTug   //QuadrumTug game

char sideBottom = 0;
char sideTop = 0;
char winningScale = 0;
bool quadrumTug_Launched = false;
bool isScoreDisplayed = false;
bool PVEMode = false;
char AIDifficulty = 1; // 1-8

char topScore = 0;
char bottomScore = 0;
bool released = false;
bool released1 = false;
bool released2 = false;
bool released3 = false;

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
        released = false;
    }
    if (digitalRead(buttonBottomRight) == HIGH) {
        released1 = false;
    }
    if (digitalRead(buttonTopLeft) == HIGH) {
        released2 = false;
    }
    if (digitalRead(buttonTopRight) == HIGH) {
        released3 = false;
    } 

    if (digitalRead(buttonBottomLeft) == LOW && released == false) {
        QuadrumTug_PVPButtons(BottomLeft);
        reduceScl.reset();
        released = true;
    } else if (digitalRead(buttonBottomRight) == LOW && released1 == false) {
        QuadrumTug_PVPButtons(BottomRight);
        reduceScl.reset();
        released1 = true;
    } else if (digitalRead(buttonTopLeft) == LOW && PVEMode == false && released2 == false) {
        QuadrumTug_PVPButtons(TopLeft);
        reduceScl.reset();
        released2 = true;
    } else if (digitalRead(buttonTopRight) == LOW && PVEMode == false && released3 == false) {
        QuadrumTug_PVPButtons(TopRight);
        reduceScl.reset();
        released3 = true;
    } else {
        reduceScl.check();
    }
}

void QuadrumTug_AssignPVPBottom () {
    int x = random(2);  
    if (x == 0) { //Left
        lcBottom.setColumn(0, 6, B00000000);
        lcBottom.setColumn(0, 7, B00000000);
        lcTop.setColumn(0, 6, B11111111);
        lcTop.setColumn(0, 7, B11111111);
        sideBottom = 0;
    } else { //Right
        lcBottom.setColumn(0, 6, B11111111);
        lcBottom.setColumn(0, 7, B11111111);
        lcTop.setColumn(0, 6, B00000000);
        lcTop.setColumn(0, 7, B00000000);
        sideBottom = 1;
    }
}

void QuadrumTug_AssignPVPTop () {
    if (PVEMode == false) {
        int x = random(2);  
        if (x == 0) { //Left
            lcBottom.setColumn(3, 0, B11111111);
            lcBottom.setColumn(3, 1, B11111111);
            lcTop.setColumn(3, 0, B00000000);
            lcTop.setColumn(3, 1, B00000000);
            sideTop = 0;
        } else { //Right
            lcBottom.setColumn(3, 0, B00000000);
            lcBottom.setColumn(3, 1, B00000000);
            lcTop.setColumn(3, 0, B11111111);
            lcTop.setColumn(3, 1, B11111111);
            sideTop = 1;
        }
    } else {
        lcBottom.setColumn(3, 2, B11111111);
        lcBottom.setColumn(3, 1, B00000000);
        lcBottom.setColumn(3, 0, B00000000);
        lcTop.setColumn(3, 2, B11111111);
        lcTop.setColumn(3, 1, B00000000);
        lcTop.setColumn(3, 0, B00000000);
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
            SetFullColumnOff(0, 2, 6);  SetFullColumnOff(1, 2, 6);
            SetFullColumnOff(0, 2, 5);  SetFullColumnOff(1, 2, 5);
            if (count > 0) {
                address = 1;
                lcTop.setColumn(address, i+1, B11111110);
                lcBottom.setColumn(address, i+1, B01111111);
                count --;
            } else {
                SetFullColumnOff(0, address, i+1);  SetFullColumnOff(1, address, i+1);
                SetFullColumnOff(0, 0, i-7);   SetFullColumnOff(1, 0, i-7);
                if (isScoreDisplayed == true) { Draw_QuadrumTug_ClearTop(); isScoreDisplayed = false; }
            }
        } else if (winningScale >7) {
            lcTop.setColumn(1, 7, B11111110);
            lcTop.setColumn(1, 6, B11111110);
            lcBottom.setColumn(1, 7, B01111111);
            lcBottom.setColumn(1, 6, B01111111);
            if (count > 0) {
                address = 0;
                lcTop.setColumn(address, i-7, B11111110);
                lcBottom.setColumn(address, i-7, B01111111);
                count --;
            } else {
                SetFullColumnOff(1, address, i-7);
                SetFullColumnOff(0, address, i-7);
            }
        } else if (winningScale == 0) {
            SetFullColumnOff(0, 1, 3);  SetFullColumnOff(1, 1, 3);
            SetFullColumnOff(0, 1, 2);  SetFullColumnOff(1, 1, 2);
            SetFullColumnOff(0, 1, 1);  SetFullColumnOff(1, 1, 1);

            SetFullColumnOff(0, 2, 6);  SetFullColumnOff(1, 2, 6);
            SetFullColumnOff(0, 2, 5);  SetFullColumnOff(1, 2, 5);
            SetFullColumnOff(0, 2, 4);  SetFullColumnOff(1, 2, 4);
        } else if (winningScale >= -7 && winningScale < 0) {
            SetFullColumnOff(0, 1, 1);  SetFullColumnOff(1, 1, 1);
            SetFullColumnOff(0, 1, 2);  SetFullColumnOff(1, 1, 2);
            if  (count < 0) {
                address = 2;
                lcTop.setColumn(address, 6-i, B11111110);
                lcBottom.setColumn(address, 6-i, B01111111);
                count ++;
            } else {
                SetFullColumnOff(0, address, 6-i);  SetFullColumnOff(1, address, 6-i);
                SetFullColumnOff(0, 3, 14-i);        SetFullColumnOff(1, 3, 14-i);
                if (isScoreDisplayed == true) { Draw_QuadrumTug_ClearBottom(); isScoreDisplayed = false; }
            }
        } else if (winningScale < -7) {
            lcTop.setColumn(2, 0, B11111110);
            lcTop.setColumn(2, 1, B11111110);
            lcBottom.setColumn(2, 0, B01111111);
            lcBottom.setColumn(2, 1, B01111111);
            if (count < 0) {
                address = 3;
                lcTop.setColumn(address, 14-i, B11111110);
                lcBottom.setColumn(address, 14-i, B01111111);
                count ++;
            } else {
                SetFullColumnOff(0, address, 14-i);  SetFullColumnOff(1, address, 14-i);
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

        SetFullColumnOn(0, 1, 0); SetFullColumnOn(1, 1, 0);
        SetFullColumnOn(0, 2, 7); SetFullColumnOn(1, 2, 7);
        SetFullColumnOn(0, 0, 5); SetFullColumnOn(1, 0, 5); //Bottom playarea edge
        SetFullColumnOn(0, 3, 2); SetFullColumnOn(1, 3, 2); //Top playarea edge
        //Start PVP
        QuadrumTug_AssignPVPBottom();
        QuadrumTug_AssignPVPTop();


        if (bottomScore == 5 || topScore == 5) {
            delay (2000);
            bottomScore = 0;
            topScore = 0;
            QuadrumTug_Reset();
        } else {
            delay (1000);
            Draw_QuadrumTug_ClearTop();
            Draw_QuadrumTug_ClearBottom();
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

#pragma region Snake    //Snake game

char speed = 1;

char snakeSize;
char snakeX[256];
char snakeY[256];
direction dir;
bool changedDir;

char foodX;
char foodY;

bool gameOn;
bool isPaused;

unsigned long prevMillis = 0;

char getAddress(char y) {
    char address;
    if (y <= 8) {
        address = 3;
    } else if (y > 8 && y <= 16) {
        address = 2;
    } else if (y > 16 && y <= 24) {
        address = 1;
    } else if (y > 24 && y <= 32) {
        address = 0;
    }
    return address;
}
char adjustedCoordinateX (char x) {
    if (x <= 8) {
        return x;
    } else {
        return x-8;
    }
}
char adjustedCoordinateY (char y) {
    if (y <= 8) {
        return y;
    } else if (y > 8 && y <= 16) {
        return y-8;
    } else if (y > 16 && y <= 24) {
        return y-16;
    } else if (y > 24) {
        return y-24;
    }
}

void Snake_Launch() {
    if (gameOn == false) {  
        for (char i = 0; i < 4; i++) {
            lcTop.clearDisplay(i);
            lcBottom.clearDisplay(i);
        }

        snakeX[0] = 8;
        snakeY[0] = 10;
        dir = down;
        snakeSize = 1;

        Snake_NewFood();
        gameOn = true;
    }

    if (isPaused == true) {
        for (char i = 0; i < 4; i++) {
            lcTop.clearDisplay(i);
            lcBottom.clearDisplay(i);
        }

        Snake_DrawFullSnake();
        Snake_DrawFood();
        isPaused = false;
    }

    Snake_DrawSnake ();
    Snake_DrawFood ();

    Snake_CheckIfOnFood();
    Snake_CheckIfHitSelf();
    Snake_CheckSpeed ();

    if (digitalRead(buttonTopLeft) == HIGH && digitalRead(buttonTopRight) == HIGH) {
        changedDir = false;
    }
    unsigned long currentMillis = millis();
    while (currentMillis - prevMillis <= 1000/speed) {
        if (changedDir == false) {
            Snake_CheckDirection();
        }
        currentMillis = millis();
    } 
    prevMillis = currentMillis;
    Snake_Move();
}

void Snake_CheckDirection () {
    if (digitalRead(buttonTopLeft) == LOW) {
        if (dir == up) {
            dir = left;
        } else if (dir == down) {
            dir = right;
        } else if (dir == left) {
            dir = down;
        } else if (dir == right) {
            dir = up;
        }
        changedDir = true;
    }
    if (digitalRead(buttonTopRight) == LOW) {
        if (dir == up) {
            dir = right;
        } else if (dir == down) {
            dir = left;
        } else if (dir == left) {
            dir = up;
        } else if (dir == right) {
            dir = down;
        }
        changedDir = true;
    }
}

void Snake_CheckSpeed () {
    speed = 1 + analogRead(potentiomentr1) * 15 / 1023;
}

void Snake_Move() {
    for (char i = snakeSize; i > 0; i--) {
        snakeX[i] = snakeX[i-1];
        snakeY[i] = snakeY[i-1];
    }
    if (dir == up) {
        if (snakeY[0] == 32) {
            snakeY[0] = 1;
        } else {
            snakeY[0]++;
        }
    } else if (dir == down) {
        if (snakeY[0] == 1) {
            snakeY[0] = 32;
        } else
        {
           snakeY[0]--;
        }        
    } else if (dir == left) {
        if (snakeX[0] == 1) {
            snakeX[0] = 16;
        } else {
            snakeX[0]--;
        }
    } else if (dir == right) {
        if (snakeX[0] == 16) {
            snakeX[0] = 1;
        } else {
            snakeX[0]++;
        }
    }
}

void Snake_CheckIfOnFood () {
    if(snakeX[0] == foodX && snakeY[0] == foodY) {
        snakeSize++;
        Snake_NewFood();
    }
}

void Snake_CheckIfHitSelf () {
    for (char i = snakeSize; i > 0; i--) {
        if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
            Snake_GameOver();
        }
    }
}

void Snake_DrawSnake() { 
    char lastAddress = getAddress(snakeY[snakeSize]);
    char lastX = adjustedCoordinateX(snakeX[snakeSize]);
    char lastY = adjustedCoordinateY(snakeY[snakeSize]);
    if (snakeX[snakeSize] > 8) {
        lcTop.setLed(lastAddress, lastX-1, lastY-1, false);
    } else {
        lcBottom.setLed(lastAddress, lastX-1, lastY-1, false); 
    }

    char address = getAddress(snakeY[0]);
    char x = adjustedCoordinateX(snakeX[0]);
    char y = adjustedCoordinateY(snakeY[0]);
    if (snakeX[0] > 8) {
        lcTop.setLed(address, x-1, y-1, true);
    } else {
        lcBottom.setLed(address, x-1, y-1, true); 
    }
}

void Snake_BlinkSnake () {
    for (char i = 0; i < snakeSize; i++) {
        char address = getAddress(snakeY[i]);
        char x = adjustedCoordinateX(snakeX[i]);
        char y = adjustedCoordinateY(snakeY[i]);
        if (snakeX[i] > 8) {
            lcTop.setLed(address, x-1, y-1, false);
        } else {
            lcBottom.setLed(address, x-1, y-1, false);
        }
    }
    delay(200); 
    for (char i = 0; i < snakeSize; i++) {
        char address = getAddress(snakeY[i]);
        char x = adjustedCoordinateX(snakeX[i]);
        char y = adjustedCoordinateY(snakeY[i]);
        if (snakeX[i] > 8) {
            lcTop.setLed(address, x-1, y-1, true);
        } else {
            lcBottom.setLed(address, x-1, y-1, true);
        }
    }
    delay(200); 
}

void Snake_DrawFullSnake() {
    for (char i = 0; i < snakeSize; i++) {
        char address = getAddress(snakeY[i]);
        char x = adjustedCoordinateX(snakeX[i]);
        char y = adjustedCoordinateY(snakeY[i]);
        if (snakeX[i] > 8) {
            lcTop.setLed(address, x-1, y-1, true);
        } else {
            lcBottom.setLed(address, x-1, y-1, true);
        }
    }
}

void Snake_DrawFood() {
    char address = getAddress(foodY);
    char x = adjustedCoordinateX(foodX);
    char y = adjustedCoordinateY(foodY);
    if (foodX > 8) {
        lcTop.setLed(address, x-1, y-1, true);
    } else {
        lcBottom.setLed(address, x-1, y-1, true);
    }
}

void Snake_NewFood () {
    foodX = random(1, 17);
    foodY = random(1, 33);
}

void Snake_GameOver() {
    for (char x = 0; x < 5; x++) {
        Snake_BlinkSnake();
    }
    gameOn = false;
}

#pragma endregion

#pragma region StackUp //Stack up game

char stackUpSpeed = 0;

char stackRow = 7;
int prevX;
int currentX;
int length = 8;
direction stackDirection = left;
int stackAddress = 0;

bool isPlaying = false;
bool buttonPressed = false;
bool firstTime = false;

void StackUp_Launch () {
    if (isPlaying == false) {
        for (int i = 0; i < 4; i++) {
            lcBottom.clearDisplay(i);
            lcTop.clearDisplay(i);
            firstTime = false;
        }
        stackRow = 7;
        stackAddress = 0;
        length = 8;
        stackDirection = left;

        isPlaying = true;
    }
    StackUp_Game();
}

void StackUp_Game (){
     while (digitalRead(buttonTopLeft) == HIGH && digitalRead(buttonTopRight) == HIGH) {
        Background_CheckHomeButton();
        if (gameNumber == 0) {
            break;
        }
        StackUp_CheckSpeed();
        delay(1400/(stackUpSpeed+5*stackAddress));
        buttonPressed = false;

        if (currentX < 0) {
            stackDirection = left;
        } else if (currentX > 14 + length) {
            stackDirection = right;
        }

        if (stackDirection == left) {
            currentX++;
            lcTop.setLed(stackAddress, currentX - length - 8, stackRow, false);
            lcBottom.setLed(stackAddress, currentX - length, stackRow, false);
        } else {
            currentX--;
            lcTop.setLed(stackAddress, currentX - 7, stackRow, false);
            lcBottom.setLed(stackAddress, currentX + 1, stackRow, false);
        }
        for (int i = 0; i < length; i++) {
            lcTop.setLed(stackAddress, currentX - i - 8, stackRow, true);
            lcBottom.setLed(stackAddress, currentX - i, stackRow, true);
        }
    }
    if (stackRow < 0) {
        stackAddress++;
        stackRow = 7;
    } 
    if (digitalRead(buttonTopLeft) == LOW || digitalRead(buttonTopRight) == LOW) {
        if (buttonPressed == false) {
            buttonPressed = true;
            if(firstTime == false) {
                firstTime = true;
                prevX = currentX;
            }
            stackRow--;
            StackUp_CheckFall();
        }
    }
}

void StackUp_CheckFall () {
    if (currentX != prevX) {
        for (int i = 0; i < 8; i++) {
            lcTop.setLed(stackAddress, prevX-length-8-i, stackRow+1, false);
            lcBottom.setLed(stackAddress, prevX-length-i, stackRow+1, false);
            lcTop.setLed(stackAddress, prevX-7+i, stackRow+1, false);
            lcBottom.setLed(stackAddress, prevX+1+i, stackRow+1, false);
        }
        length -= abs(currentX - prevX);
        if (currentX > prevX) {
            currentX -= abs(currentX - prevX);
        }
    }
    prevX = currentX;
    currentX = 0;
    if (length <= 0) {
        StackUp_GameOver();
    }
}

void StackUp_GameOver () {
    isPlaying = false;
    while (stackRow >= 0) {
        if (stackRow == 8) {
            stackRow = 0;
            stackAddress--;
        }
        if (stackAddress == -1) {
            break;
        }
        lcTop.setColumn(stackAddress, stackRow, B00000000);
        lcBottom.setColumn(stackAddress, stackRow, B00000000);
        stackRow++;
        delay(100);
    }
}

void StackUp_CheckSpeed() {
    stackUpSpeed = 5 + analogRead(potentiomentr1) * 20 / 1023;
}

#pragma endregion

#pragma region Background 

TimedAction backgroundTimer = TimedAction(3000, Background_ExitToMenu);

void Background_ExitToMenu () {
    if (gameNumber == 1) {
        quadrumTug_Launched = false;
    } else if (gameNumber == 2) {
        isPaused = true;
    } else if (gameNumber == 3) {
        isPlaying = false;
    }
    gameNumber = 0;
    isMenuUpdated = false;
    isArrowsDrawn = false;
    Draw_ExitToMenu();
}
bool enalbed = false;

void Background_CheckHomeButton () {
    if (digitalRead(buttonBottomLeft) == LOW && digitalRead(buttonBottomRight) == LOW && gameNumber != 0) {
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
    } else if (gameNumber == 2) {
        Snake_Launch();
    } else if (gameNumber == 3) {
        StackUp_Launch();
    }
    Background_CheckHomeButton();
}

