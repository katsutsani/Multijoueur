// Serveur.cpp : Définit le point d'entrée de l'application.
//

#include "Serveur.h"
#include "ServerSocket.h"
#include "ServThread.h"
#include "ServWebThread.h"
#include <string>
#include "JSON.h"

#define MAX_LOADSTRING 100

// Variables globales :
HINSTANCE hInst;                                // instance actuelle
WCHAR szTitle[MAX_LOADSTRING];                  // Texte de la barre de titre
WCHAR szWindowClass[MAX_LOADSTRING];            // nom de la classe de fenêtre principale
HWND hWnd;
bool isPlaying = false;
SOCKET tempClientSocket;
JSON jsonData;
std::string tempString;
ServerSocket servSock;
HANDLE allThreads[2];
ServWebThread servWebThread;
// Déclarations anticipées des fonctions incluses dans ce module de code :
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Placez le code ici.

	// Initialise les chaînes globales
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_SERVEUR, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Effectue l'initialisation de l'application :
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SERVEUR));
	MSG msg;
	WSAAsyncSelect(servSock.ListenSocket, hWnd, WM_USER, FD_ACCEPT | FD_CLOSE | FD_READ);
	servWebThread.createServerWebThread(hWnd);
	allThreads[0] = servWebThread.GetThread();
	// Boucle de messages principale :
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			if (listen(servSock.ListenSocket, SOMAXCONN) == SOCKET_ERROR) {
				printf("listen failed with error: %ld\n", WSAGetLastError());
				closesocket(servSock.ListenSocket);
				WSACleanup();
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  FONCTION : MyRegisterClass()
//
//  OBJECTIF : Inscrit la classe de fenêtre.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SERVEUR));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_SERVEUR);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   FONCTION : InitInstance(HINSTANCE, int)
//
//   OBJECTIF : enregistre le handle d'instance et crée une fenêtre principale
//
//   COMMENTAIRES :
//
//        Dans cette fonction, nous enregistrons le handle de l'instance dans une variable globale, puis
//        nous créons et affichons la fenêtre principale du programme.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Stocke le handle d'instance dans la variable globale

	hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FONCTION : WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  OBJECTIF : Traite les messages pour la fenêtre principale.
//
//  WM_COMMAND  - traite le menu de l'application
//  WM_PAINT    - Dessine la fenêtre principale
//  WM_DESTROY  - génère un message d'arrêt et retourne
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Analyse les sélections de menu :
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Ajoutez ici le code de dessin qui utilise hdc...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		servWebThread.Close();
		WaitForMultipleObjects(2, allThreads, TRUE, INFINITE);
		for (int i = 0; i < 2; i++)
			CloseHandle(allThreads[i]);
		CloseHandle(servWebThread.GetMutex());
		PostQuitMessage(0);
		break;
	case WM_USER:
		switch (lParam)
		{
		case FD_ACCEPT:
			tempClientSocket = INVALID_SOCKET;
			servSock.ClientSocket.insert({ servSock.players,tempClientSocket });
			servSock.ClientSocket[servSock.players] = accept(servSock.ListenSocket, NULL, NULL);
			if (servSock.ClientSocket[servSock.players] == INVALID_SOCKET) {
				printf("accept failed: %d\n", WSAGetLastError());
				closesocket(servSock.ListenSocket);
				WSACleanup();
				break;
			}
			if (servSock.players >= 2) {
				tempString = std::to_string(servSock.players) + "S";
			}
			else {
				tempString = std::to_string(servSock.players) + "P";
			}
			servSock.SendInfo(servSock.ClientSocket[servSock.players], tempString.c_str());
			servSock.players++;
			break;
		case FD_CLOSE:
			servSock.players--;
			break;
		case FD_READ:
			servSock.ReceiveInfo();
			break;
		}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Gestionnaire de messages pour la boîte de dialogue À propos de.
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
