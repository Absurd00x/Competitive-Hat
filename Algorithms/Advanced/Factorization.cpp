const int A = 1e7;
class Factorization {
private:
  int32_t max_num;
  vector<int32_t> primes, min_prime, powered, max_power;
  bool power_built;
  const int32_t NONE = -1;

  vpii extreme_factorize(int x) {
    vpii res;
    while(x > 1) {
      res.emplace_back(min_prime[x], max_power[x]);
      x /= powered[x];
    }
    return res;
  }

  vpii fast_factorize(int x) {
    vpii res;
    while(x > 1) {
      int cnt = 0;
      int factor = min_prime[x];
      while(min_prime[x] == factor) {
        x /= factor;
        ++cnt;
      }
      res.emplace_back(factor, cnt);
    }
    return res;
  }

  vpii sqrt_factorize(int x) {
    int32_t root = (int32_t)sqrtl(x) + 1;
    vpii res;
    for(ui i = 0; i < primes.size() && primes[i] <= root; ++i) {
      int cnt = 0;
      while(x % primes[i] == 0) {
        x /= primes[i];
        ++cnt;
      }
      if (cnt > 0) {
        res.emplace_back(primes[i], cnt);
      }
    }
    if (x > 1) {
      res.emplace_back(x, ONE);
    }
    return res;
  }

public:
  Factorization(int32_t max_num_, bool fast_factorization=false) {
    max_num = max_num_;
    min_prime.resize(max_num + 1, NONE);
    if (fast_factorization) {
      powered.resize(max_num + 1, NONE);
      max_power.resize(max_num + 1, NONE);
    }
    for(int32_t i = 2; i <= max_num; ++i) {
      if (min_prime[i] == NONE) {
        min_prime[i] = i;
        primes.push_back(i);
        if (fast_factorization) {
          powered[i] = i;
          max_power[i] = 1;
        }
      }
      for(ui j = 0; j < primes.size(); ++j) {
        if (primes[j] > min_prime[i]) {
          break;
        }
        ll next = 1LL * i * primes[j];
        if (next > max_num) {
          break;
        }
        min_prime[next] = primes[j];
        if (fast_factorization) {
          powered[next] = primes[j];
          max_power[next] = 1;
          if (primes[j] == min_prime[i]) {
            powered[next] *= powered[i];
            max_power[next] += max_power[i];
          }
        }
      }
    }
    power_built = fast_factorization;
  }

  inline void sanity_check(int x) {
    bool is_small = (x <= 1LL * max_num * max_num);
    bool not_zero = (x != ZERO);
    assert(is_small);
    assert(not_zero);
  }

  inline bool is_prime(int x) {
    sanity_check(x);
    if (x <= max_num) {
      return (min_prime[x] == x);
    }
    int32_t root = (int32_t)sqrtl(x) + 1;
    for(ui i = 0; i < primes.size() && primes[i] <= root; ++i) {
      if (x % primes[i] == ZERO) {
        return false;
      }
    }
    return true;
  }

  inline vpii factorize(int x) {
    sanity_check(x);
    return (x <= max_num
            ? (power_built ? extreme_factorize(x) : fast_factorize(x))
            : sqrt_factorize(x));
  }

  inline vi get_all_divisors(int x, bool sort=false) {
    vpii factors = factorize(x);
    vi divisors;
    int num = 1;
    std::function<void(int)> dfs = [&](int ind) {
      if (ind == (int)factors.size()) {
        divisors.push_back(num);
        return;
      }
      dfs(ind + 1);
      auto &[factor, power] = factors[ind];
      int cur = 1;
      for(int i = 0; i < power; ++i) {
        cur *= factor;
        num *= factor;
        dfs(ind + 1);
      }
      num /= cur;
    };
    dfs(ZERO);
    if (sort) {
      std::sort(all(divisors));
    }
    return divisors;
  }

  inline int calc_all_divisors(int x) {
    vpii factors = factorize(x);
    int res = 1;
    for(auto &[_, power] : factors) {
      res *= (power + 1);
    }
    return res;
  }

  inline int calc_prime_divisors(int x) {
    vpii factors = factorize(x);
    int res = 0;
    for(auto &[_, power] : factors) {
      res += power;
    }
    return res;
  }

} factorization(A, false);

