#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <vector>
#include <string>
using namespace std;

template<class K>
struct KeyOfValue{
	const K& operator()(const K& key){
		return key;
	}
};
// ��ɢ�У�ָ������+������Ҳ�й�ϣͰ
template<class V>
struct HashNode{

	V _value;
	HashNode<V>* _next;

	HashNode(const V& val)
	:_value(val)
	, _next(nullptr)
	{}
};


//ǰ����������໥��������
// ����Ҫ֪���ṹ��ʲô
template<class K, class V, class  KeyOfValue>
class  HashTable;
// ��ϣ��ĵ�����
template<class K, class V, class KeyOfValue>
struct HashIterator{
	typedef HashNode<V> Node;
	typedef HashIterator<K, V, KeyOfValue> Self;

	// ǰ������
	//ͨ��ָ����ʹ�ϣ��

	// �ڹ�ϣ����Ҫ�õ����� ���໥���ý������
	typedef HashTable<K, V, KeyOfValue> HT;

	Node* _node;
	HT* _ht;
	// �ڹ�ϣ������Ҫ�õ��������໥���ý������
	// �ڴ˴���Ҫ�ù�ϣ��
	HashIterator(Node* node, HT* ht)
		: _node(node)
		, _ht(ht)
	{}

	V& operator*(){
		return _node->_value;
	}

	V* operator->(){
		return &_node->_value;
	}

	bool operator != (const Self& it){
		return _node != it._node;
	}


	Self& operator++(){
		if (_node->_next){
			_node = _node->_next;
		}
		else{
			//�ҵ���һ���ǿ������ͷ���
			// 1����λ��ǰ����ڹ�ϣ���е�λ��

			KeyOfValue kov;

			int idx = kov(_node->_value) % _ht->_table.size();

			//2���ӱ�����һ��λ�ò��ҵ�һ���ǿ������ͷ���
			++idx;
			Node* cur = _ht->_table[idx];

			for (; idx < _ht->_table.size(); ++idx){
				// ֻҪ�ǿվ͸���Ϊͷ���
				if (_ht->_table[idx]){
					_node = _ht->_table[idx];
					break;
				}
			}

			// ���������������ˣ�û��Ԫ��
			// 3���ж��Ƿ��ҵ�һ���ǿ�ͷ���
			if (idx == _ht->_table.size())
				_node = nullptr;
		}
		return *this;
	}
};


// �ַ�ת��Ϊ����
struct strToInt{
	size_t operator()(const string& str){
		size_t hash = 0;

		for (const auto& ch : str){
			hash = hash * 131 + ch;
		}
		return hash;
	}
};

template<class K>
//ͨ�õ�ת������
struct hashFun{
	size_t operator()(const K& key){
		return key;
	}
};

//��װ�˹�ϣ��
template<class K, class V>
class UnorderedMap{
	struct MapKeyOfValue
	{
		const K& operator()(const pair<K, V>& value){
			return value.first;
		}
	};

public:
	bool insert(const pair<K, V>& value){
		return _ht.insert(value);
	}
private:
	HashTable<K, pair<K, V>, MapKeyOfValue> _ht;
};

template<class K>
class UnorderedSet{
	struct SetKeyOfValue{
		const K& operator()(const K& value){
			return value;
		}
	};
public:

	typedef typename HashTable<K, K, SetKeyOfValue>::iterator iterator;

	iterator begin(){
		return _ht.begin();
	}

	iterator end(){
		return _ht.end();
	}

	bool insert(const K& value){
		return _ht.insert(value);
	}

private:
	HashTable<K, K, SetKeyOfValue> _ht;
};



template<class K,class V,class  KeyOfValue>
class  HashTable{
public:
	typedef HashNode<V> Node; 

	// ������������Ϊ��ϣ�����Ԫ�࣬���Է��ʹ�ϣ���˽�г�Ա
	template<class K, class V, class KeyOfValue>
	friend struct HashIterator;

	// ������
	typedef HashIterator < K, V, KeyOfValue> iterator ;

	iterator begin(){
		//��һ���ǿ������ͷ���
		for (int i = 0; i < _table.size(); ++i){
			Node* cur = _table[i];
			if (cur)
				return iterator(cur, this);
		}
		return iterator(nullptr, this);
	}

