// The closest pair 
#include <bits/stdc++.h>
using namespace std;
#define ll long long int
#define MAX 100000

// Tăng Ngọc Phụng - 46.01.103.055
/*
Testcase 1:
6
2   3
12  30
40  50
5   1
12  10
3   4

Testcase 2
3
67  89
15  56
90  34

Testcase 3:

5
14   78
89   26
67   23
1    2
3    4

Testcase 4:
8
1   7
8   9
23  45
34  67
89  90
23  34
45  23
34  56

Testcase 5:
10
-1   5
-5   6
-9  -3
-8   3
-6  -5
-9  -4
-10 -5
-7  -8
 1   2
 3   4

Testcase 6:
12
 1    5
 6    8
 2    6
-9   -5
-8    4
-7   -9 
10    12
24    45
67    78
89    90
-5    -6
-9    -3

Testcase 7:
5
89       90
34      -23
45      -89
56      -12
34       23

Testcase 8:
14
 1        -9
 2        -5
 6        -8
 5         7
 23        45
 56        23
 67        89
-32        23
 34        67
 67        34
 45        23
 56        34
 78        -20
-56        -34

Testcase 9:
6
23      45
78      12
56      67
89      12
35      20

Testcase 10:
8
1    6
7    9
12   23
56   34
23   45
78   34
-83  -45
-56  -78
*/
struct Point { 
    double x, y; 
    friend istream& operator >> (istream& is, Point& p)
    {
        is >> p.x >> p.y;
        return is;
    }
};

// sort by x
inline int compareX(const void* a, const void* b)
{
    Point* p1 = (Point*)a, * p2 = (Point*)b;
    return (p1->x - p2->x);
}

// sort by y
inline int compareY(const void* a, const void* b)
{
    Point* p1 = (Point*)a, * p2 = (Point*)b;
    return (p1->y - p2->y);
}

// find the distance between two points
 double dist(Point p1, Point p2)
{
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) +
        (p1.y - p2.y) * (p1.y - p2.y));
}

double bruteForce(Point P[], int n, Point& p1 , Point& p2)
{
    double min = DBL_MAX;
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            if (dist(P[i], P[j]) < min) {
                min = dist(P[i], P[j]);
                p1.x = P[i].x, p1.y = P[i].y;
                p2.x = P[j].x, p2.y = P[j].y;
            }
    return min;
}

// returns minimum of two values
inline double min(double x, double y)
{
    return (x < y) ? x : y;
}


// find the distance beween the closest points of
// strip of given size. All points in strip[] are sorted by y. 
double stripPoints(Point strip[], int size, double d, Point& p1 , Point& p2)
{
    double min = d;  // Initialize the minimum distance as d

    qsort(strip, size, sizeof(Point), compareY);

    // Pick all points one by one and try the next points 
    // till the difference between y's is smaller than d.
    for (int i = 0; i < size; ++i)
        for (int j = i + 1; j < size && (strip[j].y - strip[i].y) < min; ++j)
            if (dist(strip[i], strip[j]) < min) {
                min = dist(strip[i], strip[j]);
                p1.x = strip[i].x, p1.y = strip[i].y;
                p2.x = strip[j].x, p2.y = strip[j].y;
            }

    return min;
}

// find the smallest distance recursively. 
// All point in array P are sorted by x
double closest(Point P[], Point strip[], int n, Point& p1 , Point& p2)
{
    static Point ptemp1, ptemp2, ptemp3, ptemp4;

    // use brute force when there are not enough points
    if (n <= 3)
        return bruteForce(P, n, ptemp1, ptemp2);

    // mid point
    int mid = n / 2;
    Point midPoint = P[mid];

    // calculate the smallest distance 
    // dl: left of mid point 
    // dr: right side of the mid point
    double dl = closest(P, strip, mid, ptemp1, ptemp2);
    double dr = closest(P + mid, strip, n - mid, ptemp3, ptemp4);

    // assign the pair that has smaller distance
    if (dl < dr) {
        p1.x = ptemp1.x; p1.y = ptemp1.y;
        p2.x = ptemp2.x; p2.y = ptemp2.y;
    }
    else {
        p1.x = ptemp3.x; p1.y = ptemp3.y;
        p2.x = ptemp4.x; p2.y = ptemp4.y;
    }

    double dmin = min(dl, dr);

    int j = 0;
    for (int i = 0; i < n; i++)
        if (abs(P[i].x - midPoint.x) < dmin)
            strip[j++] = P[i];

    double dmin_strip = stripPoints(strip, j, dmin, ptemp1, ptemp2);
    double final_min = dmin;
    if (dmin_strip < dmin) {
        p1.x = ptemp1.x; p1.y = ptemp1.y;
        p2.x = ptemp2.x; p2.y = ptemp2.y;
        final_min = dmin_strip;
    }
    return final_min;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    Point p1 = { DBL_MAX, DBL_MAX }, p2 = { DBL_MAX, DBL_MAX };
    int n;
    cout << "Nhap so luong phan tu n: "; cin >> n;
    Point P[20];
    cout << "Nhap so luong phan tu cua mang: \n";
    for (int i = 0; i < n; i++)
    {
        cin >> P[i];
    }
    qsort(P, n, sizeof(Point), compareX);
    // array to store points in a strip
    Point* strip = new Point[n];

    // get the distance and pair of points
    cout << "The closest distance is " << closest(P, strip, n, p1, p2) << endl;

    delete[] strip;

    return 0;
}