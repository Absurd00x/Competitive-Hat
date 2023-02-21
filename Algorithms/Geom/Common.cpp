typedef tuple<ll, ll, ll> ti;
typedef pair<ll, ll> pii;

ll skew(ll x1, ll x2, ll y1, ll y2) {
  // Псевдоскалярное произведение
  // Его иногда называют векторным или косым произведением
  // skew product
  return x1 * y2 - x2 * y1;
}

ll skew(const pii &one, const pii &other) {
  return one.first * other.second - other.first * one.second;
}

ti get_line(const pii &one, const pii &other) {
  // Тут обязательно использовать лонги из-за коэффициента C
  assert(one != other);
  auto &[x1, y1] = one;
  auto &[x2, y2] = other;
  ti res;
  auto &[A, B, C] = res;
  // Если пройти по оси Ox B единиц, то по оси Oy пройдёшь -A единиц.
  // C отвечает за точку пересечения с осями Ox, Oy.
  // -C/A = точка пересечения с Ox
  // -C/B = точка пересечения с Oy
  // {B, -A} = Направляющий вектор
  // {A, B} = Нормальный вектор
  A = y1 - y2;
  B = x2 - x1;
  C = skew(x1, x2, y1, y2);
  // Чтобы одинаковые прямые имели одинаковые коэффициенты,
  // 1. Делим все коэффициенты на их НОД
  // 2. Делаем коэффициент B неотрицательным
  // 3. Если B = 0, то делаем A неотрицательным
  ll g = gcd(A, gcd(B, C));
  A /= g;
  B /= g;
  C /= g;
  if (B < 0 || (B == 0 && A < 0)) {
    A = -A, B = -B, C = -C;
  }
  return res;
}

bool parallel(const ti &one, const ti &other) {
  auto &[A1, B1, C1] = one;
  auto &[A2, B2, C2] = other;
  // true, если направляющие вектора совпадают
  return (A1 == A2 && B1 == B2);
};

pii intersect(const ti &one, const ti &other) {
  // A1 * x + B1 * y = -C1
  // A2 * x + B2 * y = -C2
  // Метод Краммера. Детерминант равен псевдоскалярному произведению
  // двух векторов, образующих матрицу 2*2 (в двумерном случае, короче)
  int det = skew(A1, A2, B1, B2);
  return pii(skew(-C1, B1, -C2, B2) / det, skew(A1, -C1, A2, -C2) / det);
};

bool clockwise(const pii &one, const pii &other) {
  assert(one != other);
  // Если косое произведение больше нуля, то синус больше нуля, значит по часовой
  return skew(one, other) > 0;
}