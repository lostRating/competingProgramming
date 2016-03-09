#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int cnt[3][10];
int cnt2[3][10];
int sum[3][10];

string str;
stringstream strr;

int getchar(char x) {
    if (x == 'B') return 1;
    if (x == 'M') return 2;
    return 0;
}

char rgetchar(char x) {
    if (x == 1) return 'B';
    if (x == 2) return 'M';
    return 'D';
}

void init() {
    memset(cnt, 0, sizeof(cnt));
    memset(sum, 0, sizeof(sum));
    str.clear();
    cin >> str;
    strr.clear();
    strr.str(str);
    for (char x, y; ; ) {
        if (!(strr >> x)) break;
        strr >> y;
        cnt[getchar(y)][x - '0'] ++;
        sum[getchar(y)][x - '0'] ++;
    }
    memset(cnt2, 0, sizeof(cnt2));
    str.clear();
    cin >> str;
    if (str[0] == 'N') return;
    strr.clear();
    strr.str(str);
    for (char x, y; ; ) {
        if (!(strr >> x)) break;
        strr >> y;
        cnt2[getchar(y)][x - '0'] ++;
        sum[getchar(y)][x - '0'] ++;
    }
}

int purely() {
    static int sz[3];
    int ret = 0;
    memset(sz, 0, sizeof(sz));
    for (int i = 0; i < 3; ++i) {
        for (int j = 1; j <= 9; ++j) {
            sz[i] += sum[i][j];
        }
        ret += (sz[i] == 0);
    }
    return ret == 2 ? 2 : 0;
}

int dragon() {
    int ret = 0;
    for (int i = 0; i < 3; ++i)
        for (int j = 1; j <= 9; ++j)
            ret += (sum[i][j] == 4);
    return ret;
}

int seven_sky_ground() {
    for (int i = 0; i < 3; ++i)
        for (int j = 2; j <= 8; ++j)
            if (cnt[i][j]) return 0;
    return 2;
}

int seven_couples() {
    bool flag = 1;
    for (int i = 0; i < 3; ++i)
        for (int j = 1; j <= 9; ++j) {
            if (cnt2[i][j]) flag = 0;
            if (cnt[i][j] % 2) flag = 0;
        }
    if (flag == 0) return 0;
    int addtion = 0;
    addtion += dragon();
    addtion += purely();
    addtion += seven_sky_ground();
    return 3 + addtion;
}

bool logical() {
    int flag = 1;
    int tot = 0;
    static int sz[3];
    memset(sz, 0, sizeof(sz));
    for (int i = 0; i < 3; ++i) {
        for (int j = 1; j <= 9; ++j) {
            tot += cnt[i][j] + (cnt2[i][j] > 0) * 3;
            if (sum[i][j] > 4) flag = 0;
            if (cnt2[i][j] > 0 && cnt2[i][j] < 3) flag = 0;
            sz[i] += sum[i][j];
        }
    }
    if (sz[0] > 0 && sz[1] > 0 && sz[2] > 0) flag = 0;
    if (tot != 14) flag = 0;
    return flag;
}

bool check() {
    bool flag = 1;
    for (int i = 0; i < 3; ++i)
        for (int j = 1; j <= 9; ++j)
            if (cnt[i][j]) {
                if (j <= 7 && cnt[i][j + 1] && cnt[i][j + 2]) {
                    cnt[i][j] --;
                    cnt[i][j + 1] --;
                    cnt[i][j + 2] --;
                    flag = check();
                    cnt[i][j] ++;
                    cnt[i][j + 1] ++;
                    cnt[i][j + 2] ++;
                    if (flag) return 1;
                }
                if (cnt[i][j] >= 3) {
                    cnt[i][j] -= 3;
                    flag = check();
                    cnt[i][j] += 3;
                    if (flag) return 1;
                }
                return 0;
            }
    return 1;
}


