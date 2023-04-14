#ifndef NEWTON_FRACTAL_CREATEDERIVATE_H
#define NEWTON_FRACTAL_CREATEDERIVATE_H

#include <cmath>
#include <complex>
#include <iostream>
#include <numeric>
#include <type_traits>
#include <vector>

namespace nf {

template <class T> T inline factorial(T n) {
  if constexpr (!std::is_integral_v<T>) {
    return T(std::tgamma(n - 1));
  }
  if (n < 0) {
    return T(std::tgamma(n - 1));
  }
  if (n == 1 || n == 0) {
    return 1;
  } else {
    T output = 1;
    while (n != 1) {
      output *= n;
      n--;
    }
    return output;
  }
}

using Uint8 = unsigned __int8;
using complex = std::complex<double>;

std::vector<complex> inline permutation(unsigned int n,
                                        std::vector<complex> const &roots,
                                        std::vector<complex> &init) {

  std::vector<complex> output{};

  unsigned int k = 0;
  for (; n != roots.size(); n++) {
    for (unsigned int i = n; i < roots.size(); i++) {
      for (unsigned int j = i; j < roots.size(); j++) {
        output.push_back(roots[j] * init[k]);
      }
      k++;
      if (k == init.size()) {
        return output;
      }
    }
    k++;
    if (k == init.size()) {
      return output;
    }
  }
  return output;
}

void inline createDerivative(std::vector<complex> const &roots,
                             std::vector<complex> &coef) {
  switch (roots.size()) {
  case 0:
    coef.resize(0);
    break;

  case 1:
    coef.resize(1);
    coef.back() = complex(1);
    break;

  case 2:
    coef.resize(2);
    coef.back() = complex(2);
    coef.front() = -(roots[0] + roots[1]);
    break;

  default:
    coef.resize(roots.size());
    coef.back() = complex(double(roots.size()));
    coef[coef.size() - 2] =
            -std::accumulate(roots.begin(), roots.end(), complex(0)) *
            double(roots.size() - 1);
//    coef[coef.size() - 2] =
//            -std::accumulate(roots.begin(), roots.end(), complex(1)) *
//            double(roots.size() - 1);

    std::vector<complex> lastPerm(roots);
    bool isNegative = false;
    for (unsigned int n = 1; n < roots.size() - 1; n++) {
      lastPerm = permutation(n, roots, lastPerm);

      coef[roots.size() - n - 2] =
          std::accumulate(lastPerm.begin(), lastPerm.end(), complex(0)) *
          double(roots.size() - n - 1);

      if (isNegative) {
        coef[roots.size() - n - 2] *= -1;
      }
      isNegative = !isNegative;
    }
    break;
  }
}
} // namespace nf

#endif // NEWTON_FRACTAL_CREATEDERIVATE_H
