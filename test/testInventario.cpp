#include <memory>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../external/doctest/doctest.h"
#include "../src/Entity/Blocks/Bloque.h"
#include "../src/Inventory/Inventario.h"

TEST_CASE("Inventario puede añadir un bloque") {
  auto inv = std::make_unique<Inventario>();
  auto bloque = std::make_shared<Bloque>(3, 2);
  inv->addBlock(bloque);
  CHECK(!inv->vacio());
}

TEST_CASE("Inventario puede tener mas de un elemento") {
  auto inv = std::make_unique<Inventario>();
  auto bloque = std::make_shared<Bloque>(3, 2);
  auto bloque2 = std::make_shared<Bloque>(3, 2);
  inv->addBlock(bloque);
  inv->addBlock(bloque2);
  CHECK(inv->cantidadElementos() == 2);
}

TEST_CASE("Se puede sacar un bloque de un inventario y este devuelve el tamaño "
          "correcto") {
  auto inv = std::make_unique<Inventario>();
  auto bloque = std::make_shared<Bloque>(3, 3);
  auto bloque2 = std::make_shared<Bloque>(1, 2);
  inv->addBlock(bloque);
  inv->addBlock(bloque2);
  inv->tirarBloque(1);
  CHECK(inv->cantidadElementos() == 1);
}
