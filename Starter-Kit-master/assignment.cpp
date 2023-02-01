// *******************
// Course: TCP1101 PROGRAMMING FUNDAMENTALS
// Year: Trimester 1, 2022/23 (T2215)
// Lab: TT5L
// Names: Muhammad Daniel Fitri | Muhammad Danish Tan | Izzat Danial
// IDs: 1211105115 | 1221303139 | 1221303348
// Emails: 1211105115@student.mmu.edu.my  | 1221303139@student.mmu.edu.my | 1221303348@student.mmu.edu.my
// Phones: 0133580497 | 0197553382 | 0194740639
// *******************

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib> // for system()
#include <ctime>   // for time() in srand( time(NULL) );
#include <iomanip> // for setw()
using namespace std;

class Alien
{
private:
    vector<vector<char>> map_; // convention to put trailing underscore  // to make sure every function is defined through out the whole code
    int dimX_, dimY_;          // to indicate private data
public:
    Alien(int dimX = 9, int dimY = 5); 
    void init(int dimX, int dimY);
    void settings(int dimX_, int dimY_, int zombie);
    void display();

    int getDimX();
    int getDimY();

    void setObject(int x, int y, char ch);
};

Alien::Alien(int dimX, int dimY) //intializing diemnsion of rows and column
{
    init(dimX, dimY);
}

int Alien::getDimX()
{
    return dimX_;
}
int Alien::getDimY()
{
    return dimY_;
}

void Alien::init(int dimX, int dimY) //introducing characters to the board
{
    dimX_ = dimX;
    dimY_ = dimY;
    char objects[] = {' ', 'v', '^', '>', '<', 'r', 'X', 'h', 'p'};
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
}

void Alien::settings(int dimX, int dimY, int zombie) //settings for the user's preference
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
            if (userInput1 == "yes" || userInput1 == "YES" || userInput1 == "Yes" || userInput1 == "y")
            {
                cout << "Board settings             " << endl;
                cout << "---------------------------" << endl;
                cout << "Enter rows               =>" << endl;
                cin >> dimY_;
                cout << "Enter columns            =>" << endl;
                cin >> dimX_;
                cout << "Enter zombie            =>" << endl;
                cin >> zombie;
                cout << endl;
                cout << "Settings Updated." << endl;
                break;
            }
            else if (userInput1 == "no" || userInput1 == "NO" || userInput1 == "No" || userInput1 == "n")
            {
                cout << "Game will continue with default settings \n";
                break;
            }
            else
            {
                cout << "Invalid input, please enter 'yes' or 'no'." << endl;
            }
        } while (true);
        {
            system("pause");
            system("cls");
        }
    }
}

void Alien::display() // Displaying the board
{
    // comment this out during testing
    // system("cls"); // OR system("clear"); for Linux / MacOS
    cout << " --_--------------" << endl;
    cout << " = Player, Welcome to the Game =" << endl;
    cout << " _--------------_-" << endl;
    cout << endl;

    int x = dimX_ / 2; // the position of the Alien will be in the middle
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
            cout << "|" << map_[i][j];
        }
        cout << "|" << endl;
    }
    // display lower border of the last row
    cout << " ";
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

void Alien::setObject(int x, int y, char ch) 
{
    map_[dimY_ - y][x - 1] = ch;
}

void runGame() //pulls all the functions declared earlier and runs it to start the program
{
    int dimX_, dimY_, zombie;
    Alien Alien;
    Alien.settings(dimX_, dimY_, zombie);
    Alien.display();
    cin.ignore(); // to prevent from windows to closing
    cout << "Press Enter to continue..." << endl;
    cin.get();
}

int main()
{
    srand(1); // use this for fixed map during testing
    // srand(time(NULL)); // try this for random map

    Alien Alien(9, 5);
    runGame(); // display game
}