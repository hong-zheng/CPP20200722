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
// 开散列：指针数组+单链表，也叫哈希桶
template<class V>
struct HashNode{

	V _value;
	HashNode<V>* _next;

	HashNode(const V& val)
	:_value(val)
	, _next(nullptr)
	{}
};


//前置声明解决相互引用问题
// 必须要知道结构是什么
template<class K, class V, class  KeyOfValue>
class  HashTable;
// 哈希表的迭代器
template<class K, class V, class KeyOfValue>
struct HashIterator{
	typedef HashNode<V> Node;
	typedef HashIterator<K, V, KeyOfValue> Self;

	// 前置声明
	//通过指针访问哈希表

	// 在哈希表中要用迭代器 ：相互引用解决问题
	typedef HashTable<K, V, KeyOfValue> HT;

	Node* _node;
	HT* _ht;
	// 在哈希表中需要用迭代器：相互引用解决问题
	// 在此处需要用哈希表
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
			//找到下一个非空链表的头结点
			// 1、定位当前结点在哈希表中的位置

			KeyOfValue kov;

			int idx = kov(_node->_value) % _ht->_table.size();

			//2、从表中下一个位置查找第一个非空链表的头结点
			++idx;
			Node* cur = _ht->_table[idx];

			for (; idx < _ht->_table.size(); ++idx){
				// 只要非空就更新为头结点
				if (_ht->_table[idx]){
					_node = _ht->_table[idx];
					break;
				}
			}

			// 将整个表都遍历完了，没有元素
			// 3、判断是否找到一个非空头结点
			if (idx == _ht->_table.size())
				_node = nullptr;
		}
		return *this;
	}
};


// 字符转换为整数
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
//通用的转换函数
struct hashFun{
	size_t operator()(const K& key){
		return key;
	}
};

//封装了哈希表
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

	// 将迭代器声明为哈希表的友元类，可以访问哈希表的私有成员
	template<class K, class V, class KeyOfValue>
	friend struct HashIterator;

	// 迭代器
	typedef HashIterator < K, V, KeyOfValue> iterator ;

	iterator begin(){
		//第一个非空链表的头结点
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
	// 开散列的插入操作
	bool insert(const V& value){
		checkCapacity();

		// 1、计算位置
		KeyOfValue kov;
		// string类型不支持取模运算，非数值类型转换为数值
		// 非数值类型转换为数值类型
		int idx = kov(value) % _table.size();

		// 2、搜索key值是否存在

		Node* cur = _table[idx];
		while (cur){
			if (kov(value) == kov(cur->_value))
				return false;
			cur = cur->_next;
		}

		// 3、插入，头插
		// 创建结点
		cur = new Node(value);
		// 连接头结点
		cur->_next = _table[idx];
		// 更新头结点
		_table[idx] = cur;
		++_size;

		return true;
	}

	// 扩容的时候需要将原数组中的指向指向nullptr
	// 增容：
	//  遍历旧表中的每一个元素
	//  计算每一个元素在新表中的位置
	//	把元素重新挂载到新表对应的位置
	void checkCapacity(){
		if (_size == _table.size()){
			size_t newSize = _size == 0 ? 5:2*_size ;
			vector<Node*> newHt; // 新表中的就给出了默认值
			// 由于需要使用[]，所以才会resize空间
			newHt.resize(newSize); // resize就给出了新的值

			KeyOfValue kov;
			// 遍历旧表中的非空单链表
			for (int i = 0; i < _table.size(); ++i){
				Node* cur = _table[i];
				// 遍历当前单链表
				while (cur){
					// 0、记录旧表中的下一个元素
					Node* next = cur->_next;

					//1、计算新的位置
					int idx = kov(cur->_value) % newHt.size();

					// 2、头插
					cur->_next = newHt[idx];
					newHt[idx] = cur;

					// 3、处理记录的下一个元素
					cur = next;
				}
				// 原表中的指向改变，否则两个指针指向新表
				_table[i] = nullptr;
			}
			// 浅拷贝，交换指针
			_table.swap(newHt);
			//完成之后就会调用析构函数，释放原有空间
		}
	}

	// 查找需要在插入之后才行
	Node* find(const K& key){
		if (_table.size() == 0) return nullptr;
		//KeyOfValue kov;
		// 按照key来查找，计算位置
		// 用key查找就不用kov
		int idx = key % _table.size();
		
		//一般单链表中不会放太多元素，否则会降低其性能

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
	//	//单链表的删除，没有其他的复杂逻辑
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
		//单链表删除逻辑
		Node* prev = nullptr;

		KeyOfValue kov;
		while (cur){
			// 找到数据
			if (kov(cur->_value) == key){
				// 删除
				// 判断删除的是否为头结点
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
			else{//遍历链表
				prev = cur;
				cur = cur->_next;
			}
		}
		// 整个链表都遍历完成，没有找到，所以返回false
		return false;
	}
	
private:
	vector<Node*> _table;
	size_t _size = 0;//开散列中元素的个数
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
	if (!cur) cout << "100不存在-->" <<cur<< endl;

	bool iserase = ht.erase(3);
	cout << iserase << endl;
	cur = ht.find(3);
	cout << cur << endl;
}
