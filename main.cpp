#include <SFML/Graphics.hpp>

#include "App.h"

int main() {
  try {
    nf::App app{};

    app.run();

  } catch(...) {
    return 0;
  }
  return 0;
}