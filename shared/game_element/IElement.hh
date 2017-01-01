#ifndef IELEMENT_HH_
#define IELEMENT_HH_

#include <vector>
#include <cstdint>

namespace RType
{
class IElement
{
public:
  virtual ~IElement() = default;
  virtual uint32_t getIdFrom() const = 0;
  virtual uint32_t getId() const = 0;
  virtual uint16_t getType() const = 0;
  virtual uint16_t getX() const = 0;
  virtual uint16_t getY() const = 0;
  virtual uint16_t getSizeX() const = 0;
  virtual uint16_t getSizeY() const = 0;
  virtual uint16_t getHp() const = 0;
  virtual uint16_t getDamage() const = 0;
  virtual float getAngle() const = 0;
  virtual char getSpeed() const = 0;

  virtual void setIdFrom(uint32_t) = 0;
  virtual void setId(uint32_t) = 0;
  virtual void setType(uint16_t) = 0;
  virtual void setX(uint16_t) = 0;
  virtual void setY(uint16_t) = 0;
  virtual void setHp(uint16_t) = 0;
  virtual void setDamage(uint16_t) = 0;
  virtual void setSizeX(uint16_t) = 0;
  virtual void setSizeY(uint16_t) = 0;
  virtual void setAngle(float) = 0;
  virtual void setSpeed(char) = 0;

  virtual std::vector<IElement *> collideWith(IElement *) = 0;
  virtual bool						move() = 0;
};
};

#endif