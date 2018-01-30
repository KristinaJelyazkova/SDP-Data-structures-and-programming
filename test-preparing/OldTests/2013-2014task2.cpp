//Äàäåíè ñà äâà ñòåêà îò ÷èñëà, ïîäðåäåíè â íàìàëÿâàù ðåä îò âúðõà êúì äúíîòî.
//Äà ñå íàïèøå ôóíêöèÿ mergeStacks, êîÿòî ÷ðåç îïåðàöèèòå push è pop ïîñòðîÿâà íîâ ñòåê, 
//êîéòî ñå ñúñòîè îò âñè÷êè åëåìåíòè íà äàäåíèòå äâà ñòåêà, ïîäðåäåíè â íàðàñòâàù ðåä îò 
//âúðõà êúì äúíîòî.

#include<iostream>
#include<stack>

void mergeStacks(std::stack<int> s1, std::stack<int> s2, std::stack<int> &result) {
	if (s1.empty()) {
		while (!s2.empty()) {
			result.push(s2.top());
			s2.pop();
			return;
		}
	}
	if (s2.empty()) {
		while (!s1.empty()) {
			result.push(s1.top());
			s1.pop();
			return;
		}
	}
	int top1 = s1.top();
	int top2 = s2.top();
	if (top1 > top2) {
		result.push(top1);
		s1.pop();
		mergeStacks(s1, s2, result);
	}
	else {
		result.push(top2);
		s2.pop();
		mergeStacks(s1, s2, result);
	}
}

//Ïðèìåð: àêî ïúðâèÿò ñòåê ñúäúðæà 5, 3, 1, à âòîðèÿò ñòåê ñúäúðæà ÷èñëàòà 6, 2, 1, 
//ïîëó÷åíèÿò ñòåê òðÿáâà äà ñúäúðæà ÷èñëàòà 1, 1, 2, 3, 5, 6.

void testMergeStacks() {
	std::stack<int> s1;
	s1.push(1);
	s1.push(3);
	s1.push(5);
	std::stack<int> s2;
	s2.push(1);
	s2.push(2);
	s2.push(6);
	std::stack<int> result;
	mergeStacks(s1, s2, result);
	while (!result.empty()) {
		std::cout << result.top() << " ";
		result.pop();
	}
	std::cout << std::endl;
}

/*int main() {
	testMergeStacks();

	system("pause");
	return 0;
}*/
