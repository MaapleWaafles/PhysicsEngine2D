#pragma once
class Vector2
{
public:
	//Creating a union to allocate one large amount of memory
	union 
	{
		//Struct is held within the union holding the floats x and y
		struct 
		{
			//X and Y positions
			float x;
			float y;
		};

		//Creates an array of float type with 2 integers
		float data[2];
	};

	//Vector2 Constructor
	Vector2();
	//Vector2 Copy Constructor Holding the x and y positions to be passed into 
	Vector2(float x, float y);
	//Vector2 Deconstructor
	~Vector2();

	//Vector2 Operators for Addition, Subtraction, Division, Multiplicaton and Equals
	Vector2 operator + (const Vector2& other) const;
	Vector2 operator - (const Vector2& other) const;
	Vector2 operator * (float scalar) const;
	Vector2 operator / (float scalar) const;
	Vector2 operator = (const Vector2& other);

	//Vector2 Operators for Homogeneus Matrices that adds each element to the other
	Vector2 operator += (const Vector2& other);
	Vector2 operator -= (const Vector2& other);
	Vector2 operator *= (float scalar);
	Vector2 operator /= (float scalar);

	//Vector2 Operator of type Friend that is defined outside the Classes Scope but has rights to all private and public members
	friend Vector2 operator * (float scalar, const Vector2& other);
	friend Vector2 operator / (float scalar, const Vector2& other);
	friend Vector2 operator - (float scalar, const Vector2& other);
	friend Vector2 operator + (float scalar, const Vector2& other);

	//Vector2 Functions that determine the length, width, sqrt of the Vector
	Vector2 normalise() const;
	void normalised();
	Vector2 cross(const Vector2& other) const;
	float magnitude() const;
	float dot(const Vector2& other) const;
	float distance(const Vector2& other) const;
	Vector2 RightHalfPerpendicular() const;
	Vector2 LeftHalfPerpendicular() const;
	
	//Vector2 Operators for Finding the index within an array and an explicit operator which uses constructor with single parameter 
	float operator [] (int index);
	explicit operator float* ();



};

  