#ifndef __TRIEMAP__
#define __TRIEMAP__

#include <vector>
#include <string>

//фиксираме мн. ключовете да са малките латински букви
template <class ValueType>
class TrieMap
{
public:
	TrieMap();

	ValueType& operator [] (const std::string &);
	const ValueType& operator [] (const std::string&) const;

	//bool hasKey(const std::string&) const;
	TrieMap(const TrieMap&);
	TrieMap<ValueType>& operator= (const TrieMap&);
	~TrieMap();
private:
	struct Node
	{
		std::vector<Node*> children;
		ValueType *value;
		Node(ValueType*);
	};
	Node *root;

	Node *seek(const std::string&,
		unsigned int,
		Node*);
	void copy(Node*&, Node*);
	void del(Node*);
};

template <class ValueType>
TrieMap<ValueType>::TrieMap() :root(nullptr) {}

template <class ValueType>TrieMap<ValueType>::Node::Node(ValueType* v)
{
	value = v;
	children.assign(26, nullptr);
}

template <class ValueType>
const ValueType& TrieMap<ValueType>::operator [] (const std::string &key) const
{
	Node *node = seek(key, 0, root);
	assert(node != nullptr);

	return *(node->value);
}

template <class ValueType>
ValueType& TrieMap<ValueType>::operator [] (const std::string &key)
{

	if (root == nullptr)
	{
		root = new Node(nullptr);
	}

	Node *crr = root;
	unsigned int index = 0;

	//P: crr винаги сочи текещо достигнатия
	//   възел на дървото, и той никога не NULL
	while (index < key.length())
	{
		assert(key[index] >= 'a' && key[index] <= 'z');
		Node *&child = crr->children[key[index] - 'a'];

		if (child == nullptr)
		{
			child = new Node(nullptr);
		}

		crr = child;

		index++;
	}
	if (crr->value == nullptr)
	{
		crr->value = new ValueType();
	}
	return *(crr->value);

}


template <class ValueType>
typename TrieMap<ValueType>::Node *TrieMap<ValueType>
::seek(const std::string &key,
	unsigned int height,
	Node *current)
{
	if (key == "" || height == key.length())
	{
		return current;
	}
	if (current == nullptr)
	{
		return nullptr;
	}

	assert(key[height] >= 'a' && key[height] <= 'z');
	unsigned int childIx = key[height] - 'a';

	return seek(key, height + 1, current->children[childIx]);
}

template <class ValueType>
void TrieMap<ValueType>::copy(Node* &crr, Node* otherCrr) {
	/*struct Node
	{
		std::vector<Node*> children;
		ValueType *value;
		Node(ValueType*);
	};
	Node *root;*/
	if (otherCrr == nullptr) {
		crr = nullptr;
		return;
	}
	crr = new Node(otherCrr->value);
	for (int i = 0; i < 26; i++) {
		copy(crr->children[i], otherCrr->children[i]);
	}
}

template <class ValueType>
TrieMap<ValueType>::TrieMap(const TrieMap& other) {
	copy(root, other.root);
}

template <class ValueType>
void TrieMap<ValueType>::del(Node* crr) {
	if (crr == nullptr) {
		return;
	}
	for (int i = 0; i < 26; i++) {
		del(crr->children[i]);
	}
	delete crr;
}

template <class ValueType>
TrieMap<ValueType>::~TrieMap() {
	del(root);
}

template <class ValueType>
TrieMap<ValueType>& TrieMap<ValueType>::operator= (const TrieMap& other) {
	if (this != &other) {
		del(root);
		copy(root, other.root);
	}
	return *this;
}

#endif