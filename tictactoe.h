#ifndef _TIC_TAC_TOR_H_
#define _TIC_TAC_TOR_H_

#define BOARD_SIZE      3
#define CHESS_X         'X'
#define CHESS_O         'O'

const int MAX_CHESS_NUM = (BOARD_SIZE * BOARD_SIZE);

class POS
{
public:
    POS()
    {
        r = l = 0;
    }

    POS(int _r, int _l)
    {
        r = _r;
        l = _l;
    }

    int r, l;
};

enum STATE
{
    NOT_STARTED,
    PLAYER_TURN,
    AI_TURN,
    GAME_OVER
};

enum RESULT
{
    NO_RESULT,
    PLAYER_WIN,
    AI_WIN,
    DRAW
};

class TicTacToe
{
private:
    char   board[BOARD_SIZE][BOARD_SIZE];
    STATE  state;
    RESULT result;
    char   playerChess, AIChess;
    int    chessCount;

public:
    TicTacToe()
    {
        state = NOT_STARTED;
    }

    void init(int firstHand)
    {
        result = NO_RESULT;
        chessCount = 0;

        for (int i = 0; i < BOARD_SIZE; ++i)
        {
            for (int j = 0; j < BOARD_SIZE; ++j)
            {
                board[i][j] = 0;
            }
        }

        board[0][0] = board[0][2] = board[1][0] = board[1][1] = 'O';
        board[0][1] = board[1][2] = board[2][0] = 'X';

        printMap();
        chessCount = 7;
        if (firstHand == 1)
        {
            state = PLAYER_TURN;
        }

        // playerChess = (random(2) == 0 ? CHESS_O : CHESS_X);
        playerChess = CHESS_O;
        AIChess     = (playerChess == CHESS_O ? CHESS_X : CHESS_O);
    }

    bool putChess(char chess, int row, int col)
    {
        if (board[row][col] != 0)
            return false;

        board[row][col] = chess;
        ++chessCount;
        return true;
    }

    void playerPutChess()
    {
        POS pos;

        pos = getInput();
        if (pos.r == -1)
            return;

        if (! putChess(playerChess, pos.r, pos.l))
            return;

        state = AI_TURN;
        if (checkWin(pos.r, pos.l))
        {
            state = GAME_OVER;
            result = PLAYER_WIN;
            return;
        }

        if (checkGameOver())
        {
            state = GAME_OVER;
            result = DRAW;
        }
    }

    void AIPutChess()
    {
        POS pos;

        pos = getAIMove();
        if (pos.r == -1)
            return;

        if (! putChess(AIChess, pos.r, pos.l))
            return;

        state = PLAYER_TURN;
        if (checkWin(pos.r, pos.l))
        {
            state = GAME_OVER;
            result = AI_WIN;
            return;
        }

        if (checkGameOver())
        {
            state = GAME_OVER;
            result = DRAW;
        }
    }

    // 先实现 AI 随机走，功能完成了再做算法
    POS getAIMove()
    {
        int pos;
        int r, l;
        for (int i = 0; i < 100; ++i)
        {
            pos = random(9);
            r = pos / BOARD_SIZE;
            l = pos % BOARD_SIZE;
            if (board[r][l] == 0)
            {
                break;
            }
        }

        return POS(r, l);
    }

    POS getInput()
    {
        int r = 0;
        int l = 0;
        int pos = 0;

        r = pos / BOARD_SIZE;
        l = pos % BOARD_SIZE;

        return POS(r, l);
    }

    bool checkWin(int row, int col)
    {
        if (board[row][0] == board[row][1] && board[row][0] == board[row][2])
            return true;

        if (board[0][col] == board[1][col] && board[0][col] == board[2][col])
            return true;

        if (board[1][1] != board[row][col])
            return false;

        if (board[0][0] == board[1][1] && board[0][0] == board[2][2])
            return true;

        if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
            return true;

        return false;
    }

    bool checkGameOver()
    {
        if (chessCount >= MAX_CHESS_NUM)
        {
            return true;
        }

        return false;
    }


    void printMap()
    {
#if 0
        cout << "-------------------------"<< endl;
        for (int i = 0; i < BOARD_SIZE; ++i)
        {
            for (int j = 0; j < BOARD_SIZE; ++j)
            {
                cout << (board[i][j] == 0 ? '_' : board[i][j]) << " ";
            }
            cout << endl;
        }
        cout << "state: " << state << endl;
        cout << "result : " << result << endl;
        cout << endl;
#endif
    }

    void gameLoop()
    {
        int r, l;

        switch (state)
        {
            case GAME_OVER:
            case NOT_STARTED:
                break;

            case PLAYER_TURN:
                playerPutChess();
                printMap();
                break;

            case AI_TURN:
                AIPutChess();
                printMap();
                break;
        }
    }
};

#endif
