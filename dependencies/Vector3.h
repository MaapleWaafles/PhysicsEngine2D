#pragma once
class Vector3
{
public:
	//Creating a union to allocate one large amount of memory
	union
	{
		//Struct is held within the union holding the floats x y and z
		struct
		{
			//X, Y and Z positions
			float x;
			float y;
			float z;
		};
		//Creates an array of float type with 3 integers
		float data[3];
	};

	//Vector3 Constructor
	Vector3();
	//Vector3 Copy Constructor Holding the x, y and z positions to be passed into 
	Vector3(float x, float y, float z);
	//Vector3 Deconstructor
	~Vector3();

	//Vector3 Operators for Addition, Subtraction, Division, Multiplicaton and Equals
	Vector3 operator + (const Vector3& other) const;
	Vector3 operator - (const Vector3& other) const;
	Vector3 operator * (float scalar) const;
	Vector3 operator / (float scalar) const;

	//Vector3 Operators for Homogeneus Matrices that adds each element to the other
	Vector3 operator += (const Vector3& other);
	Vector3 operator -= (const Vector3& other);
	Vector3 operator *= (float scalar);
	Vector3 operator /= (float scalar);
	Vector3 operator = (const Vector3& other);


	//Vector3 Operator of type Friend that is defined outside the Classes Scope but has rights to all private and public members
	friend Vector3 operator * (float scalar, const Vector3& other);
	friend Vector3 operator / (float scalar, const Vector3& other);
	friend Vector3 operator - (float scalar, const Vector3& other);
	friend Vector3 operator + (float scalar, const Vector3& other);

	friend Vector3 operator *= (float scalar, Vector3& other);
	friend Vector3 operator /= (float scalar, Vector3& other);
	friend Vector3 operator -= (float scalar, Vector3& other);
	friend Vector3 operator += (Vector3& other, float scalar);

	//Vector3 Functions that determine the length, width, sqrt of the Vector
	Vector3 cross(const Vector3& other) const;
	void normalise();
	float magnitude() const;
	float distance(const Vector3& other) const;
	float dot(const Vector3& other) const;

	//Vector3 Operators for Finding the index within an array and an explicit operator which uses constructor with single parameter 
	float operator [] (int index);
	explicit operator float* ();
};
