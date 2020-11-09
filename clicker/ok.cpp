#include <iostream>
#include <windows.h>
#include <winuser.h>
#include <strsafe.h>
#include <ShObjIdl.h>

using namespace std;


void menu()
{
	SetConsoleTitle(TEXT("Vepe V423942 :^)"));

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 13);
	cout << endl;
	cout << "		   f4 to toggle left click		      " << endl;
	cout << "		  f5 to toggle right click		      " << endl;
	cout << "		        f6 to hide					  " << endl;
	cout << "		      f7 to selfdel					  " << endl;
	cout << endl;
}

int random(int x, int y)
{
	int random_integer;
	int lowest = x, highest = y;
	int range = (highest - lowest) + 1;
	random_integer = lowest + int(range * (rand() / (RAND_MAX + 1.0)));
	int delay = 1000 / random_integer;
	return delay;
}

void clicker()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 12);
	int x;
	int y;
	cout << "Min CPS: ";
	cin >> x;
	cout << "Max CPS: ";
	cin >> y;

	if (x > y)
	{
		cout << "Min CPS can't be greater than Max CPS." << endl;
	}

	else if (x < 0)
	{
		cout << "Min CPS can't be less than 0." << endl;
	}

	else if (y < 0)
	{
		cout << "Max CPS can't be less than 0." << endl;
	}

	cout << endl;
	SetConsoleTextAttribute(hConsole, 11);
	cout << "This will a random amount beetween " << x << " and "<< y << " to your CPS."<< endl;
	cout << "Note this only goes up to twice your CPS." << endl;
	cout << "Therefore making Max CPS higher than your normal CPS won't do anything." << endl;
	cout << endl;
	SetConsoleTextAttribute(hConsole, 10);
	cout << "Clicker started."<< endl;

	bool lclick = false;
	bool rclick = false;

	while (true)
	{
		if (GetAsyncKeyState(VK_F4))
		{
			SetConsoleTitle(TEXT("Vepe V423942 :^) [ON]"));
			lclick = !lclick;
			Sleep(500);
		}

		else if (GetAsyncKeyState(VK_F5))
		{
			SetConsoleTitle(TEXT("Vepe V423942 :^) [ON]"));
			rclick = !rclick;
			Sleep(500);
		}

		if (lclick)
		{
			if ((GetKeyState(VK_LBUTTON) & 0x100) != 0)
			{
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				Sleep(random(x, y) / 3);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
				Sleep(random(x, y));
			}
		}

		if (rclick)
		{
			if ((GetKeyState(VK_RBUTTON) & 0x100) != 0)
			{
				mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
				Sleep(random(x, y) / 3);
				mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
				Sleep(random(x, y));
			}
		}

		else
		{
			SetConsoleTitle(TEXT("Vepe V423942 :^) [OFF]"));
		}

		if (GetAsyncKeyState(VK_F6))
		{
			ITaskbarList* pTaskList = NULL;
			HRESULT initRet = CoInitialize(NULL);
			HRESULT createRet = CoCreateInstance(CLSID_TaskbarList,
				NULL,
				CLSCTX_INPROC_SERVER,
				IID_ITaskbarList,
				(LPVOID*)&pTaskList);

			if (createRet == S_OK)
			{

				pTaskList->DeleteTab(GetConsoleWindow());

				pTaskList->Release();
			}

			CoUninitialize();
		}

		if (GetAsyncKeyState(VK_F7))
		{
			#define SELF_REMOVE_STRING  TEXT("cmd.exe /C Nul & Del /f /q \"%s\"")

			TCHAR szModuleName[MAX_PATH];
			TCHAR szCmd[2 * MAX_PATH];
			STARTUPINFO si = { 0 };
			PROCESS_INFORMATION pi = { 0 };

			GetModuleFileName(NULL, szModuleName, MAX_PATH);

			StringCbPrintf(szCmd, 2 * MAX_PATH, SELF_REMOVE_STRING, szModuleName);

			CreateProcess(NULL, szCmd, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi);

			CloseHandle(pi.hThread);
			CloseHandle(pi.hProcess);
			exit(0);
		}
	}
}

int main()
{
	menu();
	clicker();
}