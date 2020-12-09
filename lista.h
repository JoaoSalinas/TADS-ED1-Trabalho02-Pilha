#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "./burro.h"

 Hand* createHand();
 int unshift(Hand* list , Card* card);
 int push(Hand* list, Card* card);
 int splice(Hand *list, Card *card, int position);
 Card* shift(Hand *list);
 Card* pop(Hand *list);
 Card* deleteCard(Hand *player, int position);
 Card* getCardFromHand(Hand* playerHand, int position);
 int lengthHand(Hand* hand);
 void showHand(Hand* player);





 