#include "sorting.h"

void quickSort(int *array, int lower, int upper) {
  /* lavora in-place */
  /* prototipo: in realta' usero' solo le versioni specializzate per le componenti e per le parole */
  int lo = lower;
  int up = upper;
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

  /* chiamo quickSort sulla partizione */
  quickSort(array, lower, lo-1);
  quickSort(array, lo+1, upper);

  return;
}

void quickSortComponents(Graph *graph, int lower, int upper) {
  /* lavora in-place */
  /* prototipo: in realta' usero' solo le versioni specializzate per le componenti e per le parole */

  int lo = lower;
  int up = upper;
  Bool leftPivot = TRUE; /* TRUE se il pivot si trova in lo, FALSE se si trova in up */
  /* inizializzare leftPivot a TRUE significa scegliere l'elemento "lower" come pivot */
  int *array = graph -> graphInfo -> sortedComponents; /* il vettore che verra' ordinato */

  int temp; /* variabile temporanea per lo swap: l'alternativa sarebbe creare una funzione swap a cui passare ogni volta l'indirizzo di array */

  if (upper <= lower) {
    return; /* caso base: vettore con un solo elemento o vuoto */
  }

  /* Partition: invece che come sulle dispense, faccio rimbalzare l'elemento pivot tra lo e up, dove e' necessario uno scambio, per avere un solo swap per iterazione */
  /* nel frattempo restringo progressivamente il range, lasciando indietro gli elementi minori del pivot a sinistra e gli elementi maggiori a destra */
  while (lo < up) {

    if (leftPivot) { /* il pivot si trova in lo */

      if (comesBefore(graph, array[lo], array[up]) <= 0) { /* confronto l'elemento piu' a destra con il pivot che si trova in lo */
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

      if (comesBefore(graph, array[lo], array[up]) <= 0) {
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

  /* chiamo quickSort sulla partizione */
  quickSortComponents(graph, lower, lo-1);
  quickSortComponents(graph, lo+1, upper);

  return;
}

void quickSortWords(Graph *graph, int lower, int upper) {
  /* lavora in-place */
  /* prototipo: in realta' usero' solo le versioni specializzate per le componenti e per le parole */

  int lo = lower;
  int up = upper;
  Bool leftPivot = TRUE; /* TRUE se il pivot si trova in lo, FALSE se si trova in up */
  /* inizializzare leftPivot a TRUE significa scegliere l'elemento "lower" come pivot */
  int *array = graph -> graphInfo -> sortedNodes; /* il vettore che verra' ordinato */

  int temp; /* variabile temporanea per lo swap: l'alternativa sarebbe creare una funzione swap a cui passare ogni volta l'indirizzo di array */

  if (upper <= lower) {
    return; /* caso base: vettore con un solo elemento o vuoto */
  }

  /* Partition: invece che come sulle dispense, faccio rimbalzare l'elemento pivot tra lo e up, dove e' necessario uno scambio, per avere un solo swap per iterazione */
  /* nel frattempo restringo progressivamente il range, lasciando indietro gli elementi minori del pivot a sinistra e gli elementi maggiori a destra */
  while (lo < up) {

    if (leftPivot) { /* il pivot si trova in lo */

      if (strcmp(getWord(graph, array[lo]), getWord(graph, array[up])) <= 0) { /* confronto l'elemento piu' a destra con il pivot che si trova in lo */
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

      if (strcmp(getWord(graph, array[lo]), getWord(graph, array[up])) <= 0) {
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

  /* chiamo quickSort sulla partizione */
  quickSortWords(graph, lower, lo-1);
  quickSortWords(graph, lo+1, upper);

  return;
}

int comesBefore(Graph *graph, unsigned int c1, unsigned int c2) {
  /* output: <0 se c1<c2, ==0 se c1==c2, >0 se c2<c1 */
  /* questa convenzione mi permette di usare direttamente l'output di strcmp dove serve confrontare le prime parole delle due coomponenti connesse */
  int answer;
  Info *thisInfo = graph -> graphInfo;

  answer = (thisInfo -> cardinalities)[c2] - (thisInfo -> cardinalities)[c1]; /* la cardinalita' piu' grande viene prima */

  if (answer != 0) {
    return answer;
  }
  answer = (thisInfo -> diameters)[c2] - (thisInfo -> diameters)[c1]; /* il diametro piu' grande viene prima */

  if (answer != 0) {
    return answer;
  }
  answer = strcmp(getWord(graph, (thisInfo -> firstWord)[c1]), getWord(graph, (thisInfo -> firstWord)[c2]));

  return answer;
}
