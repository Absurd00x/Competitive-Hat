#include <bits/stdc++.h>
using namespace std;
template<typename F,typename S,typename T>struct Triple{F first;S second;T third;Triple(F a,S b,T c){first=a,second=b,third=c;}Triple(){first=F(0),second=S(0),third=T(0);}};
template<typename F,typename S,typename T>bool operator<(const Triple<F,S,T>&a,const Triple<F,S,T>&b){return(a.first<b.first?true:(a.first==b.first?(a.second<b.second?true:(a.second==b.second?a.third<b.third:false)):false));}
template<typename F,typename S,typename T>bool operator>(const Triple<F,S,T>&a,const Triple<F,S,T>&b){return(a.first>b.first?true:(a.first==b.first?(a.second>b.second?true:(a.second==b.second?a.third>b.third:false)):false));}
template<typename F,typename S,typename T>ostream&operator<<(ostream&os,const Triple<F,S,T>&a){os<<a.first<<' '<<a.second<<' '<<a.third;return os;}
template<typename F,typename S,typename T>istream&operator>>(istream&is,Triple<F,S,T>&a){is>>a.first>>a.second>>a.third;return is;}
template<typename F,typename S>ostream&operator<<(ostream&os,const pair<F,S>&a){os<<a.first<<' '<<a.second;return os;}
template<typename F,typename S>istream&operator>>(istream&is,pair<F,S>&a){is>>a.first>>a.second;return is;}
template<typename T>ostream&operator<<(ostream&os,const vector<T>&a){for(auto&v:a)os<<v<<' ';return os;}
template<typename T>istream&operator>>(istream&is,vector<T>&a){for(auto&v:a)is>>v;return is;}
template<typename A,typename B>void remin(A&a,B b){a=a<b?a:b;}
template<typename A,typename B>void remax(A&a,B b){a=a>b?a:b;}
using ll = long long;
using ull = unsigned long long;
using ui = unsigned int;
using ld = long double;
#define int ll
#define double ld
using pii = pair<int,int>;
using pdd = pair<double,double>;
using ti = Triple<int,int,int>;
using td = Triple<double,double,double>;
using vi = vector<int>;
using vb = vector<bool>;
using vd = vector<double>;
using vvi = vector<vi>;
using vvd = vector<vd>;
#define LONG_INF (ll(3e18))
#define INT_INF ((1<<30)-int32_t(1e7))
#define fi(f,t) for(int i=f;i<int(t);++i)
#define fj(f,t) for(int j=f;j<int(t);++j)
#define fk(f,t) for(int k=f;k<int(t);++k)
#define fq(n) for(int q=0;q<int(n);++q)
#define fs(s) for(auto&shift:s)
#define within_bounds(x,y,a,b) (x>-1&&y>-1&&x<a&&y<b)
#define CLEAR "\x1B[2J\x1B[H"
#define all(x) (x).begin(),(x).end()
#define debug(x) cerr<<__FUNCTION__<<':'<<__LINE__<<' '<<#x<<" = "<<x<<endl;
const int MOD=1e9+7;
const int PRECISION=7;
const double EPS = 1e-6;
const auto boostIO=[](){ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);cout<<fixed<<setprecision(PRECISION);return 0;}();
inline int mod(const int&a,const int&b=MOD){int r=a%b;return(r<0?r+b:r);}
inline int pown(int n,int power,const int modulo=MOD){int res=1;while(power){if(power&1)res=mod(res*n,modulo);n=mod(n*n,modulo);power>>=1;}return res;}

int32_t main()
{
  

  cout.flush();
  getchar();
  return 0;
}

