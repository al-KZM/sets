/*
 *
 * Definition of the sets functions
 *
 */

#define SET_SIZE 127

/*
 *
 * A set is an unordered container of unique integers from 0 to n
 * In order to save memory, we try to simulate an array of n
 * bits, where each bit is a boolean value representing the
 * presence of the number in the set.
 *
 * To simulate this bit arrays, we use an array of integers,
 * one int is 4 bytes (32 bits), thus to store n bits we need
 * n/32 integers, this number is rounded up.
 *
 * To retrieve the position k of a bit in the array, we'll take the entire
 * part of k/32 to find the right integer and then use the remainder to find the
 * right bit within the 32 bits of the integer.
 *
 * Those operations will be wrapped by add_number, search_number and remove_number.
 *
 */
typedef int set[SET_SIZE];




