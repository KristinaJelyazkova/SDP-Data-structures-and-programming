#include<stack>

double polinomNaErmit(int n, double x) {
	if (n == 0) {
		return 1;
	}
	if (n == 1) {
		return 2 * x;
	}
	std::stack<double> s;
	s.push(1);
	s.push(2 * x);
	while (n > 1) {
		double current = s.top();
		s.pop();
		double previous = s.top();
		s.pop();
		s.push(current);
		s.push(2 * x * current + 2 * (n - 1) * previous);
		n--;
	}
	return s.top();
}