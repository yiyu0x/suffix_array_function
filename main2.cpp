#include "./build_suffix_array.cpp"
#include "./bsearch.cpp"
#include <iostream>
#include <fstream>
#include <sstream> 
#include <iomanip>

void debug(struct suffix* SA, int n) {
  cout << setw(10) << "Suffix" << setw(10) << "SA" << setw(10) << "Hei" << endl;
  cout << setw(30) << "--------------------------" << endl;
  for(int i = 0; i < n; i++) 
    cout << setw(10) << SA[i].suff
         << setw(10) << SA[i].index 
         << setw(10) << SA[i].hei << endl;
}

int sum(int n) {
    int sum = 0;
    for(int i = 1; i <= n; i++) sum += i;
    return sum;
}

int hei_sum(struct suffix *SA, int n) {
    int sum = 0;
    for(int i = 0; i < n; i++) sum += SA[i].hei;
    return sum;
}

int substring_amount(char *str, struct suffix *SA, int n) {
    return sum(strlen(str)) - hei_sum(SA, n);
}

int main(int argc, char const *argv[]) {
	
    //可自行定義
  ifstream f("a.txt");
  char target[] = "community";
  
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

  // char txt[] = "ababa"; 
	int n = strlen(txt); 
	struct suffix suffixes[n]; 
	int *suffixArr = buildSuffixArray(txt,  n, suffixes); 
	
  // debug(suffixes, n);
	// cout << "Following is suffix array for " << txt << endl; 
	// printArr(suffixArr, n);
	
  int substr_amount = substring_amount(txt, suffixes, n);
	cout << "子字串數量：" << substr_amount << endl;

  // char target[] = "aba";
  if (binary_search(suffixes, n, target))
    cout << "find!" << endl;
  else 
    cout << "not found!" << endl;
	return 0; 
}