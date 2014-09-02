/*
 * 100009_C.cc
 *
 *  Created on: Sep 2, 2014
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

/*** Big Integer ****/
#define BIGINTBASE 10000
#define DECIMALDIGITSPERDIGIT 4
struct BigIntNode
{
	BigIntNode() : v(0), next(NULL) {}
	BigIntNode(int pv) : v(pv), next(NULL) {}
	int v;
	BigIntNode * next;
};

class BigInt
{
public:
	BigInt()
	{
		lsd = new BigIntNode();
	}

	BigInt(const BigInt & x)
	{
		lsd = new BigIntNode();
		BigIntNode * a = lsd;
		BigIntNode * b = x.lsd;
		a->v = b->v;
		while(b->next)
		{
			a = a->next = new BigIntNode();
			b = b->next;
			a->v = b->v;
		}
	}

	BigInt(const string & str)
	{
		lsd = new BigIntNode();
		BigIntNode * nd = lsd;
		for(int i = (int)str.size() - 1; i >= 0; i -= DECIMALDIGITSPERDIGIT)
		{
			for(int j = min(DECIMALDIGITSPERDIGIT - 1, i); j >= 0; j--)
			{
				nd->v *= 10;
				nd->v += str[i - j] - '0';
			}
			if(i - DECIMALDIGITSPERDIGIT >= 0) nd = nd->next = new BigIntNode();
		}
	}

	BigInt(int x)
	{
		lsd = new BigIntNode(x % BIGINTBASE);
		x /= BIGINTBASE;

		BigIntNode * nd = lsd;
		while(x)
		{
			nd = nd->next = new BigIntNode(x % BIGINTBASE);
			x /= BIGINTBASE;
		}
	}

	BigInt(long long x)
	{
		lsd = new BigIntNode(x % BIGINTBASE);
		x /= BIGINTBASE;

		BigIntNode * nd = lsd;
		while(x)
		{
			nd = nd->next = new BigIntNode(x % BIGINTBASE);
			x /= BIGINTBASE;
		}
	}

	~BigInt()
	{
		cleanUp();
	}

	BigInt & operator =(const BigInt & x)
	{
		cleanUp();
		lsd = new BigIntNode();
		BigIntNode * a = lsd;
		BigIntNode * b = x.lsd;
		a->v = b->v;
		while(b->next)
		{
			a = a->next = new BigIntNode();
			b = b->next;
			a->v = b->v;
		}
	}

	long long toLongLong () const
	{
		long long result = 0;
		long long m = 1;
		for(BigIntNode * nd = lsd; nd; nd = nd->next)
		{
			result += m * nd->v;
			m *= BIGINTBASE;
		}
		return result;
	}

	int toInt () const
	{
		int result = 0;
		int m = 1;
		for(BigIntNode * nd = lsd; nd; nd = nd->next)
		{
			result += m * nd->v;
			m *= BIGINTBASE;
		}
		return result;
	}

	string toString () const
	{
		if(lsd->next == NULL && lsd->v == 0) return "0";
		string result;
		for(BigIntNode * nd = lsd; nd; nd = nd->next)
		{
			int y = nd->v;
			for(int i = 0; i < DECIMALDIGITSPERDIGIT && (y || nd->next); i++)
			{
				result.insert(result.begin(), (char)('0' + y % 10));
				y /= 10;
			}
		}
		return result;
	}

	int compareTo(const BigInt & x) const
	{
		int result = 0;

		BigIntNode * a = lsd;
		BigIntNode * b = x.lsd;
		while(a && b)
		{
			if(a->v < b->v)
				result = -1;
			else if(b->v < a->v)
				result = 1;
			a = a->next;
			b = b->next;
		}
		if(a) result = 1;
		if(b) result = -1;
		return result;
	}

	bool operator ==(const BigInt & x) const { return compareTo(x) == 0; }
	bool operator !=(const BigInt & x) const { return compareTo(x) != 0; }
	bool operator < (const BigInt & x) const { return compareTo(x) < 0; }
	bool operator <=(const BigInt & x) const { return compareTo(x) <= 0; }
	bool operator > (const BigInt & x) const { return compareTo(x) > 0; }
	bool operator >=(const BigInt & x) const { return compareTo(x) >= 0; }

	BigInt operator +(const BigInt & x) const
	{
		BigInt result(*this);
		result += x;
		return result;
	}

	BigInt operator -(const BigInt & x) const
	{
		BigInt result(*this);
		result -= x;
		return result;
	}

