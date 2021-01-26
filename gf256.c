/* +----------------------------------+ */
/* |              GF256               | */
/* |             gf256.c              | */
/* |   (c)copyright nitram147 2021    | */
/* +----------------------------------+ */
#include <stdint.h>
#include "gf256.h"

static gf256_t gf_log(gf256_t a){
	//lookup for logaritm result, shoudln't be called with a == 0 - there's no log of zero
	return gf_log_tab[a];
}

static gf256_t gf_exp(gf256_t a){
	//lookup for exponentiation result
	return gf_exp_tab[a % 255];
}

gf256_t gf_inv(gf256_t a){
	//log of zero don't exist & zero is inverse for itself 
	if (a == 0x00) return 0x00;
	// (1/g^e) = g^(-e) => get an exponent and add group order (to make it positive)
	// exponentiate it to the obtained exponent
	return gf_exp(255 - gf_log(a));
}

gf256_t gf_add(gf256_t a, gf256_t b){
	//addition is simple XOR
	return a ^ b;
}

gf256_t gf_sub(gf256_t a, gf256_t b){
	//substraction is simple XOR
	return a ^ b;
}

gf256_t gf_mul(gf256_t a, gf256_t b){
	//skip multiplication by zero
	if(a == 0x00 || b == 0x00) return 0x00;
	// (g^e * g^d) = g^(e+d) => get exponents and sum them, correct the sum by group order
	// even gf_exp function alone is doing group order correction, however it's argument is uint8_t
	// and because our result is 16bit long (sum of two 8bit integers) it has to be corrected also here
	// before the function call in order to work correctly!!!
	return gf_exp((uint16_t)(gf_log(a) + gf_log(b)) % 255);
}

gf256_t gf_div(gf256_t a, gf256_t b){
	//skip zero numerator, also skip division by zero
	if(a == 0x00 || b == 0x00) return 0x00;
	// a / b = a * (1/b)
	// multiply number a by the inverse of number b
	return gf_mul(a, gf_inv(b));
}

gf256_t gf_pow(gf256_t a, uint8_t p){
	if(a == 0x00) return 0x00;
	if(p == 0x00) return gf_exp(0);
	// (g^e)^d = g^(e*d) => get exponent of the a and multiply it by the required power, correct the result by group order
	// reason for correction is the same as in the case of gf_mul function
	return gf_exp((uint16_t)(gf_log(a) * p) % 255);
}
