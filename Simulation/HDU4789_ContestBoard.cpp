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
#include <assert.h>

using namespace std;

typedef long long int64;
typedef long long LL;
typedef long double real;
typedef long double LD;

#define mp make_pair
#define PII pair<int, int>
#define pb push_back
#define sz(X) ((int)((X).size()))

#define x first
#define y second

const double eps = 1e-8;
const double PI = acos(0.) * 2;
const int lim = 1000000000;
const int inf = ~0U >> 1;

template<class T> T abs(T x){return x < 0 ? -x : x;}

const int N = 100005;

int n, m, t1, t2;
map<string, int> NAME;
map<int, string> _NAME;

int getID(string s)
{
	if (NAME.count(s)) return NAME[s];
	int t = sz(NAME);
	NAME[s] = t;
	_NAME[t] = s;
	return t;
}

struct event
{
	event(){}
	event(int name, int pro, int time, int st):name(name), pro(pro), time(time), st(st){}
	bool operator<(const event &b) const
	{
		if (time != b.time) return time < b.time;
		return st < b.st;
	}
	int name, pro, time, st;
};

event a[N];

struct team
{
	team(){}
	void reset()
	{
		now = 0;
		sol = 0;
		pt = 0;
		for (int i = 0; i < m; ++i)
		{
			pro_st[i] = 0;
			pro_pt[i] = 0;
			pro_fst[i] = -1;
			pro_fpt[i] = 0;
			pro_cnt[i] = 0;
		}
		sol_time.clear();
	}
	void WA(int pro)
	{
		if (pro_st[pro] == 1) return;
		pro_pt[pro] += 20;
	}
	void AC(int pro, int time)
	{
		if (pro_st[pro] == 1) return;
		pt += pro_pt[pro] + time;
		pro_st[pro] = 1;
		++sol;
		sol_time.pb(time);
		sort(sol_time.begin(), sol_time.end());
	}
	void fWA(int pro)
	{
		if (pro_st[pro] == 1) return;
		pro_cnt[pro] ++;
		if (pro_fst[pro] != -1) return;
		pro_fpt[pro] += 20;
	}
	void fERR(int pro)
	{
		if (pro_st[pro] == 1) return;
		pro_cnt[pro] ++;
	}
	void fAC(int pro, int time)
	{
		if (pro_st[pro] == 1) return;
		pro_cnt[pro] ++;
		if (pro_fst[pro] != -1) return;
		pro_fst[pro] = time;
	}
	void show(int pro)
	{
		if (pro_st[pro] == 1)
		{
			if (pro_pt[pro] == 0)
				printf(" +");
			else
				printf(" +%d", pro_pt[pro] / 20);
		}
		else
		{
			if (pro_pt[pro] == 0)
				printf(" .");
			else
				printf(" -%d", pro_pt[pro] / 20);
		}
	}
	void fshow(int pro)
	{
		if (pro_st[pro] == 1)
		{
			if (pro_pt[pro] == 0)
				printf(" +");
			else
				printf(" +%d", pro_pt[pro] / 20);
		}
		else if (pro_cnt[pro])
			printf(" %d/%d", -pro_pt[pro] / 20, pro_cnt[pro]);
		else
		{
			if (pro_pt[pro] == 0)
				printf(" .");
			else
				printf(" -%d", pro_pt[pro] / 20);
		}
	}
	void unfreeze(int pro)
	{
		pro_cnt[pro] = 0;
		if (pro_fst[pro] == -1) return;
		++sol;
		pt += pro_pt[pro] + pro_fpt[pro] + pro_fst[pro];
		sol_time.pb(pro_fst[pro]);
		sort(sol_time.begin(), sol_time.end());
	}
	bool operator<(const team &b) const
	{
		if (sol != b.sol) return sol > b.sol;
		if (pt != b.pt) return pt < b.pt;
		for (int i = sz(sol_time) - 1; i >= 0; --i)
			if (sol_time[i] != b.sol_time[i])
				return sol_time[i] < b.sol_time[i];
		return name > b.name;
	}
	string name;
	int pro_st[26];
	int pro_pt[26];
	int pro_fst[26];
	int pro_fpt[26];
	int pro_cnt[26];
	int pt;
	int sol;
	int now;
	vector<int> sol_time;
};

