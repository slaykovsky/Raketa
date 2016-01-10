#include <cmath>

template <typename T> std::vector<T> sieve_of_eratosthenes(T n) {
  std::vector<T> result;
  if (n < 2) {
    return result;
  }

  std::vector<bool> input(n + 1, true);

  T sqrtN = (T)sqrt(n);

  for (T i = 2; i <= sqrtN; i++) {
    if (!input[i]) {
      continue;
    }

    for (T j = i * i; j <= n; j += i) {
      input[j] = false;
    }
  }

  result.push_back(2);

  for (T i = 3; i <= n; i += 2) {
    if (input[i]) {
      result.push_back(i);
    }
  }

  return result;
}
