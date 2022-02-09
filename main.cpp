#include <bits/stdc++.h>
namespace __HAT__ {
  /* =============================================================
      Please, hack me, if you can. Solution is at the very bottom
     ============================================================= */
  namespace __CRUTIAL__ {
    template<typename F, typename S>
    using pair = std::pair<F,S>;

    template<typename ...Args>
    using tuple = std::tuple<Args...>;

    template<typename T>
    using vector = std::vector<T>;

    using string = std::string;

    typedef long long ll;
    typedef long double ld;
    typedef unsigned int ui;
  } using namespace __CRUTIAL__;
  namespace __JOKER__ {
    #define int ll
    #define double ld
  } using namespace __JOKER__;
  namespace __CONSTANTS__ {
    const int32_t IINF = ((1 << 30) - int32_t(1e7));
    const int64_t LINF = (ll(3e18));
    const int INF = (sizeof(int) == 4 ? IINF : LINF);
    const int MOD = 1e9 + 7;
    const int ZERO = 0;
    const int ONE = 1;
    const int TWO = 2;
    const int NONE = -42691337;
    const string ENDL = "\n";
    const string UASCII = "abcdefghijklmnopqrstuvwxyz";
    const string LASCII = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const string DEC = "0123456789";
    const string HEX = "0123456789ABCDEF";
    const vector<pair<int, int>> SHIFTS = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
    const int SEED = 42;
    // can't be const
    std::mt19937_64 RNGESUS(SEED);
    const int32_t PRECISION = 12;
    const double EPS = 1e-9;
    const double PI = std::acos((double)-ONE);
  } using namespace __CONSTANTS__;
  namespace __MACROS__ {
    #define ir(x,a,b) (a <= x && x < b)
    #define ii(x,a,b) (a < x && x < b)
    #define is(x,a,b) (a <= x && x <= b)
    #define wb(x,y,a,b) ((-1 < x && x < a) && (-1 < y && y < b))
    #define gbit(x,a) ((x >> a) & 1)
    #define cbit(x) (__builtin_popcountll(x))
    #define pub push_back
    #define pob pop_back
    #define puf push_front
    #define pof pop_front
    #define eb emplace_back
    #define ff first
    #define ss second
    #define ub upper_bound
    #define lb lower_bound
    #define tos std::to_string
    #define np std::next_permutation
    #define bf std::binary_search
    #define all(x) std::begin(x),std::end(x)
    #define rall(x) std::rbegin(x),std::rend(x)
  } using namespace __MACROS__;
  namespace __FUNCTIONS__ {
    bool remin(auto &a, auto b) {
      if (a > b) {
        a = b;
        return true;
      }
      return false;
    }

    bool remax(auto &a, auto b) {
      if (a < b) {
        a = b;
        return true;
      }
      return false;
    }

    template<typename T>
    T minimum(T x) {
      return x;
    }

    template<typename T, typename... Pack>
    auto minimum(T x, Pack... p) {
      using common = typename std::common_type<T, Pack...>::type;
      return std::min((common)x, (common)minimum(p...));
    }

    template<typename T>
    T maximum(T x) {
      return x;
    }

    template<typename T, typename... Pack>
    auto maximum(T x, Pack... p) {
      using common = typename std::common_type<T, Pack...>::type;
      return std::max((common)x, (common)maximum(p...));
    }

    template<typename T>
    int msb(T num) {
      return (num == 0 ? 0 : std::__lg(num));
    }

    int rint(int from, int to) {
      std::uniform_int_distribution<int> distribution(from, to);
      return distribution(RNGESUS);
    }

    void shuffle(auto begin, auto end) {
      std::shuffle(begin, end, RNGESUS);
    }

    const auto desync = []() {
      std::ios_base::sync_with_stdio(0);
      return 0;
    }();

    ll mod(ll a, ll b=MOD) {
      ll r = (a % b);
      return (r < 0 ? r + b : r);
    }

