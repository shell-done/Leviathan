#include "view.hpp"

View::View() {
    m_window = new sf::RenderWindow(sf::VideoMode(1593, 896), "Leviathan - Alexandre THOMAS (ISEN Yncréa Ouest Brest)", sf::Style::Titlebar | sf::Style::Close);
    m_window->setFramerateLimit(30);

    loadResources();
}

void View::drawGame(TrainingSupervisor* trainingSupervisor) {
    Game* game = trainingSupervisor->bestTrainingBox() ? trainingSupervisor->bestTrainingBox()->game() : nullptr;
    if(!game)
        return;

    sf::Vector2i gridOrigin(729, 32);
    int tileSize = 32;
    
    for(int i=-1; i<=game->gridSize(); i++) {
        for(int j=-1; j<=game->gridSize(); j++) {
            Board::Tile currentTile = Board::Tile::ERR;
            
            sf::Vector2i tilePos = sf::Vector2i(gridOrigin);
            tilePos.x += (i+1)*tileSize;
            tilePos.y += (j+1)*tileSize;

            if(i < 0 || i >= game->gridSize() || j < 0 || j >= game->gridSize())
                currentTile = Board::Tile::WALL;
            else
                currentTile = game->grid()[i][j];

            if(currentTile == Board::Tile::SNAKE_HEAD) {
                drawSprite(currentTile, tilePos, tileRotation(game->headDirection()));
            } else {
                drawSprite(currentTile, tilePos);
            }
        }
    }
}

void View::drawLoading(TrainingSupervisor* trainingSupervisor) {
    sf::Vector2f origin(851, 304);

    int finished = trainingSupervisor->finished();
    int total = trainingSupervisor->populationPerGeneration();
    float completion = (float)finished / total;

    sf::RectangleShape box(sf::Vector2f(580, 250));
    box.setFillColor(sf::Color(250, 250, 250));
    box.setOutlineThickness(5);
    box.setOutlineColor(sf::Color(37, 37, 37));
    box.setPosition(origin);
    m_window->draw(box);

    sf::RectangleShape titleBox(sf::Vector2f(580, 32));
    titleBox.setFillColor(sf::Color(37, 37, 37));
    titleBox.setPosition(origin);
    m_window->draw(titleBox);

    sf::Text title;
    title.setFont(m_font);
    title.setString("Loading...");
    title.setCharacterSize(24);
    title.setFillColor(sf::Color::White);
    title.setPosition(853, 302);
    m_window->draw(title);

    title.setString(L"Simulating generation n°" + std::to_wstring(trainingSupervisor->generation() + 1));
    title.setCharacterSize(35);
    title.setFillColor(sf::Color(37, 37, 37));
    title.setPosition(851 + (580 - title.getLocalBounds().width)/2, 360);
    m_window->draw(title);

    sf::Text subtitle;
    subtitle.setFont(m_font);
    subtitle.setString("Population of " + std::to_string(total) + " with a mutation rate of " + std::to_string(trainingSupervisor->mutationRate()) + " %");
    subtitle.setCharacterSize(25);
    subtitle.setFillColor(sf::Color(100, 100, 100));
    subtitle.setPosition(851 + (580 - subtitle.getLocalBounds().width)/2, 410);
    m_window->draw(subtitle);

    sf::RectangleShape loadingBarOutline(sf::Vector2f(480, 40));
    loadingBarOutline.setFillColor(sf::Color(100, 100, 100));
    loadingBarOutline.setOutlineThickness(3);
    loadingBarOutline.setOutlineColor(sf::Color(37, 37, 37));
    loadingBarOutline.setPosition(851 + (580 - loadingBarOutline.getLocalBounds().width)/2, 470);
    m_window->draw(loadingBarOutline);

    sf::RectangleShape loadingBar(sf::Vector2f(480*completion, 40));
    loadingBar.setFillColor(sf::Color(165, 0, 0));
    loadingBar.setPosition(851 + (580 - loadingBarOutline.getLocalBounds().width)/2, 470);
    m_window->draw(loadingBar);

    sf::Text completionLabel;
    completionLabel.setFont(m_font);
    completionLabel.setString(std::to_string((int)(completion*100)) + " % completed");
    completionLabel.setCharacterSize(30);
    completionLabel.setFillColor(sf::Color(240, 240, 240));
    completionLabel.setPosition(851 + (580 - completionLabel.getLocalBounds().width)/2, 470);
    m_window->draw(completionLabel);
}

