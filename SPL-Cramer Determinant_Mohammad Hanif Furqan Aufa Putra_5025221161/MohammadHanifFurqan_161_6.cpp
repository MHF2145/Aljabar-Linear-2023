#include <iostream>
#include <iomanip>

const int M = 10;

// Fungsi untuk melakukan operasi baris
int PerformOperation(float a[M][M], int n)
{
    int i, j, k = 0, flag = 0;
    for (i = 0; i < n; i++)
    {
        if (a[i][i] == 0.0)
        {
            flag = 1;
            break;
        }
        for (j = i + 1; j < n; j++)
        {
            float ratio = a[j][i] / a[i][i];
            for (k = 0; k <= n; k++)
            {
                a[j][k] = a[j][k] - ratio * a[i][k];
            }
        }
    }
    return flag;
}

// Fungsi untuk memeriksa konsistensi
int CheckConsistency(float a[M][M], int n, int flag)
{
    int i, j;
    float sum;

    flag = 3;
    for (i = 0; i < n; i++)
    {
        sum = 0;
        for (j = 0; j < n; j++)
        {
            sum = sum + a[i][j];
        }
        if (sum == a[i][j])
            flag = 2;
    }
    return flag;
}

int main()
{
    int n;
    std::cout << "Masukkan jumlah variabel (persamaan): ";
    std::cin >> n;

    float a[M][M];

    std::cout << "Masukkan Persamaan Linear dalam Bentuk Matriks (Koefisien dan Konstanta):" << std::endl;
    for (int i = 0; i < n; i++)
    {
        std::cout << "Masukkan Persamaan " << i + 1 << ": ";
        for (int j = 0; j <= n; j++)
        {
            std::cin >> a[i][j];
        }
    }

    int flag = 0;

    // Melakukan operasi baris dan memeriksa konsistensi
    flag = PerformOperation(a, n);

    if (flag == 1)
        flag = CheckConsistency(a, n, flag);

    std::cout << std::endl;
    std::cout << "Nilai setiap variabel:" << std::endl;
    std::cout << std::fixed << std::setprecision(2);

    for (int i = 0; i < n; i++)
    {
        std::cout << "X" << i + 1 << " = " << a[i][n] / a[i][i] << std::endl;
    }

    system("pause");
}
