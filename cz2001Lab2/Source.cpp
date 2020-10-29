#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include "Node.h"
#include <chrono>

using namespace std;

void addEdge(vector<Node*> *vectorOfNodes, int u, int v)
{
	int increaseVectorSize = u;
	if (u < v)
		increaseVectorSize = v;
	while (vectorOfNodes->size() <= increaseVectorSize)
	{
		Node *newNode = new Node();
		vectorOfNodes->push_back(newNode);
	}

	//Node *thisNode = new Node();
	//Node *thatNode = new Node();
	//thisNode->setThatNode(thatNode);
	//thisNode->setid(u);
	//thatNode->setThatNode(thisNode);
	//thatNode->setid(v);
	vectorOfNodes->at(u)->setid(u);
	vectorOfNodes->at(u)->setThatNode(vectorOfNodes->at(v));
	//vectorOfNodes->at(v)->setid(v);
	//vectorOfNodes->at(v)->setThatNode(vectorOfNodes->at(u));
}

void printGraph(vector<int> adj[], int V)
{
	for (int v = 0; v < V; ++v)
	{
		cout << "\n Adjacency list of vertex " << v << "\n head ";
		for (auto x : adj[v])
			cout << "-> " << x;
		printf("\n");
	}
}

void printGraph(vector<Node*> vectorOfNodes, int V)
{
	//for (int i = 0; i < V; ++i)
	//{
	//	cout << "\n Adjacency list of vertex " << i << "\n head ";
	//	for (auto x : vectorOfNodes.at[i)
	//		cout << "-> " << x;
	//	printf("\n");
	//}
}

void main()
{
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

	std::ifstream infile("roadNet-PA.txt");
	string line;
	vector<Node*> vectorOfNodes;
	int count = 0;
	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		int a, b;
		if (!(iss >> a >> b)) 
		{ 
			continue; 
		} // error

		// process pair (a,b)
		addEdge(&vectorOfNodes, a, b);
		++count;
	}
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() << "[µs]" << std::endl;
	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;
	cin.get();
}