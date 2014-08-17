/*
 * 459_A.cc
 *
 *  Created on: Aug 15, 2014
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

//#define LocalHost
bool check(int x1, int y1, int x2, int y2)
{
	return (x1 == x2 || y1 == y2 || abs(x1-x2) == abs(y1-y2));
}
int main()
{
#ifdef LocalHost
   freopen("input.txt","r",stdin);
   freopen("output.txt","w",stdout);
#endif
   ios::sync_with_stdio( false);
   int x1,y1,x2,y2; scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
   if(x1 > x2) {
	   swap(x1,x2); swap(y1,y2);
   }
   if(!check(x1,y1,x2,y2)) {
	   cout << "-1\n";
	   return 0;
   }
   int dx = x2-x1, dy = abs(y1-y2);
   if(x1 == x2) {
	   cout << x1+dy << ' ' << max(y1,y2) << ' ' << x1+dy << ' ' << min(y1,y2) << endl;
   } else if(y1 == y2) {
	   cout << x1 << ' ' << y1+dx << ' ' << x2 << ' ' << y1+dx << endl;
   } else {
	   int miny = min(y1,y2), maxy = max(y1,y2);
	   if(y1 > y2) {
		   cout << x1 << ' ' << miny << ' ' << x2 << ' ' << maxy << endl;
	   } else {
		   cout << x1 << ' ' << maxy << ' ' << x2 << ' ' << miny << endl;
	   }
   }
   return 0;
}
