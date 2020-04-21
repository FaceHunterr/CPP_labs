#include "Vector.h"

Vector& Vector::operator=(const Vector& v)
{
  X = v.X;
  Y = v.Y;
  return *this;
}


Vector operator+(const Vector& v1, const Vector& v2)
{
  return Vector(v1.X + v2.X, v1.Y + v2.Y);
}

Vector operator-(const Vector& v1, const Vector& v2)
{
  return Vector(v1.X - v2.X, v1.Y - v2.Y);
}

Vector operator*(const Vector& v, double num)
{
  return Vector(v.X * num, v.Y * num);
}

Vector operator* (double num, const Vector v)
{
  return Vector(v.X * num, v.Y * num);
}

Vector operator*(const Vector& v1, const Vector& v2)
{
  return Vector(v1.X * v2.X, v1.Y * v2.Y);
}

Vector& Vector::operator+=(const Vector& v)
{
  X += v.X;
  Y += v.Y;
  return *this;
}

Vector& Vector::operator*= (Vector v)
{
  X *= v.X;
  Y *= v.Y;
  return *this;
}


Vector& Vector::operator-=(const Vector& v)
{
  X -= v.X;
  Y -= v.Y;
  return *this;
}


Vector& Vector::operator*=(double number)
{
  X *= number;
  Y *= number;
  return *this;
}

ostream& operator<<(ostream& output, const Vector& v)
{
  output << v.X << " " << v.Y << "\n";
  return output;
}

Vector Vector::getRotatedVector(double corner) const
{
  Vector temp;
  temp.X = X * cos(corner) - Y * sin(corner);
  temp.Y = X * sin(corner) + Y * cos(corner);
  return temp;
}

Vector& Vector::rotate(double corner)
{
  Vector temp;
  temp.X = X * cos(corner) - Y * sin(corner);
  temp.Y = X * sin(corner) + Y * cos(corner);
  *this = temp;
  return *this;
}

Vector Vector::TranslateCoordinates(double len, double high) const
{
  return Vector(X + len / 2, high / 2 - Y);
}


