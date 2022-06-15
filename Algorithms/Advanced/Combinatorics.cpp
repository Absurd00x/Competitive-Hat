// 1546D 1569C
class Combinatorics {
private:
  int pown(int n, int power) {
    int res = 1;
    while (power > 0) {
      if (power & 1) {
        res = int((1LL * res * n) % MOD);
      }
      n = int((1LL * n * n) % MOD);
      power >>= 1;
    }
    return res;
  }

  int mdiv(int num, int den) {
    return int((1LL * num * this->pown(den, MOD - 2)) % MOD);
  }
public:
  vector<int> facts;
  Combinatorics(const int A) {
    facts.resize(A + 1);
    facts[0] = 1;
    for (int i = 1; i <= A; ++i) {
      facts[i] = int((1LL * facts[i - 1] * i) % MOD);
    }
  }

  int cnk(int n, int k) {
    int num = facts[n];
    int den = int((1LL * facts[k] * facts[n - k]) % MOD);
    return mdiv(num, den);
  }

  int ank(int n, int k) {
    int num = facts[n];
    int den = facts[n - k];
    return mdiv(num, den);
  }
} comb(2e5);
