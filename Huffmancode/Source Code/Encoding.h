#pragma once
#include"Tree.h"
#include<fstream>
#include<string>
#include<vector>
#include<bitset>
#include<map>
#include<Windows.h>
#include <direct.h>
using namespace std;

class Encoding
{
private:
	string out_name;   //tên file được nén
	string file_name;  //tên file cho vào nén
	string row_of_bits; //biến đổi chuỗi cho vào thành mã nhị phân ascii
	int* array; //các ký tự của file
	int num;
	Node* Tree;       //xử lý cây huffman.
	map<int, string> codes;  //lưu lại đường đi của ký tự
	map<int, int> freqs;   
public:
	Encoding();    
	Node* get_Tree();  
	void Input_filename();
	void Set_filename(string, string);
	void save_Lines();  
	void countFreq();
	void flip_map();
	void BuildArray_Huffman_node(vector<Node*>&);
	void printCodes(Node*, string str = "");
	void save_rowofbit();
	void output_file();
	void out_file_txt(vector<Node*> tree);
};