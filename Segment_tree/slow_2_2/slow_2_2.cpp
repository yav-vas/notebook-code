// If something is unclear - try reading the comments from the previous file
#include <iostream>

using namespace std;

const int MAX_N = 1e3;
int arr[MAX_N + 2];
int prefix[MAX_N + 2]; // prefix[i] will store the sum of the elements with indexes from 0 to i - 1

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
	for (int i = 1; i <= len; i++) prefix[i] = prefix[i - 1] + arr[i - 1];
}

void edit(int pos, int val, int len) {
	int diff = val - arr[pos];
	for (int i = pos + 1; i <= len; i++) prefix[i] += diff; // that's why the execution of a task has a time complexity of O(N)
}

int sum(int start, int end) {
	return prefix[end + 1] - prefix[start]; // prefix[0] is 0 by default
}
