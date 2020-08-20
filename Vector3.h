#pragma once

#pragma pack (push, 1)

template <typename Type>
union Vector3 

{

	struct { Type x, y, z; };

	Type data[3];

	Vector3 (Type x_, Type y_, Type z_) :

		x (x_),
		y (y_),
		z (z_)

	{}

	Vector3 & operator += (const Vector3 & that)

	{
	
		x += that.x;
		y += that.y;
		z += that.z;

		return *this;

	}

	Vector3 & operator -= (const Vector3 & that)

	{
	
		x -= that.x;
		y -= that.y;
		z -= that.z;

		return *this;

	}

	Vector3 & operator *= (const Vector3 & that)

	{
	
		x *= that.x;
		y *= that.y;
		z *= that.z;

		return *this;

	}

	Vector3 & operator /= (const Vector3 & that)

	{
	
		x /= that.x;
		y /= that.y;
		z /= that.z;

		return *this;

	}

};

typedef Vector3 <int>    Vector3i;
typedef Vector3 <double> Vector3d;

#pragma pack (pop)