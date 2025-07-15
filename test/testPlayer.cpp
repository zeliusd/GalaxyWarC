
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../external/doctest/doctest.h"
#include "../src/Entity/Player/Player.h"
#include <memory>
TEST_CASE("Jugador se crea y su posicion es correcta") {

  auto player = std::make_shared<Player>(14, 12);

  CHECK(player->getY() == 12);
}
