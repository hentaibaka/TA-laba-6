#include "node.h"

Node::Node(t value, Node* parent) {
	Value = value;
	Left = nullptr;
	Right = nullptr;
	Parent = parent;
}