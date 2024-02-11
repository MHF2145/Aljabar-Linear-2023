/* Mohammad Hanif Furqan Aufa Putra-5025221161
   Sumber: https://www.geeksforgeeks.org/program-for-gauss-jordan-elimination-method/
*/

#include <iostream>
#include <iomanip>

// Maksimum ukuran matriks
#define M 10


// Fungsi untuk melakukan operasi Gauss-Jordan
int PerformOperation(float a[][M], int n)
{
    int i, j, k = 0, c, flag = 0, m = 0;
    float pro = 0;

    for (i = 0; i < n; i++)
    {
        if (a[i][i] == 0)
        {
            c = 1;
            while ((i + c) < n && a[i + c][i] == 0)
                c++;
            if ((i + c) == n) {
                flag = 1;  // Kasus ketidakcocokan
                break;
            }
            for (j = i, k = 0; k <= n; k++)
                std::swap(a[j][k], a[j + c][k]);
        }

        for (j = 0; j < n; j++) {
            if (i != j) {
                float pro = a[j][i] / a[i][i];
                for (k = 0; k <= n; k++)
                    a[j][k] = a[j][k] - (a[i][k]) * pro;
            }
        }
    }
    return flag;  // 0: solusi unik, 1: ketidakcocokan, 2: solusi tak terbatas
}


// Fungsi untuk memeriksa konsistensi matriks
int CheckConsistency(float a[][M], int n, int flag)
{
    int i, j;
    float sum;
    flag = 3;
    for (i = 0; i < n; i++)
    {
        sum = 0;
        for (j = 0; j < n; j++)
            sum = sum + a[i][j];
        if (sum == a[i][j])
            flag = 2;
    }
    return flag;  // 2: Solusi tak terbatas, 3: Tidak ada solusi
}

// Fungsi untuk mencetak hasil
void PrintResult(float a[][M], int n, int flag)
{
    std::cout << "Hasilnya adalah: ";
    if (flag == 2)
        std::cout << "Solusi tak terbatas" << std::endl;
    else if (flag == 3)
        std::cout << "Tidak ada solusi" << std::endl;
    else {
        for (int i = 0; i < n; i++)
            std::cout << a[i][n] / a[i][i] << " ";
    }
}

int main()
{
    int n;
    std::cout << "Masukkan jumlah variabel (jumlah persamaan linear): ";
    std::cin >> n;

    float a[M][M];

    for (int i = 0; i < n; i++) {
        std::cout << "Masukkan Persamaan Linear " << i + 1 << " (dalam bentuk matriks): ";
        for (int j = 0; j <= n; j++) {
            std::cin >> a[i][j];
        }
    }
    int flag = 0;

    // Melakukan transformasi matriks
    flag = PerformOperation(a, n);

    if (flag == 1)
        flag = CheckConsistency(a, n, flag);

    std::cout << std::endl;
    std::cout << "Nilai setiap variabel" << std::endl;
    std::cout << std::fixed << std::setprecision(2); // Mengatur format output
    for (int i = 0; i < n; i++) {
        std::cout << "X" << i + 1 << " = " << a[(n + i) - n][n] / a[(n + i) - n][(n + i) - n] << std::endl;
    }

    system("pause");
}
