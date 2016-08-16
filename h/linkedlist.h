#ifndef LINKEDLIST_H
#define LINKEDLIST_H


#include <fstream>
#include <string>
#include "node.h"

using namespace std;

class Linked_List{

	private:
		Node1 *root;

	public:

		struct Records{

		char character;
		int prob;
		string code;
		int numOfBits;
		double entropy;

		};	
		int recordSize;
		int recordIndex;
		double entropy;
		char character;
		Records *record;
		ifstream inFile;
		ofstream outStream;
		Linked_List();
		Node1 *findSpot(Node1 *root, Node1 *newN);
		void readFile(string file);
		void readDecodeFile(string file);
		void createTable();
		void addNode(int p, string d);	
		void encode(Node1 *root);
		void printEncodeSteps(Node1 *root);
		void printList(Node1 *root);
		void printInOrder(Node1 *tree);
		void getCode(Node1 *T, string code);
		void setRecord(char character,int prob,string code);
		void setRecordSize();
		void displayTableRecords();
		string decode(Node1 *T);
		char getBit();
		bool fileExists(string file);
		void closeFile();

};

#endif