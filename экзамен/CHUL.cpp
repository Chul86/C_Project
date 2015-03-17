# include <iostream>
# include <Windows.h>
# include <string>
# include <conio.h>
# include <stdlib.h>
# include <time.h>
# define xm 74
# define ym 24

using namespace std;

HANDLE hConsole, hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

int a=1,b=0,size=2,clr=15,fx=40,fy=15,k=0,speed=100;

struct Menu
{
string S;
int color;
};
Menu * S1;

int * records;
int c=0,save=0,rec=0;
int m_pos;
int pos=0;
int m;
int **coord;
void choice(Menu *S, int c);

string Rus(string text)
{
	char texttmp[255];
    AnsiToOem(text.c_str(),texttmp);
    return texttmp;
}

void SortQuick(int* m, int A, int B)
{
	int i = A, j = B, t, p;
	p = m[(A+B)/2];
	do{
			while ( m[i] > p ) i++;
			while ( m[j] < p ) j--;
			if (i <= j){
				t = m[i];
				m[i] = m[j];
				m[j] = t;
				i++;
				j--;
				break;
		}
	}while ( i<=j );
	if(A<j)SortQuick(m, A, j);
	if(i<B)SortQuick(m, i, B);
}

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

void Save()
{
	save=1;
	S1[0].S="1. Продолжить.";
	FILE * f;
	f =  fopen("config.ini", "wb");
	fwrite(&save,sizeof(int),1,f);
	fwrite(&size,sizeof(int),1,f);
	for(int i=0;i<size;i++)
		{
			fwrite(&coord[i][0],sizeof(int),1,f);
			fwrite(&coord[i][1],sizeof(int),1,f);
		}
	fwrite(&fx,sizeof(int),1,f);
	fwrite(&fy,sizeof(int),1,f);
	fwrite(&rec,sizeof(int),1,f);
	fclose(f);
}


void SetColor(int text, int background) // устанавливаем цвет
{
   HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
   SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

void GotoXY(int X, int Y) // позиция курсора
{
    COORD coord = { X, Y };
    SetConsoleCursorPosition(hStdOut, coord);
}

void Direct()
{
	int ch=_getch(); // считываем значение нажатой клавиши
    switch(ch)
        {
        case 80: // вниз
            a=0;b=1;
            break;
        case 72: // вверх
            a=0;b=-1;
            break;
		case 77: // вправо
            a=1;b=0;
            break;
		case 75: // влево
            a=-1;b=0;
            break;
		case 27: //esc 
			k=1;
			Save();
			break;
		default:
			break;
          }
}

void border(int &a1,int &b1) //обработка пересечения границы игрового поля
{
	if(a1==xm&&(b1!=0||b1!=ym)) a1=1;
	if(b1==ym&&(a1!=0||a1!=xm)) b1=1;
	if(a1==0&&(b1!=0||b1!=ym)) a1=xm-1;
	if(b1==0&&(a1!=0||a1!=xm)) b1=ym-1;
}

void food(int &a1,int &b1)// расположение еды
{
	a1=rand() % 72+1;
	b1=rand() % 22+1;
}

void eat_food(int &a1,int &b1)
{
	if(a1==fx&&b1==fy) {size++;speed=speed-5;food(fx,fy);rec++;}
}


void show_snake(int **c)		//		вывод змейки на экран
{
	SetColor(1,0);
	cout << '\xDA';	for(int i=0;i<=72;i++)	cout<< '\xC4'; cout << '\xBF';
	for(int i=1;i<=23;i++){GotoXY(0,i);cout<< '\xB3';GotoXY(74,i);cout<< '\xB3';}
	GotoXY(0,24);
	cout << '\xC0';	for(int i=0;i<=72;i++)	cout<< '\xC4'; cout << '\xD9';
	SetColor(2,0);
	GotoXY(fx,fy);cout<<char(15);
	SetColor(clr,0);
	for(int i=0;i<=size;i++)
	{
		GotoXY(c[i][0],c[i][1]);
		cout<<"*";
	}
}

void drive_snake(int **c)		//	движение змейки
{
	for(int i=size;i>0;i--)
	{
		c[i][0]=c[i-1][0];c[i][1]=c[i-1][1];
	}
	c[0][0]=c[0][0]+a;c[0][1]=c[0][1]+b;
}

void init_snake(int **c)		// инициализация массива координат змейки
{
	for(int i=size,j=0;i>=0;i--,j++)
	{
		c[i][0]=j+1;c[i][1]=1;
	}
}

void defeat(int **c)
{
	for(int i=1;i<=size;i++)
		if((c[i][0]==c[0][0])&&(c[i][1]==c[0][1]))
		{
			k=1;
			save=0;
			S1[0].S="1. Играть.";
			init_snake(coord);
			rec=0;a=1;b=0;size=2;fx=40;fy=15;
			if(rec>records[9])
				records[9]=rec;
			FILE * f;
			f =  fopen("config.ini", "wb");
					fwrite(&save,sizeof(int),1,f);
			fclose(f);
			f =  fopen("Records", "wb");
			for(int i=0;i<10;i++)
				{
					fwrite(&records[i],sizeof(int),1,f);
				}
			fclose(f);
			system("cls");
			cout<<Rus("GAME OVER")<<endl;
			while(true)
				if(kbhit()==true)
					if (_getch()==27)
						break;
		}

}

void IniFile()
{
	FILE * f;

		f =  fopen("config.ini", "rb");
		fread(&save,sizeof(int),1,f);
		if (save==1)
		{
			fread(&size,sizeof(int),1,f);
			for(int i=0;i<size;i++)
				{
					fread(&coord[i][0],sizeof(int),1,f);
					fread(&coord[i][1],sizeof(int),1,f);
				}
			fread(&fx,sizeof(int),1,f);
			fread(&fy,sizeof(int),1,f);
			fread(&rec,sizeof(int),1,f);
		}
		else 
			{
				init_snake(coord);
				food(fx,fy);
				rec=0;
			}
		fclose(f);
		f =  fopen("Records", "rb");
		for(int i=0;i<10;i++)
			fread(&records[i],sizeof(int),1,f);
	    fclose(f);

}

void IniMenu()
{ 
	S1 = new Menu[3];
	if (save==1)
		S1[0].S="1. Продолжить.";
	else
		S1[0].S="1. Играть.";
	S1[1].S="2. Рекорды.";
	S1[2].S="3. Выход. \n ESC для выхода из игры и списка рекордов";
	S1[0].color=2;
	S1[1].color=S1[2].color=15;
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

void ShowRecords()
{
	SortQuick(records,0,9);
	system("cls");
	for(int i=0;i<10;i++)
		cout<<i+1<<":\t"<<records[i]<<endl<<endl;
	while(true)
	if(kbhit()==true)
		if (_getch()==27)
			break;
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
			if (p==0)
			{
				k=0;
				while(k==0)
				{
					system("cls");
					show_snake(coord);		
					eat_food(coord[0][0],coord[0][1]);
					if(kbhit()==true)
					Direct();
					drive_snake(coord);
					defeat(coord);
					border(coord[0][0],coord[0][1]);
					Sleep(speed);
				}
			}
			else 
			if (p==1)
			{
				ShowRecords();
			}
			else
			if (p==2)
			{
				exit(0);
			}
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




void main()// размерность выводимого по умолчанию поля 25 Х 75
{
	srand(time(NULL));
	records=new int[10];
	coord=new int*[100];
	for(int i=0;i<100;i++)
		coord[i]=new int[2];
	IniFile();
	IniMenu();
	while(true)
	ShowMenu(S1,3);
	
	system("pause");
}
