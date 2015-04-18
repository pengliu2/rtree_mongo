#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include "Node.h"
#include "BoundingBox.h"
#include "Entry.h"

using namespace std;

int debugDump(Node *current, int level) {
    int cntLeafEntry = 0;
	vector<Entry*> & entries = current->refEntries();
	bool printDoc = current->isLeaf();

	for (int j = 0; j < level; j++) {
		cout << "\t";
	}
	if (current->isLeaf()) {
		cout << "Leaf ";
        cntLeafEntry += entries.size();
	}

	cout << "[Level "<< level << "] Node " << current;
    cout << " (" << current->getParent() <<")";
    cout << " has following entries:" << endl;
	for (int i = 0; i < entries.size(); i++) {
		Entry * entry = entries[i];
		for (int j = 0; j < level; j++) {
			cout << "\t";
		}
		cout << "\t" << i << ": ";
		if (printDoc) {
			for (auto& x : entry->refTupleID()) {
                
				cout << "<" << x.first << "> ";
                cout << x.second;
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
	}

	if (printDoc) return cntLeafEntry;

	for (int i = 0; i < entries.size(); i++) {
		Entry * entry = entries[i];
		for (int j = 0; j < level; j++) {
			cout << "\t";
		}
		cout << "\t" << "subtree of " << entry << ":" << endl;
		cntLeafEntry += debugDump(entry->getChildPointer(), level + 1);
	}
    return cntLeafEntry;
}

Entry * createEntryFromDoubles(double left, double lower, double right, double upper, unordered_map<int, string> newDoc)
{
    std::vector<double> lowerleft = std::vector<double>();
    std::vector<double> upperright = std::vector<double>();

    lowerleft.push_back(left);
    lowerleft.push_back(lower);
    upperright.push_back(right);
    upperright.push_back(upper);

    BoundingBox I = BoundingBox(lowerleft, upperright); /* can we release lower and upper after this? */

    return new Entry(I, newDoc);
}
