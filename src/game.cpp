#include "../include/Node.hpp"
#include "../include/Stick.hpp"
#include "../include/game.h"

std::vector<Node*> nodes;
std::vector<Stick*> sticks;

float linePointDistSqr(Vector2 p1, Vector2 p2, Vector2 pt) {
    Vector2 a = Vector2Subtract(pt, p1);
    Vector2 b = Vector2Subtract(p2, p1);
    float proj = Vector2DotProduct(a, b);
    float d = proj / Vector2LengthSqr(b);
    Vector2 intersection = Vector2Add(p1, Vector2Scale(b, d));
    if (d >= 1.0f) intersection = p2;
    if (d <= 0.0f) intersection = p1;
    return Vector2DistanceSqr(intersection, pt);
}

void Setup()
{

}


void Update()
{
    static Node *firstNode = NULL;
    static bool isPaused = true;
    static bool isMovable = true;
    
    if (IsKeyPressed(KEY_SPACE)) isPaused = !isPaused;
    if (IsKeyPressed(KEY_A)) {
        isMovable = !isMovable;
        printf("%s\n", isMovable ? "MOVABLE" : "STATIC");
    }
    
    Vector2 mousePos = {(float)GetMouseX(), (float)GetMouseY()};
    bool inNode = false;
    for (auto node : nodes) {
        if (Vector2Distance(mousePos, node->getPosition()) < NODE_SIZE + 3) {
            inNode = true;
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                firstNode = node;
                break;
            } else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && firstNode != NULL && firstNode != node) {
                sticks.push_back(new Stick(firstNode, node));
                firstNode = NULL;
            } 
        }
    }

    if (firstNode != NULL && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        DrawLineEx(firstNode->getPosition(), mousePos, LINE_THICKNESS, LINE_COLOR);
    }

    // Guard clause
    if (inNode) return;

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        nodes.push_back(new Node(mousePos, isMovable));
    }


    if (isPaused) return;
    
    for (auto node : nodes) {
        if (node->isMovable())
            node->update();
    }

    for (int i = 0; i < 1; i++) {
        int j = 0;
        for (auto stick : sticks) {
            float dist = linePointDistSqr(stick->a->getPosition(), stick->b->getPosition(), mousePos);
            if (dist < 25 && IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
                sticks.erase(sticks.begin() + j);
            }
            stick->update();
            j++;
        }
    }
}

void Draw()
{
    for (auto stick : sticks) {
        stick->draw();
    }

    for (auto node : nodes) {
        node->draw();
    }
}