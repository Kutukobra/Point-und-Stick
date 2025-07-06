#include "../include/Stick.hpp"

Stick::Stick(Node *a, Node *b) : a(a), b(b) {
    length = Vector2Distance(a->getPosition(), b->getPosition());
    printf("New Stick: (%f %f), (%f %f)\n", a->getPosition().x, a->getPosition().y, b->getPosition().x, b->getPosition().y);
    printf("Length: %f\n", length);
}

void Stick::update() {
    Vector2 center = Vector2Scale(Vector2Add(a->getPosition(), b->getPosition()), 0.5);
    Vector2 stickDirection = Vector2Normalize(Vector2Subtract(a->getPosition(), b->getPosition()));
    
    if (a->isMovable())
        a->setPosition(Vector2Add(center, Vector2Scale(stickDirection, length / 2)));

    if (b->isMovable())    
        b->setPosition(Vector2Add(center, Vector2Scale(stickDirection, -length / 2)));
}

void Stick::draw() const {
    DrawLineEx(a->getPosition(), b->getPosition(), LINE_THICKNESS, LINE_COLOR);
}