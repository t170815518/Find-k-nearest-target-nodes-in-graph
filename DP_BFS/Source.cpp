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

	vectorOfNodes->at(u)->setid(u);
	vectorOfNodes->at(u)->setThatNode(vectorOfNodes->at(v));
}

int BFS(int _sizeOfNodes, Node* _curNode, vector<int>* _pred, int _numberOfHospitals)
{
	int index = 0;
	Node* originNode = _curNode;
	int hospitalPassed = 0;
	int crawl = -1;
	vector<bool> visited(_sizeOfNodes, false);

	// Create a queue for BFS 
	list<Node*> queue;

	// Mark the current node as visited and enqueue it 
	visited[_curNode->getId()] = true;
	//(*_dist).at(_curNode->getId()) = 0;
	queue.push_back(_curNode);

	list<Node*>::iterator it;
	vector<int> nearestHospital;

	if (originNode->getIsHospital())
	{
		nearestHospital.push_back(originNode->getId());
		originNode->setNearestHospital(nearestHospital);
		nearestHospital.clear();
		++hospitalPassed;
		if (_numberOfHospitals == 1)
			return originNode->getId();
	}

	while (!queue.empty())
	{
		_curNode = queue.front();
		queue.pop_front();

		// Get all adjacent vertices of the dequeued 
		// vertex s. If a adjacent has not been visited,  
		// then mark it visited and enqueue it 
		for (int i = 0; i != _curNode->getVectorOfOtherNodes().size(); ++i)
		{
			if (!visited[_curNode->getVectorOfOtherNodes().at(i)->getId()])
			{
				visited[_curNode->getVectorOfOtherNodes().at(i)->getId()] = true;
				//(*_pred).push_back(_curNode->getId());
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
					//while ((*_pred).size() != index) {
					//	nearestHospital.push_back((*_pred)[index]);
					//	++index;
					//	crawl = (*_pred)[index];
					//}
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
	vector<int> pred(_sizeOfNodes, -1);
	//vector<int> dist(_sizeOfNodes, INT_MAX);
	int dest = BFS(_sizeOfNodes, _vectorOfNodes.at(src), &pred, _numberOfHospitals);
	//if (dest < 0) {
	//	return to_string(src) + " no hospitals found\n";
	//}

	string line = "";
	vector<vector<int>> vectorOfNearestHospitals = _vectorOfNodes.at(src)->getNearestHospital();
	vector<int> vectorOfNearestHospital;
	if (vectorOfNearestHospitals.size() == 0)
	{
		return to_string(src) + " no hospitals found\n";
	}
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
	}
	line += "noOfHospital:" + to_string(vectorOfNearestHospitals.size()) + "\t";

	line += "\n";
	return line;
}

void main()
{
	int numberOfHospitalsToFind;
	string graphFileName, hospitalFileName;
	graphFileName = "roadNet-CA.txt";

	cout << "Input file name: ";
	getline(cin, graphFileName);
	std::chrono::steady_clock::time_point beginReadFile = std::chrono::steady_clock::now();
	std::ifstream infile(graphFileName);
	if (!infile)
	{
		cout << graphFileName + " not found" << endl;
		cin.get();
		return;
	}
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
	std::chrono::steady_clock::time_point endReadFile = std::chrono::steady_clock::now();
	std::cout << "Parse graph time taken = " << std::chrono::duration_cast<std::chrono::seconds>(endReadFile - beginReadFile).count() << "[s]" << std::endl;
	std::cout << "Parse graph time taken = " << std::chrono::duration_cast<std::chrono::nanoseconds> (endReadFile - beginReadFile).count() << "[ns]" << std::endl;

	cout << "Input hospital file's name: ";
	getline(cin, hospitalFileName);
	infile.open(hospitalFileName);
	if (!infile)
	{
		cout << "The hospital file is not found" << endl;
		cin.get();
		return;
	}

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
	
	ofstream ofile;
	ofile.open("output.txt");
	string stringOutput = "";

	std::chrono::steady_clock::time_point beginOutputFile = std::chrono::steady_clock::now();
	for (int i = 0; i < vectorOfNodes.size(); ++i)
	{

		stringOutput += printShortestDistance(vectorOfNodes, i, vectorOfNodes.size(), numberOfHospitalsToFind);
	}
	std::chrono::steady_clock::time_point endOutputFile = std::chrono::steady_clock::now();
	ofile << stringOutput;
	ofile.close();

	std::cout << "BFS time taken = " << std::chrono::duration_cast<std::chrono::seconds>(endOutputFile - beginOutputFile).count() << "[s]" << std::endl;
	std::cout << "BFS time taken = " << std::chrono::duration_cast<std::chrono::nanoseconds> (endOutputFile - beginOutputFile).count() << "[ns]" << std::endl;

	cin.get();
}