#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <utility>

enum class Tile {
    Empty,
    Full,
    Floor
};

std::vector<Tile> findAdjacent(int x, int y, std::vector<std::vector<Tile>> &chairGrid) {
    std::vector<Tile> adjacent;
    
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if ((i == 0 && j == 0)
                || y + i < 0 || y + i >= chairGrid.size()
                || x + j < 0 || x + j >= chairGrid[0].size()) {
                continue;
            }

            Tile tile = chairGrid[y + i][x + j];
            if (tile == Tile::Full || tile == Tile::Empty) {
                adjacent.push_back(tile);
            }
        }
    }

    return adjacent;
}

std::vector<Tile> findInSight(int x, int y, std::vector<std::vector<Tile>> &chairGrid) {
    std::vector<Tile> inSight;

    const std::pair<int, int> multipliers[] = {{-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1}};
    
    for (std::pair<int, int> multiplier: multipliers) {
        for (int i = 1; ; ++i) {
            int nextX = x + multiplier.first * i, nextY = y + multiplier.second * i;
            if (nextY >= 0 && nextY < chairGrid.size()
                && nextX >= 0 && nextX < chairGrid[0].size()) {
                Tile tile = chairGrid[nextY][nextX];
                if (tile != Tile::Floor) {
                    inSight.push_back(tile);
                    break;
                }
            } else {
                break;
            }
        }
    }

    return inSight;
}

std::vector<std::vector<Tile>> tick(std::vector<std::vector<Tile>> &chairGrid, bool part2 = false) {
    std::vector<std::vector<Tile>> tickedChairGrid = chairGrid;
    int maxFull = 4;
    if (part2) {
        maxFull = 5;
    }

    for (int y = 0; y < chairGrid.size(); ++y) {
        for (int x = 0; x < chairGrid[0].size(); ++x) {
            Tile tile = chairGrid[y][x];
            if (tile == Tile::Empty || tile == Tile::Full) {
                std::vector<Tile> important;
                if (part2) {
                    important = findInSight(x, y, chairGrid);
                } else {
                    important = findAdjacent(x, y, chairGrid);
                }

                switch (tile) {
                    case Tile::Empty:
                        if (std::find(important.begin(), important.end(), Tile::Full) == important.end()) {
                            tickedChairGrid[y][x] = Tile::Full;
                        }
                        break;
                    
                    case Tile::Full:
                        {
                            int fullCount = 0;
                            for (Tile tile: important) {
                                if (tile == Tile::Full) {
                                    ++fullCount;
                                }
                            }

                            if (fullCount >= maxFull) {
                                tickedChairGrid[y][x] = Tile::Empty;
                            }
                        }
                        break;
                }
            }
        }
    }

    return tickedChairGrid;
}

int countOccupied(std::vector<std::vector<Tile>> &chairGrid) {
    int occupied = 0;
    
    for (std::vector<Tile> row: chairGrid) {
        for (Tile tile: row) {
            if (tile == Tile::Full) {
                ++occupied;
            }
        }
    }

    return occupied;
}

int main() {
    std::vector<std::vector<Tile>> chairGrid;

    std::string line;
    while (getline(std::cin, line)) {
        std::vector<Tile> row;
        for (char ch: line) {
            switch (ch) {

                case 'L':
                    row.push_back(Tile::Empty);
                    break;
                
                case '#': // Technically useless but why not
                    row.push_back(Tile::Full);
                    break;
                
                case '.':
                    row.push_back(Tile::Floor);
                    break;
            
            }
        }
        chairGrid.push_back(row);
    }
    
    std::vector<std::vector<Tile>> chairGridCopy = chairGrid;
    while (true) {
        std::vector<std::vector<Tile>> tmp = tick(chairGridCopy);
        if (tmp != chairGridCopy) {
            chairGridCopy = tmp;
        } else {
            break;
        }
    }

    std::cout << countOccupied(chairGridCopy) << '\n';

    chairGridCopy = chairGrid;
    while (true) {
        std::vector<std::vector<Tile>> tmp = tick(chairGridCopy, true);
        /*std::cout << "NEXT:\n";
        for (auto i: tmp) {
            for (auto j: i) {
                switch (j) {
                    case Tile::Empty: std::cout << 'L'; break;
                    case Tile::Full: std::cout << '#'; break;
                    case Tile::Floor: std::cout << '.'; break;
                }
            }
            std::cout << '\n';
        }*/
        if (tmp != chairGridCopy) {
            chairGridCopy = tmp;
        } else {
            break;
        }
    }

    std::cout << countOccupied(chairGridCopy) << '\n';
}