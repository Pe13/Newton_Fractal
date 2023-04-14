#ifndef NEWTON_FRACTAL_APP_H
#define NEWTON_FRACTAL_APP_H

#include <complex>
#include <numeric>
#include <vector>

#include "SFML/Graphics.hpp"

#include "createDerivative.h"
#include "createFractal.h"

namespace nf {
using std::exp;
class App {

  unsigned short const _width{400};
  unsigned short const _height{400};

  sf::RenderWindow _window;
  sf::Event _event{};

  double _rStart{-1.5};
  double _rStop{1.5};
  double _iStart{-1.5};
  double _iStop{1.5};

  std::vector<std::complex<double>> _roots{
      {1, 0},
      exp(std::complex<double>{0, 4 * M_PI / 3}),
      exp(std::complex<double>{0, 2 * M_PI / 3})};
  // coefficienti del polinomio derivata, l'indice è uguale al grado
  std::vector<std::complex<double>> _coefficientsOfDerivative{};

  std::vector<sf::Color> _colors{sf::Color::Cyan, sf::Color::Red,
                                 sf::Color::Yellow};

  std::vector<sf::Uint8> _pixels;

  sf::Texture _texture;
  sf::Sprite _sprite;

  bool redrawNeeded = true;

public:
  App() : _window{{_width, _height}, "Newtn Fractal"} {
    _window.setFramerateLimit(30);

    _texture.create(_width, _height);
    _pixels.resize(_width * _height * 4);

    createDerivative(_roots, _coefficientsOfDerivative);
  }

  void initGame() {}

  void handleEvent() {

    while (_window.pollEvent(_event)) {
      if (_event.type == sf::Event::Closed) {
        _window.close();
      }
    }
  }

  void draw() {
    if (!redrawNeeded) {
      return;
    }
    redrawNeeded = false;
    createFractal(_width, _height, _rStart, _rStop, _iStart, _iStop, 10, _roots,
                  _colors, _coefficientsOfDerivative, _pixels);

    _texture.update(_pixels.data());
    _sprite.setTexture(_texture);
    _window.draw(_sprite);

    _window.display();
  }

  void run() {
    initGame();

    while (_window.isOpen()) {
      handleEvent();
      draw();
    }
  }
};
} // namespace nf

#endif // NEWTON_FRACTAL_APP_H
