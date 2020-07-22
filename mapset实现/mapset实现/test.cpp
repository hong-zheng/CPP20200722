#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
//#include <stl_tree.h>
using namespace std;



//bool isRBTree(){
//	Node* root = _header->_parent;
//	if (root == nullptr) return true;
//	//根是否为黑色
//	if (root->_color != BLACK){
//		return false;
//	}
//
//	// 2、每条路径黑色是否相同，3、红色是否连续
//	//获取某一条路径上的黑色个数，作为基准值
//	int blackCount = 0;
//	Node * cur = root;
//	while (cur){
//		if (cur->_color == BLACK){
//			++blackCount;
//		}
//		cur = cur->_left;
//	}
//
//	// 遍历
//	int curCount = 0;
//	return _isRBTree(cur, blackCount, curCount);
//}
//
//bool _isRBTree(Node* root, int blackCount, int curCount){
//	// 当前路径上黑色个数是否相同
//	if (root == nullptr){
//		if (blackCount != curCount)
//			return false;
//		return true;
//	}
//
//	//如果当前结点为褐色，累加
//	if (root->_color == BLACK){
//		++curCount;
//	}
//
//	Node* parent = root->_parent;
//	if (parent && parent->_color == RED && root->_color == RED){
//		return false; //有红色连续的结点/返回false
//	}
//	// 保证子树是红黑树
//	return _isRBTree(root->_left,blackCount,curCount)
//		&& _isRBTree(root->_right, blackCount, curCount);
//}