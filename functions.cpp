#include "functions.h"

const double SHADES = 255.0;

static Window *CurWin = nullptr;
static Window* MainWin = nullptr;


POSITION mousePosition;
POSITION Window::position;
SIZE Window::size;

void MenuCreating(ifstream& inputFile)
{
  string readedLine;
  vector<std::string> words;
  do
  {
    if (inputFile.fail() || inputFile.eof() || inputFile.bad())
      break;
    getline(inputFile, readedLine);
    istringstream stream_line(readedLine);
    std::copy(std::istream_iterator<std::string>(stream_line), std::istream_iterator<std::string>(), std::back_inserter(words));
    if (words.empty())
      continue;
    if (ToLower(words[0]) == "main_window:")
    {
      MainWinInit(inputFile);
    }
    else if (ToLower(words[0]) == "add_button:")
    {
      addButton(inputFile);
    }
    else if (ToLower(words[0]) == "add_window:")
    {
      addSubWindow(inputFile);
    }
    else if (ToLower(words[0]) == "end_window")
    {
      CurWin = CurWin->getFirstButton()->getWindow();
    }
    else
    {
      EndWork();
      exit(1);
    }
    words.clear();
    readedLine.clear();
  } while (true);
  CurWin = MainWin;
}

void MainWinInit(ifstream& inputFile)
{
  string readedLine;
  vector<std::string> words;
  string WinName;
  POSITION position;
  SIZE size;
  COLOR color;
  for (int i = 0; i < 4; i++)
  {
    do
    {
      getline(inputFile, readedLine);
    } while (readedLine.empty());
    istringstream stream_line(readedLine);
    std::copy(std::istream_iterator<std::string>(stream_line), std::istream_iterator<std::string>(), std::back_inserter(words));
    if (ToLower(words[0]) == "name")
    {
      for (auto word = words.begin() + 1; word < words.end(); word++)
        WinName += *word + ' ';
    }
    else if (ToLower(words[0]) == "position")
    {
      position.x = atoi(words[1].c_str());
      position.y = atoi(words[2].c_str());
    }
    else if (ToLower(words[0]) == "size")
    {
      size.width = atoi(words[1].c_str());
      size.height = atoi(words[2].c_str());
    }
    else if (ToLower(words[0]) == "color")
    {
      color.red = atof(words[1].c_str()) / SHADES;
      color.green = atof(words[2].c_str()) / SHADES;
      color.blue = atof(words[3].c_str()) / SHADES;
    }
    else break;
    words.clear();
    readedLine.clear();
  }
  
  CurWin = MainWin = new Window(WinName, color, nullptr, nullptr);
  MainWin->setPosition(position);
  MainWin->setSize(size);
  glutInitWindowPosition(position.x, position.y);
  glutInitWindowSize(size.width, size.height);
  glutCreateWindow(MainWin->getWinName().c_str());
  glViewport(0, 0, size.width, size.height);
  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(0, size.width, size.height, 0);
  glMatrixMode(GL_MODELVIEW);
}

void addButton(ifstream& inputFile)
{
  string readedLine;
  vector<std::string> words;
  string BottonName;
  POSITION position;
  SIZE size;
  COLOR color;

  for (int i = 0; i < 4; i++)
  {
    
    do
    {
      getline(inputFile, readedLine);
    } while (readedLine.empty());
    istringstream stream_line(readedLine);
    std::copy(std::istream_iterator<std::string>(stream_line), std::istream_iterator<std::string>(), std::back_inserter(words));
    if (ToLower(words[0]) == "name")
    {
      for (auto word = words.begin() + 1; word < words.end(); word++)
        BottonName += *word + ' ';
    }
    else if (ToLower(words[0]) == "position")
    {
      position.x = atoi(words[1].c_str());
      position.y = atoi(words[2].c_str());
    }
    else if (ToLower(words[0]) == "size")
    {
      size.width = atoi(words[1].c_str());
      size.height = atoi(words[2].c_str());
    }
    else if (ToLower(words[0]) == "color")
    {
      color.red = atof(words[1].c_str()) / SHADES;
      color.green = atof(words[2].c_str()) / SHADES;
      color.blue = atof(words[3].c_str()) / SHADES;
    }
    else break;
    words.clear();
    readedLine.clear();
  }
  CurWin->addButton(Button(BottonName, color, position, size));

}

void addSubWindow(ifstream& inputFile)
{
  string readedLine;
  vector<std::string> words;
  string WinName;
  COLOR color;

  for (int i = 0; i < 2; i++)
  {
    do
    {
      getline(inputFile, readedLine);
    } while (readedLine.empty());
    istringstream stream_line(readedLine);
    std::copy(std::istream_iterator<std::string>(stream_line), std::istream_iterator<std::string>(), std::back_inserter(words));
    if (ToLower(words[0]) == "name")
    {
      for (auto word = words.begin() + 1; word < words.end(); word++)
        WinName += *word + ' ';
    }
    else if (ToLower(words[0]) == "color")
    {
      color.red = atof(words[1].c_str()) / SHADES;
      color.green = atof(words[2].c_str()) / SHADES;
      color.blue = atof(words[3].c_str()) / SHADES;
    }
    else break;
    words.clear();
    readedLine.clear();
  }
  CurWin->addSubWindow(Window(WinName, color, CurWin, CurWin->getLastButton()));
  CurWin = CurWin->getLastSubWindow();

}

void Display()
{
  CurWin->Clear();
  CurWin->DrawButtons(mousePosition);
  glutSwapBuffers();
}


void mouse(int button, int state, int x, int y)
{
  mousePosition.x = x;
  mousePosition.y = y;
  if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
  {
    CurWin = CurWin->PressButton(mousePosition);
    glutSetWindowTitle(CurWin->getWinName().c_str());
  }
}

void motion(int x, int y)
{
  mousePosition.x = x;
  mousePosition.y = y;
}

void EndWork(void)
{
  delete MainWin;
}

string ToLower(const string& str)
{
  string returnedString;
  for (auto simbol : str)
  {
    returnedString += tolower(simbol);
  }
  return returnedString;
}


