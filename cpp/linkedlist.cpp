#include "node.h"
#include "linkedlist.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/*
*Linked List of ordered Nodes in ascending order
*/
Linked_List::Linked_List(){

	root = new Node1();
	root->setValues("dummy",-1);
	recordSize = 0;
	recordIndex = 0;
	entropy = 0;
}
/*
*Read the input file used for creating new nodes
*
*@param file
*/
void Linked_List::readFile(string file){

	int prob;
	string data;
	inFile.open(file);
	outStream.open("C:/LinkedListOutput.txt");

	while(!inFile.eof()){

		inFile >> data >> prob;
		// create a new node
		addNode(prob,data);
	}

	inFile.close();
	setRecordSize();
	encode(root);

}// end readFile

void Linked_List::closeFile(){

	outStream.close();

}// end closeFile
/*
*Check if the file exists
*@param file
*/
bool Linked_List::fileExists(string file)
{
	bool isValid = false;

	inFile.open(file);

	if(inFile.good())
	{
		isValid = true;
		inFile.close();
	}

	return isValid;
}// end fileExists

/*
*Read the input file used for decoding
*
*@param file
*/
void Linked_List::readDecodeFile(string file){

	inFile.open(file);
	Node1 *afterRoot = root->getNext();
	string result = "";

	outStream << "Decoded result: ";
	cout << "Decoded result: ";
	while(!inFile.eof())
	{
		result = decode(afterRoot);
		outStream << result << " ";
		cout << result << " ";
	}

	outStream << endl;
	cout << endl;

	inFile.close();

}// end readDecodeFile
/*
*Retrieve information from nodes to encode and store into entropy table
*
*/
void Linked_List::createTable(){

	string data;
	string code = "";
	Node1 *afterRoot = root->getNext();
	
	getCode(afterRoot,code);
	inFile.close();
	
}// end createTable
/*
*Create and add new node to the linked list
*
*@param p
*@param d
*/
void Linked_List::addNode(int p, string d){

	Node1 *newNode = new Node1();
	recordSize++;
	Node1 *spot;
	newNode->setValues(d,p);
	spot = findSpot(root,newNode);
	newNode->next = spot->next;
	spot->next = newNode;
	printList(root);
	
}// end addNode

/*
*Print the current linked list
*
*@param *root
*/
void Linked_List::printList(Node1 *root){

	Node1 *spot = root->next;

	while(spot != NULL)
	{
		
		outStream << "Node( Probability: " << spot->getProb() << ", Data: " << spot->getData() << ", Left: " << spot->getLeft() << ", Right: " <<
			spot->getRight() << ", Next: " << spot->getNext() << ")";
		
		spot = spot->next;
		if(spot != NULL)
			outStream << "--> ";
	}
	outStream << endl;
}// end printList

/*
*Find a new spot for the new node in the linked list
*@param *root
@param *newN
@return *spot
*/
Node1 *Linked_List::findSpot(Node1 *root, Node1 *newN){

	Node1 *spot;
	spot = root;
	
	// search for a new spot
	do
	{
		if(spot->next != NULL && spot->next->getProb() < newN->getProb())
		{
			spot = spot->next;
		}
		else
			return spot;

	}while(spot->getProb() != -1);

	return spot;
}// end findSpot

/*
*Encode the tree
*
*@param *root
*/
void Linked_List::encode(Node1 *root){
	
	Node1 *spot = root;
	Node1 *newNode;
	Node1 *tempNode = NULL;
	string data;
	int prob;

    while(spot->getNext()->getProb() != 100)
	{
	
		spot = root;
		newNode = new Node1();
		tempNode = NULL;

		// combine 1st node data with 2nd node data
		data = spot->getNext()->getData() + spot->getNext()->getNext()->getData();
		// add 1st node probability with 2nd node probability
		prob = spot->getNext()->getProb() + spot->getNext()->getNext()->getProb();
	
		newNode->setValues(data,prob);
		newNode->setLeft(spot->getNext());
		newNode->setRight(spot->getNext()->getNext());
		spot->setNext(spot->getNext()->getNext()->getNext());
		tempNode = newNode->getLeft();
		tempNode->setNull();
		tempNode = newNode->getRight();
		tempNode->setNull();

		// find a spot for the new node
		spot = findSpot(root,newNode);

		newNode->next = spot->next;
		spot->next = newNode;

		// print new node contents
		cout << endl;
		cout << "New Node(" << newNode->getData() << "," << newNode->getProb() << "," << newNode->getLeft()->getProb()
			 << "," << newNode->getRight()->getProb() << ")" << endl;
		cout << endl;

		outStream << endl;
		outStream << "New Node(" << newNode->getData() << "," << newNode->getProb() << "," << newNode->getLeft()->getProb()
				  << "," << newNode->getRight()->getProb() << ")" << endl;
		outStream << endl;

		printEncodeSteps(root);

	}
	
}// end encode

