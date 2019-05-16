#include "./suffix_array.cpp"
#include "./bsearch.cpp"
#include <iostream>
#include <fstream>
#include <sstream> 
#include <iomanip>
using namespace std; 

void debug(struct suffix* SA, int n) {
  cout << setw(10) << "Suffix" << setw(10) << "SA" << setw(10) << "Hei" << endl;
  cout << setw(30) << "--------------------------" << endl;
  for(int i = 0; i < n; i++) 
    cout << setw(10) << SA[i].suff
         << setw(10) << SA[i].index 
         << setw(10) << SA[i].hei << endl;
}

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
	// ifstream f("a.txt");
	// char target[] = "authority";
	
	// string str;
	// if (f) {
	// 	ostringstream ss;
	// 	ss << f.rdbuf(); // reading data
	// 	str = ss.str();
 //   	} else {
 //   		cout << "error" << endl;
 //   		exit(0);
 //   	}
	// char txt[str.size() + 1];
	// strcpy(txt, str.c_str());
    char txt[] = "ababa";
    int n = strlen(txt); 
    struct suffix suffixes[n];
    
    int *suffixArr = buildSuffixArray(txt, n, suffixes); 
    build_hei(suffixes, n);
    debug(suffixes, n);
    //
    int substr_amount = substring_amount(txt, suffixes, n);

    cout << "子字串數量：" << substr_amount << endl;

    // printArr(suffixArr, n);
    // printSuff(suffixes, n);
    // if (binary_search(suffixes, n, target))
    // 	cout << "find!" << endl;
   	// else 
   	// 	cout << "not found!" << endl;
}