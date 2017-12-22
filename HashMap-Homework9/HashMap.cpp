#ifndef __HASHMAP__
#define __HASHMAP__

#include <vector>

template <class KeyType>
using HashFunction = unsigned int(*)(const KeyType&, unsigned int);

template <class KeyType, class ValueType>
class HashMap
{
public:
	HashMap(unsigned _n, HashFunction<KeyType> _h);
	~HashMap();
	HashMap(const HashMap<KeyType, ValueType>&);
	HashMap<KeyType, ValueType>& operator = (const HashMap<KeyType, ValueType> &);

	ValueType& operator [] (const KeyType&);
	const ValueType& operator [] (const KeyType&) const;

	bool hasKey(const KeyType &) const;

	bool operator == (const HashMap<KeyType, ValueType>&) const;
	bool operator != (const HashMap<KeyType, ValueType>&) const;

	void resize(unsigned int);

	double efficiency() const;
	void print(std::ostream&) const;
	int sumAllValues() const;
	int countOfValuesBiggerThanZero() const;
	KeyType findKeyToBiggestValue() const;
	HashMap<KeyType, std::pair<ValueType, ValueType>> operator * (const HashMap<KeyType, ValueType>& other) const;
	HashMap<KeyType, ValueType> operator + (const HashMap<KeyType, ValueType>& other) const;
	void map(void(*) (ValueType&));
	void mapKeys(KeyType(*f)(const KeyType&));
	//friend std::ostream& operator<< (std::ostream&, HashMap<KeyType, ValueType>&);
private:

	struct kvpair
	{
		kvpair(KeyType _k, ValueType _v) :key(_k), value(_v) {}
		KeyType key;
		ValueType value;
	};

	int locate(const KeyType&, unsigned int) const;

	unsigned int size, count;
	HashFunction<KeyType> h;
	std::vector<std::vector<kvpair>> *buckets;
};

template <class KeyType, class ValueType>
HashMap<KeyType, ValueType>
::HashMap(unsigned _n,
	HashFunction<KeyType> _h) :size(_n), h(_h)
{
	count = 0;
	buckets = new std::vector<std::vector<kvpair>>;
	std::vector<kvpair> emptyBucket;
	buckets->assign(size, emptyBucket);
}

template <class KeyType, class ValueType>
HashMap<KeyType, ValueType>::~HashMap()
{
	delete buckets;
}
template <class KeyType, class ValueType>
HashMap<KeyType, ValueType>::HashMap(const HashMap<KeyType, ValueType> &other)
{
	size = other.size;
	count = other.count;
	buckets = new std::vector<std::vector<kvpair>>;
	*buckets = *other.buckets;
}

template <class KeyType, class ValueType>
HashMap<KeyType, ValueType>&
HashMap<KeyType, ValueType>::operator =
(const HashMap<KeyType, ValueType> &other)
{
	if (this != &other)
	{
		delete buckets;
		buckets = new std::vector<std::vector<kvpair>>;
		*buckets = *other.buckets;
		size = other.size;
		count = other.count;
	}
	return *this;
}

template <class KeyType, class ValueType>
int HashMap<KeyType, ValueType>::locate(const KeyType& key, unsigned int ix) const
{
	for (int i = 0; i < (*buckets)[ix].size(); i++)
	{
		if ((*buckets)[ix][i].key == key)
		{
			return i;
		}
	}
	return -1;
}


template <class KeyType, class ValueType>
ValueType& HashMap<KeyType, ValueType>::operator [] (const KeyType &key)
{
	unsigned int ix = h(key, size);// % size;
	assert(ix < size);

	unsigned int n = locate(key, ix);

	if (n == -1)
	{
		(*buckets)[ix].push_back(kvpair(key, ValueType()));
		n = (*buckets)[ix].size() - 1;
		count++;
	}

	return (*buckets)[ix][n].value;

}

template <class KeyType, class ValueType>
const ValueType& HashMap<KeyType, ValueType>::operator [] (const KeyType &key) const
{
	unsigned int ix = h(key, size);// % size;
	assert(ix < size);

	unsigned int n = locate(key, ix);
	assert(n >= 0);

	return (*buckets)[ix][n].value;

}

template <class KeyType, class ValueType>
bool HashMap<KeyType, ValueType>::operator == (const HashMap<KeyType, ValueType> &other) const
{

	for (int ibucket = 0; ibucket < buckets->size(); ibucket++)
	{
		const std::vector<kvpair> &bucket = (*buckets)[ibucket];
		for (int el = 0; el < bucket.size(); el++)
		{
			const KeyType &key = bucket[el].key;
			const ValueType & value = bucket[el].value;
			if (other.hasKey(key) && other[key] != value)
			{
				return false;
			}
		}
	}

	return count == other.count;
}

template <class KeyType, class ValueType>
bool HashMap<KeyType, ValueType>::hasKey(const KeyType &key) const
{
	unsigned ix = h(key, size);
	return locate(key, ix) >= 0;
}

template <class KeyType, class ValueType>
bool HashMap<KeyType, ValueType>::operator != (const HashMap<KeyType, ValueType> &other) const
{
	return !(*this == other);
}