/*
*Print the current linked list after each encoding step
*
*@param *root
*/
void Linked_List::printEncodeSteps(Node1 *root){

	Node1 *spot = root;

	while(spot != NULL)
	{
		cout << "Node(" << spot->getData() << "," << spot->getProb(); 

		outStream << "Node(" << spot->getData() << "," << spot->getProb(); 

		if(spot->getLeft() != NULL && spot->getRight() != NULL)
		{
			cout << "," << spot->getLeft()->getProb() << "," << spot->getRight()->getProb() << ")";
		
			outStream << "," << spot->getLeft()->getProb() << "," << spot->getRight()->getProb() << ")";
		}else
		{
			cout << ", no left child, no right child)";

			outStream << ", no left child, no right child)";
		}

		spot = spot->next;
		if(spot != NULL)
		{
			cout << "--> ";

			outStream <<  "--> ";
		}
	}
	outStream << endl;
	cout << endl;

}// end printEncodingSteps

/*
*Recursive algorithmn that creates the code for each character and stores it
*in the record table
*
*@param *T
*@param code
*/
void Linked_List::getCode(Node1 *T, string code){

	if(T->getLeft() == NULL && T->getRight() == NULL) 
	{

		character = T->getData()[0];
		setRecord(character,T->getProb(),code);

		return;
	}
	else{

		getCode(T->getLeft(),code + "1");
	    getCode(T->getRight(),code + "0");
	
		}

}// end getCode

/*
*Print the nodes of the tree in order
*
*@param *tree
*/
void Linked_List::printInOrder(Node1 *tree){

	if(tree == NULL)
		return;
	else
	{
		printInOrder(tree->getLeft());
		cout << tree->getData() << endl;
		printInOrder(tree->getRight());
	}
}// end printInOrder

/*
*Set the size of the Records struct
*
*/
void Linked_List::setRecordSize(){

	record = new Records[recordSize];

}// end setRecordSize

/*
*Create a new record for each character. Each record consists of the characters
*letter, probability, code, number of bits and entropy value
*
*@param character
*@param prob
*@param code
*/
void Linked_List::setRecord(char character,int prob,string code){

	record[recordIndex].character = character;
	record[recordIndex].prob = prob;
	record[recordIndex].code = code;
	record[recordIndex].numOfBits = code.length();
	record[recordIndex].entropy = code.length() * prob;
	entropy += record[recordIndex].entropy;
	recordIndex++;
	
}// end setRecord

/*
*Print the entropy table
*
*
*/
void Linked_List::displayTableRecords(){

	outStream << endl;
	outStream << "----------------------------------------------------" << endl;
	outStream << "| Letter | Probability | Code | # Of Bits | Entropy |" << endl;
	outStream << "----------------------------------------------------" << endl;

	cout << "----------------------------------------------------" << endl;
	cout << "| Letter | Probability | Code | # Of Bits | Entropy |" << endl;
	cout << "----------------------------------------------------" << endl;

	for(int i = 0; i < recordSize; i++)
	{

	cout << "   " << record[i].character << "		" << record[i].prob << "	" << 
		record[i].code << "	   " << record[i].numOfBits << "		" <<
		record[i].entropy << endl;

	outStream << "   " << record[i].character << "		" << record[i].prob << "	" << 
		record[i].code << "	   " << record[i].numOfBits << "		" <<
		record[i].entropy << endl;
	}
	outStream << "Entropy: " << entropy/100 << endl;

	cout << "Entropy: " << entropy/100 << endl;

}// end displayTableRecords

/*
*Read a character from the decoding input file and return it
*
@return bit
*/
char Linked_List::getBit(){

	char bit;

	inFile >> bit;

	return bit;
}// end getBit

/*
*Decode the current character
*
*@param *T
*@param bit
*/
string Linked_List::decode(Node1 * T){

	char newBit = -1;
	string letter;

	if(T->getLeft() != NULL && T->getRight() != NULL) 
		newBit = getBit();

	if(T->getLeft() == NULL && T->getRight() == NULL) 
	{		
		letter = T->getData();
	
		return letter;
	}else
		if(newBit == '1')
		{		
			return decode(T->getLeft());
	
		}else
			if(newBit == '0')
			{
				return decode(T->getRight());
		}else
			if(newBit == -1)
			{
				return "An error occurred while traversing the tree!!";
			}
			else
				return letter;

}// end decode