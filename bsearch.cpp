#include <iostream>
#include <string.h> 
using namespace std;

int cmp_(struct suffix a, struct suffix b) { 
    return string(a.suff) < string(b.suff);
} 
bool binary_search(struct suffix *SA, int n, char *target) {
	
	sort(SA, SA+n, cmp_);
	// debug
	// for(int i=0; i<n; i++) cout << SA[i].suff << endl;

	int left = 0;
	int right = n;
	int target_len = strlen(target);
	while (left < right) {
		int mid = (left + right) / 2; 
		if (strncmp(SA[mid].suff, target, target_len) < 0) left = mid + 1;
		else if (strncmp(SA[mid].suff, target, target_len) > 0) right = mid - 1;
 		else return true;
	}
	return false;
}