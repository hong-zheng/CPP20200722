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
		_bit.resize(range / 32 + 1);//���٣�0+1
		// С��32��ʱ��ͷ��ڵ�һ�������д��
	}

	//��ѯ��Test
	bool Test(size_t n){
		// ����λ��
		int idx = n / 32;

		int bitIdx = n % 32;
		//��Ӧ��bitλ������ֵ

		if ((_bit[idx] >> bitIdx) & 1){
			return true;
		}
		else{
			return false;
		}
	}
	//�洢:Set
	void Set(size_t n){
		int idx = n / 32;
		int bitIdx = n % 32;

		_bit[idx] |= (1 << bitIdx);
	}

	//ɾ����Reset
	// �ָ�����ֵ
	void Reset(size_t n){
		int idx = n / 32;
		int bitIdx = n % 32;

		_bit[idx] &= ~(1 << bitIdx);
		// (1 << bitIdx) ����1�Ƶ���ɾ����λ��
		// ~�������е�ֵ��λȡ��
		// ������&����������λ��ֵ���ı䣬��ǰֵ������ζ�Ϊ0
	}

private:
	vector<int> _bit;
};

// 3����ϣ����
// ��¡������
//����ʽ����������ɾ������
template<class T,class HF1,class HF2,class HF3>
class BloomFilter{
public:
	// bitλ���� = ��ϣ��������*������/ln2
	// ln2 --> 0.7
	// 3����ϣ��������ſ��ռ�Ϊ��3/0.7*�������������ʱ��5��������
	BloomFilter(size_t num)
		:_bit(5*num)
		, _bitCount(5*num)
	{}

	// Set
	void Set(const T& value){
		HF1 hf1;
		HF2 hf2;
		HF3 hf3;
		//�����ϣֵ
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
		// ȫ����Ϊ1���ܴ�������Ǵ��ڵ�
		//����true����һ����ȷ
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
	// �����ڴ淽ʽ

	// �������룬�ڴ沢��һ������
	// �ͷ��ڴ���Ҫ�ͷ�����
	struct s* t0 = (struct s*)malloc(sizeof(struct s));
	t0->c = (char*)malloc(sizeof(char) * 16);


	// �˴��ͷ��ڴ�ֻ��Ҫ�ͷ�һ��
	//�ڴ�����ֻ��Ҫһ�Σ���ַ����
	struct sc* t1 = (struct sc*)malloc(sizeof(struct sc) + sizeof(char) * 16);

	cout << "t0" << sizeof t0 << endl;
	cout << "t1" << sizeof t1 << endl;
	t1->c;//���ʷ�ʽ����ͨ��Ա���ʷ�ʽһ��
	cout << sizeof(struct s) << endl; // 12
	cout << sizeof(struct sc) << endl; // 8
	int a = 1;
	cout << sizeof a << endl;

	// ���ֲ�ͬ�ķ�ʽ�������ݿ����ķ�ʽҲ��һ��
	//ǰ����Ҫ�������ˣ��ֱ𿽱�
	// ������ֻ��Ҫ����һ�Σ�ֱ��һ�ο���,��������������ڴ棬����������ͬ�ͽṹ���Ա�ĵ�ַ�������ģ���˿���ֱ�ӿ���
	
	// �����ڴ���Ƭ
	// ���ڽṹ�����������ͽṹ���Ա�ĵ�ַ�������ģ�����һͬ�����ڴ棬��˸���̶ȵر������ڴ���Ƭ������
	// ���ڸó�Ա����ռ�ṹ��ռ䣬��ˣ�������ԣ�����ͨ������֣Դջ�ռ����΢С��

	// �㳤����ʵ��ͬ���Ĺ���
	// ���ǲ���C99��׼����˿��ǵ�����ֲ���⣬��˲�����ʹ��

	//�ܽ᣺
	// ���������ʹ�ã�
	// λ�ڽṹ������һ��λ��
	// ��������������
	// ����Ψһ��Ա
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
