
#include "RBTree.hpp"

template <class K, class V>
class Map
{
	struct MapKeyOfValue
	{
		const K& operator()(const pair<K, V>& value)
		{
			return value.first;
		}
	};
public:
	typedef typename RBTree<K, pair<K, V>, MapKeyOfValue>::iterator iterator;

	iterator begin()
	{
		return _rbt.begin();
	}

	iterator end()
	{
		return _rbt.end();
	}

	pair<iterator, bool> insert(const pair<K, V>& value)
	{
		return _rbt.insert(value);
	}

	V& operator[](const K& key)
	{
		pair<iterator, bool> ret = _rbt.insert(make_pair(key, V()));
		return ret.first->second;
	}
private:
	RBTree<K, pair<K, V>, MapKeyOfValue> _rbt;
};

template <class K>
class Set
{
	struct SetKeyOfValue
	{
		const K& operator()(const K& key)
		{
			return key;
		}
	};
public:
	typedef typename RBTree<K, K, SetKeyOfValue>::iterator iterator;
	pair<iterator, bool> insert(const K& key)
	{
		return _rbt.insert(key);
	}
private:
	RBTree<K, K, SetKeyOfValue> _rbt;
};


void testMap()
{
	Map<int, int> m;
	m.insert(make_pair(1, 1));
	/*m.insert(make_pair(10, 10));
	m.insert(make_pair(8, 8));
	m.insert(make_pair(2, 2));
	m.insert(make_pair(7, 7));*/
	m[10] = 10;
	m[8] = 8;
	m[2] = 2;
	m[7] = 7;
	m[1] = 10000;

	Map<int, int>::iterator it = m.begin();
	while (it != m.end())
	{
		cout << it->first << "--->" << it->second << endl;
		++it;
	}
}

void testSet()
{
	Set<int> s;
	s.insert(10);
	s.insert(2);
	s.insert(0);
	s.insert(7);
}

int main()
{
	testMap();
	//testSet();
	return 0;
}