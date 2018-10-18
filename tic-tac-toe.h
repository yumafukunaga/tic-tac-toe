#define BOARD_SIZE 15
#define SPACE 0
#define NOUGHT 1
#define CROSS 2

void game_init(int *turn);
void board_disp(int **board, int board_size);
void input_position(int **board, int board_size, int turn);
int check_position(int board_size, int x, int y);
void change_turn(int *turn);
int judge(int **board, int board_size);
int check_length(int **board, int board_size, int x, int y);

