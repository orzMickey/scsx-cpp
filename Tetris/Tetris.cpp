#include<iostream>
#include<string>
#include<cstdlib>
#include<windows.h>
#include<ctime>
#include<conio.h>
#include<cstdio>
using namespace std;


class Tetris
{
private:
	int rank;				//游戏难度等级
	int score;				// 得分
	int id;					//图形ID
	int point[2];			//两基点
	int top;					//最高点高度
	clock_t startTime_add;   //起始时间
	clock_t endTime_add;	//终止时间
	clock_t startTime_dot;   //超级点起始时间
	clock_t endTime_dot;	//超级点终止时间
public:
	Tetris();
	void Welocme();			//首界面
	void DrawMap();			//游戏界面
	void SetColor(int);		//控制颜色
	void Draw(int, int, int);		//画图形
	void Run();				//运行游戏
	void ReDraw(int, int, int);			//清除图形
	bool Judge(int, int, int);
	void Turn(int);				//旋转
	void Updata();				// 更新界面
	void Pause();				//游戏暂停
	void Input_score();
	void AddLine();
	void UpdateMap();        //按照Map更新界面
	void DeleteLine();       //消除一行
	void KeyEvent();
	void SetPos(int, int);
	bool CheckDot();
	void KeyDot();
};

const int sharp[25][10] =					//组成图形的各个点的各个坐标，先纵后横
{
	//条形
	{0,0,1,0,2,0,3,0,0,0},{0,0,0,1,0,2,0,3,0,0},
	//方块
	{0,0,1,0,0,1,1,1,0,0},
	//L形
	{0,0,1,0,1,1,1,2,0,0},{0,0,0,1,1,0,2,0,0,0},{0,0,0,1,0,2,1,2,0,0},{0,1,1,1,2,0,2,1,0,1},
	//J形
	{1,0,1,1,1,2,0,2,1,0},{0,0,1,0,2,0,2,1,0,0},{0,0,0,1,0,2,1,0,0,0},{0,0,0,1,1,1,2,1,0,0},
	//T形,按顺时针旋转排序
	{0,0,0,1,0,2,1,1,0,0},{0,1,1,0,1,1,2,1,0,1},{0,1,1,0,1,1,1,2,0,1},{0,0,1,0,1,1,2,0,0,0},
	//S形,按顺时针旋转排序
	{0,1,0,2,1,0,1,1,0,1},{0,0,1,0,1,1,2,1,0,0},
	//Z形,按顺时针旋转排序
	{0,0,0,1,1,1,1,2,0,0},{0,1,1,0,1,1,2,0,0,1},
	//U形
	{ 0,0,0,2,1,0,1,1,1,2 },{ 0,0,0,1,1,0,2,0,2,1 },{ 0,0,0,1,0,2,1,0,1,2 },{ 0,0,0,1,1,1,2,0,2,1 },
	//十字形
	{ 0,1,1,0,1,1,1,2,2,1 },
	//点
	{ 0,0,0,0,0,0,0,0,0,0 }
};


const int high[25] = { 4,1,2,2,3,2,3,2,3,2,3,2,3,2,3,2,3,2,3,2,3,2,3,3,1 };
int map[28][16];
//条形
#define a1  0			
#define a2  1

// 方块
#define b 2					

//L形
#define c1 3					
#define c2 4
#define c3 5
#define c4 6

//J形
#define d1 7					
#define d2 8 
#define d3 9
#define d4 10

//T形
#define t1 11					
#define t2 12
#define t3 13
#define t4 14
//S形
#define s1 15					
#define s2 16
//Z形
#define z1 17					
#define z2 18
//U形
#define u1 19					
#define u2 20
#define u3 21
#define u4 22
//十字形
#define ten 23
//点
#define dot 24




