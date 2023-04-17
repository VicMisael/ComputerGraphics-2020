#include "Matrix4x4.hpp"
#include <iostream>

void Matrix4x4::loadIdentity()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (i == j)
				mm44[i][j] = 1;
			else
				mm44[i][j] = 0;
		}
	}
}

Matrix4x4::Matrix4x4()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (i == j)
				mm44[i][j] = 1;
			else
				mm44[i][j] = 0;
		}
	}
}

Matrix4x4::Matrix4x4(const float _mm44[4][4])
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			mm44[i][j] = _mm44[i][j];
		}
	}
}

Matrix4x4 Matrix4x4::Transpose()
{
	float tempMatrix[4][4];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			tempMatrix[i][j] = mm44[j][i];
		}
	}
	return Matrix4x4(tempMatrix);
}

Matrix4x4 Matrix4x4::Transpose(const Matrix4x4& matrix)
{
	float tempMatrix[4][4];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			tempMatrix[i][j] = matrix.mm44[j][i];
		}
	}
	return Matrix4x4(tempMatrix);
}

//Returns the same matrix if not invertible
Matrix4x4 Matrix4x4::Inverse()
{
	float inverted[4][4];
	const float adj2323 = mm44[2][2] * mm44[3][3] - mm44[2][3] * mm44[3][2];
	const float adj1323 = mm44[2][1] * mm44[3][3] - mm44[2][3] * mm44[3][1];
	const float adj1223 = mm44[2][1] * mm44[3][2] - mm44[2][2] * mm44[3][1];
	const float adj0323 = mm44[2][0] * mm44[3][3] - mm44[2][3] * mm44[3][0];
	const float adj0223 = mm44[2][0] * mm44[3][2] - mm44[2][2] * mm44[3][0];
	const float adj0123 = mm44[2][0] * mm44[3][1] - mm44[2][1] * mm44[3][0];
	const float adj2313 = mm44[1][2] * mm44[3][3] - mm44[1][3] * mm44[3][2];
	const float adj1313 = mm44[1][1] * mm44[3][3] - mm44[1][3] * mm44[3][1];
	const float adj1213 = mm44[1][1] * mm44[3][2] - mm44[1][2] * mm44[3][1];
	const float adj2312 = mm44[1][2] * mm44[2][3] - mm44[1][3] * mm44[2][2];
	const float adj1312 = mm44[1][1] * mm44[2][3] - mm44[1][3] * mm44[2][1];
	const float adj1212 = mm44[1][1] * mm44[2][2] - mm44[1][2] * mm44[2][1];
	const float adj0313 = mm44[1][0] * mm44[3][3] - mm44[1][3] * mm44[3][0];
	const float adj0213 = mm44[1][0] * mm44[3][2] - mm44[1][2] * mm44[3][0];
	const float adj0312 = mm44[1][0] * mm44[2][3] - mm44[1][3] * mm44[2][0];
	const float adj0212 = mm44[1][0] * mm44[2][2] - mm44[1][2] * mm44[2][0];
	const float adj0113 = mm44[1][0] * mm44[3][1] - mm44[1][1] * mm44[3][0];
	const float adj0112 = mm44[1][0] * mm44[2][1] - mm44[1][1] * mm44[2][0];

	float det = mm44[0][0] * (mm44[1][1] * adj2323 - mm44[1][2] * adj1323 + mm44[1][3] * adj1223)
		- mm44[0][1] * (mm44[1][0] * adj2323 - mm44[1][2] * adj0323 + mm44[1][3] * adj0223)
		+ mm44[0][2] * (mm44[1][0] * adj1323 - mm44[1][1] * adj0323 + mm44[1][3] * adj0123)
		- mm44[0][3] * (mm44[1][0] * adj1223 - mm44[1][1] * adj0223 + mm44[1][2] * adj0123);
	det = 1 / det;

	inverted[0][0] = det * (mm44[1][1] * adj2323 - mm44[1][2] * adj1323 + mm44[1][3] * adj1223);
	inverted[0][1] = det * -(mm44[0][1] * adj2323 - mm44[0][2] * adj1323 + mm44[0][3] * adj1223);
	inverted[0][2] = det * (mm44[0][1] * adj2313 - mm44[0][2] * adj1313 + mm44[0][3] * adj1213);
	inverted[0][3] = det * -(mm44[0][1] * adj2312 - mm44[0][2] * adj1312 + mm44[0][3] * adj1212);
	inverted[1][0] = det * -(mm44[1][0] * adj2323 - mm44[1][2] * adj0323 + mm44[1][3] * adj0223);
	inverted[1][1] = det * (mm44[0][0] * adj2323 - mm44[0][2] * adj0323 + mm44[0][3] * adj0223);
	inverted[1][2] = det * -(mm44[0][0] * adj2313 - mm44[0][2] * adj0313 + mm44[0][3] * adj0213);
	inverted[1][3] = det * (mm44[0][0] * adj2312 - mm44[0][2] * adj0312 + mm44[0][3] * adj0212);
	inverted[2][0] = det * (mm44[1][0] * adj1323 - mm44[1][1] * adj0323 + mm44[1][3] * adj0123);
	inverted[2][1] = det * -(mm44[0][0] * adj1323 - mm44[0][1] * adj0323 + mm44[0][3] * adj0123);
	inverted[2][2] = det * (mm44[0][0] * adj1313 - mm44[0][1] * adj0313 + mm44[0][3] * adj0113);
	inverted[2][3] = det * -(mm44[0][0] * adj1312 - mm44[0][1] * adj0312 + mm44[0][3] * adj0112);
	inverted[3][0] = det * -(mm44[1][0] * adj1223 - mm44[1][1] * adj0223 + mm44[1][2] * adj0123);
	inverted[3][1] = det * (mm44[0][0] * adj1223 - mm44[0][1] * adj0223 + mm44[0][2] * adj0123);
	inverted[3][2] = det * -(mm44[0][0] * adj1213 - mm44[0][1] * adj0213 + mm44[0][2] * adj0113);
	inverted[3][3] = det * (mm44[0][0] * adj1212 - mm44[0][1] * adj0212 + mm44[0][2] * adj0112);

	return Matrix4x4(inverted);
	/*return inverse(mm44, inverted) ? Matrix4x4(inverted) : Matrix4x4(mm44);*/
}

