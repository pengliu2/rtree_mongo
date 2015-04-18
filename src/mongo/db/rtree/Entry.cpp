/*
 * Entry.cpp
 *
 *  Created on: Apr 12, 2015
 *      Author: assma
 */

#include "Node.h"
#include <iostream>
#include <unordered_map>
#include "BoundingBox.h"
#include "Entry.h"

Entry::Entry(BoundingBox i, Node c){
	I = i;
	childNode = c;
	//childDoc = NULL;
}
Entry::Entry(BoundingBox i, std::unordered_map<int, std::string> c){
	I = i;
	childDoc = c;
}
Node Entry::getChildPointer(){ return childNode; }
std::unordered_map<int, std::string> Entry::getTupleID(){ return childDoc; }
BoundingBox Entry::getI() const { return I; }
int Entry::getNumDimen(){ return I.getNumDimen(); }
void Entry::setChild(Node c){ childNode = c; }
void Entry::setChild(std::unordered_map<int, std::string> h){ childDoc = h; }
void Entry::setI(BoundingBox i){ I = i; }
bool operator==(const Entry& lhs, const Entry& rhs) { 
	return lhs.equal(rhs);
}
bool Entry::equal(const Entry other) const {
	if (I.equal(other.getI()) && childNode.equal(other.childNode) && childDoc == other.childDoc){
		return true;
	}
	else{
		return false;
	}
}

//using namespace std;
/*
Entry::Entry(){}

Entry::Entry(BoundingBox i, Node c){
	I = i;
	childNode = c;
	//childDoc = NULL;
}
Entry::Entry(BoundingBox i, std::unordered_map<int, std::string> c){
	I = i;
	//childNode = NULL;
	childDoc = c;
}
Node Entry::getChildPointer(){ return childNode;}
std::unordered_map<int, std::string> Entry::getTupleID(){ return childDoc; }
BoundingBox Entry::getI(){return I;}
int Entry::getNumDimen(){return I.getNumDimen();}
void Entry::setChild(Node c){childNode = c;}
void Entry::setChild(std::unordered_map<int, std::string> h){ childDoc = h; }
void Entry::setI(BoundingBox i){I=i;}
bool Entry::equal(Entry other){
	if(I.equal(other.getI())&&childNode.equal(other.childNode)&&childDoc==other.childDoc){
		return true;
	}else{
		return false;
	}
}
*/


