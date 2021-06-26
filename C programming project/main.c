#include "main.h"

Player player;
F f[WIDTH];
D d[WIDTH];
C c[WIDTH];
B b[WIDTH];
A a[WIDTH];
Vadcation v[WIDTH];
Retake r[WIDTH];//각 구조체 형식의 변수, 배열들을 선언
Hotsix h[WIDTH];

void gotoxy(int x, int y) //콘솔 좌표계를 설정해주는 함수
{
    COORD pos = { 2 * x, y }; //CORD 구초제 안의 멤버 pos에 위치값를 저장
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); //SetConsoleCursorPosition(핸들 값, 위치 값) : 커서 위치를 이동
}

int isKeyDown(int key) //특정 키를 눌렀는지 확인하는 함수, 맞으면 1 반환
{
    return ((GetAsyncKeyState(key) & 0x8000) != 0);
}

void init() //초기화 작업
{
    int i = 0;
    count_f = 0;
    score = 0;
    count_g = 0;
    totalcount = 0;
    grade = 1;

    for (i = 0; i < WIDTH; i++) //모든 점수들을 비활성화 시킴
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

    player.x = WIDTH / 2; //플레이어의 처음 위치를 가로값 / 2로 설정
}

void CursorView(char show) //커서를 숨겨주는 함수
{
    HANDLE hConsole;
    CONSOLE_CURSOR_INFO ConsoleCursor; //핸들과 콘솔 등 시스템 내의 구조체 맴버를 불러옴

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //기본 핸들값을 hConsol에 저장

    ConsoleCursor.bVisible = show;
    ConsoleCursor.dwSize = 1;

    SetConsoleCursorInfo(hConsole, &ConsoleCursor); //시스템 내의 함수에 커서를 숨겨주게 하는 값을 전달
}

void Grade_() // 20개를 먹을 때 마다 학년 상승, 해당 학년에 먹은 학점 수 초기화
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

void StartDisplay() //UI 출력
{
    system("cls");
    gotoxy(WIDTH / 2 - 13, 2);
    printf("┌------------------------------------------------┐");
    gotoxy(WIDTH / 2 - 13, 3);
    printf(" |                 <AVOID FAIL!!>                |");
    gotoxy(WIDTH / 2 - 13, 4);
    printf("└------------------------------------------------┘");
    gotoxy(WIDTH / 2 - 12, 6);
    printf("떨어지는 F등급을 피해서, 높은 학점으로 졸업하라!");

    gotoxy(3, 11);
    printf("[게임 규칙]");
    gotoxy(3, 13);
    printf("●등급 20개 획득시 1학년 상승!");
    gotoxy(3, 15);
    printf("●최종 4학년을 넘어서면 <졸업성공!>");
    gotoxy(3, 17);
    printf("●단, 학점평균이 1.7 미만이면 <졸업실패!>");
    gotoxy(3, 19);
    printf("●단, F등급 3번 받으면 학점 0점 + <제적!>");

    int b = 2;
    gotoxy(WIDTH / 2 - b, 11);
    printf("[등급별 학점]");
    gotoxy(WIDTH / 2 - b, 13);
    printf("●A - 4점  B - 3점");
    gotoxy(WIDTH / 2 - b, 15);
    printf("●C - 2점  D - 1점");
    gotoxy(WIDTH / 2 - b, 17);
    printf("●F - 0점");

    int a = 12;
    gotoxy(WIDTH / 2 + a, 11);
    printf("[아이템]");
    gotoxy(WIDTH / 2 + a, 13);
    printf("●R: 재수강 - 해당학년 학점 리셋!");
    gotoxy(WIDTH / 2 + a, 15);
    printf("●H: 핫식스 - 플레이어 속도 증가!");
    gotoxy(WIDTH / 2 + a, 17);
    printf("●V: 방학 - 떨어지는 투사체 클리어");

    gotoxy(WIDTH / 2 - 9, HEIGHT - 6);
    printf("┌---------------------------------┐");
    gotoxy(WIDTH / 2 - 9, HEIGHT - 4);
    printf("└---------------------------------┘ ");
    gotoxy(WIDTH / 2 + 6, HEIGHT - 5);
    printf("    |");
    gotoxy(WIDTH / 2 - 9, HEIGHT - 5);
    printf(" |    press any key to start...");

    getch(); //아무 키 입력을 받는다
}

