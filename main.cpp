#include "./suffix_array.cpp"
#include "./bsearch.cpp"
#include <iostream>
#include <fstream>
#include <sstream> 
using namespace std; 

void printArr(int arr[], int n) { 
    for(int i = 0; i < n; i++) 
        cout << arr[i] << " "; 
    cout << endl; 
} 
void printSuff(struct suffix* SA, int n) {
	for(int i = 0; i < n; i++) 
		cout << SA[i].suff << endl;
}

int main(int argc, char const *argv[]) {
	// 可自行定義
	ifstream f("a.txt");
	char target[] = "authority";
	
	string str;
	if (f) {
		ostringstream ss;
		ss << f.rdbuf(); // reading data
		str = ss.str();
   	} else {
   		cout << "error" << endl;
   		exit(0);
   	}
   	
	char txt[str.size() + 1];
	strcpy(txt, str.c_str());
    
    int n = strlen(txt); 
    struct suffix suffixes[n];
    
    int *suffixArr = buildSuffixArray(txt, n, suffixes); 
    // debug
    // printArr(suffixArr, n);
    // printSuff(suffixes, n);

    if (binary_search(suffixes, n, target))
    	cout << "find!" << endl;
   	else 
   		cout << "not found!" << endl;
}