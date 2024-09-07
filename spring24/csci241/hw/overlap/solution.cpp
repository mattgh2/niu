#include "shapes.h"

bool overlap(const rectangle& r1, const rectangle& r2)
{
  // rectangle 1  
  int x1 = r1.origin.x;  // left side x
  int x2 = r1.origin.x + r1.width; // right side x
  int y1 = r1.origin.y; // top y
  int y2 = r1.origin.y + r1.height; // bottom y

  // rectangle 2 
  int x3 = r2.origin.x; // left side x
  int x4 = r2.origin.x + r2.width; // right side x
  int y3 = r2.origin.y; // top y
  int y4 = r2.origin.y + r2.height; // bottom y

  if (x2 < x3 || x4 < x1)
    return false;
  if (y2 < y3 || y4 < y1)
    return false;
  return true;
}

// check for overlap by comparring the sides and top/bottom
// 
// FOR SIDES
// if the right side of r1 is less than the left side of r2
// if the right side of r2 is less than the left side of r1
// Then there cannot be overlap
// FOR TOP/BOTTOM
// If the bottom of r1 is less than the top of r2
// If the bottom of r2 is less than the top of r1
// no overlap

