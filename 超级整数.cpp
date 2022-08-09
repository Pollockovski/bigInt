#include"basicFuncBigInt.h"
#include<time.h>

void main()
{
	bigInt a, b, c, d;
	string str1,str2;
	time_t begin_t, finish_t;
	while (true) {
		cin >> str1;
		cin >> str2;
		a.fromBinary(str1);
		b.fromBinary(str2);
		begin_t = clock();
		c = a % b;
		finish_t = clock();
		cout << "a=";
		a.outputBinary();
		cout << "b=";
		b.outputBinary();
		cout << "a%b=";
		c.outputBinary();
		cout << "乘数位数之和：" << a.value.size() - 2 + b.value.size() << "积的位数：" << c.value.size() - 1 << endl;
		cout << "a的位数" << a.value.size() - 1 << ",b的位数" << b.value.size() - 1 << endl;
		cout << "所用时间：" << (double)(finish_t - begin_t) / CLOCKS_PER_SEC << "s" << endl;
	}
}