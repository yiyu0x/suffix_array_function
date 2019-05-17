#include <iostream>
#include <string.h> 
using namespace std;

// int cmp_(struct suffix a, struct suffix b) { 
    // return string(a.suff) < string(b.suff);
// } 
bool binary_search(struct suffix *SA, int n, char *target, char *article) {
	
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
		// cout << "->" << SA[mid].suff << endl;
		for (int i = 0; i < target_len; i++) {
			// cout << "@index" << SA[mid].index<< endl;
			// cout << "@i" << i << endl;
			// cout << target[i] << ":" << article[SA[mid].index + i] << endl;
			if (target[i] != article[SA[mid].index + i]) {
					// cout << "false" << endl;
				// if (SA[mid].index + i <= article_len) {
					// cout << target[i] << ":" << article[SA[i].index + i] << endl;
					// cout << ":::" << SA[i].index + i << endl;
					if (target[i] > article[SA[mid].index + i]) 
						left = mid+1;
					else 
						right = mid-1;
					flag = 0;
					break;
				// }
			}
		}
		if (flag) return true;
		// if (strcmp(SA[mid].suff, target) < 0) left = mid + 1;
		// else if (strcmp(SA[mid].suff, target) > 0) right = mid - 1;
 		// else return true;
	}
	return false;
}