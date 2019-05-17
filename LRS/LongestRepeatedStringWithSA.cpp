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
char T[SIZ]; // text
int SA[SIZ], tempSA[SIZ]; // the sorted suffixes
int RA[SIZ], tempRA[SIZ]; // ranks of suffix array
int L[SIZ]; // used in counting sort
int Phi[SIZ]; // the jumping parameter
int LCP[SIZ]; // longest common prefix
int PLCP[SIZ]; // permuted longest common prefix

inline int getRA(int i)
{
	return (i < n) ? RA[i] : 0;
}

void radix_sort(int k)
{
	mem(L, 0);
	// count frequencies
	for (int i = 0; i < n; ++i)
	{
		L[getRA(i + k)]++;
	}
	// save first index of every characters
	int mx = max(n, 130);
	for (int i = 0, s = 0; i < mx; ++i)
	{
		int x = L[i];
		L[i] = s;
		s += x;
	}
	// build sorted tempSA
	for (int i = 0; i < n; ++i)
	{
		int& x = L[getRA(SA[i] + k)];
		tempSA[x++] = SA[i];
	}
	// copy tempSA to SA
	for (int i = 0; i < n; ++i)
	{
		SA[i] = tempSA[i];
	}
}
// text must ends with a $
void buildSA()
{
	// initialize
	n = strlen(T);
	T[n++] = '$', T[n] = 0; // append $
	for (int i = 0; i < n; ++i)
	{
		SA[i] = i;
		RA[i] = T[i];
	}

	// algorithm loop
	for (int k = 1; k < n; k <<= 1)
	{
		// sort by k-th ranks
		radix_sort(k);
		radix_sort(0);
		// compute new ranks
		tempRA[SA[0]] = 0;
		for (int i = 1, r = 0; i < n; ++i)
		{
			if (getRA(SA[i - 1]) != getRA(SA[i])) {
				r++;
			}
			else if (getRA(SA[i - 1] + k) != getRA(SA[i] + k)) {
				r++;
			}
			tempRA[SA[i]] = r;
		}
		for (int i = 0; i < n; ++i)
		{
			RA[i] = tempRA[i];
		}
		if (RA[SA[n - 1]] == n - 1) break;
	}
}

// Finds the Longest Common Prefix (LCP) between two adjacent suffixes
// excluding the first suffix using the Permuted LCP (PLCP) theorem.
void computeLCP()
{
	Phi[SA[0]] = -1;
	for (int i = 1; i < n; ++i)
	{
		Phi[SA[i]] = SA[i - 1];
	}

	for (int i = 0, L = 0; i < n; ++i)
	{
		if (Phi[i] == -1)
		{
			PLCP[i] = 0;
			continue;
		}
		// longest common prefix length
		L = max(L - 1, 0);
		while (T[i + L] == T[Phi[i] + L])
		{
			L++;
		}
		PLCP[i] = L;
	}

	for (int i = 0; i < n; ++i)
	{
		LCP[i] = PLCP[SA[i]];
	}
}

// LRS length is unique. But LRS substring may not be unique.
// This function returns alphabetically smallest substring
// that has been repeated twice or more.
string findLRS()
{
	int pos, lrs = 0;
	for (int i = 1; i < n; i++)
	{
		if (LCP[i] > lrs)
		{
			lrs = LCP[i];
			pos = i;
		}
	}

	if (lrs == 0)
	{
		return "";
	}

	string res = T + SA[pos];
	return res.substr(0, lrs);
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
		
		start = clock();
		
		buildSA();
		
		end = clock();
		cpu_time_build += ((double) (end - start)) / CLOCKS_PER_SEC;
		
		start = clock();
		
		computeLCP();
		string res = findLRS();
		
		end = clock();
		cpu_time_LCP += ((double) (end - start)) / CLOCKS_PER_SEC;
		
		printf("Longest Repeated Substring: %s [size = %lu]\n", res.data(), res.size());
	}
	cout << "Build Used: " << cpu_time_build << " seconds" << endl;
	cout << "LCP Used: " << cpu_time_LCP << " seconds" << endl;

	return 0;
}
