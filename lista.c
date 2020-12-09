#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "./lista.h"

 Hand* createHand(char name[]){        
     Hand* playerHand = (Hand*) malloc(sizeof(Hand));

     if(!playerHand){
         printf("Problema com a criacao da mao do jogador!\n");
         exit(0);
     }

     playerHand->first = NULL;
     playerHand->last = NULL;    
     strcpy(playerHand->name, name);

     return playerHand;
 }

 int unshift(Hand* list , Card* card){

     if(list->first == NULL){
         list->last = card;
     }else{
         card->next = list->first;
     }
     list->first = card;
    //  list->quantity++;   
     return list->first == card ? 1 : 0;
 }

 int push(Hand* list, Card* card){
     card->next = NULL;
     if(list->first == NULL){
        list->first = card;
     } else{
        list->last->next = card;
     }

     list->last = card;
    //  list->quantity++;
     return list->last == card ? 1 : 0;
 }

 int splice(Hand *list, Card *card, int position){

     int quantity = lengthHand(list);

    if (position > quantity){
        printf("Posicao invalida\n");
        return 0;
    }

    if(quantity == position){
        push(list, card);
        return 1;
    }

    if(position == 0){
        unshift(list, card);
        return 1;
    }

    Card *tmp = list->first;

    int i;
    for (i = 0; i < position-1; i++){
        tmp = tmp->next;
    }

    Card* next = tmp->next;
    card->next = next;
    tmp->next = card;

    return 1;
 }

 Card* shift(Hand *list){
    int quantity = lengthHand(list);

    Card *tmp = NULL;

    if(quantity == 0){
        printf("Vazia!\n");
        return tmp;
    }else if(quantity == 1){
        free(list->first);
        list->first = NULL;
        list->last = NULL;
    }else{
        tmp = list->first;
        list->first = list->first->next;
        free(tmp);
    }
    
    return list->first;
 }

 Card* pop(Hand *list){
     Card* tmp = NULL;
     int sizeHand = lengthHand(list);

     if(sizeHand == 0){
      printf("Mao vazia");
      return NULL;
     } else if(sizeHand == 1){
         return shift(list);
     }else{
        tmp = getCardFromHand(list, sizeHand-2);        
        list->last = tmp;
        Card* result = tmp->next;
        tmp->next = NULL;        
        return result;      
    }
    return tmp;
 }

 Card* deleteCard(Hand *player, int position){
    Card *tmp = NULL;
    int sizeHand = lengthHand(player);

    if(position == 0){
        return shift(player);        
    }else if(position == sizeHand -1){
        return pop(player);
    }

    if (position >= sizeHand || position < 0){
        printf("\nPosicao invalida\n");
        return tmp;
    }

    if(sizeHand == 0){
      printf("\nMao Vazia!\n");
      return tmp;
    }

    tmp = getCardFromHand(player, position-1);

    Card *deleting = tmp->next;

    tmp->next = deleting->next;    

    free(deleting);

    return tmp;
 }

 Card* getCardFromHand(Hand* playerHand, int position){
    Card *tmp = playerHand->first;

    int i;
    for (i = 0; i < position; i++){
        tmp = tmp->next;
    }    
    return tmp;
 }

  int lengthHand(Hand* hand){
    
    int quantity = 0;
    Card* tmp = hand->first;

    while(tmp != NULL){
      tmp= tmp->next;
      quantity++;
    }

    return quantity;
  }