    ll pown(ll n, ll power, const ll modulo=MOD) {
      ll res = 1;
      while (power > 0) {
        if (power & 1LL) {
          res = mod(res * n, modulo);
        }
        n = mod(n * n, modulo);
        power >>= 1;
      }
      return res;
    }

    ll powb(int power) {
      return 1LL << power;
    }

    ll madd(ll &me, ll num, const ll modulo=MOD) {
      return me = mod(me + num, modulo);
    }

    ll msub(ll &me, ll num, const ll modulo=MOD) {
      return me = mod(me - num, modulo);
    }

    ll mmul(ll &me, ll num, const ll modulo=MOD) {
      return me = mod(me * num, modulo);
    }

    ll mdiv(ll &me, ll den, const ll modulo=MOD) {
      return me = mmul(me, pown(den, MOD - 2), modulo);
    }

    template<typename C>
    int unique(C &container) {
      std::sort(all(container));
      auto it = std::unique(all(container));
      int duplicates = container.end() - it;
      container.erase(it, std::end(container));
      return duplicates;
    }

    template<typename C>
    int ssize(C &container) {
      return (int)container.size();
    }

    ll calc_ap(ll start, ll end, ll num, const ll modulo=LINF) {
      return mod((start + end) * num / 2, modulo);
    }
  } using namespace __FUNCTIONS__;
  class Printer {
  private:
    std::ostream &out;

    template<typename... Args, size_t... N>
    static Printer &print_tuple(Printer &os,
                                const tuple<Args...> &t,
                                std::index_sequence<N...>) {
      ((os << (N ? " " : "") << std::get<N>(t)), ...);
      return os;
    }

  public:
    Printer(std::ostream &out_=std::cout, bool tie=true):out(out_) {
      if (tie) {
        out.tie(0);
      }
      out << std::fixed << std::setprecision(PRECISION);
    }
    void print(auto begin, auto end,
                     string sep="\n",
                     string finish="\n") {
      for (auto elem = begin; elem != end; ++elem) {
        if (elem != begin) {
          (*this) << sep;
        }
        (*this) << (*elem);
      }
      (*this) << finish;
    }

    bool yn(bool v, string&&y="Yes", string&&n="No"){
      (*this) << (v ? y : n) << '\n';
      return v;
    }

    void flush() {
      out.flush();
    }

    template<typename T>
    Printer &operator<<(const T &val) {
      out << val;
      return *this;
    }

    template<typename T>
    Printer &operator<<(const vector<T> &v) {
      print(v.begin(), v.end(), " ", "");
      return *this;
    }

    Printer &operator<<(const string &s) {
      out << s;
      return *this;
    }

    template<typename F, typename S>
    Printer &operator<<(const pair<F, S> &a){
      (*this) << a.first << ' ' << a.second;
      return *this;
    }

    template<typename... Args>
    friend Printer &operator<<(Printer &os, const tuple<Args...> &t) {
      return print_tuple(os, t, std::make_index_sequence<sizeof...(Args)>{});
    }

    typedef Printer &(*PrinterManipulator)(Printer&);
    Printer &operator<<(PrinterManipulator manip) {
      return manip(*this);
    }

    static Printer &endl(Printer &stream) {
      stream << '\n';
      stream.flush();
      return stream;
    }
  };
  class Scanner {
  private:
    std::istream &in;

    template<typename... Args, size_t... N>
    static Scanner &read_tuple(Scanner &is,
                               tuple<Args...> &t,
                               std::index_sequence<N...>) {
      ((is >> std::get<N>(t)), ...);
      return is;
    }

  public:
    Scanner(std::istream &in_=std::cin, bool tie=true):in(in_) {
      if (tie) {
        in.tie(0);
      }
    }

    template<typename T>
    friend Scanner &operator>>(Scanner &is, vector<T>&v) {
      for (auto &elem : v) {
        is >> elem;
      }
      return is;
    }

