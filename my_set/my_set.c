#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "set.h"

#define MAX_OP_LEN 30
#define LINE_BUFFER_CAPACITY 30
#define OPERAND_NAME_SIZE 4

#define SUCCESS_CODE 0
#define FAIL_CODE 1
#define EOF_CODE 2
#define END_OF_CMD_CODE 3
#define STOP_CODE 4


#define FAIL_CODE_INVALID_COMMA 10
#define FAIL_CODE_OP_OVERFLOW 12
#define FAIL_CODE_UNKNOWN_CMD 13
#define FAIL_CODE_CONSECUTIVE_COMMAS 14
#define FAIL_CODE_ILLEGAL_OPERAND_NAME 15
#define FAIL_CODE_INVALID_ARGUMENT 16
#define FAIL_CODE_BAD_ENDING_POS 17
#define FAIL_CODE_ARG_OUT_OF_RANGE 18
#define FAIL_CODE_TRAILING_COMMA 19
#define FAIL_CODE_NO_COMMA_FOUND 20
#define FAIL_CODE_NO_OPERANDS 21
#define FAIL_CODE_ILLEGAL_STOP 22
#define FAIL_CODE_OPERAND_NAME_TOO_SHORT 23
#define FAIL_CODE_EXPECTED_OPERAND 24
#define FAIL_CODE_NO_ENDING_CHAR 25
#define FAIL_CODE_UNEXPECTED_ARGUMENT 26
#define FAIL_CODE_UNEXPECTED_OPERAND 27
#define FAIL_CODE_INVALID_CHARACTER 28

#define same_str(s1, s2) (strcmp(s1, s2) == 0)


set SETA = {0};
set SETB = {0};
set SETC = {0};
set SETD = {0};
set SETE = {0};
set SETF = {0};


void stop(int code){
    exit(code);
}

void print_error(int status_code){
    switch (status_code){
        case FAIL_CODE_INVALID_COMMA:
            printf("Invalid comma.");
            break;
    }
}

