/* =============================================================
    Please, hack me, if you can. Solution is at the very bottom
   ============================================================= */

#include <bits/stdc++.h>
// ======================= Crucial parts =======================
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

// ======================== Joker's Trap =======================
#define int ll
#define double ld

// ========================= Constants =========================
const int32_t INT_INF = ((1 << 30) - int32_t(1e7));
const int64_t LONG_INF = (ll(3e18));
const int MOD = 1e9+7;
const int32_t PRECISION = 12;
const double EPS = 1e-9;
const double PI = std::acos(-1.0L);

// =========================== Macro ===========================
#define within_bounds(x,y,a,b) ((-1 < x && x < a) && (-1 < y && y < b))
#define CLEAR "\x1B[2J\x1B[H"
#define all(x) std::begin(x),std::end(x)
#define rall(x) std::rbegin(x),std::rend(x)
#define debug(x) std::cerr<<__FUNCTION__<<':'<<__LINE__<<' '<<#x<<" = "<<x<<endl;

// ========================= Functions =========================
ll mod(const ll&a, const ll&b=MOD) {
  ll r = a % b;
  return (r < 0 ? r + b : r);
}

ll pown(ll n, ll power, const ll modulo=MOD) {
  ll res = 1;
  while(power > 0) {
    if(power & 1LL)
      res = mod(res * n, modulo);
    n = mod(n * n, modulo);
    power >>= 1;
  }
  return res;
}

void remin(auto &a, auto b){a = (a < b ? a : b);}
void remax(auto &a, auto b){a = (a > b ? a : b);}

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

int rand_int(int from, int to) {
  // On my computer RAND_MAX is 2147483647
  return from + (rand() % static_cast<int>(to - from + 1));
}

const auto desync = [](){
  std::ios_base::sync_with_stdio(0);
  return 0;
}();

// ================= ostream / istream wrappers ================
class Printer {
private:
  std::ostream &out;
  int32_t get_width(int n) {
    int32_t width = n < 0;
    while(n)
      ++width, n /= 10;
    return width;
  }

  int32_t get_width(const string&s) {
    return int32_t(s.size());
  }

  int32_t get_width(double f) {
    // integer part includes signum
    // +1 because point separator
    return get_width((int)f) + PRECISION + 1;
  }

  template<typename F, typename S>
  int32_t get_width(const pair<F, S> &p) {
    return get_width(p.first) + get_width(p.second) + 1;
  }

  template<typename... Args, size_t... N>
  int32_t __get_width(const tuple<Args...> &t, std::index_sequence<N...>) {
    return (int32_t)(get_width(std::get<N>(t)) + ...);
  }

  template<typename... Args>
  int32_t get_width(const tuple<Args...> &t) {
    return int32_t(__get_width(t, std::make_index_sequence<sizeof...(Args)>{}));
  }

  template<typename... Args, size_t... N>
  static Printer &print_tuple(Printer &os, const tuple<Args...> &t, std::index_sequence<N...>) {
    ((os << (N ? " " : "") << std::get<N>(t)), ...);
    return os;
  }

  static void __width(Printer &stream, int32_t width_diff) {
    while(width_diff --> 0)
      stream << ' ';
  }

public:
  Printer(std::ostream &out_=std::cout, bool tie=true):out(out_) {
    if (tie)
      out.tie(0);
    out << std::fixed << std::setprecision(PRECISION);
  }
  void print_range(auto begin, auto end,
                   string sep=" ",
                   string finish="\n",
                   const int32_t width=1) {
    for(auto elem = begin; elem != end; ++elem) {
        if (elem != begin)
          (*this) << sep;
        __width(*this, width - get_width(*elem));
        (*this) << (*elem);
    }
    (*this) << finish;
  }

  bool yn(bool v,string&&y="Yes",string&&n="No"){
    (*this) << (v ? y : n) << '\n';
    return v;
  }

  void print_matrix(auto begin,auto end,
                    string sep=" ",
                    string finish="\n") {
    int32_t max_width = 1;
    for(auto cur_row = begin; cur_row != end; ++cur_row)
      for(auto &elem : (*cur_row))
        remax(max_width, get_width(elem));
    for(auto cur_row = begin; cur_row != end; ++cur_row)
      print_range(all(*cur_row), sep, finish, max_width);
  }

  void flush() {
    out.flush();
  }

  template<typename T>
  Printer &operator<<(const T &val) {
    out << val;
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
  static Scanner &read_tuple(Scanner &is, tuple<Args...> &t, std::index_sequence<N...>) {
    ((is >> std::get<N>(t)), ...);
    return is;
  }

public:
  Scanner(std::istream &in_=std::cin, bool tie=true):in(in_) {
    if (tie)
      in.tie(0);
  }

  template<typename T>
  friend Scanner &operator>>(Scanner &is, vector<T>&v) {
    for(auto &elem : v)
      is >> elem;
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

// ========================= Shortcuts =========================
auto& endl = Printer::endl;
typedef unsigned long long ull;
typedef pair<int,int>pii;
typedef pair<double,double>pdd;
typedef tuple<int,int,int>ti;
typedef tuple<double,double,double>td;
typedef vector<int>vi;
typedef vector<bool>vb;
typedef vector<double>vd;
typedef vector<vi>vvi;
typedef vector<vd>vvd;

// =============== Wrapped input / output streams ==============
Scanner in;
Printer out;

// ========================= Variables =========================
typedef int ans_t;
ans_t ans = 42;


// ============== Behavior manipulating constants ==============
const bool BRUTE_CHECK = false;
const bool MULTITESTS = true;

// ================== Input / output functions =================
void read() {
  
}

void write() {
  
  #ifdef LOCAL_PROJECT
    out.flush();
  #endif
}

// ========================= Prototypes ========================
ans_t solve();
void gen();
ans_t brute();

// =========================== Stress ==========================
bool stress() {
  static int cnt = 0;
  /*
  ans_t mya = solve();
  ans = 42;
  ans_t cora = brute();
  if (mya != cora) {
    out << "Wrong answer on test #" << cnt << '\n';

    // print test here

    out << "My answer:      " << mya << '\n';
    out << "Correct answer: " << cora << endl;
    return false;
  }
  */
  out << "Passed test #" << ++cnt << endl;
  return true;
}

// ============================ Main ===========================

int32_t main()
{
  const string TEST_SEP(20,'=');

  if(BRUTE_CHECK) {
    do {
      gen();
    } while(stress());
  } else {
    int tests = 1;
    if (MULTITESTS)
      in >> tests;
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

// ===================== Actual coding part ====================
ans_t solve() {
  

  return ans = 42;
}

