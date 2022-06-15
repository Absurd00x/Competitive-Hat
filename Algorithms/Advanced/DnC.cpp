// 1591D
class DNC {
typedef vector<int> vi;
private:
  auto _dnc(auto start, auto finish, auto merge) {
    using T = typename decay<decltype(*start)>::type;
    using IT = typename decay<decltype(start)>::type;
    vector<T> res, part1, part2;
    int p1 = 0, p2 = 0;
    std::function<void(IT, IT)> rec = [&](IT begin, IT end) {
      if (end - begin == 1) {
        res.push_back(*begin);
        return;
      }
      IT mid = begin + (end - begin) / 2;
      p1 = (int)part1.size();
      int tmp = p1;

      rec(begin, mid);
      part1.insert(part1.end(), res.begin(), res.end());
      res.clear();
      rec(mid, end);

      part2.insert(part2.end(), res.begin(), res.end());
      p1 = tmp;
      res.clear();
      int sz1 = (int)part1.size(), sz2 = (int)part2.size();
      while (p1 < sz1 && p2 < sz2) {
        merge(p1, p2, part1, part2, res);
      }
      while (p1 < sz1) {
        res.push_back(part1[p1++]);
      }
      part1.erase(part1.begin() + tmp, part1.end());
      while (p2 < sz2) {
        res.push_back(part2[p2++]);
      }
      p2 = 0;
      part2.clear();
    };
    rec(start, finish);
    return res;
  }
public:
  int64_t calc_inversions(vi &vals) {
    assert(!vals.empty());
    int64_t cnt = 0;
    auto delegate = [&](int &l, int &r, vi &left, vi &right, vi &res) {
      if (left[l] <= right[r]) {
        res.push_back(left[l++]);
      } else {
        cnt += (int)left.size() - l;
        res.push_back(right[r++]);
      }
    };
    _dnc(vals.begin(), vals.end(), delegate);
    return cnt;
  }
} dnc;
