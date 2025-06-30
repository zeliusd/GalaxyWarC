
#include "../external/doctest/doctest.h"
#include "../src/Blocks/Bloque.h"
#include "../src/Player/Player.h"
#include <memory>
#include <utility>

TEST_CASE("Jugador puede obtener un bloque") {
  std::unique_ptr<Bloque> bloque1 =
      std::make_unique<Bloque>("Pasticho", "Melon");
  std::unique_ptr<Player> player = std::make_unique<Player>("Pedro", 4);
  player->agarrarBloque(std::move(bloque1));
  CHECK(player->cantidadObjetosEnInventario() == 1);
}
