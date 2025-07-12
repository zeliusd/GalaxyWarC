
#ifndef VIEW_H
#define VIEW_H
#include "Entity/Entity.h"
#include <memory>
class View {
public:
  virtual void draw() = 0;
  virtual ~View() = default;
  virtual void unloadTexture() = 0;
  virtual std::shared_ptr<Entity> getReference() = 0;
};

#endif
