//Имаме група от N човека.Всеки човек има 0 или повече най - добри приятели, с
//които споделя всичките си тайни(възможно е А да е най - добър приятел на Б, но Б да не е
//на А).Когато човек научи нечия тайна, веднага я споделя със своите най - добри приятели.
//По даден човек Х, споделил тайната си със своите приятели, да се намери :
//колко души ще узнаят тайната на Х

#include<iostream>
#include<set>
#include<map>

int countPeople(bool G[7][7], int n, int X, std::set<int> &visited) {
	if (visited.count(X) > 0) {
		return 0;
	}
	int count = 1;
	visited.insert(X);
	for (int Y = 0; Y < n; Y++) {
		if (G[X][Y]) {
			count += countPeople(G, n, Y, visited);
		}
	}
	return count;
}

//кой ще чуе тайната на Х от най - много различни хора

void maxPeopleHelp(bool G[7][7], int n, int X, std::set<int> &visited, std::map<int, int> &map) {
	if (visited.count(X) > 0) {
		return;
	}
	visited.insert(X);
	for (int Y = 0; Y < n; Y++) {
		if (Y != X && G[X][Y]) {
			if (map.count(Y) == 0) {
				map[Y] = 1;
			}
			else {
				++map[Y];
			}
			maxPeopleHelp(G, n, Y, visited, map);
		}
	}
}

int maxPeople(bool G[7][7], int n, int X) {
	std::set<int> visited;
	std::map<int, int> map;
	maxPeopleHelp(G, n, X, visited, map);
	bool flag = true;
	int max = 0, maxPerson = 0;
	for (std::map<int, int>::iterator it = map.begin(); it != map.end(); it++) {
		if (flag) {
			maxPerson = it->first;
			max = it->second;
			flag = false;
		}
		else if (max < it->second) {
			maxPerson = it->first;
			max = it->second;
		}
	}
	return maxPerson;
}

void testCountPeople() {
	bool G[7][7] = {
		0, 0, 1, 0, 0, 0, 1,
		0, 1, 0, 1, 0, 1, 0,
		0, 0, 1, 0, 0, 0, 1,
		0, 1, 0, 0, 1, 0, 0,
		0, 1, 0, 0, 0, 1, 0,
		1, 0, 1, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0
	};

	std::set<int> visited;
	std::cout << countPeople(G, 7, 5, visited) << std::endl;
	std::cout << maxPeople(G, 7, 3) << std::endl;
}


int main() {
	testCountPeople();

	system("pause");
	return 0;
}