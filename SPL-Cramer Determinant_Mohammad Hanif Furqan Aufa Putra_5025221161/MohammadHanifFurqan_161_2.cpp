#include <iostream>
#include <iomanip> // for std::setprecision


#define M 10 // Define the maximum size of the matrix

void getCofactor(int mat[M][M], int temp[M][M], int p, int q, int n)
{
    int i = 0, j = 0;

    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if (row != p && col != q)
            {
                temp[i][j++] = mat[row][col];

                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

int determinantOfMatrix(int mat[M][M], int n)
{
    int D = 0;

    if (n == 1)
        return mat[0][0];

    int temp[M][M];
    int sign = 1;

    for (int f = 0; f < n; f++)
    {
        getCofactor(mat, temp, 0, f, n);
        D += sign * mat[0][f] * determinantOfMatrix(temp, n - 1);
        sign = -sign;
    }

    return D;
}

int PerformOperation(float a[M][M], int n)
{
    // Implementation of Gaussian Elimination

    // Loop to perform the matrix transformation
    for (int i = 0; i < n; i++)
    {
        if (a[i][i] == 0.0)
        {
            std::cerr << "Mathematical Error!";
            return 1;
        }

        for (int j = i + 1; j < n; j++)
        {
            float ratio = a[j][i] / a[i][i];

            for (int k = 0; k <= n; k++)
            {
                a[j][k] = a[j][k] - ratio * a[i][k];
            }
        }
    }
    return 0;
}

int CheckConsistency(float a[M][M], int n, int flag)
{
    // Check for consistency
    flag = 2;
    for (int i = 0; i < n; i++)
    {
        if (a[i][i] == 0 && a[i][n] != 0)
        {
            flag = 3;
            return flag;
        }
    }
    return flag;
}

int main()
{
    int n;
    std::cout << "Enter the number of equations: ";
    std::cin >> n;

    float a[M][M];

    std::cout << "Enter the linear equations in matrix form (coefficients and constants):" << std::endl;
    for (int i = 0; i < n; i++)
    {
        std::cout << "Enter equation " << i + 1 << ": ";
        for (int j = 0; j <= n; j++)
        {
            std::cin >> a[i][j];
        }
    }

    int flag = 0;

    // Perform Gaussian Elimination
    flag = PerformOperation(a, n);

    if (flag == 1)
    {
        std::cout << "Mathematical Error!" << std::endl;
        return 1;
    }

    // Check consistency and display results
    flag = CheckConsistency(a, n, flag);

    std::cout << std::endl;
    std::cout << "Values of each variable:" << std::endl;
    std::cout << std::fixed << std::setprecision(2);

    if (flag == 2)
    {
        for (int i = 0; i < n; i++)
        {
            std::cout << "X" << i + 1 << " = " << a[i][n] << std::endl;
        }
    }
    else if (flag == 3)
    {
        std::cout << "No unique solution exists." << std::endl;
    }

    // Calculate the determinant of the coefficient matrix
    int coefficientMatrix[M][M];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            coefficientMatrix[i][j] = a[i][j];
        }
    }

    int det = determinantOfMatrix(coefficientMatrix, n);
    std::cout << "Determinant of the coefficient matrix: " << det << std::endl;

    return 0;
}
