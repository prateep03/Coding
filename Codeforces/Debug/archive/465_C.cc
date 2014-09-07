/*
 * 465_C.cc
 *
 *  Created on: Sep 7, 2014
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

string get(string pre, int n, int p)
{
	for(int i = pre.SZ-1; i >= 0; i--) {
		if(i-1 >= 0 && pre[i-1] == pre[i]) return "";
		if(i-2 >= 0 && pre[i-2] == pre[i]) return "";
	}
	if(pre.SZ == n) return pre;
	if(p == 1) return "";
	if(p == 2) {
		if(n == 2) return (pre[0] == 'a' ? "ab" : "ba");
		else return "";
	}
	string res = pre;
	FOR(l,pre.SZ,n) for(char ch = 'a'; ch <= 'c'; ch++) {
		if(l-1 >= 0 && ch == res[l-1]) continue;
		if(l-2 >= 0 && ch == res[l-2]) continue;
		res += ch;
		break;
	}
	return res;
}
int main()
{
#ifdef LocalHost
   freopen("input.txt","r",stdin);
   freopen("output.txt","w",stdout);
#endif
   ios::sync_with_stdio( false);
   int n,p; cin >> n >> p;
   string s; cin >> s;

   for(int i = s.SZ-1; i >= 0; i--) {
	   for(char c = (char)(s[i]+1); c < 'a'+p; c++) {
		   string ret = ::get(s.substr(0,i)+c, n, p);
		   if(ret.SZ > 0) {
			   cout << ret << endl;
			   goto ext;
		   }
	   }
   }
   cout << "NO\n";
 ext:
   return 0;
}
