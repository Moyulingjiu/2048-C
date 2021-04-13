#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <Mmsystem.h> //音频
#include <direct.h>   //路径
#pragma warning(disable : 4996)
#pragma warning(disable : 26451)
#pragma comment(lib, "winmm.lib")
int dot[4][4] = {0};          //4*4的棋盘矩阵
int save[6][4][4] = {0};      //悔棋保存的棋盘
int goon = 0;                 //检测游戏是否处在胜利后继续玩的情况
int maxscore = 0;             //获取游戏最大的分数
int cartoonstate = 1;         //开启或则关闭动画效果
int RegretTimes = 0;          //悔棋步数
const int soudnumber = 64;    //播放声音的数字
const int winscore = 2048;    //胜利条件
int scores = 0;               //分数
int savedScores[6] = {0};     //保存的分数
void rule();                  //规则介绍
void developer();             //开发者名单
void cleardata();             //清除数据
int starts();                 //开始
int random(int min, int max); //随机数
void newpoint(int num);       //生成新棋子
void draw();                  //绘制棋盘
void sleep(unsigned int num); //暂停
int moveup();                 //上移
int movedown();               //下移
int moveleft();               //左移
int moveright();              //右移
int quit();                   //退回到主菜单
int remake();                 //检测是否重新开始游戏
int check();                  //检查是否胜利或则游戏结束
int gamesave(int state);      //保存游戏
int gameload();               //加载游戏
int getscore();               //获取最大分数
int writescore();             //写入最大分数
void cartoon();               //动画效果
void clear_screen();          //清除屏幕显示
int regret();                 //悔棋
void regretSave();            //记录悔棋的信息
char tips();                  //方向提示（目前先写最简陋的算法，只预测下一步的最有利情况，不假设多步）
void setColor(unsigned short ForeColor, unsigned short BackGroundColor)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);                     //获取当前窗口句柄
    SetConsoleTextAttribute(handle, ForeColor + BackGroundColor * 0x10); //设置颜色
}
//设置光标位置
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
        //LoadKeyboardLayout(L"0x409", KLF_ACTIVATE | KLF_SETFORPROCESS); //切换输入法至英文
        printf(" ----------- 2048 -----------\n\n");
        printf(" 1.");
        setColor(15, 12);
        printf("开始游戏");
        setColor(0, 15);
        printf("—————————1\n");
        printf(" 2.查看游戏规则———————2\n");
        printf(" 3.查看开发者名单——————3\n");
        printf(" 4.清除游戏所有记录—————4\n");
        if (cartoonstate)
        {
            printf(" 5.");
            setColor(1, 15);
            printf("关闭");
            setColor(0, 15);
            printf("动画效果———————5\n");
        }
        else
        {
            printf(" 5.");
            setColor(1, 15);
            printf("开启");
            setColor(0, 15);
            printf("动画效果———————5\n");
        }
        printf(" 6.退出游戏—————————6\n");
        printf("\n 请输入指令：");
        char contorl;
        contorl = getch();
        fflush(stdin);
        printf("\n\n 正在处理指令，请稍后……");
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
    //规则
    printf("\n\n----------- 2048 -----------\n\n");
    printf("游戏规则：\n 1、2048有一个4*4的棋盘。\n");
    printf(" 2、开始时棋盘内随机出现两个数字，出现的数字仅可能为2或4。\n");
    printf(" 3、玩家可以选择上下左右四个方向，棋盘内的棋子按该方向位移。\n");
    printf(" a) 若有棋子在移动方向的一侧（如：右侧）为空，则将其移动到该位。\n");
    printf(" b) 若有棋子在移动方向的一侧（如：右侧）为同样的数字，则将其与该侧数字相加。不可将两个以上数字相加。\n");
    printf(" c) 若该方向无棋子满足a)或b)条件，则不移动棋子。\n");
    printf(" 4、每有效移动一步，棋盘的空位（无数字处）随机出现一个数字（为2或 4）。\n");
    printf(" 5、若四个方向都满足第3条c)规则，则判负。\n");
    printf(" 6、若出现2048，则判胜。\n");
    printf(" 7、输入\"Q\"则可以回到主菜单。\n");
    printf(" 7、输入\"E\"则可以悔棋，请注意最多只可以悔棋五步。\n");
    printf(" 8、输入\"R\"即可重开游戏。\n\n");
    system("pause");
    system("cls");
}
void developer()
{
    //开发者信息
    printf("\n\n----------- 2048 -----------\n\n");
    printf("游戏名字：2048\n");
    printf("开发案语言主体：C/C++\n");
    printf("版本号：v0.1.4\n");
    printf("开发人员：墨羽\n\n");
    printf("Copyright @ 2019, 墨羽 all rights reserved.\n\n");
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
        printf("确定要清除所有数据吗？您将会失去保存的游戏进度和历史最高分（Y/N）：");
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
            printf("删除完成!!");
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
    //游戏开始
    //system("color 0f");
    if (gameload() == 1)
    {
        maxscore = getscore(); //得到最大分数
        while (1)
        {
            printf("\n\n ----------- 2048 -----------\n\n");
            printf(" 检测到有未完成的游戏是否继续[Y/N]：");
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
                newpoint(2); //随机生成两个新数字
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
        newpoint(2); //随机生成两个新数字
    }
    RegretTimes = 0;
    gamesave(1); //保存游戏
    draw();      //绘制棋盘
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
                getnewpoint = moveup(); //上移
            else if (command == 's' || command == 'S')
                getnewpoint = movedown(); //下移
            else if (command == 'a' || command == 'A')
                getnewpoint = moveleft(); //左移
            else if (command == 'd' || command == 'D')
                getnewpoint = moveright(); //右移
            if (getnewpoint)
            {
                newpoint(1);  //生成一个新的数字
                gamesave(1);  //保存游戏
                regretSave(); //记录棋盘信息
            }
            draw();               //绘制棋盘
            int reslut = check(); //检查是否胜利或则游戏结束
            if (reslut == 1 || reslut == 5)
            {
                gamesave(0); //取消保存游戏
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
                gamesave(1); //保存游戏
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
                gamesave(1); //保存游戏
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
} //游戏开始
int quit()
{
    while (1)
    {
        system("cls");
        printf("\n\n ---------------------- 2048 ----------------------\n\n");
        printf(" 确定要回到主菜单吗？我们会保存您的游戏记录（Y/N）：");
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
        printf(" 确定要重新开始吗？您将会失去当前的游戏进度（Y/N）：");
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
    //随机数
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
    //程序休眠一段时间，保证随机数不一样;num的单位为ms
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
    clear_screen(); //清除屏幕
    //最大分数检测
    if (scores >= maxscore)
    {
        maxscore = scores;
        writescore();
    }
    printf("\n\n ---------------------------- 2048 ----------------------------\n\n");
    printf(" ┌──────────────┬──────────────┬──────────────┬──────────────┐\n");
    printf(" │              │              │              │              │      当前分数：%d\n", scores);
    for (int i = 0; i < 4; i++)
    {
        printf(" ");
        for (int j = 0; j < 4; j++)
        {
            if (dot[j][i] != 0)
                printf("│ %12d ", dot[j][i]);
            else
                printf("│              ");
        }
        printf("│\n");
        if (i != 3)
        {
            if (i == 0)
                printf(" │              │              │              │              │      历史最高：%d\n", maxscore);
            else
                printf(" │              │              │              │              │\n");
            printf(" ├──────────────┼──────────────┼──────────────┼──────────────┤\n");
            printf(" │              │              │              │              │\n");
        }
    }
    printf(" │              │              │              │              │\n");
    printf(" └──────────────┴──────────────┴──────────────┴──────────────┘\n");
    printf("\n 当前剩余悔棋步数：%d", RegretTimes);
    printf("\n （向左：A、向下：S、向右：D、向上：W、悔棋：E、退回主菜单：Q、重新开始：R)\n");
    //printf(" 目前操作：");
    fflush(0);
}
int moveup()
{
    int movevalue = 0;
    int i;
    for (i = 0; i < 4; ++i)
    {
        /* 变量j为列下标，变量k为待比较（合并）项的下标，循环进入时k<j */
        int j, k;
        for (j = 1, k = 0; j < 4; ++j)
        {
            if (dot[i][j] > 0) /* 找出k后面第一个不为空的项，下标为j，之后分三种
情况 */
            {
                if (dot[i][k] == dot[i][j])
                {
                    /* 情况1：k项和j项相等，此时合并方块并计分 */
                    dot[i][k++] *= 2;
                    scores += dot[i][k - 1];
                    dot[i][j] = 0;
                    cartoon();     //动画
                    movevalue = 1; /* 需要生成随机数和刷新界面 */
                }
                else if (dot[i][k] == 0)
                {
                    /* 情况2：k项为空，则把j项赋值给k项，相当于j方块移动到k方块
*/
                    dot[i][k] = dot[i][j];
                    dot[i][j] = 0;
                    cartoon(); //动画
                    movevalue = 1;
                }
                else
                {
                    /* 情况3：k项不为空，且和j项不相等，此时把j项赋值给k+1项，相
当于移动到k+1的位置 */
                    dot[i][++k] = dot[i][j];
                    if (j != k)
                    {
                        /* 判断j项和k项是否原先就挨在一起，若不是则把j项赋值为空
（值为0） */
                        dot[i][j] = 0;
                        cartoon(); //动画
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
                    cartoon(); //动画
                    movevalue = 1;
                }
                else if (dot[i][k] == 0)
                {
                    dot[i][k] = dot[i][j];
                    dot[i][j] = 0;
                    cartoon(); //动画
                    movevalue = 1;
                }
                else
                {
                    dot[i][--k] = dot[i][j];
                    if (j != k)
                    {
                        dot[i][j] = 0;
                        cartoon(); //动画
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
                    cartoon(); //动画
                    movevalue = 1;
                }
                else if (dot[k][i] == 0)
                {
                    dot[k][i] = dot[j][i];
                    dot[j][i] = 0;
                    cartoon(); //动画
                    movevalue = 1;
                }
                else
                {
                    dot[++k][i] = dot[j][i];
                    if (j != k)
                    {
                        dot[j][i] = 0;
                        cartoon(); //动画
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
                    cartoon(); //动画
                    movevalue = 1;
                }
                else if (dot[k][i] == 0)
                {
                    dot[k][i] = dot[j][i];
                    dot[j][i] = 0;
                    cartoon(); //动画
                    movevalue = 1;
                }
                else
                {
                    dot[--k][i] = dot[j][i];
                    if (j != k)
                    {
                        dot[j][i] = 0;
                        cartoon(); //动画
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
    //返回指令0:没有任何检测结果 1：胜利且不继续 2：胜利且继续游戏 3：胜利重开游戏 4：游戏失败重开 5：游戏失败不重开
    //检查是否胜利
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
                        printf(" 胜利！！\n\n");
                        printf("1.继续游戏请输入——————1\n");
                        printf("2.重新开始游戏请输入————2\n");
                        printf("3.回到主菜单请输入—————3\n");
                        printf("\n请输入指令：");
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
                            printf("\n\n\n无法理解您的指令\n\n\n");
                            system("pause");
                            system("cls");
                        }
                    }
                }
            }
        }
    }
    //检查是否失败
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
            printf(" 场上再无可以移动的棋子！！\n\n");
            printf("1.重新开始游戏请输入————1\n");
            printf("2.回到主菜单请输入—————2\n");
            printf("3.悔棋———————————e\n");
            printf("\n请输入指令：");
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
                printf("\n\n\n无法理解您的指令\n\n\n");
                system("pause");
                system("cls");
            }
        }
    }
    return 0;
}
int gamesave(int state)
{ //保存游戏
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
{ //加载游戏
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
    //得到最大的分数
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
    //写出最大分数
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
    //动画效果
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
        printf("当前无剩余悔棋步数");
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
        RegretTimes++; //每移动一次悔棋步数加一,最多三步悔棋
}
char tips()
{
    //未完待续...
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