#include "./bsearch.cpp"
#include <numeric>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream> 
using namespace std;
const int N = 100;
void debug_suffix(int *SA, int *RA, int *Hei, char *S, const char*s="suffix array:"){
    int n = strlen(S);
    cout<<s<<endl;
    cout<<"SA Hei:"<<endl;
    for(int i=0;i<n;i++)cout<<SA[i]<<' '<<Hei[i]<<' '<<setw(n)<<(S+SA[i])<<endl;
    cout<<"RA:"<<endl;
    for(int i=0;i<n;i++)cout<<RA[i]<<' '<<setw(n)<<(S+i)<<endl;
    cout<<"-------"<<endl;
}
bool noteq(int a, int b, int k, int n, int*RA){
    return RA[a] != RA[b] || a+k>=n || b+k>=n || RA[a+k] != RA[b+k];
}
void radix_sort(int*bg, int*ed, int*rank, int n_of_diff_rank){
    static int box[N], tmp[N];
    int n = ed-bg;
    fill_n(box, n_of_diff_rank, 0);
    for(int i=0; i<n; i++)
        box[rank[i] ]++;
    partial_sum(box, box+n_of_diff_rank, box);
    for(int i=n-1; i>=0; i--)
        tmp[--box[rank[bg[i]] ]] = bg[i];
    copy_n(tmp,n,bg);
}
void build_suffix_array(int*SA, int*RA, char*S, bool is_dec=true){
    static int RA2[N];
    int n = strlen(S);
    copy_n(S,n,RA);
    int n_of_diff_rank = 256; // char has 256 different value.
    for(int k=1; k<n; k*=2){
        // Comput SA_{2k} with RA_{k}
        // sort by rank-k ( ignore the string which len < 1+k )
        if(is_dec){ // "aa" < "a"
            iota(SA, SA+n, 0); // init SA to [0,1,2...]
            radix_sort(SA, SA+n-k, RA+k, n_of_diff_rank);
        }else{ // "a" < "aa"
            iota(SA,SA+k,n-k);
            iota(SA+k,SA+n,0); // init SA to [k,k+1...n-1,0,1,...]
            radix_sort(SA+k, SA+n, RA+k, n_of_diff_rank);
        }
        // sort by rank-0 ( include the string which len < 1+k )
        radix_sort(SA, SA+n, RA, n_of_diff_rank);

        // Comput RA_{2k} with SA_{2k}
        RA2[SA[0]] = 0; n_of_diff_rank = 1;
        for(int i=1; i<n; i++){
            if(noteq(SA[i-1], SA[i], k, n, RA) )
                n_of_diff_rank++;
            RA2[SA[i]] = n_of_diff_rank-1;
        }
        copy_n(RA2, n, RA);
        if(n_of_diff_rank == n)break; // all rank are diff => SA is fully sorted
    }
}
void build_hei(int*SA, int*RA, char*S, int*Hei){
    int k = 0, n = strlen(S);
    for(int i=0;i<n;i++){
        if(RA[i]){
            while(S[i+k]==S[SA[RA[i]-1]+k])k++;
        }
        Hei[RA[i]] = k;
        k = max(0,k-1); // hei(rank(i+1) ) >= hei(rand(i) )-1
    }
}
int sub_string_amount(char*s, int* hei) {
    int len = strlen(s);
    int sum = 0;
    int sum_hei = 0;
    for(int i = 0; i <= len; i++) {
        sum += i;
        if (i != len) 
            sum_hei += hei[i];
    }
    return sum - sum_hei;
}

void debug(int *SA, char* S) {
  int len = strlen(S);
  int SIZE = 29;
  cout << setw(SIZE) << "Suffix" << setw(SIZE) << "SA" << setw(SIZE) << endl;
  cout << setw(SIZE*3) << "--------------------------" << endl;
  for (int i = 0; i < len; i++) {
    cout << setw(SIZE) << substring(S, SA[i]) << setw(SIZE) << SA[i] << endl;
  }
}

char S[N];
int SA[N], RA[N], Hei[N];
int main(){
    
    double cpu_time_used_to_build = 0;
    double cpu_time_used_to_search = 0;
    for (int i = 1; i <= 100; i++) {
        ifstream infile;
        stringstream ss;
        // ss << "../data/TEXTs_1000/TEXT" << i << ".txt";
        ss << "../data/article.txt";
        infile.open(ss.str().c_str());
        infile.read(S, N);
        S[N-1] = 0;
        cout << "文本:"<< S << "長度:" << strlen(S) << endl;
        infile.close();
        time_t start_build, end_build;
        start_build = clock();
        build_suffix_array(SA,RA,S,true);
        end_build = clock();
        cpu_time_used_to_build += ((double) (end_build - start_build)) / CLOCKS_PER_SEC;
        debug(SA, S);
        // cout << S << endl;

        ss.str("");
        // ss << "../data/Target_for1000_Length10/TEXT" << i << ".txt";
        ss << "../data/target.txt";

        infile.open(ss.str().c_str());
        char targetSize = 10+1;
        char target[targetSize+1];
        infile.read(target, targetSize);
        target[targetSize-1] = 0;
        cout << "欲搜尋字串:" << target << endl;
        infile.close();
// /bool binary_search(int *SA, int n, char *target, char *article) {
        if (binary_search(SA, strlen(S), target, S)) {
          cout << "find" << endl;
        } else {
          cout << "not found" << endl;
        }
        
        break;
        // start_build = clock();
        // int amount = sub_string_amount(S, Hei);
        // end_build = clock();
        // cpu_time_used_to_search += ((double) (end_build - start_build)) / CLOCKS_PER_SEC;
        // debug_suffix(SA,RA,Hei,S,"Suffix Array(DES)");
        // cout << "子字串數量：" << amount << endl;
    }
    cout << "build time :" << cpu_time_used_to_build << endl;
    cout << "search time:" << cpu_time_used_to_search << endl;
}