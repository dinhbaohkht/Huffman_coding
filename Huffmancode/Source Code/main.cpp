#include"Encoding.h"
#include"Decoding.h"

int main()
{
	int k;
	cout << "Chon Chuc Nang: " << endl;
	cout << "1. Nen File" << endl;
	cout << "2. Giai Nen File" << endl;
	cin >> k;
	if (k == 1)
	{
		Encoding huffman;
		huffman.Input_filename();
		
		huffman.save_Lines();
		huffman.countFreq();
		huffman.flip_map();
		huffman.printCodes(huffman.get_Tree());
		huffman.save_rowofbit();
		huffman.output_file();
		
		
		
	}
	if (k == 2)
	{
		
		Decoding huffman;
		huffman.Input_filename();
		huffman.countFreq_txt();
		huffman.save_rowofbit();
		huffman.flip_map();
		//huffman.printCodes(huffman.get_Tree());
		huffman.output_file();
	}
	system("pause");
	return 0;
}
