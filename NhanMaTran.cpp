#include <bits/stdc++.h>
#include <conio.h>
using namespace std;

// Tăng Ngọc Phụng - 46.01.103.055
/*
Testcase 1:

2 5
1 6 7 9 3
9 1 2 3 5

5 2
1 9 
2 5
7 8
9 0
7 3

Testcase 2:

1 3
6 7 8

3 1
9
0
5

Testcase 3:
4 6
6 7 8 9 1 2
4 5 3 2 1 5
1 5 7 8 9 2
0 9 8 5 4 2

6 4
6 7 8 3
1 2 4 6 
4 6 8 3 
1 0 6 2
2 0 4 2
5 4 3 2 

Testcase 4:

3 5
1 7 8 9 3
8 4 3 2 1
6 7 0 2 5

5 3
6 7 8
9 1 2 
5 8 3
2 3 4
5 6 7

Testcase 5:

4 4
-9  3  -7  -4
 1  8   9   2
-6 -9  -5  -2
 8  1  -5   2

 4 4
 8  0 -6 -2
 1  2  3  7
-8 -7  9 -4
 5 -1  2 -4

Testcase 6:

2 2
1 0
0 2

2 2
8 4
1 -5

Testcase 7:

1 5
6 9 -4 2 1

5 1
 6 
-9
-3
-2
 5

Testcase 8:

4 3 
 4  5  1
-8 -6 -3
 3  2  1
-8  2  3

3 4
 6  9  0  1
 2  3  4  5 
-9  5  2 -5

Testcase 9:

5 5
 5  7  8  -3  -4
-6  7  2   1  -6
 8  4  2   1   9
 4  3  1   2   3
 6  7  9   3  -5

5 5
 1   3  -2  -6  -8
 2   3  -5  -6  -8
-9  -9   2  -4  -7
-4   2  -3  -7   8
 2   1  -5  -6  -9 

 Testcase 10:
3 2
-46574   48746 
 47654   674687
 74674   46476378

2 3
 253636     336364       4356714
-856787635  6286787      7567247

*/

int nextpowerof2(int k) {
    return pow(2, int(ceil(log2(k))));
}

void display(vector< vector<int>>& matrix, int m, int n) {
    cout << "Ma tran sau khi nhan: \n";
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            /* if (j != 0) {
                 cout << "\t";
             }*/
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}

