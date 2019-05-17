#include "./build_suffix_array.cpp"
#include "./bsearch.cpp"
#include <iostream>
#include <fstream>
#include <sstream> 
#include <iomanip>
#define SIZE 20
void debug(struct suffix* SA, int n) {
  cout << setw(SIZE) << "Suffix" << setw(SIZE) << "SA" << setw(SIZE) << "Hei" << endl;
  cout << setw(30) << "--------------------------" << endl;
  for(int i = 0; i < n; i++) 
    cout << setw(SIZE) << ""
         << setw(SIZE) << SA[i].index 
         << setw(SIZE) << "" << endl;
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
  
  const int articleSize = 1000;
  const int targetSize = 100;
  double cpu_time_used_to_build = 0;
  double cpu_time_used_to_search = 0;
  for (int i = 1; i <= 100; i++) {
    ifstream infile;
    stringstream ss;
    ss << "./data/TEXTs_1000/TEXT" << i << ".txt";
    infile.open(ss.str().c_str());
    char txt[articleSize];
    infile.read(txt, articleSize);
    infile.close();

    ss.str("");
    ss << "./data/Target_for1000_Length100/TEXT" << i << ".txt";
    infile.open(ss.str().c_str());
    char target[targetSize];
    infile.read(target, targetSize);
    infile.close();
  
  // cout << article << endl;
  //可自行定義
  // cout << "./data/TEXTs_10000/TEXT" + to_string(i) + ".txt" << endl;
  // ifstream f("./data/article.txt");
  // // string temp = "./data/target.txt";
  
  // char target[100000];
  // strcpy(target, temp.c_str());
  // cout << target << endl;
  // // char target[] = "legislation";
  
  // string str;
  // if (f) {
  //   ostringstream ss;
  //   ss << f.rdbuf(); // reading data
  //   str = ss.str();
  // } else {
  //   cout << "error" << endl;
  //   exit(0);
  // }
  // char txt[str.size() + 1];
  // strcpy(txt, str.c_str());

  // char txt[] = "taiwan is good"; 
    // char target[] = "2";
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
    // if (binary_search(suffixes, n, target, txt))
      // cout << "find!" << endl;
    // else 
      // cout << "not found!" << endl;
    
  }
  cout << "build time :" << cpu_time_used_to_build << endl;
  cout << "search time:" << cpu_time_used_to_search << endl;
}