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
Menu * S1;
Menu * S2;
int c=0;
int m_pos;
int pos=0;
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
    CharToOem((LPCTSTR)text.c_str(), (LPSTR)text.c_str());
    return text;
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

void IniMenu()
{
	S1 = new Menu[4];
	S1[0].S="1. Disk";
	S1[1].S="2. Directory";
	S1[2].S="3. Show";
	S1[3].S="4. Exit";
	S1[0].color=2;
	S1[1].color=S1[2].color=S1[3].color=15;
}


void ShowMenu(Menu * S, int count)
{
	system("cls");
	for (int i=0;i<count;i++)
	{
		SetColor(S[i].color,0);
		cout<<S[i].S<<endl;
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

void ShowDir();

void go(int p)
{
	if (p==2) ShowDir();
	if (p==3)exit(0);
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
			cout<<pos<<endl;
            break;
        case 72: // вверх
            if(pos-1>=0) 
            pos=pos-1;
			SetC(S,c,pos);
            break;
        case 13: // Enter
            go(pos);
            break;
	}
}

void ShowDir(/*char * DirSpec*/)
{
WIN32_FIND_DATA FindFileData; 
HANDLE hFind = INVALID_HANDLE_VALUE; 
 char DirSpec[MAX_PATH];
cout<<"Path: ";
cin.get(DirSpec, MAX_PATH);
cout<<"\n";
strncat(DirSpec, "\\*", 3);
hFind = FindFirstFile(DirSpec, &FindFileData);
 
    if(hFind == INVALID_HANDLE_VALUE)
    {
    cout<<"Error: invalid path\n";
    }
 
cout<<FindFileData.cFileName<<"\n";
 
    while(FindNextFile(hFind, &FindFileData) != 0)
    {
    cout<<Rus(FindFileData.cFileName)<<"\n";
    }
 
FindClose(hFind);
system("pause");
}

void main()
{
	IniMenu();
	while(true)
	ShowMenu(S1,4);
	system("pause");
}
