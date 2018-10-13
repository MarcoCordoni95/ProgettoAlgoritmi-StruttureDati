typedef char stringa[31];//Definisco un tipo stringa il quale è un array di char di 31 caratteri

struct grafo{//Struttura che definisce un grafo di un albero2_3
	struct tree2_3 *T;//Definisco la radice dell'albero di nome T
	struct nodo *head;//Definisco un puntatore al primo utente inserito
	struct nodo *last;//Definisco un puntatore all'utltimo utente inserito
	int conta;//Cotantore del numero di utenti inseriti nell'albero 
}

struct nodo{//Struttura che definisce i nodi dell'albero2_3
	struct utente *profilo;//Puntatore al profilo dell'utente con le sue informazioni
	int L;//E' il massimo campo id presente nel sottoalbero T1, uguale ad id se questa è una foglia
	int M;//E' il massimo campo id presente nel sottoalbero T2, uguale ad id se questa è una foglia
	struct nodo *T1;
	struct nodo *T2;
	struct nodo *T3;/*T1, T2, T3 e T4 sono puntatori a delle strutture di tipo nodo, si riempiono in ordine da T1 a T4 e se T1 è nullo 
						significa che lo saranno anche i successivi ed il nodo in questione è una foglia*/
	struct nodo *T4;/*Questo puntatore è solo ausiliario, utilizzato in fase di inserimento di un nuovo utente per verificare se è 
						necessario dividere il nodo padre per evitare che esso abbia 4 figli, quindi applicare la funzione "reduce"*/
	struct nodo *father;//Padre del nodo, NULL se è la radice
}

struct utente{//Struttura che contiene le informazioni degli utenti
	stringa nome;//Definisco un campo nome che non può superare i 30 caratteri (il trentun-esimo corrisponde a \0)
	stringa cognome;//Definisco un campo cognome che non può superare i 30 caratteri (il trentun-esimo corrisponde a \0)
	int id;//Definisco un campo identificativo di tipo int
	int pos;//Definisco un campo contenente l'ordine di inserimento dell'utente nell'albero
	struct amico *friend;//Testa della lista di adiacenza di amici dell'utente, NULL se non ve ne sono ancora
	struct utente *next;//Puntatore al prossimo utente della lista d'adiacenza di utenti, NULL se è l'ultimo inserito
}
	
struct amico{//Struttura utilizzata per indicare gli amici di un utente tramite una lista di adiacenza
	struct utente *friend;//Puntatore all'utente amico
	int anno;//Anno in cui è nata l'amicizia
	struct amico *next;//Puntatore al prossimo amico, NULL se non ve ne sono altri
}

typedef struct grafo G;//Definisco un tipo grafo di nome "G"
typedef struct nodo nodo;//Definisco un tipo nodo di nome "nodo"
typedef struct nodo tree2_3;//Definisco un tipo nodo di nome "tree2_3"
typedef struct utente utente;//Definisco un tipo utente di nome "utente"
typedef struct amico amico;//Definisco un tipo amico di nome "amico"

grafo G new_utente(grafo G);/*Questa funzione prende in ingresso una struttura grafo e richiede l'inserimento del nome, cognome ed identificativo
							di un utente e ritorna un grafo con il nuovo utente inserito se nell'albero non ne era già presente uno con lo stesso identificativo*/

tree2_3 insert(utente *u, grafo G);/*Questa funzione prende in input le informazioni di un utente, quindi il nome, cognome ed identificativo ed un grafo e 
									ritorna l'albero2_3 del grafo con l'aggiunta di un nuovo elemento nella posizione corretta se non ne era già presente uno con lo stesso id*/

tree2_3 create_tree(utente *u, grafo G);/* Questa funzione prende in input un utente con i suoi dati, quindi il nome, cognome ed identificativo e ed un grafo 
										e ritorna un albero2_3 con solo tale elemento come radice*/
	
nodo search_father(utente *u, tree2_3 T);/*Questa funzione prende in input un utente e la radice di un albero2_3 e cerca il posto in cui inserire 
										l'elemento, ovvero ritorna il suo nodo padre potenziale, quindi non si ferma alle foglie ma al livello 
										immediatamente superiore, se tale padre non esiste ritorna NULL*/

void append(utente *u, nodo *p, grafo G);/*Questa funzione prende in input un utente, il nodo padre che dovrà contenere tale utente ed il grafo, la posizione in cui 
											inserirlo sarà la prima libera fra quelle da T1 a T4, tale funzione non restituisce nulla ma modifica l'albero*/										

void reduce(nodo *p1, grafo G);/*Questa funzione prende in input un nodo p1 ed un grafo e si occupa di sistemare l'albero nel caso che 
								 a tale nodo sia stato aggiunto un nodo figlio in T4, perchè ciò significherebbe che tale nodo ha 4 figli 
								 e quindi non sarebbe corretto secondo la struttura degli alberi2_3*/
								 
int max(nodo *p);/*Questa funzione prende in input un nodo e restituisce l'id massimo presente tra i suoi sottoalberi*/

void update_threshold(nodo *p);/*Questa funzione prende in input un nodo p e si occupa di aggiornare il valore delle soglie L ed M nei nodi 
								da p fino alla radice dell'albero, quindi risalgo l'albero per mezzo del puntatore al padre e mi fermo quando tale valore
								sarà nullo perchè significherà che mi sto trovando nella radice*/
		
int ident(utente *u);/*Questa funzione prende in input un utente e ritorna il suo identificatore*/

void trova(int id, tree2_3 T);/*Questa funzione prende in input un identificativo e la radice di un albero2_3 e stampa a video i dati della persona ricercata se questa esiste*/
	
utente *search(int id, tree2_3 T);/*Questa funzione prende in input un identificativo e la radice di un albero2_3 e ritorna NULL se l'identificativo non è presente,
									oppure, se lo è, ritorna un puntatore all'utente stesso*/

void friendship(int id1, int id2);/*Questa funzione prende in input 2 identificativi di 2 utenti Facebook ed aggiunge in testa alla lista di adiacenza di
									amici di ognuno l'utente con l'altro identificativo all'interno di una struttura "amico" contenente un intero
									che indica l'anno di creazione della relazione d'amicizia, un puntatore a quell'utente ed un puntatore al prossimo
									amico della lista d'adiacenza, la funzione ritorna un messaggio d'errore se l'amicizia già esiste oppure uno o
									entrambi gli untenti con tale id non esistono*/									 
									 
void allgroups(grafo G);/*Questa funzione prende in input un grafo  ed analizza le relazione di amicizia presenti in esso, determinando i sottoinsiemi 
						di utenti che risultino in relazione d'amicizia, diretta o indiretta.
						Se nel grafo ho n utenti ma nessuno ha amici allora avrò n gruppi, al contrario se sono tutti direttamente o indirettamente
						amici allora si otterrà	un solo gruppo*/							
							
void allgroupsyear(grafo G, int year);/*Questa funzione è simile ad allgroups ma considera solo le relazioni di amicizia nate dall'anno "year" in poi*/