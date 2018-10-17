// test Bits dt

#include <stdio.h>
#include "defs.h"
#include "reln.h"
#include "tuple.h"
#include "bits.h"

int main(int argc, char **argv)
{
	Bits b = newBits(60);
	printf("t=0: "); showBits(b); printf("\n");
	setBit(b, 5);
	printf("t=1: "); showBits(b); printf("\n");
	setBit(b, 0);
	setBit(b, 50);
	setBit(b, 59);
	setBit(b, 0);
	printf("t=2: "); showBits(b); printf("\n");
	if (bitIsSet(b,5)) printf("Bit 5 is set\n");
	if (bitIsSet(b,10)) printf("Bit 10 is set\n");
	setAllBits(b);
	printf("t=3: "); showBits(b); printf("\n");
	unsetBit(b, 40);
	printf("t=4: "); showBits(b); printf("\n");
	if (bitIsSet(b,20)) printf("Bit 20 is set\n");
	if (bitIsSet(b,40)) printf("Bit 40 is set\n");
	setBit(b, 59);
	unsetBit(b, 59);	
	printf("t=5: "); showBits(b); printf("\n");
	setBit(b, 59);
	printf("t=6: "); showBits(b); printf("\n");
	unsetAllBits(b);
	printf("t=7: "); showBits(b); printf("\n");
	Bits c = newBits(61);
	printf("t=0: "); showBits(c); printf("\n");
	//setBit(c, 59);
	//setBit(c, 5);
	printf("t=1: "); showBits(c); printf("\n");
	if (isSubset(c, b)) printf("Bit c is subset of Bit b\n");

	Bits d = newBits(8);
	Bits e = newBits(8);
	setBit(d, 2); setBit(d, 3);
	printf("t=0: "); showBits(d); printf("\n");
	setBit(e, 1); setBit(e, 2); setBit(e, 5);
	andBits(d, e);
	printf("t=1: "); showBits(d); printf("\n");
	freeBits(b);
	freeBits(c);
	freeBits(d);
	freeBits(e);

	// Bits f = itob(1024,60);
	// printf("Parsing 1024 to bits representation: \n");
	// showBits(f); printf("\n");
	// if (isZero(f)) printf("1024 is nought in binary\n");
	// f = itob(536870912,60);
	// printf("Parsing 536870912 to bits representation: \n");
	// showBits(f); printf("\n");
	// if (isZero(f)) printf("536870912 is nought in binary\n");
	// f = itob(636870912,60);
	// printf("Parsing 636870912 to bits representation: \n");
	// showBits(f); printf("\n");
	// if (isZero(f)) printf("636870912 is nought in binary\n");
	// Bits g, h;
	// g = itob(240,60);
	// printf("Parsing 240 to bits representation: \n");
	// showBits(g); printf("\n");
	// if (isZero(g)) printf("240 is nought in binary\n");
	// h = itob(15, 60);
	// printf("Parsing 15 to bits representation: \n");
	// showBits(h); printf("\n");
	// if (isZero(h)) printf("15 is nought in binary\n");
	// andBits(g, h);
	// printf("Parsing 240 & 15 to bits representation: \n");
	// showBits(g); printf("\n");
	// if (isZero(g)) printf("240 & 15 is nought in binary\n");
	// freeBits(f);
	// freeBits(g);
	// freeBits(h);
	return 0;
}
