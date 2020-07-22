#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct strToInt1{
	size_t operator()(const string& s){
		size_t hash = 0;
		for (auto& ch : s){
			hash = hash * 131 + ch;
		}
		return hash;
	}
};

struct strToInt2{
	size_t operator()(const string& s){
		size_t hash = 0;
		for (auto& ch : s){
			hash = hash * 65599 + ch;
		}
		return hash;
	}
};

struct strToInt3{
	size_t operator()(const string& s){
		size_t hash = 0;
		int magic = 63689;
		for (auto& ch : s){
			hash = hash * magic + ch;
			magic *= 378551;
		}
		return hash;
	}
};

class BitMap{
public:
	BitMap(size_t range){
		_bit.resize(range / 32 + 1);//至少：0+1
		// 小于32的时候就放在第一个整数中存放
	}

	//查询：Test
	bool Test(size_t n){
		// 整数位置
		int idx = n / 32;

		int bitIdx = n % 32;
		//对应的bit位二进制值

		if ((_bit[idx] >> bitIdx) & 1){
			return true;
		}
		else{
			return false;
		}
	}
	//存储:Set
	void Set(size_t n){
		int idx = n / 32;
		int bitIdx = n % 32;

		_bit[idx] |= (1 << bitIdx);
	}

	//删除：Reset
	// 恢复成零值
	void Reset(size_t n){
		int idx = n / 32;
		int bitIdx = n % 32;

		_bit[idx] &= ~(1 << bitIdx);
		// (1 << bitIdx) ：将1移到需删除的位置
		// ~：将所有的值按位取反
		// 最后进行&操作，其他位的值不改变，当前值无论如何都为0
	}

private:
	vector<int> _bit;
};

// 3个哈希函数
// 布隆过滤器
//概率式容器：不能删除操作
template<class T,class HF1,class HF2,class HF3>
class BloomFilter{
public:
	// bit位数量 = 哈希函数个数*数据量/ln2
	// ln2 --> 0.7
	// 3个哈希函数：大概开空间为：3/0.7*数据量，因此暂时开5倍数据量
	BloomFilter(size_t num)
		:_bit(5*num)
		, _bitCount(5*num)
	{}

	// Set
	void Set(const T& value){
		HF1 hf1;
		HF2 hf2;
		HF3 hf3;
		//计算哈希值
		size_t hashCode1 = hf1(value);
		size_t hashCode2 = hf2(value);
		size_t hashCode3 = hf3(value);

		_bit.Set(hashCode1 / _bitCount);
		_bit.Set(hashCode2 / _bitCount);
		_bit.Set(hashCode3 / _bitCount);
	}

	void Test(const T& value){
		HF1 hf1;
		size_t hashCode1 = hf1(value);
		if (!_bit.Test(hashCode1%_bitCount)){
			return false;
		}
		HF2 hf2;
		size_t hashCode2 = hf2(value);
		if (!_bit.Test(hashCode2%_bitCount)){
			return false;
		}
		HF3 hf3;
		size_t hashCode3 = hf3(value);
		if (!_bit.Test(hashCode3%_bitCount)){
			return false;
		}
		// 全部都为1，很大概率上是存在的
		//返回true：不一定正确
		return false;
	}
private:
	BitMap _bit;
	size_t _bitCount;
}; 

void test(){
	BloomFilter<string, strToInt1, strToInt2, strToInt3> bf(300);


}
struct s{
	int a;
	int b;
	char* c;
};

struct sc{
	int a;
	int b;
	char c[];
}; 
void teset(){
	// 申请内存方式

	// 两次申请，内存并不一定连续
	// 释放内存需要释放两次
	struct s* t0 = (struct s*)malloc(sizeof(struct s));
	t0->c = (char*)malloc(sizeof(char) * 16);


	// 此处释放内存只需要释放一次
	//内存申请只需要一次，地址连续
	struct sc* t1 = (struct sc*)malloc(sizeof(struct sc) + sizeof(char) * 16);

	cout << "t0" << sizeof t0 << endl;
	cout << "t1" << sizeof t1 << endl;
	t1->c;//访问方式和普通成员访问方式一致
	cout << sizeof(struct s) << endl; // 12
	cout << sizeof(struct sc) << endl; // 8
	int a = 1;
	cout << sizeof a << endl;

	// 两种不同的方式导致数据拷贝的方式也不一致
	//前者需要拷贝两端，分别拷贝
	// 而后者只需要拷贝一段，直接一次拷贝,由于柔性数组的内存，它的数据内同和结构体成员的地址是连续的，因此可以直接拷贝
	
	// 减少内存碎片
	// 由于结构体的柔性数组和结构体成员的地址是连续的，即可一同申请内存，因此更大程度地避免了内存碎片，另外
	// 由于该成员本身不占结构体空间，因此，整体而言，比普通的数组郑源栈空间会稍微小点

	// 零长数组实现同样的功能
	// 但是不是C99标准，因此考虑到可移植问题，因此不建议使用

	//总结：
	// 柔性数组的使用：
	// 位于结构体的最后一个位置
	// 不完整数组类型
	// 不是唯一成员
}

struct dd{
	char a;
	char b;
};

void teseet(){
	cout << sizeof(struct dd) << endl;
}
int main(){
	test();

	system("pause");
	return 0;
}
