#include <stdio.h>
#include <string.h>

// Define a structure for Big_Int type
typedef struct {
	int digits[100]; // Array to store digits (up to 100 digits)
	int length;      // Length of the number (number of digits)
} Big_Int;

// Function to initialize a Big_Int number from a string
Big_Int init_Big_Int(char str[]) {
	Big_Int num;
	int len = strlen(str);

	// Initialize digits array with digits from string (in reverse order)
	for (int i = 0; i < len; i++) {
		num.digits[len - 1 - i] = str[i] - '0'; // Convert char to int
	}

	num.length = len; // Set length of the number
	return num;
}

// Function to print a Big_Int number
void print_Big_Int(Big_Int num) {
	for (int i = num.length - 1; i >= 0; i--) {
		printf("%d", num.digits[i]);
	}
	printf("\n");
}

// Function to add two Big_Int numbers
Big_Int add_Big_Int(Big_Int num1, Big_Int num2) {
	Big_Int result;
	int carry = 0;
	int max_len = (num1.length > num2.length) ? num1.length : num2.length;

	for (int i = 0; i < max_len; i++) {
		int sum = carry;
		if (i < num1.length) sum += num1.digits[i];
		if (i < num2.length) sum += num2.digits[i];

		result.digits[i] = sum % 10;
		carry = sum / 10;
	}

	if (carry > 0) {
		result.digits[max_len] = carry;
		result.length = max_len + 1;
	}
	else {
		result.length = max_len;
	}

	return result;
}

// Function to subtract two Big_Int numbers (assuming num1 >= num2)
Big_Int sub_Big_Int(Big_Int num1, Big_Int num2) {
	Big_Int result;
	int borrow = 0;
	int max_len = num1.length;

	for (int i = 0; i < max_len; i++) {
		int diff = num1.digits[i] - borrow;
		if (i < num2.length) diff -= num2.digits[i];

		if (diff < 0) {
			diff += 10;
			borrow = 1;
		}
		else {
			borrow = 0;
		}

		result.digits[i] = diff;
	}

	// Remove leading zeros
	while (max_len > 1 && result.digits[max_len - 1] == 0) {
		max_len--;
	}

	result.length = max_len;
	return result;
}

// Function to shift left a Big_Int number (multiply by 10^shift)
Big_Int shift_Left(Big_Int num, int shift) {
	Big_Int result = num;

	// Shift digits to the left
	for (int i = result.length - 1; i >= 0; i--) {
		result.digits[i + shift] = result.digits[i];
	}

	// Fill leading zeros
	for (int i = 0; i < shift; i++) {
		result.digits[i] = 0;
	}

	result.length += shift;
	return result;
}

// Function to slice the first n digits of a Big_Int number
Big_Int slice_Big_Int(Big_Int num, int n) {
	Big_Int result;
	int len = (n < num.length) ? n : num.length;

	for (int i = 0; i < len; i++) {
		result.digits[i] = num.digits[i];
	}

	result.length = len;
	return result;
}

// Function to multiply a Big_Int number by a single digit
Big_Int multiply_Big_Int_single(Big_Int num, int digit) {
	Big_Int result;
	int carry = 0;

	for (int i = 0; i < num.length; i++) {
		int prod = num.digits[i] * digit + carry;
		result.digits[i] = prod % 10;
		carry = prod / 10;
	}

	if (carry > 0) {
		result.digits[num.length] = carry;
		result.length = num.length + 1;
	}
	else {
		result.length = num.length;
	}

	return result;
}

// Function to multiply two Big_Int numbers
Big_Int Big_Number_Multi(Big_Int X, Big_Int Y, int n) {
	Big_Int m1, m2, m3, A, B, C, D;
	int s = 1; // Default to positive sign

	// Handle sign of X
	if (X.length == 1 && X.digits[0] == 0) {
		s = 0; // X = 0
	}

	// Handle sign of Y
	if (Y.length == 1 && Y.digits[0] == 0) {
		s = 0; // Y = 0
	}

	// Reverse sign if necessary
	if (s == -1) {
		X.digits[X.length - 1] = 1;
		Y.digits[Y.length - 1] = 1;
	}

	// Base case: single digit multiplication
	if (n == 1) {
		Big_Int result = multiply_Big_Int_single(X, Y.digits[0]);
		return result;
	}
	else {
		// Divide X and Y into A, B, C, D
		A = slice_Big_Int(X, n / 2);
		B = slice_Big_Int(X, 0);
		C = slice_Big_Int(Y, n / 2);
		D = slice_Big_Int(Y, 0);

		// Recursive calls to compute m1, m2, m3
		m1 = Big_Number_Multi(A, C, n / 2);
		m2 = Big_Number_Multi(sub_Big_Int(A, B), sub_Big_Int(D, C), n / 2);
		m3 = Big_Number_Multi(B, D, n / 2);

		// Calculate result using the formula
		Big_Int temp1 = shift_Left(m1, n);
		Big_Int temp2 = shift_Left(add_Big_Int(m1, add_Big_Int(m2, m3)), n / 2);
		Big_Int temp3 = m3;

		Big_Int result = add_Big_Int(add_Big_Int(temp1, temp2), temp3);
		return result;
	}
}

int main() {
	// Initialize two Big_Int numbers
	Big_Int X = init_Big_Int("1234567890123456789");
	Big_Int Y = init_Big_Int("9876543210987654321");
	int n = 20; // Length of the numbers (adjust as needed)

	// Print the initial Big_Int numbers
	printf("X: ");
	print_Big_Int(X);
	printf("Y: ");
	print_Big_Int(Y);

	// Perform Big_Number_Multi
	Big_Int result = Big_Number_Multi(X, Y, n);

	// Print the result
	printf("Result: ");
	print_Big_Int(result);

	getchar();

	return 0;
}
