// SA.cpp: ©w¸q¥D±±¥xÀ³¥Îµ{¦¡ªº¶i¤JÂI¡C
//
#include <typeinfo>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <set>

using namespace std;
char T[100000];
string S1;

int SubStringCount(string S1)
{
	set<string> mySet;
	for (int p = 0; p < S1.length(); p++)			
		for (int q = 1; q < S1.length() - p + 1; q++)
		{
			string tmp = S1.substr(p, q);
			mySet.insert(tmp);
		}

	return mySet.size();
}

int main() {
	double cpu_time;
    for (int i = 1; i <= 100; i++) {
        ifstream infile;
        stringstream ss;
        ss << "../data/TEXTs_1000/TEXT" << i << ".txt";
        infile.open(ss.str().c_str());
        infile.read(T, 1000);
        infile.close();
		S1 = string(T);
		time_t start_build, end_build;
		start_build = clock();
		int Ans = SubStringCount(S1);
		end_build = clock();
		cpu_time += ((double) (end_build - start_build)) / CLOCKS_PER_SEC;
		cout << "子字串數量：" << Ans << endl;
	}
	cout << "time :" << cpu_time << endl;
	// }
}
