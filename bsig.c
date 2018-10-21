// bsig.c ... functions on Tuple Signatures (bsig's)
// part of SIMC signature files
// Written by John Shepherd, September 2018

#include "defs.h"
#include "reln.h"
#include "query.h"
#include "bsig.h"
#include "psig.h"

void findPagesUsingBitSlices(Query q)
{
	assert(q != NULL);
	//TODO

	Count nthpage;
	Offset bpoff;
	Bits qsig = makePageSig(q->rel, q->qstring);
	Page bgp;
	Count nbits = (nPages(q->rel) / 8 + 1) * 8;
	Bits pages = newBits(nbits);
	setAllBits(pages);

	int i, j;
	for (i = 0; i < psigBits(q->rel); i++) {
		if (bitIsSet(qsig, i)) {
			nthpage = i / maxBsigsPP(q->rel);
			bpoff = i % maxBsigsPP(q->rel);
			bgp = getPage(bsigFile(q->rel), nthpage);
			Bits b = newBits(bsigBits(q->rel));
			getBits(bgp, bpoff, b);
			for (j = 0; j < bitNbits(pages); j++) {
				if (!bitIsSet(b, j))
					unsetBit(pages, j);
			}
		}
	}
	
	q->pages = pages;

	// The printf below is primarily for debugging
	// Remove it before submitting this function
	printf("Matched Pages:"); showBits(q->pages); putchar('\n');

}

