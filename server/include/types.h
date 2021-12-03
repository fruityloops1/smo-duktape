#pragma once

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long u64;

typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
typedef signed long s64;

typedef float f32;
typedef double f64;

namespace smo
{
    struct Vector3
    {
        f32 x, y, z;
        Vector3(f32 x, f32 y, f32 z);
        Vector3();
    };

    struct Quat
    {
        f32 x, y, z, w;
        Quat(f32 x, f32 y, f32 z, f32 w);
        Quat();
    };
}