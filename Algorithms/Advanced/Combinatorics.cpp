// 1546D 1569C
class Combinatorics {
public:
  vi facts;
  Combinatorics(const int A) {
    facts.resize(A + 1);
    facts[0] = 1;
    for (int i = 1; i <= A; ++i) {
      facts[i] = mod(facts[i - 1] * i);
    }
  }

  int cnk(int n, int k) {
    int num = facts[n];
    int den = mod(facts[k] * facts[n - k]);
    return mdiv(num, den);
  }

  int ank(int n, int k) {
    int num = facts[n];
    int den = facts[n - k];
    return mdiv(num, den);
  }
} comb(2e5);
