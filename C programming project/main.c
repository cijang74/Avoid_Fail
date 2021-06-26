#include "main.h"

Player player;
F f[WIDTH];
D d[WIDTH];
C c[WIDTH];
B b[WIDTH];
A a[WIDTH];
Vadcation v[WIDTH];
Retake r[WIDTH];//�� ����ü ������ ����, �迭���� ����
Hotsix h[WIDTH];

void gotoxy(int x, int y) //�ܼ� ��ǥ�踦 �������ִ� �Լ�
{
    COORD pos = { 2 * x, y }; //CORD ������ ���� ��� pos�� ��ġ���� ����
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); //SetConsoleCursorPosition(�ڵ� ��, ��ġ ��) : Ŀ�� ��ġ�� �̵�
}

int isKeyDown(int key) //Ư�� Ű�� �������� Ȯ���ϴ� �Լ�, ������ 1 ��ȯ
{
    return ((GetAsyncKeyState(key) & 0x8000) != 0);
}

void init() //�ʱ�ȭ �۾�
{
    int i = 0;
    count_f = 0;
    score = 0;
    count_g = 0;
    totalcount = 0;
    grade = 1;

    for (i = 0; i < WIDTH; i++) //��� �������� ��Ȱ��ȭ ��Ŵ
    {
        f[i].act = FALSE;
        d[i].act = FALSE;
        c[i].act = FALSE;
        b[i].act = FALSE;
        a[i].act = FALSE;
        v[i].act = FALSE;
        r[i].act = FALSE;
        h[i].act = FALSE;
    }

    player.x = WIDTH / 2; //�÷��̾��� ó�� ��ġ�� ���ΰ� / 2�� ����
}

void CursorView(char show) //Ŀ���� �����ִ� �Լ�
{
    HANDLE hConsole;
    CONSOLE_CURSOR_INFO ConsoleCursor; //�ڵ�� �ܼ� �� �ý��� ���� ����ü �ɹ��� �ҷ���

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //�⺻ �ڵ鰪�� hConsol�� ����

    ConsoleCursor.bVisible = show;
    ConsoleCursor.dwSize = 1;

    SetConsoleCursorInfo(hConsole, &ConsoleCursor); //�ý��� ���� �Լ��� Ŀ���� �����ְ� �ϴ� ���� ����
}

void Grade_() // 20���� ���� �� ���� �г� ���, �ش� �г⿡ ���� ���� �� �ʱ�ȭ
{
    if (totalcount == 20)
    {
        grade = 2;
        count_g = 0;
    }

    if (totalcount == 40)
    {
        grade = 3;
        count_g = 0;
    }

    if (totalcount == 60)
    {
        grade = 4;
        count_g = 0;
    }

    if (totalcount == 80)
    {
        grade = 5;
        count_f = 3;
    }
}

void StartDisplay() //UI ���
{
    system("cls");
    gotoxy(WIDTH / 2 - 13, 2);
    printf("��------------------------------------------------��");
    gotoxy(WIDTH / 2 - 13, 3);
    printf(" |                 <AVOID FAIL!!>                |");
    gotoxy(WIDTH / 2 - 13, 4);
    printf("��------------------------------------------------��");
    gotoxy(WIDTH / 2 - 12, 6);
    printf("�������� F����� ���ؼ�, ���� �������� �����϶�!");

    gotoxy(3, 11);
    printf("[���� ��Ģ]");
    gotoxy(3, 13);
    printf("�ܵ�� 20�� ȹ��� 1�г� ���!");
    gotoxy(3, 15);
    printf("������ 4�г��� �Ѿ�� <��������!>");
    gotoxy(3, 17);
    printf("�ܴ�, ��������� 1.7 �̸��̸� <��������!>");
    gotoxy(3, 19);
    printf("�ܴ�, F��� 3�� ������ ���� 0�� + <����!>");

    int b = 2;
    gotoxy(WIDTH / 2 - b, 11);
    printf("[��޺� ����]");
    gotoxy(WIDTH / 2 - b, 13);
    printf("��A - 4��  B - 3��");
    gotoxy(WIDTH / 2 - b, 15);
    printf("��C - 2��  D - 1��");
    gotoxy(WIDTH / 2 - b, 17);
    printf("��F - 0��");

    int a = 12;
    gotoxy(WIDTH / 2 + a, 11);
    printf("[������]");
    gotoxy(WIDTH / 2 + a, 13);
    printf("��R: ����� - �ش��г� ���� ����!");
    gotoxy(WIDTH / 2 + a, 15);
    printf("��H: �ֽĽ� - �÷��̾� �ӵ� ����!");
    gotoxy(WIDTH / 2 + a, 17);
    printf("��V: ���� - �������� ����ü Ŭ����");

    gotoxy(WIDTH / 2 - 9, HEIGHT - 6);
    printf("��---------------------------------��");
    gotoxy(WIDTH / 2 - 9, HEIGHT - 4);
    printf("��---------------------------------�� ");
    gotoxy(WIDTH / 2 + 6, HEIGHT - 5);
    printf("    |");
    gotoxy(WIDTH / 2 - 9, HEIGHT - 5);
    printf(" |    press any key to start...");

    getch(); //�ƹ� Ű �Է��� �޴´�
}

