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

struct group_of_sets{
    set SETA;
    set SETB;
    set SETC;
    set SETD;
    set SETE;
    set SETF;
} sets = { {0}, {0},{0},{0},{0},{0}};

set *get_set(char *set_name){
    if (same_str(set_name, "SETA"))
        return &( sets.SETA );
    else if (same_str(set_name, "SETB"))
        return &( sets.SETB );
    else if (same_str(set_name, "SETC"))
        return &( sets.SETC );
    else if (same_str(set_name, "SETD"))
        return &( sets.SETD );
    else if (same_str(set_name, "SETE"))
        return &( sets.SETE );
    else
        return &( sets.SETF );
}



void add_number(char *set_name, int n){
    int int_ix, bit_ix;
    set *s;

    s = get_set(set_name);

    /* Add 1 to n in order to store 0 value */
    n += 1;

    int_ix = n / 32;
    bit_ix = n % 32;

    *s[int_ix] |= (1 << (bit_ix-1));
}

void remove_number(char *set_name, int n){

    int int_ix, bit_ix;
    set *s;

    s = get_set(set_name);
    n += 1;

    int_ix = n / 32;
    bit_ix = n % 32;

    *s[int_ix] &= ~(1 << (bit_ix-1));
}

int search_number(char *set_name, int n){
    int int_ix, bit_ix;
    set *s;

    s = get_set(set_name);

    n += 1;

    int_ix = n / 32;
    bit_ix = n % 32;

    if ((*s[int_ix] & (1 << (bit_ix-1))) != 0)
        return 1;
    return 0;
}

void reset_set(set s){
    int i;
    for (i=0; i < ARR_SIZE; i++){
        s[i] = 0;
    }
}

void read_set(char *set_name, int *args, int args_num){
    set *s;

    s = get_set(set_name);

    /* Reset the set to create a new one */
    reset_set(*s);

    while (--args_num >= 0){
        add_number(set_name, *args++);
    }
}

void print_set(char *set_name){
    int i;
    int is_empty;
    int first;

    first = 1;
    is_empty = 1;

    for (i=0; i <= SET_SIZE; i++){

        /* Check if the number is in the set */
        /* TODO: loop through the bits. */
        if (search_number(set_name, i)){
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

void union_set(char *set1_name, char *set2_name, char *to_set_name){
    int ix;
    set *set1, *set2, *to_set;

    set1 = get_set(set1_name);
    set2 = get_set(set2_name);
    to_set = get_set(to_set_name);



    for (ix=0; ix <= ARR_SIZE; ix++){
        *to_set[ix] = *set1[ix] | *set2[ix];
    }
}

void intersect_set(char *set1_name, char *set2_name, char *to_set_name){
    int ix;
    set *set1, *set2, *to_set;

    set1 = get_set(set1_name);
    set2 = get_set(set2_name);
    to_set = get_set(to_set_name);

    for (ix=0; ix <= ARR_SIZE; ix++){
        *to_set[ix] = *set1[ix] & *set2[ix];
    }
}

void sub_set(char *set1_name, char *set2_name, char *to_set_name){
    int ix;
    set *set1, *set2, *to_set;

    set1 = get_set(set1_name);
    set2 = get_set(set2_name);
    to_set = get_set(to_set_name);

    for (ix=0; ix <= ARR_SIZE; ix++){
        *to_set[ix] = *set1[ix] & (~*set2[ix]);
    }
}

void symdiff_set(char *set1_name, char *set2_name, char *to_set_name){
    int ix;
    set *set1, *set2, *to_set;

    set1 = get_set(set1_name);
    set2 = get_set(set2_name);
    to_set = get_set(to_set_name);

    for (ix=0; ix <= ARR_SIZE; ix++){
        *to_set[ix] = *set1[ix] ^ *set2[ix];
    }
}

