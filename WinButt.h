#pragma once
#include "structures.h"
#include <string>
#include <list>
#include <vector>
#include <GL/glut.h>

using namespace std;

class Button;

class Window
{
  static POSITION position; 
  static SIZE size;
  string WinName;
  COLOR color;
  list<Button> Buttons; //список кнопок, отображаемых в окне
  list<Window> Windows; //список окон, к которым можно перейти через это окно
  Window* prevWindow; //предыдущее окно, на которое можно перейти по кнопке back
  Button* activationButton; //кнопка, принадлежащая предыдущему окну, по которой можно перейти к этому окну
public:
  explicit Window(const string& name, const COLOR& col, Window* prevWin, Button* actBut);
  Window(const Window& win);
  void setSize(const SIZE& s) { size = s; };
  void setPosition(const POSITION& pos) { position = pos; };
  string getWinName() const { return WinName; };
  COLOR getColor(void) const { return color; };
  Window* getPrevWindow(void) const { return prevWindow; };
  Button* getLastButton(void);
  Window* getLastSubWindow(void) { return &Windows.back(); };
  Window* PressButton(POSITION mousePos); //переходит к окну, активируемому кнопкой, которую выделили мышью 
  void AddBackButton(); //добавляет кнопку возврата назад (back)
  void addButton(Button button);
  void addSubWindow(const Window& win);
  void DrawButtons(const POSITION& mousePos);
  void Clear() const;
};

class Button
{
  string ButtonName;
  COLOR color;
  POSITION position;
  SIZE size;
  Window* activatedWindow;
public:
  Button(string name, COLOR col, POSITION pos, SIZE s);
  //Button(const Button& button);
  void Draw();
  void DrawEdges(); //рисует обводку вокруг кнопки
  void WriteText(); 
  bool CheckMouse(const POSITION& pos); //проверяет позицию мыши в области кнопки
  Window* getWindow(void) { return activatedWindow; };
  void SetActivatedWindow(Window* winP) { activatedWindow = winP; };
};
