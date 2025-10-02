using namespace std;

class Block {
    int x;
    int y;
    Piece * p;
    public:
        Block(int x, int y)
        {
            this->x = x;
            this->y = y;
            this->p = NULL;
        }
        piece * getPiece ()
        {
            return this->p;
        }
        void setPiece (piece *p)
        {
            this->p = p;
        }
};

class Player {
    private:
        bool iswhite;
        bool isturn;
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


class king extends Piece {
    public:
        bool can_move(block b1, block b2) override {
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

class queen extends Piece {
    public:
        bool can_move(block b1, block b2) override {
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
    Block Board[8][8];
    Player p1;
    Player p2;
    GameStatus status;
    int turn;
    bool makeMove(Player p, Block b1, Block b2)
    {
        if (Player p.isturn == false)
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
};