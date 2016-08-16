#ifndef GRAPHCOLORINGPROBLEM_H
#define GRAPHCOLORINGPROBLEM_H

#include <string>
#include <fstream>
#include "hashmapnode.h"
#include "hashmaplinkedlist.h"

using namespace std;

class Graph_Coloring_Problem{

	private:
		HMLinkedList *ll;		
		string colors;
		unsigned int colorCount;

	public:
		Graph_Coloring_Problem();
		ifstream inFile;
		ofstream outStream;
		void computeHashTableSize(string file);
		void storeData(int size,string file);
		void printHashTable();
		void methodOne();
		void methodTwo();
		int determineSpot(int matrixLocation);
		void updateHashTable(int nodeIndex,int colorsIndex);
		void getUserInput();
		string getFile();
};

#endif