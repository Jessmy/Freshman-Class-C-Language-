#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<conio.h>
#include<time.h>

//--------------------------------------------------------------------------------------------贪吃蛇模块

char gamemap[20][40];//游戏地图大小 20*40
int choose;
int choose2;//最后循环声明
int m = 0;//分数数组以及循环次数相关
int score[10] = {0};//当前分数,最大容纳10组数据 
				   //记录蛇的结点
int x[800];//每个结点的行编号
int y[800];//每个结点的列编号
int len = 0;//蛇的长度

			//记录水果信息 
int fx = 0;//食物的横坐标 
int fy = 0;//食物的纵坐标 
int fcount = 0;//食物的数目 

			   //主要函数操作 
void createfood();//生成食物 
void PrintgameMap(int x[], int y[]);//画游戏地图 
void move(int x[], int y[]);//移动蛇 

int snakegame()
{
	srand(time(NULL));
	//初始化蛇头和身体的位置,默认刚开始蛇长为2 
	x[len] = 9;
	y[len] = 9;
	len++;
	x[len] = 9;
	y[len] = 8;
	len++;

	createfood();
	PrintgameMap(x, y,score);
	move(x, y);
	printf("score:%d\n", score[m]);//=======================================================================OK
}

void createfood()
{
	if (0 == fcount)
	{
		int tfx = rand() % 18 + 1;
		int tfy = rand() % 38 + 1;
		int i, j;
		int have = 0;//为0表示食物不是食物的一部分 
		for (i = 0; i<len; i++)
		{
			for (j = 0; j<len; j++)
			{
				if (x[i] == fx&&y[j] == fy)
				{
					have = 1;
					break;
				}
				else
				{
					have = 0;
				}
			}
			if (1 == have)//如果为蛇的一部分，下一次循环 
			{
				continue;
			}
			else//否则生成新的水果 
			{
				fcount++;
				fx = tfx;
				fy = tfy;
				break;
			}
		}

	}
}
//游戏地图
void PrintgameMap(int x[], int y[],int score[])
{
	int snake = 0, food = 0;

	int i, j;
	//画游戏地图,并画出蛇的初始位置
	for (i = 0; i < 20; i++)
	{
		for (j = 0; j < 40; j++)
		{
			if (i == 0 && j >= 1 && j <= 38)
			{
				gamemap[i][j] = '=';

			}
			else if (i == 19 && j >= 1 && j <= 38)
			{
				gamemap[i][j] = '=';
			}
			else if (j == 0 || j == 39)
			{
				gamemap[i][j] = '||';
			}
			else
			{
				gamemap[i][j] = ' ';
			}
			//判断蛇是否在当前位置
			int k;
			for (k = 0; k < len; k++)
			{

				if (i == x[k] && j == y[k])
				{
					snake = 1;
					break;
				}
				else
				{
					snake = 0;
				}
			}
			{
				if (fcount&&fx == i&&fy == j)
				{
					food = 1;
				}
				else
				{
					food = 0;
				}
			}
			//如果蛇在当前位置
			if (1 == snake)
			{
				printf("*");
			}
			else if (1 == food)
			{
				printf("O");
			}
			//如果蛇不在当前位置并且当前位置没有水果 
			else
			{
				printf("%c", gamemap[i][j]);
			}

		}
		printf("\n");

	}

	printf("score:%d", score[m]);
}
//移动
void move(int x[], int y[])
{
	char s;
	s = getch();
	int move = 0, beat = 0;
	while (1)
	{

		int cx[800];
		int cy[800];
		memcpy(cx, x, sizeof(int)*len);
		memcpy(cy, y, sizeof(int)*len);
		//头

		if (s == 'w')
		{

			x[0]--;
			move = 1;
			if (x[0] <= 0)
			{
				printf("\nGame over\n");
				break;
			}

		}
		else if (s == 's')
		{
			x[0]++;
			move = 1;
			if (x[0] >= 19)
			{
				printf("\nGame over\n");
				break;
			}

		}
		else if (s == 'a')
		{
			y[0] --;
			move = 1;
			if (y[0] <= 0)
			{
				printf("\nGame over\n");
				break;
			}

		}
		else if (s == 'd')
		{
			y[0]++;
			move = 1;
			if (y[0] >= 39)
			{
				printf("\nGame over\n");
				break;
			}
		}

		//身体
		int i;
		for (i = 1; i < len; i++)
		{

			x[i] = cx[i - 1];
			y[i] = cy[i - 1];

		}
		for (i = 1; i<len; i++)//咬到自己 
		{
			if (x[0] == x[i] && y[0] == y[i])
			{
				beat = 1;
			}
			else
			{
				beat = 0;
			}
		}
		if (1 == beat)
		{
			printf("\nGame over\n");
			break;
		}
		if (1 == move)
		{
			if (fcount&&x[0] == fx&&y[0] == fy)//如果吃到了果子
			{
				//拷贝当前蛇头地址到第二个结点 
				memcpy(x + 1, cx, sizeof(int)*len);
				memcpy(y + 1, cy, sizeof(int)*len);
				len++;
				fcount--;
				fx = 0;
				fy = 0;
				score[m]++;
				createfood();
			}
			Sleep(70);
			system("cls");
			PrintgameMap(x, y,score);

		}
		else
			continue;
		if (kbhit())//判断是否按下按键 
		{
			s = getch();
		}

	}

}
//--------------------------------------------------------------------------------------------------贪吃蛇模块

