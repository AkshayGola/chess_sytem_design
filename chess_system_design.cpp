#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

class Block {
    int x;
    int y;
    Piece* PiecePtr;
    public:
        Block(int x, int y, Piece* peice) {
            this->x = x;
            this->y = y;
            this->PiecePtr = peice;
        }

        Piece* getPiecePtr() {
            return this->PiecePtr;
        }

        void setPiecePtr(Piece *peice) {
            this->PiecePtr = peice;
        }

        int getx() {
            return this->x;
        }

        int gety() {
            return this->y;
        }
};

class Player {
    private:
        bool iswhite;

    public:
        Player() = delete;

        Player(bool iswhite) {
            iswhite = this->iswhite;
        }
    
    friend Game;
};


class canMoveStrategy {
    public:
        virtual bool can_move(Block start, Block end) = 0;
};

class canMoveKingStrategy: public canMoveStrategy {
    bool can_move(Block start, Block end) {

    }
};

class canMoveQueenStrategy: public canMoveStrategy {
    bool can_move(Block start, Block end) {

    }
};

class canMoveKnightStrategy: public canMoveStrategy {
    bool can_move(Block start, Block end) {

    }
};

class canMoveBishopStrategy: public canMoveStrategy {
    bool can_move(Block start, Block end) {

    }
};

class canMoveRookStrategy: public canMoveStrategy{
    bool can_move(Block start, Block end) {

    }
};

class canMovePawnStrategy: public canMoveStrategy {
    bool can_move(Block start, Block end) {

    }
};


class Piece {
    private:
        bool isWhite;
        bool isAlive;
        string PieceType;

    public:
        Piece () {
            this->isWhite = true;
            this->isAlive = true;
        }

        void setIsWhite(bool is_white) {
            this->isWhite = is_white;
        }

        bool getIsWhite() {
            return isWhite;
        }

        bool getIsAlive() {
            return isAlive;
        }

        void setIsAlive(bool alive) {
            this->isAlive = alive;
        }

        string getPieceType() {
            return this->PieceType;
        }

        virtual bool can_move(Block start, Block end) = 0;
};


class King: public Piece {
    public:
        bool can_move(Block b1, Block b2) {
            canMoveStrategy* MoveStrategy = new canMoveKingStrategy;
            return MoveStrategy->can_move(b1, b2);
        }
};

class Queen: public Piece {
    public:
        bool can_move(Block b1, Block b2) {
            canMoveStrategy* MoveStrategy = new canMoveQueenStrategy;
            return MoveStrategy->can_move(b1, b2);
        }
};


class Bishop: public Piece {
    public:
        bool can_move(Block b1, Block b2) {
            canMoveStrategy* MoveStrategy = new canMoveBishopStrategy;
            return MoveStrategy->can_move(b1, b2);
        }
};

class Knight: public Piece {
    public:
        bool can_move(Block b1, Block b2) {
            canMoveStrategy* MoveStrategy = new canMoveKnightStrategy;
            return MoveStrategy->can_move(b1, b2);
        }
};

class Rook: public Piece {
    public:
        bool can_move(Block b1, Block b2) {
            canMoveStrategy* MoveStrategy = new canMoveRookStrategy;
            return MoveStrategy->can_move(b1, b2);
        }
};

class Pawn: public Piece {
    public:
        bool can_move(Block b1, Block b2) {
            canMoveStrategy* MoveStrategy = new canMovePawnStrategy;
            return MoveStrategy->can_move(b1, b2);
        }
};

enum GameStatus {
    ACTIVE,
    BLACK_WIN,
    WHITE_WIN
};

class Game {
    static Game* gamePtr;
    Block Board[8][8];
    Player player[2];
    GameStatus status;
    int turn;

    Game() {
        turn = 0;
        player[0] = new Player(true);
        player[1] = new Player(false);

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                Board[i][j] = Block(i, j, NULL);
            }
        }
    }


    bool makeMove(int playerInd, Block b1, Block b2)
    {
        if (status != ACTIVE) {
            cout << "Game Over!!" << '\n';
            return;
        }

        if (playerInd != turn) {
            cout << "Invalid Move" << '\n';
            return;
        }

        if (b1.getPiecePtr() == NULL) {
            cout << "Invalid Move" << '\n';
            return;
        }

        if (b1.getPiecePtr()->can_move(b1, b2) == false) {
            cout << "Invalid Move" << '\n';
            return false;
        }

        if (b1.getPiecePtr()->getIsWhite() == b2.getPiecePtr()->getIsWhite()) {
            cout << "Invalid Move" << '\n';
            return false;
        }


        if (b2.getPiecePtr() != nullptr) {
            b2.getPiecePtr()->setIsAlive(false);
            if(b2.getPiecePtr()->getPieceType() == "King") {
                if (b1.getPiecePtr()->getIsWhite() == true) {
                    cout << "White WINS!!";
                    status = WHITE_WIN;
                }
                else {
                    cout << "Black WINS!!";
                    status = BLACK_WIN;
                }
            }
        }
        b2.setPiecePtr(b1.getPiecePtr());
        b1.setPiecePtr(nullptr);

        turn = turn++;
        turn%2;
    }


    public:
    Game(Game const & game) = delete;
    Game& operator =(Game const & game) = delete;

    Game* getGame() {
        if (gamePtr == NULL) {
            this->gamePtr = new Game();
        } 
        else {
            return gamePtr;
        }
    }
};