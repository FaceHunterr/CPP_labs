#pragma once
#include "structures.h"
#include <string>
#include <list>
#include <vector>
#include <GL/glut.h>

using namespace std;

class Button;

class SubWindow;

class Window
{
  static POSITION position;
  static SIZE size;
  string WinName;
  COLOR color;
  list<Button> Buttons; //список кнопок, отображаемых в окне
  list<Window> Windows; //список окон, к которым можно перейти через это окно
public:
  explicit Window(const string& name, const COLOR& col);
  Window(const Window& win);
  Window(const SubWindow& win);
  void setSize(const SIZE& s) { size = s; };
  SIZE getSize(void) { return size; };
  void setPosition(const POSITION& pos) { position = pos; };
  string getWinName() const { return WinName; };
  COLOR getColor(void) const { return color; };
  Button* getLastButton(void);
  Button* getFirstButton(void);
  Window* getLastSubWindow(void) { return &Windows.back(); };
  Window* PressButton(POSITION mousePos); //возвращает окно, на которое нужно перейти при нажатии мышью
  void addButton(Button button);
  void addSubWindow(const SubWindow& win);
  void DrawButtons(const POSITION& mousePos);
  void Clear() const;
};

class SubWindow : public Window
{
public:
  SubWindow(const Window& win, Window* prevWin); 
};

class Button
{
  string ButtonName;
  COLOR color;
  POSITION position;
  SIZE size;
  Window* activatedWindow;
public:
  Button(string name, COLOR col, POSITION pos, SIZE s, Window* win);
  void Draw();
  void DrawEdges(); //рисует обводку вокруг кнопки
  void WriteText();
  bool CheckMouse(const POSITION& pos); //проверяет позицию мыши в области кнопки
  Window* getWindow(void) { return activatedWindow; };
  void SetActivatedWindow(Window* winP) { activatedWindow = winP; };
};
