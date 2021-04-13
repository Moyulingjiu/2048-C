#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <Mmsystem.h> //��Ƶ
#include <direct.h>   //·��
#pragma warning(disable : 4996)
#pragma warning(disable : 26451)
#pragma comment(lib, "winmm.lib")
int dot[4][4] = {0};          //4*4�����̾���
int save[6][4][4] = {0};      //���屣�������
int goon = 0;                 //�����Ϸ�Ƿ���ʤ�������������
int maxscore = 0;             //��ȡ��Ϸ���ķ���
int cartoonstate = 1;         //��������رն���Ч��
int RegretTimes = 0;          //���岽��
const int soudnumber = 64;    //��������������
const int winscore = 2048;    //ʤ������
int scores = 0;               //����
int savedScores[6] = {0};     //����ķ���
void rule();                  //�������
void developer();             //����������
void cleardata();             //�������
int starts();                 //��ʼ
int random(int min, int max); //�����
void newpoint(int num);       //����������
void draw();                  //��������
void sleep(unsigned int num); //��ͣ
int moveup();                 //����
int movedown();               //����
int moveleft();               //����
int moveright();              //����
int quit();                   //�˻ص����˵�
int remake();                 //����Ƿ����¿�ʼ��Ϸ
int check();                  //����Ƿ�ʤ��������Ϸ����
int gamesave(int state);      //������Ϸ
int gameload();               //������Ϸ
int getscore();               //��ȡ������
int writescore();             //д��������
void cartoon();               //����Ч��
void clear_screen();          //�����Ļ��ʾ
int regret();                 //����
void regretSave();            //��¼�������Ϣ
char tips();                  //������ʾ��Ŀǰ��д���ª���㷨��ֻԤ����һ���������������������ಽ��
void setColor(unsigned short ForeColor, unsigned short BackGroundColor)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);                     //��ȡ��ǰ���ھ��
    SetConsoleTextAttribute(handle, ForeColor + BackGroundColor * 0x10); //������ɫ
}
//���ù��λ��
void SetPos(int x, int y)
{
    COORD pos;
    HANDLE handle;
    pos.X = x;
    pos.Y = y;
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(handle, pos);
    return;
}
void HideCursor()
{
    CONSOLE_CURSOR_INFO cursor;
    cursor.bVisible = FALSE;
    cursor.dwSize = sizeof(cursor);
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorInfo(handle, &cursor);
    return;
}
int main()
{
    system("mode con cols=95 lines=30 ");
    HideCursor();
    while (1)
    {
        system("color f0");
        SetPos(0, 2);
        //LoadKeyboardLayout(L"0x409", KLF_ACTIVATE | KLF_SETFORPROCESS); //�л����뷨��Ӣ��
        printf(" ----------- 2048 -----------\n\n");
        printf(" 1.");
        setColor(15, 12);
        printf("��ʼ��Ϸ");
        setColor(0, 15);
        printf("������������������1\n");
        printf(" 2.�鿴��Ϸ���򡪡�����������2\n");
        printf(" 3.�鿴����������������������3\n");
        printf(" 4.�����Ϸ���м�¼����������4\n");
        if (cartoonstate)
        {
            printf(" 5.");
            setColor(1, 15);
            printf("�ر�");
            setColor(0, 15);
            printf("����Ч����������������5\n");
        }
        else
        {
            printf(" 5.");
            setColor(1, 15);
            printf("����");
            setColor(0, 15);
            printf("����Ч����������������5\n");
        }
        printf(" 6.�˳���Ϸ������������������6\n");
        printf("\n ������ָ�");
        char contorl;
        contorl = getch();
        fflush(stdin);
        printf("\n\n ���ڴ���ָ����Ժ󡭡�");
        system("cls");
        if (contorl == '1')
            starts();
        else if (contorl == '2')
            rule();
        else if (contorl == '3')
            developer();
        else if (contorl == '4')
        {
            cleardata();
        }
        else if (contorl == '5')
        {
            cartoonstate = !cartoonstate;
        }
        else if (contorl == '6')
            return 0;
        else if (contorl == '\n' || contorl == ' ')
        {
            continue;
        }
    }
    return 0;
}
void rule()
{
    //����
    printf("\n\n----------- 2048 -----------\n\n");
    printf("��Ϸ����\n 1��2048��һ��4*4�����̡�\n");
    printf(" 2����ʼʱ��������������������֣����ֵ����ֽ�����Ϊ2��4��\n");
    printf(" 3����ҿ���ѡ�����������ĸ����������ڵ����Ӱ��÷���λ�ơ�\n");
    printf(" a) �����������ƶ������һ�ࣨ�磺�ҲࣩΪ�գ������ƶ�����λ��\n");
    printf(" b) �����������ƶ������һ�ࣨ�磺�ҲࣩΪͬ�������֣�������ò�������ӡ����ɽ���������������ӡ�\n");
    printf(" c) ���÷�������������a)��b)���������ƶ����ӡ�\n");
    printf(" 4��ÿ��Ч�ƶ�һ�������̵Ŀ�λ�������ִ����������һ�����֣�Ϊ2�� 4����\n");
    printf(" 5�����ĸ����������3��c)�������и���\n");
    printf(" 6��������2048������ʤ��\n");
    printf(" 7������\"Q\"����Իص����˵���\n");
    printf(" 7������\"E\"����Ի��壬��ע�����ֻ���Ի����岽��\n");
    printf(" 8������\"R\"�����ؿ���Ϸ��\n\n");
    system("pause");
    system("cls");
}
void developer()
{
    //��������Ϣ
    printf("\n\n----------- 2048 -----------\n\n");
    printf("��Ϸ���֣�2048\n");
    printf("�������������壺C/C++\n");
    printf("�汾�ţ�v0.1.4\n");
    printf("������Ա��ī��\n\n");
    printf("Copyright @ 2019, ī�� all rights reserved.\n\n");
    system("pause");
    system("cls");
    return;
}
void cleardata()
{
    while (1)
    {
        system("cls");
        printf("\n\n---------------------- 2048 ----------------------\n\n");
        printf("ȷ��Ҫ�������������������ʧȥ�������Ϸ���Ⱥ���ʷ��߷֣�Y/N����");
        char choose;
        choose = getch();
        if (choose == 'y' || choose == 'Y')
        {
            for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                {
                    dot[i][j] = 0;
                }
            goon = 0;
            gamesave(0);
            maxscore = 0;
            writescore();
            printf("\n\n");
            setColor(15, 12);
            printf("ɾ�����!!");
            setColor(0, 15);
            printf("\n\n");
            system("pause");
            system("cls");
            return;
        }
        else if (choose == 'n' || choose == 'N')
        {
            system("cls");
            return;
        }
    }
}
int starts()
{
    //��Ϸ��ʼ
    //system("color 0f");
    if (gameload() == 1)
    {
        maxscore = getscore(); //�õ�������
        while (1)
        {
            printf("\n\n ----------- 2048 -----------\n\n");
            printf(" ��⵽��δ��ɵ���Ϸ�Ƿ����[Y/N]��");
            char choose;
            choose = getch();
            if (choose == 'y' || choose == 'Y')
            {
                break;
            }
            else if (choose == 'n' || choose == 'N')
            {
                for (int i = 0; i < 4; i++)
                    for (int j = 0; j < 4; j++)
                    {
                        dot[i][j] = 0;
                    }
                scores = 0;
                goon = 0;
                newpoint(2); //�����������������
                break;
            }
            else
            {
                system("cls");
            }
        }
    }
    else
    {
        scores = 0;
        goon = 0;
        newpoint(2); //�����������������
    }
    RegretTimes = 0;
    gamesave(1); //������Ϸ
    draw();      //��������
    char command;
    while (1)
    {
        command = getch();
        /*
switch (command)
{
case 0xE0:
switch (command = getch())
{
case 72: printf("UP\n"); break;
case 80: printf("DOWN\n"); break;
case 75: printf("LEFT\n"); break;
case 77: printf("RIGHT\n"); break;
default:
break;
}
system("pause");
break;
default:
break;
}*/
        if (command == 'w' || command == 'a' || command == 's' || command == 'd' ||
            command == 'W' || command == 'A' || command == 'S' || command == 'D')
        {
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    save[5][i][j] = dot[i][j];
                }
            }
            savedScores[5] = scores;
            int getnewpoint;
            if (command == 'w' || command == 'W')
                getnewpoint = moveup(); //����
            else if (command == 's' || command == 'S')
                getnewpoint = movedown(); //����
            else if (command == 'a' || command == 'A')
                getnewpoint = moveleft(); //����
            else if (command == 'd' || command == 'D')
                getnewpoint = moveright(); //����
            if (getnewpoint)
            {
                newpoint(1);  //����һ���µ�����
                gamesave(1);  //������Ϸ
                regretSave(); //��¼������Ϣ
            }
            draw();               //��������
            int reslut = check(); //����Ƿ�ʤ��������Ϸ����
            if (reslut == 1 || reslut == 5)
            {
                gamesave(0); //ȡ��������Ϸ
                return 0;
            }
            else if (reslut == 2)
            {
                draw();
            }
            else if (reslut == 3 || reslut == 4)
            {
                newpoint(2);
                draw();
            }
        }
        else if (command == 'q' || command == 'Q')
        {
            if (quit())
            {
                gamesave(1); //������Ϸ
                return 0;
            }
            else
                draw();
        }
        else if (command == 'r' || command == 'R')
        {
            if (remake())
            {
                scores = 0;
                newpoint(2);
                gamesave(1); //������Ϸ
            }
            draw();
        }
        else if (command == 'e' || command == 'E')
        {
            regret();
        }
        else
        {
            draw();
        }
    }
    return 0;
} //��Ϸ��ʼ
int quit()
{
    while (1)
    {
        system("cls");
        printf("\n\n ---------------------- 2048 ----------------------\n\n");
        printf(" ȷ��Ҫ�ص����˵������ǻᱣ��������Ϸ��¼��Y/N����");
        char choose;
        choose = getche();
        if (choose == 'y' || choose == 'Y')
        {
            system("cls");
            goon = 0;
            return 1;
        }
        else if (choose == 'n' || choose == 'N')
        {
            return 0;
        }
    }
}
int remake()
{
    while (1)
    {
        system("cls");
        printf("\n\n ---------------------- 2048 ----------------------\n\n");
        printf(" ȷ��Ҫ���¿�ʼ��������ʧȥ��ǰ����Ϸ���ȣ�Y/N����");
        char choose;
        choose = getche();
        if (choose == 'y' || choose == 'Y')
        {
            system("cls");
            for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                {
                    dot[i][j] = 0;
                }
            goon = 0;
            return 1;
        }
        else if (choose == 'n' || choose == 'N')
        {
            return 0;
        }
    }
}
int random(int min, int max)
{
    //�����
    int num;
    sleep(101);
    srand((unsigned)time(0));
    num = rand() % (max - min + 1) + min;
    return num;
}
void newpoint(int num)
{
    for (int i = 0; i < num; i++)
    {
        int x = random(0, 3);
        int y = random(0, 3);
        int number = random(1, 2) * 2;
        if (dot[x][y] != 0)
        {
            for (int j = 0; j < 4; j++)
                for (int k = 0; k < 4; k++)
                    if (dot[k][j] == 0)
                    {
                        dot[k][j] = number;
                        if (i == num - 1)
                            return;
                    }
        }
        else
        {
            dot[x][y] = number;
        }
    }
}
void sleep(unsigned int num)
{
    //��������һ��ʱ�䣬��֤�������һ��;num�ĵ�λΪms
    double scend = (double)(num) / 1000;
    clock_t s_time, e_time;
    s_time = clock();
    do
    {
        e_time = clock();
    } while (scend > (double)(e_time - s_time) / CLOCKS_PER_SEC);
}
void draw()
{
    clear_screen(); //�����Ļ
    //���������
    if (scores >= maxscore)
    {
        maxscore = scores;
        writescore();
    }
    printf("\n\n ---------------------------- 2048 ----------------------------\n\n");
    printf(" �������������������������������Щ����������������������������Щ����������������������������Щ�����������������������������\n");
    printf(" ��              ��              ��              ��              ��      ��ǰ������%d\n", scores);
    for (int i = 0; i < 4; i++)
    {
        printf(" ");
        for (int j = 0; j < 4; j++)
        {
            if (dot[j][i] != 0)
                printf("�� %12d ", dot[j][i]);
            else
                printf("��              ");
        }
        printf("��\n");
        if (i != 3)
        {
            if (i == 0)
                printf(" ��              ��              ��              ��              ��      ��ʷ��ߣ�%d\n", maxscore);
            else
                printf(" ��              ��              ��              ��              ��\n");
            printf(" �������������������������������੤���������������������������੤���������������������������੤����������������������������\n");
            printf(" ��              ��              ��              ��              ��\n");
        }
    }
    printf(" ��              ��              ��              ��              ��\n");
    printf(" �������������������������������ة����������������������������ة����������������������������ة�����������������������������\n");
    printf("\n ��ǰʣ����岽����%d", RegretTimes);
    printf("\n ������A�����£�S�����ң�D�����ϣ�W�����壺E���˻����˵���Q�����¿�ʼ��R)\n");
    //printf(" Ŀǰ������");
    fflush(0);
}
int moveup()
{
    int movevalue = 0;
    int i;
    for (i = 0; i < 4; ++i)
    {
        /* ����jΪ���±꣬����kΪ���Ƚϣ��ϲ�������±꣬ѭ������ʱk<j */
        int j, k;
        for (j = 1, k = 0; j < 4; ++j)
        {
            if (dot[i][j] > 0) /* �ҳ�k�����һ����Ϊ�յ���±�Ϊj��֮�������
��� */
            {
                if (dot[i][k] == dot[i][j])
                {
                    /* ���1��k���j����ȣ���ʱ�ϲ����鲢�Ʒ� */
                    dot[i][k++] *= 2;
                    scores += dot[i][k - 1];
                    dot[i][j] = 0;
                    cartoon();     //����
                    movevalue = 1; /* ��Ҫ�����������ˢ�½��� */
                }
                else if (dot[i][k] == 0)
                {
                    /* ���2��k��Ϊ�գ����j�ֵ��k��൱��j�����ƶ���k����
*/
                    dot[i][k] = dot[i][j];
                    dot[i][j] = 0;
                    cartoon(); //����
                    movevalue = 1;
                }
                else
                {
                    /* ���3��k�Ϊ�գ��Һ�j���ȣ���ʱ��j�ֵ��k+1���
�����ƶ���k+1��λ�� */
                    dot[i][++k] = dot[i][j];
                    if (j != k)
                    {
                        /* �ж�j���k���Ƿ�ԭ�ȾͰ���һ�����������j�ֵΪ��
��ֵΪ0�� */
                        dot[i][j] = 0;
                        cartoon(); //����
                        movevalue = 1;
                    }
                }
            }
        }
    }
    return movevalue;
}
int movedown()
{
    int movevalue = 0;
    int i;
    for (i = 0; i < 4; ++i)
    {
        int j, k;
        for (j = 2, k = 3; j >= 0; --j)
        {
            if (dot[i][j] > 0)
            {
                if (dot[i][k] == dot[i][j])
                {
                    dot[i][k--] *= 2;
                    scores += dot[i][k + 1];
                    dot[i][j] = 0;
                    cartoon(); //����
                    movevalue = 1;
                }
                else if (dot[i][k] == 0)
                {
                    dot[i][k] = dot[i][j];
                    dot[i][j] = 0;
                    cartoon(); //����
                    movevalue = 1;
                }
                else
                {
                    dot[i][--k] = dot[i][j];
                    if (j != k)
                    {
                        dot[i][j] = 0;
                        cartoon(); //����
                        movevalue = 1;
                    }
                }
            }
        }
    }
    return movevalue;
}
int moveleft()
{
    int movevalue = 0;
    int i;
    for (i = 0; i < 4; ++i)
    {
        int j, k;
        for (j = 1, k = 0; j < 4; ++j)
        {
            if (dot[j][i] > 0)
            {
                if (dot[k][i] == dot[j][i])
                {
                    dot[k++][i] *= 2;
                    scores += dot[k - 1][i];
                    dot[j][i] = 0;
                    cartoon(); //����
                    movevalue = 1;
                }
                else if (dot[k][i] == 0)
                {
                    dot[k][i] = dot[j][i];
                    dot[j][i] = 0;
                    cartoon(); //����
                    movevalue = 1;
                }
                else
                {
                    dot[++k][i] = dot[j][i];
                    if (j != k)
                    {
                        dot[j][i] = 0;
                        cartoon(); //����
                        movevalue = 1;
                    }
                }
            }
        }
    }
    return movevalue;
}
int moveright()
{
    int movevalue = 0;
    int i;
    for (i = 0; i < 4; ++i)
    {
        int j, k;
        for (j = 2, k = 3; j >= 0; --j)
        {
            if (dot[j][i] > 0)
            {
                if (dot[k][i] == dot[j][i])
                {
                    dot[k--][i] *= 2;
                    scores += dot[k + 1][i];
                    dot[j][i] = 0;
                    cartoon(); //����
                    movevalue = 1;
                }
                else if (dot[k][i] == 0)
                {
                    dot[k][i] = dot[j][i];
                    dot[j][i] = 0;
                    cartoon(); //����
                    movevalue = 1;
                }
                else
                {
                    dot[--k][i] = dot[j][i];
                    if (j != k)
                    {
                        dot[j][i] = 0;
                        cartoon(); //����
                        movevalue = 1;
                    }
                }
            }
        }
    }
    return movevalue;
}
int check()
{
    //����ָ��0:û���κμ���� 1��ʤ���Ҳ����� 2��ʤ���Ҽ�����Ϸ 3��ʤ���ؿ���Ϸ 4����Ϸʧ���ؿ� 5����Ϸʧ�ܲ��ؿ�
    //����Ƿ�ʤ��
    int result = 0;
    if (!goon)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (dot[i][j] == winscore)
                {
                    while (1)
                    {
                        draw();
                        printf("\n\n---------------------- 2048 ----------------------\n\n");
                        printf(" ʤ������\n\n");
                        printf("1.������Ϸ�����롪����������1\n");
                        printf("2.���¿�ʼ��Ϸ�����롪������2\n");
                        printf("3.�ص����˵������롪��������3\n");
                        printf("\n������ָ�");
                        char choose;
                        choose = getche();
                        if (choose == '1')
                        {
                            system("cls");
                            goon = 1;
                            return 2;
                        }
                        else if (choose == '2')
                        {
                            system("cls");
                            for (int i = 0; i < 4; i++)
                                for (int j = 0; j < 4; j++)
                                {
                                    dot[i][j] = 0;
                                }
                            goon = 0;
                            return 3;
                        }
                        else if (choose == '3')
                        {
                            system("cls");
                            for (int i = 0; i < 4; i++)
                                for (int j = 0; j < 4; j++)
                                {
                                    dot[i][j] = 0;
                                }
                            goon = 0;
                            return 1;
                        }
                        else
                        {
                            printf("\n\n\n�޷��������ָ��\n\n\n");
                            system("pause");
                            system("cls");
                        }
                    }
                }
            }
        }
    }
    //����Ƿ�ʧ��
    int fail = 1;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (dot[i][j] == 0)
                fail = 0;
            if (i != 0)
                if (dot[i][j] == dot[i - 1][j])
                    fail = 0;
            if (i != 3)
                if (dot[i][j] == dot[i + 1][j])
                    fail = 0;
            if (j != 0)
                if (dot[i][j] == dot[i][j - 1])
                    fail = 0;
            if (j != 3)
                if (dot[i][j] == dot[i][j + 1])
                    fail = 0;
        }
    }
    if (fail)
    {
        while (1)
        {
            draw();
            printf("\n\n---------------------- 2048 ----------------------\n\n");
            printf(" �������޿����ƶ������ӣ���\n\n");
            printf("1.���¿�ʼ��Ϸ�����롪������1\n");
            printf("2.�ص����˵������롪��������2\n");
            printf("3.���塪��������������������e\n");
            printf("\n������ָ�");
            char choose;
            choose = getche();
            if (choose == '1')
            {
                system("cls");
                for (int i = 0; i < 4; i++)
                    for (int j = 0; j < 4; j++)
                    {
                        dot[i][j] = 0;
                    }
                goon = 0;
                return 4;
            }
            else if (choose == '2')
            {
                system("cls");
                for (int i = 0; i < 4; i++)
                    for (int j = 0; j < 4; j++)
                    {
                        dot[i][j] = 0;
                    }
                goon = 0;
                return 5;
            }
            else if (choose == 'e' || choose == 'E')
            {
                if (regret())
                {
                    system("cls");
                    draw();
                    return 0;
                }
            }
            else
            {
                printf("\n\n\n�޷��������ָ��\n\n\n");
                system("pause");
                system("cls");
            }
        }
    }
    return 0;
}
int gamesave(int state)
{ //������Ϸ
    FILE *fp;
    fp = fopen("save.wavi", "w");
    if (fp == NULL)
        return -1;
    fprintf(fp, "%d\n", state);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            fprintf(fp, "%d ", dot[i][j]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
    return 0;
}
int gameload()
{ //������Ϸ
    FILE *fp;
    fp = fopen("save.wavi", "r");
    if (fp == NULL)
        return 0;
    int state = 0;
    fscanf(fp, "%d", &state);
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            fscanf(fp, "%d", &dot[i][j]);
    fclose(fp);
    return state;
}
int getscore()
{
    //�õ����ķ���
    FILE *fp;
    fp = fopen("score.wavi", "r");
    if (fp == NULL)
        return 0;
    int score = 0;
    fscanf(fp, "%d", &score);
    fclose(fp);
    return score;
}
int writescore()
{
    //д��������
    FILE *fp;
    fp = fopen("score.wavi", "w");
    if (fp == NULL)
        return -1;
    fprintf(fp, "%d", maxscore);
    fclose(fp);
    return 0;
}
void cartoon()
{
    //����Ч��
    if (cartoonstate)
    {
        sleep(30);
        draw();
    }
}
void clear_screen()
{
    COORD pos = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    CONSOLE_CURSOR_INFO info = {1, 0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}
int regret()
{
    if (RegretTimes > 0)
    {
        RegretTimes--;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                dot[i][j] = save[RegretTimes][i][j];
            }
        }
        scores = savedScores[RegretTimes];
        draw();
        return 1;
    }
    else
    {
        printf("\n\n ");
        setColor(15, 12);
        printf("��ǰ��ʣ����岽��");
        printf(" \n\n");
        setColor(0, 15);
        system("pause");
        system("cls");
        draw();
        return 0;
    }
}
void regretSave()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (RegretTimes == 5)
            {
                save[0][i][j] = save[1][i][j];
                save[1][i][j] = save[2][i][j];
                save[2][i][j] = save[3][i][j];
                save[3][i][j] = save[4][i][j];
                save[4][i][j] = save[5][i][j];
            }
            else if (RegretTimes == 4)
            {
                save[4][i][j] = save[5][i][j];
            }
            else if (RegretTimes == 3)
            {
                save[3][i][j] = save[5][i][j];
            }
            else if (RegretTimes == 2)
            {
                save[2][i][j] = save[5][i][j];
            }
            else if (RegretTimes == 1)
            {
                save[1][i][j] = save[5][i][j];
            }
            else if (RegretTimes == 0)
            {
                save[0][i][j] = save[5][i][j];
            }
        }
    }
    if (RegretTimes == 5)
    {
        savedScores[0] = savedScores[1];
        savedScores[1] = savedScores[2];
        savedScores[2] = savedScores[3];
        savedScores[3] = savedScores[4];
        savedScores[4] = savedScores[5];
    }
    else if (RegretTimes == 4)
    {
        savedScores[4] = savedScores[5];
    }
    else if (RegretTimes == 3)
    {
        savedScores[3] = savedScores[5];
    }
    else if (RegretTimes == 2)
    {
        savedScores[2] = savedScores[5];
    }
    else if (RegretTimes == 1)
    {
        savedScores[1] = savedScores[5];
    }
    else if (RegretTimes == 0)
    {
        savedScores[0] = savedScores[5];
    }
    if (RegretTimes < 5)
        RegretTimes++; //ÿ�ƶ�һ�λ��岽����һ,�����������
}
char tips()
{
    //δ�����...
    int scorenumber[4] = {0};
    for (int i = 0; i < 4; i++)
    {
        if (i > 0)
        {
            for (int j = 0; j < 3; j++)
            {
                if (dot[i][j] == dot[i - 1][j])
                {
                }
            }
        }
        if (i < 3)
        {
        }
    }
    return 'w';
}