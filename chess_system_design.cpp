#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

class Block {
    int x;
    int y;
    Piece* PiecePtr;
    public:
        Block(int x, int y, Piece* peice)
        {
            this->x = x;
            this->y = y;
            this->p = peice;
        }
        Piece * getPiece()
        {
            return this->p;
        }
        void setPiece (Piece *p)
        {
            this->p = p;
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
        bool isturn;

    public:
        Player() = delete;

        Player(bool iswhite, bool isturn)
        {
            iswhite = this->iswhite;
            isturn = this->isturn;
        }
    
    friend Game;
};

class Piece {
    private:
        bool isWhite;
        bool isAlive;

    public:
        Piece ()
        {
            this->isWhite = true;
            this->isAlive = true;
        }
        void setIsWhite(bool is_white)
        {
            this->isWhite = is_white;
        }
        bool getIsWhite()
        {
            return isWhite;
        }
                bool getIsAlive()
        {
            return isAlive;
        }
        void setIsAlive(bool alive)
        {
            this->isAlive = alive;
        }
        virtual bool can_move(Block start, Block end) = 0;
};


class King: public Piece {
    public:
        bool can_move(Block b1, Block b2) {
            if ((b1.x - b2.x) <= 1 && (b1.y - b2.y) <= 1)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
};

class Queen: public Piece {
    public:
        bool can_move(Block b1, Block b2) {
            if (((b1.x - b2.x) == (b1.y - b2.y)) || (b1.x - b2.x) == 0 || (b1.y - b2.y) == 0)
            {
                return true;
            }
            else
            {
                return false;
            }
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
    Player p1;
    Player p2;
    GameStatus status;
    int turn;
    mutex mtx;


    Game() {
        turn = 0;
        Player p1 = Player(true, true);
        Player p2 = Player(false, false);

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                Board[i][j] = Block(i, j, NULL);
            }
        }

    }


    bool makeMove(Player p, Block b1, Block b2)
    {
        if (p.isturn == false)
        {
            cout << "Invalid Move" << '\n';
            return;
        }

        if (b1.p == NULL)
        {
            cout << "Invalid Move" << '\n';
            return;
        }

        if (b1.p.can_move(b1, b2) == false)
        {
            cout << "Invalid Move" << '\n';
            return false;
        }

        if (b2.p.iswhite == NULL)
        {
            b1.setPiece(NULL);
            b2.setPiece(p);
        }

        if (b2.p.iswhite == p.iswhite)
        {
            cout << "Invalid Move" << '\n';
            return false;
        }
        else
        {
            b1.p = NULL;
            b2.p.is_alive = false;
            b2.p = p;
        }
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