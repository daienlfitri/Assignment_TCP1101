// *********************************************************
// Course: TCP1101 PROGRAMMING FUNDAMENTALS
// Year: Trimester 1, 2022/23 (T2215)
// Lab: TT5L
// Names: Muhammad Daniel Fitri Bin Zulkarnain | Muhammad Danish Tan Bin Mohamad Hazri | Izzat Danial Bin Mohamad Yusof
// IDs: 1211105115 | 1221303139 | 1221303348
// Emails: 1211105115@student.mmu.edu.my | 1221303139@student.mmu.edu.my | 1221303348@student.mmu.edu.my
// Phones: 0133580497 | 0197553382 | 0194740639
// *********************************************************

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib> // for system()
#include <ctime> // for time() in srand( time(NULL) );
#include <iomanip> // for setw()
using namespace std;

enum Direction //create data type with a set of named values
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    QUIT,
    NONE
};

class Alien
{
private:
    int life_;
    int attack_;

public:
    Alien();
    int getLife();
    int getAttack();
    void setLife(int life);
    void initializeAttributes();
};

class Zombie
{
private:
    int life_;
    int attack_;
    int range_;

public:
    Zombie();
    int getLife();
    int getAttack();
    int getRange();
    void setLife(int life);
    void initializeAttributes();
};

class Rock
{
private:
    char symbol_;

public:
    Rock();
    char getSymbol();
    void setSymbol(char symbol);
    bool hideObject(char &hiddenObject);
    bool revealObject(char &hiddenObject);
};

class Game
{
private:
    vector<vector<char>> map_; // convention to put trailing underscore  // to make sure every function is defined through out the whole code
    int dimX_, dimY_; // to indicate private data
    int alienX_, alienY_;
    int zombieX_, zombieY_;

public:
    Game(int dimX = 9, int dimY = 5);
    int getDimX();
    int getDimY();
    bool alienMove(Direction direction);
    bool zombieMove();
    bool zombieAttack();
    void init(int dimX, int dimY);
    void display();
    void setObject(int x, int y, char ch);
    void settings(int dimX, int dimY, int zombie);
    void resetTrails();
    void getZombiePosition(int &zombieX, int &zombieY);
    void getAlienPosition(int &alienX, int &alienY);
    void zombieDamage(int damage);
    void spawnZombie();
};

