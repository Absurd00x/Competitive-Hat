// 1591D
int calc_inversions(vi &vals) {
  int cnt = 0;
  std::function<vi(int, int)> merge_sort = [&](int left, int right) {
    vi res;
    if (right - left == 1) {
      res.push_back(vals[left]);
      return res;
    }
    int mid = (left + right) / 2;
    vi part1 = merge_sort(left, mid);
    vi part2 = merge_sort(mid, right);
    int sz1 = (int)part1.size();
    int sz2 = (int)part2.size();
    int p1 = 0, p2 = 0;
    while (p1 < sz1 && p2 < sz2) {
      if (part1[p1] <= part2[p2]) {
        res.push_back(part1[p1++]);
      } else {
        cnt += sz1 - p1;
        res.push_back(part2[p2++]);
      }
    }
    while (p1 < sz1) {
      res.push_back(part1[p1++]);
    }
    while (p2 < sz2) {
      res.push_back(part2[p2++]);
    }
    return res;
  };
  merge_sort(0, vals.size());
  return cnt;
}
