#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <cstdlib>

using namespace std;

#define EPSILON 1e-6 // Toleransi untuk angka mendekati nol

void PrintMatrix(const vector<vector<float> >& a, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (fabs(a[i][j]) < EPSILON) {
                printf("%d\t", 0); //Jika 0 akan tetap 0
            } else if (fabs(a[i][j] - round(a[i][j])) < EPSILON) {
                printf("%d\t", static_cast<int>(round(a[i][j])));
            } else {
                printf("%.2f\t", a[i][j]);
            }
        }
        printf("\n");
    }
    printf("-------------------------\n");
}

void PerformGauss(vector<vector<float> >& a, int n, int m) {
    for (int i = 0; i < n; i++) {
        float diag = a[i][i];
        printf("\nMembagi baris %d dengan %.2f untuk membuat diagonal menjadi 1\n", i + 1, diag);
        for (int k = 0; k < m; k++) {
            a[i][k] /= diag;
        }

        for (int j = i + 1; j < n; j++) {
            float factor = a[j][i];
            printf("Mengeliminasi elemen pada baris %d menggunakan faktor %.2f dari baris %d\n", j + 1, factor, i + 1);
            for (int k = 0; k < m; k++) {
                a[j][k] -= factor * a[i][k];
            }
        }

        printf("\nSetelah langkah operasi baris %d:\n", i + 1);
        PrintMatrix(a, n, m);
    }
}

void PerformGaussJordan(vector<vector<float> >& a, int n, int m) {
    for (int i = 0; i < n; i++) {
        float diag = a[i][i];
        printf("\nMembagi baris %d dengan %.2f untuk membuat diagonal menjadi 1\n", i + 1, diag);
        for (int k = 0; k < m; k++) {
            a[i][k] /= diag;
        }

        for (int j = 0; j < n; j++) {
            if (i != j) {
                float factor = a[j][i];
                printf("Mengeliminasi elemen pada baris %d menggunakan faktor %.2f dari baris %d\n", j + 1, factor, i + 1);
                for (int k = 0; k < m; k++) {
                    a[j][k] -= factor * a[i][k];
                }
            }
        }

        printf("\nSetelah langkah operasi baris %d:\n", i + 1);
        PrintMatrix(a, n, m);
    }
}

void CalculateInverse(vector<vector<float> >& a, int n) {
    vector<vector<float> > augmented(n, vector<float>(2 * n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            augmented[i][j] = a[i][j];
        }
        augmented[i][i + n] = 1;
    }

    for (int i = 0; i < n; i++) {
        if (fabs(augmented[i][i]) < EPSILON) {
            printf("Tidak memiliki invers matriks!\n");
            exit(0);
        }

        float diag = augmented[i][i];
        printf("\nMembagi baris %d dengan %.2f untuk membuat diagonal menjadi 1\n", i + 1, diag);
        for (int k = 0; k < 2 * n; k++) {
            augmented[i][k] /= diag;
        }

        for (int j = 0; j < n; j++) {
            if (i != j) {
                float factor = augmented[j][i];
                printf("Mengeliminasi elemen pada baris %d menggunakan faktor %.2f dari baris %d\n", j + 1, factor, i + 1);
                for (int k = 0; k < 2 * n; k++) {
                    augmented[j][k] -= factor * augmented[i][k];
                }
            }
        }

        printf("\nSetelah langkah operasi baris %d:\n", i + 1);
        PrintMatrix(augmented, n, 2 * n);
    }

    printf("\nInvers matriks adalah:\n");
    for (int i = 0; i < n; i++) {
        for (int j = n; j < 2 * n; j++) {
            printf("%.2f\t", augmented[i][j]);
        }
        printf("\n");
    }
}

void InputMatrix(vector<vector<float> >& a, int n, int m) {
    printf("Masukkan Nilai Matriks:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%f", &a[i][j]);
        }
    }
    printf("\nInisial Matriks:\n");
    PrintMatrix(a, n, m);
}

void ShowMenu() {
    int choice, n, m;
    printf("\nPilih Operasi:\n");
    printf("1. Eliminasi Gauss\n");
    printf("2. Eliminasi Gauss-Jordan\n");
    printf("3. Invers Matriks menggunakan Gauss-Jordan\n");
    printf("Pilihanmu: ");
    scanf("%d", &choice);

    if (choice == 1 || choice == 2) {
        printf("Jumlah baris: ");
        scanf("%d", &n);
        printf("Jumlah kolom: ");
        scanf("%d", &m);

        vector<vector<float> > a(n, vector<float>(m)); 

        InputMatrix(a, n, m);
        if (choice == 1) {
            printf("\nEliminasi Gauss:\n");
            PerformGauss(a, n, m);
        } else if (choice == 2) {
            printf("\nEliminasi Gauss-Jordan:\n");
            PerformGaussJordan(a, n, m);
        }
    } else if (choice == 3) {
        printf("Masukkan jumlah ordo matriks (n x n): ");
        scanf("%d", &n);

        vector<vector<float> > matrix(n, vector<float>(n)); 
        printf("Masukkan matriks untuk invers:\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                scanf("%f", &matrix[i][j]);
            }
        }
        printf("Inisial Matriks:\n");
        PrintMatrix(matrix, n, n);
        CalculateInverse(matrix, n);
    } else {
        printf("Pilihan salah!\n");
    }
}

int main() {
    ShowMenu();
    return 0;
}
