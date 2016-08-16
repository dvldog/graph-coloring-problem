#ifndef NODE_H
#define NODE_H
#include <string>

using namespace std;

class Node{

	private:
		int cost;
		int nodeNum;
		Node *next;
		char color;

	public:
		int getCost();
		void setCost(int i);
		void setNext(Node *n);
		void setColor(char c);
		void setNodeNum(int n);
		int getNodeNum();
		char getColor();
		Node *getNext();
		Node *getNode();
		Node();

};

#endif NODE_H