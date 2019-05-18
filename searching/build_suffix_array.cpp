#include <iostream> 
#include <cstring> 
#include <algorithm> 
using namespace std; 

struct suffix { 
    int index; // To store original index 
    int rank[2]; // To store ranks and next rank pair 
    // char *suff;
    // int hei;
}; 

int cmp(struct suffix a, struct suffix b) { 
    return (a.rank[0] == b.rank[0])? (a.rank[1] < b.rank[1] ?1: 0): 
               (a.rank[0] < b.rank[0] ?1: 0); 
} 
  
int *buildSuffixArray(char *txt, int n, struct suffix *suffixes) { 
    //自行增加
    for (int i = 0; i < n; i++) { 
        suffixes[i].index = i; 
        // suffixes[i].suff = (txt+i); 
    }
    ////////////////////////////////
    for (int i = 0; i < n; i++) { 
        suffixes[i].index = i; 
        suffixes[i].rank[0] = txt[i] - 'a'; 
        suffixes[i].rank[1] = ((i+1) < n)? (txt[i + 1] - 'a'): 10000; 
    } 
  
    sort(suffixes, suffixes+n, cmp); 

    int ind[n];  // This array is needed to get the index in suffixes[] 
                 // from original index.  This mapping is needed to get 
                 // next suffix. 
    for (int k = 4; k < 2*n; k = k*2) { 
        // Assigning rank and index values to first suffix 
        int rank = 0; 
        int prev_rank = suffixes[0].rank[0]; 
        suffixes[0].rank[0] = rank; 
        ind[suffixes[0].index] = 0; 
  
        // Assigning rank to suffixes 
        for (int i = 1; i < n; i++) { 
            // If first rank and next ranks are same as that of previous 
            // suffix in array, assign the same new rank to this suffix 
            if (suffixes[i].rank[0] == prev_rank && 
                    suffixes[i].rank[1] == suffixes[i-1].rank[1]) 
            { 
                prev_rank = suffixes[i].rank[0]; 
                suffixes[i].rank[0] = rank; 
            } 
            else // Otherwise increment rank and assign 
            { 
                prev_rank = suffixes[i].rank[0]; 
                suffixes[i].rank[0] = ++rank; 
            } 
            ind[suffixes[i].index] = i; 
        } 
  
        // Assign next rank to every suffix 
        for (int i = 0; i < n; i++) { 
            int nextindex = suffixes[i].index + k/2; 
            suffixes[i].rank[1] = (nextindex < n)? 
                                  suffixes[ind[nextindex]].rank[0]: 10000; 
        } 
  
        // Sort the suffixes according to first k characters 
        sort(suffixes, suffixes+n, cmp); 
    } 
  
    // Store indexes of all sorted suffixes in the suffix array 
    int *suffixArr = new int[n]; 
    for (int i = 0; i < n; i++) 
        suffixArr[i] = suffixes[i].index; 

    // build_hei(suffixes, n, txt);
    // Return the suffix array 
    return  suffixArr; 
} 
  
// A utility function to print an array of given size 
void printArr(int arr[], int n) { 
    for (int i = 0; i < n; i++) 
        cout << arr[i] << " "; 
    cout << endl; 
} 
