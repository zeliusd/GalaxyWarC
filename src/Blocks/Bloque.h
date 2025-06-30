

#ifndef BLOQUE_H
#define BLOQUE_H
#include <string>

class Bloque {
private:
  std::string nombre;
  std::string tipo;

  // No usar strings sino Objetos
public:
  Bloque(std::string nombre, std::string tipo);
  std::string obtenerNombre();
};

#endif
