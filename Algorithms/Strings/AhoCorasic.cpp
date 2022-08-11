const int K = 'z' - 'a' + 1;
const int NONE{-1};

struct Node {
  int32_t to[K];
  char psymb;
  int32_t prev, link, id;
  Node(): psymb('\0'), prev(0), link(0), id(NONE) {
    memset(to, 0, sizeof(to));
  }
};

class AhoCorasic {
private:
  vector<int32_t> table;
public:
  vector<Node> guts;

  AhoCorasic(const int MAX_NODES=1'000'000): table(256, NONE), guts(MAX_NODES) {}

  void build(vector<string> &words, const string &symbs) {
    for (int32_t i = 0; i < (int32_t)symbs.size(); ++i) {
      table[symbs[i]] = i;
    }
    guts.clear();
    guts.push_back(Node());
    for (int32_t i = 0; i < (int32_t)words.size(); ++i) {
      int32_t v = 0;
      for (char c : words[i]) {
        int32_t ind = table[c];
        if (guts[v].to[ind] == 0) {
          guts[v].to[ind] = (int32_t)guts.size();
          guts.push_back(Node());
          guts.back().psymb = c;
          guts.back().prev = v;
        }
        v = guts[v].to[ind];
      }
      guts[v].id = i;
    }
    queue<int32_t> q;
    q.push(0);
    while (!q.empty()) {
      int32_t cur = q.front();
      q.pop();
      if (guts[cur].prev != 0) {
        int32_t prev_link = guts[guts[cur].prev].link;
        guts[cur].link = guts[prev_link].to[table[guts[cur].psymb]];
      }
      for (int i = 0; i < K; ++i) {
        int32_t &next = guts[cur].to[i];
        if (next == 0) {
          next = guts[guts[cur].link].to[i];
        } else {
          q.push(next);
        }
      }
    }
  }

  int go(int v, char c) {
    return guts[v].to[table[c]];
  }
} ac;

// OOM

const int K = 'z' - 'a' + 1;
const int NONE{-1};

struct Node {
  map<char, int32_t> to;
  char psymb{'\0'};
  int32_t prev{NONE};
  int32_t link{NONE};
  int32_t id{NONE};
};

class AhoCorasic {
public:
  vector<Node> guts;

  AhoCorasic(const int MAX_NODES=1'000'000) {
    guts.resize(MAX_NODES);
  }

  void build(vector<string> &words) {
    guts.clear();
    guts.push_back(Node());
    for (int32_t i = 0; i < (int32_t)words.size(); ++i) {
      int32_t v = 0;
      for (char c : words[i]) {
        if (guts[v].to.count(c) == 0) {
          guts[v].to[c] = (int32_t)guts.size();
          guts.push_back(Node());
          guts.back().psymb = c;
          guts.back().prev = v;
        }
        v = guts[v].to[c];
      }
      guts[v].id = i;
    }
  }
  int get_link(int v) {
    if (guts[v].link != NONE) {
      return guts[v].link;
    } else if (guts[v].prev != 0){
      return guts[v].link = (int32_t)go(get_link(guts[v].prev), guts[v].psymb);
    } else {
      return guts[v].link = 0;
    }
  }
  int go(int v, char c) {
    if (guts[v].to.count(c)) {
      return guts[v].to[c];
    } else if (v != 0) {
      return guts[v].to[c] = (int32_t)go(get_link(v), c);
    } else {
      return guts[v].to[c] = 0;
    }
  }
} ac;