void EndDisplay() //끝났을 때 UI 출력, 다시하기 기능
{
    char a = { '\0' };
    system("cls");

    gotoxy(12, 8);
    printf("     ■■■■■■■■■■   ■■            ■■   ■■■■■■■■   ");
    gotoxy(12, 9);
    printf("     ■■                   ■■■■■      ■■   ■■           ■■");
    gotoxy(12, 10);
    printf("     ■■■■■■■■■■   ■■   ■■■   ■■   ■■           ■■");
    gotoxy(12, 11);
    printf("     ■■                   ■■      ■■■■■   ■■           ■■");
    gotoxy(12, 12);
    printf("     ■■■■■■■■■■   ■■            ■■   ■■■■■■■■■");
    gotoxy(12, 14);
    printf("===========================================================================");
    gotoxy(12, 18);
    printf("학점: %.1lf", score / totalcount);
    gotoxy(12, 20);

    if (grade == 5 && (score / totalcount) >= 1.7) //4학년이 끝나고 총 학점이 1.7 이상이라면
    {
        printf("--> 졸업 성공!");
    }

    else if (grade == 5 && (score / totalcount) < 1.7) //4학년이 끝나고 총 학점이 1.7 미만이라면
    {
        printf("--> 졸업 실패...");
    }

    else
    {
        printf("--> 제적 당하셨습니다.");
    }

    gotoxy(12, 24);
    printf("다시 하시겠습니까?");
    gotoxy(12, 26);
    printf("[Y]: 다시하기 [ESC]: 게임 종료");

    while (1)
    {
        a = getch();

        if (a == 27) //입력된 키가 ESC이면 게임 종료
        {
            exit_ = 0;
            break;
        }

        else if (a == 121 || a == 89) //입력된 키가 Y 또는 y라면 루프 반복
        {
            break;
        }
    }

}

