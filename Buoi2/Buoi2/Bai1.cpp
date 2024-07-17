#include <stdio.h>

// Hàm tìm kiếm nhị phân
int Binary_Search(int A[], int n, int key) {
	int left = 0; // vị trí phần tử đầu tiên trong mảng
	int right = n - 1; // vị trí phần tử cuối cùng trong mảng

	while (left <= right) {
		int mid = left + (right - left) / 2; //vị trí giữa mảng, tránh tràn số khi left và right lớn

		if (A[mid] == key)
			return mid; // Trả về vị trí của phần tử nếu tìm thấy key

		if (key < A[mid])
			right = mid - 1; // Nếu key nhỏ hơn phần tử ở vị trí mid, ta tìm kiếm bên trái của mid
		else
			left = mid + 1; // Nếu key lớn hơn phần tử ở vị trí mid, ta tìm kiếm bên phải của mid
	}

	return -1; // Không tìm thấy key trong mảng, trả về -1
}

int main() {
	int A[] = { 2, 4, 6, 8, 10, 12 }; // Mảng đã sắp xếp
	int n = sizeof(A) / sizeof(A[0]); // Số phần tử trong mảng
	int key = 8; // Giá trị cần tìm kiếm

	int result = Binary_Search(A, n, key);

	if (result != -1)
		printf(" Tim thay phan tu %d tai vi tri %d\n", key, result);
	else
		printf(" Khong tim thay phan tu %d trong mang.\n", key);

	getchar();

	return 0;
}
