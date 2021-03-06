/* +----------------------------------+ */
/* |              GF256               | */
/* |             gf256.h              | */
/* |   (c)copyright nitram147 2021    | */
/* +----------------------------------+ */
#ifndef GF256_H
#define GF256_H

#include <stdint.h>

typedef uint8_t gf256_t;

static gf256_t gf_log(gf256_t a);
static gf256_t gf_exp(gf256_t a);
gf256_t gf_inv(gf256_t a);
gf256_t gf_add(gf256_t a, gf256_t b);
gf256_t gf_sub(gf256_t a, gf256_t b);
gf256_t gf_mul(gf256_t a, gf256_t b);
gf256_t gf_div(gf256_t a, gf256_t b);
gf256_t gf_pow(gf256_t a, uint8_t p);

//Precomputed tables, scroll down to the tutorial for computation of these values
//Tables were computed for the value 0x93(147dec) of the AES (Rjindael) multiplicative group generator
//I had selected 147 because it's also the suffix of my nickname
//Any valid generator can be used - read more about possible values bellow

//last element will never be used !!! (table access goes like i%255 so this will never result in i == 255)
static const uint8_t gf_exp_tab[] = {
	0x01, 0x93, 0x84, 0xA3, 0x8A, 0x10, 0xF3, 0x98, 0xDE, 0x78, 0x1B, 0xA9, 0x43, 0x4F, 0xC1, 0xAB,
	0x7E, 0x5C, 0x9C, 0xA4, 0x5E, 0xA1, 0xB7, 0x03, 0xAE, 0x97, 0xFE, 0x85, 0x30, 0x0E, 0xB3, 0x79,
	0x88, 0x2D, 0xE0, 0xC5, 0xD1, 0x58, 0xE6, 0x82, 0xE4, 0xBF, 0xF7, 0xE2, 0xF8, 0xC2, 0x05, 0xE9,
	0xA2, 0x19, 0x94, 0x50, 0x12, 0xCE, 0x8B, 0x83, 0x77, 0x3B, 0x54, 0x68, 0xE8, 0x31, 0x9D, 0x37,
	0xDA, 0x02, 0x3D, 0x13, 0x5D, 0x0F, 0x20, 0xFD, 0x2B, 0xA7, 0xF0, 0x36, 0x49, 0x86, 0x9E, 0x99,
	0x4D, 0xFC, 0xB8, 0x23, 0x53, 0xBC, 0x59, 0x75, 0x06, 0x47, 0x35, 0xE7, 0x11, 0x60, 0x1C, 0x7D,
	0xF2, 0x0B, 0x5A, 0xDB, 0x91, 0xB9, 0xB0, 0xD7, 0x1F, 0xD3, 0x65, 0xF5, 0xDF, 0xEB, 0x9F, 0x0A,
	0xC9, 0x5F, 0x32, 0x33, 0xA0, 0x24, 0x87, 0x0D, 0x1D, 0xEE, 0x76, 0xA8, 0xD0, 0xCB, 0x62, 0x21,
	0x6E, 0xAF, 0x04, 0x7A, 0x26, 0xBA, 0x1E, 0x40, 0xE1, 0x56, 0x55, 0xFB, 0x6C, 0x92, 0x17, 0x27,
	0x29, 0x9A, 0xE3, 0x6B, 0x46, 0xA6, 0x63, 0xB2, 0xEA, 0x0C, 0x8E, 0x6A, 0xD5, 0x22, 0xC0, 0x38,
	0xFA, 0xFF, 0x16, 0xB4, 0xAD, 0x39, 0x69, 0x7B, 0xB5, 0x3E, 0xBD, 0xCA, 0xF1, 0xA5, 0xCD, 0x25,
	0x14, 0x89, 0xBE, 0x64, 0x66, 0x5B, 0x48, 0x15, 0x1A, 0x3A, 0xC7, 0xEC, 0x4B, 0xBB, 0x8D, 0xC4,
	0x42, 0xDC, 0x45, 0x08, 0xF4, 0x4C, 0x6F, 0x3C, 0x80, 0xD9, 0xAC, 0xAA, 0xED, 0xD8, 0x3F, 0x2E,
	0x4E, 0x52, 0x2F, 0xDD, 0xD6, 0x8C, 0x57, 0xC6, 0x7F, 0xCF, 0x18, 0x07, 0xD4, 0xB1, 0x44, 0x9B,
	0x70, 0xEF, 0xE5, 0x2C, 0x73, 0x41, 0x72, 0xD2, 0xF6, 0x71, 0x7C, 0x61, 0x8F, 0xF9, 0x51, 0x81,
	0x4A, 0x28, 0x09, 0x67, 0xC8, 0xCC, 0xB6, 0x90, 0x2A, 0x34, 0x74, 0x95, 0xC3, 0x96, 0x6D, 0x01,
};

