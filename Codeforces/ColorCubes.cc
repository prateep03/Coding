/*
 * ColorCubes.cc
 *
 *  Created on: Aug 19, 2014
 *      Author: prateepm
 */

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <algorithm>
#include <iterator>
#include <map>
#include <vector>
#include <list>
#include <set>
#include <queue>
#include <cassert>
#include <deque>
#include <stack>
#include <bitset>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <cmath>
#include <ctime>

using namespace std;

#define LET(x,a)        __typeof(a) x(a)
#define IFOR(i,a,b)     for(LET(i,a);i!=(b);++i)
#define EACH(it,v)      IFOR(it,v.begin(),v.end())
#define FOR(i,a,b)      for(int i=(int)(a) ; i < (int)(b);i++)
#define REP(i,n)        FOR(i,0,n)
#define SZ              size()
#define PB              push_back
#define PF              push_front
#define V(x)            vector< x >
#define two(X)          (1<<(X))
#define twoL(X)         (((int64)(1))<<(X))
#define contain(S,X)    (((S)&two(X))!=0)
#define containL(S,X)   (((S)&twoL(X))!=0
#define swap(x,y)       x ^=y ^= x^=y
#define ALL(v)          (v).begin(),(v).end()

const double pi=acos(-1.0);
const double eps=1e-11;
const int INFINITE=0x3f3f3f3f;
template<class T> inline void checkmin(T &a,T b){if(b<a) a=b;}
template<class T> inline void checkmax(T &a,T b){if(b>a) a=b;}
template<class T> inline T sqr(T x){return x*x;}
typedef pair<int,int> ipair;
template<class T> inline T lowbit(T n){return (n^(n-1))&n;}
template<class T> inline int countbit(T n){return (n==0)?0:(1+countbit(n&(n-1)));}

typedef V(int)          VI;
typedef V(VI)           VII;
typedef V(string)       VS;
typedef unsigned long long       int64;
typedef long double     LD;
typedef pair<int,int>   PI;

/* http://www.codeabbey.com/index/task_view/color-cubes */
//#define LocalHost
const int MAXN = 20;
int b[MAXN][MAXN];
int colSum[MAXN];
int dot = -1;
const int dx[4] = {0,  0,  1, -1};
const int dy[4] = {1, -1,  0,  0};
int bfs(int x, int y, int w)
{
	if(b[x][y] == -1) return 0;
	int* qx = new int[w*w];
	int* qy = new int[w*w];
	int qh = 0, qt = 0;
	qx[qh] = x; qy[qh] = y; qh++;
	int res = 0;
	while(qt < qh) {
		int x = qx[qt], y = qy[qt++];
		if(b[x][y] == dot) continue;
		REP(r,4) {
			int xx = x + dx[r], yy = y + dy[r];
			if(xx < 0 || xx > w || yy < 0 || yy > w || b[xx][yy] != b[x][y]) continue;
			qx[qh] = xx, qy[qh] = yy; qh++;
		}
		colSum[y] = colSum[y] - b[x][y] + dot;
		b[x][y] = dot;
		++res;
	}
	return res;
}
void printBoard(int w)
{
	printf("---------------\n");
//	REP(i,w) REP(j,w) printf("%c%s",(b[i][j] == dot ? '-' : (char) (b[i][j]+'0')), (j == w-1 ? "\n" : ""));
	REP(i,w) REP(j,w) cout << (b[i][j] == dot ? '-' : (char) (b[i][j]+'0')) <<  (j == w-1 ? "\n" : "");
}
void updateBoard(int w)
{
	for(int c = w-1; c >= 0; --c) if(colSum[c] == -w) {
		// shift left
		int k = c;
		FOR(cc,c+1,w) if(colSum[cc] != -w){
			REP(r,w) {
				colSum[k] = colSum[k] -b[r][k] + b[r][cc];
				b[r][k] = b[r][cc];
			}
			k=cc;
		}
		REP(r,w) b[r][k] = -1;
	}
	// stupid
	REP(c,w) {
		for(int r = w-1; r >= 0; r--) if(b[r][c] > dot) {
			int rr = r+1; int ok = 0;
			while(rr < w && b[rr][c] == dot) {
				ok = 1;
				++rr;
			}
			if(--rr < w && ok) {
				b[rr][c] = b[r][c];
				b[r][c] = dot;
			}
		}
	}
}
int doit(int x, int y, int N)
{
	int cnt = ::bfs(x,y,N);
	::updateBoard(N);
	return cnt;
}
int main()
{
#ifdef LocalHost
   freopen("input.txt","r",stdin);
   freopen("output.txt","w",stdout);
#endif
   ios::sync_with_stdio( false);
   int N; scanf("%d",&N);
   REP(i,N) {
	  char s[N]; scanf("%s",s);
	  REP(j,N) {
		  b[i][j] = s[j]-'0';
		  colSum[j] += b[i][j];
	  }
   }

   int t; scanf("%d",&t);
   int score = 0;
   REP(j,t) {
	   int x,y; char d;
	   scanf("%d%d%c",&x,&y,&d);
	   int r =::doit(N-y-1,x,N);
	   score += r * (r+1) /2;
   }
   cout << score << endl;
   return 0;
}
