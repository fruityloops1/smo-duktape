#include <types.h>

smo::Vector3::Vector3(f32 x, f32 y, f32 z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

smo::Quat::Quat(f32 x, f32 y, f32 z, f32 w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

smo::Vector3::Vector3() {}
smo::Quat::Quat() {}