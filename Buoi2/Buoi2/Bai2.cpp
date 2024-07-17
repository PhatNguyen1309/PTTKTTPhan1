#include <stdio.h>
#include <stdlib.h>

// Hàm trộn hai nửa đã sắp xếp của mảng A
void Merge(int A[], int left, int mid, int right) {
	int n1 = mid - left + 1; // Số lượng phần tử của nửa đầu
	int n2 = right - mid;    // Số lượng phần tử của nửa sau

	// Tạo các mảng tạm để chứa nửa đầu và nửa sau
	int *L = (int *)malloc(n1 * sizeof(int));
	int *R = (int *)malloc(n2 * sizeof(int));

	// Sao chép dữ liệu từ mảng A vào mảng tạm L và R
	for (int i = 0; i < n1; i++)
		L[i] = A[left + i];
	for (int j = 0; j < n2; j++)
		R[j] = A[mid + 1 + j];

	// Hợp nhất các mảng tạm L và R vào mảng A
	int i = 0, j = 0, k = left;
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			A[k] = L[i];
			i++;
		}
		else {
			A[k] = R[j];
			j++;
		}
		k++;
	}

	// Sao chép các phần tử còn lại của L vào mảng A nếu có
	while (i < n1) {
		A[k] = L[i];
		i++;
		k++;
	}

	// Sao chép các phần tử còn lại của R vào mảng A nếu có
	while (j < n2) {
		A[k] = R[j];
		j++;
		k++;
	}

	// Giải phóng bộ nhớ sau khi sử dụng
	free(L);
	free(R);
}

// Hàm sắp xếp Merge Sort
void Merge_Sort(int A[], int left, int right) {
	if (left < right) {
		int mid = left + (right - left) / 2; // Tìm điểm chia

		// Gọi đệ quy để sắp xếp từng nửa
		Merge_Sort(A, left, mid);
		Merge_Sort(A, mid + 1, right);

		// Trộn các nửa đã sắp xếp lại với nhau
		Merge(A, left, mid, right);
	}
}

int main() {
	int A[] = { 12, 11, 13, 5, 6, 7 }; // Mảng cần sắp xếp
	int n = sizeof(A) / sizeof(A[0]); // Số lượng phần tử trong mảng

	// In mảng trước khi sắp xếp
	printf("Mang ban dau: ");
	for (int i = 0; i < n; i++)
		printf("%d ", A[i]);
	printf("\n");

	// Sắp xếp mảng bằng Merge Sort
	Merge_Sort(A, 0, n - 1);

	// In mảng sau khi sắp xếp
	printf("Mang sau khi sap xep: ");
	for (int i = 0; i < n; i++)
		printf("%d ", A[i]);
	printf("\n");
	getchar();
	return 0;
}
