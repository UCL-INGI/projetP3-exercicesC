#ifndef HELP_H
#define HELP_H

#include <stdio.h>
#include <stdlib.h>

// Structures
typedef struct card{
    int value;
    struct card* next;
} card_t;

typedef struct deck{
    int id_player;
    int size;
    struct card* tail;
    struct card* head;
} deck_t;

// Prototypes
void print_deck(deck_t* deck);
int addCard(deck_t* d, int val);
int drawCard(deck_t* d);
deck_t* createDeck(int id, int* cardsData, int nCards);
int findBestActiveCard(const int* activeCards, int manyPlayers);


#endif