#include "tree.h"

void t61(Tree* tree) {
	cout << "\n<===========[Task 1]===========>\n\n";

	t values[] = {80, 40, 60, 120, 20, 100, 20, 50, 140, 100, 10, 30, 50, 70, 90, 110, 130, 150};

	for (int i = 0; i < sizeof(values) / sizeof(t); i++) tree->Add(values[i]);

	tree->Show(tree->Root, 0, false);
}
void t62(Tree* tree) {
	cout << "\n<===========[Task 2]===========>\n\n";

	t values[] = { 45, 105, 160, 135, 95, 75, 47 };

	for (int i = 0; i < sizeof(values) / sizeof(t); i++) tree->Add(values[i]);

	tree->Show(tree->Root, 0, false);
}
void t63(Tree* tree) {
	cout << "\n<===========[Task 3]===========>\n\n";

	tree->Min();
	tree->Max();
}
void t64(Tree* tree) {
	cout << "\n<===========[Task 4]===========>\n\n";

	t values[] = { 100, 25, 95, 35, 40, 90 };

	for (int i = 0; i < sizeof(values) / sizeof(t); i++) tree->Find(values[i]);

	tree->Show(tree->Root, 0, false);
}
//============================
void t71(Tree* tree) {
	cout << "\n<===========[Task 1]===========>\n\n";

	t values[] = { 30, 10, 3, 2, 1, 29, 20, 16, 14, 11, 15, 25, 24, 21, 13, 22 };

	for (int i = 0; i < sizeof(values) / sizeof(t); i++) tree->Add(values[i]);

	tree->Show(tree->Root, 0, false);
}
void t72(Tree* tree) {
	cout << "\n<===========[Task 2]===========>\n\n";

	//t values[] = { 30, 10, 3, 2, 1, 29, 20, 16, 14, 11, 15, 25, 24, 21, 13, 22 };
	t values[] = { 22, 3, 25, 29 };

	for (int i = 0; i < sizeof(values) / sizeof(t); i++) {
		cout << "Deleting [" << values[i] << "]..." << endl;
		tree->Delete(values[i]);
		tree->Show(tree->Root, 0, false);
	}
		

	
}
void t73(Tree* tree) {
	cout << "\n<===========[Task 3]===========>\n\n";

	t values[] = { 40, 46, 37, 4, 9, 36, 32, 44, 5, 8, 7, 6 };

	for (int i = 0; i < sizeof(values) / sizeof(t); i++) tree->Add(values[i]);

	tree->Show(tree->Root, 0, false);
}
void t74(Tree* tree) {
	cout << "\n<===========[Task 4]===========>\n\n";

	int min, max, rand;
	t randValue;

	t values[] = {44, 32, 21, 15, 13, 6, 5, 4, 1};

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, (sizeof(values) / sizeof(t)) - 1);

	randValue = values[dist(gen)];

	min = tree->Min();
	max = tree->Max();
	rand = tree->Find(randValue);

	cout << "Steps min: " << min << " | Steps max: " << max << " | Steps random value: " << rand << endl;

	tree->Balance1(tree->Root);
	//(*tree)->Balance();

	tree->Show(tree->Root, 0, false);

	min = tree->Min();
	max = tree->Max();
	rand = tree->Find(randValue);

	cout << "Steps min: " << min << " | Steps max: " << max << " | Steps random value: " << rand << endl;

}
void t75(Tree* tree) {
	cout << "\n<===========[Task 5]===========>\n\n";
	
	cout << "Обход в прямом порядке" << endl;
	tree->PreOrder(tree->Root);
	cout << endl;
}


int main()
{	
	setlocale(LC_ALL, "rus");

	//============6 lab============
	Tree* tree = new Tree();

	cout << "\n<===============[Laba 6]===============>\n\n";

	/*t61(tree);
	t62(tree);
	t63(tree);
	t64(tree);*/

	//============7 lab============

	tree = new Tree();

	cout << "\n<===============[Laba 7]===============>\n\n";

	t71(tree);
	t72(tree);
	t73(tree);
	t74(tree);
	tree->Delete(20);
	t75(tree);
}