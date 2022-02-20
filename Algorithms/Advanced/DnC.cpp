// 1591D
auto dnc(auto begin, auto end, auto merge) {
  using T = typename std::decay<decltype(*begin)>::type;
  vector<T> res;
  if (end - begin == 1) {
    res.push_back(*begin);
    return res;
  }
  auto mid = begin + (end - begin) / 2;
  vector<T> part1 = dnc(begin, mid, merge);
  vector<T> part2 = dnc(mid, end, merge);
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
}

int calc_inversions(vi &vals) {
  int cnt = 0;
  dnc(all(vals), [&](int &l, int &r, vi &left, vi &right, vi &res) {
    if (left[l] <= right[r]) {
      res.pub(left[l++]);
    } else {
      cnt += ssize(left) - l;
      res.pub(right[r++]);
    }
  });
  return cnt;
}
