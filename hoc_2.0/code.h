#ifndef _CODE_H_
#define _CODE_H_

#define STOP (instr_t) 0
#define MAX_PROG 2000
#define MAX_PILE 256

typedef int(*instr_t)();

union data {
  double value;
  pSymbol_t pSymb;
};

typedef union data data_t;

instr_t *PC;

instr_t *code(instr_t);


void initCode(void);

void execute(instr_t *);


data_t pop(void);

void push(data_t);

#define code2(c1, c2) \
  code(c1);           \
  code(c2)

#define code3(c1, c2, c3) \
  code(c1);               \
  code(c2);               \
  code(c3)

#endif