int sky_ground() {
    for (int i = 0; i < 3; ++i) {
        if (cnt[i][1]) {
            if (cnt[i][2] && cnt[i][3]) {
                cnt[i][1] --;
                cnt[i][2] --;
                cnt[i][3] --;
                int ret = sky_ground();
                cnt[i][1] ++;
                cnt[i][2] ++;
                cnt[i][3] ++;
                if (ret) return ret;
            }
            if (cnt[i][1] >= 3) {
                cnt[i][1] -= 3;
                int ret = sky_ground();
                cnt[i][1] += 3;
                if (ret) return ret;
            }
            return 0;
        }
        if (cnt[i][9]) {
            if (cnt[i][7] && cnt[i][8]) {
                cnt[i][7] --;
                cnt[i][8] --;
                cnt[i][9] --;
                int ret = sky_ground();
                cnt[i][7] ++;
                cnt[i][8] ++;
                cnt[i][9] ++;
                if (ret) return ret;
            }
            if (cnt[i][9] >= 3) {
                cnt[i][9] -= 3;
                int ret = sky_ground();
                cnt[i][9] += 3;
                if (ret) return ret;
            }
            return 0;
        }
    }
    int flag = 2;
    for (int i = 0; i < 3; ++i)
        for (int j = 1; j <= 9; ++j) {
            if (cnt[i][j]) flag = 0;
            if (cnt2[i][j] && j != 1 && j != 9) flag = 0;
        }
    return flag;
}

int chunkious() {
    for (int i = 0; i < 3; ++i)
        for (int j = 1; j <= 9; ++j)
            if (cnt[i][j]) {
                if (cnt[i][j] >= 3) {
                    cnt[i][j] -= 3;
                    int ret = chunkious();
                    cnt[i][j] += 3;
                    if (ret == 3 && j != 2 && j != 5 && j != 8) ret = 1;
                    if (ret) return ret;
                }
                return 0;
            }
    int ret = 3;

    for (int i = 0; i < 3; ++i)
        for (int j = 1; j <= 9; ++j)
            if (cnt2[i][j] && j != 2 && j != 5 && j != 8) ret = 1;
    return ret;
}

int haha(int x, int y) {
    if (x != 3) return x;
    if (y == 2 || y == 5 || y == 8) return x;
    return 1;
}

int oooo(int x, int y) {
    if (x != 2) return x;
    if (y == 1 || y == 9) return x;
    return 0;
}

int normal() {
    if (!logical()) return 0;
    int ret = seven_couples();
    for (int i = 0; i < 3; ++i)
        for (int j = 1; j <= 9; ++j)
            if (cnt[i][j] >= 2) {
                cnt[i][j] -= 2;
                if (check()) {
                    int addtion = 0;
                    cnt[i][j] += 2;
                    addtion += dragon();
                    addtion += purely();
                    cnt[i][j] -= 2;
                    addtion += max(oooo(sky_ground(), j), haha(chunkious(), j));
                    ret = max(ret, 1 + addtion);
                }
                cnt[i][j] += 2;
            }
    return ret;
}

int calc() {
    int ret = normal();
    return ret;
    int addtion = 0;
    addtion += dragon();
    addtion += purely();
    addtion += max(sky_ground() * (ret == 1), chunkious());
    return ret + addtion;
}

void solve() {
    init();
    bool flag = 0;

    for (int i = 0; i < 3; ++i)
        for (int j = 1; j <= 9; ++j) {
            if (sum[i][j] == 4) continue;
            cnt[i][j]++;
            sum[i][j]++;
            int ret = calc();
            if (ret) {
                printf("%d%c: %d\n", j, rgetchar(i), ret);
                flag = 1;
            }
            cnt[i][j]--;
            sum[i][j]--;
        }
    if (!flag) printf("NONE\n");
}

int main() {
    int T;
    scanf("%d", &T);
    for (int i = 1; i <= T; ++i) {
        printf("Case #%d:\n", i);
        solve();
    }
}
