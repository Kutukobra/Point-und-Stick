#include "../include/Node.hpp"
#include <cstdio>

Node::Node(Vector2 position, bool movable) : position_(position), movable_(movable) {
    positionPrevious_ = position_;
    color_ = movable ? WHITE : RED;
}

Vector2 Node::getPosition() const {
    return position_;
}

void Node::setPosition(const Vector2 position) {
    position_ = position;
}

bool Node::isMovable() const {
    return movable_;
}

void Node::update() {
    velocity_ = Vector2Subtract(position_, positionPrevious_);
    positionPrevious_ = position_;

    acceleration_ = {0, GRAVITY};

    position_ = Vector2Add(position_, Vector2Add(velocity_, Vector2Scale(acceleration_, GetFrameTime() * GetFrameTime()))); // Verlet integration
}

void Node::draw() const {
    DrawCircleV(position_, NODE_SIZE, color_);
}
