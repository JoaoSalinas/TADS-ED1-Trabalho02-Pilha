#include "lista.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

  Card* createCard( char suit[], char simbol[], int value){
    Card* card = (Card*) malloc(sizeof(Card));
      if(!card){
        printf("Sem memoria disponivel!\n");
        exit(0);
      }

      strcpy(card->suit, suit);
      strcpy(card->simbol, simbol);
      card->value = value;

    return card;
  }

  Stack* createDeck(int quantityOfDecks){            
    Stack* deck = (Stack*) malloc(sizeof(Stack));    

    char suitsRand[4][20] = {"Copas", "Ouro", "Espadas", "Paus"};
    char simbolCard[13][3] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};    
    
    if(quantityOfDecks <= 0){
      printf("Eh preciso inserir ao menos um baralho\n");
      return NULL;
    }

    while(quantityOfDecks > 0){
      for(int i = 0; i < 4; i++){
        for(int j = 0; j < 13; j++){           
          pushStack(deck, createCard(suitsRand[i],simbolCard[j], j+1));                         
        }
      }
       quantityOfDecks--;
    }

    shuffleDeck(deck);
    return deck;
  }

  void pushStack(Stack* deck, Card* card){
    if(deck->top == NULL){
      deck->top = card;
      deck->length = 1;
      return;
    } else{
      card->next = deck->top;
    }
    deck->top = card;
    deck->length++;
  }

  Card* popStack(Stack* deck){   
    Card* tmp = NULL;

    if(deck->top != NULL){      
      tmp = deck->top;            
      deck->top = deck->top->next;
      deck->length--;
    }else{
      printf("Pilha vazia");
    }
    return tmp;
  }
  
  Card* drawCard(Stack* deck, Hand* player){
    Card* tmp = NULL;

    if(deck->length <= 0){
      printf("Sem cartas no baralho. Impossivel comprar!");
      return tmp;
    }

    tmp = deck->top;
    deck->top = deck->top->next;
    deck->length--;
    
    push(player, tmp);    
  }

  Card* playCardInStackedTable(Hand* player, Stack* table, Stack* deck){
    if(table->top == NULL){
      playCardInVoidTable(player, table, deck);
      return NULL;
    }

    printf("Carta na mesa:");
    printCard(table->top);      

    while(haveSuit(table, player) != 1){
      printf("Voce nao tem um carta do naipe de %s para jogar na sua mão, comprando carta...\n\n", table->top->suit);
      drawCard(deck, player);        
    }          

    int position = 0;
    printf("\nEscolha uma carta da sua mao para jogar na mesa:\n\n");
    showHand(player);         

    printf("\nEscolha a posicao da carta da sua mao para jogar na mesa (comecando em 0 e indo ate %d):", lengthHand(player)-1);
    scanf("%d", &position);
    fflush(stdin);   

    if(position >= lengthHand(player)){      
      printf("Posicao invalida.");
      playCardInStackedTable(player, table, deck);
      return NULL;
    }

    Card* cardFromHand = getCardFromHand(player, position);             

    if(strcmp(cardFromHand->suit, table->top->suit) != 0){
      printf("A carta precisa ser do mesmo naipe que a carta do topo da pilha: %s\n\n", table->top->suit);
      playCardInStackedTable(player, table, deck);
    } else{        
      Card* tmp = getCardFromHand(player, position);            
      Card* cardTable = createCard(tmp->suit, tmp->simbol, tmp->value);  
      pushStack(table, cardTable);
      deleteCard(player, position);
    }
  }

  Card* playCardInVoidTable(Hand* player, Stack* table, Stack* deck){    

    if(table->top != NULL){
      playCardInStackedTable(player, table, deck);
      return NULL;
    }

    int position = 0;
    printf("Escolha uma carta da sua mao para jogar na mesa:\n\n");
    showHand(player);         

    printf("\n\nEscolha a posicao da carta da sua mao para jogar na mesa (comecando em 0 e indo ate %d):", lengthHand(player)-1);
    scanf("%d", &position);
    fflush(stdin);

    if(position >= lengthHand(player)){      
      printf("Posicao invalida.");
      playCardInVoidTable(player, table, deck);
      return NULL;
    }
    
    Card* tmp = getCardFromHand(player, position);
    Card* cardTable = createCard(tmp->suit, tmp->simbol, tmp->value);   
    pushStack(table, cardTable);
    deleteCard(player, position);
  } 

  void showHand(Hand* player){
    Card* tmp = player->first;

    for(int i = 0; i < lengthHand(player); i++){
      printCard(tmp);
      tmp= tmp->next;
    }
  }

  int haveSuit(Stack* table, Hand* player){
    Card* tmp = player->first;
    int haveSuit = 0;

    while(tmp->next != NULL){
      if(strcmp(tmp->suit, table->top->suit) == 0){
        haveSuit = 1;
      }
      tmp = tmp->next;
    }

    return haveSuit;    
  }

  Stack* shuffleDeck(Stack* deck){     

    srand(time(NULL));
    
    int random = 0;
    while(random < 5){
      random = rand() %50;
    }

    Stack* deck1 = (Stack*) malloc(sizeof(Stack));
    Stack* deck2 = (Stack*) malloc(sizeof(Stack));
    Stack* deck3 = (Stack*) malloc(sizeof(Stack));
    Stack* deck4 = (Stack*) malloc(sizeof(Stack));

    Stack* decks[4] = {deck1, deck2, deck3, deck4};

    int deckHalfed;

    while(random > 0){    
      deckHalfed = deck->length/4;
      for(int i = 0; i < 4; i++){
        for(int j = 0; j < deckHalfed; j++){                        
          Card* card = popStack(deck);                                 
          pushStack(decks[i], card);          
        }
      }  

      int cardsInDeck = deck1->length + deck2->length + deck3->length + deck4->length;

      for(int i = 0; i < cardsInDeck/4; i++){ 
        for(int j = 0; j < 4; j++){          
          Card* card = popStack(decks[j]);                
          pushStack(deck, card);
        }       
      }
      random--;
    }
  }
  
  int deckSize(Stack* deck){
    return deck->length;
  }

  void printCard(Card* card){
  //   printf("---------\n");
  //   printf("|%7s|\n", card->simbol);
  //   printf("|%7c|\n", ' ');    
  //   printf("|%7s|\n", card->suit);
  //   printf("---------\n");

    printf("{%s de %s}, ", card->simbol, card->suit);
  }

  void printDeck(Stack* deck){
    Card* tmp = deck->top;

    if(deck->top == NULL){
      printf("Sem baralho.");
    }

    for(int i = 0; i < deck->length; i++){
      printCard(tmp);
      tmp = tmp->next;
    }
  }

  Game* createGame(){
    Game* game = (Game*) malloc(sizeof(Game));
      if(!game){
        printf("Sem memoria disponivel!\n");
        exit(0);
      }
      game->round = 0;
    return game;
  }

  void startGame(Game* game, Hand* player1, Hand* player2, Stack* deck){
    for(int i = 0; i < 3; i++){
      drawCard(deck, player1);
      drawCard(deck, player2);
    }
      game->deck = deck;
      game->round = 1;
      game->players[0] = player1;
      game->players[1] = player2;
      game->table = (Stack*) malloc(sizeof(Stack));
  }

  void resetTable(Stack* table){
    while (table->top != NULL){
      popStack(table);
    }
  }


void pause(){
    printf("\nAperte qualquer tecla para prosseguir com o jogo...\n");
    getchar();
    scanf("c\n");
    fflush(stdin);
		printf("\33[H\33[2J");
}
