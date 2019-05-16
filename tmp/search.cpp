#include <iostream>
#include <string>

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
	cout << "要進行幾次搜尋？" << endl;
	int t;
	cin >> t;
	while (t--) {
		cout << "輸入目標字串" << endl;
		cin >> S1;
		cout << "輸入欲搜尋字串" << endl;
		cin >> S2;
		
		int pos = StringSearch(S1, S2);	//若沒搜到則回傳-1，否則傳回目標字串在搜尋字串的位置

		if (pos != -1)
			cout << "yes!" << endl;
		else
			cout << "no!" << endl;
	}
}