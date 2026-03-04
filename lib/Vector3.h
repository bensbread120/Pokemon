#ifndef VECTOR3_H
#define VECTOR3_H

class Vector3 {

  public:
    int x;
    int y;
    int z;
    Vector3();
    Vector3(int x, int y, int z);
    void set(Vector3 other);
};

#endif