#define _CODE_C_
#include "hoc.h"

extern int isFloat;

static instr_t prog[MAX_PROG];
static instr_t *progPtr;
static data_t pile[MAX_PILE];
static data_t *pilePtr;

instr_t *code(instr_t frame) {
  instr_t *adr = progPtr;
	if (progPtr >= &prog[MAX_PROG])
		printMessageTag(19);
	*progPtr++ = frame;
	return adr;
}

void execute(instr_t *p) {
  for(PC = p; *PC != STOP;) {
    (*(*PC++))();
  }
}

void initCode(void)
{
	pilePtr = pile;
	progPtr = prog;
	PC = prog;
	isFloat = 0;
	prompt();
}

data_t pop(void) {
  data_t d;
  if (pilePtr <= pile) printMessageTag(18);
  d = *--pilePtr;
  return d;
}

void push(data_t d) {
  if(pilePtr >= &pile[MAX_PILE]) printMessageTag(17);
  *pilePtr++ = d;
}