bool Game::zombieAttack()
{
    Alien alien;
    Zombie zombie;
    // store and retrieve positions
    int alienX, alienY, zombieX, zombieY;
    getAlienPosition(alienX, alienY);
    getZombiePosition(zombieX, zombieY);

    int distance = abs(alienX - zombieX) + abs(alienY - zombieY);
    // calculate distance between alien and zombie
    if (distance <= zombie.getRange())
    {
        int damage = zombie.getAttack();
        int newLife = alien.getLife() - damage;
        if (newLife <= 0)
        {
            return true;
        }
        else
        {
            alien.setLife(newLife);
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool Game::zombieMove()
{
    int alienX, alienY;
    getAlienPosition(alienX, alienY);

    int zombieX, zombieY;
    getZombiePosition(zombieX, zombieY);

    int distX = alienX - zombieX;
    int distY = alienY - zombieY;

    //calculate vertical and horizontal range
    int absDistX = abs(distX);
    int absDistY = abs(distY);

    Zombie zombie;
    int zombieRange = zombie.getRange();

    //check the range
    if (absDistX + absDistY <= zombieRange)
    {
        if (absDistX > absDistY)
        {
            if (distX > 0)
            {
                setObject(zombieX, zombieY, ' ');
                zombieX_ = zombieX + 1;
                setObject(zombieX_, zombieY, 'Z');
            }
            else if (distX < 0)
            {
                setObject(zombieX, zombieY, ' ');
                zombieX_ = zombieX - 1;
                setObject(zombieX_, zombieY, 'Z');
            }
        }
        else
        {
            if (distY > 0)
            {
                setObject(zombieX, zombieY, ' ');
                zombieY_ = zombieY + 1;
                setObject(zombieX, zombieY_, 'Z');
            }
            else if (distY < 0)
            {
                setObject(zombieX, zombieY, ' ');
                zombieY_ = zombieY - 1;
                setObject(zombieX, zombieY_, 'Z');
            }
        }

        return true;
    }

    return false;
}

Alien::Alien()
{
    initializeAttributes();
}

void Alien::initializeAttributes()
{
    srand(time(0));
    life_ = rand() % 10 + 1;
    attack_ = rand() % life_ + 1;
}

int Alien::getLife()
{
    return life_;
}

int Alien::getAttack()
{
    return attack_;
}

void Alien::setLife(int life)
{
    life_ = life;
}

void displayAttributes(Alien &a, Zombie &z)
{
    cout << "Alien Life: " << a.getLife() << endl;
    cout << "Alien Attack: " << a.getAttack() << endl;
    cout << "Zombie Life: " << z.getLife() << endl;
    cout << "Zombie Attack: " << z.getAttack() << endl;
    cout << "Zombie Range: " << z.getRange() << endl;
}

Zombie::Zombie()
{
    initializeAttributes();
}

int Zombie::getLife()
{
    return life_;
}

int Zombie::getAttack()
{
    return attack_;
}

int Zombie::getRange()
{
    return range_;
}

void Zombie::setLife(int life)
{
    life_ = life;
}

void Zombie::initializeAttributes()
{
    srand(time(0));
    life_ = rand() % 10 + 1;
    attack_ = rand() % life_ + 1;
    range_ = rand() % 10 + 1;
}

void Game::spawnZombie()
{
    int randomX = rand() % dimX_;
    int randomY = rand() % dimY_;
    zombieX_ = randomX;
    zombieY_ = randomY;
    setObject(randomX, randomY, 'Z');
}

void Game::zombieDamage(int damage)
{
    Zombie zombie;
    zombie.setLife(zombie.getLife() - damage);
}

Rock::Rock()
{
    symbol_ = 'r';
}

char Rock::getSymbol()
{
    return symbol_;
}

void Rock::setSymbol(char symbol)
{
    symbol_ = symbol;
}

bool Rock::hideObject(char &hiddenObject)
{
    if (hiddenObject == ' ')
    {
        return false;
    }
    else
    {
        symbol_ = hiddenObject;
        hiddenObject = ' ';
        return true;
    }
}

bool Rock::revealObject(char &hiddenObject)
{
    if (symbol_ == 'r')
    {
        return false;
    }
    else
    {
        hiddenObject = symbol_;
        symbol_ = 'r';
        return true;
    }
}

Game::Game(int dimX, int dimY) //intializing diemnsion of rows and column
{
    init(dimX, dimY);
    alienX_ = dimX_ / 2;
    alienY_ = dimY_ / 2;
    spawnZombie();
    setObject(alienX_, alienY_, 'A');
}

int Game::getDimX()
{
    return dimX_;
}

int Game::getDimY()
{
    return dimY_;
}

void Game::init(int dimX, int dimY) //introducing characters to the board
{
    dimX_ = dimX;
    dimY_ = dimY;
    char objects[] = {' ', 'v', '^', '>', '<', 'r', ' ', 'h', 'p'};
    int noOfObjects = 9; // number of objects in the objects array
    // create dynamic 2D array using vector
    map_.resize(dimY_); // create empty rows
    for (int i = 0; i < dimY_; ++i)
    {
        map_[i].resize(dimX_); // resize each row
    }
    // put random characters into the vector array
    for (int i = 0; i < dimY_; ++i)
    {
        for (int j = 0; j < dimX_; ++j)
        {
            int objNo = rand() % noOfObjects;
            map_[i][j] = objects[objNo];
        }
    }
    map_[alienY_][alienX_] = 'A';
}

void Game::setObject(int x, int y, char ch)
{
    map_[y][x] = ch;
}

bool Game::alienMove(Direction direction)
{
    Alien alien;
    int oldX = alienX_;
    int oldY = alienY_;

    //moving direction indicated by arrow on board
    if (direction == UP)
    {
        alienY_--;
    }
    else if (direction == DOWN)
    {
        alienY_++;
    }
    else if (direction == LEFT)
    {
        alienX_--;
    }
    else if (direction == RIGHT)
    {
        alienX_++;
    }

    if (alienX_ >= 0 && alienX_ < dimX_ && alienY_ >= 0 && alienY_ < dimY_)
    {
        setObject(oldX, oldY, '.');
        if (map_[alienY_][alienX_] == 'h')
        {
            alien.setLife(alien.getLife() + 20);
        }
        if (map_[alienY_][alienX_] == 'p')
        {
            zombieDamage(10);
        }
        if (map_[alienY_][alienX_] == 'r')
        {
            alienX_ = oldX;
            alienY_ = oldY;
            setObject(oldX, oldY, 'A');
            return false;
        }
        setObject(alienX_, alienY_, 'A');

        // Call zombieMove() after Alien has moved 1 cell
        zombieMove();
        return true;
    }
    else
    {
        alienX_ = oldX;
        alienY_ = oldY;
        return false;
    }
}

void Game::resetTrails()
{
    for (int i = 0; i < dimY_; ++i)
    {
        for (int j = 0; j < dimX_; ++j)
        {
            if (map_[i][j] != 'A' && map_[i][j] != 'Z')
            {
                map_[i][j] = ' ';
            }
        }
    }
}

void Game::getZombiePosition(int &zombieX, int &zombieY)
{
    zombieX = zombieX_;
    zombieY = zombieY_;
}

void Game::getAlienPosition(int &alienX, int &alienY)
{
    alienX = alienX_;
    alienY = alienY_;
}

void Game::settings(int dimX, int dimY, int zombie) //settings for the user's preference
{
    cout << "Default Game Settings" << endl;
    cout << "---------------------" << endl;
    cout << "Board Rows : " << dimY_ << endl;
    cout << "Board Columns : " << dimX_ << endl;
    cout << "Zombie Count : " << zombie << "\n"
         << endl;
    {
        string userInput1;
        do
        {
            cout << "Do you wish to change game settings (yes/no) => ";
            cin >> userInput1;
            cout << endl;
            if (userInput1 == "yes" || userInput1 == "YES" || userInput1 == "Y" || userInput1 == "y")
            {
                int newDimY, newDimX, newZombie;
                cout << "Board settings       " << endl;
                cout << "---------------------" << endl;
                do
                {
                    cout << "Enter rows (maximum 5)         => ";
                    cin >> newDimY;
                    if (newDimY > 5)
                    {
                        cout << "Invalid input, please enter a number less than or equal to 5. \n"
                             << endl;
                    }
                } while (newDimY > 5);
                do
                {
                    cout << "Enter columns (minimum 5)      => ";
                    cin >> newDimX;
                    if (newDimX > 9)
                    {
                        cout << "Invalid input, please enter a number less than or equal to 9. \n"
                             << endl;
                    }
                } while (newDimX > 9);
                do
                {
                    cout << "Enter zombie (minimum 1)       => ";
                    cin >> newZombie;
                    if (newZombie < 1)
                    {
                        cout << "Invalid input, please enter a number more than or equal to 1. \n"
                             << endl;
                    }
                } while (newZombie < 1);
                dimY_ = newDimY;
                dimX_ = newDimX;
                zombie = newZombie;
                cout << endl;
                cout << "Settings Updated." << endl;
                break;
            }
            else if (userInput1 == "no" || userInput1 == "NO" || userInput1 == "N" || userInput1 == "n")
            {
                cout << "Game will continue with default settings. \n";
                break;
            }
            else
            {
                cout << "Invalid input, please enter 'yes' or 'no' \n\n";
            }
        } while (true);
        {
            system("pause");
            system("cls");
        }
    }
}

void Game::display() // Displaying the board
{
    system("cls");
    cout << " ----------------------------" << endl;
    cout << " Player, Welcome to the Game " << endl;
    cout << " ----------------------------" << endl;
    cout << endl;

    // the position of the Alien will be in the middle
    int x = dimX_ / 2;
    int y = dimY_ / 2;
    map_[y][x] = 'A';

    // for each row
    for (int i = 0; i < dimY_; ++i)
    {
        // display upper border of the row
        cout << " ";
        for (int j = 0; j < dimX_; ++j)
        {
            cout << "+-";
        }
        cout << "+" << endl;
        // display row number
        cout << setw(2) << (dimY_ - i);
        // display cell content and border of each column
        for (int j = 0; j < dimX_; ++j)
        {
            cout << "|";
            if (map_[i][j] == 'h')
            {
                cout << "h";
            }
            else
            {
                cout << map_[i][j];
            }
        }
        cout << "|" << endl;
    }
    cout << " ";
    // display lower border of the last row
    for (int j = 0; j < dimX_; ++j)
    {
        cout << "+-";
    }
    cout << "+" << endl;
    // display column number
    cout << " ";
    for (int j = 0; j < dimX_; ++j)
    {
        int digit = (j + 1) / 10;
        cout << " ";
        if (digit == 0)
            cout << " ";
        else
            cout << digit;
    }
    cout << endl;
    cout << " ";
    for (int j = 0; j < dimX_; ++j)
    {
        cout << " " << (j + 1) % 10;
    }
    cout << endl
         << endl;
}

int main() //pulls all the functions declared and runs it to start the program
{
    cout << "Assignment (Part 2)" << endl;
    cout << "Let's Get Started!"
         << "\n"
         << endl;
    srand(time(0));
    int dimX = 9;
    int dimY = 5;
    int zombie = 1;
    Game a(dimX, dimY);
    a.settings(dimX, dimY, zombie);
    a.display();
    char direction = ' ';
    while (direction != 'q')
    {
        cout << "Move [w/s/a/d/q]: ";
        cin >> direction;
        cout << endl;
        Direction dir = NONE;
        switch (direction)
        {
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'q':
            dir = QUIT;
            break;
        default:
            cout << "Invalid input. Please enter a valid direction." << endl;
            continue;
        }
        a.alienMove(dir);
        a.display();
        int zombieX, zombieY;
        a.getZombiePosition(zombieX, zombieY);
        int alienX, alienY;
        a.getAlienPosition(alienX, alienY);
        if (abs(zombieX - alienX) <= 1 && abs(zombieY - alienY) <= 1)
        {
            cout << "You were killed by the zombie!" << endl;
            // to prevent from windows to closing
            cin.get();
            break;
        }
    }
    //prevent windows closing before printing output
    system("pause");
    return 0;
}