void View::drawStats(TrainingSupervisor* trainingSupervisor) {
    TrainingStats* ts = nullptr;
    int lastGen = trainingSupervisor->trainingStats().size();
    
    if(!trainingSupervisor->trainingStats().empty()) {
        if(m_currentGen == (int)trainingSupervisor->trainingStats().size() - 1 && trainingSupervisor->nextGenReady())
            m_currentGen++;

        ts = trainingSupervisor->trainingStats()[m_currentGen - 1];
    }

    sf::Vector2f origin(24, 24);

    sf::RectangleShape box(sf::Vector2f(380, 140));
    box.setFillColor(sf::Color(250, 250, 250));
    box.setOutlineThickness(5);
    box.setOutlineColor(sf::Color(37, 37, 37));
    box.setPosition(origin);
    m_window->draw(box);

    sf::RectangleShape titleBox(sf::Vector2f(380, 32));
    titleBox.setFillColor(sf::Color(37, 37, 37));
    titleBox.setPosition(origin);
    m_window->draw(titleBox);

    sf::Text title;
    title.setFont(m_font);
    if(ts)
        title.setString(L"Generation n°" + std::to_wstring(m_currentGen));
    else
        title.setString("Loading...");
    title.setCharacterSize(24);
    title.setFillColor(sf::Color::White);
    title.setPosition(50, 22);
    m_window->draw(title);

    sf::CircleShape arrow(10, 3);
    sf::Color c = m_currentGen == 1 && ts ? sf::Color(120, 120, 120) : sf::Color(250, 250, 250);
    arrow.setFillColor(c);
    arrow.setOrigin(arrow.getLocalBounds().width/2, arrow.getLocalBounds().height/2);
    arrow.setRotation(-90);
    arrow.setPosition(35, 39);
    m_window->draw(arrow);

    c = m_currentGen == lastGen && ts ? sf::Color(120, 120, 120) : sf::Color(250, 250, 250);
    arrow.setFillColor(c);
    arrow.setRotation(90);
    arrow.setPosition(68 + title.getLocalBounds().width, 37);
    m_window->draw(arrow);

    sf::Text statLabel;
    statLabel.setFont(m_font);
    statLabel.setString("Worst fitness score : ");
    statLabel.setCharacterSize(20);
    statLabel.setFillColor(sf::Color(37, 37, 37));
    statLabel.setPosition(30, 56);
    m_window->draw(statLabel);

    std::ostringstream stream;
    sf::Text statValue;
    if(ts) {
        stream << ts->minFitnessScore();
        statValue.setFont(m_font);
        statValue.setString(stream.str());
        statValue.setCharacterSize(20);
        statValue.setFillColor(sf::Color(165, 0, 0));
        statValue.setPosition(30 + statLabel.getLocalBounds().width, 56);
        m_window->draw(statValue);
    }

    statLabel.setString("Best fitness score : ");
    statLabel.setPosition(30, 82);
    m_window->draw(statLabel);

    if(ts) {
        stream.str("");
        stream << ts->maxFitnessScore();
        statValue.setString(stream.str());
        statValue.setPosition(30 + statLabel.getLocalBounds().width, 82);
        m_window->draw(statValue);
    }

    statLabel.setString("Average of fitness scores : ");
    statLabel.setPosition(30, 108);
    m_window->draw(statLabel);

    if(ts) {
        stream.str("");
        stream << ts->avgFitnessScore();
        statValue.setString(stream.str());
        statValue.setPosition(30 + statLabel.getLocalBounds().width, 108);
        m_window->draw(statValue);
    }

    statLabel.setString("Standard dev. of fitness scores : ");
    statLabel.setPosition(30, 134);
    m_window->draw(statLabel);

    if(ts) {
        stream.str("");
        stream << ts->sdFitnessScore();
        statValue.setString(stream.str());
        statValue.setPosition(30 + statLabel.getLocalBounds().width, 134);
        m_window->draw(statValue);
    }
}

