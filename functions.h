#pragma once
#include "WinButt.h"
#include <fstream>
#include <GL/glut.h> 
#include <iostream>
#include <iterator>
#include <sstream>

void MenuCreating(ifstream& inputFile);

//Считывая файл, устанавливает положение и размер окна, в котором располагаются как главное меню,
//  так и подменю, а также цвет и название главного меню.
void MainWinInit(ifstream& inputFile); 

void addButton(ifstream& inputFile);

void addSubWindow(ifstream& inputFile);

void EndWork(void);

void Display(void);

void mouse(int button, int state, int x, int y);

void motion(int x, int y);

string ToLower(const string& str);
