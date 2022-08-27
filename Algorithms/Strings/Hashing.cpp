// https://codeforces.com/blog/entry/60445
// https://codeforces.com/blog/entry/65819
// https://codeforces.com/blog/entry/60445?#comment-829689

// fast, but 2.3 * 10^18 hashspace
typedef unsigned long long ull;
namespace hashing {
  // 0 < ai < p < MOD
  const ull MOD = (1ULL << 61) - 1;
  const int N = 1e6;

  ull reduction(const ull a) {
    return (a & MOD) + (a >> 61);
  }

  ull add(ull a, const ull b) {
    return (a += b) >= MOD ? (a -= MOD) : a;
  }

  ull sub(ull a, const ull b) {
    return (a -= b) >= MOD ? (a += MOD) : a;
  }

  ull mod(const ull a) {
    return reduction(reduction(a) + 1) - 1;
  }

  ull mul(const ull a, const ull b) {
    const ull l1 = (uint32_t)a, h1 = a >> 32, l2 = (uint32_t)b, h2 = b >> 32;
    const ull l = l1 * l2, h = h1 * h2;
    const ull m = (l1 + h1) * (l2 + h2) - l - h;
    ull res = (l + (m << 32)) & MOD;
    res += (((l >> 32) + m) >> 29) + (h << 3) + 1;
    res = (res & MOD) + (res >> 61);
    return res - 1;
  }

  const vector<ull> POWS = []() {
    mt19937_64 gen(chrono::high_resolution_clock::now().time_since_epoch().count());
    ull p = uniform_int_distribution<ull>(MOD >> 1, MOD - 2)(gen);
    p |= 1;
    vector<ull> res(N + 1, 1);
    for (int i = 0; i < N; ++i) {
      res[i + 1] = mul(res[i], p);
    }
    return res;
  }();

  ull get(const string &s) {
    ull res = 0;
    for (char c : s) {
      res = add(mul(res, POWS[1]), c);
    }
    return res;
  }

  class HashedString {
  private:
    int sz;
    vector<ull> pref;

  public:
    HashedString(const string &s) {
      sz = (int)s.size();
      pref.resize(sz + 1, 0);
      for (int i = 0; i < sz; ++i) {
        pref[i + 1] = add(mul(pref[i], POWS[1]), s[i]);
      }
    }
    ull get(int l, int r) const {
      assert(l < r);
      // [l, r)
      return sub(pref[r], mul(pref[l], POWS[r - l]));
    }
  };
}

// slow, but 3.6 * 10^28 hashspace
namespace hashing {
  // 0 < ai < p < MOD
  typedef unsigned long long ull;
  typedef pair<int32_t, ull> hash;
  const int MOD = 2000000011;
  const int N = 1e6;

  hash operator*(hash a, hash b) {
    return hash(1ULL * a.first * b.first % MOD, a.second * b.second);
  }

  hash operator+(hash a, hash b) {
    return hash((0LL + a.first + b.first) % MOD, a.second + b.second);
  }

  hash operator-(hash a, hash b) {
    return hash((0LL + a.first - b.first + MOD) % MOD, a.second - b.second);
  }

  const vector<hash> POWS = []() {
    mt19937 gen(chrono::high_resolution_clock::now().time_since_epoch().count());
    int32_t p = uniform_int_distribution<int32_t>(MOD >> 1, MOD - 2)(gen);
    p |= 1;
    vector<hash> res(N + 1, hash(1, 1));
    for (int i = 0; i < N; ++i) {
      res[i + 1] = res[i] * hash(p, p);
    }
    return res;
  }();

  class HashedString {
  private:
    int sz;
    vector<hash> pref;

  public:
    HashedString(const string &s) {
      sz = (int)s.size();
      pref.resize(sz + 1, hash(0, 0));
      for (int i = 0; i < sz; ++i) {
        pref[i + 1] = pref[i] * POWS[1] + hash(s[i], s[i]);
      }
    }
    hash get(int l, int r) const {
      if (l >= r) {
        return hash(0, 0);
      }
      // [l, r)
      return pref[r] - pref[l] * POWS[r - l];
    }
  };
}