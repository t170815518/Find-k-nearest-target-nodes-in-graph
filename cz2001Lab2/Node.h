#pragma once
#include <vector>
#include <iostream>

using namespace std;

class Node
{
private:
	vector<Node*> vectorOfOtherNodes;
	int id;
public:
	Node();
	Node(Node *_thatNode, int _id);
	void setThatNode(Node *_thatNode);
	void setid(int _id);

	Node* getThatNode(int _thatNodeId);
	int getId();
};

