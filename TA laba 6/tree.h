#pragma once
#include "node.h"

struct Tree {
	Node* Root;
	Tree();
	void Show(Node* node, int level, bool left);
	void Add(t value);
	int Min();
	int Max();
	int Find(t value);
	void Delete(t value);
	void LeftSmallRot(Node* node);
	void LeftBigRot(Node* node);
	void RightSmallRot(Node* node);
	void RightBigRot(Node* node);
	int FindDepth(Node* node);
	void Balance1(Node* node);
	void ToLose(Node* node, Node* parent);
	void Balance();
	void PreOrder(Node* node);
};