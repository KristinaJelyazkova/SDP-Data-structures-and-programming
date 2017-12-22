#include<iostream>

double polNaErmitRec(double x, unsigned int n) {
	if (n == 0) return 1;
	if (n == 1) return 2 * x;
	return (2 * x * polNaErmitRec(x, n - 1)) + (2 * (n - 1) * polNaErmitRec(x, n - 2));
}

/*int main() {
	std::cout << polNaErmitRec(10, 5) << std::endl;
	system("pause");
	return 0;
}*/