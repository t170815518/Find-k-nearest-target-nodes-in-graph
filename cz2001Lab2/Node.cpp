#include "Node.h"

Node::Node()
{
}

Node::Node(Node * _thatNode, int _id)
{
	vectorOfOtherNodes.push_back(_thatNode);
	id = _id;
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

