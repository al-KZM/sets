/*
 *
 * Definition of the sets functions
 *
 */

#include <stdio.h>
#include "set.h"



void add_number(set s, int n){
    int int_ix, bit_ix;

    /* Add 1 to n in order to store 0 value */
    n += 1;

    int_ix = n / 32;
    bit_ix = n % 32;

    s[int_ix] |= (1 << (bit_ix-1));
}

void remove_number(set s, int n){


    int int_ix, bit_ix;
    n += 1;

    int_ix = n / 32;
    bit_ix = n % 32;

    s[int_ix] &= ~(1 << (bit_ix-1));
}

int search_number(set s, int n){
    int int_ix, bit_ix;

    n += 1;

    int_ix = n / 32;
    bit_ix = n % 32;

    if ((s[int_ix] & (1 << (bit_ix-1))) != 0)
        return 1;
    return 0;
}

void read_set(set s, int *args, int args_num){
    int ix;
    while (args_num-- >= 0){
        s[ix++] = *args++;
    }
}

void print_set(set s){
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

            /* Add a comma if it's not the first printed item */
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

void union_set(set set1, set set2, set to_set){
    int ix;

    for (ix=0; ix <= ARR_SIZE; ix++){
        to_set[ix] = set1[ix] | set2[ix];
    }
}

void intersect_set(set set1, set set2, set to_set){
    int ix;

    for (ix=0; ix <= ARR_SIZE; ix++){
        to_set[ix] = set1[ix] & set2[ix];
    }
}

void sub_set(set set1, set set2, set to_set){
    int ix;

    for (ix=0; ix <= ARR_SIZE; ix++){
        to_set[ix] = set1[ix] & (~set2[ix]);
    }
}

void symdiff_set(set set1, set set2, set to_set){
    int ix;

    for (ix=0; ix <= ARR_SIZE; ix++){
        to_set[ix] = set1[ix] ^ set2[ix];
    }
}

