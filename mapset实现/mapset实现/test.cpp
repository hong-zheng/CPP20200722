#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
//#include <stl_tree.h>
using namespace std;



//bool isRBTree(){
//	Node* root = _header->_parent;
//	if (root == nullptr) return true;
//	//���Ƿ�Ϊ��ɫ
//	if (root->_color != BLACK){
//		return false;
//	}
//
//	// 2��ÿ��·����ɫ�Ƿ���ͬ��3����ɫ�Ƿ�����
//	//��ȡĳһ��·���ϵĺ�ɫ��������Ϊ��׼ֵ
//	int blackCount = 0;
//	Node * cur = root;
//	while (cur){
//		if (cur->_color == BLACK){
//			++blackCount;
//		}
//		cur = cur->_left;
//	}
//
//	// ����
//	int curCount = 0;
//	return _isRBTree(cur, blackCount, curCount);
//}
//
//bool _isRBTree(Node* root, int blackCount, int curCount){
//	// ��ǰ·���Ϻ�ɫ�����Ƿ���ͬ
//	if (root == nullptr){
//		if (blackCount != curCount)
//			return false;
//		return true;
//	}
//
//	//�����ǰ���Ϊ��ɫ���ۼ�
//	if (root->_color == BLACK){
//		++curCount;
//	}
//
//	Node* parent = root->_parent;
//	if (parent && parent->_color == RED && root->_color == RED){
//		return false; //�к�ɫ�����Ľ��/����false
//	}
//	// ��֤�����Ǻ����
//	return _isRBTree(root->_left,blackCount,curCount)
//		&& _isRBTree(root->_right, blackCount, curCount);
//}