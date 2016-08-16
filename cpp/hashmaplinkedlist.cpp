#include "hashmaplinkedlist.h"
#include "hashmapnode.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

HMLinkedList::HMLinkedList()
{
	root = new Node();
	size = 0;

}// end HMLinkedList

void HMLinkedList::setSize(int s)
{
	size = s;
}// end setSize
int HMLinkedList::getSize()
{
	return size;
}// end getSize

void HMLinkedList::insertNode(Node *n)
{
	Node *node = root;
	Node *tempNode = node;
	bool inserted = false;

	while(inserted == false)
	{	
		tempNode = node->getNext();

			if(tempNode == NULL)
			{
				node->setNext(n);
				inserted = true;
			}

			node = node->getNext();
	}
	size++;

}// end insertNode

void HMLinkedList::printNodes()
{
	Node *node = root;
	string line = "";
	ofstream outStream;
	outStream.open("C:/graphcoloringoutput.txt",ios::app);

	if(node->getNext() != NULL)
	{
		cout << "Node " << node->getNext()->getNodeNum();
		
		outStream << "Node " << node->getNext()->getNodeNum();
	}
	else
	{
		cout << "Node " << node->getNodeNum();
		
		outStream << "Node " << node->getNodeNum();
	}

	while(node != NULL)
	{
		cout << "-->" << " (" << node->getCost() << ", " << node->getColor() << ") ";
		outStream << "-->" << " (" << node->getCost() << ", " << node->getColor() << ") ";

		node = node->getNext();
	}

	cout << endl;
	outStream << endl;
	
}// end printNodes

void HMLinkedList::setColor(int cost,char color)
{
	Node *node = root->getNext();

	while(node != NULL)
	{
		if(node->getCost() == cost)
		{
				node->setColor(color);		
		}
		
		node = node->getNext();
	}

}// end setColor

string HMLinkedList::colorsUsed()
{
	Node *node = root->getNext();
	string color;

	while(node != NULL)
	{
		if(node->getColor() != '!')
		{
			color = color + node->getColor();
			
		}

		node = node->getNext();

	}

	return color;

}// end colorsUsed

Node *HMLinkedList::getNode()
{
	return root->getNext();

}// end getNode 