
#include "../external/doctest/doctest.h"
#include "../src/Entity/Asteroid/Asteroid.h"
#include "../src/Entity/Player/Player.h"
#include "Entity/Entity.h"
#include <memory>

TEST_CASE("Un jugador cuando colisiona con un asteroide pierde la vida ") {
  // Arrange
  auto player = std::make_shared<Player>(14, 12);
  auto asteroide = std::make_shared<Asteroid>(14, 12);

  // Act
  player->collideWith(*asteroide);

  // Assert
  CHECK(!player->isAlive());
}

TEST_CASE("Cuando un asteroide colisiona con un jugador se elimina") {
  // Arrange
  auto player = std::make_shared<Player>(14, 12);
  auto asteroide = std::make_shared<Asteroid>(14, 12);

  // Act
  asteroide->collideWith(*player);

  // Assert
  CHECK(!asteroide->isAlive());
}

TEST_CASE("Cuando doble colision entre un jugador y un asteroide, no pasa nada "
          "ambos están muertos (Asteroide)") {
  // Arrange
  auto player = std::make_shared<Player>(14, 12);
  auto asteroide = std::make_shared<Asteroid>(14, 12);

  // Act
  asteroide->collideWith(*player);
  asteroide->collideWith(*player);
  // Assert
  CHECK(!asteroide->isAlive());
}

TEST_CASE("Cuando doble colision entre un jugador y un asteroide, no pasa nada "
          "ambos están muertos (Jugador) ") {
  // Arrange
  auto player = std::make_shared<Player>(14, 12);
  auto asteroide = std::make_shared<Asteroid>(14, 12);

  // Act
  player->collideWith(*asteroide);
  player->collideWith(*asteroide);
  // Assert
  CHECK(!player->isAlive());
}
