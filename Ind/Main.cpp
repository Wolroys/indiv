#include "Header.h"

int main()
{
	string filename1 = "file1.txt";
	string filename2 = "file2.txt";

	Set<string> set1;
	Set<string> set2;

	read_file(set1, filename1);
	read_file(set2, filename2);

	cout << set1;
	cout << set2;

	cout << (set1 && set2);

	return 0;
}