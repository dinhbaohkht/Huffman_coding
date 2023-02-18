#include"Decoding.h"
#include"Encoding.h"
Decoding::Decoding()
{
	bits = 0;
	array = NULL;
	num = 0;
	out_name = "";
	file_name = "";
	row_of_bits = NULL;
	Tree = NULL;
}

void Decoding::Input_filename()
{
	cout << "Enter name of input_file: ";
	cin >> file_name;
	cout << "Enter name of output_file: ";
	cin >> out_name;
}
void Decoding::Set_filename(string in, string out)
{
	file_name = in;
	out_name = out;
}
Node* Decoding::get_Tree()
{
	return Tree;
}


void Decoding::save_rowofbit()
{

	row_of_bits = new char[num * 8];
	int number = 0;
	for (int i = 0; i < num; i++)
	{
		int n = array[i];
		row_of_bits[number++] = (n / 128) % 2 + 48;
		row_of_bits[number++] = (n / 64) % 2 + 48;
		row_of_bits[number++] = (n / 32) % 2 + 48;
		row_of_bits[number++] = (n / 16) % 2 + 48;
		row_of_bits[number++] = (n / 8) % 2 + 48;
		row_of_bits[number++] = (n / 4) % 2 + 48;
		row_of_bits[number++] = (n / 2) % 2 + 48;
		row_of_bits[number++] = (n / 1) % 2 + 48;
	}
}

void Decoding::flip_map()
{
	vector<Node*>tree;

	multimap<int, int> dst;
	for (auto it = freqs.begin(); it != freqs.end(); ++it)
	{
		dst.insert(pair<int, int>(it->second, it->first));
	}
	for (auto it = dst.rbegin(); it != dst.rend(); ++it)
	{
		tree.push_back(Node::createdNode(it->second, it->first));
	}

	BuildArray_Huffman_node(tree);
	Tree = tree[0];
}

void Decoding::BuildArray_Huffman_node(vector<Node*> &arr)
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


void Decoding::printCodes(Node* root, string str)
{
	if (!root)
		return;
	if (!(root->pLeft) || !(root->pRight))
		codes[root->data] = str;
	printCodes(root->pLeft, str + "0");
	printCodes(root->pRight, str + "1");
}

void Decoding::output_file()
{
	ofstream outFile(out_name, ios::binary);

	Node* curr = Tree;
	for (long i = 0; i < bits; i++)
	{
		if (row_of_bits[i] == '0')
			curr = curr->pLeft;
		else
			curr = curr->pRight;
		
		if (curr->pLeft == NULL && curr->pRight == NULL)
		{
			outFile.put((char)curr->data);
			curr = Tree;
		}
	}
}

void Decoding::countFreq_txt()
{
	ifstream inFile(file_name, ios::binary);

	inFile.seekg(0, ios::end);
	array = new int[inFile.tellg()];
	inFile.seekg(0, ios::beg);


	int so_luong = inFile.get();
	if (!so_luong)
		so_luong = 256;

	int k = inFile.get();

	if (k == 3)
	{
		for (int i = 0; i < so_luong * 4; i = i + 4)
		{
			int kitu = inFile.get();
			string frequence = "";
			for (int j = 0; j < 3; j++)
			{
				int ch = inFile.get();
				bitset<8> bset(ch);
				frequence += bset.to_string();
				bset.reset();
			}
			bitset<24> bset(frequence);
			freqs[kitu] = bset.to_ulong();
			frequence.clear();
			bset.reset();
		}
		string temp;
		getline(inFile, temp);
		bits = stol(temp);

		while (1)
		{
			int ch = inFile.get();
			if (inFile.eof())
				break;
			array[num++] = ch;
		}
		inFile.close();
		return;
	}

	if (k == 2)
	{
		for (int i = 0; i < so_luong * 3; i = i + 3)
		{
			int kitu = inFile.get();
			string frequence = "";
			for (int j = 0; j < 2; j++)
			{
				int ch = inFile.get();
				bitset<8> bset(ch);
				frequence += bset.to_string();
				bset.reset();
			}
			bitset<16> bset(frequence);
			freqs[kitu] = bset.to_ulong();
			frequence.clear();
			bset.reset();
		}

		string temp;
		getline(inFile, temp);
		bits = stol(temp);

		while (1)
		{
			int ch = inFile.get();
			if (inFile.eof())
				break;
			array[num++] = ch;
		}
		inFile.close();
		return;
	}

	if (k == 1)
	{
		for (int i = 0; i < so_luong * 2; i = i + 2)
		{
			int kitu = inFile.get();
			string frequence = "";
			for (int j = 0; j < 1; j++)
			{
				int ch = inFile.get();
				bitset<8> bset(ch);
				frequence += bset.to_string();
				bset.reset();
			}
			bitset<8> bset(frequence);
			freqs[kitu] = bset.to_ulong();
			frequence.clear();
			bset.reset();
		}

		string temp;
		getline(inFile, temp);
		bits = stol(temp);

		while (1)
		{
			int ch = inFile.get();
			if (inFile.eof())
				break;
			array[num++] = ch;
		}
		inFile.close();
		return;
	}
}