#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <ctime>

using namespace std;
string S1, S2;

int StringSearch(string S1, string S2)
{
	int pos = -1;
	for (int p = 0; p < S1.length() - S2.length(); p++)	//從哪一個字開始
	{
		bool found = true;
		for (int q = 0; q < S2.length(); q++)			//目前搜到欲蒐尋字串的第幾個字
			if (S1[p + q] == S2[q])
				continue;
			else
			{
				found = false;
				break;
			}
		if (found)
		{
			pos = p;
			break;
		}
	}
	return pos;		//若沒搜到，回傳-1
}

int main() {
	const int articleSize = 1000;
	const int targetSize = 100;
	double cpu_time_used = 0;
	int gd = 0;
	for (int i=1; i<101; i++)
	{
		time_t start, end;
		
		ifstream infile;
		stringstream ss;
		ss << "../data/TEXTs_1000/TEXT" << i << ".txt";
		infile.open(ss.str().c_str());
		char article[articleSize];
		infile.read(article, articleSize);
		infile.close();
		
		ss.str("");
		ss << "../data/Target_for1000_Length100/TEXT" << i << ".txt";
		infile.open(ss.str().c_str());
		char Target[targetSize];
		infile.read(Target, 100);
		infile.close();
		
		start = clock();
		int pos = StringSearch(article, Target);	//若沒搜到則回傳-1，否則傳回目標字串在搜尋字串的位置
		end = clock();
		// if (pos != -1)
		// 	cout << "yes!" << i << endl;
		// else
		// 	cout << "no!" << i << endl;
		
		cpu_time_used += ((double) (end - start)) / CLOCKS_PER_SEC;
	}
	
	cout << cpu_time_used << endl;
}
