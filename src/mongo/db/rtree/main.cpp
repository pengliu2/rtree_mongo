#include <iostream>
#include <algorithm>
#include "RTree.h"
#include "BoundingBox.h"
#include "Entry.h"

using namespace std;

int main() {

	int dimensions = 2; //for this test code, we will stick to a two dimensional RTree
	int max = 4; //maximum number of entries allowed in a Node
	int min = 0; //minimum number of entries allowed in a Node

	std::vector<Entry*> initialEntries;
	for (int i=0; i< 5; i++){
		//create a new HashMap document
		std::unordered_map<int,std::string> newDoc;

		//create a BoundingBox for newDoc

		double rand1 = rand()%50;
		double rand2 = rand()%50;
		double rand3 = rand()%50;
		double rand4 = rand()%50;
		std::vector<double> lower;
		lower.push_back(std::min(rand1, rand2));//I'm assuming that all the boxes exist in a 50x50 coordinate plane
		lower.push_back(std::min(rand3, rand4));
		std::vector<double> upper;
		upper.push_back(std::max(rand1, rand2));
		upper.push_back(std::max(rand3, rand4));
		BoundingBox I = BoundingBox(lower, upper);

		//create an Entry for mydoc (this will be a 'leaf' entry in the tree), and add it to initialEntries
		Entry* myEnt =  new Entry(I, newDoc);
		initialEntries.push_back(myEnt);

		//cout << "Created new Entry with: " << endl;
		//gives me errors about cout...
		//cout << "lower bound = " << lower.at(0) << " " << lower.at(1) << endl;
		//cout << "upper bound = " << upper.at(0) << " " << upper.at(1) << endl;
		//myEnt.print();

	}




	// ADDED BY MATT, IS THIS HOW I ADD A BOX TO THE TREE WITH LOWER LEFT (-10,-5) AND UPPER RIGHT (10,5)??? 
	//create a new HashMap document
	std::unordered_map<int, std::string> newDoc;

	//create a BoundingBox for newDoc

	double fone = 2.0;//-10;
	double ftwo = 3.0;//-5;
	double fthree = 7.0;//10;
	double ffour = 5.0;
	std::vector<double> lower;
	lower.push_back(fone);//I'm assuming that all the boxes exist in a 50x50 coordinate plane
	lower.push_back(ftwo);
	std::vector<double> upper;
	upper.push_back(fthree);
	upper.push_back(ffour);
	BoundingBox I = BoundingBox(lower, upper);

	//create an Entry for mydoc (this will be a 'leaf' entry in the tree), and add it to initialEntries
	Entry* myEnt = new Entry(I, newDoc);
	initialEntries.push_back(myEnt);











	//create a new Node, this will be the root node
	std::vector<Entry*> e;
	Node* R =  new Node(dimensions, e, max, min,true);

	//create a new RTree
	RTree myIndex = RTree(dimensions, R, max, min);

	cout << "created the RTree!" << endl;

	//insert the entries we created into myIndex RTree
	for(int i=0; i<initialEntries.size(); i++){
		Entry* current = initialEntries.at(i);
		myIndex.insert(current);
		cout << "finished inserting entry " << i << endl;
	}
	cout << "inserted all initial entries!" << endl;

	// EDITED BY MATT, IS THIS HOW I SEARCH A BOX WITH LOWER LEFT (-2,-3) AND UPPER RIGHT (2,3)??? IF SO IT SHOULD MATCH THAT MANUAL BOX ABOVE... 
	//search for all entries overlapping a certain BoundingBox
	//create a new BoundingBox
	double rand1 = rand() % 50;//0;//-2.0;// 2.0;//
	double rand2 = rand() % 50;//0;//-3.0;// 1.0;//
	double rand3 = rand() % 50;//50;//2.0;// 4.0;//
	double rand4 = rand() % 50;//50;//3.0;// 4.0;//
	std::vector<double> lowerBB;
	lowerBB.push_back(rand1);
	lowerBB.push_back(rand2);
	std::vector<double> upperBB;
	upperBB.push_back(rand3);
	upperBB.push_back(rand4);
	BoundingBox* IBB = new BoundingBox(lowerBB, upperBB);//this is the bounding box we will be searching for

	std::vector<Entry*> overlapping = myIndex.search(IBB);
	//cout << "found: " << overlapping.size() << " search results when searching for I = ";
	//cout << "lower bounds: " << I.getLower() << endl;
	//cout << "upper bounds: " << I.getUpper() << endl;
	cout << "SEARCH FOUND " << overlapping.size() << " RESULTS" << endl;
	for(int i=0; i<overlapping.size();i++){
		cout << "Entry " << i << endl;
		//TODO print Entry
		cout << overlapping.at(i)->getI().get_ithLower(0)<< " "<< overlapping.at(i)->getI().get_ithLower(1) << endl;
		
		cout << overlapping.at(i)->getI().get_ithUpper(0)<< " " << overlapping.at(i)->getI().get_ithUpper(1) << endl;
		
	}

	//delete an entry in the RTree
	Entry* toBeDel = initialEntries.at(4);
	myIndex.deleteEntry(toBeDel);
	cout << "deleted 1 entry" << endl;
	std::string r;
	cin >> r;
	return 0;
}
