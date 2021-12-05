#include <iostream>

using namespace std;

const int MAX_N = 1e6; // now that the solution is faster larger N is possible
int arr[MAX_N + 2]; // as discussed in the book this can be omitted
int st[2 * MAX_N + 2];

void print(int);

void init(int);

void edit(int, int, int);

int sum(int, int, int);

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
			//insert sum function
			cout << sum(start, end, N) << endl;
		}
	}

	return 0;
}

void print(int N) { // call it with N being the size of the array for debugging purposes only
	cout << "Segment tree:\n";
	for (int i = 0; i < 2 * N; i++) cout << st[i] << " ";
	cout << endl;
}

void init(int N) {
	for (int i = N; i < 2 * N; i++) st[i] = arr[i - N];

	for (int i = N - 1; i > 0; i--) st[i] = st[2 * i] + st[2 * i + 1];
}

void edit(int pos, int val, int len) {
	pos = len + pos; // update the first position to edit
	int diff = val - st[pos];

	while (pos != 0){ // exit the loop when 1 / 2 = 0 is reached
		st[pos] += diff; // edit node
		pos /= 2; // move up -> only O(logn) time complexity
	}
}

int sum(int start, int end, int len) {
	int l = len + start;
	int r = len + end;
	int sum = 0;

	while (l != r) {
		if (l % 2 == 1) {
			sum += st[l];
			l++;
		}
		if (r % 2 == 0) {
			sum += st[r];
			r--;
		}
		l /= 2; // move up -> only O(logn) time complexity
		r /= 2; // move up -> only O(logn) time complexity
	}

	sum += st[l]; //does not matter whether l or r - they are equal
	
	return sum;
}
