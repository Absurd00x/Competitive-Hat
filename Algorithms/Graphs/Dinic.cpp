// 1423B
typedef tuple<int, int, int> ti;
class Dinic {
private:
  int nodes;
  const int NONE = -1;
  const int ZERO = 0;
  const int INF = numeric_limits<int>::max();
  vector<tuple<int, int, int, int>> edges; // from, to, capacity, flow
  vector<int> ptr, levels;
  vector<vector<int>> g; // [node][i] = edge index

  void _add_edge(int from, int to, int cap) {
    g[from].push_back(edges.size());
    edges.emplace_back(from, to, cap, ZERO);
    g[to].push_back(edges.size());
    edges.emplace_back(to, from, cap, ZERO);
  }

  int source, sink;
  bool _bfs() {
    std::fill(levels.begin(), levels.end(), NONE);
    std::queue<int> q;
    q.push(source);
    levels[source] = 0;
    while (!q.empty()) {
      int v = q.front();
      q.pop();
      for (int edge_index : g[v]) {
        auto &[from, to, cap, flow] = edges[edge_index];
        int available = cap - flow;
        if (available > 0 && levels[to] == NONE) {
          levels[to] = levels[v] + 1;
          q.push(to);
        }
      }
    }
    return (levels[sink] != -1);
  }

  int _dfs(int v, int cur_flow) {
    if (cur_flow == 0 || v == sink) {
      return cur_flow;
    }
    for (int &i = ptr[v]; i < (int)g[v].size(); ++i) {
      int edge_index = g[v][i];
      auto &[from, to, cap, flow] = edges[edge_index];
      auto &[_, __, ___, back_flow] = edges[edge_index ^ 1];
      int available = cap - flow;
      if (available > 0 && levels[to] == levels[v] + 1) {
        int pushed = _dfs(to, std::min(cur_flow, available));
        if (pushed > 0) {
          flow += pushed;
          back_flow -= pushed;
          return pushed;
        }
      }
    }
    return ZERO;
  }

  int _dinic() {
    int max_flow = 0;
    while (_bfs()) {
      std::fill(ptr.begin(), ptr.end(), ZERO);
      while (int pushed = _dfs(source, INF)) {
        max_flow += pushed;
      }
    }
    return max_flow;
  }

public:
  void build(int nodes_, vector<ti> &edges_) {
    nodes = nodes_;
    g.clear();
    g.resize(nodes);
    levels.resize(nodes);
    ptr.resize(nodes);
    edges.clear();
    for (auto &[weight, from, to] : edges_) {
      _add_edge(from, to, weight);
    }
  }

  int run(int source_, int sink_) {
    source = source_;
    sink = sink_;
    return _dinic();
  }
};
