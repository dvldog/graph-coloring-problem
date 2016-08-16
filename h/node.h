#ifndef NODE1_H
#define NODE1_H

#include <string>

using namespace std;

class Node1{
		
	private:
		int prob;
		string data;

	public:
		Node1 *next;
		Node1 *left;
		Node1 *right;
		Node1();
		void setNext(Node1 *n);// set pointer to next node
		void setLeft(Node1 *l);// set left node
		void setRight(Node1 *r);// set right node
		Node1 *getNext();// return next node
		Node1 *getLeft();// return left node
		Node1 *getRight();// return right node
		void setValues(string d, int p);// set values data and probability
		void setData(string d);
		void setProb(int p);
		void setNull();
		string getData();// return data
		int getProb();// return probability
			
};

#endif