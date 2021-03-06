
#include "stdafx.h"
#include "Main.h"

#include <math.h>
#include <string.h>
#include <ctime>

#include "debug.h"
#include "RD.h"
#include "USB.h"
#include "CVE_reg.h"
#include "CVE.h"
#include "cve_constants.h"
#include "ProxyTester.h"
#include "Calibr.h"

#define MAX_LOADSTRING 100

const int ID_ExitButton         = 102;
const int ID_PotentialButton    = 103;
const int ID_AltCombo           = 110;
const int ID_AttCombo           = 111;
const int ID_AuxAttCombo        = 112;
const int ID_CalibrateEnable    = 113;
const int ID_PowerPotentialTest = 114;
const int ID_AltitudeTest       = 115;
const int ID_FindPotential		= 116;
const int ID_FindAltitude       = 117;



// Глобальные переменные:
HINSTANCE hInst;								// текущий экземпляр
TCHAR szTitle[MAX_LOADSTRING];					// Текст строки заголовка
TCHAR szWindowClass[MAX_LOADSTRING];			// имя класса главного окна
ProxyTester* tester = new ProxyTester(); 

// Отправить объявления функций, включенных в этот модуль кода:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: разместите код здесь.
	MSG msg;
	HACCEL hAccelTable;

	// Инициализация глобальных строк
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_TESTER, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Выполнить инициализацию приложения:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TESTER));

	// Цикл основного сообщения:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  НАЗНАЧЕНИЕ: регистрирует класс окна.
//
//  КОММЕНТАРИИ:
//
//    Эта функция и ее использование необходимы только в случае, если нужно, чтобы данный код
//    был совместим с системами Win32, не имеющими функции RegisterClassEx'
//    которая была добавлена в Windows 95. Вызов этой функции важен для того,
//    чтобы приложение получило "качественные" мелкие значки и установило связь
//    с ними.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TESTER));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_TESTER);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   НАЗНАЧЕНИЕ: сохраняет обработку экземпляра и создает главное окно.
//
//   КОММЕНТАРИИ:
//
//        В данной функции дескриптор экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится на экран главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Сохранить дескриптор экземпляра в глобальной переменной

   int x0 = GetSystemMetrics(SM_CXSCREEN)/8;
   int y0 = GetSystemMetrics(SM_CYSCREEN)/8;

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, x0*2, y0*2, x0*3, y0*3, NULL, NULL, hInstance, NULL);
      
   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  НАЗНАЧЕНИЕ:  обрабатывает сообщения в главном окне.