int main()
{
	do
	{
		printf("*********************************************\n");
		printf("*                贪吃蛇游戏                 *\n");
		printf("*              (请输入数字1~0)              *\n");
		printf("*-------------------------------------------*\n");
		printf("*                1:开始游戏                 *\n");
		printf("*                2:分数管理系统             *\n");
		printf("*                                           *\n");
		printf("*                0:结束程序                 *\n");
		printf("*********************************************\n");
		printf("请进行选择\n");
		int key;
		key = getch();
		switch (key)
		{
		case'1':
		{
			snakegame();
			FILE*fp = NULL;
			if (m == 0)
			{
				fp = fopen("D:\\file.txt", "w");
				if (fp == NULL)
				{
					printf("\nError!\n");//检查有无文件   
					exit(0);
				}
				fprintf(fp, "%10d%10d\n", m, score[m]);
				fclose(fp);//文件输入
			}
			else
			{
				fp = fopen("D:\\file.txt", "a+");
				fseek(fp, 0, SEEK_END);
				if (fp == NULL)
				{
					printf("\nError!\n");//检查有无文件   
					exit(0);
				}
				fprintf(fp, "%10d%10d\n", m, score[m]);
				fclose(fp);
			}

			break;//游戏程序
		}//1第一部 数据输入OK~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		case'2':
		{
			goto stop;
			break;
		}//2
		case'0':
		{
			printf("再见");
			exit(0);
		}//0
		default:
		{
			printf("请输入数字1~2或0,谢谢\n");
			break;
		}//default
		}//switch
		m++;
		printf("是否还要再次选择,请输入y/n(yes or no)\n");
		do
		{
			choose = getch();
		} while (choose != 'y'&&choose != 'n');//do
	} while (choose == 'y');//do
		printf("再见\n");
		exit(0);
		//------------------------------------------------------------------第一个do-while贪吃蛇游戏

	stop:
		do
		{
			printf("*********************************************\n");
			printf("*                分数管理系统               *\n");
			printf("*              (请输入数字1~0)              *\n");
			printf("*-------------------------------------------*\n");
			printf("*                1:分数榜                   *\n");
			printf("*                2:查找分数                 *\n");
			printf("*                3:最高分                   *\n");
			printf("*                4:删除记录                 *\n");
			printf("*                5:分数排序                 *\n");
			printf("*                                           *\n");
			printf("*                0:结束程序                 *\n");
			printf("*********************************************\n");
			printf("请进行选择\n");
			int key;
			key = getch();
			switch (key)
			{
			case'1':
			{
				int z = 0;
				struct st
				{
					int a;
					int b;
				}; struct st lalala[10] = { 0 };
				FILE*fp = NULL;
				fp = fopen("D:\\file.txt", "r");
				if (fp == NULL)
				{
					printf("\nError!\n");
					exit(0);
				}
				printf("分数榜：\n");
				while (feof(fp) == 0)
				{
					for(z=0;z<=10;z++)
					fscanf(fp, "%d%d\n", &lalala[z].a, &lalala[z].b);
					for (z = 0; z < 10; z++)
					{
						printf("第%d次游戏 分数：%d\n",lalala[z].a+1,lalala[z].b);
					}
					break;
				}
				fclose(fp);
				break;//输出
			}//1
			case'2':
			{
				int n = 0,x=0,i=0,t=0;
				int z = 0;
				struct st
				{
					int a;
					int b;
				}; struct st lalala[10] = { 0 };
				FILE*fp = NULL;
				fp = fopen("D:\\file.txt", "r");
				if (fp == NULL)
				{
					printf("\nError!\n");
					exit(0);
				}
				while (feof(fp) == 0)
				{
					for (z = 0; z <= 10; z++)
						fscanf(fp, "%d%d\n", &lalala[z].a, &lalala[z].b);
					break;
				}
				fclose(fp);
				printf("\n请输入要查找的游戏次数：");
				scanf("%d", &x);
				if (x <= 10)
				{
					for (i = 0; i <= 10; i++)
					{
						if (x == lalala[i].a + 1)
						{
							t = lalala[i].b;
							goto next;
						}
					}
					next:
					printf("第%d次 分数：%d\n", x, t);
				}
				else
					printf("该游戏次数不存在\n");
				break;//
			}//2//查找ok~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			case'3':
			{
				int n = 0, x = 0, i = 0;
				int z = 0;
				struct st
				{
					int a;
					int b;
				}; struct st lalala[10] = { 0 };
				FILE*fp = NULL;
				fp = fopen("D:\\file.txt", "r");
				if (fp == NULL)
				{
					printf("\nError!\n");
					exit(0);
				}
				while (feof(fp) == 0)
				{
					for (z = 0; z <= 10; z++)
						fscanf(fp, "%d%d\n", &lalala[z].a, &lalala[z].b);
					break;
				}
				fclose(fp);
				int maxscore = 0;
				for (int i = 0; i <= 10; i++)
				{
					if (maxscore < lalala[i].b)
						maxscore = lalala[i].b;//
				}//for
				printf("最高分是%d\n", maxscore);
				break;//两个数比较赋值
			}//3最高分OK~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			case'4':
			{
				int n = 0, x = 0, i = 0;
				int z = 0;
				struct st
				{
					int a;
					int b;
				}; struct st lalala[10] = { 0 };
				FILE*fp = NULL;
				FILE*fip = NULL;
				fp = fopen("D:\\file.txt", "r");
				if (fp == NULL)
				{
					printf("\nError!\n");
					exit(0);
				}
				while (feof(fp) == 0)
				{
					for (z = 0; z <= 10; z++)
						fscanf(fp, "%d%d\n", &lalala[z].a, &lalala[z].b);
					break;
				}
				fclose(fp);
				int k, t;
				printf("待删除的分数于第几位:");
				scanf("%d", &k);
				if (k <= 10)
				{
					for (int i = 0; i <= 10; i++)
						if (i == k-1)
						{
							t = i;
							break;
						}//for
					for (int j = t; j <= 10; j++)//最大储存10位
						lalala[j].b = lalala[j + 1].b;
				}
				else
					printf("没有进行该次游戏");
				for (n = 0; n <= 10; n++)
				{
					if (n == 0)
					{
						fip = fopen("D:\\tmp.txt", "w");
						if (fip == NULL)
						{
							printf("\nError!\n");//检查有无文件   
							exit(0);
						}
						fprintf(fip, "%10d%10d\n", lalala[n].a, lalala[n].b);
						fclose(fip);//文件输入
					}
					else
					{
						fip = fopen("D:\\tmp.txt", "a+");
						fseek(fip, 0, SEEK_END);
						if (fip == NULL)
						{
							printf("\nError!\n");//检查有无文件   
							exit(0);
						}
						fprintf(fip, "%10d%10d\n", lalala[n].a, lalala[n].b);
						fclose(fip);
					}
				}
				remove("D:\\file.txt");
				rename("D:\\tmp.txt", "D:\\file.txt");
				break;//新建临时文件rename
			}//4

			case'5':
			{
				int n = 0, x = 0, i = 0;
				int z = 0;
				struct st
				{
					int a;
					int b;
				}; struct st lalala[10] = { 0 };
				FILE*fp = NULL;
				FILE*fip = NULL;
				fp = fopen("D:\\file.txt", "r");
				if (fp == NULL)
				{
					printf("\nError!\n");
					exit(0);
				}
				while (feof(fp) == 0)
				{
					for (z = 0; z <= 10; z++)
						fscanf(fp, "%d%d\n", &lalala[z].a, &lalala[z].b);
					break;
				}
				fclose(fp);
				int t, j, k;
				for (j = 0; j <= m; j++)
					for (t = 0; t < 10 - 1 - j; t++)
						if (lalala[t].b < lalala[t+1].b)
						{
							k = lalala[t].b;
							lalala[t].b = lalala[t + 1].b;
							lalala[t + 1].b = k;
						}//冒泡法比较大小排序
				printf("排序已成功！\n");
				for (n = 0; n <= 10; n++)
				{
					if (n == 0)
					{
						fip = fopen("D:\\tmp.txt", "w");
						if (fip == NULL)
						{
							printf("\nError!\n");//检查有无文件   
							exit(0);
						}
						fprintf(fip, "%10d%10d\n", lalala[n].a, lalala[n].b);
						fclose(fip);//文件输入
					}
					else
					{
						fip = fopen("D:\\tmp.txt", "a+");
						fseek(fip, 0, SEEK_END);
						if (fip == NULL)
						{
							printf("\nError!\n");//检查有无文件   
							exit(0);
						}
						fprintf(fip, "%10d%10d\n", lalala[n].a, lalala[n].b);
						fclose(fip);
					}
				}
				remove("D:\\file.txt");
				rename("D:\\tmp.txt", "D:\\file.txt");
				break;//冒泡法
			}//5
			case'0':
			{
				printf("再见\n");
				exit(0);
				break;
			}//0
			default:
			{
				printf("请输入数字1~5或0,谢谢\n");
				break;
			}//default



			}//switch
			printf("是否还要再次选择,请输入y/n(yes or no)\n");
			do
			{
				choose = getch();
			} while (choose != 'y'&&choose != 'n');//do
		} while (choose == 'y');//do
		printf("是否还要进行游戏,请输入y/n(yes or no)\n");
		printf("再见\n");
		exit(0);
		do
		{
			choose2 = getch();
		} while (choose2 != 'y'&&choose2 != 'n');//do------------------------------------------------------------------------------第二个do-while分数管理系统
} //main