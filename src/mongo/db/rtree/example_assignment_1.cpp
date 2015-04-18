#include <iostream>
#include <algorithm>
#include "RTree.h"
#include "BoundingBox.h"
#include "Entry.h"

using namespace std;

double assigment1[][4] = {
	{ 1, 14, 2, 16 },
	{ 9, 14, 10, 16 },
	{ 8, 11, 11, 13 },
	{ 4, 9, 5, 11 },
	{ 10, 1, 11, 6 },
	{ 8, 5, 10, 9 },
	{ 1, 1, 3, 14 },
	{ 4, 1, 5, 5 },
	{ -4, -3, -1, -2 },
	{ 0, 0, 2, 1 }, // 10
	{ 1, 2, 3, 4 },
	{ 5, 6, 7, 8 },
	{ 9, 10, 11, 12 },
};

double search_targets[][4] = {
	{ 1, 1, 2, 2 }, /* in R7 */
	{ 4, 9, 5, 11 }, /* is R4 */
	{ 7, 6, 9, 7 }, /* overlaps R6 */
	{ 6, 6, 7, 7 }, /* nowhere */
	{ -2, -5, -1, -1 },
	{ 1, 0, 4, 1 },
	{ -20, -21, 50, 50 },
};

void debugDump(Node *current, int level) {
	vector<Entry*> & entries = current->refEntries();
	bool printDoc = current->isLeaf();

	for (int j = 0; j < level; j++) {
		cout << "\t";
	}
	if (current->isLeaf()) {
		cout << "Leaf ";
	}

	cout << "Node " << current << "has following entries:" << endl;
	for (int i = 0; i < entries.size(); i++) {
		Entry * entry = entries[i];
		for (int j = 0; j < level; j++) {
			cout << "\t";
		}
		cout << "\t" << i << ":";
		if (printDoc) {
			for (auto& x : entry->refTupleID()) {
				cout << x.first;
			}
			cout << " <";
			BoundingBox box = entry->refI();
			vector<double> tmpLower = box.getLower();
			vector<double> tmpUpper = box.getUpper();
			for (auto & x : tmpLower) {
				cout << x << ",";
			}
			for (auto & x : tmpUpper) {
				cout << x << ",";
			}

			cout << ">" << endl;
		}
		else {
			cout << entry;
			cout << "<";
			BoundingBox box = entry->refI();
			vector<double> tmpLower = box.getLower();
			vector<double> tmpUpper = box.getUpper();
			for (auto & x : tmpLower) {
				cout << x << ",";
			}
			for (auto & x : tmpUpper) {
				cout << x << ",";
			}

			cout << ">" << endl;
		}
	}

	if (printDoc) return;

	for (int i = 0; i < entries.size(); i++) {
		Entry * entry = entries[i];
		for (int j = 0; j < level; j++) {
			cout << "\t";
		}
		cout << "\t" << "subtree of " << entry << ":" << endl;
		debugDump(entry->getChildPointer(), level + 1);
	}
}


int main() {
	int dimensions = 2; //for this test code, we will stick to a two dimensional RTree
	int max = 6; //maximum number of entries allowed in a Node
	int min = 3; //minimum number of entries allowed in a Node

	std::vector<Entry*> e;
	Node* R = new Node(dimensions, e, max, min, true);
	RTree myIndex = RTree(dimensions, R, max, min);

	for (int i = 0; i < 13; i++) {
		std::vector<double> lower = std::vector<double>();
		std::vector<double> upper = std::vector<double>();
		lower.push_back(assigment1[i][0]);
		lower.push_back(assigment1[i][1]);
		upper.push_back(assigment1[i][2]);
		upper.push_back(assigment1[i][3]);

		std::unordered_map<int, std::string> newDoc = { { i + 1, "box" } };

		BoundingBox I = BoundingBox(lower, upper); /* can we release lower and upper after this? */
		myIndex.insert(new Entry(I, newDoc));

		cout << "*** dumping index after insering rectangle " << i + 1 << "***" << endl;

		Node* root = myIndex.getRoot();
		debugDump(root, 0);

		cin.get();
	}
	
	cin.get();

	cout << "### start searching ###" << endl;

	for (int i = 0; i < 7; i++) {
		std::vector<double> lowerBB;
		lowerBB.push_back(search_targets[i][0]);
		lowerBB.push_back(search_targets[i][1]);
		std::vector<double> upperBB;
		upperBB.push_back(search_targets[i][2]);
		upperBB.push_back(search_targets[i][3]);
		BoundingBox* IBB = new BoundingBox(lowerBB, upperBB);//this is the bounding box we will be searching for

		cout << "box < ";
		for (int j = 0; j < 4; j++) {
			cout << search_targets[i][j] << " ";
		}
		cout << ">" << " found at:" << endl;

		std::vector<Entry*> overlapping = myIndex.search(IBB);
		if (overlapping.size() <= 0) {
			cout << "NULL" << endl;
		}
		else {
			cout << "BOX WAS FOUND TO INTERSECT: " << overlapping.size() << endl;
			for (int y = 0; y < overlapping.size(); y++) {
				cout << "### " << overlapping.at(y)->getI().get_ithLower(0) << "," << overlapping.at(y)->getI().get_ithLower(1) << " and "
					<< overlapping.at(y)->getI().get_ithUpper(0) << "," << overlapping.at(y)->getI().get_ithUpper(1)
					<< " ###" << endl;
			}
			/*for (auto& x : overlapping[0]->refTupleID()) {
				cout << "### " << x.first << " ###" << endl;
			}*/
		}
	}
	cout << "### end searching ###" << endl;
	cin.get();
	return 0;
}
