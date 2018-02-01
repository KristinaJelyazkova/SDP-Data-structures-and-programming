#include<iostream>
#include<fstream>
#include<queue>
#include<string>

//�� �� ��������� ���������, �������� ������� �� ������� � ������� � ���(�� 20 �������), 
//���(�� 40 �������) � ����� � ��(���� �����).

struct Animal {
	std::string name;
	std::string species;
	int weight;
	Animal(std::string _name, std::string _species, int _weight)
		: name(_name), species(_species), weight(_weight){}
};

std::ostream& operator<<(std::ostream& out, Animal animal) {
	out << animal.name << " " << animal.species << " " << animal.weight << std::endl;
	return out;
}

//�� �� ������ �������, ����� �� ������ ������ Q �� ������� � ������ ������ �� ����� 
//w1 < w2 < ... < wn ��������� � ��������� ���, ��������� ������ �� n+1 ������ 
//q0, q1, q2, ..., qn � ������� ��������� �� Q ����, �� � �������� qi �� �� ������� 
//������� � ����� �� wi �� wi+1 (�������, �� w0 = 0, wn+1 = 200000).

void makeQueue(std::queue<Animal> animals, std::queue<int> weights, std::queue<std::queue<Animal>> &ordered) {
	if (weights.empty()) {
		ordered.push(animals);
		return;
	}

	if (animals.empty()) {
		ordered.push(std::queue<Animal>());
		weights.pop();
		makeQueue(animals, weights, ordered);
	}
	else {

		std::queue<Animal> heavier, current;
		int weight = weights.front();
		weights.pop();

		while (!animals.empty()) {
			Animal animal = animals.front();
			animals.pop();
			if (animal.weight < weight) {
				current.push(animal);
			}
			else {
				heavier.push(animal);
			}
		}

		ordered.push(current);

		makeQueue(heavier, weights, ordered);
	}
}

//�� �� ������ �������, ����� �� ������ ������ �� ������ �� ������� � ����� 
//����� �� ������ ������� ������� �� ������ �������, ����� �� ������� � 
//����������� ������ � ������� ���� � ��� animals.txt.

void saveInFile(std::queue<std::queue<Animal>> animals, int n) {
	std::ofstream out("animals.txt");
	while (n > 0) {
		animals.pop();
		n--;
	}
	std::queue<Animal> anim = animals.front();
	while (!anim.empty()) {
		out << anim.front();
		anim.pop();
	}
}


void testMakeQueue() {
	std::queue<Animal> animals;
	animals.push(Animal("Eli", "elephant", 300));
	animals.push(Animal("Tiggy", "tiger", 100));
	animals.push(Animal("Stuart", "mouse", 10));
	animals.push(Animal("Tom", "cat", 40));
	animals.push(Animal("Lola", "lamma", 150));
	animals.push(Animal("Rihanna", "rhino", 500));

	std::queue<int> weights;
	weights.push(50);
	weights.push(200);

	std::queue<std::queue<Animal>> ordered;

	makeQueue(animals, weights, ordered);

	saveInFile(ordered, 1);

	while (!ordered.empty()) {
		std::queue<Animal> crr = ordered.front();
		ordered.pop();
		std::cout << "Category:\n";
		if (crr.empty()) {
			std::cout << "No animals in this category.\n";
		}
		else {
			while (!crr.empty()) {
				std::cout << crr.front();
				crr.pop();
			}
		}
	}
}


int main() {
	testMakeQueue();

	system("pause");
	return 0;
}