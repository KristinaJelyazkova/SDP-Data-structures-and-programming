#ifndef _HASHMAP_
#define _HASHMAP_

#include<vector>

template<class KeyType>
using HashFunction = unsigned int(*)(const KeyType&, unsigned int);

template<class KeyType, class ValueType>
class HashMap {
public:
	HashMap(unsigned int, HashFunction<KeyType>);
	HashMap(const HashMap<KeyType, ValueType>&);
	HashMap<KeyType, ValueType>& operator=(const HashMap<KeyType, ValueType>&);
	~HashMap();

	ValueType& operator[](const KeyType&);
	const ValueType& operator[](const KeyType&) const;

	bool hasKey(const KeyType&) const;

	bool operator==(const HashMap<KeyType, ValueType>&) const;
	bool operator!=(const HashMap<KeyType, ValueType>&) const;

	void resize(unsigned int);

	double efficiency() const;
	void print(std::ostream&) const;
	unsigned int sumOfAllValues() const;
	unsigned int countOfValuesBiggerThaZero() const;
	const KeyType& findKeyToBiggestValue() const;
	HashMap<KeyType, std::pair<ValueType, ValueType>> operator* (const HashMap<KeyType, ValueType> &)
	HashMap<KeyType, ValueType> operator+ (const HashMap<KeyType, ValueType> &) const;

private:
	struct kvpair {
		kvpair(KeyType _key, ValueType _value) : key(_key), value(_value) {}
		KeyType key;
		ValueType value;
	};

	int locate(const KeyType&, unsigned int) const;

	unsigned int size, count;
	HashFunction<KeyType> h;
	std::vector<std::vector<kvpair>> *buckets;
};

template<class KeyType, class ValueType>
HashMap<KeyType, ValueType>::HashMap(unsigned int _size, HashFunction _h) :
	size(_size), h(_h) {
	count = 0;
	buckets = new std::vector<std::vector<kvpair>>;
	std::vector<kvpair> emptyBucket;
	buckets->assign(size, emptyBucket);
}

template<class KeyType, class ValueType>
HashMap<KeyType, ValueType>::HashMap(const HashMap<KeyType, ValueType> &other) {
	size = other.size;
	h = other.h;
	count = other.count;
	buckets = new std::vector<std::vector<kvpair>>;
	*buckets = *other.buckets;
}

template<class KeyType, class ValueType>
HashMap<KeyType, ValueType>& HashMap<KeyType, ValueType>::operator=(const HashMap<KeyType, ValueType> &other) {
	if (this != &other) {
		delete buckets;
		size = other.size;
		h = other.h;
		count = other.count;
		buckets = new std::vector<std::vector<kvpair>>;
		*buckets = *other.buckets;
	}
	return *this;
}

template<class KeyType, class ValueType>
HashMap<KeyType, ValueType>::~HashMap() {
	delete buckets;
}

template<class KeyType, class ValueType>
int HashMap<KeyType, ValueType>::locate(const KeyType& key, unsigned int index) const {
	std::vector<kvpair> bucket = (*buckets)[index];
	for (int i = 0; i < bucket.size(); i++) {
		if (bucket[i].key == key) {
			return i;
		}
	}
	return -1;
}

template<class KeyType, class ValueType>
ValueType& HashMap<KeyType, ValueType>::operator[](const KeyType& key) {
	unsigned int index = h(key, size);
	assert(index < size);
	int i = locate(key, index);
	if (i == -1) {
		(*buckets)[index].push_back(kvpair(key, ValueType()));
		i = (*buckets)[index].size() - 1;
		count++;
	}
	return (*buckets)[index][i].value;
}

template<class KeyType, class ValueType>
const ValueType& HashMap<KeyType, ValueType>::operator[](const KeyType& key) const {
	unsigned int index = h(key, size);
	assert(index < size);
	int i = locate(key, index);
	assert(i >= 0);
	return (*buckets)[index][i].value;
}

template<class KeyType, class ValueType>
bool HashMap<KeyType, ValueType>::operator==(const HashMap<KeyType,ValueType> &other) const {
	for (int i = 0; i < buckets->size(); i++) {
		const std::vector<kvpair> &bucket = (*buckets)[i];
		for (int j = 0; j < bucket.size(); j++) {
			const KeyType &key = bucket[j].key;
			const ValueType &value = bucket[j].value;
			if (other.hasKey(key) && other[key] != value) {
				return false;
			}
		}
	}
	return count == other.count;
}

template<class KeyType, class ValueType>
bool HashMap<KeyType, ValueType>::operator!=(const HashMap<KeyType, ValueType> &other) const {
	return !((*this) == other);
}

template<class KeyType, class ValueType>
bool HashMap<KeyType, ValueType>::hasKey(const KeyType &key) const {
	unsigned int index = h(key, size);
	return locate(key, index) >= 0;
}

template<class KeyType, class ValueType>
void HashMap<KeyType, ValueType>::resize(unsigned int newSize) {
	HashMap<KeyType, ValueType> newMap(newSize, h);
	for (int i = 0; i < buckets->size(); i++) {
		const std::vector<kvpair> &bucket = (*buckets)[i];
		for (int j = 0; j < bucket.size(); j++) {
			const KeyType &key = bucket[j].key;
			const ValueType &value = bucket[j].value;
			newMap[key] = value;
		}
	}
	size = newSize;
	std::vector<std::vector<kvpair>> *save = buckets;
	buckets = newMap.buckets;
	newMap.buckets = save;
}

