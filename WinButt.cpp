#include "WinButt.h"
#include <iostream>
#define FONT GLUT_BITMAP_HELVETICA_18

Window::Window(const string& name, const COLOR& col, Window* prevWin, Button* actBut)
{
  WinName = name;
  color = col;
  activationButton = actBut;
}

Window::Window(const Window& win)
{
  WinName = win.WinName;
  color = win.color;
  activationButton = win.activationButton;
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

void Window::addSubWindow(const Window& win)
{
  Windows.push_back(win);
  Windows.back().activationButton->SetActivatedWindow(&(Windows.back()));
  Windows.back().AddBackButton();
  Windows.back().getFirstButton()->SetActivatedWindow(this);
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

void Window::AddBackButton()
{
  COLOR ButtColor;
  ButtColor.blue = (color.blue >= 0.5) ? color.blue - 0.5 : color.blue + 0.5;
  ButtColor.green = (color.green >= 0.5) ? color.green - 0.5 : color.green + 0.5;
  ButtColor.red = (color.red >= 0.5) ? color.red - 0.5 : color.red + 0.5;
  POSITION ButtPosition = { size.width * 9 / 10, 0 };
  SIZE ButtSize = { int(size.width * 0.1), int(size.height * 0.1) };
  Buttons.push_back(Button("Back", ButtColor, ButtPosition, ButtSize));

}


//////////////////

Button::Button(string name, COLOR col, POSITION pos, SIZE s)
{
  ButtonName = name;
  color = col;
  position = pos;
  size = s;
  activatedWindow = nullptr;
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
