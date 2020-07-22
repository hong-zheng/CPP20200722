#include "RBTree.h"
#include "RBTree2.hpp"
#include <iostream>
using namespace std;
// ������ĵ�����
// ͨ����װ�����ʵ�ֵ���������
template<class V>
struct RBTIterator{
public:
	RBTIterator(Node* node)
		:_node(node){}

	//*,->,!=,==,++
	V& operator*(){
		return _node->_value;
	}

	V* operator->(){
		return &_node->_value;
	}

	bool operator!=(const Self& it){
		return _node != it._node;
	}

	bool operator==(const Self& it){
		return _node == it._node;
	}


	//�ص�:�������
	// _node ָ��ĵ�ǰ�������������䵱ǰ��㶼�Ѿ��������

	Self& operator++(){
		if (_node->_right){
			// ������������ڣ���һ��λ�ã���������������
			_node = _node->_right;
			while (_node->_left)
				_node = _node->_left;
		}
		else{
			//���û������������Ҫ���ϻ���
			Node* parent = _node->parent;
			while (_node == parent->_right){
				_node = parent;
				parent = parent->_parent;
			}
			// ��һ����Ҫ���ʵĽ��λ��
			_node = parent;

			if (_node->_right != parent)
				_node = parent;
		}

		return *this;
	}

private:
	typedef RBNode<V> Node;
	typedef RBTIterator<V> Self;

	Node* _node;
};

template<class K,class V>
class Map{
	struct MapKeyOfValue{
		const K& operator()(const pair<K,V>& value){
			//return ;
			return value.first;
		}
	};
public:
	bool insert(const pair<K, V>& value){
		return _rbt.insert(value).second ;
	}


private:
	RBTree<K, pair<K, V>, MapKeyOfValue> _rbt;
};
//
//
//template<class K>
//class Set{
//
//public:
//	bool insert(const K& key){
//		_rbt.insert(key);
//	}
//private:
//	RBTree<K, V> _rbt;
//};
void testMap(){


	Map<int, int> m;
	m.insert(make_pair(102, 2));
	m.insert(make_pair(12, 2));
	m.insert(make_pair(125, 2));
	m.insert(make_pair(132, 2));
	m.insert(make_pair(132, 2));
	m.insert(make_pair(2, 2));
	m.insert(make_pair(1, 2));
}


int main(){


	system("pause");
	return 0;
}

// KeyOfValue����ȡV����Ӧ��Kֵ
// �º���

struct KeyOfValue{

};
