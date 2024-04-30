#include <math.h>
struct Vector2d
{
    float x = 0.0;
    float y = 0.0;
};
float clamp(float x, float a, float b)
{
    return x < a ? a : (x > b ? b : x);
}
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

void ScaleMatrix(float x, float y, float z, float *m)
{
    float temp[16] = {
        x, 0, 0, 0,
        0, y, 0, 0,
        0, 0, z, 0,
        0, 0, 0, 1};
    for (int i = 0; i < 16; i++)
    {
        m[i] = temp[i];
    }
}
float getDistance(Vector2d point, Vector2d line1, Vector2d line2)
{
    // float a = point.x - line1.x;
    // float b = point.y - line1.y;
    float px = line2.x - line1.x;
    float py = line2.y - line1.y;

    float lenSq = px * px + py * py;
    float u = ((point.x - line1.x) * px + (point.y - line1.y) * py) / (lenSq);
    if (u > 1)
    {
        u = 1;
    }
    else if (u < 0)
    {
        u = 0;
    }
    float x = line1.x + u * px;
    float y = line1.y + u * py;

    float dx = x - point.x;
    float dy = y - point.y;
    double dist = sqrt(dx * dx + dy * dy);
    return dist;
}