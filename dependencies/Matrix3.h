#pragma once
//Included Vector3 to use its properties
#include "Vector3.h"
class Matrix3
{
public:
	// Creating a union to allocate one large amount of memory
	union {		
		//Struct is held within the union axis array of 3 x points, 3 y points and 3 z points
		struct
		{
			//axis array holding the points
			Vector3 xAxis;
			Vector3 yAxis;
			union
			{
				Vector3 zAxis;
				Vector3 Translate;
			};
		};
		//Vector3 Type axis array holding 3D Points
		float axis[9];
		Vector3 axisV3[3];
	};

	//Matrix3 Constructor
	Matrix3();
	//Matrix3 Copy Constructor Holding the x, y and z positions to be passed into 
	Matrix3(float ax, float ay, float az, float bx, float by, float bz, float cx, float cy, float cz);
	//Matrix3 Copy Constructor that references back of Matrix3 type
	Matrix3(const Matrix3& other);
	//Matrix3 Deconstructor
	~Matrix3();

	//Matrix3 Functions that holds the identity Matrix, Transformation Matrix, Transpose of the Matrix, Matrix by Matrix Function and Vector3 = Vector3 Type
	Matrix3 Transpose();
	Matrix3& operator = (const Matrix3& m_matrix);
	Matrix3 operator *(const Matrix3& a_matrix) const;
	Vector3 operator *(const Vector3& a_vector) const;
	static const Matrix3 identity;

	//Matrix3 Operators for Finding the index within an array and an explicit operator which uses constructor with single parameter
	//setRotate Functions for X, Y and Z and Rotate for X, Y and Z
	Vector3& operator [] (int index);
	explicit operator float* ();
	void setScaled(float x, float y, float z);
	void scale(float x, float y, float z);
	void setRotateX(float radians);
	void setRotateY(float radians);
	void setRotateZ(float radians);
	void rotateX(float radians);
	void rotateY(float radians);
	void rotateZ(float radians);
	void translate(float x, float y);
};

