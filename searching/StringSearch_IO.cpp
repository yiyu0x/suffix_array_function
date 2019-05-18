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
	for (int p = 0; p < S1.length() - S2.length(); p++)	//�q���@�Ӧr�}�l
	{
		bool found = true;
		for (int q = 0; q < S2.length(); q++)			//�ثe�j����`�M�r�ꪺ�ĴX�Ӧr
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
	return pos;		//�Y�S�j��A�^��-1
}

int main() {
	const int articleSize = 1000;
	const int targetSize = 100;
	double cpu_time_used = 0;
	for (int r=0; r<10; r++)
	{
		for (int i=1; i<101; i++)
		{
			time_t start, end;
			
			ifstream infile;
			stringstream ss;
			ss << "../data/TEXTs_1000/TEXT" << i << ".txt";
			infile.open(ss.str().c_str());
			char article[articleSize+1];
			infile.read(article, articleSize);
			infile.close();
			article[articleSize] = 0;
			
			ss.str("");
			ss << "../data/Target_100_Rnd/TEXT" << i << ".txt";
			infile.open(ss.str().c_str());
			char Target[targetSize+1];
			infile.read(Target, targetSize);
			infile.close();
			Target[targetSize] = 0;
			
			start = clock();
			int pos = StringSearch(article, Target);	//�Y�S�j��h�^��-1�A�_�h�Ǧ^�ؼЦr��b�j�M�r�ꪺ��m
			end = clock();
			
			cpu_time_used += ((double) (end - start)) / CLOCKS_PER_SEC;
		}
		cout << r << endl;
	}
	cout << cpu_time_used/10.0 << endl;
}
