// Table de code
typedef int(*instr_t)();

#define STOP (instr_t) 0
#define MAX_PROG 2000

instr_t *code(instr_t);

void execute(instr_t *);

// Pile de données
typedef union {
    double value;
    symbol_t pSymb;
} data_t;

#define MAX_PILE 256

data_t pop(void);

void push(data_t);
