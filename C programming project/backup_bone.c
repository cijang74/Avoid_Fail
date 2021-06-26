#include <stdio.h>
#include <stdlib.h> //system, sleep
#include <Windows.h> //SetConsoleCursorPosition, GetStdHandle, STD_OUTPUT_HANDLE

#define WIDTH 60
#define HEIGHT 30 //����: WIDTH 20, HEIGHT 10, ���� ȭ���� ũ�⸦ ����

typedef struct //�˰� ���õ� ����(����ü)
{
    int x;
    int y;

    int act;
}Poo;

typedef struct // �÷��̾�� ���õ� ����(����ü)
{
    int x;
}Player;

Poo poo[WIDTH];
Player player;

void gotoxy (int x, int y) //�ܼ� ��ǥ�踦 �������ִ� �Լ�
{
    COORD pos = { 2 * x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
} 

int isKeyDown(int key) //Ư�� Ű�� �������� Ȯ���ϴ� �Լ�, ������ 1 ��ȯ
{
    return ((GetAsyncKeyState(key) & 0x8000) != 0);
}

void init() //
{
    int i;

    for (i = 0; i < WIDTH; i++)
        poo[i].act = FALSE; //��� ���� ��Ȱ��ȭ ��Ŵ

    player.x = WIDTH / 2; //�÷��̾��� ó�� ��ġ�� ���ΰ�/2�� ����
}

void CreatePoo() //���� �����ϴ� �Լ�
{
    int i;

    for (i = 0; i < WIDTH; i++) //���� ������ ��ġ ����
    {
        if (!poo[i].act) //���� i��° ���� ��Ȱ��ȭ ���¶��
        {
            poo[i].x = rand() % WIDTH; //���� ������ x���� ��ġ�� ���������� ���ΰ����� ���� ���� ������
            poo[i].y = HEIGHT - 1; //���� ������ y���� ��ġ�� ���̰� - 1

            poo[i].act = TRUE; //i��° �� Ȱ��ȭ

            return;
        }
    }
}

void MovePoo() //���� �����̰� �ϴ� �Լ�
{
    int i;
    
    for (i = 0; i < WIDTH; i++)
    {
        if (poo[i].act) //i��° ���� Ȱ��ȭ ���¶��
        {
            poo[i].y--; //i����ŭ ����߸�
        }
    }
}

void DeletePoo() //���� ���ִ� �Լ�
{
    int i;

    for (i = 0; i < WIDTH; i++)
    {
        if (poo[i].act && poo[i].y < 0) //Ȱ��ȭ�� ���� Y���� 0 �̸��� ��
        {
            poo[i].act = FALSE; //���� ��Ȱ��ȭ
        }
    }
}

int PlayerContainsPoo() //�÷��̾ �˿� �¾��� �� �Լ�
{
    int i;

    for (i = 0; i < WIDTH; i++)
    {
        if ((poo[i].act) && (poo[i].y == 0) && (poo[i].x == player.x)) //Ȱ��ȭ�� ���� x���� y���� �÷��̾�� ���ٸ�
        {
            return TRUE; //True ���� ��ȯ
        }
    }

    return FALSE; //�� �¾��� ���� False �� ��ȯ
}

void MovePlayer() //�÷��̾��� �������� ����ϴ� �Լ�
{
    if (isKeyDown(VK_LEFT)) //���࿡ ����Ű�� �����ٴ� ���� Ȯ���� �ȴٸ�
        player.x -= 5; //�÷��̾��� x���� 1 ����
    if (isKeyDown(VK_RIGHT)) //"������Ű
        player.x += 5; //"x�� 1����

    if (player.x < 0)
        player.x = 0;
    if (player.x > WIDTH - 1)
        player.x = WIDTH - 1; //�׵θ� ���� �Ѿ�� �ʵ��� ��.
}

void PrintMap() //�ʰ� ������Ʈ ���
{
    system("cls"); //�ܼ� ȭ���� ����� �Լ�: �� �ʱ�ȭ

    int i;

    for (i = 0; i < WIDTH; i++)
    {
        if (poo[i].act) //���� Ȱ��ȭ ���¶��
        {
            gotoxy(poo[i].x, HEIGHT - poo[i].y); //(���� x�� , ���̰� - ���� y��)�� 
            printf("F"); //"F"�� ���
        }
    }

    gotoxy(player.x, HEIGHT); //�Ʒ������� ������ y���� �����ϹǷ� (�÷��̾� x��ǥ, ���̰� 30)�� 
    printf("��"); //"��"�� ���

    gotoxy(0, HEIGHT + 1); //(0, ����+1)��
    for (i = 0; i < WIDTH; i++)
        printf("��"); //"��"�� ���
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

        Sleep(i); //������: 100 ���� 0.1�� ��� �� �������� �ӵ��� ���̰� �ʹٸ� ���� �����ϸ� ��

        if (i != 20) //�������� �ӵ��� �ִ밪�� 0.02�� ���� ����
        {
            i = i - 0.00000000005; //0.00000000000005�ʾ� ������.
        }

    } while (!(PlayerContainsPoo())); //�÷��̾ �˿� �±� �� ���� ����ؼ� ���� ����

    system("cls");
    printf("�׾����ϴ�!");
}