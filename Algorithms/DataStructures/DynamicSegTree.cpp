// Edu 5 2 279653F
// assign to seg
// get sum
struct Elem {
  int left, right;
  int assigned, sum;
};

class DynamicSegTree {
private:
  const Elem NEUTRAL{NONE, NONE, ZERO, ZERO};
  int start, finish;
  int qleft, qright;
  int cleft, cright;
  vector<Elem> guts;

inline void create(int &child) {
  if (child == NONE) {
    child = ssize(guts);
    guts.pub(NEUTRAL);
  }
}

inline void update_from_children(int x) {
  clear(x);
  update_from_node(x, guts[x].left);
  update_from_node(x, guts[x].right);
}

inline void set_cur(int left, int right) {
  cleft = left;
  cright = right;
}

inline void push(int x) {
  if (cright - cleft > 1) {
    create(guts[x].left);
    create(guts[x].right);
    if (has_lazy(x)) {
      propagate_lazy(x);
    }
  }
  if (has_lazy(x)) {
    apply_lazy(x);
    clear_lazy(x);
  }
}

void prepare(int left, int right) {
  qleft = left;
  qright = (right == NONE ? left + 1 : right);
  clear(0);
}

// change after this part

inline void clear(int x) {
  guts[x].assigned = NEUTRAL.assigned;
  guts[x].sum = NEUTRAL.sum;
}

inline void update_from_node(int x, int y) {
  guts[x].sum += guts[y].sum;
}

inline void update_from_value(int x) {
  guts[x].assigned = guts[0].assigned;
  guts[x].sum = guts[x].assigned * (cright - cleft);
}

inline void apply_lazy(int x) {
  guts[x].sum = guts[x].assigned * (cright - cleft);
}

inline bool has_lazy(int x) {
  return (guts[x].assigned != NEUTRAL.assigned);
}

inline void propagate_lazy(int x) {
  int mid = (cleft + cright) / 2;
  Elem &par = guts[x];
  Elem &left = guts[par.left];
  Elem &right = guts[par.right];

  left.assigned = par.assigned;
  left.sum = par.assigned * (mid - cleft);
  right.assigned = par.assigned;
  right.sum = par.assigned * (cright - mid);
}

inline void query_update(int x) {
  guts[0].sum += guts[x].sum;
}

inline void clear_lazy(int x) {
  guts[x].assigned = NEUTRAL.assigned;
}

void _ass_to_seg(int x, int left, int right) {
  set_cur(left, right);
  push(x);
  if (qleft <= left && right <= qright) {
    update_from_value(x);
    push(x);
  } else {
    int mid = (left + right) / 2;
    if (qleft < mid) {
      _ass_to_seg(guts[x].left, left, mid);
    }
    if (mid < qright) {
      _ass_to_seg(guts[x].right, mid, right);
    }
    update_from_children(x);
  }
}

void _sum_on_seg(int x, int left, int right) {
  set_cur(left, right);
  push(x);
  if (qleft <= left && right <= qright) {
    query_update(x);
  } else {
    int mid = (left + right) / 2;
    if (qleft < mid) {
      _sum_on_seg(guts[x].left, left, mid);
    }
    if (mid < qright) {
      _sum_on_seg(guts[x].right, mid, right);
    }
  }
}

public:
  void build(int min, int max, int mbsize=0) {
    start = min;
    finish = max + 1;
    int bsize = mbsize * 1024 * 1024;
    guts.resize(bsize / sizeof(Elem), NEUTRAL);
    guts.clear();
    guts.pub(NEUTRAL);
    guts.pub(NEUTRAL);
  }

  void ass_to_seg(int value, int left, int right=NONE) {
    // [left, right)
    prepare(left, right);
    guts[0].assigned = value;
    _ass_to_seg(1, start, finish);
  }

  int sum_on_seg(int left, int right=NONE) {
    // [left, right)
    prepare(left, right);
    _sum_on_seg(1, start, finish);
    return guts[0].sum;
  }
} kappa;
