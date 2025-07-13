#include "../include/Node.hpp"
#include "../include/Stick.hpp"
#include "../include/game.h"

static std::vector<Node*> nodes;
static std::vector<Stick*> sticks;

// Calculates distance to a line segment (squared). Used mostly to detect distance to edges.
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

    if (isPaused) {
        for (auto node : nodes) {
            node->draw();
        }
    }
    
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
                sticks.push_back(new Stick(firstNode, node)); // Memory concerns, smart pointer implementation otw
                firstNode = NULL;
            } 
        }
    }

    if (firstNode != NULL && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        DrawLineEx(firstNode->getPosition(), mousePos, LINE_THICKNESS, LINE_COLOR);
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !inNode) {
        nodes.push_back(new Node(mousePos, isMovable));
    }    

    // Guard clause
    if (isPaused) return;
    
    for (auto node : nodes) {
        if (node->isMovable())
            node->update();
    }

    // More iterations makes more ridgid edges (komputasi lebih akurat)
    for (int i = 0; i < 20; i++) {
        int j = -1;
        for (auto stick : sticks) {
            j++;
            float dist = linePointDistSqr(stick->a->getPosition(), stick->b->getPosition(), mousePos);
            if (dist < 25 && IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
                sticks.erase(sticks.begin() + j);
                continue;
            }
            stick->update();
        }
    }
}

void Draw()
{
    for (auto stick : sticks) {
        stick->draw();
    }

    // 
}