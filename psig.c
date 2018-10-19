// psig.c ... functions on page signatures (psig's)
// part of SIMC signature files
// Written by John Shepherd, September 2018

#include "defs.h"
#include "reln.h"
#include "query.h"
#include "psig.h"
#include "hash.h"

// helper function that generates codeword for tuple signatures

static Bits codeword(char *attr, int m, int k)
{
	Count nbits = 0;
	Bits cword  = newBits(m);
	srandom(hash_any(attr, strlen(attr)));
	while (nbits < k) {
		int i = random() % m;
		if (!bitIsSet(cword, i)) {
			setBit(cword, i);
			nbits++;
		}
	}

	return cword;
}

Bits makePageSig(Reln r, Tuple t)
{
	assert(r != NULL && t != NULL);
	//TODO
	Bits psig = newBits(psigBits(r));
	char **attrs = tupleVals(r, t);
	int  i;

	for (i = 0; i < nAttrs(r); i++) {
		if (attrs[i][0] == '?')		// ? makes no contribution to descriptor
			continue;
		Bits cw = codeword(attrs[i], psigBits(r), codeBits(r));
		orBits(psig, cw);
		freeBits(cw);
	}
	freeVals(attrs, nAttrs(r));

	return psig;
}

void findPagesUsingPageSigs(Query q)
{
	assert(q != NULL);
	//TODO

	Bits qsig = makePageSig(q->rel, q->qstring);
	unsetAllBits(q->pages);

	int total = 0;
	Offset pos;
	Page pgp;
	PageID pgpid;
	Bits psig  = newBits(8 * psigsize(q->rel));
	Bits pages = newBits(nPages(q->rel));

	for (pgpid = 0; pgpid < nPsigPages(q->rel); pgpid++) {
		pgp = getPage(psigFile(q->rel), pgpid);
		printf("%d\n", pageNitems(pgp));
		for (pos = 0; pos < pageNitems(pgp); pos++, total++) {
			getBits(pgp, pos, psig);
			if (isSubset(qsig, psig)) {
				setBit(pages, total);

			}
		}
	}

	q->pages = pages;

	// The printf below is primarily for debugging
	// Remove it before submitting this function
	printf("Matched Pages:"); showBits(q->pages); putchar('\n');
}

