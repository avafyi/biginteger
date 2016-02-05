/*****************************************************************
 * Defines main function containing some BigInt tests
 *****************************************************************/
#include <iostream>
#include <stddef.h>
#include <stdlib.h>
#include "BigInt.h"

using namespace std;

int main(void) {
	int a = 92104;
	int b = 74836;

	cout << (BigInt(a) - BigInt(b)) << endl;
	cout << (BigInt(b) - BigInt(a)) << endl;
	cout << (BigInt(-a) - BigInt(-b)) << endl;
	cout << (BigInt(-b) - BigInt(-a)) << endl;
	cout << (BigInt(a) - BigInt(-b)) << endl;
	cout << (BigInt(b) - BigInt(-a)) << endl;
	cout << (BigInt(-a) - BigInt(b)) << endl;
	cout << (BigInt(-b) - BigInt(a)) << endl;

	cout << +(BigInt(-37)) << endl;
	cout << -(BigInt(-37)) << endl;
	cout << -(BigInt(0));

	cout << endl;

	cout << (BigInt(1) == BigInt(1));

	cout << (BigInt(-3737) == BigInt(-3737)) << endl;
	cout << (BigInt(-3735) == BigInt(-3737)) << endl;
	cout << (BigInt(-3737) != BigInt(-3737)) << endl;
	cout << (BigInt(-3735) != BigInt(-3737)) << endl;

	cout << (BigInt(1) > BigInt(0));
	cout << (BigInt(0) > BigInt(1));
	cout << (BigInt(-1) > BigInt(0));
	cout << (BigInt(1489) > BigInt(1489));
	cout << (BigInt(1489) > BigInt(1488));
	cout << (BigInt(1489) > BigInt(1490)) << endl;
	cout << (BigInt(1212000) > BigInt(-1212121));
	cout << (BigInt(1489) > BigInt(1488));
	cout << (BigInt(1489) > BigInt(1488)) << endl;

	BigInt num1(40963);
	BigInt num2(9999);
	BigInt num3(1);
	BigInt num4 = num2 + num3;
	BigInt num5(1024);
	BigInt num6(1024);
	BigInt num7 = num5 + num6;

	cout << num1 << endl;
	cout << num4 << endl;
	cout << num7 << endl;
	cout << (num2 + num5) << " " << (num2 + num3 + num7) << endl;

	cout << (BigInt(0) + BigInt(0)) << endl;
	cout << (BigInt(0)) << endl << endl;

	BigInt num8(500);
	cout << "num8: " << num8 << endl;
	num8 = num5;
	cout << "num8: " << num8 << endl;
	num8 = BigInt(num5 + num3);
	cout << num8 << endl;
	num8 += num3;
	cout << num8 << endl;
	num8 += num5;
	cout << num8 << endl;

	cout << endl;

	cout << (BigInt(789) * BigInt(789)) << endl;
	cout << (BigInt(-789) * BigInt(-789)) << endl;
	cout << (BigInt(-789) * BigInt(789)) << endl;
	cout << (BigInt(789) * BigInt(-789)) << endl;

	cout << (BigInt(25) * BigInt(25)) << endl;

	cout << (BigInt(25) * BigInt(25)) << endl;

	BigInt m1 = BigInt(789);
	BigInt m2 = BigInt(-789);
	for (int i = 0; i < 10; i++) {
		m1 *= m2;
		cout << m1 << endl;
	}

	cout << endl;

	// compute 1000!
	m1 = BigInt(1);
	for (int i = 2; i <= 1000; i++) {
		m1 *= BigInt(i);
	}

	cout << m1 << endl << endl;

	cout << (BigInt(10000) - BigInt(999)) << endl;

	cout << (BigInt(894) / BigInt(56)) << endl;
	cout << (BigInt(894) % BigInt(56)) << endl << endl;

	cout << (BigInt(56) / BigInt(56)) << endl;
	cout << (BigInt(56) % BigInt(56)) << endl << endl;

	cout << (BigInt(20) / BigInt(56)) << endl;
	cout << (BigInt(20) % BigInt(56)) << endl << endl;

	cout << (BigInt(20) / BigInt(56)) << endl;
	cout << (BigInt(20) % BigInt(56)) << endl << endl;

	BigInt pp1(0);
	cout << pp1;
	pp1++;
	cout << pp1;
	++pp1;
	cout << pp1;
	pp1++;
	cout << pp1;
	++pp1;
	cout << pp1 << endl;
	BigInt pp2 = pp1;
	cout << pp2;
	pp2--;
	cout << pp2;
	--pp2;
	cout << pp2;
	pp2--;
	cout << pp2;
	--pp2;
	cout << pp2 << endl << endl;

	pp1 += 10;
	cout << pp1 << endl;
	pp1 -= 5;
	cout << pp1 << endl;
	pp1 *= 5;
	cout << pp1 << endl;
	pp1 /= 5;
	cout << pp1 << endl;
	pp1 %= 10;
	cout << pp1 << endl << endl;

	cout << 5 + pp1 << endl;
	cout << (2000 / (-pp1)) << endl;
	cout << 100 - pp1 << endl;
	cout << -100 - pp1 << endl;
	cout << 100 % pp1 << endl;
	cout << 5 * pp1 << endl;
	cout << (-pp1) << endl << endl;

	cout << pp1 / 0 << endl << endl;

	int beep = 3;
	cout << pp1 + beep << endl << endl;

	BigInt inf = pp1 / 0;
	BigInt ninf = BigInt(-3) / 0;
	cout << inf << endl;
	cout << -inf << endl;
	cout << ninf << endl;
	cout << -ninf << endl;
	cout << 3 / inf << endl;
	cout << -3 / ninf << endl;
	cout << 3 / -inf << endl << endl;
	
	cout << inf / ninf + 3 << endl;
	cout << (inf + ninf) % 3 << endl;
	cout << ninf - ninf << endl;
	cout << 0 * inf << endl;
	cout << ninf * 0 << endl;
	cout << 3 % ninf << endl;
	cout << inf % ninf << endl;
	cout << inf / 3 << endl;
	cout << ninf / 3 << endl;
	cout << inf / -3 << endl;
	cout << ninf / -3 << endl;
	cout << ninf / 0 / 0 / 0 / 0 / 0 << endl;
	cout << 0 / inf << endl;
	cout << inf % 3 << endl;
	cout << inf % 0 << endl;
	cout << BigInt(0) % 0 << endl;

	cout << endl;

	cout << inf * ninf << endl;
	cout << -ninf * inf << endl;
	cout << 3 * inf << endl;
	cout << 3 * ninf << endl;
	cout << inf * -3 << endl;
	cout << ninf * -3 << endl;

	cout << endl;

	cout << inf + 3 << endl;
	cout << inf - 3 << endl;
	cout << -3 - inf << endl;
	cout << -3 + inf << endl;
	cout << 3 - inf << endl;
	cout << -3 + ninf << endl;
	cout << -3 - ninf << endl;
	cout << 3 + ninf << endl;

	cout << endl;

	cout << -3 + ninf << endl;
	cout << 3 + inf << endl;
	cout << ninf - 3 << endl;

	cout << endl;

	cout << BigInt(0) * -4857 << endl;
	cout << BigInt(-4757) * 0 << endl;
	cout << BigInt(3) - 3 << endl;
	cout << BigInt(-3) + 3 << endl;
	cout << BigInt(-3) / 4 << endl;
	cout << BigInt(3) / -4 << endl;
	cout << BigInt(-3) % 3 << endl;
	cout << BigInt(3) % -3 << endl;

	cout << endl;

	cout << 0 / inf << endl;
	cout << 0 / ninf << endl;

	cout << endl << "DONE" << endl;

	return EXIT_SUCCESS;
}
