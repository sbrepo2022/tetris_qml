#include "TetrisCore.h"

// private

const bool Field::figure[NUM_FIGURES][4][4] = {
        {{0,0,0,0},
         {0,1,1,0},
         {0,1,1,0},
         {0,0,0,0}},
        
        {{0,0,0,0},
         {1,1,1,1},
         {0,0,0,0},
         {0,0,0,0}},
        
        {{0,0,0,0},
         {1,1,0,0},
         {0,1,1,0},
         {0,0,0,0}},
        
        {{0,0,0,0},
         {0,1,1,1},
         {0,1,0,0},
         {0,0,0,0}},

        {{0,0,0,0},
         {0,0,1,1},
         {0,1,1,0},
         {0,0,0,0}},

        {{0,0,0,0},
         {1,1,1,0},
         {0,0,1,0},
         {0,0,0,0}}
};

bool Field::checkCollision(int figure_type, int figure_x, int figure_y, int rot) {
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            // check border collision
            if (figure_x + x < 0 || figure_y + y < 0 || figure_x + x >= WIDTH || figure_y + y >= HEIGHT) {
                if (getFigureCell(x, y, rot))
                    return true;
                else
                    continue;
            }
            
            // check collision with field cells
            if (field[figure_y + y][figure_x + x] && getFigureCell(x, y, rot))
                return true;
        }
    }
    return false;
}

int Field::checkLine() {
    bool full = false;
	for (int y = 0; y < HEIGHT; y++) {
		full = true;
        for (int x = 0; x < WIDTH; x++) {
            if (! field[y][x])
				full = false;
        }
		if (full) {
            lines_completed++;
			deleteLine(y);
		}
    }
}

void Field::deleteLine(int num_line) {
    for (int y = num_line; y > 0; y--) {
		for (int x = 0; x < WIDTH; x++) {
			field[y][x] = field[y - 1][x];
		}
	}
}

bool Field::getFigureCell(int x, int y, int rot) {
    switch (rot) {
        case 0:
            return figure[figure_type][y][x];
                    
        case 1:
            return figure[figure_type][x][3 - y];
                    
        case 2:
            return figure[figure_type][3 - y][3 - x];
                    
        case 3:
            return figure[figure_type][3 - x][y];
    }
}

// public

void Field::init() {
    game_over = false;
    rotate = 0;
    figure_x = figure_y = 0;
    
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            field[y][x] = 0;
        }
    }
    spawnFigure();
}

void Field::spawnFigure() {
    int type = rand() % NUM_FIGURES;
    int x = WIDTH / 2 - 1;
    int y = 0;
    int rot = 0;
    if (! checkCollision(type, x, y, rot)) {
        figure_type = type;
        figure_x = x;
        figure_y = y;
        rotate = rot;
    }
    else {
        game_over = true;
    }
}

void Field::turnLeft() {
    int rot = rotate;
    if (rot == 0)
        rot = 3;
    else
        rot--;
    if (! checkCollision(figure_type, figure_x, figure_y, rot))
        rotate = rot;
}

void Field::turnRight() {
    int rot = rotate;
    if (rot == 3)
        rot = 0;
    else
        rot++;
    if (! checkCollision(figure_type, figure_x, figure_y, rot))
        rotate = rot;
}

void Field::moveLeft() {
    int pos_x = figure_x;
    pos_x--;
    if (! checkCollision(figure_type, pos_x, figure_y, rotate))
        figure_x = pos_x;
}

void Field::moveRight() {
    int pos_x = figure_x;
    pos_x++;
    if (! checkCollision(figure_type, pos_x, figure_y, rotate))
        figure_x = pos_x;
}

void Field::next() {
    int pos_y = figure_y;
    pos_y++;
    if (checkCollision(figure_type, figure_x, pos_y, rotate)) {
        for (int y = 0; y < 4; y++) {
            for (int x = 0; x < 4; x++) {
                if (getFigureCell(x, y, rotate))
                    field[figure_y + y][figure_x + x] = 1;
            }
        }
        checkLine();
        spawnFigure();
    }
    else {
        figure_y = pos_y;
    }
}

QString Field::getFieldData() {
    bool print_field[HEIGHT][WIDTH];
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (field[y][x])
                print_field[y][x] = 1;
            else
                print_field[y][x] = 0;
        }
    }
    // add figure info to output array
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (getFigureCell(x, y, rotate))
                print_field[figure_y + y][figure_x + x] = 1;
        }
    }

    QString data;
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            print_field[y][x] ? data += "1" : data += "0";
        }
    }

    return data;
}
