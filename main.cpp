#include <windows.h>
#include <shellapi.h>
#include <fstream>

#define ID_BUTTON1 1
#define ID_BUTTON2 2
#define ID_BUTTON3 3
#define ID_BUTTON4 4
#define ID_TEXTBOX1 5
#define ID_TEXTBOX2 6


using namespace std;
static HWND hwndTextBox1, hwndTextBox2;

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		
		case WM_CREATE: {
			
			CreateWindow(TEXT("STATIC"), TEXT("Sistema MapSearch - Coordenadas Geográficas"),
				WS_CHILD | WS_VISIBLE,
				130, 40, 340, 40,
				hwnd, (HMENU) NULL, NULL, NULL);
				
			CreateWindow(TEXT("STATIC"), TEXT("Coordenadas"),
				WS_CHILD | WS_VISIBLE,
				130, 90, 340, 40,
				hwnd, (HMENU) NULL, NULL, NULL);
				
			CreateWindow(TEXT("STATIC"), TEXT("Ponto de Referência"),
				WS_CHILD | WS_VISIBLE,
				130, 170, 340, 40,
				hwnd, (HMENU) NULL, NULL, NULL);
				
			hwndTextBox1 = CreateWindow(TEXT("EDIT"), TEXT(""),
				WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
				130, 110, 320, 22,
				hwnd, (HMENU) ID_TEXTBOX1, NULL, NULL);
				
			hwndTextBox2 = CreateWindow(TEXT("EDIT"), TEXT(""),
				WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
				130, 190, 320, 22,
				hwnd, (HMENU) ID_TEXTBOX2, NULL, NULL);
			
			CreateWindow(TEXT("BUTTON"), TEXT("Buscar"),
				WS_CHILD | WS_VISIBLE | WS_BORDER,
				160, 280, 80, 25,
				hwnd, (HMENU) ID_BUTTON1, NULL, NULL);
				
			CreateWindow(TEXT("BUTTON"), TEXT("Adicionar"),
				WS_CHILD | WS_VISIBLE | WS_BORDER,
				330, 280, 80, 25,
				hwnd, (HMENU) ID_BUTTON2, NULL, NULL);
				
			CreateWindow(TEXT("BUTTON"), TEXT("Localizações Salvas"),
				WS_CHILD | WS_VISIBLE | WS_BORDER,
				130, 218, 150, 20,
				hwnd, (HMENU) ID_BUTTON3, NULL, NULL);
				
			CreateWindow(TEXT("BUTTON"), TEXT("Instruções"),
				WS_CHILD | WS_VISIBLE | WS_BORDER,
				480, 10, 90, 20,
				hwnd, (HMENU) ID_BUTTON4, NULL, NULL);
			
			break;
		}
		
		case WM_COMMAND: {
			if (LOWORD(wParam) == ID_BUTTON1) {
				int length = GetWindowTextLength(hwndTextBox1) + 1;
				static char text[500];
				std::string url; 
				
				GetWindowText(hwndTextBox1, text, length);
				
				if (std::string(text) == "") {
					MessageBox(hwnd, "Nenhuma coordenada foi informada.",
					"Erro", MB_ICONWARNING);
				}
				else {
					ShellExecute(0, 0, ("https://www.google.com.br/maps/@" + std::string(text) + 
					",172m/data=!3m1!1e3").c_str(), 0, 0, SW_SHOW);
					SetWindowText(hwndTextBox1, "");
					SetWindowText(hwndTextBox2, "");
				}
			}
			else if (LOWORD(wParam) == ID_BUTTON2) {
				fstream file;
				int length1 = GetWindowTextLength(hwndTextBox1) + 1;
				int length2 = GetWindowTextLength(hwndTextBox2) + 1;
				static char text1[500];
				static char text2[500];
				
				GetWindowText(hwndTextBox1, text1, length1);
				GetWindowText(hwndTextBox2, text2, length2);
				
				if (std::string(text1) == "") {
					MessageBox(hwnd, "Nenhuma coordenada foi informada.",
					"Erro", MB_ICONWARNING);
				}
				else if (std::string(text2) == "") {
					MessageBox(hwnd, "Nenhum ponto de referência foi informado.",
					"Erro", MB_ICONWARNING);
				}
				else {
					file.open("locations.txt", ios::out | ios::app);
					file << std::string(text1) << "___" << std::string(text2) << "\n";
					MessageBox(hwnd, "Localização adicionada ao arquivo 'location.txt' com sucesso.",
					"MapSearch System", MB_ICONINFORMATION);
				}
			}
			else if (LOWORD(wParam) == ID_BUTTON3)
				ShellExecute(0, 0, "locations.txt", 0, 0, SW_SHOW);
			else if (LOWORD(wParam) == ID_BUTTON4)
				ShellExecute(0, 0, "README.txt", 0, 0, SW_SHOW);
			break;
		}
		
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc;
	HWND hwnd;
	MSG msg;

	memset(&wc,0,sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; 
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	
	wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	wc.lpszClassName = "WindowClass";
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION); 
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION);

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","MapSearch System",WS_VISIBLE|WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT, 
		600, 
		400, 
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	while(GetMessage(&msg, NULL, 0, 0) > 0) { 
		TranslateMessage(&msg); 
		DispatchMessage(&msg); 
	}
	return msg.wParam;
}
