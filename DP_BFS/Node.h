#pragma once
#include <vector>
#include <iostream>

using namespace std;

class Node
{
private:
	vector<Node*> vectorOfOtherNodes;
	vector<vector<int>> nearestHospital;
	int id;
	bool isHospital;
	bool checkedNearestHospitals;
public:
	Node();
	Node(Node *_thatNode, int _id);
	Node(Node *_thatNode, int _id, bool _isHospital);
	void setThatNode(Node *_thatNode);
	void setid(int _id);
	void setIsHospital(bool _isHospital);
	void setNearestHospital(vector<int> _nearestHospital);
	void setCheckedNearestHospitals(bool _checkedNearestHospitals);

	Node* getThatNode(int _thatNodeId);
	int getId();
	bool getIsHospital();
	vector<Node*> getVectorOfOtherNodes();
	vector<vector<int>> getNearestHospital();
	bool getCheckedNearestHospitals();
};

