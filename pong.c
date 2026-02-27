#include<stdio.h>

#define FIELD_WIDTH 80
#define FIELD_HEIGHT 25
#define PADDLE_SIZE 3
#define PLAYER1_UP 'w'
#define PLAYER1_DOWN 's'
#define PLAYER2_UP 'e'
#define PLAYER2_DOWN 'd'
#define MAX_SCORE 2;
#define GREEN "\033[32m"
#define RESET "\033[0m"

int left_right_movement = 1;
int up_down_movement = 1;
int player_turn = 1;
int player1_score = 0;
int player2_score = 0;

int BallPositionChangeX(int left_paddle_position, int right_paddle_position, int ball_position_X, int ball_position_Y) {
    switch (ball_position_X)
    {
    case 3:
        if (ball_position_Y >= left_paddle_position && ball_position_Y <= left_paddle_position + PADDLE_SIZE - 1)
        {
            left_right_movement = 1;
        }
        break;
    case FIELD_WIDTH - 3:
        if (ball_position_Y >= right_paddle_position && ball_position_Y <= right_paddle_position + PADDLE_SIZE - 1)
        {
            left_right_movement = 0;
        }
    
    default:
        break;
    }
    
    return left_right_movement ? ball_position_X + 1 : ball_position_X - 1;
}
int BallPositionChangeY(int ball_position_X, int ball_position_Y)
{

    return ball_position_Y;
}

void PrintField(int left_paddle_position, int right_paddle_position, int ball_position_X, int ball_position_Y) {
    int tempLeft = 0;
    int tempRight = 0;
    for (int i = 0; i < FIELD_HEIGHT; i++) {
        for(int j = 0; j < FIELD_WIDTH; j++) {
            
            if (j == ball_position_X  && i == ball_position_Y) {
                printf("⬤");
                continue;
            }
            if  (i == 0 || i == FIELD_HEIGHT - 1) {
                putchar('-');
                continue;
            }
            if (j == FIELD_WIDTH / 2 + 1) {
                putchar('|');
                continue;
            }
            if(j == 2 && left_paddle_position  <= i && tempLeft < PADDLE_SIZE) {
                putchar('|');
                tempLeft++;
                j++;
            }
            if(j == FIELD_WIDTH - 2 && right_paddle_position <= i && tempRight < PADDLE_SIZE) {
                putchar('|');
                tempRight++;
                j++;
            }
            putchar(' ');
        }
        putchar('\n');
    }
    
    if (player_turn) {
        
        printf("\t\t"GREEN"Player1"RESET"\t\t\t\t\tPlayer2\n");
    }
    else {
        printf("\t\tPlayer1\t\t\t\t\t"GREEN"Player2"RESET"\n");
    }
    player_turn = player_turn ? 0 : 1;
    printf("Controls:\t  %c/%c\t\t\t\t\t  %c/%c\n", PLAYER1_UP, PLAYER1_DOWN, PLAYER2_UP, PLAYER2_DOWN);

}


void clear_screen() {
    printf("\033[2J");
    printf("\033[H");
}


int main() {
    int left_paddle_position = FIELD_HEIGHT / 2 - 1;    //Начальная позиция левой платформы
    int right_paddle_position = FIELD_HEIGHT /  2 - 1;  //Начальная позиция правой платформы
    int ball_position_X = FIELD_WIDTH / 2 + 1;          //Начальная позиция шара по оси X
    int ball_position_Y = FIELD_HEIGHT / 2;             //Начальная позиция шара по оси Y
    PrintField(left_paddle_position, right_paddle_position, ball_position_X, ball_position_Y);  //Вывод поля с объектами на начальных позициях
    char command_char = ' ';
    while ((command_char = getchar()) != 'n')   //Регистрация ввода символа
    {
        switch (command_char)   //Проверка на тип символа
        {
        case PLAYER1_DOWN:
            if(left_paddle_position < FIELD_HEIGHT - PADDLE_SIZE - 1)left_paddle_position++;    //Проверка не выходит ли наша платформа за пределы нижней границы
            ball_position_X = BallPositionChangeX(left_paddle_position, right_paddle_position, ball_position_X, ball_position_Y);   //Изменение позиции шара по оси Х
            clear_screen(); //Очистка экрана
            PrintField(left_paddle_position, right_paddle_position, ball_position_X, ball_position_Y); //Вывод поля с обновленными позициями объектов
            break;
        case PLAYER1_UP:
            if(left_paddle_position > 1)left_paddle_position--; //Проверка не выходит ли платформа за пределы верхней границы
            ball_position_X = BallPositionChangeX(left_paddle_position, right_paddle_position, ball_position_X, ball_position_Y);
            clear_screen();
            PrintField(left_paddle_position, right_paddle_position, ball_position_X, ball_position_Y);
            break;
        case PLAYER2_DOWN:
            if(right_paddle_position < FIELD_HEIGHT - PADDLE_SIZE - 1)right_paddle_position++;
            ball_position_X = BallPositionChangeX(left_paddle_position, right_paddle_position, ball_position_X, ball_position_Y);
            clear_screen();
            PrintField(left_paddle_position, right_paddle_position, ball_position_X, ball_position_Y);
            break;
        case PLAYER2_UP:
            if(right_paddle_position > 1)right_paddle_position--;
            ball_position_X = BallPositionChangeX(left_paddle_position, right_paddle_position, ball_position_X, ball_position_Y);
            clear_screen();
            PrintField(left_paddle_position, right_paddle_position, ball_position_X, ball_position_Y);
            break;
        case ' ':
            ball_position_X = BallPositionChangeX(left_paddle_position, right_paddle_position, ball_position_X, ball_position_Y);
            clear_screen();
            PrintField(left_paddle_position, right_paddle_position, ball_position_X, ball_position_Y);
            break;
        default:
            break;
        }
    }
    
    return 0;
}