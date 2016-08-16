#include "node.h"
#include <string>

using namespace std;

Node1::Node1(){

	next = NULL;
	left = NULL;
	right = NULL;
	prob = -1;
	data = "";
}
void Node1::setNext(Node1 *n){
	
	next = n;
}
void Node1::setNull(){

	next = NULL;
}
void Node1::setLeft(Node1 *l){

	left = l;
}
void Node1::setRight(Node1 *r){

	right = r;
}
void Node1::setValues(string d, int p){
	
	data = d;
	prob = p;
}
Node1 *Node1::getNext(){

	return next;
}
Node1 *Node1::getLeft(){

	return left;
}
Node1 *Node1::getRight(){

	return right;
}
string Node1::getData(){

	return data;
}
int Node1::getProb(){

	return prob;
}