void EndDisplay() //������ �� UI ���, �ٽ��ϱ� ���
{
    char a = { '\0' };
    system("cls");

    gotoxy(12, 8);
    printf("     �����������   ���            ���   ���������   ");
    gotoxy(12, 9);
    printf("     ���                   ������      ���   ���           ���");
    gotoxy(12, 10);
    printf("     �����������   ���   ����   ���   ���           ���");
    gotoxy(12, 11);
    printf("     ���                   ���      ������   ���           ���");
    gotoxy(12, 12);
    printf("     �����������   ���            ���   ����������");
    gotoxy(12, 14);
    printf("===========================================================================");
    gotoxy(12, 18);
    printf("����: %.1lf", score / totalcount);
    gotoxy(12, 20);

    if (grade == 5 && (score / totalcount) >= 1.7) //4�г��� ������ �� ������ 1.7 �̻��̶��
    {
        printf("--> ���� ����!");
    }

    else if (grade == 5 && (score / totalcount) < 1.7) //4�г��� ������ �� ������ 1.7 �̸��̶��
    {
        printf("--> ���� ����...");
    }

    else
    {
        printf("--> ���� ���ϼ̽��ϴ�.");
    }

    gotoxy(12, 24);
    printf("�ٽ� �Ͻðڽ��ϱ�?");
    gotoxy(12, 26);
    printf("[Y]: �ٽ��ϱ� [ESC]: ���� ����");

    while (1)
    {
        a = getch();

        if (a == 27) //�Էµ� Ű�� ESC�̸� ���� ����
        {
            exit_ = 0;
            break;
        }

        else if (a == 121 || a == 89) //�Էµ� Ű�� Y �Ǵ� y��� ���� �ݺ�
        {
            break;
        }
    }

}

void Create_Faller() //���Ϲ��� �����ϴ� �Լ�
{
    int i = 0, limit, difficulty = 0; //limit: rand�� ������ ������ ��, difficulty: ���Ϲ��� �������� Ƚ���� ����

    if (grade == 1) //�г��� ������ ���� F�� �������� ������ Ŀ����, �ٸ� ���Ϲ��� ������ �۾���.
    {
        difficulty = 30000;
    }

    if (grade == 2)
    {
        difficulty = 20000;
    }

    if (grade == 3)
    {
        difficulty = 15000;
    }

    if (grade == 4)
    {
        difficulty = 10000;
    }

    for (i = 0; i < WIDTH; i++) //���Ϲ��� ������ ��ġ ����
    {
        limit = rand();

        if (limit > difficulty) //���� �������� difficulty ������ ũ�ٸ�
        {
            if (!f[i].act) //���� i��° F�� ��Ȱ��ȭ ���¶��
            {
                f[i].x = rand() % WIDTH; //F�� ������ x���� ��ġ�� ���������� ���ΰ����� ���� ���� ������
                f[i].y = HEIGHT - 1; //F�� ������ y���� ��ġ�� ���̰� - 1

                f[i].act = TRUE; //i��° F Ȱ��ȭ

                return;
            }
        }

        else if (limit < difficulty && limit > difficulty - 4000) //���� �������� difficulty ���� �۰� difficulty - 4000 ���� ũ�ٸ�
        {
            if (!d[i].act)
            {
                d[i].x = rand() % WIDTH;
                d[i].y = HEIGHT - 1;

                d[i].act = TRUE;

                return;
            }
        }

        else if (limit < difficulty - 4000 && limit > difficulty - 8000)
        {
            if (!c[i].act)
            {
                c[i].x = rand() % WIDTH;
                c[i].y = HEIGHT - 1;

                c[i].act = TRUE;

                return;
            }
        }

        else if (limit < difficulty - 8000 && limit > difficulty - 9500)
        {
            if (!b[i].act)
            {
                b[i].x = rand() % WIDTH;
                b[i].y = HEIGHT - 1;

                b[i].act = TRUE;

                return;
            }
        }

        else if (limit < difficulty - 9500 && limit > difficulty - 9900)
        {
            if (!a[i].act)
            {
                a[i].x = rand() % WIDTH;
                a[i].y = HEIGHT - 1;

                a[i].act = TRUE;

                return;
            }
        }

        else if (limit < 100 && limit > 60)
        {
            if (!v[i].act)
            {
                v[i].x = rand() % WIDTH;
                v[i].y = HEIGHT - 1;

                v[i].act = TRUE;

                return;
            }
        }

        else if (limit < 60 && limit > 30)
        {
            if (!r[i].act)
            {
                r[i].x = rand() % WIDTH;
                r[i].y = HEIGHT - 1;

                r[i].act = TRUE;

                return;
            }
        }

        else if (limit < 30 && limit > 0)
        {
            if (!h[i].act)
            {
                h[i].x = rand() % WIDTH;
                h[i].y = HEIGHT - 1;

                h[i].act = TRUE;

                return;
            }
        }
    }
}

