#include<iostream>
#include<stack>

const int accessible = 0;
const int mazeSize = 10;
const int visited = 8;
const int goal = 9;

int maze[mazeSize][mazeSize] ={ 
	0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	1, 0, 1, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 1, 0, 0, 0, 0, 0, 0, 9 };

bool correct(int x, int y) {
	return x >= 0 && x < mazeSize &&
		y >= 0 && y < mazeSize;
}

bool way(int x, int y) {
	if (!correct(x, y)) {
		return false;
	}
	if (maze[x][y] == goal) {
		return true;
	}
	if (maze[x][y] != accessible) {
		return false;
	}
	maze[x][y] = visited;
	if (way(x, y + 1)) {
		return true;
	}
	if (way(x + 1, y)) {
		return true;
	}
	if (way(x, y - 1)) {
		return true;
	}
	if (way(x - 1, y)) {
		return true;
	}
	return false;
}

bool isGoal(std::pair<int,int> &p) {
	return correct(p.first, p.second) && maze[p.first][p.second] == goal;
}

std::ostream& operator<<(std::ostream& out, std::stack<std::pair<int, int>> s) {
	out << s.size() << " elements.\n";
	while (!s.empty()) {
		out << '(' << s.top().first << " , " << s.top().second << ')' << std::endl;
		s.pop();
	}
	return out;
}

bool wayIter(int x, int y) {
	std::stack<std::pair<int, int>> s;
	s.push({ x,y });
	while (!s.empty() && !isGoal(s.top())) {
		std::pair<int, int> crrState = s.top();
		s.pop();
		if (correct(crrState.first, crrState.second) &&
			maze[crrState.first][crrState.second] == accessible) {
			maze[crrState.first][crrState.second] = visited;
			s.push({ crrState.first - 1, crrState.second });
			s.push({ crrState.first, crrState.second - 1 });
			s.push({ crrState.first + 1, crrState.second });
			s.push({ crrState.first, crrState.second + 1});
		}
	}
	return !s.empty();
}

class Mario {
private:
	std::stack<std::pair<int, int>> s;
public:
	Mario(int, int);
	void makeStep();
	std::pair<int, int> getCurrentPosition();
	bool canMakeMoreSteps();
	bool goalReached();
};

Mario::Mario(int x, int y) {
	s.push({ x,y });
}

void Mario::makeStep() {
	std::pair<int, int> crrState = s.top();
	s.pop();
	int x = crrState.first, y = crrState.second;
	if (correct(x, y) &&
		maze[x][y] == accessible) {
		maze[x][y] = visited;
		s.push({ x - 1, y });
		s.push({ x, y - 1 });
		s.push({ x + 1, y });
		s.push({ x, y + 1 });
	}
}

std::pair<int, int> Mario::getCurrentPosition() {
	return s.top();
}

bool Mario::canMakeMoreSteps() {
	return !s.empty() && !isGoal(s.top());
}

bool Mario::goalReached() {
	return isGoal(s.top());
}

int main() {
	Mario m(0, 0);
	while (m.canMakeMoreSteps() && !m.goalReached()) {
		std::cout << "Mario is currently at position ("
			<< m.getCurrentPosition().first
			<< ","
			<< m.getCurrentPosition().second
			<< ")"
			<< std::endl;
		m.makeStep();
	}
	std::cout << "Goal reached: " << (m.goalReached() ? "Yes" : "No") << std::endl;
	system("pause");
	return 0;
}