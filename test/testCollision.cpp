
#include "../external/doctest/doctest.h"
#include "../src/Entity/Asteroid/Asteroid.h"
#include "../src/Entity/Boss/Boss.h"
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

TEST_CASE("Cuando el jugador colisiona con un boss pierde la vida") {
  // Arrange
  auto player = std::make_shared<Player>(14, 12);
  auto boss = std::make_shared<Boss>(14, 12);

  // Act
  player->collideWith(*boss);

  // Assert
  CHECK(!player->isAlive());
}

TEST_CASE("Cuando el boss colisiona con una bala random no se le disminuye la "
          "salud") {
  // Arrange
  auto bullet = std::make_shared<Bullet>(14, 12, 0, 0, nullptr);
  auto boss = std::make_shared<Boss>(14, 12);
  auto salud = boss->getHealth();

  // Act
  boss->collideWith(*bullet);

  // Assert
  CHECK(boss->getHealth() == salud);
}

TEST_CASE("Cuando el jugador colisiona con una bala que no es suya muere") {
  // Arrange
  auto bullet = std::make_shared<Bullet>(14, 12, 0, 0, nullptr);
  auto player = std::make_shared<Player>(14, 12);

  // Act
  player->collideWith(*bullet);

  // Assert
  CHECK(!player->isAlive());
}

TEST_CASE("Cuando el jugador colisiona con una bala que es suya no muere") {
  // Arrange
  auto player = std::make_shared<Player>(14, 12);
  auto bullet = player->shotBullet();

  // Act
  player->collideWith(*bullet);

  // Assert
  CHECK(player->isAlive());
}

TEST_CASE(
    "Cuando el boss colisiona con una bala suya no se le disminuye la salud") {
  // Arrange

  auto boss = std::make_shared<Boss>(14, 12);
  auto bullets = boss->shotBullets();
  auto salud = boss->getHealth();

  // Act
  boss->collideWith(*bullets.begin()->get());

  // Assert
  CHECK(boss->getHealth() == salud);
}

TEST_CASE("Cuando el boss colisiona con una bala que es del jugador se le "
          "disminuye la salud") {
  // Arrange

  auto boss = std::make_shared<Boss>(14, 12);
  auto player = std::make_shared<Player>(14, 12);
  auto bullet = player->shotBullet();
  auto salud = boss->getHealth();

  // Act
  boss->collideWith(*bullet);

  // Assert
  CHECK(boss->getHealth() != salud);
}

TEST_CASE("Cuando el jugador colisiona con una bala del boss pierde la vida") {
  // Arrange

  auto boss = std::make_shared<Boss>(14, 12);
  auto bullets = boss->shotBullets();
  auto player = std::make_shared<Player>(14, 12);

  // Act
  player->collideWith(*bullets.begin()->get());

  // Assert
  CHECK(!player->isAlive());
}
