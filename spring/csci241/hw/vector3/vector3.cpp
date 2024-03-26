#include "vector3.h"


vector3::vector3(double x, double y, double z) {
  this-> x = x;
  this-> y = y;
  this-> z = z;
}
std::ostream& operator<<(std::ostream& os, const vector3& obj) {
  os << "(" << obj.x << ", " << obj.y << ", " << obj.z << ")";
  return os;
}

vector3 vector3::operator+(const vector3& obj) const {
  vector3 tempobj;

  tempobj.x = this->x + obj.x;
  tempobj.y = this-> y + obj.y; 
  tempobj.z = this-> z + obj.z;

  return tempobj;
}

vector3 vector3::operator-(const vector3& obj) const {
  vector3 tempobj;

  tempobj.x = this->x - obj.x;
  tempobj.y = this-> y - obj.y; 
  tempobj.z = this-> z - obj.z;

  return tempobj;
}

double vector3::operator*(const vector3& obj) const {
  double scalar = 0;

  scalar += this-> x * obj.x;
  scalar += this-> y * obj.y;
  scalar += this-> z * obj.z;

  return scalar;
}
vector3 vector3::operator*(double scalar) const {
  vector3 tempobj; 

  tempobj.x = this-> x * scalar;
  tempobj.y = this-> y * scalar;
  tempobj.z = this-> z * scalar;

  return tempobj;
}
vector3 operator*(double scalar, const vector3& obj) {
  vector3 tempobj;
  
  tempobj.x = scalar * obj.x;
  tempobj.y = scalar * obj.y;
  tempobj.z = scalar * obj.z;
  return tempobj;
}
bool vector3::operator==(const vector3& obj) const {

  if (this-> x != obj.x) 
    return false;

  if (this-> y != obj.y) 
    return false;

  if (this-> z != obj.z) 
    return false;

  return true;
}

double vector3::operator[](size_t pos) const {

  switch (pos) {
    case 0:
      return this-> x;
    case 1:
      return this-> y;
    case 2:
      return this-> z;
    default:
      return 0.0;
  }
}

double& vector3::operator[](size_t pos) {
  switch (pos) {
    case 0:
      return this-> x;
    case 1:
      return this-> y;
    case 2:
      return this-> z;
  }
  return this->x;
}






