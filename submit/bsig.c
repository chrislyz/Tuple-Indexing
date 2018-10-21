// bsig.c ... functions on Tuple Signatures (bsig's)
// part of SIMC signature files
// Written by John Shepherd, September 2018

#include "defs.h"
#include "reln.h"
#include "query.h"
#include "bsig.h"
#include "psig.h"	// for calling makePageSig()

void findPagesUsingBitSlices(Query q)
{
	assert(q != NULL);
	//TODO
	
	Bits qsig = makePageSig(q->rel, q->qstring);

	Count nthpage;
	Offset bpoff;
	int *pagearr = malloc(bsigBits(q->rel)*2*sizeof(int));
	memset(pagearr, -1, 100*sizeof(int));	
	Page bgp;
	Count nbits;

	if (nPages(q->rel) % 8 != 0)
		nbits = (nPages(q->rel) / 8 + 1) * 8;
	else
		nbits = nPages(q->rel);
	Bits pages = newBits(nbits);
	setAllBits(pages);
	int i, j;
	int idx = 0;
	Bool isRepeat = FALSE;

	for (i = 0; i < psigBits(q->rel); i++) {
		if (bitIsSet(qsig, i)) {
			q->nsigs++;
			nthpage = i / maxBsigsPP(q->rel);
			pagearr[idx] = nthpage;
			idx++;
			bpoff = i % maxBsigsPP(q->rel);
			bgp = getPage(bsigFile(q->rel), nthpage);
			Bits b = newBits(bsigBits(q->rel));
			getBits(bgp, bpoff, b);
			for (j = 0; j < bitNbits(pages); j++) {
				if (!bitIsSet(b, j))
					unsetBit(pages, j);
			}
			free(b);
		}
	}

	for (i = 0; i < bsigBits(q->rel)*2; i++) {
		if (pagearr[i] == -1)
			break;
		for (j = 0; j < i; j++) {
			if (pagearr[j] == pagearr[i]) {
				isRepeat = TRUE;
				break;
			}
		}
		if (isRepeat) {
			isRepeat = FALSE;
			continue;
		}
		q->nsigpages++;

	}
	free(pagearr);

	Bool all = TRUE;
	char **attrs = tupleVals(q->rel, q->qstring);
	for (i = 0; i < nAttrs(q->rel); i++)
		if (attrs[i][0] != '?')
			all = FALSE;

	if (all) {
		q->nsigs = nBsigs(q->rel);
		q->nsigpages = nBsigPages(q->rel);
	}

	freeVals(attrs, nAttrs(q->rel));



	q->pages = pages;
}

