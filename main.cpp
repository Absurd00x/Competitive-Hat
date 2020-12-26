//#pragma GCC optimize("O")
#include <bits/stdc++.h>
using namespace std;
template<typename F,typename S,typename T>struct Triple{F first;S second;T third;Triple(F a,S b,T c){first=a,second=b,third=c;}Triple(){first=F(0),second=S(0),third=T(0);}};
template<typename F,typename S,typename T>bool operator<(const Triple<F,S,T>&a,const Triple<F,S,T>&b){return(a.first<b.first?true:(a.first==b.first?(a.second<b.second?true:(a.second==b.second?a.third<b.third:false)):false));}
template<typename F,typename S,typename T>bool operator>(const Triple<F,S,T>&a,const Triple<F,S,T>&b){return(a.first>b.first?true:(a.first==b.first?(a.second>b.second?true:(a.second==b.second?a.third>b.third:false)):false));}
template<typename F,typename S,typename T>ostream&operator<<(ostream&os,const Triple<F,S,T>&a){os<<a.first<<' '<<a.second<<' '<<a.third;return os;}
template<typename Fi,typename Se,typename Th,typename Fo>struct Quad{Fi first;Se second;Th third;Fo fourth;Quad(Fi a,Se b,Th c,Fo d){first=a,second=b,third=c,fourth=d;}Quad(){first=Fi(0),second=Se(0),third=Th(0),fourth=Fo(0);}};
template<typename Fi,typename Se,typename Th,typename Fo>bool operator<(const Quad<Fi,Se,Th,Fo>&a,const Quad<Fi,Se,Th,Fo>&b){return(a.first<b.first?true:(a.first==b.first?(a.second<b.second?true:(a.second==b.second?(a.third<b.third?true:(a.third==b.third?a.fourth<b.fourth:false)):false)):false));}
template<typename Fi,typename Se,typename Th,typename Fo>ostream&operator<<(ostream&os,const Quad<Fi,Se,Th,Fo>&a){os<<a.first<<' '<<a.second<<' '<<a.third<<' '<<a.fourth;return os;}
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef long double ld;
#define int ll
#define double ld
typedef pair<int,int>pii;
typedef pair<double,double>pdd;
typedef Triple<int,int,int>ti;
typedef Triple<double,double,double>td;
typedef Quad<int,int,int,int>qi;
typedef vector<int>vi;
typedef vector<double>vd;
typedef vector<vi>vvi;
typedef vector<vd>vvd;
#define LONG_INF (ll(3e18))
#define INT_INF ((1<<30)-int32_t(1e7))
#define fi(f,t) for(int i=f;i<int(t);++i)
#define fj(f,t) for(int j=f;j<int(t);++j)
#define fk(f,t) for(int k=f;k<int(t);++k)
#define fq(n) for(int q=0;q<int(n);++q)
#define fs(s) for(auto&shift:s)
#define within_bounds(x,y,a,b) (x>-1&&y>-1&&x<a&&y<b)
#define CLEAR "\x1B[2J\x1B[H"
const int MOD=1e9+7;
const int PRECISION=7;
const double EPS = 1e-6;
const vector<pii>SHIFTS={{0,1},{-1,0},{0,-1},{1,0}};
const vector<pii>KING_SHIFTS={{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1},{1,0},{1,1}};
const vector<pii>KNIGHT_SHIFTS={{-1,2},{-2,1},{-2,-1},{-1,-2},{1,-2},{2,-1},{2,1},{1,2}};
const auto boostIO=[](){ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);cout<<fixed<<setprecision(PRECISION);return 0;}();
inline int mod(const int&a,const int&b=MOD){int r=a%b;return(r<0?r+b:r);}
inline int pown(int n,int power,const int modulo=MOD){int res=1;while(power){if(power&1)res=mod(res*n,modulo);n=mod(n*n,modulo);power>>=1;}return res;}

int32_t main()
{
  

  cout.flush();
  getchar();
  return 0;
}


