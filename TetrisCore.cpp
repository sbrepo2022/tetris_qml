#include "TetrisCore.h"

// private

const bool Field::figure[NUM_FIGURES][4][4] = {
        {{0,0,0,0},
         {0,1,1,0},
         {0,1,1,0},
         {0,0,0,0}},
        
        {{0,0,0,0},
         {0,0,0,0},
         {1,1,1,1},
         {0,0,0,0}},
        
        {{0,0,0,0},
         {1,1,0,0},
         {0,1,1,0},
         {0,0,0,0}},
        
        {{0,0,0,0},
         {0,1,1,1},
         {0,1,0,0},
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
	int num_lines = 0;
	for (int y = 0; y < HEIGHT; y++) {
		full = true;
        for (int x = 0; x < WIDTH; x++) {
            if (! field[y][x])
				full = false;
        }
		if (full) {
			num_lines++;
			deleteLine(y);
		}
    }
}

void Field::deleteLine(int num_line) {
	for (int y = num_line; y > 0; y++) {
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

void Field::print() {
    // create output field array
    char print_field[HEIGHT][WIDTH];
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (field[y][x])
                print_field[y][x] = FILLED_CELL;
            else
                print_field[y][x] = ' ';
        }
    }
    // add figure info to output array
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (getFigureCell(x, y, rotate))
                print_field[figure_y + y][figure_x + x] = FILLED_CELL;
        }
    }
    
    // print field
    std::cout << "+";
    for (int x = 0; x < WIDTH; x++) {
        std::cout << "-";
    }
    std::cout << "+\n";
        
    for (int y = 0; y < HEIGHT; y++) {
        std::cout << "|";
        for (int x = 0; x < WIDTH; x++) {
            std::cout << print_field[y][x];
        }
        std::cout << "|\n";
    }
    
    std::cout << "+";
    for (int x = 0; x < WIDTH; x++) {
        std::cout << "-";
    }
    std::cout << "+\n";
}

void Field::spawnFigure() {
    int type = rand() % 4;
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
        spawnFigure();
    }
    else {
        figure_y = pos_y;
    }
}

