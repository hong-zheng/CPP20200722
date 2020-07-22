#include "test.h"


void test(){

	UnorderedSet<int> us;
	us.insert(1);
	us.insert(13);
	us.insert(31);
	us.insert(14);
	us.insert(61);

	UnorderedSet<int>::iterator it = us.begin();

	while (it != us.end()){
		cout << *it << " ";
		++it;
	}
	cout << endl;
}

// 放非数值类型
void test2(){
	UnorderedSet<string> us;
	us.insert("3jflis");
	us.insert("ewe3jflis");
	us.insert("3jfdslis");
	us.insert("3323jflis");
}
int main(){
	test2();
	//test();

	system("pause");
}
//void test2(){
//	UnorderedMap<int, int> um;
//	um.insert(make_pair(2, 2));
//	um.insert(make_pair(4, 2));
//	um.insert(make_pair(3, 2));
//	um.insert(make_pair(12, 2));
//	um.insert(make_pair(12, 2));
//}
//
//
//void find(string& sa, string& sb, vector<string>& ret){
//	for (int i = 0; i<sa.size(); i++){
//		for (int j = 0; j<sb.size(); j++){
//			if (sa[i] == sb[j]){
//				string tmp;
//				int curi = i;
//				for (int k = j; k<sb.size(); k++){
//					if (sa[curi] == sb[k])
//						tmp += sb[k];
//					else{
//						break;
//					}
//					curi++;
//					if (curi == sa.size())
//						break;
//				}
//				if (tmp.size() > 0){
//					ret.reserve(1);
//					ret.push_back(tmp);
//				}
//			}
//		}
//	}
//}
//int main(){
//	string sa; // 短串
//	string sb; // 长串
//	while (cin >> sa >> sb){
//		if ((sa.size() == 0) || (sb.size() == 0)) continue;
//		if (sa.size() > sb.size()){
//			string tmp = sa;
//			sa = sb;
//			sb = tmp;
//		}
//		vector<string> ret;
//		find(sa, sb, ret);
//		int max = 0;
//		int maxj = 0;
//		for (int i = 0; i<ret.size(); ++i){
//			if (ret[i].size() > maxj){
//				maxj = ret[i].size();
//				max = i;
//			}
//		}
//		cout << ret[max].c_str();
//		cout << endl;
//	}
//	cout << endl;
//	return 0;
//}
////int main(){
////
////	system("pause");
////	return 0;
////}