	BigInt operator *(const BigInt & x) const
	{
		BigInt result;
		BigIntNode * a = lsd;
		BigIntNode * b = x.lsd;
		BigIntNode * c = result.lsd;
		while(b)
		{
			BigIntNode * ca = a;
			BigIntNode * cc = c;
			while(ca)
			{
				cc->v += b->v * ca->v;
				if(ca->next && cc->next == NULL) cc->next = new BigIntNode();
				ca = ca->next;
				cc = cc->next;
			}
			cc = c;
			int carry = 0;
			while(cc)
			{
				cc->v += carry;
				carry = cc->v / BIGINTBASE;
				cc->v %= BIGINTBASE;
				if(cc->next == NULL && carry) cc->next = new BigIntNode();
				cc = cc->next;
			}
			if(b->next && c->next == NULL) c->next = new BigIntNode();
			b = b->next;
			c = c->next;
		}
		return result;
	}

	BigInt operator /(const BigInt & x) const
	{
		BigInt powtwo = 1;

		stack<BigInt> pows;
		while(x * powtwo <= *this)
		{
			pows.push(powtwo);
			powtwo *= 2;
		}

		BigInt ret;
		while(!pows.empty())
		{
			if(x * (ret + pows.top()) <= *this)
			{
				ret += pows.top();
			}
			pows.pop();
		}

		return ret;
	}

	BigInt operator %(const BigInt & x) const
	{
		BigInt ret = *this - x * (*this / x);
		return ret;
	}

	BigInt & operator +=(const BigInt & x)
	{
		BigIntNode * a = lsd;
		BigIntNode * b = x.lsd;
		int carry = 0;
		while(b)
		{
			a->v += b->v + carry;
			carry = a->v / BIGINTBASE;
			a->v %= BIGINTBASE;
			if(a->next == NULL && (carry || b->next)) a->next = new BigIntNode();
			a = a->next;
			b = b->next;
		}
		while(carry)
		{
			a->v += carry;
			carry = a->v / BIGINTBASE;
			a->v %= BIGINTBASE;
			if(a->next == NULL && carry) a->next = new BigIntNode();
			a = a->next;
		}
		return *this;
	}

	BigInt & operator -=(const BigInt & x)
	{
		BigIntNode * a = lsd;
		BigIntNode * b = x.lsd;
		BigIntNode * c = a;
		while(a)
		{
			if(b) a->v -= b->v;
			if(a->v < 0)
			{
				a->next->v += (a->v + 1) / BIGINTBASE - 1;
				a->v = (BIGINTBASE * BIGINTBASE + a->v) % BIGINTBASE;
			}
			if(a->v) c = a;
			a = a->next;
			if(b) b = b->next;
		}
		BigIntNode * d = c->next;
		c->next = NULL;
		while(d)
		{
			c = d->next;
			delete d;
			d = c;
		}
	}
	BigInt & operator *=(const BigInt & x)
	{
		return *this = *this * x;
	}
	BigInt & operator /=(const BigInt & x)
	{
		return *this = *this / x;
	}
	BigInt & operator %=(const BigInt & x)
	{
		return *this = *this % x;
	}
	BigInt & operator ++() // Prefix  increment
	{
		operator +=(BigInt(1));
		return *this;
	}
	BigInt operator ++(int junk) // Postfix  increment
	{
		BigInt temp = *this;
		operator +=(BigInt(1));
		return temp;
	}
	BigInt & operator --() // Prefix  increment
	{
		operator -=(BigInt(1));
		return *this;
	}
	BigInt operator --(int junk) // Postfix  increment
	{
		BigInt temp = *this;
		operator -=(BigInt(1));
		return temp;
	}
private:
	BigIntNode * lsd;
	void cleanUp()
	{
		while(lsd)
		{
			BigIntNode * temp = lsd->next;
			delete lsd;
			lsd = temp;
		}
	}
};
std::ostream &operator <<(std::ostream & os, const BigInt & x)
{
	os << x.toString();
	return os;
}
/*** End ******/
typedef vector< vector<BigInt> > Matrix;
void mult(Matrix A, Matrix B, Matrix& C)
{
	REP(i,2) REP(j,2) {
		C[i][j] = 0;
		REP(k,2) C[i][j] = C[i][j] + (A[i][k] * B[k][j]);
//		cout << C[i][j] << ' ';
	}
}
void doit(BigInt N)
{
	if(N < 2) {
		cout << 1 << endl;
		return;
	}
	Matrix M(2);
	REP(i,2) M[i].resize(2);
	M[0][0] = 1;
	M[0][1] = 1;
	M[1][0] = 1;
	M[1][1] = 0;

	Matrix res(2);
	REP(i,2) res[i].resize(2);
	res[0][0] = 1; res[1][1] = 1;
	res[0][1] = 0; res[1][0] = 0;

	while(N > 0) {
		if(N % 2 > 0) mult(M,res,res);
		mult(M,M,M);
		N /= 2;
	}

	BigInt ret = res[0][1] + res[0][0];
	cout << ret << endl;
}

int main()
{
#ifdef LocalHost
   freopen("input.txt","r",stdin);
   freopen("output.txt","w",stdout);
#endif
   ios::sync_with_stdio( false);
   string _n; cin >> _n; //scanf("%s",_n);
   BigInt N = _n;
   doit(N-2);
   return 0;
}
