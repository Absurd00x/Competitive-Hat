#ifdef LOCAL_PROJECT
  #pragma GCC optimize("O0")
#else
  #pragma GCC optimize("O3")
#endif
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
#define int ll
#define double ld

#define all(x) std::begin(x),std::end(x)
#define rall(x) std::rbegin(x),std::rend(x)

const auto boostIO = []() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout << fixed;
  cout.precision(12);
  return 0;
}();



signed main() {
  int tests;
  while (tests --> 0) {
    read();
    solve();
    write();
  }
  cout.flush();
  return 0;
}