	iterator end(){
		return iterator(nullptr, this);
	}
	// ��ɢ�еĲ������
	bool insert(const V& value){
		checkCapacity();

		// 1������λ��
		KeyOfValue kov;
		// string���Ͳ�֧��ȡģ���㣬����ֵ����ת��Ϊ��ֵ
		// ����ֵ����ת��Ϊ��ֵ����
		int idx = kov(value) % _table.size();

		// 2������keyֵ�Ƿ����

		Node* cur = _table[idx];
		while (cur){
			if (kov(value) == kov(cur->_value))
				return false;
			cur = cur->_next;
		}

		// 3�����룬ͷ��
		// �������
		cur = new Node(value);
		// ����ͷ���
		cur->_next = _table[idx];
		// ����ͷ���
		_table[idx] = cur;
		++_size;

		return true;
	}

	// ���ݵ�ʱ����Ҫ��ԭ�����е�ָ��ָ��nullptr
	// ���ݣ�
	//  �����ɱ��е�ÿһ��Ԫ��
	//  ����ÿһ��Ԫ�����±��е�λ��
	//	��Ԫ�����¹��ص��±��Ӧ��λ��
	void checkCapacity(){
		if (_size == _table.size()){
			size_t newSize = _size == 0 ? 5:2*_size ;
			vector<Node*> newHt; // �±��еľ͸�����Ĭ��ֵ
			// ������Ҫʹ��[]�����ԲŻ�resize�ռ�
			newHt.resize(newSize); // resize�͸������µ�ֵ

			KeyOfValue kov;
			// �����ɱ��еķǿյ�����
			for (int i = 0; i < _table.size(); ++i){
				Node* cur = _table[i];
				// ������ǰ������
				while (cur){
					// 0����¼�ɱ��е���һ��Ԫ��
					Node* next = cur->_next;

					//1�������µ�λ��
					int idx = kov(cur->_value) % newHt.size();

					// 2��ͷ��
					cur->_next = newHt[idx];
					newHt[idx] = cur;

					// 3�������¼����һ��Ԫ��
					cur = next;
				}
				// ԭ���е�ָ��ı䣬��������ָ��ָ���±�
				_table[i] = nullptr;
			}
			// ǳ����������ָ��
			_table.swap(newHt);
			//���֮��ͻ���������������ͷ�ԭ�пռ�
		}
	}

	// ������Ҫ�ڲ���֮�����
	Node* find(const K& key){
		if (_table.size() == 0) return nullptr;
		//KeyOfValue kov;
		// ����key�����ң�����λ��
		// ��key���ҾͲ���kov
		int idx = key % _table.size();
		
		//һ�㵥�����в����̫��Ԫ�أ�����ή��������

		Node* cur = _table[idx];
		KeyOfValue kov;

		while (cur){
			if (kov(cur->_value) == key){
				return cur;
			}
			cur = cur->_next;
		}
		return nullptr;
	}

	//bool erase(const K& key){
	//	int idx = key%_table.size();

	//	KeyOfValue kov;
	//	Node* cur = _table[idx];
	//	Node* prev = nullptr;
	//	//�������ɾ����û�������ĸ����߼�
	//	while (cur){
	//		prev = cur;
	//		if (kov(cur->_value) == key){
	//			break;
	//		}
	//		cur = cur->_next;
	//	}
	//	if (!prev) return false;
	//	else{
	//		prev->_next = cur->_next;
	//	}
	//	return true;
	//}

	bool erase(const K& key){
		int idx = key%_table.size();

		Node* cur = _table[idx];
		//������ɾ���߼�
		Node* prev = nullptr;

		KeyOfValue kov;
		while (cur){
			// �ҵ�����
			if (kov(cur->_value) == key){
				// ɾ��
				// �ж�ɾ�����Ƿ�Ϊͷ���
				if (prev == nullptr){
					_table[idx] = cur->_next;
				}
				else{
					prev->_next = cur->_next;
				}

				delete cur;
				--_size;
				return true;
			}
			else{//��������
				prev = cur;
				cur = cur->_next;
			}
		}
		// ��������������ɣ�û���ҵ������Է���false
		return false;
	}
	
private:
	vector<Node*> _table;
	size_t _size = 0;//��ɢ����Ԫ�صĸ���
};


void test1(){
	HashTable<int, int, KeyOfValue<int>> ht;


	ht.insert(3);
	ht.insert(23);
	ht.insert(32);
	ht.insert(13);
	ht.insert(30);

	HashNode<int>* cur = ht.find(3);
	cout << cur->_value << endl;
	cur = ht.find(100);
	if (!cur) cout << "100������-->" <<cur<< endl;

	bool iserase = ht.erase(3);
	cout << iserase << endl;
	cur = ht.find(3);
	cout << cur << endl;
}
