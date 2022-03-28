#include <iostream>

using namespace std;

const int MAX_N = 1e3; // The solution is slow so it isn't reasonable to create a bigger array
int arr[MAX_N + 2]; // Add two so it doesn't overflow

void edit(int, int);

int sum(int, int);

int main() {
	int N;
	cin >> N;

	for (int i = 0; i < N; i++) cin >> arr[i];

	int M;
	cin >> M;

	char type; // e for edit and s for sum
	int index, val; // for edit task
	int start, end; // for sum task

	for (int i = 0; i < M; i++) {
		cin >> type;
		
		if (type == 'e') {
			cin >> index >> val;
			edit(index, val);
		}

		if (type == 's') {
			cin >> start >> end;
			cout << sum(start, end) << '\n';
		}
	}

	return 0;
}

void edit(int pos, int val) {
	arr[pos] = val;
}

int sum(int start, int end) {
	int sum = 0;
	for (int i = start; i <= end; i++) sum += arr[i]; // that's why the execurion of a task has a time complexity of O(N)
	return sum;
}
