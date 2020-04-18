#include "board.hpp"

using namespace std;

Board::Board(int s) : m_size(s) {
    m_grid = new Tile*[m_size];

    for(int i=0; i<m_size; i++) {
        m_grid[i] = new Tile[m_size];

        for(int j=0; j<m_size; j++) {
            m_grid[i][j] = Tile::EMPTY;
        }
    }
}

Board::~Board() {
    for(int i=0; i<m_size; i++) {
        delete[] m_grid[i];
    }

    delete[] m_grid;
}

int Board::size() {
    return m_size;
}

Board::Tile Board::tile(int x, int y) {
    if(x < 0 || x >= m_size || y < 0 || y >= m_size)
        return Tile::ERR;

    return m_grid[x][y];
}

Board::Tile Board::tile(Vector2D v) {
    return tile(v.x(), v.y());
}

void Board::setTile(Tile t, int x, int y) {
    if(x < 0 || x >= m_size || y < 0 || y >= m_size)
        return;

    m_grid[x][y] = t;
}

void Board::setTile(Tile t, Vector2D v) {
    setTile(t, v.x(), v.y());
}

Board::Tile** Board::grid() {
    return m_grid;
}

bool Board::isOut(Vector2D& v) {
    if(v.x() < 0 || v.x() >= m_size || v.y() < 0 || v.y() >= m_size)
        return true;

    return false;
}

void Board::print() {
    cout << "Grille de jeu :" << endl;

    for(int i=0; i<=m_size*2 + 1; i++)
        cout << '#';

    cout << endl;

    for(int i=0; i<m_size; i++) {
        cout << '#';

        for(int j=0; j<m_size; j++) {
            cout << toChar(m_grid[j][i]) << ' ';
        }

        cout << "#" << endl;
    }

    for(int i=0; i<=m_size*2 + 1; i++)
        cout << "#";

    cout << endl;
}

char Board::toChar(Board::Tile t) {
    return (char)t;
}