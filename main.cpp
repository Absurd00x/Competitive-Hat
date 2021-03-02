#include <bits/stdc++.h>
#define endl std::endl
#define pair std::pair
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
template<typename T>std::ostream&operator<<(std::ostream&os,const vector<T>&a){size_t sz=a.size()-1;for(size_t i=0;i<sz;++i)os<<a[i]<<' ';os<<a.back()<<'\n';return os;}
template<typename T>std::ostream&operator<<(std::ostream&os,const std::set<T>&s){auto end=std::prev(s.end());for(auto it=s.begin();it!=end;++it)os<<(*it)<<' ';os<<(*end)<<'\n';return os;}
template<typename T>std::istream&operator>>(std::istream&is,vector<T>&a){for(auto&v:a)is>>v;return is;}
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
void remin(auto&a,auto b){a=a<b?a:b;}
void remax(auto&a,auto b){a=a>b?a:b;}
ll mod(const ll&a,const ll&b=MOD){ll r=a%b;return(r<0?r+b:r);}
ll pown(ll n,ll power,const ll modulo=MOD){ll res=1;while(power){if(power&1)res=mod(res*n,modulo);n=mod(n*n,modulo);power>>=1;}return res;}
int rand_int(int from,int to){return from+(rand()%static_cast<int>(to-from+1));}
string&yn(bool v,string&&y="Yes",string&&n="No"){return(v?y:n);}

std::istream&in=std::cin;
std::ostream&out=std::cout;
const auto boostIO=[](){std::ios_base::sync_with_stdio(0);in.tie(0);return 0;}();
const auto editIO=[](){out<<std::fixed<<std::setprecision(PRECISION);return 0;}();

// variables

// variables
const bool BRUTE_CHECK = false;

void read() {
  
}

auto solve() {
  
}

void write() {
  
  #ifdef LOCAL_PROJECT
    out.flush();
  #endif
}

void gen(){}
auto brute(){}
bool stress(){return false;}

int32_t main()
{
  const string TEST_SEP(20,'=');

  if(BRUTE_CHECK)
    do{gen();}while(stress());
  else {
    int tests;in>>tests;
    while(tests--) {
      read();
      #ifdef LOCAL_PROJECT
        out << TEST_SEP << endl;
      #endif
      solve();
      write();
    }
  }

  out.flush();
  #ifdef LOCAL_PROJECT
    getchar();
  #endif
  return 0;
}

