#include <iostream>

using namespace std;

const int MAX_N = 1e6;
int arr[MAX_N + 2];
int st[2 * MAX_N + 2];

void print(int);

int realSize(int); // nearest to N bigger power of two

void init(int, int);

void edit(int, int, int, int, int, int);

int main() {
	int N;
	cin >> N;

	for (int i = 0; i < N; i++) cin >> arr[i];

	N = realSize(N); // change N to the real size at the beginning; needed for building the segment tree and everything else

	init(1, N); // start from root (index 1)

	int M;
	cin >> M;

	char type;
	int index, val;
	int start, end;

	for (int i = 0; i < M; i++) {
		cin >> type;

		if (type == 'e') {
			cin >> index >> val;
			edit(index, val, N, 0, N - 1, 1);
			print(N);
		}
	}
	return 0;
}

void print(int N) {
	cout << "Segment tree:\n";
	for (int i = 0; i < 2 * realSize(N); i++) cout << st[i] << " ";
	cout << endl;
}

int realSize(int N) {
	int ans = 1;

	while (N > ans) ans *= 2;

	return ans;
}

void init(int i, int N) { // here N is the real size given from the function
	if (i >= N) { // current node is leaf
		st[i] = arr[i - N];
		return;
	}

	init(2 * i, N);
	init(2 * i + 1, N);

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
