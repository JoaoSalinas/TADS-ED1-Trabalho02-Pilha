  typedef struct card{
    char suit[20];
    char simbol[2];
    int value;
    struct card* next;
  }Card;

    typedef struct stack{
      Card *top;
      int length;
  }Stack;

   typedef struct hand{
      Card *first;
      Card *last;        
      int winnerOfLastRound;
      char name[20];
  }Hand;

  typedef struct game{
      Hand* players[2];
      Stack* deck;
      int round;
      Stack* table;
  } Game;

  Card* createCard( char suit[], char simbol[], int value);

  //* Cria Baralho com 4 Naipes. O baralho será uma estrutura de dados do tipo Pilha;
  Stack* createDeck(int quantityOfDecks); 
  
  //* Embaralha as cartas (a função deve realizar o embaralhamento de modo aleatório, retirando cartas do baralho e colocando em  outros baralhos para simular a troca nas posições das cartas. Ao final do processo o baralho principal ficará alterado).
  Stack* shuffleDeck(Stack* deck);
  
  //* O jogo (main) deve ter no mínimo dois jogadores, cada jogador poderá ter uma lista de carta em sua mão (Lista Simplesmente Encadeada);
  //* A cada rodada um jogador pode:
  //* compra uma carta do baralho (pop) ou jogar um carta da sua lista de carta (Mão de cartas);
  Card* drawCard(Stack* deck, Hand* player);
  Card* playCardInStackedTable(Hand* player, Stack* table, Stack* deck);
  Card* playCardInVoidTable(Hand* player, Stack* table, Stack* deck);
  void showCard(Card* card);  

  //* O adversário deve:
  //* jogar uma carta do mesmo naipe (Primeiro jogador), caso não tenha esta carta, deve comprar (pop) do baralho, até encontrar a carta de mesmo Naipe;  
  int haveSuit(Stack* table, Hand* player);

  //* O jogador que jogar a carta com maior valor vence a rodada e se tornará o primeiro jogador da próxima rodada;

  //* O jogador que ficar sem cartas na mão primeiro vence o jogo;
  int deckSize(Stack* deck);

  void pushStack(Stack* deck, Card* card);
  Card* popStack(Stack* deck);
  void pause();
  void printCard(Card* card);
  void printDeck(Stack* deck);
  Game* createGame();

  void startGame(Game* game, Hand* player1, Hand* player2, Stack* deck);
  void resetTable(Stack* table);
  
