#include <ctime>
#include <cstdlib>
#include <QString>

class Field {
private:
    static const int WIDTH = 20, HEIGHT = 20;
    static const int NUM_FIGURES = 6;
    static const bool figure[NUM_FIGURES][4][4];
    
    static const char FILLED_CELL = '#';
    
    bool field[HEIGHT][WIDTH];
    // figure settings
    int figure_type;
    int figure_x, figure_y;
    int rotate;
    // cycle settings
    bool game_over;
    // game data
    int lines_completed;
    
    // inside functions
    bool checkCollision(int figure_type, int figure_x, int figure_y, int rot); // +
	int checkLine();
	void deleteLine(int num_line);
    bool getFigureCell(int x, int y, int rot); // +
    
public:
    Field() {srand(time(NULL));}
    void init(); // +
    void spawnFigure(); // +
    void turnLeft(); // +
    void turnRight(); // +
    void moveLeft(); // +
    void moveRight(); // +
    void next(); // +
    bool isGameOver() {return game_over;}

    QString getFieldData();
    int width() {return WIDTH;}
    int height() {return HEIGHT;}
    int linesCompleted() {return lines_completed;}
};
