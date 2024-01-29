#include "../include/main.h"
#include "../include/Buffer.h"

#include "../projects/defaultProject.cpp"


void updateWindowSize(HWND hwnd) {
	LPRECT rectDlg = (LPRECT)malloc(sizeof(*rectDlg));
	GetWindowRect(hwnd, rectDlg);
	if (rectDlg != nullptr) {
		GL_WINDOW_WIDTH = (rectDlg->right - rectDlg->left);
		GL_WINDOW_HEIGHT = (rectDlg->bottom - rectDlg->top);
	}
}

void drawCall(HWND hwnd) {
		HDC hdc = GetDC(hwnd);
		updateWindowSize(hwnd);
		Graphics graphics(hdc);
		Bitmap bitmap = Bitmap(GL_WINDOW_WIDTH, GL_WINDOW_HEIGHT);
		WindowBuffer::getInstance()->updateWindowBuffer();
		WindowBuffer::getInstance()->loadCurrentFrameBufferToBitmap(bitmap);
		graphics.DrawImage(&bitmap, 0, 0, GL_WINDOW_WIDTH, GL_WINDOW_HEIGHT);
		ReleaseDC(hwnd, hdc);
}

void  CALLBACK Update(HWND hwnd, UINT message, UINT_PTR iTimerID, DWORD dwTime)
{
	//Project Update
	GL_MAIN_PROJECT->update();
	drawCall(hwnd);
}

void end() {
	WindowBuffer::getInstance()->deleteInstance();
	if (GL_MAIN_PROJECT != NULL) {
		delete GL_MAIN_PROJECT;
		GL_MAIN_PROJECT = NULL;
	}

}

void Init() {
	Project* project = new DefaultProject();
	project->init();
	GL_MAIN_PROJECT = project;
}




LRESULT CALLBACK WinSunProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		HDC hdc;
		PAINTSTRUCT  ps;
	case WM_CLOSE:
		end();
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT: {
		hdc = BeginPaint(hwnd, &ps);
		if (GL_MAIN_PROJECT != NULL) {
			GL_MAIN_PROJECT->update();
		}
		drawCall(hwnd);
		EndPaint(hwnd, &ps);
		break;
	}
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd) {

	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	// Initialize GDI+.
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);


	WNDCLASS wndcls;
	wndcls.cbClsExtra = 0;
	wndcls.cbWndExtra = 0;
	wndcls.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndcls.hCursor = 0;
	wndcls.hIcon = 0;
	wndcls.hInstance = hInstance;
	wndcls.lpfnWndProc = WinSunProc;
	wndcls.lpszClassName = CONF_CLASSNAME;
	wndcls.lpszMenuName = NULL;
	wndcls.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wndcls);

	GL_HINSTANCE = hInstance;

	GL_HWND = CreateWindowEx(
		0,
		CONF_CLASSNAME,
		CONF_WINDOWTITLE,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL,
		NULL,
		GL_HINSTANCE,
		NULL
	);

	if (GL_HWND == NULL) {
		return 0;
	}
	ShowWindow(GL_HWND, SW_SHOWNORMAL);
	UpdateWindow(GL_HWND);

	SetTimer(GL_HWND, 1, CONF_REFRESH_TIME, Update);

	Init();

	MSG msg;
	//Listening Message
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	GdiplusShutdown(gdiplusToken);

	return msg.wParam;
}