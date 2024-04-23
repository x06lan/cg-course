#include <math.h>
void translateMatrix(float x, float y, float z, float *m)
{
    float temp[16] = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        x, y, z, 1};
    for (int i = 0; i < 16; i++)
    {
        m[i] = temp[i];
    }
}

void rotateX(float x, float *m)
{
    float temp[16] = {
        1, 0, 0, 0,
        0, static_cast<float>(cos(x)), static_cast<float>(-sin(x)), 0,
        0, static_cast<float>(sin(x)), static_cast<float>(cos(x)), 0,
        0, 0, 0, 1};
    for (int i = 0; i < 16; i++)
    {
        m[i] = temp[i];
    }
}

void rotateY(float y, float *m)
{
    float temp[16] = {
        static_cast<float>(cos(y)), 0, static_cast<float>(sin(y)), 0,
        0, 1, 0, 0,
        static_cast<float>(-sin(y)), 0, static_cast<float>(cos(y)), 0,
        0, 0, 0, 1};
    for (int i = 0; i < 16; i++)
    {
        m[i] = temp[i];
    }
}

void rotateZ(float z, float *m)
{
    float temp[16] = {
        static_cast<float>(cos(z)), static_cast<float>(-sin(z)), 0, 0,
        static_cast<float>(sin(z)), static_cast<float>(cos(z)), 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1};
    for (int i = 0; i < 16; i++)
    {
        m[i] = temp[i];
    }
}