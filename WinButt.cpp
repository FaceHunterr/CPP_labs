#include "WinButt.h"
#include <iostream>
#define FONT GLUT_BITMAP_HELVETICA_18

Window::Window(const string& name, const COLOR& col)
{
  WinName = name;
  color = col;
}

Window::Window(const Window& win)
{
  WinName = win.WinName;
  color = win.color;
  for (auto b : win.Buttons)
    Buttons.push_back(b);
}

Window::Window(const SubWindow& win)
{
  WinName = win.WinName;
  color = win.color;
  for (auto b : win.Buttons)
    Buttons.push_back(b);
}

void Window::Clear() const
{
  glBegin(GL_QUADS);
  glColor3f(color.red * 1.25, color.green * 1.25, color.blue * 1.25);
  glVertex2f(0, 0);
  glVertex2f(size.width, 0);
  glColor3f(color.red * 0.8, color.green * 0.8, color.blue * 0.8);
  glVertex2f(size.width, size.height);
  glVertex2f(0, size.height);
  glEnd();
}

void Window::addButton(Button button)
{
  Buttons.push_back(button);
}

void Window::DrawButtons(const POSITION& mousePos)
{
  for (auto button : Buttons)
  {
    button.Draw();
    if (button.CheckMouse(mousePos))
      button.DrawEdges();
    button.WriteText();
  }
}

Button* Window::getLastButton()
{
  return &Buttons.back();
}

Button* Window::getFirstButton()
{
  return &Buttons.front();
}

void Window::addSubWindow(const SubWindow& win)
{
  Windows.push_back(win);
  getLastButton()->SetActivatedWindow(getLastSubWindow());
}

Window* Window::PressButton(POSITION mousePos)
{
  for (auto button : Buttons)
  {
    if (button.CheckMouse(mousePos) && button.getWindow())
      return button.getWindow();
  }
  return this;
}


//////////////////

SubWindow::SubWindow(const Window& win, Window* prevWin) :
  Window(win)
{
  COLOR ButtColor = getColor();
  ButtColor.blue = (ButtColor.blue >= 0.5) ? ButtColor.blue - 0.5 : ButtColor.blue + 0.5;
  ButtColor.green = (ButtColor.green >= 0.5) ? ButtColor.green - 0.5 : ButtColor.green + 0.5;
  ButtColor.red = (ButtColor.red >= 0.5) ? ButtColor.red - 0.5 : ButtColor.red + 0.5;
  POSITION ButtPosition = { getSize().width * 9 / 10, 0 };
  SIZE ButtSize = { int(getSize().width * 0.1), int(getSize().height * 0.1) };
  addButton(Button("Back", ButtColor, ButtPosition, ButtSize, prevWin));
}

//////////////////

Button::Button(string name, COLOR col, POSITION pos, SIZE s, Window* win)
{
  ButtonName = name;
  color = col;
  position = pos;
  size = s;
  activatedWindow = win;
}

void Button::Draw()
{
  glColor3f(color.red, color.green, color.blue);
  glBegin(GL_QUADS);
  glColor3f(color.red * 0.8, color.green * 0.8, color.blue * 0.8);
  glVertex2f(position.x, position.y);
  glVertex2f(position.x + size.width, position.y);
  glColor3f(color.red * 1.25, color.green * 1.25, color.blue * 1.25);
  glVertex2f(position.x + size.width, position.y + size.height);
  glVertex2f(position.x, position.y + size.height);
  glEnd();
}

void Button::DrawEdges()
{
  COLOR EdgeColor;
  EdgeColor.blue = (color.blue >= 0.5) ? color.blue - 0.5 : color.blue;
  EdgeColor.green = (color.green >= 0.5) ? color.green - 0.5 : color.green;
  EdgeColor.red = (color.red >= 0.5) ? color.red - 0.5 : color.red;
  glColor3f(EdgeColor.red, EdgeColor.green, EdgeColor.blue);
  glLineWidth(2);
  glBegin(GL_LINE_STRIP);
  glVertex2f(position.x, position.y);
  glVertex2f(position.x + size.width, position.y);
  glVertex2f(position.x + size.width, position.y + size.height);
  glVertex2f(position.x, position.y + size.height);
  glVertex2f(position.x, position.y);
  glEnd();
}

bool Button::CheckMouse(const POSITION& pos)
{
  if (pos.x >= position.x && pos.x <= position.x + size.width &&
    pos.y >= position.y && pos.y <= position.y + size.height)
    return true;
  return false;
}

void Button::WriteText()
{
  COLOR newCol;
  newCol.blue = (color.blue <= 0.25) ? 1 : 0;
  newCol.green = (color.green <= 0.25) ? 1 : 0;
  newCol.red = (color.red <= 0.25) ? 1 : 0;
  glColor3f(newCol.red, newCol.green, newCol.blue);
  //тут попытки написать текст примерно по середине, по возможности обрезая слишком длинные названия
  int NameWidth = glutBitmapLength(FONT, (unsigned char*)ButtonName.c_str());
  int simbWidth = NameWidth / ButtonName.size();
  int maxNameLen = (NameWidth > size.width - simbWidth * 2) ? size.width / simbWidth - 2: NameWidth / simbWidth;
  int width = glutBitmapWidth(FONT, (unsigned char)(ButtonName[0]));
  glRasterPos2d((double)position.x + size.width / 2.0 - maxNameLen * simbWidth  / 2.0, (double)position.y + size.height / 2.0 + width / 2.0);
  for (auto c : ButtonName.substr(0, maxNameLen))
  {
    glutBitmapCharacter(FONT, c);
  }
}
