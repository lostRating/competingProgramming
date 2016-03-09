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



int main()
{
	char c;
	cin >> c;
	if (c == 'O' || c == 'P' || c == 'K' || c == 'L')
		puts("Right");
	else
		puts("Left");
	return 0;
}
