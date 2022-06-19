// Edu part 2 step 2 F
struct Elem {
  int assigned, sum;
};
const Elem NEUTRAL{-1, 0};
const int NONE{-1};

class SegTree {
protected:
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
    update_from_node(x, x * 2);
    update_from_node(x, x * 2 + 1);
  }

  void set_cur(int left, int right) {
    cleft = left;
    cright = right;
  }

  void push(int x) {
    if (has_lazy(x)) {
      if (cright - cleft > 1) {
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
    int sb = (len == 0 ? 0 : std::__lg(len));
    return cleft + std::min((1 << (sb - 1)) + (len - (1 << sb)), int(1 << sb));
  }

  void _query(int x, int left, int right, auto on_node) {
    set_cur(left, right);
    push(x);
    if (qleft <= left && right <= qright) {
      on_node(x);
      push(x);
    } else {
      int mid = get_mid();
      if (qleft < mid) {
        _query(x * 2, left, mid, on_node);
      }
      if (mid < qright) {
        _query(x * 2 + 1, mid, right, on_node);
      }
      update_from_children(x);
    }
  }

  void _traverse(int x, int left, int right, auto on_leaf) {
    set_cur(left, right);
    push(x);
    if (cright - cleft == 1) {
      on_leaf(x);
    } else {
      int mid = get_mid();
      _traverse(x * 2, left, mid, on_leaf);
      _traverse(x * 2 + 1, mid, right, on_leaf);
      update_from_children(x);
    }
  }

  void _descend(int x, int left, int right, auto on_node) {
    set_cur(left, right);
    push(x);
    if (qleft <= left && right <= qright) {
      bool add_me = on_node(x);
      if (!add_me && cright - cleft > 1) {
        int mid = get_mid();
        push(x * 2);
        bool add_left = on_node(x * 2);
        if (add_left) {
          qright = right;
          _descend(x * 2 + 1, mid, right, on_node);
        } else {
          qright = mid;
          _descend(x * 2, left, mid, on_node);
        }
        update_from_children(x);
      }
    } else {
      int mid = get_mid();
      if (qleft < mid) {
        _descend(x * 2, left, mid, on_node);
      }
      if (mid < qright) {
        _descend(x * 2 + 1, mid, right, on_node);
      }
      update_from_children(x);
    }
  }

  void traverse(auto delegate) {
    _traverse(ROOT, START, elems, delegate);
  }

  void query(auto delegate) {
    _query(ROOT, START, elems, delegate);
  }

  void descend(auto delegate) {
    _descend(ROOT, START, elems, delegate);
  }

  virtual void update_from_node(int x, int y) {
    x = x, y = y;
    throw std::logic_error("update_from_node() not implemented");
  }

  virtual bool has_lazy(int x) {
    x = x;
    throw std::logic_error("has_lazy() not implemented");
  }

  virtual void propagate_lazy(int x) {
    x = x;
    throw std::logic_error("propagate_lazy() not implemented");
  }

  virtual void apply_lazy(int x) {
    x = x;
    throw std::logic_error("apply_lazy() not implemented");
  }

  virtual void clear_lazy(int x) {
    x = x;
    throw std::logic_error("clear_lazy() not implemented");
  }

  void wipe(int sz) {
    elems = sz;
    nodes = elems * 2;
    guts.clear();
    guts.resize(nodes, NEUTRAL);
  }
};

class STAddAss : public SegTree {
private:
  void update_from_node(int x, int y) override {
    guts[x].sum += guts[y].sum;
  }

  bool has_lazy(int x) override {
    return (guts[x].assigned != NEUTRAL.assigned);
  }

  void propagate_lazy(int x) override {
    int mid = get_mid();
    Elem &par = guts[x];
    Elem &left = guts[x * 2];
    Elem &right = guts[x * 2 + 1];

    left.assigned = par.assigned;
    right.assigned = par.assigned;
  }

  void apply_lazy(int x) override {
    guts[x].sum = guts[x].assigned * (cright - cleft);
  }

  void clear_lazy(int x) override {
    guts[x].assigned = NEUTRAL.assigned;
  }

public:
  void build(int sz) {
    wipe(sz);
  }

  void build(const vi &init) {
    build((int)init.size());
    // fill and build
    auto on_leaf = [&](int x) {
      guts[x].sum = init[cleft];
    };
    traverse(on_leaf);
  }

  vi propagate() {
    vi res(elems);
    auto on_leaf = [&](int x) {
      res[cleft] = guts[x].sum;
    };
    traverse(on_leaf);
    return res;
  }

  void ass_to_seg(int value, int left, int right=NONE) {
    prepare(left, right);
    guts[0].assigned = value;
    auto update_from_value = [&](int x) {
      guts[x].assigned = value;
    };
    query(update_from_value);
  }

  int sum_on_seg(int left, int right=NONE) {
    prepare(left, right);
    auto query_update = [&](int x) {
      guts[0].sum += guts[x].sum;
    };
    query(query_update);
    return guts[0].sum;
  }

  int kth_order(int k) {
    prepare(0, elems);
    int last = NONE;
    auto query_update = [&](int x) {
      int next = guts[0].sum + guts[x].sum;
      if (next < k) {
        guts[0].sum = next;
        return true;
      }
      last = cleft;
      return false;
    };
    descend(query_update);
    return last;
  }
} kappa;
