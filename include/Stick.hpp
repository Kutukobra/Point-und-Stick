#pragma once

#include "Node.hpp"
#include <raylib.h>
#include <raymath.h>
#include <vector>
#include <cstdio>

#define LINE_THICKNESS 5
#define LINE_COLOR GREEN

class Stick {
public:
	Stick(Node *a, Node *b);
	void update();
	void draw() const;
	Node *a, *b;
	
private:
	float length;
};