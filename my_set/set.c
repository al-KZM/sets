/*
 *
 * Definition of the sets functions
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"

#define same_str(s1, s2) (strcmp(s1, s2) == 0) /* TODO global header */


void add_number(set *s, int n){
    int int_ix, bit_ix;


    int_ix = n / 32;
    bit_ix = n % 32;

    (*s)[int_ix] |= (1 << (bit_ix-1));
}

void remove_number(set *s, int n){

    int int_ix, bit_ix;

    int_ix = n / 32;
    bit_ix = n % 32;

    (*s)[int_ix] &= ~(1 << (bit_ix-1));
}

int search_number(set *s, int n){
    int int_ix, bit_ix;

    int_ix = n / 32;
    bit_ix = n % 32;

    if (( (*s)[int_ix] & (1 << (bit_ix-1) )) != 0)
        return 1;
    return 0;
}

void reset_set(set *s){
    int i;
    for (i=0; i < ARR_SIZE; i++){
        (*s)[i] = 0;
    }
}

void read_set(set *s, int *args, int args_num){
    /* Reset the set to create a new one */
    reset_set(s);

    while (--args_num >= 0){
        add_number(s, *args++);
    }
}

void print_set(set *s){
    int i;
    int is_empty;
    int first;

    first = 1;
    is_empty = 1;

    for (i=0; i <= SET_SIZE; i++){

        /* Check if the number is in the set */
        /* TODO: loop through the bits. */
        if (search_number(s, i)){
            is_empty = 0;

            /* Add a comma innoremap vimf it's not the first printed item */
            if (first == 1)
                printf("%d ", i);
            else
                printf(", %d", i);

            /* Every 16 values, break a line */
            if (i != 0 && i % 16 == 0)
                printf("\n");
        }
    }

    if (is_empty == 1)
        printf("The set is empty");

    printf("\n");
}

void union_set(set *set1, set *set2, set *to_set){
    int ix;

	reset_set(to_set);

    for (ix=0; ix < ARR_SIZE; ix++){
        (*to_set)[ix] = (*set1)[ix] | (*set2)[ix];
    }
}

void intersect_set(set *set1, set *set2, set *to_set){
    int ix;

	reset_set(to_set);

    for (ix=0; ix < ARR_SIZE; ix++){
        (*to_set)[ix] = (*set1)[ix] & (*set2)[ix];
    }
}

void sub_set(set *set1, set *set2, set *to_set){
    int ix;

	reset_set(to_set);

    for (ix=0; ix < ARR_SIZE; ix++){
        (*to_set)[ix] = (*set1)[ix] & (~(*set2)[ix]);
    }
}

void symdiff_set(set *set1, set *set2, set *to_set){
    int ix;

	reset_set(to_set);

    for (ix=0; ix < ARR_SIZE; ix++){
        ( *to_set )[ix] = ( *set1 )[ix] ^ ( *set2 )[ix];
    }
}