    template<typename F,typename S>
    friend Scanner &operator>>(Scanner &is, pair<F, S> &a){
      is >> a.first >> a.second;
      return is;
    }

    template<typename... Args>
    friend Scanner &operator>>(Scanner &is, tuple<Args...> &t) {
      return read_tuple(is, t, std::make_index_sequence<sizeof...(Args)>{});
    }

    template<typename T>
    Scanner &operator>>(T &val) {
      in >> val;
      return *this;
    }
  };
  namespace __SHORTCUTS__ {
    auto& endl = Printer::endl;
    typedef unsigned long long ull;
    typedef pair<int,int>pii;
    typedef pair<double,double>pdd;
    typedef tuple<int,int,int>ti;
    typedef tuple<int,int,int,int>qi;
    typedef tuple<double,double,double>td;
    typedef vector<int>vi;
    typedef vector<pii>vpii;
    typedef vector<ti>vti;
    typedef vector<bool>vb;
    typedef vector<double>vd;
    typedef vector<string>vs;
    typedef vector<vi>vvi;
    typedef vector<vd>vvd;
  } using namespace __SHORTCUTS__;
} using namespace __HAT__;
namespace __IO_WRAPPERS__ {
  Scanner in;
  Printer out;
} using namespace __IO_WRAPPERS__;
namespace __DATA_STRUCTURE__ {

} using namespace __DATA_STRUCTURE__;
namespace __VARIABLES__ {
  typedef int ans_t;
  ans_t ans;
} using namespace __VARIABLES__;
namespace __BEHAVIOR__ {
  const bool BSOLVE = false;
  const bool BCHECK = false;
  const bool MULTITESTS = true;
} using namespace __BEHAVIOR__;
namespace __INTERACTIVE__ {
  /*
  void offask() {
    
  }

  void onask() {
    
  }

  void ask() {
    return (BCHECK ? offask() : onask());
  }

  void guess() {
    if (BCHECK) {
      return;
    }
  }
  */
} using namespace __INTERACTIVE__;
namespace __IO__ {
  void read() {
    
  }

  void write() {
    
    #ifdef LOCAL_PROJECT
      out.flush();
    #endif
  }
} using namespace __IO__;
namespace __PROTOTYPES__ {
  ans_t solve();
  void gen();
  ans_t brute();
} using namespace __PROTOTYPES__;
bool stress() {
  static int cnt = 0;
  /*
  ans_t mya = solve();
  ans = 42;
  ans_t cora = brute();
  ++cnt;
  if (mya != cora) {
    out << "Wrong answer on test #" << cnt << ENDL;
    if (MULTITESTS) {
      out << '1' << ENDL;
    }

    // print test here

    out << "My answer:      " << mya << ENDL;
    out << "Correct answer: " << cora << endl;
    return false;
  }
  */
  out << "Passed test #" << cnt << endl;
  return true;
}
int32_t main() {
  auto start = clock();
  const string TEST_SEP(20,'=');
  if (BCHECK) {
    do {
      gen();
    } while (stress());
  } else {
    int tests = 1;
    if (MULTITESTS) {
      in >> tests;
    }
    while (tests--) {
      read();
      #ifdef LOCAL_PROJECT
        out << TEST_SEP << endl;
      #endif
      if (BSOLVE) {
        brute();
      } else {
        solve();
      }
      write();
    }
  }
  out.flush();
  auto finish = clock();
  #ifdef LOCAL_PROJECT
    out << TEST_SEP << '\n';
    out << "Execution time: " << ld(finish - start) / CLOCKS_PER_SEC << endl;
    getchar();
  #endif
  return 0;
}
// ===================== Actual coding part ====================
void __PROTOTYPES__::gen() {}

ans_t __PROTOTYPES__::brute() {return ans;}

ans_t __PROTOTYPES__::solve() {
  
  return ans;
}
