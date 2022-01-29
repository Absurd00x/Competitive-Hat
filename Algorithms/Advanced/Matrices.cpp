// 185A
class Matrix {
private:
  vvi _mul(const Matrix &other) {
    assert(m == other.n);
    vvi res(n, vi(other.m));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        for (int k = 0; k < other.m; ++k) {
          madd(res[i][k], guts[i][j] * other.guts[j][k]);
        }
      }
    }
    return res;
  }

public:
  int n, m;
  vvi guts;

  Matrix(vvi &mat) {
    std::swap(guts, mat);
    n = ssize(guts);
    m = ssize(guts[0]);
  }

  Matrix(int n_) : guts(n_, vi(n_, ZERO)) {
    n = m = n_;
    for (int i = 0; i < n; ++i) {
      guts[i][i] = 1;
    }
  }

  Matrix mul(const Matrix &other) {
    vvi res = _mul(other);
    return Matrix(res);
  }

  void imul(const Matrix &other) {
    vvi res = _mul(other);
    std::swap(guts, res);
  }

  void pown(int power) {
    int sz = ssize(guts);
    Matrix powered(guts);
    (*this) = Matrix(sz);
    while (power > 0) {
      if (power & 1LL) {
        (*this).imul(powered);
      }
      powered.imul(powered);
      power >>= 1;
    }
  }
};
