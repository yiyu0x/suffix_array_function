#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

void computeLPSArray(char* pat, int M, int* lps); 
  
// Prints occurrences of txt[] in pat[] 
void KMPSearch(char* pat, char* txt) 
{ 
    int M = strlen(pat); 
    int N = strlen(txt); 
  
    // create lps[] that will hold the longest prefix suffix 
    // values for pattern 
    int lps[M]; 
  
    // Preprocess the pattern (calculate lps[] array) 
    computeLPSArray(pat, M, lps); 
  
    int i = 0; // index for txt[] 
    int j = 0; // index for pat[] 
    while (i < N) { 
        if (pat[j] == txt[i]) { 
            j++; 
            i++; 
        } 
  
        if (j == M) { 
            printf("Found pattern at index %d ", i - j); 
            j = lps[j - 1]; 
        } 
  
        // mismatch after j matches 
        else if (i < N && pat[j] != txt[i]) { 
            // Do not match lps[0..lps[j-1]] characters, 
            // they will match anyway 
            if (j != 0) 
                j = lps[j - 1]; 
            else
                i = i + 1; 
        } 
    } 
} 
  
// Fills lps[] for given patttern pat[0..M-1] 
void computeLPSArray(char* pat, int M, int* lps) 
{ 
    // length of the previous longest prefix suffix 
    int len = 0; 
  
    lps[0] = 0; // lps[0] is always 0 
  
    // the loop calculates lps[i] for i = 1 to M-1 
    int i = 1; 
    while (i < M) { 
        if (pat[i] == pat[len]) { 
            len++; 
            lps[i] = len; 
            i++; 
        } 
        else // (pat[i] != pat[len]) 
        { 
            // This is tricky. Consider the example. 
            // AAACAAAA and i = 7. The idea is similar 
            // to search step. 
            if (len != 0) { 
                len = lps[len - 1]; 
  
                // Also, note that we do not increment 
                // i here 
            } 
            else // if (len == 0) 
            { 
                lps[i] = 0; 
                i++; 
            } 
        } 
    } 
} 

int main() {
	const int articleSize = 100000;
	const int targetSize = 10;
	double cpu_time_used = 0;
	for (int r=0; r<10; r++)
	{
		for (int i=1; i<101; i++)
		{
			time_t start, end;
			
			ifstream infile;
			stringstream ss;
			ss << "../data/TEXTs_100000/TEXT" << i << ".txt";
			infile.open(ss.str().c_str());
			char article[articleSize];
			infile.read(article, articleSize);
			infile.close();
			
			ss.str("");
			ss << "../data/Target_100_Rnd/TEXT" << i << ".txt";
			infile.open(ss.str().c_str());
			char Target[targetSize];
			infile.read(Target, targetSize);
			infile.close();
			
			start = clock();
			int pos = KMPSearch(article, Target);	//若沒搜到則回傳-1，否則傳回目標字串在搜尋字串的位置
			end = clock();
			if (pos != -1)
			 	cout << "yes!" << i << endl;
			
			cpu_time_used += ((double) (end - start)) / CLOCKS_PER_SEC;
		}
		cout << r << endl;
	}
	cout << cpu_time_used/10.0 << endl;
}
