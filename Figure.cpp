#include "Figure.h"

Figure::Figure() : centre(0.0, 0.0), orientation(1.0, 0.0),
radius(25.0), ribs(6), Speed(0.0, 0.0) {};

Figure::Figure(const Vector& c, const Vector& o, double r, double ri, const Vector& s) :
  centre(c), orientation(o), radius(r), ribs(ri), Speed(s) {};

Figure::Figure(const Figure& f) :
  centre(f.centre), orientation(f.orientation), radius(f.radius), 
    ribs(f.ribs), Speed(f.Speed){};

Figure& Figure::operator=(const Figure f)
{
  centre = f.centre;
  orientation = f.orientation;
  radius = f.radius;
  ribs = f.ribs;
  Speed = f.Speed;
  return *this;
};

void Figure::Draw(HDC hdc, RECT rect)
{
  Vector top = radius * orientation;
  Vector TransCentre = centre.TranslateCoordinates(rect.right - rect.left, rect.bottom - rect.top);
  MoveToEx(hdc, TransCentre.getx() + int(top.getx()), TransCentre.gety() + int(top.gety()), NULL);
  for (int i = 0; i < ribs; i++)
  {
    top.rotate(pi * 2 / ribs);

    LineTo(hdc, TransCentre.getx() + int(top.getx()), TransCentre.gety() + int(top.gety()));
  }
}

void Figure::rotate(double corner)
{
  orientation.rotate(corner);
}

void Figure::CheckBorders(RECT rect)
{
  if (fabs(centre.getx()) + radius >= (rect.right - rect.left) / 2)
  {
    if (centre.getx() > 0)
      centre.setx((rect.right - rect.left) - centre.getx() - 2 *radius);
    else
      centre.setx(rect.left - rect.right - centre.getx() + 2 * radius);
    Speed *= Vector(-1, 1);
  }
  if (fabs(centre.gety()) + radius >= (rect.bottom - rect.top) / 2)
  {
    if (centre.gety() > 0)
      centre.sety((rect.bottom - rect.top) - centre.gety() - 2 * radius);
    else
      centre.sety(rect.top - rect.bottom- centre.gety() + 2 * radius);
    Speed *= Vector(1, -1);
  }
}

void Figure::SlowDown(double value)
{
  Speed *= (1 / 1.3);
  if (fabs(Speed.getx()) < value && fabs(Speed.gety()) < value)
  {
    Speed.setx(0);
    Speed.sety(0);
  }
}
void Figure::SpeedUp()
{
  if(fabs(Speed.getx()) < 2000 && fabs(Speed.gety()) < 2000)
    Speed *= (1.3);
}






