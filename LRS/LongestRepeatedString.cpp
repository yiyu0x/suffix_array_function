#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <ctime>
using namespace std;
#define mem(a,b) memset(a, b, sizeof(a))
#define loop(i, x) for(__typeof((x).begin()) i=(x).begin(); i!=(x).end(); ++i)
#define rloop(i, x) for(__typeof((x).rbegin()) i=(x).rbegin(); i!=(x).rend(); ++i)
/*------------------------------------------------------------------------------------*/

int test, cas = 1;

const int SIZ = 10000050; // maximum possible size

int n; // text length
char T[SIZ]; 	// text
string S1;

// Finds the Longest Common Prefix (LCP) between two adjacent suffixes
// excluding the first suffix using the Permuted LCP (PLCP) theorem.
string repeted(string str) {
    int len = str.length();

    int **c = new int*[len + 1];
    for (int i = 0; i <= len; ++i)
        c[i] = new int[len + 1];
    for (int i = 0; i <= len; ++i) {
        c[i][0] = 0;
        c[0][i] = 0;
    }

    int max_len = 0, index = len + 1;
    for (int i = 1; i <= len; ++i) {
        for (int j = 1; j <= len; ++j) {
            if (str[i-1] == str[j-1] && abs(i-j) > c[i-1][j-1]) {
                c[i][j] = c[i-1][j-1] + 1;
                if (c[i][j] > max_len) {
                    max_len = c[i][j];
                    index = std::min(i, j);
                }
            } else {
                c[i][j] = 0;
            }
        }
    }
    
    for (int i = 0; i <= len; ++i)
        delete[] c[i];
    delete[] c;
 
    if (max_len > 0) {
        std::string ret = str.substr(index - max_len, max_len);
        for (int i = 0; i < max_len; ++i)
            if(ret[i] != ' ')
                return ret;
    }

    return "NONE";
}

int main()
{
	/*
	GATAGACA
	abcabxabcd
	*/
	double cpu_time_build = 0, cpu_time_LCP = 0;
	for (int i=1; i<101; i++)
	{
		time_t start, end;
		memset(T, 0, sizeof(T));
		
		ifstream infile;
		stringstream ss;
		ss << "../data/TEXTs_1000/TEXT" << i << ".txt";
		infile.open(ss.str().c_str());
		infile.read(T, 1000);
		infile.close();
		
		S1 = string(T);
		start = clock();
		S1 = repeted(S1);
		end = clock();
		
		cout << "Longest Repeated Substring: " << S1 << " [size = " << S1.length() << "]\n";
		cpu_time_LCP += ((double) (end - start)) / CLOCKS_PER_SEC;
	}
	cout << "LCP Used: " << cpu_time_LCP << " seconds" << endl;

	return 0;
}
