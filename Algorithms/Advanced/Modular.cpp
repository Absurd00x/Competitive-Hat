// 1778D
template<typename F, typename S>
F pown(F num, S p) {
  F res(1);
  while (p > 0) {
    if (p & 1) {
      res *= num;
    }
    num *= num;
    p >>= 1;
  }
  return res;
}

template<int32_t MOD>
struct IntMod {
  int32_t value;
  IntMod(int32_t value_ = 0) : value(value_) {
    if (value < 0 || value >= MOD) {
      value %= MOD;
    }
    if (value < 0) {
      value += MOD;
    }
  }
  IntMod(int64_t value_) {
    if (value < 0 || value >= MOD) {
      value %= MOD;
    }
    if (value < 0) {
      value += MOD;
    }
    value = int(value_);
  }
  IntMod& operator+=(IntMod num) {
    value += num.value;
    if (value >= MOD) {
      value -= MOD;
    }
    return *this;
  }
  IntMod& operator-=(IntMod num) {
    value -= num.value;
    if (value < 0) {
      value += MOD;
    }
    return *this;
  }
  IntMod operator+(IntMod num) const {return IntMod(*this) += num;}
  IntMod operator-(IntMod num) const {return IntMod(*this) -= num;}
  IntMod operator*(IntMod num) const {return IntMod(int32_t(1LL * value * num.value % MOD));}
  IntMod& operator*=(IntMod num) {return *this = *this * num;}
  IntMod operator/(IntMod num) const {return *this * pown(num, MOD - 2);}
  IntMod& operator/=(IntMod num) {return *this = *this / num;}
  friend bool operator<(const IntMod<MOD> &a, const IntMod<MOD> &b) {return a.value < b.value;}
  friend bool operator>(const IntMod<MOD>& a, const IntMod<MOD>& b) {return b < a;}
  friend bool operator<=(const IntMod<MOD>& a, const IntMod<MOD>& b) {return !(a > b);}
  friend bool operator>=(const IntMod<MOD>& a, const IntMod<MOD>& b) {return !(a < b);}
  friend bool operator!=(const IntMod<MOD>& a, const IntMod<MOD>& b) {return a < b || b < a;}
  friend bool operator==(const IntMod<MOD>& a, const IntMod<MOD>& b) {return !(a != b);}
  friend ostream& operator<<(ostream& os, const IntMod<MOD> &num) {
    return os << num.value;
  }
};

const int MOD = 998244353;
typedef IntMod<MOD> Int;
