#ifndef HMLINKEDLIST_H
#define HMLINKEDLIST_H

#include <fstream>
#include <string>
#include "hashmapnode.h"


using namespace std;

class HMLinkedList{

	private:
		Node *root;
		int size;

	public:
		HMLinkedList();
		void insertNode(Node *n);
		void printNodes();
		void setSize(int s);
		int getSize();
		void setColor(int cost,char color);
		string colorsUsed();
		Node *getNode();

};

#endif