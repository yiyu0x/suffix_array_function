#include "./build_suffix_array.cpp"
#include "./bsearch.cpp"
#include <iostream>
#include <fstream>
#include <sstream> 
#include <iomanip>
#include <ctime> 
#define SIZE 20
void debug(struct suffix* SA, int n) {
  cout << setw(SIZE) << "Suffix" << setw(SIZE) << "SA" << setw(SIZE) << endl;
  cout << setw(30) << "--------------------------" << endl;
  for(int i = 0; i < n; i++) 
    cout << setw(SIZE) << ""
         << setw(SIZE) << SA[i].index 
         << setw(SIZE) << "" << endl;
}

// int sum(int n) {
//     int sum = 0;
//     for(int i = 1; i <= n; i++) sum += i;
//     return sum;
// }

// int hei_sum(struct suffix *SA, int n) {
//     int sum = 0;
//     for(int i = 0; i < n; i++) sum += SA[i].hei;
//     return sum;
// }

// int substring_amount(char *str, struct suffix *SA, int n) {
//     return sum(strlen(str)) - hei_sum(SA, n);
// }

int main(int argc, char const *argv[]) {
  double tb=0, ts=0;
  for (int r=0; r<10; r++)
  {
  const int articleSize = 100000;
  const int targetSize = 10;
  double cpu_time_used_to_build = 0;
  double cpu_time_used_to_search = 0;
  for (int i = 1; i <= 100; i++) {
    ifstream infile;
    stringstream ss;
    ss << "../data/TEXTs_100000/TEXT" << i << ".txt";
    infile.open(ss.str().c_str());
    char txt[articleSize+1];
    infile.read(txt, articleSize);
    infile.close();
    txt[articleSize] = 0;

    ss.str("");
    ss << "../data/Target_for10000_Length10/TEXT" << i << ".txt";
    infile.open(ss.str().c_str());
    char target[targetSize+1];
    infile.read(target, targetSize);
    infile.close();
    target[targetSize] = 0;
  
  	int n = strlen(txt); 
  	struct suffix suffixes[n]; 

    time_t start_build, end_build;
    start_build = clock();
  	int *suffixArr = buildSuffixArray(txt,  n, suffixes); 
  	end_build = clock();
    cpu_time_used_to_build += ((double) (end_build - start_build)) / CLOCKS_PER_SEC;
    // debug(suffixes, n);
  	// cout << "Following is suffix array for " << txt << endl; 
  	// printArr(suffixArr, n);
  	
    // int substr_amount = substring_amount(txt, suffixes, n);
  	// cout << "子字串數量：" << substr_amount << endl;

    // char target[] = "aba";
    start_build = clock();
    binary_search(suffixes, n, target, txt);
    end_build = clock();
    cpu_time_used_to_search += ((double) (end_build - start_build)) / CLOCKS_PER_SEC;
    if (binary_search(suffixes, n, target, txt))
       cout << "find!" << endl;
	else 
       cout << "not found!" << endl;
  }
  cout << r;
  tb+=cpu_time_used_to_build;
  ts+=cpu_time_used_to_search;
}
  cout << "build time :" << tb/10.0 << endl;
  cout << "search time:" << ts/10.0 << endl;
}
