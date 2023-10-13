/*
 *	programma per implementare SDES  
 */
#include<stdlib.h>
#include<stdio.h>

#include "../include/SDES.h"

// funzione cifra che restituisce 12 bit (3 char) di cipher text
// prende in input un array di 2 char (16 bit, di cui solo 12 sono usati) che è il plain text e la chiave (9 bit quindi sempre 3 char con i primi 3 bit settati a 0)
char* cifra(char * plaintext, char * key){
	// schema cifra:
	//	1. plain text ha 12 bit (6 sx e 6 dx), chiave 9 bit(8 + 1 parità) 
	//	2. i 6 bit di dx vanno in feistel e poi vengono xorati con parte di sinistra e così ottengo la nuova parte destra
	//	3. la parte di sx metto i vecchi bit di dx
	//
	// per cifrare devo:
	// applicare iterazione 3 volte
	// calcolando ogni volta la chiave
	char *cifr = (char*)malloc(sizeof(char)*2);
	// copio i byte che ho in plaintext in cifr
	cifr[0] = plaintext[0];
	cifr[1] = plaintext[1];
	for(int i = 0; i < 3; i++){
		printf("\niterazione %d ris:", i);
		cifr = iterazione(cifr, calcolaChiave(key, i), i);
		printf("sx:");
		stampaBin(cifr[1]);
		printf("dx:");
		stampaBin(cifr[0]);

		printf("\tchiave usata: ");
		stampaBin(calcolaChiave(key, i));
	}
	
	return cifr;
}

char calcolaChiave(char *key, int i){
	char chiave_it = 0;
	int pos;
	char v;
  	for (int j = 0; j < 8; j++) {
		pos = (i+j)%8;
		
		if (pos == 0){
			// accedo al primo bit memorizzato in key[1]
			v = !!((key[1] << j) & 0x80);
		}else{
			// accedo al bit chiesto in key[0]
			v = !!(((key[0] << pos) & 0x80)>>j);
		}
		chiave_it = chiave_it | (v << (7-j));
 	}
	return chiave_it;
}
// esegue la iesima iterazione
char * iterazione(char *plaintext, char key, int i){
	// faccio spazio per il testo cifrato
	char *cifr = (char*)malloc(sizeof(char)*2);
	// prende la parte destra e
	// applica la funzione di feistel
	char v = feistel(plaintext[0], key);
	// esegue xor con la parte sinistra
	char newDx = plaintext[1]^v;	
	// la nuova sinistra è la nuova destra	
	cifr[0] = newDx;
	cifr[1] = plaintext[0];

	return cifr;
}
char feistel(char v, char key){
	char ris;
	// espande
	ris = espansione(v);

	// esegue lo xor con la chiave
	ris = ris ^ key;
	// comprime con sbox
	// devo prendere i primi 4 bit come input per S1 e ultimi 4 bit come input S2
	char sx = (ris >> 4 & 15);
	char dx = (ris & 15);
	ris = (S1(sx) << 3 | S2(dx)); 	
	return ris;
}
// funzione usata per l'espansione 
// prende in input 6 bit e da in output 8 bit (utilizzata per il plaintext)
char  espansione(char  v){
	// faccio spazio per 1 char (8 bit)
	char esp = 0;	
	// i primi due bit sono i primi due bit del v	
	// poi ci sono i due bit di mezzo copiati due volte in ordine inverso
	// infine ci sono i due bit di coda
	// imposto i primi due bit
	esp = esp | (v & 48) << 2;
	// imposto i bit di mezzo
	esp = esp | inverti((v&12)>> 2) <<4;
	esp = esp | inverti((v&12) >> 2) << 2; 
	esp = esp | (v & 3);
	return esp;
}

// funzione per invertire i bit
char inverti(char v){
	v = v & 3;
	switch(v){
	case 0: return 0;
	case 1: return 2;
	case 2: return 1;
	case 3: return 3;
	}
	return 4;
}
// funzione usata per rappresentare l'SBOX 1
char S1(char v){
	switch(v){
		case 0: return 5;
		case 1: return 2;
		case 2: return 1;
		case 3: return 6;
		case 4: return 3;
		case 5: return 4;
		case 6: return 7;
		case 7: return 0;
		
		case 8: return 1;
		case 9: return 4;
		case 10: return 6;
		case 11: return 2;
		case 12: return 0;
		case 13: return 7;
		case 14: return 5;
		case 15: return 3;
		default: return 0;
	}
}
// funzione usata per rappresentare l'SBOX 2
char S2(char v){
	switch(v){
		case 0: return 4;
		case 1: return 0;
		case 2: return 6;
		case 3: return 5;
		case 4: return 7;
		case 5: return 1;
		case 6: return 3;
		case 7: return 2;
		
		case 8: return 5;
		case 9: return 3;
		case 10: return 0;
		case 11: return 7;
		case 12: return 6;
		case 13: return 2;
		case 14: return 1;
		case 15: return 4;
		default: return 0;
	}
}
void stampaBin(char a){
  int i;
  printf("[");
  for (i = 0; i < 8; i++) {
      printf("%d", !!((a << i) & 0x80));
  }
  printf("]");
}
