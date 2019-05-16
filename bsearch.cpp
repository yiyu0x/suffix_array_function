#include <iostream>
using namespace std;

bool binary_search(struct suffix *SA, int n, char *target) {
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