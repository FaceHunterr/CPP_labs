#include <windows.h>
#include "Figure.h"
#include <list>
//const double PI = 3.141592653;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
char szClassName[] = "Workspace";
Figure figure;
list<Figure> track;


const unsigned int TIMER1 = 1;
const double TURN_SPEED = 2 * pi / 4;
const unsigned int DT = 10;
const double ACCELERATION = 50;
const unsigned int TRACK_SIZE = 16;

////////////////////////////////////////////////////////////////////////////////////////////////////
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
  HWND hWnd;
  MSG lpMsg;
  WNDCLASS wc;

  // Заполняем структуру класса окна
  wc.style = CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc = WndProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = hInstance;
  wc.hIcon = NULL;
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
  wc.lpszMenuName = NULL;
  wc.lpszClassName = (LPCWSTR)szClassName;

  // Регистрируем класс окна
  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, (LPCWSTR)"Не могу зарегистрировать класс окна!", (LPCWSTR)"Ошибка", MB_OK);
    return 0;
  }

  // Создаем основное окно приложения
  hWnd = CreateWindow(
    (LPCWSTR)szClassName, // Имя класса 
    L"Окошечко", // Текст заголовка
    WS_OVERLAPPEDWINDOW, // Стиль окна 
    50, 50, // Позиция левого верхнего угла 
    1200, 700, // Ширина и высота окна 
    (HWND)NULL, // Указатель на родительское окно NULL 
    (HMENU)NULL, // Используется меню класса окна 
    (HINSTANCE)hInstance, // Указатель на текущее приложение
    NULL); // Передается в качестве lParam в событие WM_CREATE

  if (!hWnd)
  {
    MessageBox(NULL, (LPCWSTR)"Не удается создать главное окно!", (LPCWSTR)"Ошибка", MB_OK);
    return 0;
  }

  // Показываем наше окно
  ShowWindow(hWnd, nCmdShow);
  UpdateWindow(hWnd);

  // Выполняем цикл обработки сообщений до закрытия приложения
  while (GetMessage(&lpMsg, NULL, 0, 0))
  {
    TranslateMessage(&lpMsg);
    DispatchMessage(&lpMsg);
  }
  return (lpMsg.wParam);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK WndProc(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam)
{
  PAINTSTRUCT ps;
  RECT Rect;
  HDC hdc, hCmpDC;
  HBITMAP hBmp;
  int KeyPressed;
  unsigned int color;
  GetClientRect(hWnd, &Rect);
  
  switch (messg)
  {
  case WM_CREATE:
    SetTimer(hWnd, TIMER1, DT, nullptr);
    figure = Figure(Vector(0, 0), Vector(1, 0), (Rect.bottom - Rect.top) / 20.0, 10, Vector(0, 0)); //создает фигуру по центру экрана
    break;
  case WM_TIMER:
    InvalidateRect(hWnd, NULL, FALSE);
    break;
  case WM_KEYDOWN:
    KeyPressed = int(wParam);
    if (KeyPressed == VK_RIGHT)
    {
      figure.addSpeed(Vector(ACCELERATION, 0)); //ускоряет вправо
    }
    if (KeyPressed == VK_LEFT)
    {
      figure.addSpeed(Vector(-ACCELERATION, 0)); //ускоряет влево
    }
    if (KeyPressed == VK_UP)
    {
      figure.addSpeed(Vector(0, ACCELERATION)); //ускоряет вверх
    }
    if (KeyPressed == VK_DOWN)
    {
      figure.addSpeed(Vector(0, -ACCELERATION)); //ускоряет вниз
    }
    if (KeyPressed == VK_SHIFT)
    {
      figure.SpeedUp(); // ускоряет в направлении текущего движения
    }
    if (KeyPressed == VK_SPACE)
    {
      figure.SlowDown(100); //замедляет
    }
    InvalidateRect(hWnd, NULL, FALSE);
    break;
  case WM_PAINT:
    GetClientRect(hWnd, &Rect);
    hdc = BeginPaint(hWnd, &ps);

    // Создание теневого контекста для двойной буферизации
    hCmpDC = CreateCompatibleDC(hdc);
    hBmp = CreateCompatibleBitmap(hdc, Rect.right - Rect.left,
      Rect.bottom - Rect.top);
    SelectObject(hCmpDC, hBmp);

    // Закраска фоновым цветом
    LOGBRUSH br;
    br.lbStyle = BS_SOLID;
    br.lbColor = 0xEECCCC;
    HBRUSH brush;
    brush = CreateBrushIndirect(&br);
    FillRect(hCmpDC, &Rect, brush);
    DeleteObject(brush);

    // Здесь рисуем на контексте hCmpDC

    figure.rotate(TURN_SPEED * DT / 1000.0); //обеспечивает постоянное вращение
    figure.move(figure.GetSpeed() * (DT / 1000.0)); // передвигает
    figure.CheckBorders(Rect); //реализует отражение от стенок

    //образует след
    if (track.size() >= TRACK_SIZE)
    {
      track.pop_front();
    }
    track.push_back(figure);
    color = 8 * TRACK_SIZE;
    for(auto f : track)
    {
      HPEN pn = CreatePen(PS_SOLID, 2, RGB(color, color, color));
      SelectObject(hCmpDC, pn);
      f.Draw(hCmpDC, Rect);
      color -= 0x080808;
      DeleteObject(pn);

    }
    



    // Копируем изображение из теневого контекста на экран
    SetStretchBltMode(hdc, COLORONCOLOR);
    BitBlt(hdc, 0, 0, Rect.right - Rect.left, Rect.bottom - Rect.top,
      hCmpDC, 0, 0, SRCCOPY);

    // Удаляем ненужные системные объекты
    DeleteDC(hCmpDC);
    DeleteObject(hBmp);
    hCmpDC = NULL;

    EndPaint(hWnd, &ps);
    break;

  case WM_DESTROY:
    PostQuitMessage(0);
    break;

  default:
    return (DefWindowProc(hWnd, messg, wParam, lParam));
  }
  return (0);
}