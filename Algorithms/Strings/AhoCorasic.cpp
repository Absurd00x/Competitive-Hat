const int K = 'z' - 'a' + 1;
typedef unsigned char uc;

struct Node {
  int next[K];
  bool is_term;
  int prev;
  char psymb;
  int link;
  Node() : is_term(0), prev(0), psymb(0), link(0) {
    memset(next, 0, sizeof(next));
  }
};

class AhoCorasic {
private:

  uc get_ind(char c) {
    return uc(c - 'a');
  }

public:
  vector<Node> guts;

  void build(const vector<string> &words, int MBsize) {
    int Bsize = MBsize * 1024 * 1024;
    guts.resize(Bsize / sizeof(Node));
    guts.clear();
    guts.push_back(Node());
    // добавляю строчки в бор
    for (auto &s : words) {
      int v = 0;
      for (char c : s) {
        uc i = get_ind(c);
        if (guts[v].next[i] == 0) {
          guts[v].next[i] = (int)guts.size();
          guts.push_back(Node());
          guts.back().prev = v;
          guts.back().psymb = c;
        }
        v = guts[v].next[i];
      }
      guts[v].is_term = true;
    }
    queue<int> q;
    // у корня и его детей суффиксная ссылка всегда ведёт в корень
    for (int child : guts[0].next) {
      if (child != 0) {
        for (int i = 0; i < K; ++i) {
          int &next = guts[v].next[i];
          if (next != 0) {
            q.push(next);
          } else {
            next = guts[0].to[i];
          }
        }
      }
    }
    while (!q.empty()) {
      int v = q.front();
      q.pop();
      int prev_link = guts[guts[v].prev].link;
      int cur_link = guts[prev_link].next[get_ind(guts[v].psymb)];
      guts[v].link = cur_link;
      for (uc i = 0; i < K; ++i) {
        int &next = guts[v].next[i];
        if (next == 0) {
          next = guts[cur_link].next[i];
        } else {
          q.push(next);
        }
      }
    }
  }

  int step(int v, char c) {
    return guts[v].next[get_ind(c)];
  }
} ac;
