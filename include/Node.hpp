#pragma once

#include "raylib.h"
#include "raymath.h"
#include <vector>
#define GRAVITY 2000

#define NODE_SIZE 10

class Node { 
  public:
  Node(Vector2 position, bool movable);
  bool isMovable() const;
  void update();
  void draw() const;

  Vector2 getPosition() const;
  void setPosition(const Vector2 position);
  
  private:
  Vector2 position_;
  Vector2 velocity_;
  Vector2 acceleration_;
  Vector2 positionPrevious_;
  bool movable_;
  Color color_;
};