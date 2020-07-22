#include "RBTree.h"
#include "RBTree2.hpp"
#include <iostream>
using namespace std;
// 红黑树的迭代器
// 通过封装结点来实现迭代器操作
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


	//重点:中序遍历
	// _node 指向的当前结点的左子树及其当前结点都已经访问完成

	Self& operator++(){
		if (_node->_right){
			// 如果右子树存在，下一个位置：右子树的最左结点
			_node = _node->_right;
			while (_node->_left)
				_node = _node->_left;
		}
		else{
			//如果没有右子树，需要向上回溯
			Node* parent = _node->parent;
			while (_node == parent->_right){
				_node = parent;
				parent = parent->_parent;
			}
			// 下一步需要访问的结点位置
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

// KeyOfValue：获取V所对应的K值
// 仿函数

struct KeyOfValue{

};
