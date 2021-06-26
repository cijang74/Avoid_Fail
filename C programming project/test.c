#include <stdio.h>
#include <stdlib.h> //system, sleep
#include <Windows.h> //SetConsoleCursorPosition, GetStdHandle, STD_OUTPUT_HANDLE

#define WIDTH 60
#define HEIGHT 30 //기존: WIDTH 20, HEIGHT 10, 게임 화면의 크기를 조정

typedef struct //똥과 관련된 값들(구조체)
{
    int x;
    int y;

    int act;
}Poo;

typedef struct //A와 관련된 값들(구조체)
{
    int x;
    int y;

    int act;
}A;

typedef struct //B와 관련된 값들(구조체)
{
    int x;
    int y;

    int act;
}B;

typedef struct //C와 관련된 값들(구조체)
{
    int x;
    int y;

    int act;
}C;

typedef struct //D와 관련된 값들(구조체)
{
    int x;
    int y;

    int act;
}D;

typedef struct // 플레이어와 관련된 값들(구조체)
{
    int x;
}Player;

Poo poo[WIDTH];

A a[WIDTH];

B b[WIDTH];

C c[WIDTH];

D d[WIDTH];

Player player;

void gotoxy(int x, int y) //콘솔 좌표계를 설정해주는 함수
{
    COORD pos = { 2 * x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int isKeyDown(int key) //특정 키를 눌렀는지 확인하는 함수, 맞으면 1 반환
{
    return ((GetAsyncKeyState(key) & 0x8000) != 0);
}

void init() //
{
    int i;

    for (i = 0; i < WIDTH; i++)
        poo[i].act = FALSE; //모든 똥을 비활성화 시킴

    player.x = WIDTH / 2; //플레이어의 처음 위치를 가로값/2로 설정
}

void CreatePoo() //똥을 생성하는 함수
{
    int i_p, i_a, i_b, limit = 0;

    for (i_p = 0; i_p < WIDTH; i_p++) //똥이 생성될 위치 범위
    {
        limit = rand();

        if (limit < 20000)
        {
            if (!poo[i_p].act) //만약 i번째 똥이 비활성화 상태라면
            {
                poo[i_p].x = rand() % WIDTH; //똥이 생성될 x값의 위치는 무작위수를 가로값으로 나눈 값의 나머지
                poo[i_p].y = HEIGHT - 1; //똥이 생성될 y값의 위치는 높이값 - 1

                poo[i_p].act = TRUE; //i번째 똥 활성화

                break;
            }
        }
    }

    for (i_a = 0; i_a < WIDTH; i_a++) //A가 생성될 위치 범위
    {
        limit = rand(); //높은 등급일 수록 적게 나오게 하기 위한 기능을 구현하는데에 쓰이는 함수

        if (limit < 50) //만약 limit가 50 이하라면(RAND_MAX = 32767 이므로 50 이하의 숫자가 나올 확률은 적다.)
        {
            if (!a[i_a].act) //만약 i번째 A가 비활성화 상태라면
            {
                a[i_a].x = rand() % WIDTH; //A가 생성될 x값의 위치는 무작위수를 가로값으로 나눈 값의 나머지
                a[i_a].y = HEIGHT - 1; //A가 생성될 y값의 위치는 높이값 - 1

                if ((a[i_a].x != a[i_p].x) && (a[i_a].y != a[i_p].y)) //만약에 A가 다른 오브젝트와 안 겹친다면
                {
                    a[i_a].act = TRUE; //i번째 A 활성화
                }
                return;
            }
        }
    }


    for (i_b = 0; i_b < WIDTH; i_b++) //A가 생성될 위치 범위
    {
        limit = rand(); //높은 등급일 수록 적게 나오게 하기 위한 기능을 구현하는데에 쓰이는 함수

        if (limit < 1000) //만약 limit가 50 이하라면(RAND_MAX = 32767 이므로 50 이하의 숫자가 나올 확률은 적다.)
        {
            if (!b[i_b].act) //만약 i번째 A가 비활성화 상태라면
            {
                b[i_b].x = rand() % WIDTH; //A가 생성될 x값의 위치는 무작위수를 가로값으로 나눈 값의 나머지
                b[i_b].y = HEIGHT - 1; //A가 생성될 y값의 위치는 높이값 - 1

                if ((b[i_b].x != b[i_p].x) && (b[i_b].y != b[i_p].y) &&
                    (b[i_b].x != a[i_a].x) && (b[i_b].y != a[i_a].y)
                    ) //만약에 B가 다른 오브젝트와 안 겹친다면
                {
                    b[i_b].act = TRUE; //i번째 A 활성화
                }
                return;
            }
        }
    }
}

void MovePoo()
{
    int i_p, i_a, i_b;
    for (i_p = 0; i_p < WIDTH; i_p++)
    {
        if (poo[i_p].act) //i번째 똥이 활성화 상태라면
        {
            poo[i_p].y--; //i값만큼 떨어뜨림
        }
    }

    for (i_a = 0; i_a < WIDTH; i_a++)
    {
        if (a[i_a].act) //i번째 A가 활성화 상태라면
        {
            a[i_a].y--; //i값만큼 떨어뜨림
        }
    }

    for (i_b = 0; i_b < WIDTH; i_b++)
    {
        if (b[i_b].act) //i번째 A가 활성화 상태라면
        {
            b[i_b].y--; //i값만큼 떨어뜨림
        }
    }
}

void DeletePoo() //똥을 없애는 함수
{
    int i_p, i_a, i_b, i_c, i_d;

    for (i_p = 0; i_p < WIDTH; i_p++)
    {
        if (poo[i_p].act && poo[i_p].y < 0) //활성화된 똥의 Y값이 0 미만일 때
        {
            poo[i_p].act = FALSE; //똥을 비활성화
        }
    }

    for (i_a = 0; i_a < WIDTH; i_a++)
    {
        if (a[i_a].act && a[i_a].y < 0) //활성화된 똥의 Y값이 0 미만일 때
        {
            a[i_a].act = FALSE; //똥을 비활성화
        }
    }

    for (i_b = 0; i_b < WIDTH; i_b++)
    {
        if (b[i_b].act && b[i_b].y < 0) //활성화된 똥의 Y값이 0 미만일 때
        {
            b[i_b].act = FALSE; //똥을 비활성화
        }
    }
}

int PlayerContainsPoo() //플레이어가 똥에 맞았을 때 함수
{
    int i;

    for (i = 0; i < WIDTH; i++)
    {
        if ((poo[i].act) && (poo[i].y == 0) && (poo[i].x == player.x)) //활성화된 똥의 x값과 y값이 플레이어와 같다면
        {
            return TRUE; //True 값을 반환
        }
    }

    return FALSE; //안 맞았을 때는 False 값 반환
}

void MovePlayer() //플레이어의 움직임을 담당하는 함수
{
    if (isKeyDown(VK_LEFT)) //만약에 왼쪽키를 눌렀다는 것이 확인이 된다면
        player.x -= 1; //플레이어의 x값을 1 감소
    if (isKeyDown(VK_RIGHT)) //"오른쪽키
        player.x += 1; //"x값 1증가

    if (player.x < 0)
        player.x = 0;
    if (player.x > WIDTH - 1)
        player.x = WIDTH - 1; //테두리 값을 넘어가지 않도록 함.
}

void PrintMap() //맵과 오브젝트 출력
{
    system("cls"); //콘솔 화면을 지우는 함수: 맵 초기화

    int i, i_p, i_a, i_b, i_c, i_d;

    for (i_p = 0; i_p < WIDTH; i_p++)
    {
        if (poo[i_p].act) //똥이 활성화 상태라면
        {
            gotoxy(poo[i_p].x, HEIGHT - poo[i_p].y); //(똥의 x값 , 높이값 - 똥의 y값)에 
            printf("F"); //"F"를 출력
        }
    }

    for (i_a = 0; i_a < WIDTH; i_a++)
    {
        if (a[i_a].act) //똥이 활성화 상태라면
        {
            gotoxy(a[i_a].x, HEIGHT - a[i_a].y); //(똥의 x값 , 높이값 - 똥의 y값)에 
            printf("A"); //"A"를 출력
        }
    }

    for (i_b = 0; i_b < WIDTH; i_b++)
    {
        if (a[i_b].act) //똥이 활성화 상태라면
        {
            gotoxy(b[i_b].x, HEIGHT - b[i_b].y); //(똥의 x값 , 높이값 - 똥의 y값)에 
            printf("B"); //"A"를 출력
        }
    }

    gotoxy(player.x, HEIGHT); //아래쪽으로 갈수록 y값은 증가하므로 (플레이어 x좌표, 높이값 30)에 
    printf("웃"); //"ㅁ"를 출력

    gotoxy(0, HEIGHT + 1); //(0, 높이+1)에
    for (i = 0; i < WIDTH; i++)
        printf("▦"); //"▦"를 출력
}

void main()
{
    char key;
    int i = 100;

    init();

    do
    {
        srand((int)malloc(NULL));

        CreatePoo();

        MovePoo();
        DeletePoo();

        MovePlayer();

        PrintMap();

        Sleep(40); //기존값: 100 따라서 0.1초 대기 → 떨어지는 속도를 높이고 싶다면 여기 수정하면 됨

    } while (!(PlayerContainsPoo())); //플레이어가 똥에 맞기 전 까지 계속해서 게임 실행

    system("cls");
    printf("죽었습니다!");
}