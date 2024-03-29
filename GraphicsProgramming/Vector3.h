#ifndef _VECTOR3_H_
#define _VECTOR3_H_

#include <math.h>

class Vector3 {
	
public:
	Vector3(float x = 0, float y = 0, float z = 0);
	
	Vector3 copy();

	static Vector3 zero() { return Vector3(0, 0, 0); };
	static Vector3 one() { return Vector3(1, 1, 1); };

	void set(float x, float y, float z);
	void setX(float x);
	void setY(float y);
	void setZ(float z);

	float getX();
	float getY();
	float getZ();

	void add(const Vector3& v1, float scale = 1.0);
	void subtract(const Vector3& v1, float scale = 1.0);
	void scale(float scale);
	Vector3 multiply(float scalar);

	float dot(const Vector3& v2);
	Vector3 cross(const Vector3& v2);

	void normalise();
	Vector3 normalised();
	float length();
	float lengthSquared();

	bool equals(const Vector3& v2, float epsilon);
	bool equals(const Vector3& v2);
	
	bool operator==(const Vector3& v3);

	Vector3 operator+(const Vector3& v2);
	Vector3 operator-(const Vector3& v2);

	Vector3& operator+=(const Vector3& v2);
	Vector3& operator-=(const Vector3& v2);

	bool containsValueLessThan(float epsilon);

	float x;
	float y;
	float z;

};

#endif