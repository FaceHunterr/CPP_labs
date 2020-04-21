#pragma once
#include <iostream>

using namespace std;

class Vector
{
  double X;
  double Y;
public:
  explicit Vector(double x = 0.0, double y = 0.0) : X(x), Y(y) {};
  Vector(const Vector& v) : X(v.X), Y(v.Y) {};
  Vector& operator= (const Vector& v);
  Vector& operator+= (const Vector& v);
  Vector& operator-= (const Vector& v);
  Vector& operator*= (double number);
  Vector& operator*= (Vector v);
  friend Vector operator* (double number, const Vector v);
  double getx() const { return X; };
  double gety() const { return Y; };
  void setx(double x) { X = x; };
  void sety(double y) { Y = y; };
  friend ostream& operator<<(ostream& output, const Vector& v);
  friend Vector operator*(const Vector& v, double num);
  friend Vector operator*(const Vector& v1, const Vector& v2); //скалярное произведение векторов
  friend Vector operator+(const Vector& v1, const Vector& v2);
  friend Vector operator-(const Vector& v1, const Vector& v2);

  Vector getRotatedVector(double corner) const;
  Vector& rotate(double corner);
  Vector TranslateCoordinates(double len, double high) const; //переводит координаты из декартовой системы в экранную

};


