#include "relations.h"

Bool areRelated(const char *firstWord, const char *secondWord) {

  int n = strlen(firstWord);
  int m = strlen(secondWord);
  int d = n - m;

  unsigned int i;
  unsigned int j;
  const char *initialPosition1 = firstWord;
  const char *initialPosition2 = secondWord;
  unsigned int differentLetters = 0; /* counter per il solo caso n == m */

  if (abs(d) > 1) {
    return FALSE; /* caso piu' semplice */
  }

  switch (d) {

    /* se le due parole differiscono in lunghezza per una lettera, tolgo l'i-esima lettera alla parola piu' lunga e la confronto con l'altra */
    case -1: /* n < m */
      for (i = 0; i < m; i++) { /* ciclo tra le lettere da eliminare (una per una, dalla parola piu' lunga) */

        for (firstWord = initialPosition1, secondWord = initialPosition2, j = 0; j < n; j++, firstWord++, secondWord++) { /* ciclo tra le lettere da confrontare */

          if (i == j) {
            secondWord++; /* salto l'i-esima lettera della parola piu' lunga */
          }

          if (*firstWord != *secondWord) { /* sto confrontando char */
            break;
          }

          if (j == n-1) {
            return TRUE;  /* se sono arrivato qui significa che le due parole, troncata la seconda, sono uguali */
          }

        }
      }
      break;

    case 1: /* n > m */
    for (i = 0; i < n; i++) { /* ciclo tra le lettere da eliminare (una per una, dalla parola piu' lunga) */

      for (firstWord = initialPosition1, secondWord = initialPosition2, j = 0; j < m; j++, firstWord++, secondWord++) { /* ciclo tra le lettere da confrontare */

        if (i == j) {
          firstWord++; /* salto l'i-esima lettera della parola piu' lunga */
        }

        if (*firstWord != *secondWord) { /* sto confrontando char */
          break;
        }

        if (j == m-1) {
          return TRUE;  /* se sono arrivato qui significa che le due parole, troncata la prima, sono uguali */
        }

      }
    }
    break;

    /* se le due parole hanno lo stesso numero di lettere, ricalco l'implementazione di strcmp: e' piu' veloce che usare n volte strcmp stesso come sopra */
    default: /* n == m */
      for (; differentLetters < 2; firstWord++, secondWord++) {


        if (*firstWord == '\0') {
          return TRUE; /* se arrivo in fondo significa che le parole sono identiche */
          fprintf(stderr, "\nAttenzione [string.c - areRelated]: il file contiene parole doppie\n");
        }
        if (*firstWord != *secondWord) { /* sto confrontando char */
          differentLetters++;
        }
      }

      return FALSE; /* non devo controllare differentLetters >= 2: se questo non accade allora il ciclo ha gia' ritornato TRUE arrivando alla fine di firstWord */

  }
  return FALSE;
}