//first element shouldn't be used - there isn't logaritm of zero!!!
static const uint8_t gf_log_tab[] = {
	0xFF, 0x00, 0x41, 0x17, 0x82, 0x2E, 0x58, 0xDB, 0xC3, 0xF2, 0x6F, 0x61, 0x99, 0x77, 0x1D, 0x45,
	0x05, 0x5C, 0x34, 0x43, 0xB0, 0xB7, 0xA2, 0x8E, 0xDA, 0x31, 0xB8, 0x0A, 0x5E, 0x78, 0x86, 0x68,
	0x46, 0x7F, 0x9D, 0x53, 0x75, 0xAF, 0x84, 0x8F, 0xF1, 0x90, 0xF8, 0x48, 0xE3, 0x21, 0xCF, 0xD2,
	0x1C, 0x3D, 0x72, 0x73, 0xF9, 0x5A, 0x4B, 0x3F, 0x9F, 0xA5, 0xB9, 0x39, 0xC7, 0x42, 0xA9, 0xCE,
	0x87, 0xE5, 0xC0, 0x0C, 0xDE, 0xC2, 0x94, 0x59, 0xB6, 0x4C, 0xF0, 0xBC, 0xC5, 0x50, 0xD0, 0x0D,
	0x33, 0xEE, 0xD1, 0x54, 0x3A, 0x8A, 0x89, 0xD6, 0x25, 0x56, 0x62, 0xB5, 0x11, 0x44, 0x14, 0x71,
	0x5D, 0xEB, 0x7E, 0x96, 0xB3, 0x6A, 0xB4, 0xF3, 0x3B, 0xA6, 0x9B, 0x93, 0x8C, 0xFE, 0x80, 0xC6,
	0xE0, 0xE9, 0xE6, 0xE4, 0xFA, 0x57, 0x7A, 0x38, 0x09, 0x1F, 0x83, 0xA7, 0xEA, 0x5F, 0x10, 0xD8,
	0xC8, 0xEF, 0x27, 0x37, 0x02, 0x1B, 0x4D, 0x76, 0x20, 0xB1, 0x04, 0x36, 0xD5, 0xBE, 0x9A, 0xEC,
	0xF7, 0x64, 0x8D, 0x01, 0x32, 0xFB, 0xFD, 0x19, 0x07, 0x4F, 0x91, 0xDF, 0x12, 0x3E, 0x4E, 0x6E,
	0x74, 0x15, 0x30, 0x03, 0x13, 0xAD, 0x95, 0x49, 0x7B, 0x0B, 0xCB, 0x0F, 0xCA, 0xA4, 0x18, 0x81,
	0x66, 0xDD, 0x97, 0x1E, 0xA3, 0xA8, 0xF6, 0x16, 0x52, 0x65, 0x85, 0xBD, 0x55, 0xAA, 0xB2, 0x29,
	0x9E, 0x0E, 0x2D, 0xFC, 0xBF, 0x23, 0xD7, 0xBA, 0xF4, 0x70, 0xAB, 0x7D, 0xF5, 0xAE, 0x35, 0xD9,
	0x7C, 0x24, 0xE7, 0x69, 0xDC, 0x9C, 0xD4, 0x67, 0xCD, 0xC9, 0x40, 0x63, 0xC1, 0xD3, 0x08, 0x6C,
	0x22, 0x88, 0x2B, 0x92, 0x28, 0xE2, 0x26, 0x5B, 0x3C, 0x2F, 0x98, 0x6D, 0xBB, 0xCC, 0x79, 0xE1,
	0x4A, 0xAC, 0x60, 0x06, 0xC4, 0x6B, 0xE8, 0x2A, 0x2C, 0xED, 0xA0, 0x8B, 0x51, 0x47, 0x1A, 0xA1,
};

//Tutorial for computation of exp and log tables:
//
//Step 1.) Select AES multiplicative group generator from the following list:
//
//	0x03 0x05 0x06 0x09 0x0b 0x0e 0x11 0x12 0x13 0x14 0x17 0x18 0x19 0x1a 0x1c 0x1e
//	0x1f 0x21 0x22 0x23 0x27 0x28 0x2a 0x2c 0x30 0x31 0x3c 0x3e 0x3f 0x41 0x45 0x46
//	0x47 0x48 0x49 0x4b 0x4c 0x4e 0x4f 0x52 0x54 0x56 0x57 0x58 0x59 0x5a 0x5b 0x5f
//	0x64 0x65 0x68 0x69 0x6d 0x6e 0x70 0x71 0x76 0x77 0x79 0x7a 0x7b 0x7e 0x81 0x84
//	0x86 0x87 0x88 0x8a 0x8e 0x8f 0x90 0x93 0x95 0x96 0x98 0x99 0x9b 0x9d 0xa0 0xa4
//	0xa5 0xa6 0xa7 0xa9 0xaa 0xac 0xad 0xb2 0xb4 0xb7 0xb8 0xb9 0xba 0xbe 0xbf 0xc0
//	0xc1 0xc4 0xc8 0xc9 0xce 0xcf 0xd0 0xd6 0xd7 0xda 0xdc 0xdd 0xde 0xe2 0xe3 0xe5
//	0xe6 0xe7 0xe9 0xea 0xeb 0xee 0xf0 0xf1 0xf4 0xf5 0xf6 0xf8 0xfb 0xfd 0xfe 0xff
//
//
//Step 2.) Build an exponentiation table mapping indexes from range {0,1,...,254} to the element g^i where g == generator value
// selected from the table above
//
// Init table with size 255 or 256 elements (in case of 256 the last one would not be used) named exp_tab
// Set t=0x01
// For i in range {0,1,..254} do:
//		exp_tab[i] = t
//		t = aes_multiply(g, t)
// Done
// Group is cyclic (g^255 == g^0, g^256 == g^1, etc.) so you can find g^i as exp_tab[i % 255]
//
//Step 3.) Build an logaritm table log_tab mapping g^i to the i where i is from range {0,1,...,254}
//
// Init table with size 256 elements (first wouldn't be used but we will keep it for easier indexing) named log_tab
// For i in range {0,1,...,254} do:
//		log_tab[exp_tab[i]] = i
// Done
// We can keep log_tab[0] uninitialized or initialize it by any value
//
// Everything's done. Enjoy the tables :-)

#endif
