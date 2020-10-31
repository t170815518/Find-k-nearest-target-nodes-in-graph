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

int BFS(int _sizeOfNodes, Node* _curNode, vector<int>* _pred, vector<int>* _dist, int _numberOfHospitals)
{
	Node* originNode = _curNode;
	int hospitalPassed = 0;
	int crawl = -1;
	int previousCrawl = -2;
	bool *visited = new bool[_sizeOfNodes];
	for (int i = 0; i < _sizeOfNodes; i++)
	{
		visited[i] = false;
	}

	// Create a queue for BFS 
	list<Node*> queue;

	// Mark the current node as visited and enqueue it 
	visited[_curNode->getId()] = true;
	(*_dist).at(_curNode->getId()) = 0;
	queue.push_back(_curNode);

	// 'i' will be used to get all adjacent 
	// vertices of a vertex 
	list<Node*>::iterator it;
	vector<int> nearestHospital;
	while (!queue.empty())
	{
		// Dequeue a vertex from queue and print it 
		_curNode = queue.front();
		cout << _curNode->getId() << " ";
		queue.pop_front();

		// Get all adjacent vertices of the dequeued 
		// vertex s. If a adjacent has not been visited,  
		// then mark it visited and enqueue it 
		for (int i = 0; i != _curNode->getVectorOfOtherNodes().size(); ++i)
		{
			//i = _vectorOfNodes.at(_curNode)->getVectorOfOtherNodes().at(i)->getId();
			if (!visited[_curNode->getVectorOfOtherNodes().at(i)->getId()])
			{
				visited[_curNode->getVectorOfOtherNodes().at(i)->getId()] = true;
				(*_dist)[_curNode->getVectorOfOtherNodes().at(i)->getId()] = (*_dist)[_curNode->getId()]+1;

				(*_pred)[_curNode->getVectorOfOtherNodes().at(i)->getId()] = _curNode->getId();
				queue.push_back(_curNode->getVectorOfOtherNodes().at(i));
				if (_curNode->getVectorOfOtherNodes().at(i)->getIsHospital() == true)
				{
					crawl = _curNode->getVectorOfOtherNodes().at(i)->getId();
					nearestHospital.push_back(crawl);
					while ((*_pred)[crawl] != -1) {
						nearestHospital.push_back((*_pred)[crawl]);
						crawl = (*_pred)[crawl];
					}
					originNode->setNearestHospital(nearestHospital);
					nearestHospital.clear();
					++hospitalPassed;
					if (hospitalPassed == _numberOfHospitals)
						return _curNode->getVectorOfOtherNodes().at(i)->getId();
				}
			}
		}
	}
	return -1;
}

string printShortestDistance(vector<Node*> _vectorOfNodes, int src, int _sizeOfNodes,int _numberOfHospitals)
{
	// predecessor[i] array stores predecessor of 
	// i and distance array stores distance of i 
	// from s 

	vector<int> pred(_sizeOfNodes, -1);
	vector<int> dist(_sizeOfNodes, INT_MAX);
	int dest = BFS(_sizeOfNodes, _vectorOfNodes.at(src), &pred, &dist, _numberOfHospitals);
	if (dest < 0) {
		cout << "Given source and destination"
			<< " are not connected";
		return "error";
	}

	// vector path stores the shortest path 
	//vector<int> path;
	//int crawl = dest;
	//path.push_back(crawl);
	//while (pred[crawl] != -1) {
	//	path.push_back(pred[crawl]);
	//	crawl = pred[crawl];
	//}

	// printing path from source to destination 
	//cout << "\nPath is::\n";

	string line = "";
	vector<vector<int>> vectorOfNearestHospitals = _vectorOfNodes.at(src)->getNearestHospital();
	vector<int> vectorOfNearestHospital;
	for (int i = 0; i < vectorOfNearestHospitals.size(); ++i)
	{
		vectorOfNearestHospital = vectorOfNearestHospitals.at(i);
		for (int j = vectorOfNearestHospital.size()-1; j >= 0; --j)
		{
			if (_vectorOfNodes.at(vectorOfNearestHospital.at(j))->getIsHospital())
			{
				line += "[" + to_string(_vectorOfNodes.at(vectorOfNearestHospital.at(j))->getId()) + "]" + ">";
			}
			else
				line += to_string(_vectorOfNodes.at(vectorOfNearestHospital.at(j))->getId()) + ">";
		}
		line += "SP:" + to_string(vectorOfNearestHospital.size() - 1) + "\t";
		//if (_vectorOfNodes.at(path[i])->getIsHospital())
		//{
		//	line += "[" + to_string(path[i]) + "]" + ">";
		//}
		//else
		//	line += to_string(path[i]) + ">";
	}

	// distance from source is in distance array 
	//line += "\tSP: " + to_string(dist[dest]) + "\n";
	line += "\n";
	return line;
}

void main()
{
	int numberOfHospitalsToFind;
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
		int a;
		if (!(iss >> a))
		{
			line.erase(0, 1);
			numberOfHospitalsToFind = stoi(line);
			continue;
		} // error
		vectorOfNodes.at(a)->setIsHospital(true);
	}
	infile.close();
	infile.clear();

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() << "[µs]" << std::endl;
	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;


	//ofile << "Writing this to a file.\n";
	ofstream ofile;
	ofile.open("output.txt");
	string stringOutput = "";
	for (int i = 0; i < vectorOfNodes.size(); ++i)
	{
		stringOutput += printShortestDistance(vectorOfNodes, i, vectorOfNodes.size(), numberOfHospitalsToFind);
	}
	ofile << stringOutput;
	ofile.close();

	cin.get();
}