#include <bits/stdc++.h>
using namespace std;
#define ll long long 
// Tăng Ngọc Phụng - 46.01.103.055
/*
Testcase 1:
12
12

Testcase 2:
5
6

Testcase 3:
23
4

Testcase 4:
2
0

Testcase 5:
56
7

Testcase 6:
12
16

Testcase 7:
14
12

Testcase 8:
34
5

Testcase 9:
16
7

Testcase 9:
89
8

Testcase 10:
0
2
*/

ll f(ll x, ll n)
{
	if (n == 0) return 1;
	if (n % 2 != 0)
	{
		ll y = f(x, (n - 1) / 2);
		return x * y * y;
	}
	else
	{
		ll y = f(x, n / 2);
		return y * y;
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	ll a, n;
	cout << "Hay nhap co so: "; cin >> a;
	cout << "Hay nhap so mu: "; cin >> n;
	cout << "Ket qua cua luy thua: ";
	cout << f(a, n);
}