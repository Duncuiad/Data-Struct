La compilazione del codice del progetto è gestita tramite makefile:

Per compilare il programma e le librerie a cui esso si appoggia nell'ordine
corretto è sufficiente digitare "make main" da riga di comando.

Se necessario, ho implementato il comando "make clean" per eliminare tutti
i file oggetto (*.o) presenti nella cartella root del progetto.

Per eseguire il programma, lanciare da terminale il comando
./main.x NOME_FILE_SORGENTE NOME_FILE_DI_ARRIVO

Ho raccolto tutti i file (sorgente, soluzione e di appoggio) nella cartella files
Per questo motivo i due nomi dei file dati in input al programma dovrebbero
rispettare il formato
NOME_FILE_SORGENTE = ./files/Esempio.txt
NOME_FILE_DI_ARRIVO = ./files/EsempioMySolution.txt

Importante: includere l'estensione nel nome del file

Nota: ho denotato con l'estensione .dat i file nel formato di stampa della
funzione saveGraph, il cui unico ruolo (non rilevante per il progetto ma
rilevante per lo sviluppo del codice) è di salvare le informazioni strutturali
di un grafo su un file di testo con un formato interno alle librerie che ho
implementato. I file .dat vengono letti dalla funzione loadGraph (diversa dalla
funzione importGraph, che si occupa di costruire il grafo delle parole a partire
da un file di testo nel formato specificato nella traccia del problema)
