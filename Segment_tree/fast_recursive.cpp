#include <iostream>

using namespace std;

const int MAX_N = 1e6;
int arr[MAX_N + 2];
int st[2 * MAX_N + 2];

void print(int);

int realSize(int); // nearest to N bigger power of two

void init(int, int);

int main() {
	int N;
	cin >> N;

	for (int i = 0; i < N; i++) cin >> arr[i];

	init(1, realSize(N)); // start from root (index 1)

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
