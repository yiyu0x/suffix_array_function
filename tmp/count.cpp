// SA.cpp: 定義主控台應用程式的進入點。
//

#include <iostream>
#include <string>
#include <set>

using namespace std;
string S1, S2;

int SubStringCount(string S1)
{
	set<string> mySet;
	for (int p = 0; p < S1.length(); p++)			//從字串的何處開始
		for (int q = 1; q < S1.length() - p + 1; q++)		//子字串的長度
		{
			string tmp = S1.substr(p, q);
			mySet.insert(tmp);
		}

	return mySet.size();
}

int main() {
	cout << "目標：算出一字串之相異子字串數量" << endl;
	cout << "請輸入要算幾次" << endl;
	int t;
	cin >> t;
	while (t--) {
		cout << "輸入目標字串" << endl;
		cin >> S1;
		
		int Ans = SubStringCount(S1);

		cout << "有 " << Ans << " 個!" << endl;
	}
}