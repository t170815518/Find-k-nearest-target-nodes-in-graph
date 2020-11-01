#include "Node.h"

Node::Node()
{
	id = -1;
}

Node::Node(Node * _thatNode, int _id)
{
	vectorOfOtherNodes.push_back(_thatNode);
	id = _id;
}

Node::Node(Node * _thatNode, int _id, bool _isHospital)
{
	vectorOfOtherNodes.push_back(_thatNode);
	id = _id;
	isHospital = _isHospital;
}

void Node::setThatNode(Node * _thatNode)
{
	if (_thatNode == nullptr)
	{
		std::cout << "nullptr" << std::endl;
		return;
	}
	vectorOfOtherNodes.push_back(_thatNode);
}

void Node::setid(int _id)
{
	id = _id;
}

void Node::setIsHospital(bool _isHospital)
{
	isHospital = _isHospital;
}

void Node::setNearestHospital(vector<int> _nearestHospital)
{
	nearestHospital.push_back(_nearestHospital);
}

Node * Node::getThatNode(int _thatNodeId)
{
	for (int i = 0; i < vectorOfOtherNodes.size(); ++i)
	{
		if (vectorOfOtherNodes.at(i)->getId() == _thatNodeId)
			return vectorOfOtherNodes.at(i);
	}
	return nullptr;
}

int Node::getId()
{
	return id;
}

bool Node::getIsHospital()
{
	return isHospital;
}

vector<Node*> Node::getVectorOfOtherNodes()
{
	return vectorOfOtherNodes;
}

vector<vector<int>> Node::getNearestHospital()
{
	return nearestHospital;
}