float Matrix4x4::Determinant()
{
	float adj2323 = mm44[2][2] * mm44[3][3] - mm44[2][3] * mm44[3][2];
	float adj1323 = mm44[2][1] * mm44[3][3] - mm44[2][3] * mm44[3][1];
	float adj1223 = mm44[2][1] * mm44[3][2] - mm44[2][2] * mm44[3][1];
	float adj0323 = mm44[2][0] * mm44[3][3] - mm44[2][3] * mm44[3][0];
	float adj0223 = mm44[2][0] * mm44[3][2] - mm44[2][2] * mm44[3][0];
	float adj0123 = mm44[2][0] * mm44[3][1] - mm44[2][1] * mm44[3][0];


	return (mm44[0][0] * (mm44[1][1] * adj2323 - mm44[1][2] * adj1323 + mm44[1][3] * adj1223)
		- mm44[0][1] * (mm44[1][0] * adj2323 - mm44[1][2] * adj0323 + mm44[1][3] * adj0223)
		+ mm44[0][2] * (mm44[1][0] * adj1323 - mm44[1][1] * adj0323 + mm44[1][3] * adj0123)
		- mm44[0][3] * (mm44[1][0] * adj1223 - mm44[1][1] * adj0223 + mm44[1][2] * adj0123));
}

void Matrix4x4::ConcatTransformation(const float _mm[4][4])
{
	float temp[4][4];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			float num = 0;
			for (int k = 0; k < 4; k++)
			{
				num += _mm[i][k] * mm44[k][j];
			}

			temp[i][j] = num;
		}
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			mm44[i][j] = temp[i][j];
		}
	}
}

void Matrix4x4::ConcatTransformation(const Matrix4x4& matrix44)
{
	ConcatTransformation(matrix44.mm44);
}

void Matrix4x4::ConcatRotateX(float angle)
{
	float rot[4][4] = {
		{1, 0, 0, 0},
		{0, cos(angle), sin(angle), 0},
		{0, -sin(angle), cos(angle), 0},
		{0, 0, 0, 1}
	};
	this->ConcatTransformation(rot);
}

void Matrix4x4::ConcatRotateY(float angle)
{
	float rot[4][4] = {
		{cos(angle), 0, -sin(angle), 0},
		{0, 1, 0, 0},
		{sin(angle), 0, cos(angle), 0},
		{0, 0, 0, 1}
	};
	this->ConcatTransformation(rot);
}

void Matrix4x4::ConcatRotateZ(float angle)
{
	float rot[4][4] = {
		{cos(angle), -sin(angle), 0, 0},
		{sin(angle), cos(angle), 0, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 1}
	};
	this->ConcatTransformation(rot);
}

void Matrix4x4::ConcatTranslate(float tx, float ty, float tz)
{
	float translateMatrix[4][4] = {
		{1, 0, 0, tx},
		{0, 1, 0, ty},
		{0, 0, 1, tz},
		{0, 0, 0, 1},
	};
	this->ConcatTransformation(translateMatrix);
}

void Matrix4x4::ConcatScale(float x)
{
	float scaleMatrix[4][4] = {
		{x, 0, 0, 0},
		{0, x, 0, 0},
		{0, 0, x, 0},
		{0, 0, 0, 1},
	};
	this->ConcatTransformation(scaleMatrix);
}

void Matrix4x4::ConcatScale(float x, float y, float z)
{
	float scaleMatrix[4][4] = {
		{x, 0, 0, 0},
		{0, y, 0, 0},
		{0, 0, z, 0},
		{0, 0, 0, 1},
	};
	this->ConcatTransformation(scaleMatrix);
}

void Matrix4x4::ConcatShearx(float Shy, float Shz)
{
	float shearMatrix[4][4] = {
		{1, 0, 0, 0},
		{Shy, 1, 0, 0},
		{Shz, 0, 1, 0},
		{0, 0, 0, 1},
	};
	this->ConcatTransformation(shearMatrix);
}

void Matrix4x4::ConcatSheary(float Shx, float Shz)
{
	float shearMatrix[4][4] = {
		{1, Shx, 0, 0},
		{0, 1, 0, 0},
		{0, Shz, 1, 0},
		{0, 0, 0, 1},
	};
	this->ConcatTransformation(shearMatrix);
}

void Matrix4x4::ConcatShearz(float Shx, float Shy)
{
	float shearMatrix[4][4] = {
		{1, 0, Shx, 0},
		{0, 1, Shy, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 1},
	};
	this->ConcatTransformation(shearMatrix);
}

void Matrix4x4::ConcatReflect(bool xS, bool yS, bool zS)
{
	float x = xS ? -1 : 1;
	float y = yS ? -1 : 1;
	float z = zS ? -1 : 1;
	float reflectMatrix[4][4] = {
		{x, 0, 0, 0},
		{0, y, 0, 0},
		{0, 0, z, 0},
		{0, 0, 0, 1},
	};
	this->ConcatTransformation(reflectMatrix);
}


void Matrix4x4::printMatrix()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			std::cout << mm44[i][j] << " ";
		}
		std::cout << std::endl;
	}
}
