#include "hashmapnode.h"
#include "hashmaplinkedlist.h"
#include "graphcoloringproblem.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

//Constructor 
Graph_Coloring_Problem::Graph_Coloring_Problem()
{
	colors = ("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	colorCount = 0;
	outStream.open("C:/graphcoloringoutput.txt",ios::app);

}// end Graph_Coloring_Problem

/*
*Read the input file and calculate the hash table size
*
*@param file
*/
void Graph_Coloring_Problem::computeHashTableSize(string file)
{
	inFile.open(file);	
	int size = 0;
	colorCount = 0;

	inFile >> size;
	size = size + 1;

	inFile.close();

	storeData(size,file);

}// end computeHashTableSize

/*
*Insert a new node into the hash table
*
*@param size
*@param file
*/
void Graph_Coloring_Problem::storeData(int size,string file)
{
	ifstream inFile;
	inFile.open(file);
	ll = new HMLinkedList[size];
	ll->setSize(size);
	int index = 0;
	int nodeCost = 0;
	int temp;

	inFile >> temp;

	while(!inFile.eof())
	{
		inFile >> index >> nodeCost;
		Node *n = new Node();
		n->setCost(nodeCost);
		n->setNodeNum(index);
		ll[index].insertNode(n);
	}

}// end storeData

/*
*print the hash table contents
*/
void Graph_Coloring_Problem::printHashTable()
{
	for(int i = 0; i < ll->getSize(); i++)
	{
		ll[i].printNodes();
	}
	cout << endl;
	cout << "Total color count: " << ++colorCount << endl;
	cout << "Colors used: ";

	outStream << endl;
	outStream << "Total color count: " << colorCount << endl;
	outStream << "Colors used: ";

	for(unsigned int i = 0; i < colorCount; i++)
	{
		cout << colors[i] << " ";
		outStream << colors[i] << " ";
	}

	cout << endl;
	cout << endl;

	outStream << endl;
	outStream << endl;

}// end printHashTable

/*
*Greedy method one. This method uses a brute force approach to color nodes. The first node in
*the hashtable is colored and each node after that is colored sequentially
*/
void Graph_Coloring_Problem::methodOne()
{
	int iterator = 1;
	unsigned int colorsIndex = 0;
	string colorsUsed;
	int index = 0;
	int colorsUsedIndex = 0;
	int spot;

	// Select first node available and give it a color
	updateHashTable(1,0);

	// Find a color for all remaining nodes
	for(int j = 2; j < ll->getSize(); j++)
	{
		colorsUsed = ll[j].colorsUsed();

		if(colorsUsed.length() == 1)
		{
			spot = determineSpot(j);
			// Update hash table of all the nodes at index j of the matrix array and all other
			// indicies that have edges to the same node number
			updateHashTable(j,spot);
		}
		else
			if(colorsUsed.length() > 1)
			{
				spot = determineSpot(j);
				updateHashTable(j,spot);
			}
			else
			{
				// The current node is not adjacent to any nodes with a color. Give it the first 
				// color; color 'A'
				updateHashTable(j,0);
			}
	}


}// end methodOne

/*
*This greedy method organized the nodes according to the largest edge count. Nodes with the largest
*amount of edges get colors first 
*/
void Graph_Coloring_Problem::methodTwo()
{
	int startIndex = 1;
	int endIndex = ll->getSize() - 1;
	int walkerIndex;
	HMLinkedList temp;
	bool swapOccurred = true;

	// Sort the array of Linked Lists by Number of Nodes each index contains
	while(endIndex >= startIndex || swapOccurred == true){
		
		walkerIndex = startIndex;
		swapOccurred = false;
		
		while(walkerIndex < endIndex){
		
			if(ll[walkerIndex].getSize() < ll[walkerIndex + 1].getSize())
			{
				temp = ll[walkerIndex];
				ll[walkerIndex] = ll[walkerIndex + 1];
				ll[walkerIndex + 1] = temp;
				
				swapOccurred = true;
			}	
			
			walkerIndex++;
		}
		endIndex--;
	}

	int currentNode = 0;
	unsigned int colorsIndex = 0;
	string colorsUsed;
	int index = 0;
	int colorsUsedIndex = 0;
	int spot = 0;

	// Select the first color for the node with the most edges. Update all nodes with this number
	updateHashTable(1,0);

	for(int j = 2; j < ll->getSize(); j++)
	{
		colorsUsed = ll[j].colorsUsed();

		if(colorsUsed.length() == 1)
		{
			spot = determineSpot(j);
			// Update hash table of all the nodes at index j of the matrix array and all other
			// indicies that have edges to the same node number
			updateHashTable(j,spot);
		}
		else
			if(colorsUsed.length() > 1)
			{
				spot = determineSpot(j);
				updateHashTable(j,spot);
			}
			else
			{
				// The current node is not adjacent to any nodes with a color. Give it the first 
				// color; color 'A'
				updateHashTable(j,0);

			}
	}

}// end methodTwo

/*
* Determine the spot of the node to be updated
*
*@param matrixLocation
*/
int Graph_Coloring_Problem::determineSpot(int matrixLocation)
{
	unsigned int index = 0;
	string colorsUsed = ll[matrixLocation].colorsUsed();
	string newColors = ("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	char color = '!';
	bool found = false;

	if(colorsUsed.length() == 1)
	{
		if(ll[matrixLocation].colorsUsed() == "A")
		{
			index++;
		}else
			index = 0;
	}else
	{		
		// Loop through the colors array and determine which colors are being used
		for(unsigned int i = 0; i < colorsUsed.length(); i++)
		{
			for(unsigned int j = 0; j < newColors.length(); j++)
			{
				if(colorsUsed[i] == newColors[j])
				{
					newColors[j] = '!';
				}
			}
		}

		// Select the next index for the new color
		// color = (ABCDEF...Z)
		while(found == false && index < newColors.length())
		{	
			color = newColors[index];

			if(color != '!')
			{
				found = true;
			
				// Keep track of how many colors are being used
					if(index != 0 && colorCount < index)
					{
							colorCount = index;
					}

			}else
				{
					index++;
				}				
		}
		
	}

	return index;

}// end determineSpot

/*
*@param nodeIndex
*@param colorsIndex
*/
void Graph_Coloring_Problem::updateHashTable(int nodeIndex,int colorsIndex)
{
	Node *node = ll[nodeIndex].getNode();
	int nodeNum;

	if(node->getNext() != NULL)
		nodeNum = node->getNext()->getNodeNum();

	// Set the color for the current node
	for(int i = 1; i < ll->getSize(); i++)
	{
		ll[i].setColor(nodeNum,colors[colorsIndex]);
	}
}// end updateHashTable

void Graph_Coloring_Problem::getUserInput()
{
	string file;
	int answer;
	bool done = false;

	while(done == false)
	{

		cout << "Which greedy method would you like to use?" << endl;
		cout << "1) Method One" << endl;
		cout << "2) Method Two" << endl;
		cout << "3) Finished" << endl;
		cin >> answer;

			if(answer == 1)
			{
				file = getFile();
				computeHashTableSize(file);
				methodOne();
				printHashTable();

			}else
				if(answer == 2)
				{
					file = getFile();
					computeHashTableSize(file);
					methodTwo();
					printHashTable();

				}
				else
					if(answer == 3)
					{
						done = true;
						cout << "Program terminated.";
					}
					else
					{
						cout << "Invalid response!!! Please try again." << endl;
						cin.clear();
						cin.ignore(10000,'\n');
				
					}
		}
}// end getUserInput

string Graph_Coloring_Problem::getFile()
{
	string file;
	string location = "C:/";
	bool isValid = false;

	while(isValid == false)
	{
		cout << "Enter file name with extension: ";
		cin >> file;

		file = location + file;
		inFile.open(file);

		if(inFile.good())
		{
			isValid = true;
			inFile.close();
		}else
		{
			cout << "File does not exist!!" << endl;
		}
	}

	return file;

}// end getFile