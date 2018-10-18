//------------------------------------
// Tic-Tac-Toe (Noughts and Crosses)
//------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "tic-tac-toe.h"

#define INCLUDE_WINDOWS 0
#if INCLUDE_WINDOWS
    #include <windows.h>
#endif

int main(int argc, char **argv){
    int turn;
    int i, board_size;
    //int board[board_size][board_size] = {{SPACE}};
    int** board;
    
    board_size = (int)*argv[1];
    if((argc == 1) && (3 <= board_size && board_size <= 20)){
        board = (int**)malloc(sizeof(int)*board_size);
        for(i = 0; i < board_size; i++)
            board[i] = (int*)malloc(sizeof(int)*board_size);
    }else{
        printf("不正なコマンドライン引数");
        return 1;
    }

    game_init(&turn);
    board_disp(board);
    while(1){
        input_position(board, turn);
        change_turn(&turn);
        board_disp(board);
        if(judge(board)) break;
    }

    for(i = 0; i < board_size; i++)
        free(board[i]);
    free(board);
    return 0;
}

void game_init(int *turn){
    *turn = NOUGHT;
#if INCLUDE_WINDOWS
    system("cls");
    printf("  #######                #######                     #######              \n");
    printf("     #    #  ####           #      ##    ####           #     ####  ######\n");
    printf("     #    # #    #          #     #  #  #    #          #    #    # #     \n");
    printf("     #    # #      #####    #    #    # #      #####    #    #    # ##### \n");
    printf("     #    # #               #    ###### #               #    #    # #     \n");
    printf("     #    # #    #          #    #    # #    #          #    #    # #     \n");
    printf("     #    #  ####           #    #    #  ####           #     ####  ######\n");
    sleep(2);
#endif
}

void board_disp(int **board, int board_size){
    int i, j;
#if INCLUDE_WINDOWS
    system("cls");
#endif
    printf("y\\x");
    for(i = 0; i < board_size; i++)
        printf("| %2d", i);
    printf("|\n");
    for(i = 0; i < board_size; i++){
        printf("---");
        for(j = 0; j < board_size; j++)
            printf("+---");
        printf("+\n %2d",i);
        for(j = 0; j < board_size; j++){
            switch(board[i][j]){
            case SPACE : printf("|   "); break;
            case NOUGHT: printf("| o "); break;
            case CROSS : printf("| x "); break;
            }
        }
        printf("|\n");
    }
    printf("---");
    for(j = 0; j < board_size; j++)
        printf("+---");
    printf("+\n\n");
}

void input_position(int **board, int board_size, int turn){
    int position_x, position_y;

    printf("It's %s's turn.\nplease type position.(x y) : ", (turn == NOUGHT) ? "o" : "x");
    while(1){
        scanf("%d %d", &position_x, &position_y);
        if(check_position(position_x, position_y) && board[position_x][position_y] == SPACE)
            break;
        printf(" input error.\nplease retype position. : ");
    }
    //board[position_x][position_y] = turn;
    board[position_y][position_x] = turn;
}

int check_position(int board_size, int x, int y){
    return (0 <= x && x < board_size && 0 <= y && y < board_size);
}

void change_turn(int *turn){
    *turn = (*turn == NOUGHT) ? CROSS : NOUGHT;
}

int judge(int **board, int board_size){
    int i, j;

    for(i = 0; i < board_size; i++){
        for(j = 0; j < board_size; j++){
            if(board[i][j] == SPACE)
                continue;
            if(check_length(board, j, i)){
                printf("%s win!\n", (board[i][j] == NOUGHT) ? "o" : "x");
                return 1;
            }
        }
    }
    return 0;
}

int check_length(int **board, int board_size, int x, int y){
    int i, j, len_flag;
    int dx[] = { 0, 1, 1 };
    int dy[] = { 1, 0, 1 };

    for(i = 0; i < 3; i++){
        for(j = 1, len_flag = 1; j <= 4; j++){
            //printf("",board[y+j*dy[i]][x+j*dx[i]])
            if(board[y][x] != board[y+j*dy[i]][x+j*dx[i]]){
                len_flag = 0;
                break;
            }
        }
        if(len_flag == 1)
            return 1;
    }
    return 0;
}

