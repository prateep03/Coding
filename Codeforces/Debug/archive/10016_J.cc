/*
 * 10016_J.cc
 *
 *  Created on: Aug 27, 2014
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

#define LocalHost

typedef struct people {
	string name;
	int d;

	people(string _s, int _d) : name(_s), d(_d) {}

	bool const operator < (people o) const { return d > o.d; }
} people;

vector< people > boys;
vector<people> girls;

int getFromGirls(int v, int s, int e)
{
	if(s == e-1) return e;
	int l = s, h = e;
	while(l+1 < h) {
		int m = (l+h)/2;
		if(girls[m].d >= v) l = m;
		else h = m;
	}
	return min(e,h+1);
}

int getFromBoys(int v, int s, int e)
{
	if(s == e-1) return e;
	int l = s, h = e;
	while(l+1 < h) {
		int m = (l+h)/2;
		if(boys[m].d >= v) l = m;
		else h = m;
	}
	return min(e,h+1);
}

int getPos(int v, int s, int e, int t)
{
	if(t == 0) return ::getFromGirls(v,s,e);
	else if(t == 1) return ::getFromBoys(v,s,e);
}
int main()
{
#ifdef LocalHost
   freopen("taxi.in","r",stdin);
//   freopen("output.txt","w",stdout);
#endif
   ios::sync_with_stdio( false);
   int n; cin >> n;
   REP(i,n) {
	   string s; cin >> s;
	   int d; cin >> d;
	   boys.PB(people(s,d));
   }
   int m; cin >> m;
   REP(i,m) {
	   string s; cin >> s;
	   int d; cin >> d;
	   girls.PB(people(s,d));
   }
   sort(ALL(boys));
   sort(ALL(girls));

   int total = (int) ceil(1.f*(n+m)/4);
   VS taxi[total];
   int* curTime = new int[total];
   int b = 0, g = 0, k = 0, res = 0;
   {
//   while(b < n && g < m) {
//	   if(boys[b].d > girls[g].d) {
//		   int f = ::getPos(girls[g].d, b, n, 1);
//		   if(f-b > 3) f = min(n,b+3);
//		   taxi[k].clear();
//		   taxi[k].PB(girls[g].name);
//		   FOR(i,b,f) taxi[k].PB(boys[i].name);
//		   res += boys[b].d;
//		   b = f; g++;
//	   } else if(boys[b].d < girls[g].d) {
//		   int f = ::getPos(boys[b].d, g, m, 0);
//		   if(f-g > 3) f = min(m,g+3);
//		   taxi[k].clear();
//		   taxi[k].PB(boys[b].name);
//		   FOR(i,g,f) taxi[k].PB( girls[i].name );
//		   res += girls[g].d;
//		   g = f; b++;
//	   }
//	   ++k;
////	   cout << b << ' ' << g << ' ' << k << endl;
//   }
   }
   // distribute boys
   while(b < n) {
	   int l = b + (int) ceil(1.f*n/total);
	   FOR(i,b,min(n,l)) taxi[k].PB(boys[i].name);
	   curTime[k] = boys[b].d;
	   k++;
	   b = l;
   }
   assert(k == total);
   k = 0;
   /* greedy ??? */
   REP(g,m) {
	   int ok = 0;

	   REP(t,total) if(curTime[t] >= girls[g].d && taxi[t].SZ < 4) {
		   ok = 1;
		   taxi[t].PB(girls[g].name);
		   break;
	   }

	   if(!ok) {
		   REP(t,total) if(taxi[t].SZ < 4) {
			   taxi[t].PB(girls[g].name);
			   checkmax(curTime[t], girls[g].d);
			   break;
		   }
	   }
   }
   REP(i,total) res += curTime[i];

   // O/P
   cout << res << "\n" << total << "\n";
   REP(i,total) {
	   cout << "Taxi " << (i+1) << ": ";
	   REP(j,taxi[i].SZ-1) {
		   cout << taxi[i][j];
		   if(j == taxi[i].SZ-2) cout << " and ";
		   else cout << ", ";
	   }
	   cout << taxi[i][taxi[i].SZ-1] << ".\n";
   }
   return 0;
}