void Move_Faller() //���Ϲ��� �����̰� �ϴ� �Լ�
{
    int i = 0;

    for (i = 0; i < WIDTH; i++)
    {
        if (f[i].act) //i��° F Ȱ��ȭ ���¶��
        {
            f[i].y--; //i����ŭ ����߸�
        }

        if (d[i].act)
        {
            d[i].y--;
        }

        if (c[i].act)
        {
            c[i].y--;
        }

        if (b[i].act)
        {
            b[i].y--;
        }

        if (a[i].act)
        {
            a[i].y--;
        }

        if (v[i].act)
        {
            v[i].y--;
        }

        if (r[i].act)
        {
            r[i].y--;
        }

        if (h[i].act)
        {
            h[i].y--;
        }
    }
}

void Delete_Faller() //�ٴڿ� ���� ���Ϲ��� ���ִ� �Լ�
{
    int i;

    for (i = 0; i < WIDTH; i++)
    {
        if (f[i].act && f[i].y < 0) //Ȱ��ȭ�� F�� Y���� 0 �̸��� ��
        {
            f[i].act = FALSE; //F�� ��Ȱ��ȭ
        }

        if (d[i].act && d[i].y < 0)
        {
            d[i].act = FALSE;
        }

        if (c[i].act && c[i].y < 0)
        {
            c[i].act = FALSE;
        }

        if (b[i].act && b[i].y < 0)
        {
            b[i].act = FALSE;
        }

        if (a[i].act && a[i].y < 0)
        {
            a[i].act = FALSE;
        }

        if (v[i].act && v[i].y < 0)
        {
            v[i].act = FALSE;
        }

        if (r[i].act && r[i].y < 0)
        {
            r[i].act = FALSE;
        }

        if (h[i].act && h[i].y < 0)
        {
            h[i].act = FALSE;
        }
    }
}

int PlayerContains_Fail() //�÷��̾ F�� �¾��� �� �Լ�
{
    int i;

    for (i = 0; i < WIDTH; i++)
    {
        if ((f[i].act) && (f[i].y == 0) && (f[i].x == player.x)) //Ȱ��ȭ�� F�� x���� y���� �÷��̾�� ���ٸ�
        {
            count_f += 1;
            count_g += 1;
            totalcount += 1; //f�� ���� Ƚ��, �ش� �г⿡�� ȹ���� ���� ����, �� ȹ���� ���� �� + 1
        }
    }
    if (count_f == 3) return TRUE;
    return FALSE; //�� �¾��� ���� False �� ��ȯ
}

