#include "Matrix4x4.hpp"
#include <iostream>

void getCofactor(float A[4][4], float temp[4][4], int p, int q, int n)
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

float determinant(float A[4][4], int n)
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

float Matrix4x4::Determinant()
{
    // for (int i = 0; i < 4; i++)
    // {
    //     for (int j = 0; j < 4; j++)
    //     {
    //         std::cout <<" "<<mm44[i][j];
    //     }
    //     std::cout << std::endl;
    // }
    return determinant(mm44, 4);
}
