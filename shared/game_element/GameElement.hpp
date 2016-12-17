#ifndef R_TYPE_GAMEELEMENT_HPP_
#define R_TYPE_GAMEELEMENT_HPP_

#include <cstdint>

class GameElement
{
private:
  uint32_t _idFrom;
  uint32_t _id;
  uint16_t _type;
  uint16_t _x;
  uint16_t _y;
  uint16_t _size_x;
  uint16_t _size_y;
  float _angle;
  char _speed;

public:
  GameElement();
  ~GameElement();
  uint32_t getIdFrom() const;
  uint32_t getId() const;
  uint16_t getType() const;
  uint16_t getX() const;
  uint16_t getY() const;
  uint16_t getSizeX() const;
  uint16_t getSizeY() const;
  float getAngle() const;
  char getSpeed() const;

  void setIdFrom(uint32_t);
  void setId(uint32_t);
  void setType(uint16_t);
  void setX(uint16_t);
  void setY(uint16_t);
  void setSizeX(uint16_t);
  void setSizeY(uint16_t);
  void setAngle(float);
  void setSpeed(char);
};

#endif //R_TYPE_GAMEELEMENT_HPP_