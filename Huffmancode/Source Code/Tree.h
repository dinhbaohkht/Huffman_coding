#pragma once
#include<iostream>

class Node
{
public:
	int data;    
	int freq;
	Node* pLeft; 
	Node* pRight;
	//typedef Node* Tree;
	static Node* createdNode(int _data, int _freq);
	static Node* createdRoof(int _freq, Node* right, Node* left);
};