Tetris::Tetris()				//构造函数， 初始化各个值
{
	point[0] = 0;
	point[1] = 5;
	score = 0;
	top = 25;
}
void Tetris::Input_score()
{
	SetColor(3);
	SetPos(30, 19);
	cout << "得分: " << score;
}
void Tetris::Welocme()			//欢迎界面
{
	SetColor(1);
	char x;
	while (1)
	{
		system("cls");
		cout << "■■■■■■■■■■■■■■■■■■■■■" << endl;
		cout << "		俄罗斯方块		" << endl;
		cout << "■■■■■■■■■■■■■■■■■■■■■" << endl;
		cout << "		操作方式：" << endl;
		cout << "		↑ - 旋转" << endl;
		cout << "		↓ - 加速下移" << endl;
		cout << "		← - 左移" << endl;
		cout << "		→ - 右移" << endl;
		cout << "		空格 - 暂停" << endl;
		cout << "■■■■■■■■■■■■■■■■■■■■■" << endl;
		cout << "■ 按1—3选择难度■" << endl;
		SetPos(20, 10);
		x = getchar();
		if (x <= '9' && x >= '0')
		{
			rank = x - '0';
			break;
		}
	}
}
void Tetris::SetColor(int color_num)			//设置颜色
{
	int n;
	switch (color_num)
	{
	case 0: n = 0x08; break;
	case 1: n = 0x0C; break;
	case 2: n = 0x0D; break;
	case 3: n = 0x0E; break;
	case 4: n = 0x0A; break;
	case 5: n = 0x0B; break;
	case 6: n = 0x0F; break;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), n);
}
void Tetris::DrawMap()				//画游戏时界面
{
	int i;
	SetColor(0);

	for (i = 0; i < 24; i++)		//宽24格
	{
		SetPos(i * 2, 0);
		cout << "■";
		SetPos(i * 2, 26);
		cout << "■";
	}

	for (i = 0; i < 26; i++)		//高26格
	{
		SetPos(0, i);
		cout << "■";
		SetPos(28, i);
		cout << "■";
		SetPos(46, i);
		cout << "■";
	}

	for (i = 14; i < 24; i++)
	{
		SetPos(i * 2, 16);
		cout << "■";
	}

	SetColor(3);
	Input_score();
	SetPos(30, 21);
	cout << "难度等级: " << rank;
	SetPos(32, 2);
	cout << "下一图形";
}
void Tetris::Turn(int num)				//旋转函数
{
	/*
	通过条形旋转的方式完成其他形状的旋转
	有兴趣的同学也可以通过其他方法完成此功能
	*/
	switch (num)
	{
		//条形旋转
	case a1: id = a2; break;
	case a2: id = a1; break;
		//方块旋转
	case b: id = b; break;
		//L形旋转
	case c1: id = c2; break;
	case c2: id = c3; break;
	case c3: id = c4; break;
	case c4: id = c1; break;
		//J型旋转
	case d1: id = d2; break;
	case d2: id = d3; break;
	case d3: id = d4; break;
	case d4: id = d1; break;
		//T形旋转
	case t1: id = t2; break;
	case t2: id = t3; break;
	case t3: id = t4; break;
	case t4: id = t1; break;
		//S形旋转
	case s1: id = s2; break;
	case s2: id = s1; break;
		//Z形旋转
	case z1: id = z2; break;
	case z2: id = z1; break;
		//U形旋转
	case u1: id = u2; break;
	case u2: id = u3; break;
	case u3: id = u4; break;
	case u4: id = u1; break;
		//十字形旋转
	case ten: id = ten; break;
	}
}
void Tetris::SetPos(int i, int j)			//控制光标位置， 列， 行
{
	COORD pos = { i,j };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void Tetris::Pause()				// 暂停函数
{
	SetPos(32, 10);
	cout << "游戏暂停!" << endl;
	SetPos(30, 11);
	cout << "你的分数为 " << score;
	char temp;
	while (1)
	{
		while (1)
		{
			if (_kbhit())
			{
				temp = _getch();
				break;
			}
		}
		if (temp == 32)
			break;
	}
	SetPos(32, 10);					// 清除暂停时显示的信息
	cout << "         ";
	SetPos(30, 11);
	cout << "              ";
}

void Tetris::AddLine() //实现最下方增加一行	
{
	endTime_add = clock();
	if ((endTime_add - startTime_add) / CLOCKS_PER_SEC >= 10) {
		int index = top;
		for (index; index <= 24; index++) {
			for (int j = 0; j < 13; j++) {
				map[index - 1][j] = map[index][j];
			}
		}
		int sum = 0;
		while (sum == 0 || sum == 13) {
			sum = 0;
			for (int j = 0; j < 13; j++) {
				srand((int)time(0));
				map[24][j] = rand() % 2;
			}
			for (int j = 0; j < 13; j++) {
				sum = sum + map[24][j];
			}
		}
		top = top - 1;
		UpdateMap();
		startTime_add = clock();//重置开始时间
	}
}

void Tetris::UpdateMap() {
	for (int x = 0; x < 25; x++) {
		for (int y = 0; y < 13; y++) {
			SetPos((y + 1) * 2, x + 1);
			if (map[x][y] == 0) { cout << "  "; }
			else {
				SetColor(5);
				cout << "■";
			}
		}
	}
}

void Tetris::DeleteLine() {
	int i, flag;
	for (i = point[0]; i < point[0] + high[id]; i++)			//消除行
	{
		//startTime = clock();
		//将flag赋值为1，flag为1表示某一行满，0表示未满。
		flag = 1;
		// map[i][j] == 0表示在地图的第i行，第j列的地方没有方块，输出的形式为"  "
		// map[i][j] == 1表示在地图的第i行，第j列的地方有方块，输出的形式为"■"
		//注：游戏区的列数为13列
		//判断某一行是否为满
		/*请在下方补全判断是否为满功能代码*/
		for (int j = 0; j < 13; j++) {
			if (map[i][j] != 1) {
				flag = 0;
				break;
			}
		}
		//当flag为1时，消行
		if (flag == 1)
		{
			/*
			请在下方补全消行功能代码
			*/
			int index = i;
			for (index; index >= 0; index--) {
				for (int j = 0; j < 13; j++) {
					map[index][j] = map[index - 1][j];
				}
			}
			UpdateMap();

			//计算得分
			score += 10;
			Input_score();
			startTime_add = clock();//重置开始时间
		}
	}
}

void Tetris::Updata()					//更新函数
{
	int nx, ny;
	for (int i = 0; i < 5; i++)
	{
		nx = point[0] + sharp[id][i * 2];
		ny = point[1] + sharp[id][i * 2 + 1];
		SetPos((ny + 1) * 2, nx + 1);
		SetColor(5);
		cout << "■";
		map[nx][ny] = 1;					//界面各个点是否为空的更新
	}

	if (point[0] < top)
		top = point[0];					//最高点的更新

	DeleteLine();//消除行
	AddLine();//计算时间，实现最下方增加一行		
}

void Tetris::Draw(int x, int y, int num)				//画图形
{
	int nx, ny;
	for (int i = 0; i < 5; i++)
	{
		nx = x + sharp[num][2 * i];
		ny = y + sharp[num][2 * i + 1];
		SetPos((ny + 1) * 2, nx + 1);
		if (num == 24)SetColor(5);
		else SetColor(i + 1);
		cout << "■";
	}
}

void Tetris::ReDraw(int x, int y, int num)				//为更新图形的位置清除图形
{
	int nx, ny;
	for (int i = 0; i < 5; i++)
	{
		nx = x + sharp[num][2 * i];
		ny = y + sharp[num][2 * i + 1];
		SetPos((ny + 1) * 2, nx + 1);
		cout << "  ";
	}
}

bool Tetris::Judge(int x, int y, int num)				//判定在x, y 所指位置是否可画编号为
{													//num 的图形， 若不可画则反回true
	int nx, ny;
	for (int i = 0; i < 5; i++)
	{
		nx = x + sharp[num][2 * i];
		ny = y + sharp[num][2 * i + 1];
		if (!(nx < 25 && nx >= 0 && ny < 13 && ny >= 0 && !map[nx][ny]))
			return true;
	}
	return false;
}

void Tetris::Run()					//运行游戏
{
	int next_id;
	srand((int)time(0));
	startTime_add = clock();
	//id = rand() % 1;
	id = rand() % 23;
	//next_id = rand() % 24;
	next_id = 24;
	Draw(point[0], point[1], id);
	Draw(5, 16, next_id);
	int count;
	if (rank == 1)
		count = 150;
	else if (rank == 2)
		count = 100;
	else if (rank == 3)
		count = 50;
	else
		count = 5;
	int i = 0;  //不同等级对应不同count
	while (1)
	{
		AddLine();
		if (!(i < count))				//i 与 count 用于控制时间
		{
			i = 0;
			AddLine();
			if (Judge(point[0] + 1, point[1], id))			//在某一位置不能下落的话
			{
				Updata();
				id = next_id;
				ReDraw(5, 16, next_id);
				//next_id = 24;
				next_id = rand() % 24;

				point[0] = 0; point[1] = 5;
				Draw(point[0], point[1], id);
				Draw(5, 16, next_id);

				while (CheckDot()) {
					AddLine();
					id = next_id;
					ReDraw(5, 16, next_id);
					//next_id = 24;
					next_id = rand() % 24;

					point[0] = 0; point[1] = 5;
					Draw(point[0], point[1], id);
					Draw(5, 16, next_id);
				}//重复超级点

				if (Judge(point[0], point[1], id))
				{
					system("cls");
					SetPos(20, 10);
					cout << "游戏结束！" << endl;
					SetPos(20, 11);
					cout << "你的分数为 " << score << endl;
					system("pause");
					exit(1);
				}
			}
			else					//继续下落
			{
				ReDraw(point[0], point[1], id);
				point[0]++;
				Draw(point[0], point[1], id);
				AddLine();
			}
		}
		AddLine();
		KeyEvent();
		Sleep(1);		//等待1毫秒
		i++;				//控制下落间隔
	}
}
void Tetris::KeyEvent() {
	if (_kbhit())				//键盘输入值时 
	{
		int key, key2;
		key = _getch();
		if (key == 224)
		{
			key2 = _getch();

			if (key2 == 72)			//按向上方向键时
			{
				int temp = id;
				Turn(id);
				if (Judge(point[0], point[1], id))
					id = temp;
				ReDraw(point[0], point[1], temp);
				Draw(point[0], point[1], id);
			}
			if (key2 == 80)				//按向下方向键时
			{
				if (!Judge(point[0] + 2, point[1], id))
				{
					ReDraw(point[0], point[1], id);
					point[0] += 2;
					Draw(point[0], point[1], id);
				}
			}
			else if (key2 == 75)				//按向左方向键时
			{
				if (!Judge(point[0], point[1] - 1, id))
				{
					ReDraw(point[0], point[1], id);
					point[1]--;
					Draw(point[0], point[1], id);
				}
			}
			else if (key2 == 77)					//按向右方向键时
			{
				if (!Judge(point[0], point[1] + 1, id))
				{
					ReDraw(point[0], point[1], id);
					point[1]++;
					Draw(point[0], point[1], id);
				}
			}
		}
		else if (key == 32)					// 按下空格暂停
			Pause();
	}
}

bool Tetris::CheckDot() {
	startTime_dot = clock();
	if (id == 24) {
		endTime_dot = clock();
		while ((endTime_dot - startTime_dot) / CLOCKS_PER_SEC < 5)
		{
			KeyDot();
			endTime_dot = clock();
		}
		UpdateMap();//消除超级点
		return true;
	}
	return false;
}

void Tetris::KeyDot()
{
	if (_kbhit())				//键盘输入值时 
	{
		int key, key2;
		key = _getch();
		if (key == 224)
		{
			key2 = _getch();

			if (key2 == 72)			//按向上方向键时
			{
				for (int x = 0; x < 25; x++) {
					if ((map[x][point[1]] == 0 && map[x + 1][point[1]] != 0) || (map[x][point[1]] == 0 && x == 24)) {
						map[x][point[1]] = 1;
						SetPos((point[1] + 1) * 2, x + 1);
						SetColor(5);
						cout << "■";
						int temp = point[0];
						point[0] = x;
						Updata();
						point[0] = temp;
						break;
					}
				}
			}
			if (key2 == 80)				//按向下方向键时
			{
				for (int x = 0; x < 25; x++) {
					if (map[x][point[1]] != 0) {
						SetPos((point[1] + 1) * 2, x + 1);
						cout << "  ";
						map[x][point[1]] = 0;
						int sign1 = 0;
						for (int i = 0; i < 25; i++) {
							if (map[x][i] != 0) {
								sign1 = 1;
								break;
							}
							else sign1 = 0;
						}//判断top是否需要改变
						if (sign1 == 1) top = top - 1;
						UpdateMap();
						break;
					}
					//Updata();
				}
			}
			else if (key2 == 75)				//按向左方向键时
			{
				if (!Judge(point[0], point[1] - 1, id))
				{
					ReDraw(point[0], point[1], id);
					point[1]--;
					Draw(point[0], point[1], id);

				}
			}
			else if (key2 == 77)					//按向右方向键时
			{

				if (!Judge(point[0], point[1] + 1, id))
				{
					ReDraw(point[0], point[1], id);
					point[1]++;
					Draw(point[0], point[1], id);
				}
			}
			else if (key == 32)					// 按下空格暂停
				Pause();
		}
	}
}


int main()
{
	Tetris game;
	game.Welocme();
	system("cls");				//清除欢迎界面
	game.DrawMap();
	game.Run();
}