#ifndef NEWTON_FRACTAL_CREATEFRACTAL_H
#define NEWTON_FRACTAL_CREATEFRACTAL_H

#include <cmath>
#include <complex>
#include <functional>
#include <numeric>
#include <vector>

#include <SFML/Graphics.hpp>

namespace nf {
using sf::Uint8;
using complex = std::complex<double>;

bool nearRoot (complex const& c, double const& rInc, double const& iInc, std::vector<complex> const &roots) {
  for (const auto& root: roots) {
    double dist = std::abs(root - c);
    if (dist < std::min(rInc, iInc) * 5) {
      return true;
    }
  }
  return false;
}

void inline createFractal(unsigned short const& width,
                          unsigned short const& height, double const &rStart,
                          double const &rStop, double const &iStart,
                          double const &iStop, Uint8 N,
                          std::vector<complex> const &roots,
                          std::vector<sf::Color> const &colors,
                          std::vector<complex> const &coef,
                          std::vector<Uint8> &pixels) {

  double rInt = (rStop - rStart);
  double iInt = (iStop - iStart);

  double rInc = rInt / double(width);
  double iInc = iInt / double(height);

  for (unsigned short j = 0; j < height; j++) {
    double const i = iStop - iInc * j;
    for (unsigned short k = 0; k < width; k++) {
      unsigned long long int offset = (j * width + k) * 4;
      complex c{rStart + rInc * k, i};

      if (nearRoot(c, rInc, iInc, roots)) {
        pixels[offset] = 0;
        pixels[offset + 1] = 0;
        pixels[offset + 2] = 0;
        pixels[offset + 3] = 1;
        continue ;
      }

//      for (const auto& root: roots) {
//        double dist = std::abs(root - c);
//        if (dist < std::min(rInc, iInc) * 5) {
//          pixels[offset] = 0;
//          pixels[offset + 1] = 0;
//          pixels[offset + 2] = 0;
//          pixels[offset + 3] = 0;
//          goto rLoop;
//        }
//      }

      for (Uint8 _ = 0; _ < N; _++) {
        complex y = 1;
        std::accumulate(roots.begin(), roots.end(), y,
                        [&](auto init, auto elt) { return init * (c - elt); });

        complex m = 1; // m perché è la "pendenza della retta tangente"
        for (Uint8 index = 0; index < coef.size(); index++) {
          m += coef[index] * pow(c, index);
        }
        c = c - y / m;
      }
      std::vector<double> distances;
      distances.reserve(roots.size());
      std::for_each(roots.begin(), roots.end(), [&](const auto &item) {
        complex dist = c - item;
        distances.push_back(
            std::abs(dist));
      });
      Uint8 minIndex =
          Uint8(&*std::min_element(distances.begin(), distances.end()) -
                distances.data());
      sf::Color color = colors[minIndex];

      pixels[offset] = color.r;
      pixels[offset + 1] = color.g;
      pixels[offset + 2] = color.b;
      pixels[offset + 3] = color.a;
    }
  }

  //    return pixels;
}
} // namespace nf

#endif // NEWTON_FRACTAL_CREATEFRACTAL_H
