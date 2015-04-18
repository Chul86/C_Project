#include<Windows.h>
#include<stdlib.h>
#include<string>
#include<tchar.h>
#include<conio.h>
#include <io.h>



static TCHAR WindowsClass[] = _T("win32app");

static TCHAR Title[] = _T("MyApp");
char szText[] = "";
int i = 0;
HINSTANCE hinst;

#define ID_BUTTON1 1002
#define ID_BUTTON2 1003
#define ID_BUTTON3 1004
#define ID_EDIT 1011
#define ID_LISTBOX1 1021
#define ID_LISTBOX2 1022
#define ID_LISTBOX3 1023
#define ID_CHECK1 1030 
#define ID_CHECK2 1031 
#define ID_CHECK3 1032 
#define ID_CHECK4 1033 




HWND button1, button2, button3, list1, list2, checkbox1, checkbox2, checkbox3, checkbox4, list,edit,list3;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int l1=1,l2=201;
char s[10];
int l;
std::string str, spisok;

int WINAPI WinMain(HINSTANCE hinstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hinstance;
	wcex.hIcon = LoadIcon(hinstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	/*wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);*/
	wcex.hbrBackground = CreateSolidBrush(RGB(150, 70, 150));
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = WindowsClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL, "Call faild!", "MyApp", NULL);
		return 1;
	}

	hinst = hinstance;

	HWND hWnd = CreateWindow(
		WindowsClass,
		Title,
		WS_OVERLAPPEDWINDOW,
		100,
		100,
		700,
		500,
		NULL,
		NULL,
		hinst,
		NULL);

	if (!hWnd)
	{
		MessageBox(NULL, _T("Create window faild!"), "MyApp", NULL);
		return 1;
	}
	SetTimer(hWnd, 1, 100, NULL);
	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return(int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rect;
	int xPos, yPos, length, mY = 0;
	std::string str1;
	/*wchar_t str[10];*/
	HWND hwndlist1 = GetDlgItem(hWnd, ID_LISTBOX1);
	HWND hwndlist2 = GetDlgItem(hWnd, ID_LISTBOX2);


	switch (message)
	{
	case WM_COMMAND:
					
	case BN_CLICKED:
		{

			if (LOWORD(wParam) == ID_LISTBOX1)
			{
				if (l!=0)
				{
					if(list==list2)
					l2=l;
					else l1=l;
				}
				l=l1;
				list=list1;
			}

			if (LOWORD(wParam) == ID_LISTBOX2)
			{
				if (l!=0)
				{
				if(list==list1)
					l1=l;
				else l2=l;
				}
				l=l2;
				list=list2;
			}

			if (LOWORD(wParam) == ID_CHECK1)
			{
				auto res = SendMessage(checkbox1, BM_GETCHECK, 0, 0);
				if (res == BST_CHECKED)
					str.append(" Brave ");
				if (res == BST_UNCHECKED)
				{
					str.erase(str.find(" Brave "),7);
				}
			}

			if (LOWORD(wParam) == ID_CHECK2)
			{
				auto res = SendMessage(checkbox2, BM_GETCHECK, 0, 0);
				if (res == BST_CHECKED)
					str.append(" Strong ");
				if (res == BST_UNCHECKED)
				{
					str.erase(str.find(" Strong "),8);
				}
			}

			if (LOWORD(wParam) == ID_CHECK3)
			{
				auto res = SendMessage(checkbox3, BM_GETCHECK, 0, 0);
				if (res == BST_CHECKED)
					str.append(" Kind ");
				if (res == BST_UNCHECKED)
				{
					str.erase(str.find(" Kind "),6);
				}
			}

			if (LOWORD(wParam) == ID_CHECK4)
			{
				auto res = SendMessage(checkbox4, BM_GETCHECK, 0, 0);
				if (res == BST_CHECKED)
					str.append(" Intelligent ");
				if (res == BST_UNCHECKED)
				{
					str.erase(str.find(" Intelligent "),13);
				}
			}

			if (LOWORD(wParam) == ID_BUTTON1)
			{
					itoa(l++, s, 10);
					SendMessage(list, LB_ADDSTRING, 0, (LPARAM)s);
			}

			if (LOWORD(wParam) == ID_BUTTON2)
			{
				MessageBox(hWnd, str.c_str(), "", TRUE);
			}

			if (LOWORD(wParam) == ID_BUTTON3)
			{
				SendMessage(edit, WM_GETTEXT, sizeof(str1), (LPARAM)str1.c_str());
				auto res = SendMessage(list3, LB_FINDSTRING, -1, (LPARAM) str1.c_str());
				if (res==LB_ERR)
				MessageBox(hWnd, "Строка не найдена", "", TRUE);
				else 
					MessageBox(hWnd, "Строка найдена", "", TRUE);
			}
		}
		break;
	break;	
	case WM_CREATE:
		button1 = CreateWindowEx(NULL, "button", "ADD", WS_CHILD | WS_VISIBLE, 10, 420, 120, 20, hWnd, (HMENU)ID_BUTTON1, hinst, NULL);
		button2 = CreateWindowEx(NULL, "button", "ADD", WS_CHILD | WS_VISIBLE, 150, 200, 100, 20, hWnd, (HMENU)ID_BUTTON2, hinst, NULL);
		button3 = CreateWindowEx(NULL, "button", "FIND", WS_CHILD | WS_VISIBLE, 280, 420, 100, 20, hWnd, (HMENU)ID_BUTTON3, hinst, NULL);		
		list1 = CreateWindowEx(WS_EX_CLIENTEDGE, "listbox","", WS_CHILD | WS_VISIBLE | LBS_STANDARD | LBS_EXTENDEDSEL | LBS_SORT, 10, 10, 50, 400, hWnd,(HMENU)ID_LISTBOX1, hinst, NULL);
		list2 = CreateWindowEx(WS_EX_CLIENTEDGE, "listbox","", WS_CHILD | WS_VISIBLE | LBS_STANDARD | LBS_EXTENDEDSEL | LBS_SORT, 80, 10, 50, 400, hWnd,(HMENU)ID_LISTBOX2, hinst, NULL);
		checkbox1 = CreateWindow("button", "Brave", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 150, 10, 100, 40, hWnd, (HMENU)ID_CHECK1, hinst, NULL);
		checkbox2 = CreateWindow("button", "Strong", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 150, 50, 100, 40, hWnd, (HMENU)ID_CHECK2, hinst, NULL);
		checkbox3 = CreateWindow("button", "Kind", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 150, 90, 100, 40, hWnd, (HMENU)ID_CHECK3, hinst, NULL);
		checkbox4 = CreateWindow("button", "Intelligent", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 150, 130, 100, 40, hWnd, (HMENU)ID_CHECK4, hinst, NULL);
		edit = CreateWindowEx(NULL, "edit", "Введите искомую строку", WS_CHILD | WS_VISIBLE, 280, 370, 350, 20, hWnd, (HMENU)ID_EDIT, hinst, NULL);
		list3 = CreateWindowEx(WS_EX_CLIENTEDGE, "listbox","", WS_CHILD | WS_VISIBLE | LBS_STANDARD | LBS_EXTENDEDSEL | LBS_SORT, 280, 10, 350, 350, hWnd,(HMENU)ID_LISTBOX2, hinst, NULL);

		char st[10];
		for (int i = 0; i < 10; i++){
			itoa(i, st, 10);
			strcat(st, " String");
			SendMessage(list3, LB_ADDSTRING, 0, (LPARAM)st);
		}

		char s1[10],s2[10];
		for (int j = 0; j < 5; j++)
		{
			itoa(l1++, s1, 10);
			SendMessage(list1, LB_ADDSTRING, 0, (LPARAM)s1);
			itoa(l2++, s2, 10);
			SendMessage(list2, LB_ADDSTRING, 0, (LPARAM)s2);
		}


	

		break;
	case WM_LBUTTONDBLCLK:
		break;
	case WM_LBUTTONDOWN:
		break;
	case WM_KEYDOWN:
		break;
	case WM_RBUTTONDOWN:
		break;
	case WM_MOUSEMOVE:
		xPos = LOWORD(lParam);
		yPos = HIWORD(lParam);
		break;
	case WM_KILLFOCUS:
		break;

	case WM_NOTIFY:		
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		/*TextOut(hdc, 5, 5, "Hello!", 6);*/
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}