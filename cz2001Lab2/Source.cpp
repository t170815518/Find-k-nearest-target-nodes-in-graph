#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include "Node.h"
#include <chrono>
#include <list>

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

int BFS(int _sizeOfNodes, Node* _curNode, vector<int>* _pred, vector<int>* _dist)
{
	bool *visited = new bool[_sizeOfNodes];
	for (int i = 0; i < _sizeOfNodes; i++)
	{
		visited[i] = false;
	}

	// Create a queue for BFS 
	vector<Node*> queue;

	// Mark the current node as visited and enqueue it 
	visited[_curNode->getId()] = true;
	(*_dist).at(_curNode->getId()) = 0;
	queue.push_back(_curNode);

	// 'i' will be used to get all adjacent 
	// vertices of a vertex 
	list<Node*>::iterator it;

	while (!queue.empty())
	{
		// Dequeue a vertex from queue and print it 
		_curNode = queue.front();
		cout << _curNode->getId() << " ";
		queue.erase(queue.begin());

		// Get all adjacent vertices of the dequeued 
		// vertex s. If a adjacent has not been visited,  
		// then mark it visited and enqueue it 
		for (int i = 0; i != _curNode->getVectorOfOtherNodes().size(); ++i)
		{
			//i = _vectorOfNodes.at(_curNode)->getVectorOfOtherNodes().at(i)->getId();
			Node* tempNode;
			if (!visited[_curNode->getVectorOfOtherNodes().at(i)->getId()])
			{
				visited[_curNode->getVectorOfOtherNodes().at(i)->getId()] = true;
				(*_dist)[_curNode->getVectorOfOtherNodes().at(i)->getId()] = (*_dist)[_curNode->getId()]+1;

				(*_pred)[_curNode->getVectorOfOtherNodes().at(i)->getId()] = _curNode->getId();
				queue.push_back(_curNode->getVectorOfOtherNodes().at(i));
				if (_curNode->getVectorOfOtherNodes().at(i)->getIsHospital() == true)
				{
					return _curNode->getVectorOfOtherNodes().at(i)->getId();
				}
			}
		}
	}
	return -1;
}

void printShortestDistance(vector<Node*> _vectorOfNodes, int src, int _sizeOfNodes)
{
	// predecessor[i] array stores predecessor of 
	// i and distance array stores distance of i 
	// from s 

	vector<int> pred(_sizeOfNodes, -1);
	vector<int> dist(_sizeOfNodes, INT_MAX);
	int dest = BFS(_sizeOfNodes, _vectorOfNodes.at(src), &pred, &dist);
	if (dest < 0) {
		cout << "Given source and destination"
			<< " are not connected";
		return;
	}

	// vector path stores the shortest path 
	vector<int> path;
	int crawl = dest;
	path.push_back(crawl);
	while (pred[crawl] != -1) {
		path.push_back(pred[crawl]);
		crawl = pred[crawl];
	}

	// distance from source is in distance array 
	cout << "Shortest path length is : "
		<< dist[dest];

	// printing path from source to destination 
	cout << "\nPath is::\n";
	for (int i = path.size() - 1; i >= 0; i--)
		cout << path[i] << " ";
}

void main()
{
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

	std::ifstream infile("roadNet-CA.txt");
	string line;
	vector<Node*> vectorOfNodes;
	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		int a, b;
		if (!(iss >> a >> b)) 
		{ 
			continue; 
		} // error
		addEdge(&vectorOfNodes, a, b);
	}
	infile.close();
	infile.clear();

	infile.open("hospital.txt");
	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		int a, b;
		if (!(iss >> a))
		{
			continue;
		} // error
		vectorOfNodes.at(a)->setIsHospital(true);
	}
	infile.close();
	infile.clear();

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() << "[µs]" << std::endl;
	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;

	printShortestDistance(vectorOfNodes, 0, vectorOfNodes.size());
	cin.get();
}