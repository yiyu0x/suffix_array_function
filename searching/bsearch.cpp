#include <iostream>
#include <string.h> 
using namespace std;

// int cmp_(struct suffix a, struct suffix b) { 
    // return string(a.suff) < string(b.suff);
// } 

string substring(char* txt, int start) {
	string s(txt);
	return s.substr(start);
}
bool binary_search(int *SA, int n, char *target, char *article) {
	
	// sort(SA, SA+n, cmp_);
	// debug
	// for(int i=0; i<n; i++) cout << SA[i].suff << endl;

	int left = 0;
	int right = n;
	int target_len = strlen(target);
	int article_len = strlen(article);
	while (left <= right) {
		int flag = 1;
		int mid = (left + right) / 2; 
		// cout << "->" << substring(article, SA[mid]) << endl;
		for (int i = 0; i < target_len; i++) {
			if (target[i] != article[SA[mid]+i]) {
				// cout << target[i] << "!=" << article[SA[mid]+i] << endl;
				if (target[i] > article[SA[mid]+i]) 
					left = mid+1;
				else 
					right = mid-1;
				flag = 0;
				break;
			} else {
				// cout << "i=" << i << endl;
				// cout << target[i] << "=" << article[SA[mid]+i] << endl;
			}
		}
		if (flag) return true;
		// if (strcmp(SA[mid].suff, target) < 0) left = mid + 1;
		// else if (strcmp(SA[mid].suff, target) > 0) right = mid - 1;
 		// else return true;
	}
	return false;
}