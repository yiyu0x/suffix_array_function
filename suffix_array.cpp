// REF : https://www.geeksforgeeks.org/suffix-array-set-1-introduction/
#include <cstring> 
#include <algorithm> 
#include <iostream>
using namespace std; 
  
// Structure to store information of a suffix 
struct suffix { 
    int index; 
    char *suff; 
    int hei;
}; 

int int_sum(int n) {
    int sum = 0;
    for(int i = 1; i <= n; i++) sum += i;
    return sum;
}

int hei_sum(struct suffix *suffixes, int n) {
    int sum = 0;
    for(int i = 0; i < n; i++) 
        sum += suffixes[i].hei;
    return sum;
}

int substring_amount(char *str, struct suffix *suffixes, int n) {
    return int_sum(strlen(str)) - hei_sum(suffixes, n);
}

void build_hei(struct suffix *suffixes, int n) {
    int k;
    int sa, sa_prev;
    suffixes[0].hei = 0;
    for (int i = 1; i < n; i++) {
        k = 0;
        while (suffixes[i].suff[k] == suffixes[i-1].suff[k]) k++;
        suffixes[i].hei = k;
    }
}
// A comparison function used by sort() to compare two suffixes 
int cmp(struct suffix a, struct suffix b) { 
    return a.suff[0] < b.suff[0] ? (strcmp(a.suff, b.suff) < 0 ? 1 : 0) : 0; 
    // strcmp相等回傳0 str1<str2回傳 <0
} 
  
// This is the main function that takes a string 'txt' of size n as an 
// argument, builds and return the suffix array for the given string 
int *buildSuffixArray(char *txt, int n, struct suffix *suffixes) { 
    // A structure to store suffixes and their indexes 
    // struct suffix suffixes[n]; 
    // Store suffixes and their indexes in an array of structures. 
    // The structure is needed to sort the suffixes alphabatically 
    // and maintain their old indexes while sorting 
    for (int i = 0; i < n; i++) { 
        suffixes[i].index = i; 
        suffixes[i].suff = (txt+i); 
    } 
    // Sort the suffixes using the comparison function 
    // defined above. 
    sort(suffixes, suffixes+n, cmp); 

    // Store indexes of all sorted suffixes in the suffix array 
    int *suffixArr = new int[n]; 
    for (int i = 0; i < n; i++) 
        suffixArr[i] = suffixes[i].index; 
    
    build_hei(suffixes, n);
    // Return the suffix array 
    return  suffixArr; 
} 
