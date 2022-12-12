/*********_********_*********_********_*********_********_***********_*********/
/*                  M A C H I N E  D' E X E C U T I O N                       */
/*********_********_*********_********_*********_********_***********_*********/
////////////////////////////////////////////////////////////////////////////////
#ifndef _CODE_H_
#define _CODE_H_
/*********_********_*********_********_*********_********_***********_*********/
///////////     MANIPULATION DE LA PILE DES DONNEES                 ////////////
/*********_********_*********_********_*********_********_***********_*********/
////////////////////////////////////////////////////////////////////////////////
// DECLARATIONS:
// Définition du type d'éléments manipulés par la pile de données
typedef union {
	double value;
	symbol_t *pSymb;
} data_t;
// Taille Max de la Pile
#define MAX_PILE 256
////////////////////////////////////////////////////////////////////////////////
// PILE-DATA-EXECUTION :    push(), pop()
/*********_********_*********_********_*********_********_***********_*********/
// Empiler une donnée sur la pile de données
void push(data_t d);
/*********_********_*********_********_*********_********_***********_*********/
// Dépiler une donnée depuis la pile de données : sommet
data_t pop(void);
////////////////////////////////////////////////////////////////////////////////
/*********_********_*********_********_*********_********_***********_*********/
///////////     MANIPULATION DE LA PILE D'INSTRUCTIONS              ////////////
/*********_********_*********_********_*********_********_***********_*********/
////////////////////////////////////////////////////////////////////////////////
// DECLARATIONS:
// Taille max d'un prog
#define MAX_PROG 2000
// Définition du type d'instructions machine
typedef int (*instr_t) ();
#define STOP (instr_t) 0 		 // Instruction STOP
instr_t *PC;            		 // Compteur d'éxecution
////////////////////////////////////////////////////////////////////////////////
// CODE-GENERATION: code(), codeSy(), codeOp(), jump()
/*********_********_*********_********_*********_********_***********_*********/
// Installer une instruction machine dans la pile d'instructions
instr_t  *code(instr_t  frame);
/*********_********_*********_********_*********_********_***********_*********/
#define code2(c1,c2)        code(c1);   code(c2)
#define code3(c1,c2,c3)     code(c1);   code(c2);   code(c3)
////////////////////////////////////////////////////////////////////////////////
// CODE-EXECUTION:  execute(), parcoursPROG(), offsetPROG(), dbgAddrsMAC,
//                  _prompt(), initCode(), clearInput()
/*********_********_*********_********_*********_********_***********_*********/
// Executer un programme situé à l'adresse p dans la pile d'instructions
void execute(instr_t  *pc);
/*********_********_*********_********_*********_********_***********_*********/
// Initialiser les différents adresses
void initCode(void);
////////////////////////////////////////////////////////////////////////////////

#endif	/* _CODE_H_ */
