/**
 *  \var    _consts[]
 *  \brief  Déclaration des variables (constantes mathématiques) prédéfinines
 */
static struct {
  char *cName; short cType;
  double cValue; char *cDesc;
} _consts[] = {
  "PI",         REEL,     3.14159265358979323846,   "Archimede's constant",
  "E",          REEL,     2.71828182845904523536,   "Euler's constant",
  "GAMMA",      REEL,     0.57721566490153286060,   "Another Euler's constant",
  "DEG",        REEL,     57.2957795130823208768,   "360/2*Pi",
  "PHI",        REEL,     1.61803398874989484820,   "Golden ratio",
  "MAXSTACK",   ENTIER,   256,                      "Taille de la pile d'exe",
  "MAX_PROG",   ENTIER,   2000,                     "Taille de la machine d'exe",
  NULL,         0,        0,                        NULL,
};

/**
 *  \fn void installDefaultSymbols(void)
 *  \brief  Installe les symboles par défaut dans la table des symboles :
 *          <UL>
 *            <LI> Constantes : PI, E, ... </LI>
 *            <LI> Fonction mathématiques : sin(), cos(), ... </LI>
 *          </UL>
 */
void installDefaultSymbols(void) {
  int *pInt;
  double *pFlo;

  for (int i = 0; _consts[i].cName != NULL; i++) {
    if (_consts[i].cType == ENTIER) {
      pInt = (int *) malloc(sizeof(int));
      *pInt = (int) _consts[i].cValue;
      installSymbol(_consts[i].cName, CST, _consts[i].cType, sizeof(int), pInt);
    }
    else if (_consts[i].cType == REEL) {
      pFlo = (double *) malloc(sizeof(double));
      *pFlo = _consts[i].cValue;
      installSymbol(_consts[i].cName, CST, _consts[i].cType, sizeof(double), pFlo);
    }
  }
}