void View::drawReplay(TrainingSupervisor* trainingSupervisor) {
    Game* game = trainingSupervisor->bestTrainingBox() ? trainingSupervisor->bestTrainingBox()->game() : nullptr;
    sf::Vector2f origin(437, 24);

    sf::RectangleShape box(sf::Vector2f(252, 140));
    box.setFillColor(sf::Color(250, 250, 250));
    box.setOutlineThickness(5);
    box.setOutlineColor(sf::Color(37, 37, 37));
    box.setPosition(origin);
    m_window->draw(box);

    sf::RectangleShape titleBox(sf::Vector2f(252, 32));
    titleBox.setFillColor(sf::Color(37, 37, 37));
    titleBox.setPosition(origin);
    m_window->draw(titleBox);

    sf::Text title;
    title.setFont(m_font);
    title.setString("Replay");
    title.setCharacterSize(24);
    title.setFillColor(sf::Color::White);
    title.setPosition(440, 22);
    m_window->draw(title);

    sf::Text statLabel;
    statLabel.setFont(m_font);
    statLabel.setString("Apples : ");
    statLabel.setCharacterSize(20);
    statLabel.setFillColor(sf::Color(37, 37, 37));
    statLabel.setPosition(443, 65);
    m_window->draw(statLabel);

    std::ostringstream stream;
    sf::Text statValue;
    if(game) {
        stream << game->score();
        statValue.setFont(m_font);
        statValue.setString(stream.str());
        statValue.setCharacterSize(20);
        statValue.setFillColor(sf::Color(165, 0, 0));
        statValue.setPosition(443 + statLabel.getLocalBounds().width, 65);
        m_window->draw(statValue);
    }

    statLabel.setString("Moves : ");
    statLabel.setPosition(443, 95);
    m_window->draw(statLabel);

    if(game) {
        stream.str("");
        stream << game->moves();
        statValue.setString(stream.str());
        statValue.setPosition(443 + statLabel.getLocalBounds().width, 95);
        m_window->draw(statValue);
    }

    statLabel.setString("Moves left : ");
    statLabel.setPosition(443, 125);
    m_window->draw(statLabel);

    if(game) {
        stream.str("");
        stream << game->movesLeft();
        statValue.setString(stream.str());
        statValue.setPosition(443 + statLabel.getLocalBounds().width, 125);
        m_window->draw(statValue);
    }
}

void View::drawNeuralNetwork(TrainingSupervisor* trainingSupervisor) {
    int width = 650;
    int height = 619;
    sf::Vector2f origin(70, 235);
    sf::Vector2f boxOrigin(24, 196);

    sf::RectangleShape box(sf::Vector2f(665, 670));
    box.setFillColor(sf::Color(250, 250, 250));
    box.setOutlineThickness(5);
    box.setOutlineColor(sf::Color(37, 37, 37));
    box.setPosition(boxOrigin);
    m_window->draw(box);

    sf::RectangleShape titleBox(sf::Vector2f(665, 32));
    titleBox.setFillColor(sf::Color(37, 37, 37));
    titleBox.setPosition(boxOrigin);
    m_window->draw(titleBox);

    sf::Text title;
    title.setFont(m_font);
    title.setString("Neural network");
    title.setCharacterSize(24);
    title.setFillColor(sf::Color::White);
    title.setPosition(27, 194);
    m_window->draw(title);

    if(!trainingSupervisor->isLoading()) {
        NeuralNetwork* neuralNetwork = trainingSupervisor->bestTrainingBox()->neuralNetwork();
        Vector inputVector = trainingSupervisor->bestTrainingBox()->game()->inputVector();
        std::vector<Vector> vectors = neuralNetwork->middleVectors(inputVector);
        for(int i=0; i<(int)vectors.size(); i++) {
            Vector& v = vectors[i];
            int col = i*width/vectors.size();
            int nextCol = (i+1)*width/vectors.size();

            for(int j=0; j<(int)v.dim(); j++) {
                int row = j*height/v.dim();

                if(i != (int)v.dim() - 1) {
                    Matrix& weights = neuralNetwork->layer(i)->weights;

                    for(int m=0; m<weights.m(); m++) {
                        int nextRow = m*height/vectors[i+1].dim();
                        sf::Color color = weights.el(m, j) > 0 ? sf::Color(13, 104, 137) : sf::Color(183, 46, 25);

                        sf::Vertex line[] = {
                            sf::Vertex(sf::Vector2f(col + 14 + origin.x, 2 + row + origin.y + height/(2*v.dim())), color),
                            sf::Vertex(sf::Vector2f(nextCol - 8 + origin.x, 2 + nextRow + origin.y + height/(2*vectors[i+1].dim())), color)
                        };

                        m_window->draw(line, 2, sf::Lines);
                    }
                }

                sf::Sprite sprite(m_nodeTileset, sf::IntRect(32, 0, 32, 32));
                sprite.setScale(0.75, 0.75);
                sprite.setOrigin(12, 12);
                sprite.setColor(sf::Color((v[j] > 1 ? 1 : v[j])*97, (v[j] > 1 ? 1 : v[j])*145, (v[j] > 1 ? 1 : v[j])*21));
                sprite.setPosition(origin.x + col, origin.y + row + height/(2*v.dim()));

                m_window->draw(sprite);
            }
        }

        sf::Text direction;
        direction.setFont(m_font);
        direction.setString("Up");
        direction.setCharacterSize(35);
        direction.setFillColor(sf::Color(37, 37, 37));
        direction.setPosition(585, 292);
        m_window->draw(direction);

        direction.setString("Right");
        direction.setPosition(585, 445);
        m_window->draw(direction);

        direction.setString("Down");
        direction.setPosition(585, 599);
        m_window->draw(direction);

        direction.setString("Left");
        direction.setPosition(585, 755);
        m_window->draw(direction);
    }
}