void add(vector<vector<int>>& A, vector<vector<int>>& B, vector<vector<int>>& C, int size) {
    int i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void sub(vector<vector<int>>& A, vector<vector<int>>& B, vector<vector<int>>& C, int size) {
    int i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

void Strassen_algorithmA(vector<vector<int>>& A, vector<vector<int>>& B, vector<vector<int>>& C, int size)
{
    //base case
    if (size == 1)
    {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }
    else
    {
        int new_size = size / 2;
        vector<int> z(new_size);
        vector<vector<int>>
            a11(new_size, z), a12(new_size, z), a21(new_size, z), a22(new_size, z),
            b11(new_size, z), b12(new_size, z), b21(new_size, z), b22(new_size, z),
            c11(new_size, z), c12(new_size, z), c21(new_size, z), c22(new_size, z),
            p1(new_size, z), p2(new_size, z), p3(new_size, z), p4(new_size, z),
            p5(new_size, z), p6(new_size, z), p7(new_size, z),
            aResult(new_size, z), bResult(new_size, z);

        int i, j;

        //dividing the matrices into sub-matrices:
        for (i = 0; i < new_size; i++)
        {
            for (j = 0; j < new_size; j++)
            {
                a11[i][j] = A[i][j];
                a12[i][j] = A[i][j + new_size];
                a21[i][j] = A[i + new_size][j];
                a22[i][j] = A[i + new_size][j + new_size];

                b11[i][j] = B[i][j];
                b12[i][j] = B[i][j + new_size];
                b21[i][j] = B[i + new_size][j];
                b22[i][j] = B[i + new_size][j + new_size];
            }
        }

        // Calculating p1 to p7:

        add(a11, a22, aResult, new_size);     // a11 + a22
        add(b11, b22, bResult, new_size);    // b11 + b22
        Strassen_algorithmA(aResult, bResult, p1, new_size);
        // p1 = (a11+a22) * (b11+b22)

        add(a21, a22, aResult, new_size); // a21 + a22
        Strassen_algorithmA(aResult, b11, p2, new_size);
        // p2 = (a21+a22) * (b11)

        sub(b12, b22, bResult, new_size);      // b12 - b22
        Strassen_algorithmA(a11, bResult, p3, new_size);
        // p3 = (a11) * (b12 - b22)

        sub(b21, b11, bResult, new_size);       // b21 - b11
        Strassen_algorithmA(a22, bResult, p4, new_size);
        // p4 = (a22) * (b21 - b11)

        add(a11, a12, aResult, new_size);      // a11 + a12
        Strassen_algorithmA(aResult, b22, p5, new_size);
        // p5 = (a11+a12) * (b22)

        sub(a21, a11, aResult, new_size);      // a21 - a11
        add(b11, b12, bResult, new_size);
        // b11 + b12
        Strassen_algorithmA(aResult, bResult, p6, new_size);
        // p6 = (a21-a11) * (b11+b12)

        sub(a12, a22, aResult, new_size);      // a12 - a22
        add(b21, b22, bResult, new_size);
        // b21 + b22
        Strassen_algorithmA(aResult, bResult, p7, new_size);
        // p7 = (a12-a22) * (b21+b22)

        // calculating c21, c21, c11 e c22:

        add(p3, p5, c12, new_size); // c12 = p3 + p5
        add(p2, p4, c21, new_size); // c21 = p2 + p4

        add(p1, p4, aResult, new_size);       // p1 + p4
        add(aResult, p7, bResult, new_size);  // p1 + p4 + p7
        sub(bResult, p5, c11, new_size); // c11 = p1 + p4 - p5 + p7

        add(p1, p3, aResult, new_size);       // p1 + p3
        add(aResult, p6, bResult, new_size);  // p1 + p3 + p6
        sub(bResult, p2, c22, new_size); // c22 = p1 + p3 - p2 + p6

        // Grouping the results obtained in a single matrix:
        for (i = 0; i < new_size; i++)
        {
            for (j = 0; j < new_size; j++)
            {
                C[i][j] = c11[i][j];
                C[i][j + new_size] = c12[i][j];
                C[i + new_size][j] = c21[i][j];
                C[i + new_size][j + new_size] = c22[i][j];
            }
        }
    }
}
void Strassen_algorithm(vector<vector<int>>& A, vector<vector<int>>& B, int m, int n, int a, int b)
{
    /* Check to see if these matrices are already square and have dimensions of a power of 2. If not,
     * the matrices must be resized and padded with zeroes to meet this criteria. */
    int k = max({ m, n, a, b });

    int s = nextpowerof2(k);

    vector<int> z(s);
    vector<vector<int>> Aa(s, z), Bb(s, z), Cc(s, z);

    for (unsigned int i = 0; i < m; i++)
    {
        for (unsigned int j = 0; j < n; j++)
        {
            Aa[i][j] = A[i][j];
        }
    }
    for (unsigned int i = 0; i < a; i++)
    {
        for (unsigned int j = 0; j < b; j++)
        {
            Bb[i][j] = B[i][j];
        }
    }
    Strassen_algorithmA(Aa, Bb, Cc, s);
    vector<int> temp1(b);
    vector<vector<int>> C(m, temp1);
    for (unsigned int i = 0; i < m; i++)
    {
        for (unsigned int j = 0; j < b; j++)
        {
            C[i][j] = Cc[i][j];
        }
    }
    display(C, m, b);
}
void Input(vector<vector<int>>& a, int& m, int& n, int  matrix[100][100])
{
    vector<int> v;
    cout << "Hay nhap vao phan tu cua ma tran hai chieu: \n";
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> matrix[i][j];
            v.push_back(matrix[i][j]);
        }
        a.push_back(v);
        v.clear();
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int m1, n1, m2, n2; // m dong n cot a{m.m.m}
    int matrix[100][100];
    vector<vector<int>> a;
    vector<vector<int>> b;
    cout << "Hay nhap vao so cot va so dong cua ma tran: \n";
    cin >> m1 >> n1;
    Input(a, m1, n1, matrix);
    cout << "Hay nhap vao so cot va so dong cua ma tran: \n";
    cin >> m2 >> n2;
    while (n1 != m2)
    {
        cout << "Nhan hai ma tran phai: so cot cua ma tran 1 phai bang so dong cua ma tran 2. Vui long nhap lai so cot va so dong cua ma tran 2 \n";
        cin >> m2 >> n2;
    }
    Input(b, m2, n2, matrix);
    Strassen_algorithm(a, b, m1, n1, m2, n2);
    return 0;
    _getch();
}