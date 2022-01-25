#include <iostream>

using namespace std;

const int MAX_N = 1e5;

struct node {
	int left;
	int right;
	int freq;
};

node arr[MAX_N + 2];
node st[2 * MAX_N + 2];

void print(int); // debugging function printing the segment tree

int fill_seq(int); // returns the number of sequences

int realSize(int);

void init(int, int, int);

int freq(int, int, int, int, int, int);

void empty_array(int);

int main() {
	int n, q;
	cin >> n;

	while (n != 0) {
		cin >> q;
		
		int num_seq = realSize(fill_seq(n)); // make num_seq equal to the real size used in the segment tree

		init(1, num_seq, n);

		int start, end;

		for (int i = 0; i < q; i++) {
			cin >> start >> end;
			cout << freq(start, end, num_seq, st[1].left, st[1].right, 1) << endl;
		}
		
		empty_array(n);

		cin >> n;
	}
}

void print(int num_seq) {
	for (int i = 0; i <= 2 * num_seq; i++) {
		cout << st[i].left << " " << st[i].right << " " << st[i].freq << endl;
	}
}

int fill_seq(int n) {
	int a, last_a, num_seq = 0, start_index = 1;

	cin >> a;
	for (int i = 2; i <= n; i++) {
		last_a = a;
		cin >> a;

		if (a != last_a) { // new sequence started
			arr[num_seq].left = start_index;
			arr[num_seq].right = i - 1;
			arr[num_seq].freq = arr[num_seq].right - arr[num_seq].left + 1;

			start_index = i;
			num_seq++;
		}
	}

	// count the last sequence

	arr[num_seq].left = start_index;
	arr[num_seq].right = n;
	arr[num_seq].freq = arr[num_seq].right - arr[num_seq].left + 1;

	start_index = n + 1;
	num_seq++;

	return num_seq;
}

int realSize(int N) {
	int ans = 1;

	while (N > ans) ans *= 2;

	return ans;
}

void init(int i, int N, int n) { // N - number of sequences, n - length of the entered sequence
	if (i >= N) { // leaf
		st[i].left = arr[i - N].left;
		st[i].right = arr[i - N].right;
		st[i].freq = arr[i - N].freq;
		return;
	}

	init(2 * i, N, n);
	init(2 * i + 1, N, n);

	st[i].left = st[2 * i].left;
	st[i].right = st[2 * i + 1].right;
	if (st[2 * i + 1].right == 0 and st[2 * i].right != 0) st[i].right = n; // fix for when merged with dummy values
	st[i].freq = max(st[2 * i].freq, st[2 * i + 1].freq);
}

int freq(int start, int end, int N, int l, int r, int i) {
	if (start <= l and r <= end) { // full overlap
		return st[i].freq;
	}

	if (r < start or end < l) { // no overlap
		return 0;
	}

	if (i >= N) { // leaf - get only a part of it
		if (l <= start and end <= r) return end - start + 1;
		if (l <= start) return r - start + 1;
		if (l > start) return end - l + 1;
	}

	return max(freq(start, end, N, st[2 * i].left, st[2 * i].right, 2 * i), freq(start, end, N, st[2 * i + 1].left, st[2 * i + 1].right, 2 * i + 1));
}

void empty_array(int N) {
	for (int i = 0; i <= N + 2; i++) {
		arr[i].left = 0;
		arr[i].right = 0;
		arr[i].freq = 0;
	}

	for (int i = 0; i <= 2 * N + 2; i++) {
		st[i].left = 0;
		st[i].right = 0;
		st[i].freq = 0;
	}
}
