#pragma once
#include "Vector.h"
#include <cmath>
#include <Windows.h>
#define pi 3.141592653589793

class Figure
{
  static constexpr double maxSpeed = 100;
  Vector centre;
  Vector orientation;
  double radius;
  double ribs;
  Vector Speed;
  //Vector acceleration;
public:
  Figure();
  Figure(const Vector& c, const Vector& o, double r, double ri, const Vector& s);
  Figure(const Figure& f);
  Figure& operator=(const Figure f);
  void Draw(HDC hdc, RECT rect);
  void rotate(double corner);
  void addSpeed(const Vector& s) { Speed += s; };
  Vector GetSpeed() { return Speed; };
  void move(Vector v) { centre += v; };
  void CheckBorders(RECT rect);
  void SlowDown(double value);
  void SpeedUp();
};