template<class KeyType, class ValueType>
double HashMap<KeyType, ValueType>::efficiency() const {
	double all = count;
	double coliding = 0;
	for (int i = 0; i < buckets->size(); i++) {
		const std::vector<kvpair> &bucket = (*buckets)[i];
		coliding += bucket.size();
	}
	return (all - coliding) / all;
}

template<class KeyType, class ValueType>
void HashMap<KeyType, ValueType>::print(std::ostream& out) const {
	for (int i = 0; i < buckets->size(); i++) {
		const std::vector<kvpair> &bucket = (*buckets)[i];
		for (int j = 0; j < bucket.size(); j++) {
			out << "m[" << bucket[j].key << "] = " << bucket[j].value << "\n";
		}
	}
}

template<class KeyType, class ValueType>
std::ostream& operator<<(std::ostream& out, const HashMap<KeyType, ValueType> &map) {
	map.print(out);
	return out;
}

template<class KeyType>
unsigned int HashMap<KeyType, unsigned int>::sumOfAllValues() const {
	unsigned int sum = 0;
	for (int i = 0; i < buckets->size(); i++) {
		const std::vector<kvpair> &bucket = (*buckets)[i];
		for (int j = 0; j < bucket.size(); j++) {
			sum += bucket[j].value;
		}
	}
	return sum;
}

template<class KeyType>
unsigned int HashMap<KeyType, unsigned int>::countOfValuesBiggerThaZero() const {
	unsigned int count = 0;
	for (int i = 0; i < buckets->size(); i++) {
		const std::vector<kvpair> &bucket = (*buckets)[i];
		for (int j = 0; j < bucket.size(); j++) {
			if (bucket[j].value > 0)
				count++;
		}
	}
	return count;
}

template<class KeyType>
const KeyType& HashMap<KeyType, unsigned int>::findKeyToBiggestValue() const {
	unsigned int max;
	KeyType &key;
	bool flag = false;
	for (int i = 0; i < buckets->size(); i++) {
		const std::vector<kvpair> &bucket = (*buckets)[i];
		for (int j = 0; j < bucket.size(); j++) {
			if (!flag) {
				key = bucket[j].key;
				max = bucket[j].value;
				flag = true;
			}
			else if (bucket[j].value > max) {
				key = bucket[j].key;
				max = bucket[j].value;
			}
		}
	}
	return key;
}

template<class KeyType, class ValueType>
HashMap<KeyType, std::pair<ValueType, ValueType>> HashMap<KeyType, ValueType>::operator* (const HashMap<KeyType, ValueType> &other) const {
	HashMap<KeyType, std::pair<ValueType, ValueType>> result(other.size, other.h);
	for (int i = 0; i < buckets->size(); i++) {
		const std::vector<kvpair> &bucket = (*buckets)[i];
		for (int j = 0; j < bucket.size(); j++) {
			const KeyType &key = bucket[j].key;
			const ValueType &value = bucket[j].value;
			if (other.hasKey(key)) {
				result[key] = { value, other[key] };
			}
		}
	}
	return result;
}

template<class KeyType, class ValueType>
HashMap<KeyType, ValueType> HashMap<KeyType, ValueType>::operator+ (const HashMap<KeyType, ValueType> &other) const {
	HashMap<KeyType, ValueType> result(size + other.size, other.h);
	for (int i = 0; i < buckets->size(); i++) {
		const std::vector<kvpair> &bucket = (*buckets)[i];
		for (int j = 0; j < bucket.size(); j++) {
			const KeyType &key = bucket[j].key;
			const ValueType &value = bucket[j].value;
			if (!other.hasKey(key)) {
				result[key] = value;
			}
		}
	}
	for (int i = 0; i < other.buckets->size(); i++) {
		const std::vector<kvpair> &bucket = (*other.buckets)[i];
		for (int j = 0; j < bucket.size(); j++) {
			const KeyType &key = bucket[j].key;
			const ValueType &value = bucket[j].value;
			if (!hasKey(key)) {
				result[key] = value;
			}
		}
	}
	return result;
}

template<class KeyType, class ValueType>
void HashMap<KeyType, ValueType>::map(void(*f)(ValueType&)) {
	for (int i = 0; i < buckets->size(); i++) {
		const std::vector<kvpair> &bucket = (*buckets)[i];
		for (int j = 0; j < bucket.size(); j++) {
			ValueType &value = bucket[j].value;
			f(value);
		}
	}
}

template<class KeyType, class ValueType>
void HashMap<KeyType, ValueType>::mapKeys(KeyType(*f)(const KeyType&)) {
	HashMap<KeyType, ValueType> result(size, h);
	for (int i = 0; i < buckets->size(); i++) {
		const std::vector<kvpair> &bucket = (*buckets)[i];
		for (int j = 0; j < bucket.size(); j++) {
			const KeyType &key = bucket[j].key;
			result[f(key)] = bucket[j].value;
		}
	}
	std::vector < std::vector<kvpair> *save = buckets;
	buckets = result.buckets;
	result.buckets = save;
}

#endif // !_HASHMAP_
