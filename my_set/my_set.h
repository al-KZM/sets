char * parse_operation(char *cmd, char *op, int max_len, int *status_code);

void stop(int code);

void print_error(int status_code);

int read_line(char **buf_ptr);

char * parse_operation(char *cmd, char *op, int max_len, int *status_code);

int init_operation_config(char *operation, int *operands_required_num, int *args_required);

int is_valid_operand(char *operand);

char * parse_operand(char *str, char *to, int *status_code);

char * goto_comma(char *str, int *comma_pos, int *status_code);

int has_consecutive_comma(char *str);

int isnumber(char *str);

int exec_cmd(char *cmd);
