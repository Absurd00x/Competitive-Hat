// 1591D
auto dnc(auto start, auto finish, auto merge) {
  using T = typename std::decay<decltype(*start)>::type;
  using IT = typename std::decay<decltype(start)>::type;
  vector<T> res, part1, part2;
  int p1 = 0, p2 = 0;
  std::function<void(IT, IT)> rec = [&](IT begin, IT end) {
    if (end - begin == 1) {
      res.push_back(*begin);
      return;
    }
    IT mid = begin + (end - begin) / 2;
    p1 = ssize(part1);
    int tmp = p1;

    rec(begin, mid);
    part1.insert(part1.end(), all(res));
    res.clear();
    rec(mid, end);

    part2.insert(part2.end(), all(res));
    p1 = tmp;
    res.clear();
    while (p1 < ssize(part1) && p2 < ssize(part2)) {
      merge(p1, p2, part1, part2, res);
    }
    while (p1 < ssize(part1)) {
      res.pub(part1[p1++]);
    }
    part1.erase(part1.begin() + tmp, part1.end());
    while (p2 < ssize(part2)) {
      res.pub(part2[p2++]);
    }
    p2 = 0;
    part2.clear();
  };
  rec(start, finish);
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
