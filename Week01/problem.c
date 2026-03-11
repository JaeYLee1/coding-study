#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#if 0
// 1) 배열 연습문제
int main(void)
{
	int num;
	int a[100] = { 0 };
	int i = 0;

	while ((scanf("%d", &num) == 1) && num != 0)
	{
		// 일의 자리수만 저장
		a[i] = num % 10;
		i++;
	}

	//<i = +0
	for (int j = 0; j < i - 1; ++j) {
		for (int k = j + 1; k < i; ++k) {
			if (a[j] > a[k]) {
				int temp = a[j];
				a[j] = a[k];
				a[k] = temp;
			}
		}
	}

	int n1 = a[0];
	int n2 = 0;

	for (int p = 0; p < i+1; p++) {
		if (n1 != a[p]) {
			printf("%d : %d개\n", n1, n2);
			n1 = a[p];
			n2 = 0;
		}
		n2++;
	}

	return 0;
}
#endif

#if 0
// 수정된 내 코드
#include <stdio.h>

int main(void)
{
	int num;
	int a[100] = { 0 };
	int i = 0;

	while (scanf("%d", &num) == 1 && num != 0) {
		a[i] = num % 10;
		i++;
	}

	for (int j = 0; j < i - 1; ++j) {
		for (int k = j + 1; k < i; ++k) {
			if (a[j] > a[k]) {
				int temp = a[j];
				a[j] = a[k];
				a[k] = temp;
			}
		}
	}

	if (i > 0) {
		int n1 = a[0];
		int n2 = 1;

		for (int p = 1; p < i; p++) {
			if (n1 == a[p]) {
				n2++;
			}
			else {
				printf("%d : %d개\n", n1, n2);
				n1 = a[p];
				n2 = 1;
			}
		}

		printf("%d : %d개\n", n1, n2);
	}

	return 0;
}
#endif

#if 0
// 최적의 코드
// 배열 크기 10 (자릿수 0~9), 0으로 초기화(한 자리수의 갯수)
// 각 배열의 자릿수의 수 증가
int main(void)
{
	int n;
	int count[10] = { 0 };
	while ((scanf("%d", &n) == 1) && (n != 0))
		count[n % 10]++;

	for (int i = 0; i < 10; i++) {
		if (count[i] > 0) {
			printf("%d : %d개\n", i, count[i]);
		}
	}

	return 0;
}
#endif

// 2) 도약 (연습문제)
#if 0

// 이분 탐색
int binarySearch(int arr[], int size, int target)
{
	int low = 0;
	int high = size - 1;

	while (low <= high)
	{
		int mid = (low + high) / 2;

		if (arr[mid] > target) high = mid - 1;
		else if (arr[mid] < target) low = mid + 1;
		else return mid;
	}
	return -1;
}

// lower_bound: 타겟이상의 값이 처음 등장하는 인덱스를 반환하는 함수
int lower_bound(int arr[], int left, int right, int target)
{
	while (left < right) {
		int mid = (left + right) / 2;
		if (arr[mid] < target) left = mid + 1;
		else right = mid;
	}
	return left;
}

// upper_bound: 타켓보다 큰 값의 인덱스를 반환하는 함수
int upper_bound(int arr[], int left, int right, int target)
{
	while (left < right) {
		int mid = (left + right) / 2;
		if (arr[mid] <= target)left = mid + 1;
		else right = mid;
	}
	return left;
}

int main(void)
{
	int N;

	while ((scanf("%d", &N) == 1) && (N < 3))
		printf("연못의 갯수를 다시 입력해주세요.\n");

	int x[1000];

	// 좌표값 넣기
	for (int i = 0; i < N; i++)
		scanf("%d", &x[i]);

	for(int i =0; i<N-1; ++i)
		for (int j = i + 1; j < N; ++j) {
			if (x[i] > x[j]) {
				int temp = x[j];
				x[j] = x[i];
				x[i] = temp;
			}
		}

	int cnt = 0;
	// 좌표 선택
	for (int i = 0; i < N; ++i)
		for (int j = i + 1; j < N; ++j) {
			int A = x[i];
			int B = x[j];
			int d = B - A; // 첫번째 거리

			int L = B + d;
			int R = B + 2 * d;

			int left = lower_bound(x, j + 1, N, L);
			int right = upper_bound(x, j + 1, N, R);

			cnt += (right - left);
		}

	printf("%d\n", cnt);
	return 0;
}

#endif

#if 0
// n: 벨트위에 있는 초밥의 갯수
// k: 연속으로 초밥을 선택할 수 있는 수
void slidingWindowSum(int arr[], int n, int k) {
	int windowSum = 0;

	// 첫 번째 윈도우의 합 계산
	for (int i = 0; i < k; i++) {
		windowSum += arr[i];
	}

	// 슬라이딩 윈도우 적용
	for (int i = k; i < n; i++) {
		windowSum += arr[i] - arr[k - i];
	}
}

int main(void)
{
	// N: 접시의 수, d: 초밥의 가짓수
	// k: 연속해서 먹는 접시의 수, c: 쿠폰 번호
	int N, d, k, c;
	int arr[33000];
	int cnt[3001] = { 0 };

	scanf("%d %d %d %d", &N, &d, &k, &c);

	// 벨트 위 종류별 초밥
	// count[x] == 1 -> 0 (종류 하나 사라짐)
	// count[x] == 0 -> 1 (종류 하나 생김)
	// count[x] >= 2 (종류 하나 취급)
	
	// 벨트에 놓여진 초밥
	for (int i = 0; i < N; i++)
		scanf("%d", &arr[i]);

	for (int i = 0; i < k - 1; i++)
		arr[N + i] = arr[i];

	// 종류 수 num
	int num = 0;

	// 처음 윈도우
	for (int i = 0; i < k; i++) {
		cnt[arr[i]]++;
		if (cnt[arr[i]] == 1)
			num++;
	}

	int max = num;
	if (cnt[c] == 0) max++;

	// 슬라이딩 윈도우
	for (int i = k; i < N + k - 1; i++) {
		cnt[arr[i - k]]--;
		if (cnt[arr[i - k]] == 0)
			num--;

		cnt[arr[i]]++;
		if (cnt[arr[i]] == 1)
			num++;

		int total = num;
		if (cnt[c] == 0)total++;
		if (max < total) max = total;
	}

	printf("%d", max);

	return 0;
}
#endif