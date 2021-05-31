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
	int rank;				//��Ϸ�Ѷȵȼ�
	int score;				// �÷�
	int id;					//ͼ��ID
	int point[2];			//������
	int top;					//��ߵ�߶�
	clock_t startTime_add;   //��ʼʱ��
	clock_t endTime_add;	//��ֹʱ��
	clock_t startTime_dot;   //��������ʼʱ��
	clock_t endTime_dot;	//��������ֹʱ��
public:
	Tetris();
	void Welocme();			//�׽���
	void DrawMap();			//��Ϸ����
	void SetColor(int);		//������ɫ
	void Draw(int, int, int);		//��ͼ��
	void Run();				//������Ϸ
	void ReDraw(int, int, int);			//���ͼ��
	bool Judge(int, int, int);
	void Turn(int);				//��ת
	void Updata();				// ���½���
	void Pause();				//��Ϸ��ͣ
	void Input_score();
	void AddLine();
	void UpdateMap();        //����Map���½���
	void DeleteLine();       //����һ��
	void KeyEvent();
	void SetPos(int, int);
	bool CheckDot();
	void KeyDot();
};

const int sharp[25][10] =					//���ͼ�εĸ�����ĸ������꣬���ݺ��
{
	//����
	{0,0,1,0,2,0,3,0,0,0},{0,0,0,1,0,2,0,3,0,0},
	//����
	{0,0,1,0,0,1,1,1,0,0},
	//L��
	{0,0,1,0,1,1,1,2,0,0},{0,0,0,1,1,0,2,0,0,0},{0,0,0,1,0,2,1,2,0,0},{0,1,1,1,2,0,2,1,0,1},
	//J��
	{1,0,1,1,1,2,0,2,1,0},{0,0,1,0,2,0,2,1,0,0},{0,0,0,1,0,2,1,0,0,0},{0,0,0,1,1,1,2,1,0,0},
	//T��,��˳ʱ����ת����
	{0,0,0,1,0,2,1,1,0,0},{0,1,1,0,1,1,2,1,0,1},{0,1,1,0,1,1,1,2,0,1},{0,0,1,0,1,1,2,0,0,0},
	//S��,��˳ʱ����ת����
	{0,1,0,2,1,0,1,1,0,1},{0,0,1,0,1,1,2,1,0,0},
	//Z��,��˳ʱ����ת����
	{0,0,0,1,1,1,1,2,0,0},{0,1,1,0,1,1,2,0,0,1},
	//U��
	{ 0,0,0,2,1,0,1,1,1,2 },{ 0,0,0,1,1,0,2,0,2,1 },{ 0,0,0,1,0,2,1,0,1,2 },{ 0,0,0,1,1,1,2,0,2,1 },
	//ʮ����
	{ 0,1,1,0,1,1,1,2,2,1 },
	//��
	{ 0,0,0,0,0,0,0,0,0,0 }
};


const int high[25] = { 4,1,2,2,3,2,3,2,3,2,3,2,3,2,3,2,3,2,3,2,3,2,3,3,1 };
int map[28][16];
//����
#define a1  0			
#define a2  1

// ����
#define b 2					

//L��
#define c1 3					
#define c2 4
#define c3 5
#define c4 6

//J��
#define d1 7					
#define d2 8 
#define d3 9
#define d4 10

//T��
#define t1 11					
#define t2 12
#define t3 13
#define t4 14
//S��
#define s1 15					
#define s2 16
//Z��
#define z1 17					
#define z2 18
//U��
#define u1 19					
#define u2 20
#define u3 21
#define u4 22
//ʮ����
#define ten 23
//��
#define dot 24




