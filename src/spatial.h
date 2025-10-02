#ifndef TFS_SPATIAL_H
#define TFS_SPATIAL_H

#include <cmath>
#include <limits>

struct Vec2f
{
        float x;
        float y;

        Vec2f() : x(0.f), y(0.f) {}
        Vec2f(float xIn, float yIn) : x(xIn), y(yIn) {}

        Vec2f operator+(const Vec2f& other) const
        {
                return Vec2f(x + other.x, y + other.y);
        }

        Vec2f operator-(const Vec2f& other) const
        {
                return Vec2f(x - other.x, y - other.y);
        }

        Vec2f operator*(float scalar) const
        {
                return Vec2f(x * scalar, y * scalar);
        }

        Vec2f& operator+=(const Vec2f& other)
        {
                x += other.x;
                y += other.y;
                return *this;
        }

        float length() const
        {
                return std::sqrt((x * x) + (y * y));
        }

        Vec2f normalized() const
        {
                const float len = length();
                if(len <= std::numeric_limits<float>::epsilon())
                        return Vec2f();

                const float invLen = 1.f / len;
                return Vec2f(x * invLen, y * invLen);
        }
};

struct AABB
{
        Vec2f min;
        Vec2f max;

        AABB() : min(), max() {}
        AABB(const Vec2f& minIn, const Vec2f& maxIn) : min(minIn), max(maxIn) {}

        static AABB fromCenterAndHalfExtents(const Vec2f& center, const Vec2f& halfExtents)
        {
                return AABB(Vec2f(center.x - halfExtents.x, center.y - halfExtents.y),
                        Vec2f(center.x + halfExtents.x, center.y + halfExtents.y));
        }

        bool intersects(const AABB& other) const
        {
                return !(other.min.x > max.x || other.max.x < min.x || other.min.y > max.y || other.max.y < min.y);
        }

        AABB translated(const Vec2f& offset) const
        {
                return AABB(Vec2f(min.x + offset.x, min.y + offset.y), Vec2f(max.x + offset.x, max.y + offset.y));
        }
};

#endif // TFS_SPATIAL_H
