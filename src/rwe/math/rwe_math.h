#ifndef RWE_MATH_RWE_MATH_H
#define RWE_MATH_RWE_MATH_H

#include <rwe/Point.h>
#include <rwe/math/Vector2f.h>

namespace rwe
{
    /**
     * Quantizes a value to the nearest multiple of the given interval.
     *
     * @param value The value to quantize.
     * @param interval The interval. Must be a positive (>0) number.
     * @return The quantized value.
     */
    float snapToInterval(float value, float interval);

    /**
     * Quantizes a value to the multiple of the given interval that is closest to zero.
     *
     * @param value The value to quantize.
     * @param interval The interval. Must be a positive (>0) number.
     * @return The quantized value.
     */
    float truncateToInterval(float value, float interval);

    float wrap(float min, float max, float value);

    int wrap(int min, int max, int value);

    /**
     * Returns true if a and b both have the same sign, ignoring zeroes.
     */
    bool sameSign(float a, float b);

    /**
     * Returns true if a, b and c all have the same sign, ignoring zeroes.
     */
    bool sameSign(float a, float b, float c);

    unsigned int roundUpToPowerOfTwo(unsigned int v);

    bool almostEquals(float a, float b, float delta);

    float distanceToRange(float min, float max, float pos);

    float distanceSquaredToRange(float min, float max, float pos);
}

#endif
