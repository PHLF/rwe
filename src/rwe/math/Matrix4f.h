#ifndef RWE_MATH_MATRIX4F_H
#define RWE_MATH_MATRIX4F_H

#include <rwe/math/Vector3f.h>

namespace rwe
{
    struct Matrix4f
    {
        static Matrix4f identity();
        static Matrix4f translation(const Vector3f& v);
        static Matrix4f scale(float size);
        static Matrix4f scale(const Vector3f& v);
        static Matrix4f shearXZ(float x, float z);
        static Matrix4f cabinetProjection(float x, float y);
        static Matrix4f orthographicProjection(float left, float right, float bottom, float top, float nearVal, float farVal);
        static Matrix4f inverseOrthographicProjection(float left, float right, float bottom, float top, float nearVal, float farVal);
        static Matrix4f rotationToAxes(const Vector3f& side, const Vector3f& up, const Vector3f& forward);

        /** Anti-clockwise rotation about the X axis. */
        static Matrix4f rotationX(float angle);
        /** Anti-clockwise rotation about the Y axis. */
        static Matrix4f rotationY(float angle);
        /** Anti-clockwise rotation about the Z axis. */
        static Matrix4f rotationZ(float angle);

        static Matrix4f rotationXYZ(const Vector3f& angles);

        static Matrix4f rotationZXY(const Vector3f& angles);

        /**
         * Elements are stored in column-major order,
         * i.e. the array is indexed E[(column * column_length) + row] or E[(x * height) + y].
         */
        float data[16];

        Matrix4f transposed() const;

        /**
         * Multiplies the upper-left 3x3 portion of this matrix by the given vector.
         */
        Vector3f mult3x3(const Vector3f& v) const;
    };

    Matrix4f operator*(const Matrix4f& a, const Matrix4f& b);

    /**
     * Multiplication of row vector a by matrix b.
     * It is implied that the vector contains a fourth component,
     * w, which is 1.
     * The last column of the matrix is ignored.
     */
    Vector3f operator*(const Vector3f& a, const Matrix4f& b);

    /**
     * Multiplication of matrix a by column vector b.
     * It is implied that the vector contains a fourth component,
     * w, which is 1.
     * The last row of the matrix is ignored.
     */
    Vector3f operator*(const Matrix4f& a, const Vector3f& b);
}

#endif
