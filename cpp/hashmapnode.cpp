#include "hashmapnode.h"
#include <string>

using namespace std;

Node::Node()
{
	cost = 0;
	next = NULL;
	color = '!';
	nodeNum = -1;
}
void Node::setCost(int i)
{
	cost = i;
}
int Node::getCost(){

	return cost;
}
void Node::setNext(Node *n)
{
	next = n;
}
void Node::setColor(char c)
{
	color = c;
}
char Node::getColor()
{
	return color;
}
void Node::setNodeNum(int n)
{
	nodeNum = n;
}
int Node::getNodeNum()
{
	return nodeNum;
}
Node *Node::getNext()
{
	return next;
}
Node *Node::getNode()
{
	return this;
}