#include <stdio.h>
#include <stdlib.h>//system, sleep
#include <Windows.h>//SetConsoleCursorPosition, GetStdHandle, STD_OUTPUT_HANDLE
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib") //������ Ʋ�� ���� �������

#define WIDTH 60
#define HEIGHT 30 //���� ȭ���� ũ�⸦ �����ϴ� �Լ�

int exit_ = 1; //���� ���ῡ ���Ǵ� ����
double score = 0; //�� ����
int count_f = 0; //f������ ���� ��
int count_g = 0; //���� �г⿡�� ȹ���� ���� ����
int totalcount = 0; //�� ȹ���� ���� ����
int grade = 1; //�г�
int dt = 60;

typedef struct
{
    int x;
}Player; //�÷��̾� ����ü

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
}A; //�� �������� ����ü

typedef struct
{
    int x;
    int y;
    int act;
}Vadcation; //���� ������ ����ü

typedef struct
{
    int x;
    int y;
    int act;
}Retake; //����� ������ ����ü

typedef struct
{
    int x;
    int y;
    int act;
}Hotsix; //�ֽĽ� ������ ����ü