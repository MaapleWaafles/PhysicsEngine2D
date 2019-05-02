#pragma once
//Included Vector4 to use its properties
#include "Vector4.h"
class Matrix4
{
public:
	// Creating a union to allocate one large amount of memory
	union {
		//Struct is held within the union axis array of 4 x points, 4 y points, 4 z points and 4 w points
		struct
		{
			//axis array holding the points
			float axis[16];
		};
		//Vector4 Type axis array holding 3D Points
		Vector4 axisV4[4];
	};

	//Matrix4 Constructor
	Matrix4();
	//Matrix4 Copy Constructor Holding the x, y and z positions to be passed into 
	Matrix4(float ax, float ay, float az, float aw, float bx, float by, float bz, float bw, float cx, float cy, float cz, float cw, float dx, float dy, float dz, float dw);
	//Matrix4 Copy Constructor that references back of Matrix4 type
	Matrix4(const Matrix4& other);
	//Matrix4 Deconstructor
	~Matrix4();

	//Matrix4 Functions that holds the identity Matrix, Transformation Matrix, Transpose of the Matrix, Matrix by Matrix Function and Vector4 = Vector4 Type
	Matrix4 Identity();
	Matrix4 Transpose();
	Matrix4& operator = (const Matrix4& m_matrix);
	Matrix4 operator *(const Matrix4& a_matrix) const;
	Vector4 operator *(const Vector4& a_vector) const;
	
	//Matrix4 Operators for Finding the index within an array and an explicit operator which uses constructor with single parameter
	//setRotate Functions for X, Y and Z and Rotate for X, Y and Z
	Vector4& operator [] (int index);
	explicit operator float* ();
	void setRotateX(float radians);
	void setRotateY(float radians);
	void setRotateZ(float radians);
	void rotateX(float radians);
	void rotateY(float radians);
	void rotateZ(float radians);
};











































