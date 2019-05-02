#pragma once
//Included Matrix2 to use its properties
#include "Vector2.h"
class Matrix2
{
public:
	// Creating a union to allocate one large amount of memory
	union {
		//Struct is held within the union axis array of 2 x points and 2 y points
		struct 
		{
			//axis array holding the points
			float axis[4];
		};
	};

	//Matrix2 Constructor
	Matrix2();
	//Matrix2 Copy Constructor Holding the x and y positions to be passed into 
	Matrix2(float ax, float ay, float bx, float by);
	//Matrix2 Copy Constructor that references back of Matrix2 type
	Matrix2(const Matrix2& other);
	//Matrix2 Deconstructor
	~Matrix2();

	//Matrix2 Functions that holds the identity Matrix, Transformation Matrix, Transpose of the Matrix, and Matrix by Matrix Function
	Matrix2 Identity();
	Matrix2 Transpose();
	Matrix2 operator *(const Matrix2& a_matrix) const;
	Vector2 operator *(const Vector2& a_vector) const;

	//Matrix2 Operators for Finding the index within an array and an explicit operator which uses constructor with single parameter
	//And Rotatation Setting of the 4 points
	float operator [] (int index);
	explicit operator float* ();
	void setRotate(float radians);
};