int PlayerContains_Socre_Item() //�÷��̾ A,B,C,D �Ǵ� �����ۿ� �¾�����
{
    int i;

    for (i = 0; i < WIDTH; i++)
    {
        if ((a[i].act) && (a[i].y == 0) && (a[i].x == player.x))
        {
            score += 4;
            count_g += 1;
            totalcount += 1; //����, �ش� �г⿡�� ȹ���� ���� ����, �� ȹ���� ���� �� + 1
        }
    }

    for (i = 0; i < WIDTH; i++)
    {
        if ((b[i].act) && (b[i].y == 0) && (b[i].x == player.x))
        {
            score += 3;
            count_g += 1;
            totalcount += 1;
        }
    }

    for (i = 0; i < WIDTH; i++)
    {
        if ((c[i].act) && (c[i].y == 0) && (c[i].x == player.x))
        {
            score += 2;
            count_g += 1;
            totalcount += 1;
        }
    }

    for (i = 0; i < WIDTH; i++)
    {
        if ((d[i].act) && (d[i].y == 0) && (d[i].x == player.x))
        {
            score += 1;
            count_g += 1;
            totalcount += 1;
        }
    }

    for (i = 0; i < WIDTH; i++)
    {
        if ((v[i].act) && (v[i].y == 0) && (v[i].x == player.x))
        {
            for (int j = 0; j < WIDTH; j++)
            {
                f[j].act = FALSE; //��� �������� ��Ȱ��ȭ ��Ŵ
                d[j].act = FALSE;
                c[j].act = FALSE;
                b[j].act = FALSE;
                a[j].act = FALSE;
                v[j].act = FALSE;
                r[j].act = FALSE;
            }
        }
    }

    for (i = 0; i < WIDTH; i++)
    {
        if ((r[i].act) && (r[i].y == 0) && (r[i].x == player.x))
        {
            count_g = 0; //�ش� �г⿡�� ȹ���� ���� �� �ʱ�ȭ
        }
    }

    for (i = 0; i < WIDTH; i++)
    {
        if ((h[i].act) && (h[i].y == 0) && (h[i].x == player.x))
        {  
            if (dt > 20) dt = dt - 5; //�÷��̾�� ���Ϲ��� �ӵ��� ���(�ִ� ���� ����.)
        }
    }
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

void Print_Map_Object() //�ʰ� ������Ʈ ���
{
    system("cls"); //�ܼ� ȭ���� ����� �Լ�: �� �ʱ�ȭ

    int i;

    for (i = 0; i < WIDTH; i++)
    {
        if (f[i].act) //F�� Ȱ��ȭ ���¶��
        {
            gotoxy(f[i].x, HEIGHT - f[i].y); //(F�� x�� , ���̰� - F�� y��)�� 
            printf("F"); //"F"�� ���
        }

        if (d[i].act)
        {
            gotoxy(d[i].x, HEIGHT - d[i].y);
            printf("D");
        }

        if (c[i].act)
        {
            gotoxy(c[i].x, HEIGHT - c[i].y);
            printf("C");
        }

        if (b[i].act)
        {
            gotoxy(b[i].x, HEIGHT - b[i].y);
            printf("B");
        }

        if (a[i].act)
        {
            gotoxy(a[i].x, HEIGHT - a[i].y);
            printf("A");
        }

        if (v[i].act)
        {
            gotoxy(v[i].x, HEIGHT - v[i].y);
            printf("V");
        }

        if (r[i].act)
        {
            gotoxy(r[i].x, HEIGHT - r[i].y);
            printf("V");
        }

        if (r[i].act)
        {
            gotoxy(r[i].x, HEIGHT - r[i].y);
            printf("R");
        }

        if (h[i].act)
        {
            gotoxy(h[i].x, HEIGHT - h[i].y);
            printf("H");
        }

    }

    gotoxy(player.x, HEIGHT); //�Ʒ������� ������ y���� �����ϹǷ� (�÷��̾� x��ǥ, ���̰� 30)�� 
    printf("��"); //"��"�� ���

    gotoxy(0, HEIGHT + 1); //(0, ����+1)��

    for (i = 0; i < WIDTH; i++)
        printf("��"); //"��"�� ���
}

void PrintScore()
{
    gotoxy(WIDTH - 10, 2);
    printf("<���� �г�:  %d�г� >", grade);

    gotoxy(WIDTH - 10, 3);
    printf("<�г� ���:  %d/20  >", count_g);

    gotoxy(WIDTH - 10, 4);

    if (totalcount == 0)
    {
        printf("<���� ����:   0.0  >");
    }

    else
    {
        printf("<���� ����:   %.1lf  >", score / totalcount);
    }

    gotoxy(WIDTH - 10, 5);
    printf("<���� ���: "); //���� ����� ���� ��Ʈ���� �޶���

    if (count_f == 0)
    {
        gotoxy(WIDTH - 4, 5);
        printf("������ >");
    }

    if (count_f == 1)
    {
        gotoxy(WIDTH - 4, 5);
        printf("������ >");
    }

    if (count_f == 2)
    {
        gotoxy(WIDTH - 4, 5);
        printf("������ >");
    }
}

void PlayBgm()
{
    PlaySound(TEXT("music.wav"), NULL, SND_ASYNC | SND_LOOP); // music.wav �̶�� ���� �ݺ� ���
}

void Game()
{
    PlayBgm();
    do
    {
        srand((int)malloc(NULL)); //rand �õ尪�� ��� �ٲ�
        Create_Faller();
        Move_Faller();
        Delete_Faller();
        MovePlayer();
        Print_Map_Object();
        PrintScore();
        Grade_();
        PlayerContains_Socre_Item();
        CursorView(0); //Ŀ�� �����

        Sleep(dt);

    } while (!(PlayerContains_Fail())); //�÷��̾ �˿� �±� �� ���� ����ؼ� ���� ����
}

void main()
{
    init();
    StartDisplay();
    while (exit_)
    {
        init();
        Game();
        system("cls");
        EndDisplay();
    }

    CursorView(0);
}