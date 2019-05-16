void build_hei(struct suffix *suffixes, int n) {
	int k;
	int sa, sa_prev;
	suffixes[0].hei = 0;
	for (int i = 1; i < n; i++) {
		k = 0;
		while (suffixes[i].suff[k] == suffixes[i-1].suff[k]) k++;
		suffixes[i].hei = k;
	}
}