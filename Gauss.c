#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define EPS 1e-9  // very small number compared to zero

float **newMat(int n){  // allocating memory for a new matrix
    int i;
    float **mat = (float**)malloc(n*sizeof(float*));
    for (i = 0; i<n; i++){
        mat[i] = (float*)malloc(n*sizeof(float));
    }
    return mat;
}


void readMat(int n, float **mat){  // reading the matrix
    int i, j;
    for (i = 0; i<n; i++){
        for (j = 0; j<n; j++){
            scanf("%f", &mat[i][j]);
        }
    }
}


// additional function for displaying a matrix in step form

// void printMat(int n, float **mat){  
//     int i, j;
//     for (i = 0; i<n; i++){
//         for (j = 0; j<n; j++){
//             printf("%4.2f ", mat[i][j]);
//         }
//         printf("\n");
//     }
// }



float determinant(int n, float **mat){  // search for a determinant
    int i;
    float det = 1.0;
    for (i = 0; i<n; i++){
        det*=mat[i][i];
    }
    return det;
}


void Gauss(int n, float **mat){  // Gauss method
    int i, j, k;
    for (i = 0; i < n; i++) {  // going through the rows from top to bottom
        if (mat[i][i] == 0.0) {  // find a string whose leading element is 0
            for (j = i+1; j < n; j++) {  // search for a row below with a non-zero element in this column
                if (mat[j][i] != 0.0) {
                    for (k = 0; k < n; k++) {  // if we find it, we swap the lines.
                        float temp = mat[i][k];
                        mat[i][j] = mat[j][k];
                        mat[j][k] = temp;
                    }
                    k = n; //break - exiting the search loop
                }
            }
        }

        // we want to make all elements under the leading element zero

        for (k = i+1; k < n; k++) {  // we go through all the rows below the current one
            if (mat[i][i] != 0.0) {  // check that the leading element is not zero
                float coeff = mat[k][i] / mat[i][i];  // we calculate the coefficient by which the current row should be multiplied
                for (j = i; j < n; j++) {
                    mat[k][j] = mat[k][j] - coeff * mat[i][j];  // subtract line i multiplied by the coefficient from line k
                }
            }
        }
    }
}


void freeMat(int n, float **mat){  // clear memory
    int i;
    for (i = 0; i<n; i++){
        free(mat[i]);
    }
    free(mat);
}



int main(void) {
    int n;  // creating and entering the number n - matrix size
    scanf("%d", &n);
    
    float **mat = newMat(n);  // calling a function to allocate memory
    
    readMat(n, mat);  // calling a function to read the matrix

    Gauss(n, mat);  // Gauss method

    // additional function for displaying a matrix in step form
    // printMat(n, mat);  

    float det = determinant(n, mat);  // calling a function to search for a determinant

    if (fabs(det) < EPS) {  // if the determinant is close to zero, then we round it
        printf("0\n");
    } else {  // otherwise, we just output the determinant
        printf("%.9f\n", det);
    }
        
    freeMat(n, mat);  // calling a function to clear memory

    return 0;
}


// some tests

// 5
// 1.5 6 3 5 0.22
// -22 3.5 3.3 3.2 99
// -0.03 -4 -333 23.45 2.4
// 1 2 3 4 5  
// 6 7 8 9 0
// real answer: -903315.5992999999816888



// 3
// 0.22 -123 3.44
// 0.0 55.002 -3.33333
// 20 2 1
// real answer: 4429.4213052000004727



// 7
// 1 2 3 4 5 6 7
// 1.1 2.2 3.3 4.4 5.5 6.6 7.7
// 1.11 2.22 3.33 4.44 5.55 6.66 7.77
// 999 0 0 0 0 0 0
// 7.77 6.66 5.55 4.44 3.33 2.22 1.11
// 7.7 6.6 5.5 4.4 3.3 2.2 1.1
// 7 6 5 4 3 2 1
// real answer: 4.431124440000042 * 10^(-75) - in our program, it's just zero (a very very small number)



// 3
// 0 -0 -0.0
// 0.0000 -0 0
// 0 0 0
// real answer: 0