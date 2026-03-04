#include "Vector3.h"

Vector3::Vector3() {
  this->x = 0;
  this->y = 0;
  this->z = 0;
};

Vector3::Vector3(int x, int y, int z) {
  this->x = x;
  this->y = y;
  this->z = z;
};

void Vector3::set(Vector3 other) {
  this->x = other.x;
  this->y = other.y;
  this->z = other.z;
};
