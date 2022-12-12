#ifndef _CODE_H_
#define _CODE_H_

union data
{
	double value;
	pSymbol_t pSymb;
};

typedef union data data_t;

#define MAX_PILE 256

void push(data_t d);
data_t pop(void);

#define MAX_PROG 2000
typedef void (*instr_t)();
#define STOP (instr_t)0

instr_t *PC;

instr_t *code(instr_t frame);
void initCode(void);
void execute(instr_t *p);

#define code2(c1, c2) \
	code(c1);         \
	code(c2)

#define code3(c1, c2, c3) \
	code(c1);             \
	code(c2);             \
	code(c3)

#endif /* _CODE_H_ */
