// 1501D
ti ex_gcd(int a, int b) {
  if (a == 0) {
    return ti(b, ZERO, ONE);
  }
  auto [g, x, y] = ex_gcd(b % a, a);
  return ti(g, y - (b / a) * x, x);
}
