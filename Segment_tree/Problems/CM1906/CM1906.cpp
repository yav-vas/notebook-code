#include <iostream>

using namespace std;

const int MAX_N = 1e5;

long long arr[MAX_N + 2];

struct node {
	int distinct[11 + 2];
};

node st[2 * MAX_N + 2];

void print(int);

int count_distinct(long long);

void init(int);

void update(int, int, long long);

int query(int, int, int, int);

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int N;

	cin >> N;

	for (int i = 0; i < N; i++) cin >> arr[i];

	init(N);

	int Q;
	int type;
	int u, l, r, c;
	long long v;

	cin >> Q;
	for (int i = 0; i < Q; i++) {
		cin >> type;

		if (type == 0) {
			cin >> u >> v;
			
			u--;

			update(N, u, arr[u] + v);
		}

		if (type == 1) {
			cin >> u >> v;

			u--;

			update(N, u, v);
		}

		if (type == 2) {
			cin >> l >> r >> c;

			l--;
			r--;

			cout << query(l, r, c, N) << "\n";
		}
	}

	return 0;
}

void print(int N) {
	for (int i = 1; i < 2 * N; i++) {
		for (int j = 1; j <= 10; j++) {
			cout << st[i].distinct[j] << " ";
		}
		cout << "\n";
	}

	return;
}

int count_distinct(long long num) {
	bool dig[10 + 2] = {0};

	while (num != 0) {
		dig[num % 10] = 1;
		num /= 10;
	}

	int ans = 0;

	for (int i = 0; i < 10; i++) ans += dig[i];

	return ans;
}

void init(int N) {
	for (int i = N; i < 2 * N; i++) {
		st[i].distinct[count_distinct(arr[i - N])] = 1;
	}
	
	for (int i = N - 1; i > 0; i--) {
		for (int j = 1; j <= 10; j++) st[i].distinct[j] = st[2 * i].distinct[j] + st[2 * i + 1].distinct[j];
	}

	return;
}

void update(int N, int index, long long val) {
	index += N;
	st[index].distinct[count_distinct(arr[index - N])] = 0; // delete the previous value
	arr[index - N] = val;
	st[index].distinct[count_distinct(arr[index - N])] = 1;
	index /= 2;

	while (index >= 1) {
		for (int i = 1; i <= 10; i++) st[index].distinct[i] = st[2 * index].distinct[i] + st[2 * index + 1].distinct[i];

		index /= 2;
	}

	return;
}

int query(int l, int r, int search, int N) {
	int ans = 0;

	l += N;
	r += N;

	while (l < r) {
		if (l % 2 == 1) {
			ans += st[l].distinct[search];
			l++;
		}

		if (r % 2 == 0) {
			ans += st[r].distinct[search];
			r--;
		}

		l /= 2;
		r /= 2;
	}

	if (l == r) ans += st[l].distinct[search];

	return ans;
}
