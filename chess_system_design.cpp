using namespace std;

class block {
    int x;
    int y;
    piece * p;
    public:
        block(int x, int y)
        {
            this->x = x;
            this->y = y;
            this->p = NULL;
        }
};

class player {
    private:
        bool iswhite;
        bool isturn;
};

class piece {
    private:
        bool is_white;
        bool is_alive;

    public:
        piece ()
        {
            this->is_white = true;
            this->is_alive = true;
        }
        void set_is_white(bool is_white)
        {
            this->is_white = is_white;
        }
        bool get_is_white()
        {
            return is_white;
        }
        virtual bool can_move(block start, block end) = 0;
};


class king extends piece {
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

class queen extends piece {
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

class game {
    board block[8][8];
    player p1;
    player p2;
    int status;
    int turn;
    bool make_move(player p, block b1, block b2)
    {
        if (player p.isturn == false)
        {
            cout << "Invalid Move" << '\n';
            return;
        }

        if (b1.peice == NULL)
        {
            cout << "Invalid Move" << '\n';
            return;
        }

        if (b1.peice.can_move(b1, b2) == false)
        {
            cout << "Invalid Move" << '\n';
            return false;
        }

        if (b2.piece.iswhite == NULL)
        {
            b1.piece = NULL;
            b2.piece = p;
        }

        if (b2.piece.iswhite == p.iswhite)
        {
            cout << "Invalid Move" << '\n';
            return false;
        }
        else
        {
            b1.piece = NULL;
            b2.piece.is_alive = false;
            b2.piece = p;
        }

    }
};