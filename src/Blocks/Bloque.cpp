#include "Bloque.h"
Bloque::Bloque(std::string nombre, std::string tipo) {
  this->nombre = nombre;
  this->tipo = tipo;
}

std::string Bloque::obtenerNombre() { return nombre; }
