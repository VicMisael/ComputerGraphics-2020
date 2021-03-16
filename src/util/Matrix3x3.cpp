#include "Matrix3x3.hpp"
#include <iostream>
void getCofactor(float A[3][3], float temp[3][3], int p, int q, int n)
{
    int i = 0, j = 0;

    // Looping for each element of the matrix
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            //  Copying into temporary matrix only those element
            //  which are not in given row and column
            if (row != p && col != q)
            {
                temp[i][j++] = A[row][col];

                // Row is filled, so increase row index and
                // reset col index
                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

float inline determinant(float A[3][3], int n)
{
    float D = 0; // Initialize result

    //  Base case : if matrix contains single element
    if (n == 1)
        return A[0][0];

    float temp[3][3]; // To store cofactors

    int sign = 1; // To store sign multiplier

    // Iterate for each element of first row
    for (int f = 0; f < n; f++)
    {
        // Getting Cofactor of A[0][f]
        getCofactor(A, temp, 0, f, n);
        D += sign * A[0][f] * determinant(temp, n - 1);

        // terms are to be added with alternate sign
        sign = -sign;
    }

    return D;
}

// Function to get adjoint of A[N][N] in adj[N][N].
void adjoint(float A[3][3], float adj[3][3])
{

    // temp is used to store cofactors of A[][]
    int sign = 1;
    float temp[3][3];

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            // Get cofactor of A[i][j]
            getCofactor(A, temp, i, j, 3);

            // sign of adj[j][i] positive if sum of row
            // and column indexes is even.
            sign = ((i + j) % 2 == 0) ? 1 : -1;

            // Interchanging rows and columns to get the
            // transpose of the cofactor matrix
            adj[j][i] = (sign) * (determinant(temp, 2));
        }
    }
}

// Function to calculate and store inverse, returns false if
// matrix is singular
float inverse(float A[3][3], float inverse[3][3])
{
    // Find determinant of A[][]
    float det = determinant(A, 3);
    if (det == 0)
    {
        return false;
    }

    float adj[3][3];
    adjoint(A, adj);

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            inverse[i][j] = adj[i][j] / det;

    return true;
}

Matrix3x3::Matrix3x3()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (i == j)
                mm33[i][j] = 1;
            else
                mm33[i][j] = 0;
        }
    }
}

Matrix3x3::Matrix3x3(float _mm33[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            mm33[i][j] = _mm33[i][j];
        }
    }
}

Matrix3x3 Matrix3x3::Transpose()
{
    float tempMatrix[3][3];
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            tempMatrix[i][j] = mm33[j][i];
        }
    }
    return Matrix3x3(tempMatrix);
}

Matrix3x3 Matrix3x3::Transpose(const Matrix3x3 &matrix)
{
    float tempMatrix[3][3];
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            tempMatrix[i][j] = matrix.mm33[j][i];
        }
    }
    return Matrix3x3(tempMatrix);
}

void Matrix3x3::ConcatTransformation(const float _mm[3][3])
{
    float temp[3][3];
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            float num = 0;
            for (int k = 0; k < 3; k++)
            {
                num += _mm[i][k] * mm33[k][j];
            }

            temp[i][j] = num;
        }
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            mm33[i][j] = temp[i][j];
        }
    }
}
void Matrix3x3::ConcatTransformation(const Matrix3x3 &matrix)
{
    ConcatTransformation(matrix.mm33);
}
Matrix3x3 Matrix3x3::Inverse()
{
    float inverted[3][3];
    return inverse(mm33, inverted) ? Matrix3x3(inverted) : Matrix3x3(mm33);
}

float Matrix3x3::Determinant()
{
    return determinant(mm33, 3);
}
void Matrix3x3::ConcatRotateX(float angle)
{
    float rot[3][3] = {{1, 0, 0},
                       {0, cos(angle), sin(angle)},
                       {0, -sin(angle), cos(angle)}};
    this->ConcatTransformation(rot);
}
void Matrix3x3::ConcatRotateY(float angle)
{
    float rot[3][3] = {{cos(angle), 0, -sin(angle)},
                       {0, 1, 0},
                       {sin(angle), 0, cos(angle)}};
    this->ConcatTransformation(rot);
}
void Matrix3x3::ConcatRotateZ(float angle)
{
    float rot[3][3] = {{cos(angle), -sin(angle), 0},
                       {sin(angle), cos(angle), 0},
                       {0, 0, 1}};
    this->ConcatTransformation(rot);
}
void Matrix3x3::printMatrix()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            std::cout << mm33[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
