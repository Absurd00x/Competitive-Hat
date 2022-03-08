// 1411C
class DSU {
private:
  int sz;
  vi leaders;
public:
  vi ranks, sizes;

  void build(int sz_) {
    sz = sz_;
    ranks.clear();
    ranks.resize(sz, ONE);
    sizes.clear();
    sizes.resize(sz, ONE);
    leaders.resize(sz);
    std::iota(all(leaders), ZERO);
  }

  int get_leader(int v) {
    if (v == leaders[v]) {
      return v;
    }
    return leaders[v] = get_leader(leaders[v]);
  }

  bool unite(int a, int b) {
    a = get_leader(a);
    b = get_leader(b);
    if (a != b) {
      if (ranks[a] < ranks[b]) {
        std::swap(a, b);
      }
      leaders[b] = a;
      sizes[a] += sizes[b];
      if (ranks[a] == ranks[b]) {
        ++ranks[a];
      }
      return true;
    }
    return false;
  }
};
