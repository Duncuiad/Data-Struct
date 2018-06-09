#include "string.h"

void deleteAt(const char *word, char *container, unsigned int index) {
  /* elimina l'index-esima lettera della parola word e memorizza la parola residua in container */
  /* ATTENZIONE: container DEVE essere già allocato ed essere della dimensione sufficiente */
  int n = strlen(word);

  if (index >= n) {
    fprintf(stderr, "Errore [string.c - deleteAt()]: ho cercato di eliminare un carattere che non appartiene alla stringa");
    exit(-1);
  }
  if (index != 0) {
    memcpy(container, word, index);
  }
  if (index != n-1) {
    memcpy(&container[index], &word[index+1], n-1-index);
  }
  container[n-1] = '\0';
  return;
}

Bool areRelated(const char *firstWord, const char *secondWord) {
  int n = strlen(firstWord);
  int m = strlen(secondWord);
  int d = n - m;
  char temp[MAX_STR_LEN]; /* serve solo come argomento del parametro "container" di deleteAt */
  unsigned int i;
  unsigned int differentLetters = 0; /* counter per il solo caso n == m */

  if (abs(d) > 1) {
    return FALSE; /* caso piu' semplice */
  }

  switch (d) {

    /* se le due parole differiscono in lunghezza per una lettera, tolgo l'i-esima lettera alla parola piu' lunga e la confronto con l'altra */
    case -1: /* n < m */
      for (i = 0; i < m; i++) {
        deleteAt(secondWord, temp, i);
        if (strcmp(firstWord, temp) == 0) {
          return TRUE;
        }
      }
      break;

    case 1: /* n > m */
      for (i = 0; i < n; i++) {
        deleteAt(firstWord, temp, i);
        if (strcmp(secondWord, temp) == 0) {
          return TRUE;
        }
      }
    break;

    /* se le due parole hanno lo stesso numero di lettere, ricalco l'implementazione di strcmp: e' piu' veloce che usare n volte strcmp stesso come sopra */
    default: /* n == m */
      for (; differentLetters < 2; firstWord++, secondWord++) {
        if (*firstWord == '\0') {
          return TRUE; /* se arrivo in fondo significa che le parole sono identiche */
        }
        if (*firstWord != *secondWord) { /* sto confrontando char */
          differentLetters++;
        }
      }
      return FALSE; /* non devo controllare differentLetters >= 2: se questo non accade allora il ciclo ha gia' ritornato TRUE arrivando alla fine di firstWord */

  }
  return FALSE;
}
