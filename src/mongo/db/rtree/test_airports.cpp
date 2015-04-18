#include <iostream>
#include <fstream>
#include <cstdlib>
#include <unordered_map>
#include "RTree.h"
#include "debug.h"

using namespace std;

int appendRecordFrom(RTree & myIndex, ifstream & input, double box)
{
    string line;
    char buf[32];
    int number;
    double lng, lat;
    int lines = 0;

    box = box/2;

    while (getline(input, line)) {
        sscanf(line.c_str(), "%d,%lf,%lf,%s", &number, &lat, &lng, buf);
		unordered_map<int, string> newDoc = { { number, string(buf) } };
        cout << "*** Inserting <" << number << "> "
             << "<" << lng-box << "," << lat-box << "," << lng+box << "," << lat+box << ">" << endl;
        cout.flush();
        myIndex.insert(createEntryFromDoubles(lng-box, lat-box, lng+box, lat+box, newDoc));
    }
    cout << "*** Dumping Tree starts ***" << endl;
    cout.flush();

    Node* root = myIndex.getRoot();
    int cntLeafEntry = debugDump(root, 0);
    cout << "*** Dumping Tree stopped with [" << cntLeafEntry <<"] leaves ***" << endl;
    cout.flush();
}

int main(int argc, char* argv[])
{
    double box = 0.5;

    if (argc < 2) {
        cout << "Usage:" << endl;
        cout << "\t" << argv[0] << " airports.csv [<box size>]" << endl;
        return -1;
    } else if (argc >= 3) {
        box = atof(argv[2]);
    }

    ifstream airports(argv[1]);
    if (!airports) {
        cout << "File opening failed" << endl;
        return -1;
    }

    vector<Entry*> e;
    Node * R = new Node(2, e, 6, 3, true);
    RTree myIndex(2, R, 6, 3);

    appendRecordFrom(myIndex, airports, box);
    airports.close();
        
}
