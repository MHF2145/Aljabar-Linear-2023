// Mohammad Hanif Furqan Aufa Putra
// referrence:
// https://www.geeksforgeeks.org/system-linear-equations-three-variables-using-cramers-rule/
// https://www.geeksforgeeks.org/cpp-program-for-determinant-of-a-matrix/amp/

#include <iostream>
#include <iomanip>

const int M = 10;

// Fungsi untuk mendapatkan matriks minor atau koefisien dari suatu matriks
void getCofactor(float mat[M][M], float temp[M][M], int p, int q, int n)
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

// Fungsi untuk menghitung determinan matriks
float determinantOfMatrix(float mat[M][M], int n)
{
    float D = 0;

    if (n == 1)
        return mat[0][0];

    float temp[M][M];
    float sign = 1;

    for (int f = 0; f < n; f++)
    {
        getCofactor(mat, temp, 0, f, n);
        D += sign * mat[0][f] * determinantOfMatrix(temp, n - 1);
        sign = -sign;
    }

    return D;
}

// Fungsi untuk melakukan operasi eliminasi Gauss
int PerformOperation(float a[M][M], int n)
{
    // Implementasi Eliminasi Gauss

    // Loop untuk melakukan transformasi matriks
    for (int i = 0; i < n; i++)
    {
        if (a[i][i] == 0.0)
        {
            std::cerr << "Kesalahan Matematika!";
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

// Fungsi untuk memeriksa konsistensi sistem persamaan linear
int CheckConsistency(float a[M][M], int n, int flag)
{
    // Memeriksa konsistensi
    flag = 2;
    for (int i = 0; i < n; i++)
    {
        if (a[i][i] == 0.0 && a[i][n] != 0.0)
        {
            flag = 3;
            return flag;
        }
    }
    return flag;
}

// Fungsi untuk mencetak matriks identitas
void printIdentityMatrix(int n)
{
    std::cout << "Matriks Identitas:" << std::endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                std::cout << "1 ";
            else
                std::cout << "0 ";
        }
        std::cout << std::endl;
    }
}

int main()
{
    int n;
    std::cout << "Masukkan jumlah persamaan: ";
    std::cin >> n;

    float a[M][M];

    std::cout << "Masukkan persamaan linear dalam bentuk matriks (koefisien dan konstanta):" << std::endl;
    for (int i = 0; i < n; i++)
    {
        std::cout << "Masukkan persamaan " << i + 1 << ": ";
        for (int j = 0; j <= n; j++)
        {
            std::cin >> a[i][j];
        }
    }

    int flag = 0;

    // Melakukan Eliminasi Gauss
    flag = PerformOperation(a, n);

    if (flag == 1)
    {
        std::cout << "Kesalahan Matematika!" << std::endl;
        return 1;
    }

    // Memeriksa konsistensi dan menampilkan hasil
    flag = CheckConsistency(a, n, flag);

    std::cout << std::endl;
    // Mencetak matriks identitas
    printIdentityMatrix(n);
    std::cout << "Nilai setiap variabel:" << std::endl;
    std::cout << std::fixed << std::setprecision(2);

    if (flag == 2)
    {
        for (int i = 0; i < n; i++)
        {
            std::cout << "X" << i + 1 << " = " << a[i][n] / a[i][i] << std::endl;
        }
    }
    else if (flag == 3)
    {
        std::cout << "Tidak ada solusi tunggal." << std::endl;
    }

    // Menghitung determinan matriks koefisien
    float coefficientMatrix[M][M];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            coefficientMatrix[i][j] = a[i][j];
        }
    }

    float det = determinantOfMatrix(coefficientMatrix, n);
    std::cout << "Determinan matriks koefisien: " << det << std::endl;

    system("pause");
}
