// 1546D 1569C
class Combinatorics {
private:
  int pown(int n, int power) {
    int res = 1;
    while (power > 0) {
      if (power & 1) {
        res = int(1LL * res * n % MOD);
      }
      n = int(1LL * n * n % MOD);
      power >>= 1;
    }
    return res;
  }

public:
  vector<int> facts, ifacts;
  Combinatorics(const int A) {
    facts.resize(A + 1);
    ifacts.resize(A + 1);
    facts[0] = ifacts[0] = 1;
    for (int i = 1; i <= A; ++i) {
      facts[i] = int(1LL * facts[i - 1] * i % MOD);
    }
    ifacts[A] = this->pown(facts[A], MOD - 2);
    for (int i = A - 1; i > 0; --i) {
      ifacts[i] = 1LL * (i + 1) * ifacts[i + 1] % MOD;
    }
  }

  int cnk(int n, int k) {
    return int(facts[n] * (1LL * ifacts[k] * ifacts[n - k] % MOD) % MOD);
  }

  int ank(int n, int k) {
    return int(facts[n] * ifacts[n - k] % MOD);
  }
} comb(2e5);
