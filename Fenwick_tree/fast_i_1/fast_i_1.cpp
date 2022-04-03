#include <iostream>

using namespace std;

const int MAX_N = 1e6;
int arr[MAX_N + 2];
int ft[MAX_N + 2];

void init(int);

void edit(int, int, int);

int sum(int, int);

int main() {
	int N;
	cin >> N;

	for (int i = 0; i < N; i++) cin >> arr[i];

	init(N);

	int M;
	cin >> M;

	char type;
	int index, val;
	int start, end;

	for (int i = 0; i < M; i++) {
		cin >> type;

		if (type == 'e') {
			cin >> index >> val;
			edit(index, val, N);
		}

		if (type == 's') {
			cin >> start >> end;
			cout << sum(start, end) << '\n';
		}
	}

	return 0;
}

void init(int len) {
	ft[1] = arr[0];

	for (int i = 2; i <= len; i++) ft[i] = ft[i - 1] + arr[i - 1];

	for (int i = len; i >= 1; i--) ft[i] -= ft[i - (i & (-i))];
}

void edit(int pos, int val, int len) {
	int diff = val - arr[pos];
	arr[pos] = val;
	for (int i = pos + 1; i <= len; i += (i & (-i))) ft[i] += diff;
}

int sum(int start, int end) {
	int to_start = 0, to_end = 0; // to_start - don't include start; to_end - include end

	for (int i = start; i >= 1; i -= (i & (-i))) to_start += ft[i];
	
	for (int i = end + 1; i >= 1; i -= (i & (-i))) to_end += ft[i];

	return to_end - to_start;
}
