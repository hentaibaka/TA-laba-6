#pragma once
#include "include.h"

struct Node {
	t Value;
	Node* Left;
	Node* Right;
	Node* Parent;
	Node(t value, Node* parent);
};