# include <iostream>
# include <Windows.h>
# include <conio.h>
# include <io.h>
# include <stdlib.h>
# include <string>


using namespace std;

struct Menu
{
string S;
int color;
};
struct Submarine
{
	string Name;
	int Fuel;
	int Torpedo;
	string Target;
	int State;			//0 - стоит, 1 - двигается вперед, -1 - двигается назад
	int Consumption;
	int StateTorpedo;	//0 - не заряжен, 1 - заряжен
};

Menu * S1, * S2, * S3, * S4, * S5;
int c=0;
int m_pos,v=0;
int pos=0;
int postmp[3];
int m;
Submarine * SMarine;
HANDLE hConsole, hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
void choice(Menu *S, int c);
enum ConsoleColor
{
    Black         = 0,
    Blue          = 1,
    Green         = 2,
    Cyan          = 3,
    Red           = 4,
    Magenta       = 5,
    Brown         = 6,
    LightGray     = 7,
    DarkGray      = 8,
    LightBlue     = 9,
    LightGreen    = 10,
    LightCyan     = 11,
    LightRed      = 12,
    LightMagenta  = 13,
    Yellow        = 14,
    White         = 15
};

string Rus(string text)
{
	char texttmp[255];
    AnsiToOem(text.c_str(),texttmp);
    return texttmp;
}

void SetColor(int text, int background) // устанавливаем цвет
{
   HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
   SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

void IniTarget(int p)
{
	SMarine->Target=S5[p].S;
}


void IniMenu()
{
	S1 = new Menu[4];
	S1[0].S="1. Информация.";
	S1[1].S="2. Режим хода.";
	S1[2].S="3. Режим атаки.";
	S1[3].S="4. Выход.";
	S1[0].color=2;
	S1[1].color=S1[2].color=S1[3].color=15;
	S2 = new Menu[4];
	S2[0].S="1. Название.";
	S2[1].S="2. Кол-во торпед.";
	S2[2].S="3. Запас топлива.";
	S2[3].S="4. Назад.";
	S2[0].color=2;
	S2[1].color=S2[2].color=S2[3].color=15;
	S3 = new Menu[5];
	S3[0].S="1. Начать движение вперед.";
	S3[1].S="2. Остановиться.";
	S3[2].S="3. Начать движение назад.";
	S3[3].S="3. Дозаправка (только в режиме остановки).";
	S3[4].S="4. Назад.";
	S3[0].color=2;
	S3[3].color=7;
	S3[1].color=S3[2].color=S3[4].color=15;
	S4 = new Menu[4];
	S4[0].S="1. Поиск цели.";
	S4[1].S="2. Зарядка пускового аппарата (торпед).";
	S4[2].S="3. Атака.";
	S4[3].S="4. Назад.";
	S4[0].color=2;
	S4[1].color=S4[2].color=S4[3].color=15;
	S5 = new Menu[4];
	S5[0].S="1. Цель №1.";
	S5[1].S="2. Цель №2.";
	S5[2].S="3. Цель №3.";
	S5[3].S="4. Назад.";
	S5[0].color=2;
	S5[1].color=S5[2].color=S5[3].color=15;
}


void ShowMenu(Menu * S, int count)
{
	system("cls");
	for (int i=0;i<count;i++)
	{
		SetColor(S[i].color,0);
		cout<<Rus(S[i].S)<<endl;
	}
	choice(S,count);
}

void SetC(Menu *S, int c, int p)
{
	for (int i=0;i<c;i++)
	{
		if(i==p)
			S[i].color=2;
		else S[i].color=15;
	}
}


void go(int p, int c)
{
			if (p==0&&v==0)
			{
				v=1;pos=0;postmp[v]=p;m=1;
				while(v==1)
				ShowMenu(S2,4);
			}
			else 
			if (p==1&&v==0)
			{
				v=1;pos=0;postmp[v]=p;m=2;
				while(v==1)
				ShowMenu(S3,5);
			}
			else
			if (p==2&&v==0)
			{
				v=1;pos=0;postmp[v]=p;m=3;
				while(v==1)
				ShowMenu(S4,4);
			}
			else
	if (p==(c-1)&&(v==1||v==2))
	{
		pos=postmp[v];
		v--;
	}
	else 
	if (p==0&&v==1&&m==3)
	{
		v=2;pos=0;postmp[v]=p;
		while(v==2)
		ShowMenu(S5,4);
	}
	else
	if (p==0&&v==1&&m==1)
			{
				system("cls");
				cout<<Rus("Название субмарины : ")<<SMarine->Name<<endl<<endl;
				system("pause");
			}
	else
	if (p==1&&v==1&&m==1)
			{
				system("cls");
				cout<<Rus("Боезапас : ")<<SMarine->Torpedo<<Rus(" торпед")<<endl<<endl;
				system("pause");
			}
	else
	if (p==2&&v==1&&m==1)
			{
				system("cls");
				cout<<Rus("Запас топлива : ")<<SMarine->Fuel<<Rus(" л")<<endl<<endl;
				system("pause");
			}
	else
	if (p==0&&v==1&&m==2)
			{
				SMarine->State=1;
			}
	else
	if (p==1&&v==1&&m==2)
			{
				SMarine->State=0;
			}
	else
	if (p==2&&v==1&&m==2)
			{
				SMarine->State=-1;
			}
	else
	if (p==3&&v==1&&m==2)
			{
				try
				{
					if (SMarine->State!=0)
						throw 1;
					SMarine->Fuel=50;
					SMarine->Torpedo=2;
				}
				catch(int i)
				{
					system("cls");
					cout<<Rus("Субмарина движется. Дозаправка невозможна.")<<endl<<endl;
					system("pause");
				}
			}
	else
	if ((p==0||p==1||p==2)&&v==2&&m==3)
			{
				IniTarget(p);
				pos=postmp[v];
				v--;
			}
	else
	if (p==1&&v==1&&m==3)
			{
				SMarine->StateTorpedo=1;
			}
	else
	if (p==2&&v==1&&m==3)
			{
				try
				{
					if (SMarine->StateTorpedo==0)
						throw 1;
					system("cls");
					cout<<Rus("Атака произведена")<<endl<<endl;
					system("pause");
				}
				catch(int i)
				{
					system("cls");
					cout<<Rus("Торпедный аппарат не заряжен. Атака невозможна.")<<endl<<endl;
					system("pause");
				}
			}
	else
			if (p==(c-1)&&v==0)exit(0);
}

void choice(Menu *S, int c) // функция выбора
{
	int ch=_getch(); // считываем значение нажатой клавиши
	switch(ch)
    {
		 case 80: // вниз
            if(pos+1<c)
            pos=pos+1;
			SetC(S,c,pos);
            break;
        case 72: // вверх
            if(pos-1>=0) 
            pos=pos-1;
			SetC(S,c,pos);
            break;
        case 13: // Enter
            go(pos,c);
            break;
	}
}



void main()
{
	SMarine = new Submarine;
	SMarine->Name="Yellow SubMarine";
	SMarine->Fuel=50;
	SMarine->Torpedo=2;
	SMarine->Consumption=2;
	SMarine->State=0;
	SMarine->StateTorpedo=0;
	IniMenu();
	while(true)
	ShowMenu(S1,4);
	system("pause");
}
