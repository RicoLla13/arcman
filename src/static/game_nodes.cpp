#include "game.hpp"

void Game::initNodes() {
    nodes.push_back(new Node(1 * rect_size, 3 * rect_size));   // node A 0
    nodes.push_back(new Node(6 * rect_size, 3 * rect_size));   // node B 1
    nodes.push_back(new Node(8 * rect_size, 3 * rect_size));   // node C 2
    nodes.push_back(new Node(13 * rect_size, 3 * rect_size));  // node D 3
    nodes.push_back(new Node(6 * rect_size, 5 * rect_size));   // node E 4
    nodes.push_back(new Node(8 * rect_size, 5 * rect_size));   // node F 5
    nodes.push_back(new Node(1 * rect_size, 6 * rect_size));   // node G 6
    nodes.push_back(new Node(4 * rect_size, 6 * rect_size));   // node H 7
    nodes.push_back(new Node(6 * rect_size, 6 * rect_size));   // node I 8
    nodes.push_back(new Node(8 * rect_size, 6 * rect_size));   // node J 9
    nodes.push_back(new Node(10 * rect_size, 6 * rect_size));  // node K 10
    nodes.push_back(new Node(13 * rect_size, 6 * rect_size));  // node L 11
    nodes.push_back(new Node(4 * rect_size, 8 * rect_size));   // node M 12
    nodes.push_back(new Node(10 * rect_size, 8 * rect_size));  // node N 13
    nodes.push_back(new Node(1 * rect_size, 12 * rect_size));  // node O 14
    nodes.push_back(new Node(4 * rect_size, 12 * rect_size));  // node P 15
    nodes.push_back(new Node(6 * rect_size, 12 * rect_size));  // node Q 16
    nodes.push_back(new Node(8 * rect_size, 12 * rect_size));  // node R 17
    nodes.push_back(new Node(10 * rect_size, 12 * rect_size)); // node S 18
    nodes.push_back(new Node(13 * rect_size, 12 * rect_size)); // node T 19
    nodes.push_back(new Node(6 * rect_size, 13 * rect_size));  // node U 20
    nodes.push_back(new Node(8 * rect_size, 13 * rect_size));  // node V 21
    nodes.push_back(new Node(1 * rect_size, 15 * rect_size));  // node W 22
    nodes.push_back(new Node(4 * rect_size, 15 * rect_size));  // node X 23
    nodes.push_back(new Node(6 * rect_size, 15 * rect_size));  // node Y 24
    nodes.push_back(new Node(8 * rect_size, 15 * rect_size));  // node Z 25
    nodes.push_back(new Node(10 * rect_size, 15 * rect_size)); // node Alpha
    nodes.push_back(new Node(13 * rect_size, 15 * rect_size)); // node Beta

    // define node connections
    // node A
    nodes[0]->setNeighbour(Direction::RIGHT, nodes[1]);     // node B
    nodes[0]->setNeighbour(Direction::DOWN, nodes[6]);      // node G
    // node B
    nodes[1]->setNeighbour(Direction::LEFT, nodes[0]);      // node A
    nodes[1]->setNeighbour(Direction::DOWN, nodes[4]);      // node E
    // node C
    nodes[2]->setNeighbour(Direction::RIGHT, nodes[3]);
    nodes[2]->setNeighbour(Direction::DOWN, nodes[5]);
    // node D
    nodes[3]->setNeighbour(Direction::LEFT, nodes[2]);
    nodes[3]->setNeighbour(Direction::DOWN, nodes[11]);
    // node E
    nodes[4]->setNeighbour(Direction::UP, nodes[1]);
    nodes[4]->setNeighbour(Direction::DOWN, nodes[8]);
    nodes[4]->setNeighbour(Direction::RIGHT, nodes[5]);
    // node F
    nodes[5]->setNeighbour(Direction::UP, nodes[2]);
    nodes[5]->setNeighbour(Direction::DOWN, nodes[9]);
    nodes[5]->setNeighbour(Direction::LEFT, nodes[4]);
    // node G
    nodes[6]->setNeighbour(Direction::UP, nodes[0]);
    nodes[6]->setNeighbour(Direction::RIGHT, nodes[7]);
    // node H
    nodes[7]->setNeighbour(Direction::LEFT, nodes[6]);
    nodes[7]->setNeighbour(Direction::RIGHT, nodes[8]);
    nodes[7]->setNeighbour(Direction::DOWN, nodes[12]);
    // node I
    nodes[8]->setNeighbour(Direction::LEFT, nodes[7]);
    nodes[8]->setNeighbour(Direction::UP, nodes[4]);
    // node J
    nodes[9]->setNeighbour(Direction::UP, nodes[5]);
    nodes[9]->setNeighbour(Direction::RIGHT, nodes[10]);
    // node K
    nodes[10]->setNeighbour(Direction::LEFT, nodes[9]);
    nodes[10]->setNeighbour(Direction::RIGHT, nodes[11]);
    nodes[10]->setNeighbour(Direction::DOWN, nodes[13]);
    // node L
    nodes[11]->setNeighbour(Direction::LEFT, nodes[10]);
    nodes[11]->setNeighbour(Direction::UP, nodes[3]);
    // node M
    nodes[12]->setNeighbour(Direction::UP, nodes[7]);
    nodes[12]->setNeighbour(Direction::DOWN, nodes[15]);
    nodes[12]->setNeighbour(Direction::RIGHT, nodes[13]);
    // node N
    nodes[13]->setNeighbour(Direction::UP, nodes[10]);
    nodes[13]->setNeighbour(Direction::DOWN, nodes[18]);
    nodes[13]->setNeighbour(Direction::LEFT, nodes[12]);
    // node O
    nodes[14]->setNeighbour(Direction::RIGHT, nodes[15]);
    nodes[14]->setNeighbour(Direction::DOWN, nodes[22]);
    // node P
    nodes[15]->setNeighbour(Direction::UP, nodes[12]);
    nodes[15]->setNeighbour(Direction::DOWN, nodes[23]);
    nodes[15]->setNeighbour(Direction::RIGHT, nodes[16]);
    nodes[15]->setNeighbour(Direction::LEFT, nodes[14]);
    // node Q
    nodes[16]->setNeighbour(Direction::DOWN, nodes[20]);
    nodes[16]->setNeighbour(Direction::LEFT, nodes[15]);
    // node R
    nodes[17]->setNeighbour(Direction::RIGHT, nodes[18]);
    nodes[17]->setNeighbour(Direction::DOWN, nodes[21]);
    // node S
    nodes[18]->setNeighbour(Direction::UP, nodes[13]);
    nodes[18]->setNeighbour(Direction::DOWN, nodes[26]);
    nodes[18]->setNeighbour(Direction::RIGHT, nodes[19]);
    nodes[18]->setNeighbour(Direction::LEFT, nodes[17]);
    // node T
    nodes[19]->setNeighbour(Direction::LEFT, nodes[18]);
    nodes[19]->setNeighbour(Direction::DOWN, nodes[27]);
    // node U
    nodes[20]->setNeighbour(Direction::UP, nodes[16]);
    nodes[20]->setNeighbour(Direction::DOWN, nodes[24]);
    nodes[20]->setNeighbour(Direction::RIGHT, nodes[21]);
    // node V
    nodes[21]->setNeighbour(Direction::UP, nodes[17]);
    nodes[21]->setNeighbour(Direction::DOWN, nodes[25]);
    nodes[21]->setNeighbour(Direction::LEFT, nodes[20]);
    // node W
    nodes[22]->setNeighbour(Direction::UP, nodes[14]);
    nodes[22]->setNeighbour(Direction::RIGHT, nodes[23]);
    // node X
    nodes[23]->setNeighbour(Direction::UP, nodes[15]);
    nodes[23]->setNeighbour(Direction::RIGHT, nodes[24]);
    nodes[23]->setNeighbour(Direction::LEFT, nodes[22]);
    // node Y
    nodes[24]->setNeighbour(Direction::UP, nodes[20]);
    nodes[24]->setNeighbour(Direction::LEFT, nodes[23]);
    // node Z
    nodes[25]->setNeighbour(Direction::UP, nodes[21]);
    nodes[25]->setNeighbour(Direction::RIGHT, nodes[26]);
    // node Alpha
    nodes[26]->setNeighbour(Direction::UP, nodes[18]);
    nodes[26]->setNeighbour(Direction::RIGHT, nodes[27]);
    nodes[26]->setNeighbour(Direction::LEFT, nodes[25]);
    // node Beta
    nodes[27]->setNeighbour(Direction::UP, nodes[19]);
    nodes[27]->setNeighbour(Direction::LEFT, nodes[26]);
}

void Game::drawNodes() {
    // for each node draw a red circle with radius 20
    for(auto node : nodes) {
        if(node == nullptr)
            throw CustomException("[!] #gameLoop()# -> A node in node vector is null!");

        sf::CircleShape circle(20);
        circle.setFillColor(sf::Color::Blue);
        circle.setPosition(node->getPosition());
        this->draw(circle);

        // draw connections
        for(auto neighbor : node->getAllNeighbours()) {
            if(neighbor == nullptr)
                continue;

            // Calculate the positions of the nodes
            sf::Vector2f startPos = node->getPosition() + sf::Vector2f(20, 20); // Start of the line (center of the node)
            sf::Vector2f endPos = neighbor->getPosition() + sf::Vector2f(20, 20); // End of the line (center of the connected node)

            // Create line vertices
            sf::Vertex line[] = {
                sf::Vertex(startPos),
                sf::Vertex(endPos)
            };

            // Draw the line
            this->draw(line, 2, sf::Lines);
        }
    }
}
