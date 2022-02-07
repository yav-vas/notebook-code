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
int arr_position[MAX_N + 2]; // store in which leaf index is the entered element

int fill_seq(int); // reads the array, fills arr[], arr_position[] and returns the number of sequences

void init(int);

int freq(int, int, int);

void empty_array(int);

int main() {
	int n, q;
	cin >> n;

	while (n != 0) {
		cin >> q;

		int num_seq = fill_seq(n);

		init(num_seq);

		int start, end;

		for (int i = 0; i < q; i++) {
			cin >> start >> end;
			cout << freq(start, end, num_seq) << endl;
		}

		empty_array(n);

		cin >> n;
	}

	return 0;
}

int fill_seq(int n) {
	int a, last_a, num_seq = 0, start_index = 1;

	cin >> a;
	arr_position[1] = num_seq;

	for (int i = 2; i <= n + 1; i++) { // n + 1 in order to count the last sequence
		last_a = a;
		if (i != n + 1) cin >> a; // don't read if after the end of the sequence

		if (a != last_a or i == n + 1) { // new sequence started or the last ended
			arr[num_seq].left = start_index;
			arr[num_seq].right = i - 1;
			arr[num_seq].freq = arr[num_seq].right - arr[num_seq].left + 1;

			start_index = i;
			num_seq++;
		}

		if (i != n + 1) arr_position[i] = num_seq;
	}

	return num_seq;
}

void init(int N) {
	for (int i = N; i < 2 * N; i++) {
		st[i].left = arr[i - N].left;
		st[i].right = arr[i - N].right;
		st[i].freq = arr[i - N].freq;
	}

	for (int i = N - 1; i > 0; i--) {
		st[i].left = st[2 * i].left;
		st[i].right = st[2 * i + 1].right;
		st[i].freq = max(st[2 * i].freq, st[2 * i + 1].freq);
	}

	return;
}

int freq(int start, int end, int N) {
	int l = arr_position[start] + N;
	int r = arr_position[end] + N;

	int ans = 0;

	if (l == r) {
		ans = end - start + 1;
		return ans;
	}

	ans = max(ans, st[l].right - start + 1);
	ans = max(ans, end - st[r].left + 1);
	l++;
	r--;
	if (l > r) return ans;

	while (l < r) {
		if (l % 2 == 1) {
			ans = max(ans, st[l].freq);
			l++;
		}

		if (r % 2 == 0) {
			ans = max(ans, st[r].freq);
			r--;
		}

		l /= 2;
		r /= 2;
	}

	if (l > r) return ans;

	ans = max(ans, st[l].freq);

	return ans;
}

void empty_array(int N) {
	for (int i = 0; i < N + 2; i++) {
		arr[i].left = 0;
		arr[i].right = 0;
		arr[i].freq = 0;
		arr_position[i] = 0;
	}

	for (int i = 0; i < 2 * N + 2; i++) {
		st[i].left = 0;
		st[i].right = 0;
		st[i].freq = 0;
	}

	return;
}
