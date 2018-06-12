#include "sorting.h"

void quickSort(int *array, unsigned int lower, unsigned int upper) {

  unsigned int lo = lower;
  unsigned int up = upper;
  Bool leftPivot = TRUE; /* TRUE se il pivot si trova in lo, FALSE se si trova in up */
  /* inizializzare leftPivot a TRUE significa scegliere l'elemento "lower" come pivot */

  int temp; /* variabile temporanea per lo swap: l'alternativa sarebbe creare una funzione swap a cui passare ogni volta l'indirizzo di array */

  if (upper <= lower) {
    return; /* caso base: vettore con un solo elemento o vuoto */
  }

  /* Partition: invece che come sulle dispense, faccio rimbalzare l'elemento pivot tra lo e up, dove e' necessario uno scambio, per avere un solo swap per iterazione */
  /* nel frattempo restringo progressivamente il range, lasciando indietro gli elementi minori del pivot a sinistra e gli elementi maggiori a destra */
  while (lo < up) {

    if (leftPivot) { /* il pivot si trova in lo */

      if (array[lo] <= array[up]) { /* confronto l'elemento piu' a destra con il pivot che si trova in lo */
        up--; /* lascio l'ultimo elemento dov'e' */
      }
      else {
        /* swap */
        temp = array[lo];
        array[lo] = array[up];
        array[up] = temp;

        lo++; /* passo oltre */

        leftPivot = FALSE; /* mi ricordo di aver spostato il pivot in up */
      }

    } else { /* il pivot si trova in up */

      if (array[lo] <= array[up]) {
        lo++;
      }
      else {
        /* swap */
        temp = array[lo];
        array[lo] = array[up];
        array[up] = temp;

        up--;

        leftPivot = TRUE; /* mi ricordo di aver spostato il pivot in lo */
      }
    }
  }

  /* lo == up a questo punto della procedura, ed entrambi indicizzano il pivot */

  /* passaggio di ricorsione */
  quickSort(array, lower, lo-1);
  quickSort(array, lo+1, upper);

  return;
}
