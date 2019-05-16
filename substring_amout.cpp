#include <cstring>
int sum(int n) {
 	int sum = 0;
 	for(int i = 1; i <= n; i++) sum += i;
 	return sum;
}

int hei_sum(struct suffixes *SA, int n) {
	int sum = 0;
	for(int i = 0; i < n; i++) sum += SA[i].hei;
	return sum;
}

void substring_amount(char *str, struct suffixes *SA, int n) {
	return sum(len(str)) - hei_sum(SA, n);
}