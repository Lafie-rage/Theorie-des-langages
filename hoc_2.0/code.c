#define _CODE_C_
#include "hoc.h"

// Table de code
instr_t prog[MAX_PROG];
instr_t *progPtr;
instr_t *PC;

instr_t *code(instr_t frame) {
  instr_t *adr = progPtr;
  if (progPtr >= &prog[MAX_PROG]) printMessageTag(19);
  *progPtr++ = frame;
  #ifdef DBG_CODE
  printf("Debug code %p\n", frame);
  #endif
  return adr;
}

void execute(instr_t *p) {
  for(PC = p; *PC != STOP;) {
    (*(*PC++))();
  }
}

// Pile de données
data_t pile[MAX_PILE];
data_t *pilePtr;

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
