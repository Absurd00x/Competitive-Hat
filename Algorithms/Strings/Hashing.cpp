// https://codeforces.com/blog/entry/60445
// https://codeforces.com/blog/entry/65819
// https://codeforces.com/blog/entry/60445?#comment-829689

// fast, but 2.3 * 10^18 hashspace
namespace hashing {
  // 0 < ai < p < MOD
  typedef unsigned long long hash_t;
  const hash_t MOD = (1ULL << 61) - 1;
  const int32_t N = 1e6;

  hash_t reduction(const hash_t a) {
    return (a & MOD) + (a >> 61);
  }

  hash_t add(hash_t a, const hash_t b) {
    return (a += b) >= MOD ? (a -= MOD) : a;
  }

  hash_t sub(hash_t a, const hash_t b) {
    return (a -= b) >= MOD ? (a += MOD) : a;
  }

  hash_t mod(const hash_t a) {
    return reduction(reduction(a) + 1) - 1;
  }

  hash_t mul(const hash_t a, const hash_t b) {
    const hash_t l1 = (uint32_t)a, h1 = a >> 32, l2 = (uint32_t)b, h2 = b >> 32;
    const hash_t l = l1 * l2, h = h1 * h2;
    const hash_t m = (l1 + h1) * (l2 + h2) - l - h;
    hash_t res = (l + (m << 32)) & MOD;
    res += (((l >> 32) + m) >> 29) + (h << 3) + 1;
    res = (res & MOD) + (res >> 61);
    return res - 1;
  }

  const vector<hash_t> POWS = []() {
    mt19937_64 gen(chrono::high_resolution_clock::now().time_since_epoch().count());
    hash_t p = uniform_int_distribution<hash_t>(MOD >> 1, MOD - 2)(gen);
    p |= 1;
    vector<hash_t> res(N + 1, 1);
    for (int32_t i = 0; i < N; ++i) {
      res[i + 1] = mul(res[i], p);
    }
    return res;
  }();

  hash_t get(const string &s) {
    hash_t res = 0;
    for (char c : s) {
      res = add(mul(res, POWS[1]), c);
    }
    return res;
  }

  class HashedString {
  private:
    int32_t sz;
    vector<hash_t> pref;

  public:
    HashedString(const string &s) {
      sz = (int)s.size();
      pref.resize(sz + 1, 0);
      for (int32_t i = 0; i < sz; ++i) {
        pref[i + 1] = add(mul(pref[i], POWS[1]), s[i]);
      }
    }
    hash_t get(int l, int r) const {
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
  typedef pair<int32_t, ull> hash_t;
  const int32_t MOD = 2000000011;
  const int32_t N = 1e6;

  hash_t operator*(hash_t a, hash_t b) {
    return hash_t(1ULL * a.first * b.first % MOD, a.second * b.second);
  }

  hash_t operator+(hash_t a, hash_t b) {
    return hash_t((0LL + a.first + b.first) % MOD, a.second + b.second);
  }

  hash_t operator-(hash_t a, hash_t b) {
    return hash_t((0LL + a.first - b.first + MOD) % MOD, a.second - b.second);
  }

  const vector<hash_t> POWS = []() {
    mt19937 gen(chrono::high_resolution_clock::now().time_since_epoch().count());
    int32_t p = uniform_int_distribution<int32_t>(MOD >> 1, MOD - 2)(gen);
    p |= 1;
    vector<hash_t> res(N + 1, hash_t(1, 1));
    for (int32_t i = 0; i < N; ++i) {
      res[i + 1] = res[i] * hash_t(p, p);
    }
    return res;
  }();

  hash_t get(const string &s) {
    hash_t res(0, 0);
    for (char c : s) {
      res = res * POWS[1] + hash_t(c, c);
    }
    return res;
  }

  class HashedString {
  private:
    int32_t sz;
    vector<hash_t> pref;

  public:
    HashedString(const string &s) {
      sz = (int32_t)s.size();
      pref.resize(sz + 1, hash_t(0, 0));
      for (int32_t i = 0; i < sz; ++i) {
        pref[i + 1] = pref[i] * POWS[1] + hash_t(s[i], s[i]);
      }
    }
    hash_t get(int l, int r) const {
      assert(l < r);
      // [l, r)
      return pref[r] - pref[l] * POWS[r - l];
    }
  };
}