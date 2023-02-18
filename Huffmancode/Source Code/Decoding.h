#include"Encoding.h"

class Decoding
{
private:
	long bits;
	string out_name;   
	string file_name;
	char* row_of_bits;
	int* array;
	int num;
	Node* Tree;
	map<int, string> codes;
	map<int, int> freqs;
public:
	Decoding(); //Hàm khởi tạo không đối
	Node* get_Tree();
	void Input_filename();
	void Set_filename(string, string);
	void flip_map();
	void BuildArray_Huffman_node(vector<Node*>&);
	void printCodes(Node*, string str = "");
	void save_rowofbit();
	void output_file();
	void countFreq_txt();
};