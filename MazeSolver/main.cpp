
#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <stack>
#include <SFML/Graphics.hpp>

// Define colors
sf::Color white(255, 255, 255);      
sf::Color black(0, 0, 0);            
sf::Color magenta(255, 0, 255);      
sf::Color green(0, 255, 0);          
sf::Color red(255, 0, 0);            
sf::Color blue(0, 0, 255);           
sf::Color yellow(255, 255, 0);       

// Maze structure
struct Maze {
    std::vector<std::vector<char>> cells;
    int start_x, start_y, end_x, end_y;
};

// Function to load maze from file
bool loadMaze(const std::string& filename, Maze& maze) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }

    int rows, cols;
    file >> rows >> cols;
    maze.cells.resize(rows, std::vector<char>(cols));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            file >> maze.cells[i][j];
            if (maze.cells[i][j] == 'S') {
                maze.start_y = i;
                maze.start_x = j;
            } else if (maze.cells[i][j] == 'E') {
                maze.end_y = i;
                maze.end_x = j;
            }
        }
    }

    file.close();
    return true;
}

// Function to draw the maze
void drawMaze(Maze& maze, sf::RenderWindow& window) {
    window.clear(); 

    // Loop over every row & column in the maze array
    for (size_t i = 0; i < maze.cells.size(); ++i) {
        for (size_t j = 0; j < maze.cells[i].size(); ++j) {
            sf::RectangleShape cell(sf::Vector2f(15.f, 15.f)); 

            // Position the cell based on its row and column
            cell.setPosition(static_cast<float>(j * 15), static_cast<float>(i * 15));

            // Color the rectangle based on the value in the maze at that position
            switch (maze.cells[i][j]) {
                case '#':
                    cell.setFillColor(sf::Color::Black); // Wall
                    break;
                case '.':
                    cell.setFillColor(sf::Color::White); // Open space
                    break;
                case 'S':
                    cell.setFillColor(sf::Color::Green); // Start
                    break;
                case 'E':
                    cell.setFillColor(sf::Color::Red); // End
                    break;
                case 'V':
                    cell.setFillColor(sf::Color::Magenta); // Visited
                    break;
                case 'P':
                    cell.setFillColor(sf::Color::Blue); // Potential cell to explore
                    break;
                case 'Y':
                    cell.setFillColor(sf::Color::Yellow); // Path from start to end
                    break;
                default:
                    break;
            }

            window.draw(cell); 
        }
    }

    window.display();
    sf::sleep(sf::milliseconds(50)); 
}
// Function to perform BFS
bool BFS(Maze& maze, sf::RenderWindow& window) {
    std::queue<std::pair<int, int>> q;
    q.push({maze.start_y, maze.start_x});

    while (!q.empty()) {
        int y = q.front().first;
        int x = q.front().second;
        q.pop();

        // Skip the cell if it's already visited
        if (maze.cells[y][x] == 'V' || maze.cells[y][x] == 'Y') {
            continue;
        }

        // Mark the cell as visited or as the endpoint if reached
        if (y == maze.end_y && x == maze.end_x) {
            maze.cells[y][x] = 'E'; // Mark the end cell
            return true;
        } else {
            maze.cells[y][x] = 'Y'; // Mark as visited
        }

        // Draw the maze at each step
        drawMaze(maze, window);
        window.display(); // Update the window
        

        // SFML event handling loop
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return false; // Terminate the search if the window is closed
            }
        }

        // Check neighbors
        int dy[] = {-1, 1, 0, 0};
        int dx[] = {0, 0, -1, 1};

        // Explore unvisited neighbors
        for (int i = 0; i < 4; ++i) {
            int ny = y + dy[i];
            int nx = x + dx[i];

            // Check if the neighbor is within bounds and unvisited
            if (ny >= 0 && ny < (int)maze.cells.size() && nx >= 0 && nx < (int)maze.cells[0].size() &&
                (maze.cells[ny][nx] == '.' || maze.cells[ny][nx] == 'E')) {
                if (maze.cells[ny][nx] == '.') {
                    maze.cells[ny][nx] = 'P'; // Mark the potential cell to explore
                }
                q.push({ny, nx});
            }
        }
    }

    return false; // If the search is exhausted
}
// Function to perform DFS
bool DFS(Maze& maze, sf::RenderWindow& window) {
    std::stack<std::pair<int, int>> s;
    s.push({maze.start_y, maze.start_x});

    while (!s.empty()) {
        int y = s.top().first;
        int x = s.top().second;

        // Mark the cell as visited or as the endpoint if reached
        if (y == maze.end_y && x == maze.end_x) {
            maze.cells[y][x] = 'E'; // Mark the end cell
            return true;
        } else if (maze.cells[y][x] == '.') {
            maze.cells[y][x] = 'V'; // Mark as visited
        }

        // Draw the maze at each step
        drawMaze(maze, window);
        window.display();
        

        // SFML event handling loop
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return false;  // Terminate the search if the window is closed
            }
        }

        // Flag to determine if there are unvisited neighbors
        bool found = false;

        
        int dy[] = {-1, 0, 1, 0};
        int dx[] = {0, 1, 0, -1};

        // Explore unvisited neighbors
        for (int i = 0; i < 4; ++i) {
            int ny = y + dy[i];
            int nx = x + dx[i];
                if (maze.cells[ny][nx] == '.') {
                maze.cells[ny][nx] = 'P'; // Mark the potential cell to explore
                }

        }
        int dy1[] = {-1, 0, 1, 0};
        int dx1[] = {0, 1, 0, -1};
         for (int i = 0; i < 4; ++i) {
            int ny1 = y + dy1[i];
            int nx1= x + dx1[i];
            // Check if the neighbor is within bounds and unvisited
            if (ny1 >= 0 && ny1 < (int)maze.cells.size() && nx1 >= 0 && nx1 < (int)maze.cells[0].size() &&
                (maze.cells[ny1][nx1] == 'P' || maze.cells[ny1][nx1] == 'E')) {
                maze.cells[ny1][nx1] = 'Y';
                s.push({ny1, nx1});
                found = true; // Mark that we found an unvisited neighbor

                break; // Break out of the loop after finding one unvisited neighbor
            }
        }
        
        // If no unvisited neighbors were found, backtrack
        if (!found) {
            maze.cells[y][x] = 'V';
            s.pop();
        }
    }

    return false; // If the search is exhausted
}
int main() {
    std::string mazeFilename;
    std::cout << "Enter the maze number(1-12): ";
    std::cin >> mazeFilename;
    mazeFilename = "mazePack\\" + mazeFilename+ ".maze";
    Maze maze;
    if (!loadMaze(mazeFilename, maze)) {
        return 1;
    }

    // Create SFML window
    sf::RenderWindow window(sf::VideoMode(maze.cells[0].size() * 15, maze.cells.size() * 15), "Maze Solver");
    drawMaze(maze, window);
    // Ask the user for the search algorithm (BFS or DFS)
    std::string algorithm;
    std::cout << "Choose search algorithm (BFS or DFS): ";
    std::cin >> algorithm;

    // Perform the search based on user input
    bool result;
    if (algorithm == "BFS") {
        result = BFS(maze, window);
        
    } else if (algorithm == "DFS") {
        result = DFS(maze, window);
        
    } else {
        std::cerr << "Invalid algorithm choice. Please choose BFS or DFS." << std::endl;
        return 1;
    }

    // Display the result of the search
    if (result) {
        std::cout << "Path found!" << std::endl;
    } else {
        std::cout << "Unsolvable maze." << std::endl;
    }

    // Draw the final state of the maze
    drawMaze(maze, window);

    // Close the window when the user presses a key
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Q) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
        }
    }

    return 0;
}