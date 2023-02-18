#include"Tree.h"




Node* Node::createdNode(int _data, int _freq)
{
	Node* p = new Node;
	p->data = _data;
	p->freq = _freq;
	p->pLeft = NULL;
	p->pRight = NULL;
	return p;
}
Node* Node::createdRoof(int _freq, Node* right, Node* left)
{
	Node* roof = createdNode(0, _freq);
	roof->pLeft = left;
	roof->pRight = right;
	return roof;
}
