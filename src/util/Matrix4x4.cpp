#include "Matrix4x4.hpp"
#include <iostream>

void  getCofactor(float A[4][4], float temp[4][4], int p, int q, int n)
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

float inline determinant(float A[4][4], int n)
{
    float D = 0; // Initialize result

    //  Base case : if matrix contains single element
    if (n == 1)
        return A[0][0];

    float temp[4][4]; // To store cofactors

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
void adjoint(float A[4][4], float adj[4][4])
{

    // temp is used to store cofactors of A[][]
    int sign = 1;
    float temp[4][4];

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            // Get cofactor of A[i][j]
            getCofactor(A, temp, i, j, 4);

            // sign of adj[j][i] positive if sum of row
            // and column indexes is even.
            sign = ((i + j) % 2 == 0) ? 1 : -1;

            // Interchanging rows and columns to get the
            // transpose of the cofactor matrix
            adj[j][i] = (sign) * (determinant(temp, 3));
        }
    }
}

// Function to calculate and store inverse, returns false if
// matrix is singular
float inverse(float A[4][4], float inverse[4][4])
{
    // Find determinant of A[][]
    float det = determinant(A, 4);
    if (det == 0)
    {
        return false;
    }

    float adj[4][4];
    adjoint(A, adj);

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            inverse[i][j] = adj[i][j] / det;

    return true;
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
Matrix4x4::Matrix4x4(float _mm44[4][4])
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
Matrix4x4 Matrix4x4::Transpose(const Matrix4x4 &matrix)
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
    return inverse(mm44, inverted) ? Matrix4x4(inverted) : Matrix4x4(mm44);
}
float Matrix4x4::Determinant()
{
    return determinant(mm44, 4);
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
void Matrix4x4::ConcatTransformation(const Matrix4x4 &matrix44)
{
    ConcatTransformation(matrix44.mm44);
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
