#include "game.hpp"

using namespace std;

Game::Game(int gridSize, std::vector<Vector2D> replayFruits) : m_board(gridSize), m_score(0), m_moves(0), m_movesLeft(100), m_isDead(false), m_isReplay(false) {
    Vector2D head;
    head.setX(gridSize/2);
    head.setY(gridSize/2);

    m_snake.push(head + Vector2D(gridSize/2, gridSize/2 -3));
    m_snake.push(head + Vector2D(gridSize/2, gridSize/2 -2));
    m_snake.push(head + Vector2D(gridSize/2, gridSize/2 -1));
    m_snake.push(head);
    m_board.setTile(Board::Tile::SNAKE_HEAD, head);

    if(!replayFruits.empty()) {
        m_fruitPos = replayFruits;
        m_isReplay = true;
    }
    generateFruit();
}

int Game::gridSize() {
    return m_board.size();
}

Board::Tile** Game::grid() {
    return m_board.grid();
}

int Game::score() {
    return m_score;
}

int Game::moves() {
    return m_moves;
}

int Game::movesLeft() {
    return m_movesLeft;
}

double Game::fitness() {
    double fitness;

    fitness = double(m_moves) * double(m_moves) * double(pow(3, m_score))/1000;

    return fitness;
}

Game::Direction Game::headDirection() {
    return m_headDirection;
}

bool Game::isDead() {
    return m_isDead;
}

Vector2D Game::snakeHead() {
    return Vector2D(m_snake.back());
}

Vector2D Game::fruit() {
    return m_fruit;
}

void Game::move(Direction dir) {
    if(m_isDead)
        return;

    if(m_movesLeft <= 0) {
        m_isDead = true;
        return;
    }
    
    Vector2D dirVector;
    m_headDirection = dir;

    if(dir == Direction::UP) dirVector = Vector2D(0, -1);
    else if(dir == Direction::RIGHT) dirVector = Vector2D(1, 0);
    else if(dir == Direction::DOWN) dirVector = Vector2D(0, 1);
    else if(dir == Direction::LEFT) dirVector = Vector2D(-1, 0);

    Vector2D newPos(m_snake.back());
    newPos += dirVector;
    
    if(newPos.x() < 0 || newPos.x() >= m_board.size() || newPos.y() < 0 || newPos.y() >= m_board.size()) {
        m_isDead = true;
        return;
    }

    m_board.setTile(Board::Tile::SNAKE_BODY, Vector2D(m_snake.back()));

    switch (m_board.tile(newPos)) {
    case Board::Tile::SNAKE_HEAD:
    case Board::Tile::SNAKE_BODY:
    case Board::Tile::WALL:
        m_isDead = true;
        return;
        break;
    
    case Board::Tile::FRUIT:
        m_snake.push(newPos);

        m_score++;
        m_movesLeft += 100;
        if(m_movesLeft > 300)
            m_movesLeft = 200;

        generateFruit();
        break;

    case Board::Tile::EMPTY:
        m_board.setTile(Board::Tile::EMPTY, Vector2D(m_snake.front()));

        m_movesLeft--;
        m_snake.push(newPos);
        m_snake.pop();
        break;

    case Board::Tile::ERR:
    default:
        std::cout << "[WARNING] Unknown next tile";
        break;
    }

    m_moves++;
    m_board.setTile(Board::Tile::SNAKE_HEAD, newPos);
}

void Game::generateFruit() {
    if(m_isReplay) {
        m_fruit = m_fruitPos[m_score];
    } else {
        do {
            m_fruit.setX(std::rand() % m_board.size());
            m_fruit.setY(std::rand() % m_board.size());
        } while(m_board.tile(m_fruit) == Board::Tile::SNAKE_HEAD || m_board.tile(m_fruit) == Board::Tile::SNAKE_BODY);

        m_fruitPos.push_back(m_fruit);
    }

    m_board.setTile(Board::Tile::FRUIT, m_fruit);
}

float Game::distThreshold(int dist) {
    if(dist > 5)
        return 0;

    return (float)(5 - dist)/5;
}

Vector Game::inputVector() {
    Vector v(24);
    Vector2D head = this->snakeHead();

    int cpt = 0;
    Vector2D direction[8];
    
    for(int i=-1; i<=1; i++) {
        for(int j=-1; j<=1; j++) {
            if(i != 0 || j != 0) {
                direction[cpt] = Vector2D(i, j);
                cpt++;
            }
        }
    }

    for(int i=0; i<8; i++) {
        Vector2D newPos = head + direction[i];

        int wallStep = 1;
        int tailStep = 0;
        int fruitStep = 0;
        while(!m_board.isOut(newPos)) {
            if(m_board.tile(newPos) == Board::Tile::SNAKE_BODY && !tailStep) {
                tailStep = 1;
            } else if(m_board.tile(newPos) == Board::Tile::FRUIT && !fruitStep) {
                fruitStep = 1;
            }

            newPos = newPos + direction[i];
            wallStep++;
        }

        v[i*3] = 1.0/wallStep;
        v[i*3+1] = tailStep;
        v[i*3+2] = fruitStep;
    }

    return v;
}

std::vector<Vector2D> Game::fruitsPos() {
    return m_fruitPos;
}

void Game::print() {
    cout << "Move " << m_moves << " : " << endl;
    m_board.print();

    cout << endl << endl << endl;
}