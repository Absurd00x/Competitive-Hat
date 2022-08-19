const int INF = 9e18;
struct Elem {
  int sum, min, add, assigned, val;
};
const Elem NEUTRAL{0, INF, 0, -1, -1};
const int NONE{-1};

class SegTree {
private:
typedef vector<int> vi;
  const int ROOT{1}, START{0};
  int cleft, cright;
  int nodes, elems;
  int qleft, qright;
  vector<Elem> guts;

  void clear(int x) {
    guts[x] = NEUTRAL;
  }

  void update_from_children(int x) {
    clear(x);
    int tleft = cleft, tright = cright, mid = get_mid();
    cright = mid;
    push(x * 2);
    cright = tright;
    update_from_node(x, x * 2);
    cleft = mid;
    push(x * 2 + 1);
    cleft = tleft;
    update_from_node(x, x * 2 + 1);
  }

  void set_cur(int left, int right) {
    cleft = left;
    cright = right;
  }

  void push(int x) {
    if (has_lazy(x)) {
      if (x * 2 < nodes) {
        propagate_lazy(x);
      }
      apply_lazy(x);
      clear_lazy(x);
    }
  }

  void prepare(int left, int right) {
    qleft = left;
    qright = (right == NONE ? left + 1 : right);
    clear(0);
  }

  int get_mid() {
    int len = cright - cleft;
    assert(len > 1);
    int sb = std::__lg(len);
    return cleft + std::min((1 << (sb - 1)) + (len - (1 << sb)), int(1 << sb));
  }

  void query(int x, int left, int right, auto on_node) {
    set_cur(left, right);
    push(x);
    if (qleft <= left && right <= qright) {
      on_node(x);
      push(x);
    } else {
      int mid = get_mid();
      if (qleft < mid) {
        query(x * 2, left, mid, on_node);
      }
      if (mid < qright) {
        query(x * 2 + 1, mid, right, on_node);
      }
      set_cur(left, right);
      update_from_children(x);
    }
  }

  void traverse(int x, int left, int right, auto on_leaf) {
    set_cur(left, right);
    push(x);
    if (cright - cleft == 1) {
      on_leaf(x);
    } else {
      int mid = get_mid();
      traverse(x * 2, left, mid, on_leaf);
      traverse(x * 2 + 1, mid, right, on_leaf);
      set_cur(left, right);
      update_from_children(x);
    }
  }

  void descend(int x, int left, int right, auto on_node, const bool rl) {
    set_cur(left, right);
    push(x);
    if (qleft <= left && right <= qright) {
      bool add_me = on_node(x);
      if (add_me) {
        return;
      }
      if (cright - cleft == 1) {
        (rl ? qleft = left : qright = right);
        return;
      }
      int mid = get_mid();
      if (!rl) {
        cright = mid;
        push(x * 2);
        bool add_left = on_node(x * 2);
        cright = right;
        if (add_left) {
          qright = right;
          descend(x * 2 + 1, mid, right, on_node, rl);
        } else {
          qright = mid;
          descend(x * 2, left, mid, on_node, rl);
        }
      } else {
        cleft = mid;
        push(x * 2 + 1);
        bool add_right = on_node(x * 2 + 1);
        cleft = left;
        if (add_right) {
          qleft = left;
          descend(x * 2, left, mid, on_node, rl);
        } else {
          qleft = mid;
          descend(x * 2 + 1, mid, right, on_node, rl);
        }
      }
      set_cur(left, right);
      update_from_children(x);
    } else {
      int mid = get_mid();
      if (qleft < mid) {
        descend(x * 2, left, mid, on_node, rl);
      }
      if (mid < qright) {
        descend(x * 2 + 1, mid, right, on_node, rl);
      }
      set_cur(left, right);
      update_from_children(x);
    }
  }

public:
  void build(int sz) {
    elems = sz;
    nodes = elems * 2;
    guts.clear();
    guts.resize(nodes, NEUTRAL);
  }

// ===================== change this =====================

  vi propagate() {
    vi res(elems);
    auto on_leaf = [&](int x) {
      res[cleft] = guts[x].sum;
    };
    traverse(ROOT, START, elems, on_leaf);
    return res;
  }

  void build(const vi &init) {
    build((int)init.size());
    // fill and build
    auto on_leaf = [&](int x) {
      guts[x].sum = guts[x].min = init[cleft];
      guts[x].val = cleft;
    };
    traverse(ROOT, START, elems, on_leaf);
  }

  void update_from_node(int x, int y) {
    // в детях не бывает лени, когда от них обновляешься
    guts[x].sum += guts[y].sum;
    if (guts[x].min > guts[y].min) {
      guts[x].min = guts[y].min;
      guts[x].val = guts[y].val;
    }
  }

  bool has_lazy(int x) {
    bool assigned_lazy = (guts[x].assigned != NEUTRAL.assigned);
    bool add_lazy = (guts[x].add != NEUTRAL.add);
    return assigned_lazy || add_lazy;
  }

  void propagate_lazy(int x) {
    // int mid = get_mid();
    Elem &par = guts[x];
    Elem &left = guts[x * 2];
    Elem &right = guts[x * 2 + 1];

    if (par.assigned != NEUTRAL.assigned) {
      left.assigned = par.assigned;
      right.assigned = par.assigned;
      left.add = right.add = 0;
    }
    left.add += par.add;
    right.add += par.add;
  }

  void apply_lazy(int x) {
    if (guts[x].assigned != NEUTRAL.assigned) {
      guts[x].sum = guts[x].assigned * (cright - cleft);
      guts[x].min = guts[x].assigned;
      guts[x].val = cleft;
    }
    guts[x].sum += guts[x].add * (cright - cleft);
    guts[x].min += guts[x].add;
  }

  void clear_lazy(int x) {
    guts[x].assigned = NEUTRAL.assigned;
    guts[x].add = NEUTRAL.add;
  }

public:
  void ass_to_seg(int value, int left, int right=NONE) {
    prepare(left, right);
    auto update_from_value = [&](int x) {
      guts[x].assigned = value;
    };
    query(ROOT, START, elems, update_from_value);
  }

  void add_to_seg(int value, int left, int right=NONE) {
    prepare(left, right);
    auto update_from_value = [&](int x) {
      guts[x].add += value;
    };
    query(ROOT, START, elems, update_from_value);
  }

  int min_on_seg(int left, int right=NONE) {
    prepare(left, right);
    auto query_update = [&](int x) {
      if (guts[0].min > guts[x].min) {
        guts[0].min = guts[x].min;
        guts[0].val = guts[x].val;
      }
    };
    query(ROOT, START, elems, query_update);
    return guts[0].val;
  }

  int kth_order(int k, int left, int right) {
    prepare(left, right);
    --k; // Теперь ищем элемент, в котором сумма строго больше
    int last = NONE;
    auto query_update = [&](int x) {
      int next = guts[0].sum + guts[x].sum;
      if (next <= k) {
        guts[0].sum = next;
        return true;
      }
      last = cleft;
      return false;
    };
    descend(ROOT, START, elems, query_update, false);
    return last;
  }
} kappa;

