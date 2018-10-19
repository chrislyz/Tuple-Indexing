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

	// Bits qsig = makePageSig(q->rel, q->qstring);
	setAllBits(q->pages);

	// Page bgp;
	// Bits pages = newBits(nPages(q->rel));
	// setAllBits(pages);
	// bgp = getPage(bsigFile(q->rel), 0);
}