Tetris::Tetris()				//���캯���� ��ʼ������ֵ
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
	cout << "�÷�: " << score;
}
void Tetris::Welocme()			//��ӭ����
{
	SetColor(1);
	char x;
	while (1)
	{
		system("cls");
		cout << "������������������������������������������" << endl;
		cout << "		����˹����		" << endl;
		cout << "������������������������������������������" << endl;
		cout << "		������ʽ��" << endl;
		cout << "		�� - ��ת" << endl;
		cout << "		�� - ��������" << endl;
		cout << "		�� - ����" << endl;
		cout << "		�� - ����" << endl;
		cout << "		�ո� - ��ͣ" << endl;
		cout << "������������������������������������������" << endl;
		cout << "�� ��1��3ѡ���Ѷȡ�" << endl;
		SetPos(20, 10);
		x = getchar();
		if (x <= '9' && x >= '0')
		{
			rank = x - '0';
			break;
		}
	}
}
void Tetris::SetColor(int color_num)			//������ɫ
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
void Tetris::DrawMap()				//����Ϸʱ����
{
	int i;
	SetColor(0);

	for (i = 0; i < 24; i++)		//��24��
	{
		SetPos(i * 2, 0);
		cout << "��";
		SetPos(i * 2, 26);
		cout << "��";
	}

	for (i = 0; i < 26; i++)		//��26��
	{
		SetPos(0, i);
		cout << "��";
		SetPos(28, i);
		cout << "��";
		SetPos(46, i);
		cout << "��";
	}

	for (i = 14; i < 24; i++)
	{
		SetPos(i * 2, 16);
		cout << "��";
	}

	SetColor(3);
	Input_score();
	SetPos(30, 21);
	cout << "�Ѷȵȼ�: " << rank;
	SetPos(32, 2);
	cout << "��һͼ��";
}
void Tetris::Turn(int num)				//��ת����
{
	/*
	ͨ��������ת�ķ�ʽ���������״����ת
	����Ȥ��ͬѧҲ����ͨ������������ɴ˹���
	*/
	switch (num)
	{
		//������ת
	case a1: id = a2; break;
	case a2: id = a1; break;
		//������ת
	case b: id = b; break;
		//L����ת
	case c1: id = c2; break;
	case c2: id = c3; break;
	case c3: id = c4; break;
	case c4: id = c1; break;
		//J����ת
	case d1: id = d2; break;
	case d2: id = d3; break;
	case d3: id = d4; break;
	case d4: id = d1; break;
		//T����ת
	case t1: id = t2; break;
	case t2: id = t3; break;
	case t3: id = t4; break;
	case t4: id = t1; break;
		//S����ת
	case s1: id = s2; break;
	case s2: id = s1; break;
		//Z����ת
	case z1: id = z2; break;
	case z2: id = z1; break;
		//U����ת
	case u1: id = u2; break;
	case u2: id = u3; break;
	case u3: id = u4; break;
	case u4: id = u1; break;
		//ʮ������ת
	case ten: id = ten; break;
	}
}
void Tetris::SetPos(int i, int j)			//���ƹ��λ�ã� �У� ��
{
	COORD pos = { i,j };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void Tetris::Pause()				// ��ͣ����
{
	SetPos(32, 10);
	cout << "��Ϸ��ͣ!" << endl;
	SetPos(30, 11);
	cout << "��ķ���Ϊ " << score;
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
	SetPos(32, 10);					// �����ͣʱ��ʾ����Ϣ
	cout << "         ";
	SetPos(30, 11);
	cout << "              ";
}

void Tetris::AddLine() //ʵ�����·�����һ��	
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
		startTime_add = clock();//���ÿ�ʼʱ��
	}
}

void Tetris::UpdateMap() {
	for (int x = 0; x < 25; x++) {
		for (int y = 0; y < 13; y++) {
			SetPos((y + 1) * 2, x + 1);
			if (map[x][y] == 0) { cout << "  "; }
			else {
				SetColor(5);
				cout << "��";
			}
		}
	}
}

void Tetris::DeleteLine() {
	int i, flag;
	for (i = point[0]; i < point[0] + high[id]; i++)			//������
	{
		//startTime = clock();
		//��flag��ֵΪ1��flagΪ1��ʾĳһ������0��ʾδ����
		flag = 1;
		// map[i][j] == 0��ʾ�ڵ�ͼ�ĵ�i�У���j�еĵط�û�з��飬�������ʽΪ"  "
		// map[i][j] == 1��ʾ�ڵ�ͼ�ĵ�i�У���j�еĵط��з��飬�������ʽΪ"��"
		//ע����Ϸ��������Ϊ13��
		//�ж�ĳһ���Ƿ�Ϊ��
		/*�����·���ȫ�ж��Ƿ�Ϊ�����ܴ���*/
		for (int j = 0; j < 13; j++) {
			if (map[i][j] != 1) {
				flag = 0;
				break;
			}
		}
		//��flagΪ1ʱ������
		if (flag == 1)
		{
			/*
			�����·���ȫ���й��ܴ���
			*/
			int index = i;
			for (index; index >= 0; index--) {
				for (int j = 0; j < 13; j++) {
					map[index][j] = map[index - 1][j];
				}
			}
			UpdateMap();

			//����÷�
			score += 10;
			Input_score();
			startTime_add = clock();//���ÿ�ʼʱ��
		}
	}
}

void Tetris::Updata()					//���º���
{
	int nx, ny;
	for (int i = 0; i < 5; i++)
	{
		nx = point[0] + sharp[id][i * 2];
		ny = point[1] + sharp[id][i * 2 + 1];
		SetPos((ny + 1) * 2, nx + 1);
		SetColor(5);
		cout << "��";
		map[nx][ny] = 1;					//����������Ƿ�Ϊ�յĸ���
	}

	if (point[0] < top)
		top = point[0];					//��ߵ�ĸ���

	DeleteLine();//������
	AddLine();//����ʱ�䣬ʵ�����·�����һ��		
}

