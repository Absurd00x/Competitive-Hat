#include <bits/stdc++.h>
#define endl std::endl
#define pair std::pair
#define sort stable_sort
#define string std::string
#define swap std::swap
#define vector std::vector
template<typename F,typename S,typename T>struct Triple{F first;S second;T third;Triple(F a,S b,T c){first=a,second=b,third=c;}Triple(){first=F(0),second=S(0),third=T(0);}};
template<typename F,typename S,typename T>bool operator<(const Triple<F,S,T>&a,const Triple<F,S,T>&b){return(a.first<b.first?true:(a.first==b.first?(a.second<b.second?true:(a.second==b.second?a.third<b.third:false)):false));}
template<typename F,typename S,typename T>bool operator>(const Triple<F,S,T>&a,const Triple<F,S,T>&b){return(a.first>b.first?true:(a.first==b.first?(a.second>b.second?true:(a.second==b.second?a.third>b.third:false)):false));}
template<typename F,typename S,typename T>std::ostream&operator<<(std::ostream&os,const Triple<F,S,T>&a){os<<a.first<<' '<<a.second<<' '<<a.third<<'\n';return os;}
template<typename F,typename S,typename T>std::istream&operator>>(std::istream&is,Triple<F,S,T>&a){is>>a.first>>a.second>>a.third;return is;}
template<typename F,typename S>std::ostream&operator<<(std::ostream&os,const pair<F,S>&a){os<<a.first<<' '<<a.second<<'\n';return os;}
template<typename F,typename S>std::istream&operator>>(std::istream&is,pair<F,S>&a){is>>a.first>>a.second;return is;}
template<typename T>std::ostream&operator<<(std::ostream&os,const vector<T>&a){for(auto&v:a)os<<v<<' ';os<<'\n';return os;}
template<typename T>std::ostream&operator<<(std::ostream&os,const std::set<T>&s){for(auto&v:s)os<<v<<' ';os<<'\n';return os;}
template<typename T>std::istream&operator>>(std::istream&is,vector<T>&a){for(auto&v:a)is>>v;return is;}
template<typename A,typename B>void remin(A&a,B b){a=a<b?a:b;}
template<typename A,typename B>void remax(A&a,B b){a=a>b?a:b;}
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
typedef vector<int>vi;
typedef vector<bool>vb;
typedef vector<double>vd;
typedef vector<vi>vvi;
typedef vector<vd>vvd;
#define fi(f,t) for(int i=f;i<int(t);++i)
#define fj(f,t) for(int j=f;j<int(t);++j)
#define fk(f,t) for(int k=f;k<int(t);++k)
#define fv(f,t) for(int v=f;v<int(t);++v)
#define fq(n) for(int q=0;q<int(n);++q)
#define within_bounds(x,y,a,b) (x>-1&&y>-1&&x<a&&y<b)
#define CLEAR "\x1B[2J\x1B[H"
#define all(x) std::begin(x),std::end(x)
#define rall(x) std::rbegin(x),std::rend(x)
#define debug(x) std::cerr<<__FUNCTION__<<':'<<__LINE__<<' '<<#x<<" = "<<x<<endl;
const int32_t INT_INF=((1<<30)-int32_t(1e7));
const int64_t LONG_INF=(ll(3e18));
const int MOD=1e9+7;
const int PRECISION=7;
const double EPS = 1e-6;
const double PI = std::acos(-1.0L);
inline int mod(const int&a,const int&b=MOD){int r=a%b;return(r<0?r+b:r);}
inline int pown(ll n,ll power,const ll modulo=MOD){int res=1;while(power){if(power&1)res=mod(res*n,modulo);n=mod(n*n,modulo);power>>=1;}return res;}

std::istream&in=std::cin;
std::ostream&out=std::cout;
const auto boostIO=[](){std::ios_base::sync_with_stdio(0);in.tie(0);return 0;}();
const auto editIO=[](){out<<std::fixed<<std::setprecision(PRECISION);return 0;}();

// variables

// variables

void read() {
  
}

auto solve() {
  
}

void write() {
  
  #ifdef LOCAL_PROJECT
    out.flush();
  #endif
}

int32_t main()
{
  int t;in>>t;
  fq(t) {
    read();
    solve();
    write();
  }

  out.flush();
  #ifdef LOCAL_PROJECT
    getchar();
  #endif
  return 0;
}

