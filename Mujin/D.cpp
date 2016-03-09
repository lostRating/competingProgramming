#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <ctime>
#include <sstream>
#include <fstream>
#include <bitset>
#include <iomanip>
#include <cassert>

using namespace std;

typedef long long int64;
typedef long long LL;
typedef long double LD;

#define mp make_pair
#define pb push_back
#define sz(X) ((int)((X).size()))
#define x first
#define y second

const double eps = 1e-8;
const double PI = acos(0.) * 2;
const int lim = 1000000000;
const int inf = ~0U >> 1;

template<class T> T abs(T x){return x < 0 ? -x : x;}

const int N = 100005 * 5;

int n, min1[N], min2[N], sum1[N], sum2[N], v[N];
vector<int> b;

void init(int a, int l, int r)
{
	min1[a] = min2[a] = lim;
	for (int i = l; i <= r; ++i)
	{
		if (v[i] >= 0) ++sum1[a];
		else --sum1[a];
		min1[a] = min(min1[a], sum1[a]);
	}
	for (int i = r; i >= l; --i)
	{
		if (v[i] <= 0) ++sum2[a];
		else --sum2[a];
		min2[a] = min(min2[a], sum2[a]);
	}
	if (l == r) return;
	int mid = (l + r) / 2;
	init(a * 2, l, mid);
	init(a * 2 + 1, mid + 1, r);
}

void query(int a, int l, int r, int ll, int rr)
{
	if (r < ll || rr < l) return;
	if (ll <= l && r <= rr)
	{
		b.pb(a);
		return;
	}
	int mid = (l + r) / 2;
	query(a * 2, l, mid, ll, rr);
	query(a * 2 + 1, mid + 1, r, ll, rr);
}

int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
	{
		char c;
		scanf(" %c", &c);
		if (c == '(') v[i] = 1;
		else if (c == ')') v[i] = -1;
		else v[i] = 0;
	}
	init(1, 1, n);
	int q;
	scanf("%d", &q);
	while (q--)
	{
		int l, r;
		scanf("%d%d", &l, &r);
		b.clear();
		query(1, 1, n, l, r);
		bool flag = true;
		for (int i = 0, s = 0; i < sz(b); ++i)
		{
			if (s + min1[b[i]] < 0) flag = false;
			s += sum1[b[i]];
		}
		for (int i = sz(b) - 1, s = 0; i >= 0; --i)
		{
			if (s + min2[b[i]] < 0) flag = false;
			s += sum2[b[i]];
		}
		if ((r - l + 1) & 1)
			flag = false;
		if (flag)
			puts("Yes");
		else
			puts("No");
	}
	return 0;
}
