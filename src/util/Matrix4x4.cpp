#include "Matrix4x4.hpp"
#include <iostream>
// void getCofactor(float A[4][4], float temp[4][4], int p, int q, int n)
// {
//     int i = 0, j = 0;

//     // Looping for each element of the matrix
//     for (int row = 0; row < n; row++)
//     {
//         for (int col = 0; col < n; col++)
//         {
//             //  Copying into temporary matrix only those element
//             //  which are not in given row and column
//             if (row != p && col != q)
//             {
//                 temp[i][j++] = A[row][col];

//                 // Row is filled, so increase row index and
//                 // reset col index
//                 if (j == n - 1)
//                 {
//                     j = 0;
//                     i++;
//                 }
//             }
//         }
//     }
// }

// float inline determinant(float A[4][4], int n)
// {
//     float D = 0; // Initialize result

//     //  Base case : if matrix contains single element
//     if (n == 1)
//         return A[0][0];

//     float temp[4][4]; // To store cofactors

//     int sign = 1; // To store sign multiplier

//     // Iterate for each element of first row
//     for (int f = 0; f < n; f++)
//     {
//         // Getting Cofactor of A[0][f]
//         getCofactor(A, temp, 0, f, n);
//         D += sign * A[0][f] * determinant(temp, n - 1);

//         // terms are to be added with alternate sign
//         sign = -sign;
//     }

//     return D;
// }

// // Function to get adjoint of A[N][N] in adj[N][N].
// void adjoint(float A[4][4], float adj[4][4])
// {

//     // temp is used to store cofactors of A[][]
//     int sign = 1;
//     float temp[4][4];

//     for (int i = 0; i < 4; i++)
//     {
//         for (int j = 0; j < 4; j++)
//         {
//             // Get cofactor of A[i][j]
//             getCofactor(A, temp, i, j, 4);

//             // sign of adj[j][i] positive if sum of row
//             // and column indexes is even.
//             sign = ((i + j) % 2 == 0) ? 1 : -1;

//             // Interchanging rows and columns to get the
//             // transpose of the cofactor matrix
//             adj[j][i] = (sign) * (determinant(temp, 3));
//         }
//     }
// }

// Function to calculate and store inverse, returns false if
// matrix is singular
// float inverse(float A[4][4], float inverse[4][4])
// {
//     // Find determinant of A[][]
//     float det = determinant(A, 4);
//     if (det == 0)
//     {
//         return false;
//     }

//     float adj[4][4];
//     adjoint(A, adj);

//     for (int i = 0; i < 4; i++)
//         for (int j = 0; j < 4; j++)
//             inverse[i][j] = adj[i][j] / det;

//     return true;
// }
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
    float adj2323 = mm44[2][2] * mm44[3][3] - mm44[2][3] * mm44[3][2];
    float adj1323 = mm44[2][1] * mm44[3][3] - mm44[2][3] * mm44[3][1];
    float adj1223 = mm44[2][1] * mm44[3][2] - mm44[2][2] * mm44[3][1];
    float adj0323 = mm44[2][0] * mm44[3][3] - mm44[2][3] * mm44[3][0];
    float adj0223 = mm44[2][0] * mm44[3][2] - mm44[2][2] * mm44[3][0];
    float adj0123 = mm44[2][0] * mm44[3][1] - mm44[2][1] * mm44[3][0];
    float adj2313 = mm44[1][2] * mm44[3][3] - mm44[1][3] * mm44[3][2];
    float adj1313 = mm44[1][1] * mm44[3][3] - mm44[1][3] * mm44[3][1];
    float adj1213 = mm44[1][1] * mm44[3][2] - mm44[1][2] * mm44[3][1];
    float adj2312 = mm44[1][2] * mm44[2][3] - mm44[1][3] * mm44[2][2];
    float adj1312 = mm44[1][1] * mm44[2][3] - mm44[1][3] * mm44[2][1];
    float adj1212 = mm44[1][1] * mm44[2][2] - mm44[1][2] * mm44[2][1];
    float adj0313 = mm44[1][0] * mm44[3][3] - mm44[1][3] * mm44[3][0];
    float adj0213 = mm44[1][0] * mm44[3][2] - mm44[1][2] * mm44[3][0];
    float adj0312 = mm44[1][0] * mm44[2][3] - mm44[1][3] * mm44[2][0];
    float adj0212 = mm44[1][0] * mm44[2][2] - mm44[1][2] * mm44[2][0];
    float adj0113 = mm44[1][0] * mm44[3][1] - mm44[1][1] * mm44[3][0];
    float adj0112 = mm44[1][0] * mm44[2][1] - mm44[1][1] * mm44[2][0];

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
    inverted[3] [3] = det * (mm44[0][0] * adj1212 - mm44[0][1] * adj0212 + mm44[0][2] * adj0112);

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
void Matrix4x4::ConcatTransformation(const Matrix4x4 &matrix44)
{
    ConcatTransformation(matrix44.mm44);
}
void Matrix4x4::ConcatRotateX(float angle)
{
    float rot[4][4] = {{1, 0, 0, 0},
                       {0, cos(angle), sin(angle), 0},
                       {0, -sin(angle), cos(angle), 0},
                       {0, 0, 0, 1}};
    this->ConcatTransformation(rot);
}
void Matrix4x4::ConcatRotateY(float angle)
{
    float rot[4][4] = {{cos(angle), 0, -sin(angle), 0},
                       {0, 1, 0, 0},
                       {sin(angle), 0, cos(angle), 0},
                       {0, 0, 0, 1}};
    this->ConcatTransformation(rot);
}

void Matrix4x4::ConcatRotateZ(float angle)
{
    float rot[4][4] = {{cos(angle), -sin(angle), 0, 0},
                       {sin(angle), cos(angle), 0, 0},
                       {0, 0, 1, 0},
                       {0, 0, 0, 1}};
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
    float translateMatrix[4][4] = {
    {x, 0, 0, 0},
    {0, x, 0, 0},
    {0, 0, x, 0},
    {0, 0, 0, 1},
    };
    this->ConcatTransformation(translateMatrix);
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
