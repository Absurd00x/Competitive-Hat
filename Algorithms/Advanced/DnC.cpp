// 1591D
int calc_inversions(vi &vals) {
  using mft = std::function<void(int&, int&, vi&, vi&, vi&)>;
  std::function<vi(int, int, mft)> dnc = [&](int left, int right, mft merge) {
    vi res;
    if (right - left == 1) {
      res.push_back(vals[left]);
      return res;
    }
    int mid = (left + right) / 2;
    vi part1 = dnc(left, mid, merge);
    vi part2 = dnc(mid, right, merge);
    int p1 = 0, p2 = 0;
    while (p1 < ssize(part1) && p2 < ssize(part2)) {
      merge(p1, p2, part1, part2, res);
    }
    while (p1 < ssize(part1)) {
      res.pub(part1[p1++]);
    }
    while (p2 < ssize(part2)) {
      res.pub(part2[p2++]);
    }
    return res;
  };
  int cnt = 0;
  dnc(ZERO, ssize(vals), [&](int &l, int &r, vi &left, vi &right, vi &res) {
    if (left[l] <= right[r]) {
      res.pub(left[l++]);
    } else {
      cnt += ssize(left) - l;
      res.pub(right[r++]);
    }
  });
  return cnt;
}