void View::render(TrainingSupervisor* trainingSupervisor) {
    sf::Event event;
    
    while(m_window->pollEvent(event)) {
        if(event.type == sf::Event::Closed) {
            m_window->close();
            return;
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i pos = sf::Mouse::getPosition(*m_window);

                if(pos.x >= 25 && pos.y >= 25 && pos.x <= 47 && pos.y <= 50)
                    if(m_currentGen > 1) m_currentGen--;

                if(pos.x >= 206 && pos.y >= 25 && pos.x <= 228 && pos.y <= 50)
                    if(m_currentGen < trainingSupervisor->generation()) m_currentGen++;
            }
        }
    }

    m_window->clear(sf::Color(196, 196, 196));
    
    drawGame(trainingSupervisor);
    if(trainingSupervisor->isLoading()) {
        drawLoading(trainingSupervisor);
    }
    
    drawStats(trainingSupervisor);
    drawReplay(trainingSupervisor);
    drawNeuralNetwork(trainingSupervisor);
    
    m_window->display();
}

bool View::isOpen() {
    return m_window->isOpen();
}

void View::loadResources() {
    if(!m_gameTileset.loadFromFile("resources/game_tileset.png"))
        throw GraphicException("Cannot load texture file : resources/game_tileset.png");

    if(!m_nodeTileset.loadFromFile("resources/node_tileset.png"))
        throw GraphicException("Cannot load texture file : resources/node_tileset.png");

    if(!m_font.loadFromFile("resources/calibri.ttf"))
        throw GraphicException("Cannot load font file : resources/calibri.ttf");

    m_tileRects[Board::Tile::WALL] = sf::IntRect(0, 0, 32, 32);
    m_tileRects[Board::Tile::EMPTY] = sf::IntRect(32, 0, 32, 32);
    m_tileRects[Board::Tile::SNAKE_HEAD] = sf::IntRect(64, 0, 32, 32);
    m_tileRects[Board::Tile::FRUIT] = sf::IntRect(0, 32, 32, 32);
    m_tileRects[Board::Tile::ERR] = sf::IntRect(32, 32, 32, 32);
    m_tileRects[Board::Tile::SNAKE_BODY] = sf::IntRect(64, 32, 32, 32);

    m_nodeTileset.setSmooth(true);
}

int View::tileRotation(Game::Direction direction) {
    switch (direction) {
    case Game::Direction::UP:
        return 0;
    
    case Game::Direction::RIGHT:
        return 90;
    
    case Game::Direction::DOWN:
        return 180;

    case Game::Direction::LEFT:
        return 270;

    default:
        return 0;
    }
}

void View::drawSprite(Board::Tile tile, int x, int y, int r) {
    sf::Sprite sprite(m_gameTileset, m_tileRects[tile]);
    sprite.setOrigin(16, 16);
    sprite.setPosition(x, y);

    if(r != 0) {
        sprite.setRotation(r);
    }

    m_window->draw(sprite);
}

void View::drawSprite(Board::Tile tile, sf::Vector2i u, int r) {
    drawSprite(tile, u.x, u.y, r);
}