team b[N];

struct node
{
	node(){}
	node(int i):i(i){}
	bool operator<(const node &a) const
	{
		return b[i] < b[a.i];
	}
	int i;
};

int main(){
	map<string, int> TMP;
	TMP["ERROR"] = 0;
	TMP["NO"] = 1;
	TMP["YES"] = 2;

	int T;
	scanf("%d", &T);
	for (int tt = 1; tt <= T; ++tt)
	{
		printf("Case #%d:\n", tt);
		scanf("%d%d%d%d", &n, &m, &t1, &t2);
		NAME.clear();
		_NAME.clear();
		for (int i = 0; i < n; ++i)
		{
			char _name[25], _pro, _st[10];
			int time;
			scanf("%s %c %d %s", _name, &_pro, &time, _st);
			a[i] = event(getID(_name), _pro - 'A', time, TMP[_st]);
		}
		sort(a, a + n);
		for (int i = 0; i < sz(NAME); ++i)
		{
			b[i].name = _NAME[i];
			b[i].reset();
		}
		for (int i = 0; i < n; ++i)
		{
			int name = a[i].name;
			int pro = a[i].pro;
			int time = a[i].time;
			int st = a[i].st;
			if (st == 1)
			{
				if (time < t2)
					b[name].WA(pro);
				else
					b[name].fWA(pro);
			}
			else if (st == 2)
			{
				if (time < t2)
					b[name].AC(pro, time);
				else
					b[name].fAC(pro, time);
			}
			else if (st == 0 && time >= t2)
				b[name].fERR(pro);
		}
		sort(b, b + sz(NAME));
		for (int i = 0; i < sz(NAME); ++i)
		{
			printf("%s %d %d %d", b[i].name.c_str(), i + 1, b[i].sol, b[i].pt);
			for (int j = 0; j < m; ++j)
				b[i].fshow(j);
			puts("");
		}

		set<node> Set;
		for (int i = 0; i < sz(NAME); ++i)
			Set.insert(node(i));
		set<node>::iterator it2, it1, tmp;
		int last, follow, now;
		it2 = Set.end();
		--it2;
		while (1)
		{
			last = it2->i;
			it1 = it2;
			++it1;
			if (it1 == Set.end())
				follow = -1;
			else
				follow = it1->i;
			int j = -1;
			for (int i = 0; i < m; ++i)
				if (b[last].pro_cnt[i] > 0)
				{
					j = i;
//					b[last].now = i + 1;
					break;
				}
			if (j == -1)
			{
				if (it2 == Set.begin()) break;
				--it2;
			}
			else
			{
				Set.erase(last);
				b[last].unfreeze(j);
				Set.insert(last);
				it2 = Set.find(last);
				tmp = it2;
				++tmp;
				if (tmp == Set.end())
					now = -1;
				else
					now = tmp->i;
				if (now == follow) continue;
				printf("%s %s %d %d\n", b[last].name.c_str(), b[now].name.c_str(), b[last].sol, b[last].pt);
				if (follow == -1)
					it2 = Set.end();
				else
					it2 = Set.find(follow);
				--it2;
			}
		}

		vector<string> qq;
		for (it1 = Set.begin(); it1 != Set.end(); ++it1)
			qq.pb(b[it1->i].name);

		for (int i = 0; i < sz(NAME); ++i)
		{
			b[i].name = _NAME[i];
			b[i].reset();
		}
		for (int i = 0; i < n; ++i)
		{
			int name = a[i].name;
			int pro = a[i].pro;
			int time = a[i].time;
			int st = a[i].st;
			if (st == 1) b[name].WA(pro);
			else if (st == 2) b[name].AC(pro, time);
		}
		sort(b, b + sz(NAME));
		for (int i = 0; i < sz(NAME); ++i)
		{
			printf("%s %d %d %d", b[i].name.c_str(), i + 1, b[i].sol, b[i].pt);
			for (int j = 0; j < m; ++j)
				b[i].show(j);
			puts("");
		}
	}
	return 0;

}
