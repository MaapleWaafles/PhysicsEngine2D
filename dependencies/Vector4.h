#pragma once
class Vector4
{
public:
	//Creating a union to allocate one large amount of memory
	union
	{
		//Struct is held within the union holding the floats x y z and w
		struct
		{
			//X, Y, Z and W positions
			float x;
			float y;
			float z;
			float w;
		};
		//Creates an array of float type with 4 integers
		float data[4];
	};

	//Vector4 Constructor
	Vector4();
	//Vector4 Copy Constructor Holding the x and y positions to be passed into 
	Vector4(float x, float y, float z, float w);
	//Vector4 Constructor
	~Vector4();

	//Vector4 Operators for Addition, Subtraction, Division, Multiplicaton and Equals
	Vector4 operator + (const Vector4& other) const;
	Vector4 operator - (const Vector4& other) const;
	Vector4 operator * (float scalar) const;
	Vector4 operator / (float scalar) const;

	//Vector4 Operators for Homogeneus Matrices that adds each element to the other
	Vector4 operator += (const Vector4& other);
	Vector4 operator -= (const Vector4& other);
	Vector4 operator *= (float scalar);
	Vector4 operator /= (float scalar);
	Vector4 operator = (const Vector4& other);

	//Vector4 Operator of type Friend that is defined outside the Classes Scope but has rights to all private and public members
	friend Vector4 operator * (float scalar, const Vector4& other);
	friend Vector4 operator / (float scalar, const Vector4& other);
	friend Vector4 operator - (float scalar, const Vector4& other);
	friend Vector4 operator + (float scalar, const Vector4& other);

	//Vector4 Functions that determine the length, width, sqrt of the Vector
	Vector4 cross(const Vector4& other) const;
	void normalise();
	float magnitude() const;
	float distance(const Vector4& other) const;
	float dot(const Vector4& other) const;

	//Vector4 Operators for Finding the index within an array and an explicit operator which uses constructor with single parameter 
	float operator [] (int index);
	explicit operator float* ();
};
