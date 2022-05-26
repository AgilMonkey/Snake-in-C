#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <unistd.h>
#include <conio.h>

const int width = 30;
const int height = 20;

int i, j;
int gameover, score;
int x, y, fruitx, fruity, flag = 1;
int snakeBodyL = 600;
int whatBodynow = 580;


struct snakeBody {
    int isOn;
    int posX;
    int posY;
};

struct snakeBody Bodies[600];

/*
    1 = left, 2 = up, 3 = down, 4 = right
*/

int CheckIfHittingBody(int _x, int _y);
int DrawBodies(int _x, int _y);

//Function to draw the screen
void draw(){
    //Draw the boundary

    system("cls");
    for(i = 0; i < height; i++){
        for(j = 0; j < width; j++){
            if(i == 0 || i == height - 1 || j == 0 || j == width - 1){
                printf("#");
            }
            else {
                if (i == y && j == x){
                    printf("@");
                } else if (DrawBodies(j, i)){
                    printf("0");
                } else if (i == fruity && j == fruitx){
                    printf("Q");
                }else {
                    printf(" ");
                }
            }
        }
        printf("\n");
    }

    printf("Score = %d\n", score);
    printf("Press x to quit the game");

}

void setup(){
    gameover = 0;

    x = width/2;
    y = height/2;

    whatBodynow = 580;

    generateFruit();
}

void generateFruit(){
    fruitx = rand()%width;
    if (fruitx <= 0){
        fruitx = 2;
    } else if (fruitx >= width-1){
        fruitx = width - 2;
    }
    fruity = rand()%height;
    if (fruity <= 0){
        fruity = 2;
    } else if (fruity >= height-1){
        fruity = height - 2;
    }
}

void input(){
    if (kbhit()){
        switch (getch()){
        case 'a':   //left
            if (flag != 4) flag = 1;
            break;
        case 'w':   //up
            if (flag != 3) flag = 2;
            break;
        case 's':   //down
            if (flag != 2) flag = 3;
            break;
        case 'd':   // right
            if (flag != 1)  flag = 4;
            break;
        case 'x':   //exit
            gameover = 1;
            break;
        }
    }
}

void logic(){
    //Determine last pos
    setPos(&Bodies[whatBodynow], x, y);
    whatBodynow++;
    if(whatBodynow >= snakeBodyL) whatBodynow = 0;

    //Player movement
    switch (flag){
    case 1:
        x--;
        break;
    case 2:
        y--;
        break;
    case 3:
        y++;
        break;
    case 4:
        x++;
        break;
    }

    //When snake got point
    if (x == fruitx && y == fruity){
        score++;
        generateFruit();
    }

    //game over
    if (y <= 0 || y >= height-1 || x <= 0 || x >= width-1){
        gameover = 1;
    }
    if (CheckIfHittingBody(x, y)) gameover = 1;

    //DEbug
    //printf("\n\n body = %d", whatBodynow);
}

void setPos(struct snakeBody body, int _x, int _y){
    body.posX = _x;
    body.posY = _y;
}

int DrawBodies(int _x, int _y){
    return CheckIfHittingBody(_x, _y);
}

int bodyRightBefore;
int CheckIfHittingBody(int _x, int _y){
    int i;
    for (i = 0; i < score; i++){
        bodyRightBefore = whatBodynow - i - 1;
        if (bodyRightBefore < 0) bodyRightBefore = bodyRightBefore + snakeBodyL;//If minus
        if(Bodies[bodyRightBefore].posX == _x && Bodies[bodyRightBefore].posY == _y){
            return 1;
        }
    }

    return 0;
}

int main()
{
    setup();
    while(gameover == 0){
        draw();
        input();
        logic();
        sleep(0.8);
    }
    printf("\n\nYou lose, press enter to quit...");
    scanf("%c");


    return 0;
}
