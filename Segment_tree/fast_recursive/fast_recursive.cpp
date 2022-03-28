#include <iostream>

using namespace std;

const int MAX_N = 1e6;
int arr[MAX_N + 2];
int st[4 * MAX_N + 2];

void print(int);

int realSize(int); // nearest to N bigger power of two

void init(int, int, int);

void edit(int, int, int, int, int, int);

int sum(int, int, int, int, int, int);

int main() {
	int N;
	cin >> N;

	for (int i = 0; i < N; i++) cin >> arr[i];

	int real_N = realSize(N); // change N to the real size at the beginning; needed for building the segment tree and everything else

	init(1, real_N, N); // start from root (index 1)

	int M;
	cin >> M;

	char type;
	int index, val;
	int start, end;

	for (int i = 0; i < M; i++) {
		cin >> type;

		if (type == 'e') {
			cin >> index >> val;
			edit(index, val, real_N, 0, real_N - 1, 1);
		}

		if (type == 's') {
			cin >> start >> end;
			cout << sum(start, end, real_N, 0, real_N - 1, 1) << '\n';
		}
	}
	return 0;
}

void print(int N) { // call it with N being the real or the entered size of the array for debugging purposes only
	cout << "Segment tree:\n";
	for (int i = 0; i < 2 * realSize(N); i++) cout << st[i] << " ";
	cout << endl;
}

int realSize(int N) {
	int ans = 1;

	while (N > ans) ans *= 2;

	return ans;
}

void init(int i, int N, int n) { // here N is the real size given from the function and n being the original length
	if (i >= N) { // current node is leaf
		if (i >= N + n) { // avoid getting out of the arr[] boundaries filling the dummy values as explained in 4.4.2.
			st[i] = 0;
			return;
		}

		st[i] = arr[i - N];
		return;
	}

	init(2 * i, N, n);
	init(2 * i + 1, N, n);

	st[i] = st[2 * i] + st[2 * i + 1];
}

void edit(int pos, int val, int N, int l, int r, int i) {
	if (i >= N) {
		st[i] = val;
		return;
	}

	int mid = (l + r) / 2;
	
	if (pos <= mid) edit(pos, val, N, l, mid, 2 * i); // go to the left
	else edit(pos, val, N, mid + 1, r, 2 * i + 1); // go to the right

	st[i] = st[2 * i] + st[2 * i + 1];
}

int sum(int start, int end, int N, int l, int r, int i) {
	if (start <= l and r <= end) { // situation 1.
		return st[i];
	}

	if (r < start or end < l) { // situation 2.
		return 0;
	}

	// if not situation 1. or 2. then situation 3.

	int mid = (l + r) / 2;

	return sum(start, end, N, l, mid, 2 * i) + sum(start, end, N, mid + 1, r, 2 * i + 1);
}
