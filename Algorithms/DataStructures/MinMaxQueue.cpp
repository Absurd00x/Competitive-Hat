struct MaxModule {
  static bool cmp(const int &a, const int &b) {
    return a <= b;
  }
};

struct MinModule {
  static bool cmp(const int &a, const int &b) {
    return a >= b;
  }
};

template <typename Module>
class MinMaxQueue {
private:
  std::deque<pii> q;
  int cnt{0}, last{0}, sz{0};
  int default_value{-1};
public:
  void push(int val) {
    while(false == q.empty() && Module::cmp(q.back().first, val)) {
      q.pop_back();
    }
    q.push_back({val, cnt++});
    ++sz;
  }

  void set_default(int val) {
    default_value = val;
  }

  void pop() {
    if (q.front().second == last++) {
      q.pop_front();
    }
    --sz;
  }

  int get_minmax() {
    return q.size() ? q.front().first : default_value;
  }

  int get_size() {
    return sz;
  }
};
