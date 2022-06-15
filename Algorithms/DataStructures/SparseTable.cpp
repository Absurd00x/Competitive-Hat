// 1549D
typedef pair<int, int> pii;
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
  vector<vector<pii>> guts;
  int pows;

  int msb(int num) {
    return (num == 0 ? 0 : std::__lg(num));
  }

public:
  void build(const vector<int> &nums) {
    int sz = (int)nums.size();
    assert(sz > 0);
    pows = msb(sz - 1) + 1;
    guts.resize(pows);
    guts[0].clear();
    for (int i = 0; i < sz; ++i) {
      guts[0].emplace_back(nums[i], i);
    }
    for (int pow = 1; pow < pows; ++pow) {
      int cur = 1 << pow;
      int prev = 1 << (pow - 1);
      int size = sz - cur + 1;
      guts[pow].clear();
      guts[pow].resize(size);
      for (int j = 0; j < size; ++j) {
        guts[pow][j] = Module::func(guts[pow - 1][j], guts[pow - 1][j + prev]);
      }
    }
  };

  pii get(int left, int right) {
    int len = right - left;
    assert(len > 0);
    int pow = msb(len - 1);
    return Module::func(guts[pow][left], guts[pow][right - (1 << pow)]);
  }
};
