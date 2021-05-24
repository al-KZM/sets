#define SET_SIZE 128
#define ARR_SIZE SET_SIZE/32

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
 * right bit within the 32 bits of the integer (starting from the right of the byte).
 *
 * Those operations will be wrapped by add_number, search_number and remove_number.
 *
 * In order to be able to store 0, we will add 1 to every value in the set, as the very first
 * value is 0.
 *
 */

typedef int set[ARR_SIZE];

/*
 * Return the set corresponding to <set_name>
 */
set *get_set(char *set_name);
void reset_set(set s);

/*
 *
 * Add or remove a number <n> from a set <s>
 *
 * The logic of this function is described in the documentation of the set typedef
 */
void add_number(char *set_name, int n);
void remove_number(char *set_name, int n);

/*
 * Return 1 if the number exists in the set else 0
 */
int search_number(char *set_name, int n);


/*
 * Output the content of the set to stdout
 */
void print_set(char *set_name);

/*
 * Adds an undefined number of arguments into a set
 */
void read_set(char *set_name, int *args, int args_num);

/*
 * The following function store the result of
 * the operation on <set1> and <set2> into <to_set>
 */

/*
 * Union: the set containing all elements that appear in set1 or set2
 */
void union_set(char *set1_name, char *set2_name, char *to_set_name);

/*
 * Intersect: the set containing all elements that appear in set1 and set2
 */
void intersect_set(char *set1_name, char *set2_name, char *to_set_name);

/*
 * Sub: the set containing all the elements that appear in set1 but not in set2
 */
void sub_set(char *set1_name, char *set2_name, char *to_set_name);

/*
 * Symdiff: the set containing all the elements that appear in only one of
 * set1 and set2
 */
void symdiff_set(char *set1_name, char *set2_name, char *to_set_name);