void Create_Faller() //낙하물을 생성하는 함수
{
    int i = 0, limit, difficulty = 0; //limit: rand로 생성된 무작위 수, difficulty: 낙하물이 떨어지는 횟수를 조절

    if (grade == 1) //학년이 증가될 수록 F가 떨어지는 비중이 커지고, 다른 낙하물의 비중이 작아짐.
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

    for (i = 0; i < WIDTH; i++) //낙하물이 생성될 위치 범위
    {
        limit = rand();

        if (limit > difficulty) //만약 랜덤값이 difficulty 값보다 크다면
        {
            if (!f[i].act) //만약 i번째 F가 비활성화 상태라면
            {
                f[i].x = rand() % WIDTH; //F이 생성될 x값의 위치는 무작위수를 가로값으로 나눈 값의 나머지
                f[i].y = HEIGHT - 1; //F이 생성될 y값의 위치는 높이값 - 1

                f[i].act = TRUE; //i번째 F 활성화

                return;
            }
        }

        else if (limit < difficulty && limit > difficulty - 4000) //만약 랜덤값이 difficulty 보다 작고 difficulty - 4000 보다 크다면
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

void Move_Faller() //낙하물을 움직이게 하는 함수
{
    int i = 0;

    for (i = 0; i < WIDTH; i++)
    {
        if (f[i].act) //i번째 F 활성화 상태라면
        {
            f[i].y--; //i값만큼 떨어뜨림
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

void Delete_Faller() //바닥에 닿은 낙하물을 없애는 함수
{
    int i;

    for (i = 0; i < WIDTH; i++)
    {
        if (f[i].act && f[i].y < 0) //활성화된 F의 Y값이 0 미만일 때
        {
            f[i].act = FALSE; //F를 비활성화
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

int PlayerContains_Fail() //플레이어가 F에 맞았을 때 함수
{
    int i;

    for (i = 0; i < WIDTH; i++)
    {
        if ((f[i].act) && (f[i].y == 0) && (f[i].x == player.x)) //활성화된 F의 x값과 y값이 플레이어와 같다면
        {
            count_f += 1;
            count_g += 1;
            totalcount += 1; //f를 맞은 횟수, 해당 학년에서 획득한 학점 개수, 총 획득한 학점 수 + 1
        }
    }
    if (count_f == 3) return TRUE;
    return FALSE; //안 맞았을 때는 False 값 반환
}

int PlayerContains_Socre_Item() //플레이어가 A,B,C,D 또는 아이템에 맞았을때
{
    int i;

    for (i = 0; i < WIDTH; i++)
    {
        if ((a[i].act) && (a[i].y == 0) && (a[i].x == player.x))
        {
            score += 4;
            count_g += 1;
            totalcount += 1; //점수, 해당 학년에서 획득한 학점 개수, 총 획득한 학점 수 + 1
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
                f[j].act = FALSE; //모든 점수들을 비활성화 시킴
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
            count_g = 0; //해당 학년에서 획득한 학점 수 초기화
        }
    }

    for (i = 0; i < WIDTH; i++)
    {
        if ((h[i].act) && (h[i].y == 0) && (h[i].x == player.x))
        {  
            if (dt > 20) dt = dt - 5; //플레이어와 낙하물의 속도를 상승(최대 제한 있음.)
        }
    }
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

void Print_Map_Object() //맵과 오브젝트 출력
{
    system("cls"); //콘솔 화면을 지우는 함수: 맵 초기화

    int i;

    for (i = 0; i < WIDTH; i++)
    {
        if (f[i].act) //F가 활성화 상태라면
        {
            gotoxy(f[i].x, HEIGHT - f[i].y); //(F의 x값 , 높이값 - F의 y값)에 
            printf("F"); //"F"를 출력
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

    gotoxy(player.x, HEIGHT); //아래쪽으로 갈수록 y값은 증가하므로 (플레이어 x좌표, 높이값 30)에 
    printf("웃"); //"옷"를 출력

    gotoxy(0, HEIGHT + 1); //(0, 높이+1)에

    for (i = 0; i < WIDTH; i++)
        printf("▦"); //"▦"를 출력
}

void PrintScore()
{
    gotoxy(WIDTH - 10, 2);
    printf("<현재 학년:  %d학년 >", grade);

    gotoxy(WIDTH - 10, 3);
    printf("<학년 상승:  %d/20  >", count_g);

    gotoxy(WIDTH - 10, 4);

    if (totalcount == 0)
    {
        printf("<현재 학점:   0.0  >");
    }

    else
    {
        printf("<현재 학점:   %.1lf  >", score / totalcount);
    }

    gotoxy(WIDTH - 10, 5);
    printf("<남은 목숨: "); //남은 목숨에 따라 하트량이 달라짐

    if (count_f == 0)
    {
        gotoxy(WIDTH - 4, 5);
        printf("♥♥♥ >");
    }

    if (count_f == 1)
    {
        gotoxy(WIDTH - 4, 5);
        printf("♥♥♡ >");
    }

    if (count_f == 2)
    {
        gotoxy(WIDTH - 4, 5);
        printf("♥♡♡ >");
    }
}

void PlayBgm()
{
    PlaySound(TEXT("music.wav"), NULL, SND_ASYNC | SND_LOOP); // music.wav 이라는 음악 반복 재생
}

void Game()
{
    PlayBgm();
    do
    {
        srand((int)malloc(NULL)); //rand 시드값이 계속 바뀜
        Create_Faller();
        Move_Faller();
        Delete_Faller();
        MovePlayer();
        Print_Map_Object();
        PrintScore();
        Grade_();
        PlayerContains_Socre_Item();
        CursorView(0); //커서 숨기기

        Sleep(dt);

    } while (!(PlayerContains_Fail())); //플레이어가 똥에 맞기 전 까지 계속해서 게임 실행
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