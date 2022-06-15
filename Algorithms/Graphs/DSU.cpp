// 1411C
class DSU {
private:
  int sz;
  vector<int> leaders;
public:
  vector<int> ranks, sizes;

  void build(int sz_) {
    sz = sz_;
    ranks.clear();
    ranks.resize(sz, 1);
    sizes.clear();
    sizes.resize(sz, 1);
    leaders.resize(sz);
    std::iota(leaders.begin(), leaders.end(), 0);
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
} dsu;
