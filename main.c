#include<stdio.h>
#include<stdlib.h>
#include"lista.h"


int main(){  
    int quantityOfDecks;

    Game* game = createGame();

    printf("Quantos baralhos serao utilizados?");
    scanf("%d", &quantityOfDecks);
    fflush(stdin);
    Stack* deck = createDeck(quantityOfDecks);    
    pause();

    char player1Name[30];
    printf("Informe o nome do jogador 1: ");
    scanf("%s", player1Name);
    fflush(stdin);
    Hand* player1 = createHand(player1Name);
    pause();

    char player2Name[30];
    printf("Informe o nome do jogador 2: ");
    scanf("%s", player2Name);
    fflush(stdin);  
    Hand* player2 = createHand(player2Name);   
    pause();      

    printf("embaralhando...");
    shuffleDeck(deck);
    pause();
    startGame(game, player1, player2, deck);   

    int winnerOfLastRound = 0; 

    while(lengthHand(player1) > 0 && lengthHand(player2) > 0){
        printf("turno do jogador: %s\n", game->players[0]->name); 
        playCardInVoidTable(game->players[0], game->table, deck);
        pause();

        printf("turno do jogador: %s.\n", game->players[1]->name); 
        playCardInStackedTable(game->players[1], game->table, deck);            
        pause();

        winnerOfLastRound = game->table->top->value > game->table->top->next->value ? 1 : 0;

        if(winnerOfLastRound == 1){
            Hand* playerTmp = game->players[0];
            game->players[0] = game->players[1];
            game->players[1] = playerTmp;
        }

        printf("Final da rodada. Quem ganhou esta rodada foi o jogador: %s.\n", game->players[0]->name);
        pause();

        printf("Comecando nova rodada\n\n");
        resetTable(game->table);

    }

    printf("Fim de jogo! o vencedor foi o jogador %s.\n", lengthHand(game->players[0]) == 0 ? game->players[0]->name : game->players[1]->name );
    pause();

    return 0;
}