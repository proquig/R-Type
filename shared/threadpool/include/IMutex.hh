#pragma once

class IMutex
{
public:
  virtual ~IMutex() = default;
public:
  virtual void lock() = 0;
  virtual void trylock() = 0;
  virtual void unlock() = 0;
};