class DSU {
private:
  int sz;
  vi leaders, ranks;
public:
  DSU(int sz_) {
    sz = sz_;
    ranks.resize(sz, 1);
    leaders.resize(sz);
    std::iota(all(leaders), 0LL);
  }

  int get_leader(int v) {
    if (v == leaders[v]) {
      return v;
    }
    return leaders[v] = get_leader(leaders[v]);
  }

  void unite(int a, int b) {
    a = get_leader(a);
    b = get_leader(b);
    if (a != b) {
      if (ranks[a] < ranks[b]) {
        std::swap(a, b);
      }
      leaders[b] = a;
      if (ranks[a] == ranks[b]) {
        ++ranks[a];
      }
    }
  }
};

