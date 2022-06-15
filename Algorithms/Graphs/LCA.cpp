// 1328E
class LCA {
private:
  const int NONE = -1;
  int pows;
  vector<int> depth, last;
  vector<vector<int>> guts;

  int msb(int num) {
    return (num == 0 ? 0 : std::__lg(num));
  };
public:
  void build(vector<vector<int>> &graph) {
    int vertices = (int)graph.size();
    assert(vertices > 0);
    guts.resize(1);

    last.resize(vertices);
    depth.resize(vertices);

    vector<int> &tour = guts[0];
    tour.resize(2 * vertices + 10);
    tour.clear();
    vector<bool> vis(vertices, false);

    std::function<void(int, int)> _dfs = [&](int cur, int cur_depth) {
      vis[cur] = true;
      depth[cur] = cur_depth;
      last[cur] = (int)tour.size();
      tour.push_back(cur);
      for (int next : graph[cur]) {
        if (false == vis[next]) {
          _dfs(next, cur_depth + 1);
          tour.push_back(cur);
        }
      }
    };

    for (int i = 0; i < vertices; ++i) {
      if (false == vis[i]) {
        _dfs(i, 0);
      }
    }

    int sz = (int)tour.size();
    pows = msb(sz - 1) + 1;
    guts.resize(pows);

    for (int pow = 1; pow < pows; ++pow) {
      int cur = 1 << pow;
      int prev = 1 << (pow - 1);
      int size = sz - cur + 1;
      guts[pow].clear();
      guts[pow].resize(size);
      for (int i = 0; i < size; ++i) {
        if (depth[guts[pow - 1][i]] < depth[guts[pow - 1][i + prev]]) {
          guts[pow][i] = guts[pow - 1][i];
        } else {
          guts[pow][i] = guts[pow - 1][i + prev];
        }
      }
    }
  }

  int lca(int v, int u) {
    if (depth[v] == depth[u] && depth[v] == 0 && u != v) {
      return NONE;
    }
    int left = last[v];
    int right = last[u];
    if (left > right)
      std::swap(left, right);
    ++right;

    int len = right - left;
    int pow = msb(len - 1);
    int step = 1 << pow;
    if (depth[guts[pow][left]] < depth[guts[pow][right - step]]) {
      return guts[pow][left];
    }
    return guts[pow][right - step];
  }
} lca;
