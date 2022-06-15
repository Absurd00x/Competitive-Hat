// 1501D
tuple<int, int, int> ex_gcd(int a, int b) {
  if (a == 0) {
    return ti(b, 0, 1);
  }
  auto [g, x, y] = ex_gcd(b % a, a);
  return {g, y - (b / a) * x, x};
}
