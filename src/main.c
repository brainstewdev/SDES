#include<stdio.h>
#include<stdlib.h>

#include "../include/SDES.h"
/*
 *	argomenti:
 *		- primo argomento: intero da usare come messaggio
 *		- secondo argomento: intero da usare come chiave
 * */
int main(int argc, char **argv){
	if(argc != 3){
		printf("sintassi: SDES [messaggio] [chiave]\n");
		return 1;
	}
	int msg_read;
	int key_read;

	sscanf(argv[1], "%d", &msg_read);
	sscanf(argv[2], "%d", &key_read);

	char * mess = (char*)malloc(sizeof(char)*2);
	char *key = (char*)malloc(sizeof(char)*2);

	// copio la parte alta della chiave letta (un bit) all'interno di key
	key[1] = (char)(key_read & 256 >> 9);
	// printf("left chiave:");
	// stampaBin((char)(key_read & 256 >> 9));
	// copio il resto della chiave letta (8 bit) all'interno di key
	key[0] = (char)key_read &255;
	
	mess[1] = (char)((msg_read & 16128) >> 8);
	mess[0] = (char)msg_read & 63;
	
	printf("cifro il messaggio ");
	stampaBin(mess[1]);
	stampaBin(mess[0]);

	printf("\ncon la chiave ");
	stampaBin(key[1]);
	stampaBin(key[0]);

	char *ris = cifra(mess, key);
	
	printf("\nrisultato:");
	stampaBin(ris[1]);
	stampaBin(ris[0]);
	printf("\n");
}
