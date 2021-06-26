#include <stdio.h>
#include <stdlib.h>//system, sleep
#include <Windows.h>//SetConsoleCursorPosition, GetStdHandle, STD_OUTPUT_HANDLE
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib") //음악을 틀기 위한 헤더파일

#define WIDTH 60
#define HEIGHT 30 //게임 화면의 크기를 조절하는 함수

int exit_ = 1; //게임 종료에 사용되는 변수
double score = 0; //총 점수
int count_f = 0; //f학점을 맞은 수
int count_g = 0; //현재 학년에서 획득한 학점 개수
int totalcount = 0; //총 획득한 학점 개수
int grade = 1; //학년
int dt = 60;

typedef struct
{
    int x;
}Player; //플레이어 구조체

typedef struct
{
    int x;
    int y;
    int act;
}F;

typedef struct
{
    int x;
    int y;
    int act;
}D;

typedef struct
{
    int x;
    int y;
    int act;
}C;

typedef struct
{
    int x;
    int y;
    int act;
}B;

typedef struct
{
    int x;
    int y;
    int act;
}A; //각 학점들의 구조체

typedef struct
{
    int x;
    int y;
    int act;
}Vadcation; //방학 아이템 구조체

typedef struct
{
    int x;
    int y;
    int act;
}Retake; //재수강 아이템 구조체

typedef struct
{
    int x;
    int y;
    int act;
}Hotsix; //핫식스 아이템 구조체