void Tetris::Draw(int x, int y, int num)				//��ͼ��
{
	int nx, ny;
	for (int i = 0; i < 5; i++)
	{
		nx = x + sharp[num][2 * i];
		ny = y + sharp[num][2 * i + 1];
		SetPos((ny + 1) * 2, nx + 1);
		if (num == 24)SetColor(5);
		else SetColor(i + 1);
		cout << "��";
	}
}

void Tetris::ReDraw(int x, int y, int num)				//Ϊ����ͼ�ε�λ�����ͼ��
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

bool Tetris::Judge(int x, int y, int num)				//�ж���x, y ��ָλ���Ƿ�ɻ����Ϊ
{													//num ��ͼ�Σ� �����ɻ��򷴻�true
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

void Tetris::Run()					//������Ϸ
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
	int i = 0;  //��ͬ�ȼ���Ӧ��ͬcount
	while (1)
	{
		AddLine();
		if (!(i < count))				//i �� count ���ڿ���ʱ��
		{
			i = 0;
			AddLine();
			if (Judge(point[0] + 1, point[1], id))			//��ĳһλ�ò�������Ļ�
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
				}//�ظ�������

				if (Judge(point[0], point[1], id))
				{
					system("cls");
					SetPos(20, 10);
					cout << "��Ϸ������" << endl;
					SetPos(20, 11);
					cout << "��ķ���Ϊ " << score << endl;
					system("pause");
					exit(1);
				}
			}
			else					//��������
			{
				ReDraw(point[0], point[1], id);
				point[0]++;
				Draw(point[0], point[1], id);
				AddLine();
			}
		}
		AddLine();
		KeyEvent();
		Sleep(1);		//�ȴ�1����
		i++;				//����������
	}
}
void Tetris::KeyEvent() {
	if (_kbhit())				//��������ֵʱ 
	{
		int key, key2;
		key = _getch();
		if (key == 224)
		{
			key2 = _getch();

			if (key2 == 72)			//�����Ϸ����ʱ
			{
				int temp = id;
				Turn(id);
				if (Judge(point[0], point[1], id))
					id = temp;
				ReDraw(point[0], point[1], temp);
				Draw(point[0], point[1], id);
			}
			if (key2 == 80)				//�����·����ʱ
			{
				if (!Judge(point[0] + 2, point[1], id))
				{
					ReDraw(point[0], point[1], id);
					point[0] += 2;
					Draw(point[0], point[1], id);
				}
			}
			else if (key2 == 75)				//���������ʱ
			{
				if (!Judge(point[0], point[1] - 1, id))
				{
					ReDraw(point[0], point[1], id);
					point[1]--;
					Draw(point[0], point[1], id);
				}
			}
			else if (key2 == 77)					//�����ҷ����ʱ
			{
				if (!Judge(point[0], point[1] + 1, id))
				{
					ReDraw(point[0], point[1], id);
					point[1]++;
					Draw(point[0], point[1], id);
				}
			}
		}
		else if (key == 32)					// ���¿ո���ͣ
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
		UpdateMap();//����������
		return true;
	}
	return false;
}

void Tetris::KeyDot()
{
	if (_kbhit())				//��������ֵʱ 
	{
		int key, key2;
		key = _getch();
		if (key == 224)
		{
			key2 = _getch();

			if (key2 == 72)			//�����Ϸ����ʱ
			{
				for (int x = 0; x < 25; x++) {
					if ((map[x][point[1]] == 0 && map[x + 1][point[1]] != 0) || (map[x][point[1]] == 0 && x == 24)) {
						map[x][point[1]] = 1;
						SetPos((point[1] + 1) * 2, x + 1);
						SetColor(5);
						cout << "��";
						int temp = point[0];
						point[0] = x;
						Updata();
						point[0] = temp;
						break;
					}
				}
			}
			if (key2 == 80)				//�����·����ʱ
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
						}//�ж�top�Ƿ���Ҫ�ı�
						if (sign1 == 1) top = top - 1;
						UpdateMap();
						break;
					}
					//Updata();
				}
			}
			else if (key2 == 75)				//���������ʱ
			{
				if (!Judge(point[0], point[1] - 1, id))
				{
					ReDraw(point[0], point[1], id);
					point[1]--;
					Draw(point[0], point[1], id);

				}
			}
			else if (key2 == 77)					//�����ҷ����ʱ
			{

				if (!Judge(point[0], point[1] + 1, id))
				{
					ReDraw(point[0], point[1], id);
					point[1]++;
					Draw(point[0], point[1], id);
				}
			}
			else if (key == 32)					// ���¿ո���ͣ
				Pause();
		}
	}
}


int main()
{
	Tetris game;
	game.Welocme();
	system("cls");				//�����ӭ����
	game.DrawMap();
	game.Run();
}