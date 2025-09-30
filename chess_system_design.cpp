class block {
    int x;
    int y;
    public:
        block(int x, int y)
        {
            this->x = x;
            this->y = y;
        }
};

class player {
    private:
        bool iswhite;
};



class Piece {
    private:
        bool iswhite;

    public:
        virtual bool can_move(block start, block end) = 0;
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