// 1501D
tuple<int, int, int> ex_gcd(int a, int b) {
  if (a == 0) {
    return tuple<int, int, int>(b, 0, 1);
  }
  auto [g, x, y] = ex_gcd(b % a, a);
  return {g, y - (b / a) * x, x};
}

tuple<int, int, int> fas(int a, int b, int c) {
  tuple<int, int, int> res = ex_gcd(abs(a), abs(b));
  auto &[g, ra, rb] = res;
  assert(c % g == 0);
  ra *= c / g;
  rb *= c / g;
  if (a < 0) {
    ra = -ra;
  }
  if (b < 0) {
    rb = -rb;
  }
  while (ra == 0 || rb == 0) {
    ra += b / g;
    rb -= a / g;
  }
  return res;
}
