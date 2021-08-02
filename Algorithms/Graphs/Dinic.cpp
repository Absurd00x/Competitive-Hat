class Dinic {
private:
  const int ZERO = 0;
  const int NONE = -1;
  int nodes;
  vector<qi> edges; // from, to, capacity, flow
  vi ptr, levels;
  vvi g; // [node][i] = edge index

  void __add_edge(int from, int to, int cap) {
    g[from].push_back(edges.size());
    edges.emplace_back(from, to, cap, ZERO);
    g[to].push_back(edges.size());
    edges.emplace_back(to, from, cap, ZERO);
  }

  int source, sink;
  bool __bfs() {
    std::fill(all(levels), NONE);
    std::queue<int> q;
    q.push(source);
    levels[source] = 0;
    while(q.empty() == false) {
      int v = q.front();
      q.pop();
      for(int edge_index : g[v]) {
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

  int __dfs(int v, int cur_flow) {
    if (cur_flow == 0 || v == sink)
      return cur_flow;
    for(int &i = ptr[v]; i < (int)g[v].size(); ++i) {
      int edge_index = g[v][i];
      auto &[from, to, cap, flow] = edges[edge_index];
      auto &[_, __, ___, back_flow] = edges[edge_index ^ 1];
      int available = cap - flow;
      if (available > 0 && levels[to] == levels[v] + 1) {
        int pushed = __dfs(to, std::min(cur_flow, available));
        if (pushed > 0) {
          flow += pushed;
          back_flow -= pushed;
          return pushed;
        }
      }
    }
    return ZERO;
  }

  int __dinic() {
    int max_flow = 0;

    while(__bfs()) {
      std::fill(all(ptr), ZERO);
      while(int pushed = __dfs(source, INF))
        max_flow += pushed;
    }
    return max_flow;
  }

public:
  void build(int nodes_, vector<ti> &edges_) {
    nodes = nodes_;
    g.resize(nodes);
    levels.resize(nodes);
    ptr.resize(nodes);
    edges.clear();
    for(auto &[weight, from, to] : edges_) {
      __add_edge(from, to, weight);
    }
  }

  int run(int source_, int sink_) {
    source = source_;
    sink = sink_;
    return __dinic();
  }
};
