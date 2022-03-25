#include <bits/stdc++.h>
using namespace std;
#define ll long long int
#define MAX 100000
// Tìm phần tử max - min trong dãy
// Tăng Ngọc Phụng - 46.01.103.055
/*
* Testcase 1:
5
890 190 49 456 23

Testcase 2:
6
2 4 5 7 8 2 

Testcase 3:
10
-9039 9309494 367647 7389 1897893 752897 48379 -49298914798 874686747 8736837

Testcase 4:
3
1 0 -1

Testcase 5:
3
-9373 134 4567

Testcase 6:
20
1 9 10 2 -5767 876487 -74467 8764 74648 87648 -984794 -94874 746487 3876387 94874 6487648 763873 476487 -98478 37457

Testcase 7:
1
2

Testcase 8: 
4
19 20 536 -984794

Testcase 9:
7
1 -5985 34 678 874 -94847  876

Testcase 10:
8
-938 3656 2576 7256 -398795 -8367837  6375736 447763
*/
void MaxMin(ll a[], ll i, ll j, ll& max, ll& min)
{
	if (i == j)
	{
		if (max < a[i]) max = a[i];
		if (min > a[i]) min = a[i];
		return;
	}
	else if (j == i + 1)
	{
		if (a[i] > a[j])
		{
			if (max < a[i]) max = a[i];
			if (min > a[j]) min = a[j];
		}
		else
		{
			if (max < a[j]) max = a[j];
			if (min > a[i]) min = a[i];
		}
		return;
	}
	else
	{
		int mid = (i + j) / 2;
		MaxMin(a, i, mid, max, min);
		MaxMin(a, mid + 1, j, max, min);
	}
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	ll len, a[MAX], max = INT_MIN, min = INT_MAX;
	cout << "Nhap vao so luong phan tu cua mang: ";
	cin >> len;
	cout << "Nhap vao nhung phan tu cua mang: ";
	for (int i = 0; i < len; i++) cin >> a[i];
	MaxMin(a, 0, len - 1, max, min);
	cout << "Phan tu co gia tri nho nhat trong mang: " << min << '\n';
	cout << "Phan tu co gia tri lon nhat trong mang: " << max;
}

