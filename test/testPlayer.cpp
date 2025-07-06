
#include "../external/doctest/doctest.h"
#include "../src/Blocks/Bloque.h"
#include "../src/Player/Player.h"
#include <memory>

TEST_CASE("Jugador puede obtener un bloque") {
  std::shared_ptr<Bloque> bloque1 = std::make_shared<Bloque>(2, 3);
  std::unique_ptr<Player> player = std::make_unique<Player>(5, 4);
  player->agarrarBloque(bloque1);
  CHECK(player->cantidadObjetosEnInventario() == 1);
}

TEST_CASE("Jugador puede obtener más de un bloque") {
  std::unique_ptr<Player> player = std::make_unique<Player>(5, 4);
  player->agarrarBloque(std::make_shared<Bloque>(3, 2));
  player->agarrarBloque(std::make_shared<Bloque>(3, 2));
  CHECK(player->cantidadObjetosEnInventario() == 2);
}
