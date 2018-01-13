#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<conio.h>
#include<time.h>

//--------------------------------------------------------------------------------------------̰����ģ��

char gamemap[20][40];//��Ϸ��ͼ��С 20*40
int choose;
int choose2;//���ѭ������
int m = 0;//���������Լ�ѭ���������
int score[10] = {0};//��ǰ����,�������10������ 
				   //��¼�ߵĽ��
int x[800];//ÿ�������б��
int y[800];//ÿ�������б��
int len = 0;//�ߵĳ���

			//��¼ˮ����Ϣ 
int fx = 0;//ʳ��ĺ����� 
int fy = 0;//ʳ��������� 
int fcount = 0;//ʳ�����Ŀ 

			   //��Ҫ�������� 
void createfood();//����ʳ�� 
void PrintgameMap(int x[], int y[]);//����Ϸ��ͼ 
void move(int x[], int y[]);//�ƶ��� 

int snakegame()
{
	srand(time(NULL));
	//��ʼ����ͷ�������λ��,Ĭ�ϸտ�ʼ�߳�Ϊ2 
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
		int have = 0;//Ϊ0��ʾʳ�ﲻ��ʳ���һ���� 
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
			if (1 == have)//���Ϊ�ߵ�һ���֣���һ��ѭ�� 
			{
				continue;
			}
			else//���������µ�ˮ�� 
			{
				fcount++;
				fx = tfx;
				fy = tfy;
				break;
			}
		}

	}
}
//��Ϸ��ͼ
void PrintgameMap(int x[], int y[],int score[])
{
	int snake = 0, food = 0;

	int i, j;
	//����Ϸ��ͼ,�������ߵĳ�ʼλ��
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
			//�ж����Ƿ��ڵ�ǰλ��
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
			//������ڵ�ǰλ��
			if (1 == snake)
			{
				printf("*");
			}
			else if (1 == food)
			{
				printf("O");
			}
			//����߲��ڵ�ǰλ�ò��ҵ�ǰλ��û��ˮ�� 
			else
			{
				printf("%c", gamemap[i][j]);
			}

		}
		printf("\n");

	}

	printf("score:%d", score[m]);
}
//�ƶ�
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
		//ͷ

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

		//����
		int i;
		for (i = 1; i < len; i++)
		{

			x[i] = cx[i - 1];
			y[i] = cy[i - 1];

		}
		for (i = 1; i<len; i++)//ҧ���Լ� 
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
			if (fcount&&x[0] == fx&&y[0] == fy)//����Ե��˹���
			{
				//������ǰ��ͷ��ַ���ڶ������ 
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
		if (kbhit())//�ж��Ƿ��°��� 
		{
			s = getch();
		}

	}

}
//--------------------------------------------------------------------------------------------------̰����ģ��

