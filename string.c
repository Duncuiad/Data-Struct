#include "string.h"

void deleteAt(const char *word, char *container, unsigned int index) {
  /* ATTENZIONE: container DEVE essere già allocato ed essere della dimensione sufficiente */
  int n = strlen(word);

  if (index >= n) {
    fprintf(stderr, "Errore [string.h - deleteAt()]: ho cercato di eliminare un carattere che non appartiene alla stringa");
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
  char temp[MAX_STR_LEN];
  char temp2[MAX_STR_LEN];
  int i;

  if (abs(n-m) > 1) {
    return FALSE; /* caso piu' semplice */
  }

  if (n < m) {
    for (i = 0; i < m; i++) {
      deleteAt(secondWord, temp, i);
      if (strcmp(firstWord, temp) == 0) {
        return TRUE;
      }
    }
  }

  else if (n > m) {
    for (i = 0; i < n; i++) {
      deleteAt(firstWord, temp, i);
      if (strcmp(secondWord, temp) == 0) {
        return TRUE;
      }
    }
  }

  else if (n==m) {
    for (i = 0; i < n; i++) {
      deleteAt(firstWord, temp, i);
      deleteAt(secondWord, temp2, i);
      if (strcmp(temp, temp2) == 0) {
        return TRUE;
      }
    }
  }

  return FALSE;
}
