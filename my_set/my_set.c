#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "set.c"

#define MAX_OP_LEN 30
#define LINE_BUFFER_CAPACITY 30

#define SUCCESS_CODE 0
#define FAIL_CODE 1
#define EOF_CODE 2
#define END_OF_CMD_CODE 3
#define STOP_CODE 4


#define FAIL_CODE_INVALID_COMMA 10
#define FAIL_CODE_OP_OVERFLOW 12
#define FAIL_CODE_UNKNOWN_CMD 13

#define same_str(s1, s2) (strcmp(s1, s2) == 0)



struct ints_buffer{
    int arr[];
    int capacity;
    int elems;
}

struct ints_buffer * init_buffer()

void print_error(int status_code){
    switch (status_code){
        case FAIL_CODE_INVALID_COMMA:
            printf("Invalid comma.");
            break;
    }
}

/*
 *
 * A generic pointer is set to the 'str' attribute of <obj>.
 * If the structure is a linked list, the <current_list> pointer will be bound to the
 * address of the first node in order to move to the next node when needed.
 *
 *
 * During the user input, each character is added to the string array of the
 * data structure, if the number of characters exceeds the capacity of the array,
 * this one is extended and the loop continue.
 *
 * At the end, a \0 character is manually added to the end of the string. The whole raw input
 * should be contained in the buffer <obj>
 *
 * Linebreaks are ignored.
 *
 */
int read_line(char **buf_ptr){
    /*
     * running_ptr: runs over the chars in the array
     * alloc_count: number of reallocations applied to the buffer
     * str_count:
     */
    char *running_ptr, c;
    int str_count, alloc_count;

    running_ptr = *buf_ptr;

    str_count = 0;
    alloc_count = 1;


    while ( (c = getchar()) != EOF ){

        /* End of line \n */
        if (c == '\n' )
            return SUCCESS_CODE;
        if (c == EOF)
            return EOF_CODE;

        /* Assign the current_list character to the inputted one */
        *running_ptr++ = c;
        str_count++;

        /* If the str_count excess the maximum capacity of the buffer */
        if (str_count >= LINE_BUFFER_CAPACITY){
            /* allocate more memory to the buffer array */

            *buf_ptr = (char *) realloc(*buf_ptr, LINE_BUFFER_CAPACITY*++alloc_count);

            /* Check for fail, if so, exit the function */
            if (*buf_ptr == NULL){
                *(running_ptr-1) = '\0';
                return FAIL_CODE;
            }

            /* Reinitialize str_count */
            str_count = 0;
        }
    }
    *running_ptr = '\0';
    return 0;
}

int is_valid_operand(char *operand){
    if (
            same_str(operand, "SETA") ||
            same_str(operand, "SETB") ||
            same_str(operand, "SETC") ||
            same_str(operand, "SETD") ||
            same_str(operand, "SETE") ||
            same_str(operand, "SETF")
        )
        return 1;
    return 0;
}

int has_consecutive_comma(char *str){
    while ( *str++ == ' ')
        {}

    if (*str == ',')
        return 1;

    return 0;

}

char * goto_comma(char *str, int *comma_pos, int *status_code){
    char c;
    int i;

    *status_code = SUCCESS_CODE;
    i=0;
    while ( (c = *str++) != ','){
        if (c == '\0'){
            *status_code = FAIL_CODE_NO_COMMA_FOUND;
            return NULL;
        }
        i++;
    }

    if (has_consecutive_comma(str)){
        *status_code = FAIL_CODE_CONSECUTIVE_COMMAS;
        return NULL;
    }

    if (comma_pos != NULL){
        *comma_pos = i;
    }

    return str;

}

char * parse_operand(char *str, char *to, int *status_code){
    int i;

    *status_code = SUCCESS_CODE;

    for (i=0; i < OPERAND_NAME_SIZE; i++){
        if ( !(isalpha(*str)) ){
            *status_code = FAIL_CODE_ILLEGAL_OPERAND_NAME;
            return NULL;
        }

        *to++ = *str++;
    }

    if (!is_valid_operand(to)){
        *status_code = FAIL_CODE_ILLEGAL_OPERAND_NAME;
        return NULL;
    }

    return str;
}

char * parse_operation(char *cmd, char *op, int max_len, int *status_code){
    char c;
    int i;

    *status_code = SUCCESS_CODE;

    i = 0;
    while ( (c = *cmd++) != ' '){

        if (c == '\0'){
            *status_code = END_OF_CMD_CODE;
            break;
        }

        /* Errors: */

        if (i >= max_len-1){
            *status_code = FAIL_CODE_OP_OVERFLOW;
            return NULL;
        }


        if (c == ','){
            *status_code = FAIL_CODE_INVALID_COMMA;
            return NULL;
        }

        *op++ = c;
    }

    *op = '\0';

    return cmd;
}

int init_operation_config(char *operation, int *operands_required_num, int *args_required){
        if (same_str(command, "stop"))
            return STOP_CODE;
        else if (same_str("read_set", command)){
            *operands_required_num = 1;
            *args_required = 1;
        }
        else if (same_str("print_set", command)){
            *operands_required_num = 1;
            *args_required = 0;
        }
        else if (
                same_str("union_set", command) ||
                same_str("intersect_set", command) ||
                same_str("sub_set", command) ||
                same_str("symdiff_set", command)
                ){
            *operands_required_num = 3;
            *args_required = 1;
        }
        else{
            return FAIL_CODE_UNKNOWN_CMD;
        }

        return SUCCESS_CODE;
}

int add_int_to_arr(int arr[], int val){

}

int exec_cmd(char *cmd){
    char c;
    int i;
    int status_code;
    char *str_ptr;

    char operation[MAX_OP_LEN];
    char operands[3][4];
    char operand[4];

    int arguments[5];

    int comma_pos;

    int operands_required_num, args_required;

    status_code = 0;

    str_ptr = cmd;

    /*  Parse operation name */
    str_ptr = parse_operation(str_ptr, operation, MAX_OP_LEN, &status_code);

    /* Initialize configuration flags for every operation */
    status_code = init_operation_config(operation, &operands_required_num, &args_required);

    /* Parse the right number of operands */
    for (i=0; i < operands_required_num; i++){
        str_ptr = parse_operand(str_ptr, operands[i], &status_code);
        str_ptr = goto_comma(str_ptr, &comma_pos, &status_code);
    }

    /* Check if this command needs arguments */
    if ( args_required == 0 ){
        /* Execute the operation with the right operands */
    }
    else{
        /* Parse the arguments */
    }


    return SUCCESS_CODE;

}

int main(int argc, char *argv[]){
    char *line_ptr;
	int keep_running;
	char c;
	char command[30], set1[4], set2[4], set3[4];
    int status_code;

	keep_running = 1;

	while (keep_running){
        line_ptr = (char *) calloc(LINE_BUFFER_CAPACITY, sizeof(char));

        printf("> ");
        read_line(&line_ptr);
        printf("\n");

        status_code = exec_cmd(line_ptr);
        if (status_code != SUCCESS_CODE)
            print_error(status_code);

	}

	return 0;
}