set *get_set(char *set_name){
    if (same_str(set_name, "SETA"))
        return &SETA;
    else if (same_str(set_name, "SETB"))
        return &SETB;
    else if (same_str(set_name, "SETC"))
        return &SETC;
    else if (same_str(set_name, "SETD"))
        return &SETD;
    else if (same_str(set_name, "SETE"))
        return &SETE;
    else
        return &SETF;
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
    while ( isspace(*str++) )
        {}
    str--;

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

    if (has_consecutive_comma(str) == 1){
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

    /* Skip all the whitespaces */
    while ( isspace(*str++) ){}
    str--;

    for (i=0; i < OPERAND_NAME_SIZE; i++){
        if ( *str == '\0'){
            *status_code = END_OF_CMD_CODE;
            break;
        }

        if ( *str == ',' ){
            printf("Operand name too short: %s", to);
            *status_code = FAIL_CODE_OPERAND_NAME_TOO_SHORT;
            return NULL;
        }

        to[i] = *str++;
    }

    to[i] = '\0';

    if ( is_valid_operand(to) == 0 ){
        printf("Illegal operand name: <%s>\n", to);
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
        i++;
    }

    *op = '\0';

    return cmd;
}

int init_operation_config(char *operation, int *operands_required_num, int *args_required){
        if (same_str(operation, "stop"))
            return STOP_CODE;
        else if (same_str("read_set", operation)){
            *operands_required_num = 1;
            *args_required = 1;
        }
        else if (same_str("print_set", operation)){
            *operands_required_num = 1;
            *args_required = 0;
        }
        else if (
                same_str("union_set", operation) ||
                same_str("intersect_set", operation) ||
                same_str("sub_set", operation) ||
                same_str("symdiff_set", operation)
                ){
            *operands_required_num = 3;
            *args_required = 1;
        }
        else{
            return FAIL_CODE_UNKNOWN_CMD;
        }

        return SUCCESS_CODE;
}

int count_commas(char *str){
    int count = 0;
    char c;

    while ((c = *str++) != '\0'){
        if (c == ',') count++;
    }
    return count;
}

int exec_cmd(char *cmd){
    char c;
    int i, j;
    int status_code;
    char *str_ptr;

    char operation[MAX_OP_LEN];
    char operands[3][5];
    set *sets_operands[3];

    int number;
    int arguments_count;
    int *arguments;

    int comma_pos;

    int operands_required_num, args_required;

    status_code = 0;

    str_ptr = cmd;

    /*  Parse operation name */
    str_ptr = parse_operation(str_ptr, operation, MAX_OP_LEN, &status_code);
    if ( str_ptr == NULL )
        return status_code;

    if ( status_code == END_OF_CMD_CODE ){
        if ( same_str(operation, "stop") )
            stop(0);
        return FAIL_CODE_NO_OPERANDS;
    }

    /* If the operation is stop but the command is not empty */
    if ( same_str(str_ptr, "stop") ){
        return FAIL_CODE_ILLEGAL_STOP;
    }

    /* Initialize configuration flags for every operation */
    status_code = init_operation_config(operation, &operands_required_num, &args_required);
    if ( status_code != SUCCESS_CODE )
        return status_code;

    /* Parse the right number of operands */
    for (i=0; i < operands_required_num; i++){
        str_ptr = parse_operand(str_ptr, operands[i], &status_code);

        if (status_code == END_OF_CMD_CODE && i != operands_required_num-1)
            return FAIL_CODE_EXPECTED_OPERAND;

        sets_operands[i] = get_set(operands[i]);

        if (str_ptr == NULL)
            return status_code;

        str_ptr = goto_comma(str_ptr, &comma_pos, &status_code);
        if (str_ptr == NULL){
            if (i == operands_required_num - 1)
                break;
            if ( status_code == FAIL_CODE_NO_COMMA_FOUND )
                return FAIL_CODE_EXPECTED_OPERAND;
            else
                return status_code;
        }
    }

    /* Check if this command needs arguments */
    if ( args_required == 0 ){

        if (str_ptr != NULL && *str_ptr != '\0'){
            while ( *str_ptr++ == ' '){}

            if (*str_ptr == ',')
                return FAIL_CODE_TRAILING_COMMA;
            else if (isalpha(*str_ptr))
                return FAIL_CODE_UNEXPECTED_OPERAND;
            else if (isdigit(*str_ptr))
                return FAIL_CODE_UNEXPECTED_ARGUMENT;
            else
                return FAIL_CODE_INVALID_CHARACTER;
        }

        /* Execute the operation with the right operands */
        if (same_str(operation, "print_set"))
            print_set( *sets_operands[0] );
        else if (same_str(operation, "union_set"))
            union_set( *sets_operands[0], *sets_operands[1], *sets_operands[2] );
        else if (same_str(operation, "intersect_set"))
            intersect_set( *sets_operands[0], *sets_operands[1], *sets_operands[2]);
        else if (same_str(operation, "sub_set"))
            sub_set( *sets_operands[0], *sets_operands[1], *sets_operands[2] );
        else if (same_str(operation, "symdiff_set"))
            symdiff_set( *sets_operands[0], *sets_operands[1], *sets_operands[2] );
    }
    else{ /* Parse the arguments */

        /* Check how many arguments are at most in the string and initialize an array out of that */
        /* This number of argument doesn't count the last '-1' argument, thus we will
         * add it in the loop */
        arguments_count = count_commas(str_ptr);
        arguments = calloc(arguments_count, sizeof(int));

        for (i=0; i <= arguments_count; i++){
            /* Else go trough the string to next comma to parse the number */
            goto_comma(str_ptr, &comma_pos, &status_code);

            /* First, check if the number is -1 */
            if ( str_ptr[0] == '-' && str_ptr[1] == '1' ){
                if ( str_ptr[2] == '\0' ){
                    /* Gently exit the loop */
                    break;
                }

                if ( str_ptr[2] == ',' ) {
                    if ( str_ptr[3] == '\0' )
                        return FAIL_CODE_TRAILING_COMMA;
                    else
                        return FAIL_CODE_BAD_ENDING_POS;
                }
            }


            if (status_code == FAIL_CODE_NO_COMMA_FOUND)
                return FAIL_CODE_NO_ENDING_CHAR;

            number = 0;
            /* Parse number */
            for (j=0; j < comma_pos; j++){
                c = *str_ptr++;

                if (!isdigit(c)){
                    return FAIL_CODE_INVALID_ARGUMENT;
                }
                number *= 10;
                number += (int)(c)-48; /* remove 48 because 0 is at place 48 in the ascii table */
                if (number < 0 || number > 127)
                    return FAIL_CODE_ARG_OUT_OF_RANGE;
            }
            arguments[i] = number;
            /* Move after the comma */
            str_ptr++;

        } /* End of argument parsing */
        read_set( *sets_operands[0], arguments, arguments_count );

    }


    return SUCCESS_CODE;

}

int main(int argc, char *argv[]){
    char *line_ptr;
	int keep_running;
    int status_code;


	keep_running = 1;

	while (keep_running){
        line_ptr = (char *) calloc(LINE_BUFFER_CAPACITY, sizeof(char));

        printf("> ");
        read_line(&line_ptr);
        printf("\n");

        status_code = exec_cmd(line_ptr);
        printf("Returned: %d\n", status_code);
	}

	return 0;
}

/* int main(int argc, char *argv[]){ */
/*     set seta = {0}; */
/*     set setb = {0}; */
/*     set setc = {0}; */

/*     add_number(seta, 5); */
/*     add_number(seta, 120); */
/*     add_number(seta, 78); */
/*     add_number(seta, 1); */

/*     remove_number(seta, 78); */
/*     print_set(seta); */

/*     add_number(setb, 10); */
/*     add_number(setb, 20); */
/*     print_set(setb); */

/*     union_set(seta, setb, setc); */
/*     print_set(setc); */


/*     return 0; */

/* } */