template <class KeyType, class ValueType>
void HashMap<KeyType, ValueType>::resize(unsigned int newSize)
{
	HashMap<KeyType, ValueType> newMap(size, h);

	for (int ibucket = 0; ibucket < buckets->size(); ibucket++)
	{
		const std::vector<kvpair> &bucket = *buckets[ibucket];
		for (int el = 0; el < bucket.size(); el++)
		{
			const KeyType &key = bucket[el].key;
			const ValueType & value = bucket[el].value;
			newMap[key] = value;
		}
	}

	size = newSize;

	std::vector<std::vector<kvpair>> *save = buckets;
	buckets = newMap.buckets;
	newMap.buckets = save;

}

template <class KeyType, class ValueType>
double HashMap<KeyType, ValueType>::efficiency() const {
	int all = count;
	int coliding = all;
	for (int i = 0; i < buckets->size(); i++) {
		if ((*buckets)[i].size() == 1)
			coliding--;
	}
	return (double)(all - coliding) / all;
}

template <class KeyType, class ValueType>
void HashMap<KeyType, ValueType>::print(std::ostream& out) const {
	for (int i = 0; i < buckets->size(); i++) {
		const std::vector<kvpair> &bucket = (*buckets)[i];
		for (int j = 0; j < bucket.size(); j++) {
			const KeyType &key = bucket[j].key;
			const ValueType &value = bucket[j].value;
			out << "m[" << key << "] = " << value << '\n';
		}
	}
}

template <class KeyType, class ValueType>
std::ostream& operator<< (std::ostream& out, HashMap<KeyType, ValueType>& map) {
	map.print(out);
	return out;
}

template <class KeyType, class ValueType>
int HashMap<KeyType, ValueType>::sumAllValues() const {
	int sum = 0;
	for (int i = 0; i < buckets->size(); i++) {
		std::vector<kvpair> &bucket = (*buckets)[i];
		for (int j = 0; j < bucket.size(); j++) {
			sum += bucket[j].value;
		}
	}
	return sum;
}

template <class KeyType, class ValueType>
int HashMap<KeyType, ValueType>::countOfValuesBiggerThanZero() const {
	int count = 0;
	for (int i = 0; i < buckets->size(); i++) {
		std::vector<kvpair> &bucket = (*buckets)[i];
		for (int j = 0; j < bucket.size(); j++) {
			if (bucket[j].value > 0)
				count++;
		}
	}
	return count;
}

template <class KeyType, class ValueType>
KeyType HashMap<KeyType, ValueType>::findKeyToBiggestValue() const {
	ValueType max;
	KeyType maxKey;
	bool flag = false;
	for (int i = 0; i < buckets->size(); i++) {
		std::vector<kvpair> &bucket = (*buckets)[i];
		for (int j = 0; j < bucket.size(); j++){
			if (!flag) {
				max = bucket[j].value;
				maxKey = bucket[j].key;
				flag = true;
			}
			else if (bucket[j].value > max) {
				max = bucket[j].value;
				maxKey = bucket[j].key;
			}
		}
	}
	return maxKey;
}

template <class KeyType, class ValueType>
HashMap<KeyType, std::pair<ValueType, ValueType>> HashMap<KeyType, ValueType>::operator * (const HashMap<KeyType, ValueType>& other) const {
	HashMap<KeyType, std::pair<ValueType, ValueType>> result(other.size, other.h);
	for (int i = 0; i < buckets->size(); i++) {
		std::vector<kvpair> &bucket = (*buckets)[i];
		for (int j = 0; j < bucket.size(); j++) {
			KeyType &key = bucket[j].key;
			if (other.hasKey(key)) {
				result[key] = { bucket[j].value, other[key] };
			}
		}
	}
	return result;
}

std::ostream& operator << (std::ostream& out, std::pair<int, int> p) {
	out << "[" << p.first << ", " << p.second << "]";
	return out;
}

template <class KeyType, class ValueType>
HashMap<KeyType, ValueType> HashMap<KeyType, ValueType>::operator + (const HashMap<KeyType, ValueType>& other) const {
	HashMap<KeyType, ValueType> result(other.size, other.h);
	for (int i = 0; i < buckets->size(); i++) {
		std::vector<kvpair> &bucket = (*buckets)[i];
		for (int j = 0; j < bucket.size(); j++) {
			KeyType &key = bucket[j].key;
			if (!other.hasKey(key)) {
				result[key] = bucket[j].value;
			}
		}
	}
	for (int i = 0; i < other.buckets->size(); i++) {
		std::vector<kvpair> &bucket = (*other.buckets)[i];
		for (int j = 0; j < bucket.size(); j++) {
			KeyType &key = bucket[j].key;
			if (!hasKey(key)) {
				result[key] = bucket[j].value;
			}
		}
	}
	return result;
}

template <class KeyType, class ValueType>
void HashMap<KeyType, ValueType>::map(void(*f) (ValueType&)) {
	for (int i = 0; i < buckets->size(); i++) {
		std::vector<kvpair> &bucket = (*buckets)[i];
		for (int j = 0; j < bucket.size(); j++) {
			f(bucket[j].value);
		}
	}
}

template <class KeyType, class ValueType>
void HashMap<KeyType, ValueType>::mapKeys(KeyType(*f)(const KeyType&)) {
	HashMap<KeyType, ValueType> result(size, h);
	for (int i = 0; i < buckets->size(); i++) {
		std::vector<kvpair> &bucket = (*buckets)[i];
		for (int j = 0; j < bucket.size(); j++) {
			KeyType key = f(bucket[j].key);
			ValueType &value = bucket[j].value;
			bucket.erase(bucket.begin() + j);
			result[key] = value;
		}
	}
	(*this) = result;
}

#endif