int main()
{
	do
	{
		printf("*********************************************\n");
		printf("*                ̰������Ϸ                 *\n");
		printf("*              (����������1~0)              *\n");
		printf("*-------------------------------------------*\n");
		printf("*                1:��ʼ��Ϸ                 *\n");
		printf("*                2:��������ϵͳ             *\n");
		printf("*                                           *\n");
		printf("*                0:��������                 *\n");
		printf("*********************************************\n");
		printf("�����ѡ��\n");
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
					printf("\nError!\n");//��������ļ�   
					exit(0);
				}
				fprintf(fp, "%10d%10d\n", m, score[m]);
				fclose(fp);//�ļ�����
			}
			else
			{
				fp = fopen("D:\\file.txt", "a+");
				fseek(fp, 0, SEEK_END);
				if (fp == NULL)
				{
					printf("\nError!\n");//��������ļ�   
					exit(0);
				}
				fprintf(fp, "%10d%10d\n", m, score[m]);
				fclose(fp);
			}

			break;//��Ϸ����
		}//1��һ�� ��������OK~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		case'2':
		{
			goto stop;
			break;
		}//2
		case'0':
		{
			printf("�ټ�");
			exit(0);
		}//0
		default:
		{
			printf("����������1~2��0,лл\n");
			break;
		}//default
		}//switch
		m++;
		printf("�Ƿ�Ҫ�ٴ�ѡ��,������y/n(yes or no)\n");
		do
		{
			choose = getch();
		} while (choose != 'y'&&choose != 'n');//do
	} while (choose == 'y');//do
		printf("�ټ�\n");
		exit(0);
		//------------------------------------------------------------------��һ��do-whilḛ������Ϸ

	stop:
		do
		{
			printf("*********************************************\n");
			printf("*                ��������ϵͳ               *\n");
			printf("*              (����������1~0)              *\n");
			printf("*-------------------------------------------*\n");
			printf("*                1:������                   *\n");
			printf("*                2:���ҷ���                 *\n");
			printf("*                3:��߷�                   *\n");
			printf("*                4:ɾ����¼                 *\n");
			printf("*                5:��������                 *\n");
			printf("*                                           *\n");
			printf("*                0:��������                 *\n");
			printf("*********************************************\n");
			printf("�����ѡ��\n");
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
				printf("������\n");
				while (feof(fp) == 0)
				{
					for(z=0;z<=10;z++)
					fscanf(fp, "%d%d\n", &lalala[z].a, &lalala[z].b);
					for (z = 0; z < 10; z++)
					{
						printf("��%d����Ϸ ������%d\n",lalala[z].a+1,lalala[z].b);
					}
					break;
				}
				fclose(fp);
				break;//���
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
				printf("\n������Ҫ���ҵ���Ϸ������");
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
					printf("��%d�� ������%d\n", x, t);
				}
				else
					printf("����Ϸ����������\n");
				break;//
			}//2//����ok~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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
				printf("��߷���%d\n", maxscore);
				break;//�������Ƚϸ�ֵ
			}//3��߷�OK~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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
				printf("��ɾ���ķ����ڵڼ�λ:");
				scanf("%d", &k);
				if (k <= 10)
				{
					for (int i = 0; i <= 10; i++)
						if (i == k-1)
						{
							t = i;
							break;
						}//for
					for (int j = t; j <= 10; j++)//��󴢴�10λ
						lalala[j].b = lalala[j + 1].b;
				}
				else
					printf("û�н��иô���Ϸ");
				for (n = 0; n <= 10; n++)
				{
					if (n == 0)
					{
						fip = fopen("D:\\tmp.txt", "w");
						if (fip == NULL)
						{
							printf("\nError!\n");//��������ļ�   
							exit(0);
						}
						fprintf(fip, "%10d%10d\n", lalala[n].a, lalala[n].b);
						fclose(fip);//�ļ�����
					}
					else
					{
						fip = fopen("D:\\tmp.txt", "a+");
						fseek(fip, 0, SEEK_END);
						if (fip == NULL)
						{
							printf("\nError!\n");//��������ļ�   
							exit(0);
						}
						fprintf(fip, "%10d%10d\n", lalala[n].a, lalala[n].b);
						fclose(fip);
					}
				}
				remove("D:\\file.txt");
				rename("D:\\tmp.txt", "D:\\file.txt");
				break;//�½���ʱ�ļ�rename
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
						}//ð�ݷ��Ƚϴ�С����
				printf("�����ѳɹ���\n");
				for (n = 0; n <= 10; n++)
				{
					if (n == 0)
					{
						fip = fopen("D:\\tmp.txt", "w");
						if (fip == NULL)
						{
							printf("\nError!\n");//��������ļ�   
							exit(0);
						}
						fprintf(fip, "%10d%10d\n", lalala[n].a, lalala[n].b);
						fclose(fip);//�ļ�����
					}
					else
					{
						fip = fopen("D:\\tmp.txt", "a+");
						fseek(fip, 0, SEEK_END);
						if (fip == NULL)
						{
							printf("\nError!\n");//��������ļ�   
							exit(0);
						}
						fprintf(fip, "%10d%10d\n", lalala[n].a, lalala[n].b);
						fclose(fip);
					}
				}
				remove("D:\\file.txt");
				rename("D:\\tmp.txt", "D:\\file.txt");
				break;//ð�ݷ�
			}//5
			case'0':
			{
				printf("�ټ�\n");
				exit(0);
				break;
			}//0
			default:
			{
				printf("����������1~5��0,лл\n");
				break;
			}//default



			}//switch
			printf("�Ƿ�Ҫ�ٴ�ѡ��,������y/n(yes or no)\n");
			do
			{
				choose = getch();
			} while (choose != 'y'&&choose != 'n');//do
		} while (choose == 'y');//do
		printf("�Ƿ�Ҫ������Ϸ,������y/n(yes or no)\n");
		printf("�ټ�\n");
		exit(0);
		do
		{
			choose2 = getch();
		} while (choose2 != 'y'&&choose2 != 'n');//do------------------------------------------------------------------------------�ڶ���do-while��������ϵͳ
} //main