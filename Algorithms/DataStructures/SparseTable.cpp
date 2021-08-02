struct MinModule {
  static pii func(const pii &a, const pii &b) {
    return std::min(a, b);
  }
};

struct MaxModule {
  static pii func(const pii &a, const pii &b) {
    return std::max(a, b);
  }
};

struct GCDModule {
  static pii func(const pii &a, const pii &b) {
    return pii(std::gcd(a.first, b.first), a.second);
  }
};

template <typename Module>
class SparseTable {
private:
  vector<vpii> guts;
  int pows;

public:
  void build(const vi &nums) {
    int sz = (int)nums.size();
    assert(sz > 0);
    pows = std::__lg(sz - 1) + 1;
    guts.resize(pows);
    for(int i = 0; i < sz; ++i) {
      guts[0].emplace_back(nums[i], i);
    }
    for(int pow = 1; pow < pows; ++pow) {
      int cur = 1LL << pow;
      int prev = 1LL << (pow - 1);
      int size = sz - cur + 1;
      guts[pow].resize(size);
      for(int j = 0; j < size; ++j) {
        guts[pow][j] = Module::func(guts[pow - 1][j], guts[pow - 1][j + prev]);
      }
    }
  };

  pii get_elem_index(int left, int right) {
    int len = right - left;
    assert(len > 0);
    int pow = std::__lg(len - 1);
    int cur = 1LL << pow;
    return Module::func(guts[pow][left], guts[pow][right - cur]);
  }
};

