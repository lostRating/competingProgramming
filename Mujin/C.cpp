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

const int N = 16;

int s, edge[N][N], n, v[N];

bool contain(int s, int i)
{
	return (s & (1 << i)) > 0;
}

void dfs(int i, int fa)
{
	v[i] = fa;
	for (int j = 0; j < n; ++j)
	{
		if (v[j] != -1 || !edge[i][j]) continue;
		if (contain(s, i) ^ contain(s, j))
			dfs(j, fa);
	}
}

int main()
{
	int m;
	cin >> n >> m;
	for (int i = 0; i < m; ++i)
	{
		int x, y;
		cin >> x >> y;
		--x, --y;
		edge[x][y] = edge[y][x] = 1;
	}
	int ans = 0;
	for (s = 0; s < (1 << n); ++s)
	{
		bool flag = false;
		for (int i = 0; i < n; ++i)
			v[i] = -1;
		for (int i = 0; i < n; ++i)
			if (v[i] == -1)
			{
				if (!contain(s, i))
					flag = true;
				dfs(i, i);
			}
		for (int i = 0; i < n; ++i)
			for (int j = i + 1; j < n; ++j)
				if (edge[i][j] && contain(s, i) == contain(s, j) && v[i] != v[j])
					flag = true;
		if (flag) continue;
		++ans;
	}
	cout << ans << endl;
	return 0;
}
