#include "shapes.h"

bool is_inside(const point& p, const rectangle& r)
{
  int Top = r.origin.y;
  int Bot = r.origin.y + r.height;
  int rightSide = r.origin.x + r.width; 
  int leftSide = r.origin.x;

  if (p.x >= leftSide && p.x <= rightSide)
    if (p.y >= Top && p.y <= Bot)
      return true;
  return false;
}

