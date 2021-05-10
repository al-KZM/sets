


/*
 *
 * Add or remove a number <n> from a set <s>
 *
 * The logic of this function is described in the documentation of the set typedef
 */
void add_number(set s, int n);
void remove_number(set s, int n);

/*
 * Return 1 if the number exists in the set else 0
 */
int search_number(set s, int n);


/*
 * Output the content of the set to stdout
 */
void print_set(set s);

/*
 * Adds an undefined number of arguments into a set
 */
void read_set(set s, ...);

/*
 * The following function store the result of
 * the operation on <set1> and <set2> into <to_set>
 */

/*
 * Union: the set containing all elements that appear in set1 or set2
 */
void union_set(set set1, set set2, set to_set);

/*
 * Intersect: the set containing all elements that appear in set1 and set2
 */
void intersect_set(set set1, set set2, set to_set);

/*
 * Sub: the set containing all the elements that appear in set1 but not in set2
 */
void sub_set(set set1, set set2, set to_set);

/*
 * Symdiff: the set containing all the elements that appear in only one of
 * set1 and set2
 */
void symdiff_set(set set1, set set2, set to_set);



