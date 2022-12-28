typedef tuple<ll, ll, ll> ti;
typedef pair<ll, ll> pii;

ti get_line(const pii &a, const pii &b) {
  assert(a != b);
  ti res;
  auto &[A, B, C] = res;
  auto &[x1, y1] = a;
  auto &[x2, y2] = b;
  A = y1 - y2;
  B = x2 - x1;
  C = x1 * y2 - x2 * y1;
  ll g = gcd(A, gcd(B, C));
  A /= g;
  B /= g;
  C /= g;
  if (A < 0 || (A == 0 && B < 0)) {
    A = -A, B = -B, C = -C;
  }
  return res;
}
