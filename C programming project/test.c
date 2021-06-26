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

typedef struct //A�� ���õ� ����(����ü)
{
    int x;
    int y;

    int act;
}A;

typedef struct //B�� ���õ� ����(����ü)
{
    int x;
    int y;

    int act;
}B;

typedef struct //C�� ���õ� ����(����ü)
{
    int x;
    int y;

    int act;
}C;

typedef struct //D�� ���õ� ����(����ü)
{
    int x;
    int y;

    int act;
}D;

typedef struct // �÷��̾�� ���õ� ����(����ü)
{
    int x;
}Player;

Poo poo[WIDTH];

A a[WIDTH];

B b[WIDTH];

C c[WIDTH];

D d[WIDTH];

Player player;

void gotoxy(int x, int y) //�ܼ� ��ǥ�踦 �������ִ� �Լ�
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
    int i_p, i_a, i_b, limit = 0;

    for (i_p = 0; i_p < WIDTH; i_p++) //���� ������ ��ġ ����
    {
        limit = rand();

        if (limit < 20000)
        {
            if (!poo[i_p].act) //���� i��° ���� ��Ȱ��ȭ ���¶��
            {
                poo[i_p].x = rand() % WIDTH; //���� ������ x���� ��ġ�� ���������� ���ΰ����� ���� ���� ������
                poo[i_p].y = HEIGHT - 1; //���� ������ y���� ��ġ�� ���̰� - 1

                poo[i_p].act = TRUE; //i��° �� Ȱ��ȭ

                break;
            }
        }
    }

    for (i_a = 0; i_a < WIDTH; i_a++) //A�� ������ ��ġ ����
    {
        limit = rand(); //���� ����� ���� ���� ������ �ϱ� ���� ����� �����ϴµ��� ���̴� �Լ�

        if (limit < 50) //���� limit�� 50 ���϶��(RAND_MAX = 32767 �̹Ƿ� 50 ������ ���ڰ� ���� Ȯ���� ����.)
        {
            if (!a[i_a].act) //���� i��° A�� ��Ȱ��ȭ ���¶��
            {
                a[i_a].x = rand() % WIDTH; //A�� ������ x���� ��ġ�� ���������� ���ΰ����� ���� ���� ������
                a[i_a].y = HEIGHT - 1; //A�� ������ y���� ��ġ�� ���̰� - 1

                if ((a[i_a].x != a[i_p].x) && (a[i_a].y != a[i_p].y)) //���࿡ A�� �ٸ� ������Ʈ�� �� ��ģ�ٸ�
                {
                    a[i_a].act = TRUE; //i��° A Ȱ��ȭ
                }
                return;
            }
        }
    }


    for (i_b = 0; i_b < WIDTH; i_b++) //A�� ������ ��ġ ����
    {
        limit = rand(); //���� ����� ���� ���� ������ �ϱ� ���� ����� �����ϴµ��� ���̴� �Լ�

        if (limit < 1000) //���� limit�� 50 ���϶��(RAND_MAX = 32767 �̹Ƿ� 50 ������ ���ڰ� ���� Ȯ���� ����.)
        {
            if (!b[i_b].act) //���� i��° A�� ��Ȱ��ȭ ���¶��
            {
                b[i_b].x = rand() % WIDTH; //A�� ������ x���� ��ġ�� ���������� ���ΰ����� ���� ���� ������
                b[i_b].y = HEIGHT - 1; //A�� ������ y���� ��ġ�� ���̰� - 1

                if ((b[i_b].x != b[i_p].x) && (b[i_b].y != b[i_p].y) &&
                    (b[i_b].x != a[i_a].x) && (b[i_b].y != a[i_a].y)
                    ) //���࿡ B�� �ٸ� ������Ʈ�� �� ��ģ�ٸ�
                {
                    b[i_b].act = TRUE; //i��° A Ȱ��ȭ
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
        if (poo[i_p].act) //i��° ���� Ȱ��ȭ ���¶��
        {
            poo[i_p].y--; //i����ŭ ����߸�
        }
    }

    for (i_a = 0; i_a < WIDTH; i_a++)
    {
        if (a[i_a].act) //i��° A�� Ȱ��ȭ ���¶��
        {
            a[i_a].y--; //i����ŭ ����߸�
        }
    }

    for (i_b = 0; i_b < WIDTH; i_b++)
    {
        if (b[i_b].act) //i��° A�� Ȱ��ȭ ���¶��
        {
            b[i_b].y--; //i����ŭ ����߸�
        }
    }
}

void DeletePoo() //���� ���ִ� �Լ�
{
    int i_p, i_a, i_b, i_c, i_d;

    for (i_p = 0; i_p < WIDTH; i_p++)
    {
        if (poo[i_p].act && poo[i_p].y < 0) //Ȱ��ȭ�� ���� Y���� 0 �̸��� ��
        {
            poo[i_p].act = FALSE; //���� ��Ȱ��ȭ
        }
    }

    for (i_a = 0; i_a < WIDTH; i_a++)
    {
        if (a[i_a].act && a[i_a].y < 0) //Ȱ��ȭ�� ���� Y���� 0 �̸��� ��
        {
            a[i_a].act = FALSE; //���� ��Ȱ��ȭ
        }
    }

    for (i_b = 0; i_b < WIDTH; i_b++)
    {
        if (b[i_b].act && b[i_b].y < 0) //Ȱ��ȭ�� ���� Y���� 0 �̸��� ��
        {
            b[i_b].act = FALSE; //���� ��Ȱ��ȭ
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
        player.x -= 1; //�÷��̾��� x���� 1 ����
    if (isKeyDown(VK_RIGHT)) //"������Ű
        player.x += 1; //"x�� 1����

    if (player.x < 0)
        player.x = 0;
    if (player.x > WIDTH - 1)
        player.x = WIDTH - 1; //�׵θ� ���� �Ѿ�� �ʵ��� ��.
}

void PrintMap() //�ʰ� ������Ʈ ���
{
    system("cls"); //�ܼ� ȭ���� ����� �Լ�: �� �ʱ�ȭ

    int i, i_p, i_a, i_b, i_c, i_d;

    for (i_p = 0; i_p < WIDTH; i_p++)
    {
        if (poo[i_p].act) //���� Ȱ��ȭ ���¶��
        {
            gotoxy(poo[i_p].x, HEIGHT - poo[i_p].y); //(���� x�� , ���̰� - ���� y��)�� 
            printf("F"); //"F"�� ���
        }
    }

    for (i_a = 0; i_a < WIDTH; i_a++)
    {
        if (a[i_a].act) //���� Ȱ��ȭ ���¶��
        {
            gotoxy(a[i_a].x, HEIGHT - a[i_a].y); //(���� x�� , ���̰� - ���� y��)�� 
            printf("A"); //"A"�� ���
        }
    }

    for (i_b = 0; i_b < WIDTH; i_b++)
    {
        if (a[i_b].act) //���� Ȱ��ȭ ���¶��
        {
            gotoxy(b[i_b].x, HEIGHT - b[i_b].y); //(���� x�� , ���̰� - ���� y��)�� 
            printf("B"); //"A"�� ���
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

        Sleep(40); //������: 100 ���� 0.1�� ��� �� �������� �ӵ��� ���̰� �ʹٸ� ���� �����ϸ� ��

    } while (!(PlayerContainsPoo())); //�÷��̾ �˿� �±� �� ���� ����ؼ� ���� ����

    system("cls");
    printf("�׾����ϴ�!");
}