#include <stdio.h>
#include "gf256.h"

int test_value(uint8_t real, uint8_t expected){
	if(real == expected){
		printf("Testing 0x%02x == 0x%02x PASSED!\n", real, expected);
		return 1;
	}else{
		printf("Testing 0x%02x == 0x%02x FAILED!\n", real, expected);
	}
	return 0;
}

int main(){

	gf256_t a, b, c, d;
	int all_good = 1;

	a = 147;
	b = 9;
	printf("a = 0x%02x\n", (int)a);
	printf("b = 0x%02x\n", (int)b);
	
	c = gf_mul(a, b);
	printf("c = a*b = 0x%02x\n", (int)c);
	all_good &= test_value(c, 0x67);

	d = gf_div(c, b);
	printf("d = c/b = 0x%02x\n", (int)d);
	all_good &= test_value(d, a);

	printf("a = 0x%02x\n", (int)a);
	printf("~a = 0x%02x\n", (int)gf_inv(a));
	gf256_t i = gf_mul(a, gf_inv(a));
	printf("i = a * ~a = 0x%02x\n", (int)i);
	all_good &= test_value(i, 0x01);

	gf256_t g = 147, p = 4;
	gf256_t gp = gf_pow(g, p);
	printf("gp = g^a = 0x%02x ^ 0x%02x = 0x%02x\n", (int)g, (int)p, (int)gp);
	all_good &= test_value(gp, 0x8a);

	if(!all_good){
		printf("Some of the tests failed. Library isn't working properly!\n");
		return 1;
	}

	printf("All test passed. Library is working properly!\n");

	return 0;
}
