#define _CRT_SECURE_NO_WARNINGS
#include"Encoding.h"
#include"Tree.h"


Encoding::Encoding()
{
	array = NULL;
	num = 0;
	out_name = "";
	file_name = "";
	row_of_bits = "";
	Tree = NULL;

}
void Encoding::Input_filename()
{
	cout << "Enter name of input_file: ";
	cin >> file_name;
	cout << "Enter name of output_file: ";
	cin >> out_name;
}
void Encoding::Set_filename(string in, string out)
{
	file_name = in;
	out_name = out;
}




Node* Encoding::get_Tree()
{
	return Tree;
}
void Encoding::save_Lines()   //lưu từng ký tự của file vào chacracter. 
{
	ifstream inFile(file_name, ios::binary);
	
	inFile.seekg(0, ios::end);
    array = new int[inFile.tellg()];
	inFile.seekg(0, ios::beg);


	while (1)
	{
		int ch = inFile.get();
		if (inFile.eof())
			break;
		array[num++] = ch;
	}
	
	inFile.close();
}
void Encoding::countFreq()  //hàm đếm tần suất của ký tự trong mã ascii, từ 0 đến 255.
{
	bool* visited = new bool[num] {0};
	for (int i = 0; i < num; i++) {

		// Skip this element if already processed 
		if (visited[i] == 1)
			continue;

		// Count frequency 
		int count = 1;
		for (int j = i + 1; j < num; j++) {
			if (array[i] == array[j]) {
				visited[j] = 1;
				count++;
			}
		}
		//cout << arr[i] << " " << count << endl;
		freqs[array[i]] = count;
	}


}

void Encoding::flip_map()
{
	vector<Node*>tree;  

	multimap<int, int> dst; //tạo dst có fisrt là tần suất, sẽ được sắp xếp lớn nhất.
	for (auto it = freqs.begin(); it != freqs.end(); ++it)
	{
		dst.insert(pair<int, int>(it->second, it->first));
	}

	for (auto it = dst.rbegin(); it != dst.rend(); ++it) //tạo vector tree lưu lại dst.
	{
		tree.push_back(Node::createdNode(it->second, it->first));
	}

	Encoding::out_file_txt(tree); //xuất bảng tần suất vào file nén

	BuildArray_Huffman_node(tree); //tạo cây huffman từ cây tree.
	Tree = tree[0];  //lưu lại cây huffman
}	

void Encoding::BuildArray_Huffman_node(vector<Node*> &arr)
{
	int n = arr.size() - 2;
	for (int i = n; i >= 0; i--)
	{
		int sum_freq = arr[i]->freq + arr[i + 1]->freq;
		Node* roof = Node::createdRoof(sum_freq, arr[i], arr[i + 1]);
		for (int j = 0; j <= i; j++)
			if (arr[j]->freq <= sum_freq)
			{
				auto itPos = arr.begin() + j;
				auto newIt = arr.insert(itPos, roof);
				break;
			}
	}
}

void Encoding::printCodes(Node* root,string str)  //lưu đường đi, từ cây huffman
{
	if (!root)
		return;
	if (!(root->pLeft) || !(root->pRight))
		codes[root->data] = str;
	printCodes(root->pLeft, str + "0");
	printCodes(root->pRight, str + "1");
}

void Encoding::save_rowofbit()   //chuyển chuỗi ký tự thành dãy bít 01
{
	
	string mangg[256];

	for (auto it = codes.begin(); it != codes.end(); ++it)
	{
		mangg[it->first] = it->second;
	}

	for (int i = 0; i < num; i++)
	{
		row_of_bits += mangg[array[i]];
	}

}
void Encoding::output_file()  //xuất file.
{
	ofstream outFile(out_name, ios::binary | ios::app);



	long n = row_of_bits.length();
	outFile << n << endl;

	if (n % 8 != 0)
	{
		for (int i = 0; i < 8 - n % 8; i++)
		{
			row_of_bits.push_back('0');
		}
	}

	const char* row_of_bitss = row_of_bits.data();

	for (long i = 0; i < n; i = i + 8)
	{
		int temp = 128 * row_of_bitss[i] + 64 * row_of_bitss[i + 1] + 32 * row_of_bitss[i + 2] + 16 * row_of_bitss[i + 3] + 8 * row_of_bitss[i + 4] + 4 * row_of_bitss[i + 5] + 2 * row_of_bitss[i + 6] + row_of_bitss[i + 7] - 12240;
		outFile.put((char)temp);
	}
	outFile.close();
}


void Encoding::out_file_txt(vector<Node*> tree)
{
	ofstream outFile(out_name, ios::binary);
	outFile.put(tree.size());  //so luong ky tu.

	if (tree[0]->freq > 65535)
	{
		outFile.put(3);
		for (int i = 0; i < tree.size(); i++)
		{
			outFile.put(tree[i]->data);

			bitset<24> bset1(tree[i]->freq);
			string frequence = bset1.to_string();
			for (int j = 0; j < 24; j = j + 8)
			{
				bitset<8> bset(frequence.substr(j, 8));
				outFile.put((char)bset.to_ullong());
				bset.reset();
			}
			bset1.reset();
			frequence.clear();
		}
		outFile.close();
		return;
	}




	if (tree[0]->freq > 255)
	{
		outFile.put(2);
		for (int i = 0; i < tree.size(); i++)
		{
			outFile.put(tree[i]->data);

			bitset<16> bset1(tree[i]->freq);
			string frequence = bset1.to_string();
			for (int j = 0; j < 16; j = j + 8)
			{
				bitset<8> bset(frequence.substr(j, 8));
				outFile.put((char)bset.to_ullong());
				bset.reset();
			}
			bset1.reset();
			frequence.clear();
		}
		outFile.close();
		return;
	}


	outFile.put(1);
	for (int i = 0; i < tree.size(); i++)
	{
		outFile.put(tree[i]->data);

		bitset<8> bset1(tree[i]->freq);
		string frequence = bset1.to_string();
		for (int j = 0; j < 8; j = j + 8)
		{
			bitset<8> bset(frequence.substr(j, 8));
			outFile.put((char)bset.to_ullong());
			bset.reset();
		}
		bset1.reset();
		frequence.clear();
	}

	outFile.close();
	return;
}
