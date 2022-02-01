// Edu
struct Elem {
  int sum, add, mult;
};

class SegTree {
// can add number to segment and
// can multiply numbers on segment
private:
  const Elem NEUTRAL{ZERO, ZERO, ONE};
  int start, end, size;
  vector<Elem> guts;

inline void clear(int x) {
  guts[x] = NEUTRAL;
}

inline void update_from_node(int x, int y) {
  guts[x].sum += guts[y].sum;
}

inline void update_from_children(int x) {
  clear(x);
  update_from_node(x, x * 2);
  update_from_node(x, x * 2 + 1);
}

inline void update_from_value(int x) {
  guts[x].add += guts[0].add;
  guts[x].mult *= guts[0].mult;
}

inline void apply_lazy(int x) {
  guts[x].sum += guts[x].add;
  guts[x].sum *= guts[x].mult;
}

inline void propagate_lazy(int x) {
  guts[x * 2].add += guts[x].add;
  guts[x * 2].mult *= guts[x].mult;
  guts[x * 2 + 1].add += guts[x].add;
  guts[x * 2 + 1].mult *= guts[x].mult;
}

inline void query_update(int x) {
  guts[0].sum += guts[x].sum;
}

inline void clear_lazy(int x) {
  guts[x].add = NEUTRAL.add;
  guts[x].mult = NEUTRAL.mult;
}

inline void push(int x) {
  apply_lazy(x);
  if (x < start) {
    propagate_lazy(x);
  }
  clear_lazy(x);
}

  int qleft, qright;
void _update_seg(int x, int left, int right) {
  push(x);
  if (qleft <= left && right <= qright) {
    update_from_value(x);
    push(x);
  } else {
    int mid = (left + right) / 2;
    if (qleft < mid) {
      _update_seg(x * 2, left, mid);
    }
    if (mid < qright) {
      _update_seg(x * 2 + 1, mid, right);
    }
    update_from_children(x);
  }
}

void _sum_on_seg(int x, int left, int right) {
  push(x);
  if (qleft <= left && right <= qright) {
    query_update(x);
  } else {
    int mid = (left + right) / 2;
    if (qleft < mid) {
      _sum_on_seg(x * 2, left, mid);
    }
    if (mid < qright) {
      _sum_on_seg(x * 2 + 1, mid, right);
    }
  }
}

void prepare(int left, int right) {
  qleft = left;
  qright = (right == NONE ? left + 1 : right);
  clear(0);
}

public:
  void build(int sz) {
    start = powb(msb(sz - 1) + 1);
    end = start + sz;
    size = start * 2;

    guts.resize(size, NEUTRAL);
    std::fill(all(guts), NEUTRAL);
  }

  void build(const vi &init) {
    int sz = ssize(init);
    start = powb(msb(sz - 1) + 1);
    end = start + sz;
    size = start << 1;

    guts.resize(size, NEUTRAL);
    std::fill(all(guts), NEUTRAL);
    // fill
    for (int i = 0; i < sz; ++i) {
      guts[i + start].sum = init[i];
    }
    // build
    for (int i = start - 1; i > 0; --i) {
      update_from_children(i);
    }
  }

  vi propagate() {
    for (int i = 1; i < end; ++i) {
      push(i);
    }
    vi res(end - start);
    for (int i = 0; i < end - start; ++i) {
      res[i] = guts[i + start].sum;
    }
    return res;
  }

  void add_to_seg(int value, int left, int right=NONE) {
    // [left, right)
    prepare(left, right);
    guts[0].add = value;
    _update_seg(1, 0, start);
  }

  void mult_to_seg(int value, int left, int right=NONE) {
    // [left, right)
    prepare(left, right);
    guts[0].mult = value;
    _update_seg(1, 0, start);
  }

  int sum_on_seg(int left, int right=NONE) {
    // [left, right)
    prepare(left, right);
    _sum_on_seg(1, 0, start);
    return guts[0].sum;
  }
};
