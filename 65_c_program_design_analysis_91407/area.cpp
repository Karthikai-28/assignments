#include <bits/stdc++.h>
using namespace std;

int largestArea(int arr1[], int n,
				int arr2[], int m)
{
	int end = 0, start = 0, i = 0, j = 0;
	sort(arr1, arr1 + n);
	sort(arr2, arr2 + m);
	while (i < n and j < m) {
		if (arr1[i] == arr2[j]) {
			if (start == 0)
				start = arr1[i];
			else
				end = arr1[i];
			i++;
			j++;
		}
		else if (arr1[i] > arr2[j])
			j++;
		else
			i++;
	}
	if (end == 0 or start == 0)
		return 0;
	else
		return (end - start);
}

int main()
{
	int arr1[] = { 3, 3, 4, 4, 6, 6, 10, 10, 13, 13, 17, 17, 18, 18, 20, 20};

	int N = sizeof(arr1) / sizeof(arr1[0]);

	int arr2[] = { 0, 1, 1, 3, 3, 6, 6, 2, 2, 5, 5, 1, 1, 8, 8, 0};

	int M = sizeof(arr2) / sizeof(arr2[0]);

	cout << largestArea(arr1, N, arr2, M);

	return 0;
}
