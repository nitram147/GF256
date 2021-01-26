/* +----------------------------------+ */
/* |              GF256               | */
/* |    exp_log_tables_generator.c    | */
/* |   (c)copyright nitram147 2021    | */
/* +----------------------------------+ */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/* AES (Rjindael) field multiplication code from wikipedia */

	uint8_t gmul(uint8_t a, uint8_t b) {
		uint8_t p = 0; /* the product of the multiplication */
		while (a && b) {
	            if (b & 1) /* if b is odd, then add the corresponding a to p (final product = sum of all a's corresponding to odd b's) */
	                p ^= a; /* since we're in GF(2^m), addition is an XOR */

	            if (a & 0x80) /* GF modulo: if a >= 128, then it will overflow when shifted left, so reduce */
	                a = (a << 1) ^ 0x11b; /* XOR with the primitive polynomial x^8 + x^4 + x^3 + x + 1 (0b1_0001_1011) – you can change it but it must be irreducible */
	            else
	                a <<= 1; /* equivalent to a*2 */
	            b >>= 1; /* equivalent to b // 2 */
		}
		return p;
	}

/* End of code from wikipedia */

const uint8_t generators_array[] = {
	0x03, 0x05, 0x06, 0x09, 0x0b, 0x0e, 0x11, 0x12, 0x13, 0x14, 0x17, 0x18, 0x19, 0x1a, 0x1c, 0x1e,
	0x1f, 0x21, 0x22, 0x23, 0x27, 0x28, 0x2a, 0x2c, 0x30, 0x31, 0x3c, 0x3e, 0x3f, 0x41, 0x45, 0x46,
	0x47, 0x48, 0x49, 0x4b, 0x4c, 0x4e, 0x4f, 0x52, 0x54, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x5b, 0x5f,
	0x64, 0x65, 0x68, 0x69, 0x6d, 0x6e, 0x70, 0x71, 0x76, 0x77, 0x79, 0x7a, 0x7b, 0x7e, 0x81, 0x84,
	0x86, 0x87, 0x88, 0x8a, 0x8e, 0x8f, 0x90, 0x93, 0x95, 0x96, 0x98, 0x99, 0x9b, 0x9d, 0xa0, 0xa4,
	0xa5, 0xa6, 0xa7, 0xa9, 0xaa, 0xac, 0xad, 0xb2, 0xb4, 0xb7, 0xb8, 0xb9, 0xba, 0xbe, 0xbf, 0xc0,
	0xc1, 0xc4, 0xc8, 0xc9, 0xce, 0xcf, 0xd0, 0xd6, 0xd7, 0xda, 0xdc, 0xdd, 0xde, 0xe2, 0xe3, 0xe5,
	0xe6, 0xe7, 0xe9, 0xea, 0xeb, 0xee, 0xf0, 0xf1, 0xf4, 0xf5, 0xf6, 0xf8, 0xfb, 0xfd, 0xfe, 0xff,
};

void print_generator_options(){
	printf("Select one from the following generator options:\n");
	printf(
		"\t0x03, 0x05, 0x06, 0x09, 0x0b, 0x0e, 0x11, 0x12, 0x13, 0x14, 0x17, 0x18, 0x19, 0x1a, 0x1c, 0x1e,\n"
		"\t0x1f, 0x21, 0x22, 0x23, 0x27, 0x28, 0x2a, 0x2c, 0x30, 0x31, 0x3c, 0x3e, 0x3f, 0x41, 0x45, 0x46,\n"
		"\t0x47, 0x48, 0x49, 0x4b, 0x4c, 0x4e, 0x4f, 0x52, 0x54, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x5b, 0x5f,\n"
		"\t0x64, 0x65, 0x68, 0x69, 0x6d, 0x6e, 0x70, 0x71, 0x76, 0x77, 0x79, 0x7a, 0x7b, 0x7e, 0x81, 0x84,\n"
		"\t0x86, 0x87, 0x88, 0x8a, 0x8e, 0x8f, 0x90, 0x93, 0x95, 0x96, 0x98, 0x99, 0x9b, 0x9d, 0xa0, 0xa4,\n"
		"\t0xa5, 0xa6, 0xa7, 0xa9, 0xaa, 0xac, 0xad, 0xb2, 0xb4, 0xb7, 0xb8, 0xb9, 0xba, 0xbe, 0xbf, 0xc0,\n"
		"\t0xc1, 0xc4, 0xc8, 0xc9, 0xce, 0xcf, 0xd0, 0xd6, 0xd7, 0xda, 0xdc, 0xdd, 0xde, 0xe2, 0xe3, 0xe5,\n"
		"\t0xe6, 0xe7, 0xe9, 0xea, 0xeb, 0xee, 0xf0, 0xf1, 0xf4, 0xf5, 0xf6, 0xf8, 0xfb, 0xfd, 0xfe, 0xff,\n"
	);
}

void print_help(){
	printf(	"Provide generator value as the first argument.\n"
			"Value can be in hex or dec format.\n"
			"For example 0xff or 255\n");
	print_generator_options();
}

void print_tabs(const uint8_t *exp_tab, const uint8_t *log_tab){
	printf("static const uint8_t gf_exp_tab[] = {\n");
	for(unsigned i=0; i<256; ++i){
		printf("%s0x%02X,%s", (i%16 == 0) ? "\t" : "", exp_tab[i], (i%16 == 15) ? "\n" : " ");
	}
	printf("};\n");
	
	printf("\n");

	printf("static const uint8_t gf_log_tab[] = {\n");
	for(unsigned i=0; i<256; ++i){
		printf("%s0x%02X,%s", (i%16 == 0) ? "\t" : "", log_tab[i], (i%16 == 15) ? "\n" : " ");
	}
	printf("};\n");	
}

int main(int argc, char *argv[]){

	if(argc < 2){
		print_help();
		return 0;
	}

	unsigned long tmp_generator;
	if(argv[1][0] == '0' && argv[1][1] == 'x'){
		tmp_generator = strtoul(argv[1], NULL, 16);
	}else{
		tmp_generator = strtoul(argv[1], NULL, 10);
	}

	if(tmp_generator > (unsigned long)255){
		printf("Bad generator value - value is too big!\n");
		print_generator_options();
		return 1;
	}

	uint8_t generator = (uint8_t)tmp_generator;
	
	int success = 0;
	for(int i=0; i < 16*8; ++i){
		if(generators_array[i] == generator){
			success = 1;
			break;
		}
	}

	if(!success){
		printf("Bad generator value - provided values is not correct generator value!\n");
		print_generator_options();
		return 2;
	}

	uint8_t exp_tab[256];
	uint8_t log_tab[256];

	uint8_t t=0x01;
	for(uint8_t i=0; i<255; ++i){
		exp_tab[i] = t;
		t = gmul(generator, t);
	}
	exp_tab[255] = 0x01;

	for(uint8_t i=0; i<255; ++i){
		log_tab[exp_tab[i]] = i;
	}
	log_tab[0] = 0xff;

	print_tabs(exp_tab, log_tab);

	return 0;
}