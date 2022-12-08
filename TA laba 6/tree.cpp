#include "tree.h"

Tree::Tree() {
	Root = nullptr;
}
void Tree::Show(Node* node, int level, bool right) {
	if (node)
	{
		Show(node->Right, level + 1, true);
		for (int i = 0; i < level; i++) {
			cout << "   ";
		}
		cout << (node == Root ? "|" : (right ? "/" : "\\")) << "---";
		cout << node->Value << endl;
		Show(node->Left, level + 1, false);
	}
}
void Tree::Add(t value) {
	if (!Root) Root = new Node(value, nullptr);
	else {
		Node* tmp = Root;
		while (tmp) {
			if (lt(value, tmp->Value)) {
				if (tmp->Left) tmp = tmp->Left;
				else {
					tmp->Left = new Node(value, tmp);
					return;
				}
			}
			else if (gt(value, tmp->Value)) {
				if (tmp->Right) tmp = tmp->Right;
				else {
					tmp->Right = new Node(value, tmp);
					return;
				}
			}
			else return;
		}
	}
}
int Tree::Min() {
	if (!Root) return 0;

	Node* tmp = Root;
	int count = 0;

	while (tmp->Left) {
		tmp = tmp->Left;
		count++;
	}

	cout << "Min: " << tmp->Value << endl;

	return count;
}
int Tree::Max() {
	if (!Root) return 0;

	Node* tmp = Root;
	int count = 0;

	while (tmp->Right) {
		tmp = tmp->Right;
		count++;
	}

	cout << "Max: " << tmp->Value << endl;

	return count;
}
int Tree::Find(t value) {
	Node* temp = Root;
	int count = 0;
	
	while (temp) {
		if (gt(value, temp->Value)) temp = temp->Right;
		else if (lt(value, temp->Value)) temp = temp->Left;
		else {
			cout << "Value [" << value << "] was found" << endl;
			return count;
		}
		count++;
	}
	cout << "Value [" << value << "] wasn't found. Adding..." << endl;
	Add(value);

	return count;
}
void Tree::Delete(t value) {
	Node* temp = Root;

	while (temp) { // ищем значение которое нужно удалить
		if (gt(value, temp->Value)) temp = temp->Right;
		else if (lt(value, temp->Value)) temp = temp->Left;
		else break;
	}
	if (temp) { //если нашли
		if (!temp->Left && !temp->Right) { //если у найденного значения нет детей
			if (temp->Parent) {
				if (temp->Parent->Left == temp) temp->Parent->Left = nullptr; 
				else temp->Parent->Right = nullptr;
			}
			else Root = nullptr;
		}
		else if (!temp->Left) { // если у найденного значения только правый ребёнок
			if (temp->Parent) {
				if (temp->Parent->Left == temp) temp->Parent->Left = temp->Right;
				else temp->Parent->Right = temp->Right;				
			}
			else Root = temp->Right;

			temp->Right->Parent = temp->Parent;
		}
		else if (!temp->Right) { // если у найденного значения только левый ребёнок
			if (temp->Parent) {
				if (temp->Parent->Left == temp) temp->Parent->Left = temp->Left;
				else temp->Parent->Right = temp->Left;
			}
			else Root = temp->Left;

			temp->Left->Parent = temp->Parent;
		}
		else { // если у найденного значения два ребёнок
			Node* min = temp->Right;

			while (min->Left) min = min->Left; // ищем минимального потомка у правой ветви найдённого значения

			if (min->Right && min->Parent != temp) {
				min->Right->Parent = min->Parent;
				min->Parent->Left = min->Right;
			}
			if (min->Right && min->Parent == temp) {
				min->Right->Parent = min->Parent;
				min->Parent->Right = min->Right;
			}
			else if (min->Parent != temp) min->Parent->Left = nullptr;

			if (temp->Parent) {
				if (temp->Parent->Left == temp) temp->Parent->Left = min;
				else temp->Parent->Right = min;
			}
			else Root = min;

			min->Left = temp->Left;
			min->Left->Parent = min;

			if (min != temp->Right) {
				min->Right = temp->Right;
				min->Right->Parent = min;
			}
			else min->Right = nullptr;

			min->Parent = temp->Parent;
		} 
		//delete temp;
	}
	else { // если не нашли
		cout << "Value wasn't found" << endl;
	}
}
void Tree::PreOrder(Node* node) {
	if (!node) return;

	cout << node->Value << " ";

	PreOrder(node->Left);
	PreOrder(node->Right);
}
void Tree::LeftSmallRot(Node* node) {
	if (!node) return;

	Node* temp = node->Right;

	if (temp) {
		node->Right = temp->Left;
		if (temp->Left) temp->Left->Parent = node;
		temp->Left = node;
		temp->Parent = node->Parent;
		if (node->Parent) {
			if (node == node->Parent->Left) node->Parent->Left = temp;
			else node->Parent->Right = temp;
		}
		node->Parent = temp;
		if (node == Root) Root = temp;
	}
}
void Tree::LeftBigRot(Node* node) {
	if (!node) return;

	RightSmallRot(node->Right);
	LeftSmallRot(node);
}
void Tree::RightSmallRot(Node* node) {
	if (!node) return;

	Node* temp = node->Left;

	if (temp) {
		node->Left = temp->Right;
		if (temp->Right) temp->Right->Parent = node;
		temp->Right = node;
		temp->Parent = node->Parent;
		if (node->Parent) {
			if (node == node->Parent->Left) node->Parent->Left = temp;
			else node->Parent->Right = temp;
		}
		node->Parent = temp;
		if (node == Root) Root = temp;
	}
}
void Tree::RightBigRot(Node* node) {
	if (!node) return;

	LeftSmallRot(node->Left);
	RightSmallRot(node);
}
int Tree::FindDepth(Node* node) {
	if (!node) return 0;

	int a = FindDepth(node->Left);
	int b = FindDepth(node->Right);

	return std::max(a, b) + 1;
}
void Tree::Balance1(Node* node) {
	if (!node) return;

	//cout << "current node " << node->Value << endl;

	Balance1(node->Left);
	Balance1(node->Right);

	if (std::abs(FindDepth(node->Right) - FindDepth(node->Left)) > 1) {
		if (node->Left && FindDepth(node->Left->Right) > FindDepth(node->Left->Left)) {
			RightBigRot(node);
			//cout << "right big rot " << node->Value << endl;
		}
		else if (node->Left || (node->Left && FindDepth(node->Left->Right) <= FindDepth(node->Left->Left))) {
			RightSmallRot(node);
			//cout << "right small rot " << node->Value << endl;
		}
		else if (node->Right && FindDepth(node->Right->Left) > FindDepth(node->Right->Right)) {
			LeftBigRot(node);
			//cout << "left big rot " << node->Value << endl;
		}
		else if (node->Right && FindDepth(node->Right->Left) <= FindDepth(node->Right->Right)) {
			LeftSmallRot(node);
			//cout << "left small rot " << node->Value << endl;
		}
	}
	//Show(Root, 0, false);
	//cout << endl;
}
void Tree::ToLose(Node* node, Node* parent) {
	if (!node) return;

	Node* right = node->Right;
	Node* left = node->Left;

	ToLose(right, parent);
	if (!Root) {
		Root = node;
		node->Parent = nullptr;
	}
	else {
		Node* temp = Root;
		while (temp->Left) temp = temp->Left;
		temp->Left = node;
		node->Parent = temp;
	}
	node->Right = nullptr;
	node->Left = nullptr;

	ToLose(left, parent);
}
void Tree::Balance() {
	if (!Root) return;

	Node* temp = Root;
	Node* temptemp = nullptr;

	Root = nullptr;

	ToLose(temp, nullptr);

	int count = 0;

	temp = Root;
	while (temp->Left) {
		temp = temp->Left;
		count++;
	}
	//count на 1 меньше чем эл-тов
	if (count % 2 == 1 && temp->Parent) RightSmallRot(temp->Parent);

	temp = Root;
	int log2 = std::log2(count);
	for (int j = 0; j < log2; j++) {
		temp = Root;
		for (int i = 0; i < count - 1; i += 2) {
			temp = temp->Left->Left;
			RightSmallRot(temp->Parent->Parent);
		}
		count /= 2;
	}
}