//
//  WM_COMMAND	- обработка меню приложения
//  WM_PAINT	-Закрасить главное окно
//  WM_DESTROY	 - ввести сообщение о выходе и вернуться.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	static HWND hButton, ExitButton, PotencialButton, AltCombo, AttCombo, AuxAttCombo;
	static HWND CalibrateEnable, PowerPotentialTest, AltitudeTest;
	static HWND FindPotential, FindAltitude;
    char arv[10];
	std::string s;
	int itemIndex = 0, J = 0;
	bool vk = FALSE;
	int err = 0;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		switch (wmId)
		{
		case ID_ExitButton:
			delete tester; // удаление глобальной переменной при закрытии окна
			PostQuitMessage(0);
			break;

		case ID_AltCombo:
			itemIndex = SendDlgItemMessage(hWnd, ID_AltCombo,CB_GETCURSEL,0,0);		// считываем номер выбранного значения высоты 
			tester->SetAltitude(itemIndex*StepAlt);									// и отправляем команду в тестер на установку значения
			if (SendDlgItemMessage(hWnd, ID_AltCombo, CB_GETDROPPEDSTATE , 0,0))	// после выбора меню переключаем фокус на основное окно
				SetFocus(hWnd);	
			break;

		case ID_AttCombo:
            itemIndex = SendDlgItemMessage(hWnd, ID_AttCombo,CB_GETCURSEL,0,0);		// считываем номер выбранного значения ослабления 
            tester->SetAttenuation(itemIndex);										// и отправляем команду в тестер на установку значения
			if (SendDlgItemMessage(hWnd, ID_AttCombo, CB_GETDROPPEDSTATE, 0, 0))	// после выбора меню переключаем фокус на основное окно
				SetFocus(hWnd);
			break;

		case ID_AuxAttCombo:														// считываем номер выбранного значения дополнительного ослабления
			itemIndex = SendDlgItemMessage(hWnd, ID_AuxAttCombo,CB_GETCURSEL, 0, 0);
            tester->SetAuxAttenuation(itemIndex);
			if (SendDlgItemMessage(hWnd, ID_AuxAttCombo, CB_GETDROPPEDSTATE, 0, 0))
				SetFocus(hWnd);
			break;

		case ID_CalibrateEnable:													// считываем флаг установки калибровки 
			tester->SetEnableCal(SendMessage(CalibrateEnable, BM_GETCHECK, 0, 0));
			break;

		case ID_PowerPotentialTest:													// запуск теста потенциала
			tester->SetVK(FALSE);													// сбросили выдачу команды
			J = SendDlgItemMessage(hWnd, ID_AttCombo, CB_GETCURSEL, 0, 0);
			for(int i = J; i>=0; i--){
				SendDlgItemMessage(hWnd, ID_AttCombo, CB_SETCURSEL, i, 0);			// изменение значения ослабления на форме
				UpdateWindow(hWnd);													// обновление окна
				tester->SetAttenuation(i*StepAtt);									// установка текущего значения ослабления в тестер
				Sleep(6);															// пауза компенсации переходных процессов
				vk = tester->GetVK();												// считывание наличия выходной команды
				err = tester->GetError();											// считывание наличия ошибок
				if ( vk == TRUE ){													// при наличии выходной команды выходим из
					s = "Attenuation = " + std::to_string((long double) tester->GetAttenuation());
					break;
				}
			}
			// вывод сообщения об измеренном значении потенциала
			if ( vk == TRUE )
				CreateWindowA("STATIC",  (LPSTR) s.c_str(), WS_CHILD | WS_VISIBLE |SS_CENTER | SS_CENTERIMAGE, 350, 80, 200, 30, hWnd, NULL, NULL, NULL );		
			else
				CreateWindow("STATIC", "no command", WS_CHILD | WS_VISIBLE |SS_CENTER | SS_CENTERIMAGE, 350, 80, 200, 30, hWnd, NULL, NULL, NULL );		

			tester->SetAttenuation(J*StepAtt);
			SendDlgItemMessage(hWnd, ID_AttCombo, CB_SETCURSEL, J, 0);				// установка значения ослабления в первоначальное положение
		
			break;

		case ID_AltitudeTest: 														// запуск теста высоты
			tester->SetVK(FALSE);													// сбросили выдачу команды
			J = SendDlgItemMessage(hWnd, ID_AltCombo, CB_GETCURSEL, 0, 0);
			for(int i = J; i>=0; i--){
				SendDlgItemMessage(hWnd, ID_AltCombo, CB_SETCURSEL, i, 0);			// изменение значения высоты на форме
				UpdateWindow(hWnd);													// обновление окна
				tester->SetAltitude(i*StepAlt);										// установка текущего значения ослабления в тестер
				Sleep(6);															// пауза компенсации переходных процессов
				vk = tester->GetVK();												// считывание наличия выходной команды
				err = tester->GetError();											// считывание наличия ошибок
				if ( vk == TRUE ){													// при наличии выходной команды выходим из теста
					s = "Altitude = " + std::to_string((long double) tester->GetAltitude());
					break;
				}
			}

			if ( vk == TRUE )
				CreateWindowA("STATIC",  (LPSTR) s.c_str(), WS_CHILD | WS_VISIBLE |SS_CENTER | SS_CENTERIMAGE, 350, 190, 200, 30, hWnd, NULL, NULL, NULL );		
			else
				CreateWindow("STATIC", "no command", WS_CHILD | WS_VISIBLE |SS_CENTER | SS_CENTERIMAGE, 350, 190, 200, 30, hWnd, NULL, NULL, NULL );		
			
			SendDlgItemMessage(hWnd, ID_AltCombo,CB_SETCURSEL, J, 0);				// вывод сообщения об измеренном значении высоты
			tester->SetAltitude(J*StepAlt);
			break;
			
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;

		default:
			break;
		}
	    break;

	case WM_CREATE:
		
		ExitButton         = CreateWindow("button", "Exit", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  150, 255, 80, 30, hWnd, (HMENU)ID_ExitButton, hInst, 0);
		AltCombo           = CreateWindow("ComboBox", NULL, CBS_HASSTRINGS | CBS_DROPDOWN | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | WS_VSCROLL, 150, 45, 80, 250, hWnd, (HMENU)ID_AltCombo, hInst,   0);
		AttCombo           = CreateWindow("ComboBox", "", CBS_HASSTRINGS | CBS_DROPDOWN | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | WS_VSCROLL, 150, 90, 80, 250, hWnd, (HMENU)ID_AttCombo, hInst,    0);
		AuxAttCombo        = CreateWindow("ComboBox", "", CBS_HASSTRINGS | CBS_DROPDOWN | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | WS_VSCROLL, 150, 135, 80, 250, hWnd, (HMENU)ID_AuxAttCombo, hInst,  0);
		CalibrateEnable    = CreateWindow("button", "Calibrate", WS_CHILD|WS_VISIBLE|BS_AUTOCHECKBOX, 150, 180, 80, 50, hWnd, (HMENU)ID_CalibrateEnable, hInst, NULL);
		PowerPotentialTest = CreateWindow("button", "Power Potential Test", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  350, 40, 200, 30, hWnd, (HMENU)ID_PowerPotentialTest, hInst, 0);
		AltitudeTest       = CreateWindow("button", "Altitude Test", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  350, 150, 200, 30, hWnd, (HMENU)ID_AltitudeTest, hInst, 0);
		FindPotential      = CreateWindow("STATIC", "no test result", WS_CHILD | WS_VISIBLE |SS_CENTER | SS_CENTERIMAGE, 350, 80, 200, 30, hWnd, NULL, NULL, NULL );
		FindAltitude       = CreateWindow("STATIC", "no test result", WS_CHILD | WS_VISIBLE |SS_CENTER | SS_CENTERIMAGE, 350, 190, 200, 30, hWnd, NULL, NULL, NULL );

		// начальные установки диапазона выбора высоты
		for(int i = 0; i<NAlt; i++){
			sprintf_s(arv, "%.3f", double(i)*StepAlt); 
			SendMessage(AltCombo, CB_ADDSTRING, 0, (LPARAM) arv);
		}
		SendMessage(AltCombo, CB_SETCURSEL, 250, 0);
		
		// начальные установки диапазона выбора ослабления
		for(int i = 0; i<127; i++){
			sprintf_s(arv, "%ld", i); 
			SendMessage(AttCombo, CB_ADDSTRING, 0, (LPARAM)arv);
		}
		SendMessage(AttCombo, CB_SETCURSEL, 120, 0);

		// начальные установки диапазона выбора дополнительного ослабления
		for(int i = 0; i<15; i++){
			sprintf_s(arv, "%ld", i); 
			SendMessage(AuxAttCombo, CB_ADDSTRING, 0, (LPARAM)arv);
		}
		SendMessage(AuxAttCombo, CB_SETCURSEL, 10, 0);
	    break;

	case WM_PAINT:
		// рисование статичных  надписей
		hdc = BeginPaint(hWnd, &ps);
			TextOutA(hdc, 20, 50,  "Altitude", strlen("Altitude"));
            TextOutA(hdc, 20, 95,  "Atteniation", strlen("Atteniation"));
            TextOutA(hdc, 20, 135, "AuxAtt", strlen("AuxAtt"));
		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		delete tester; // удаление глобальной переменной при закрытии окна
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
