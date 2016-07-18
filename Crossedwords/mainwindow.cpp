#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <vector>

#include "reader.h" // Brings in <string> too
#include "answer.h"
#include "point.h"

QTableWidget * table;
QListView * list;

void initTable();
std::string getRandomLetter();
void deleteItem(int x, int y);
std::string getItem(int x, int y);
void setItem(int x, int y, std::string str);
bool placeAnswer(Answer* ans);
void resetTable();
void generateAnswer();

const short squares = 14;
short numberOfItems = 10;
std::vector<Answer*> ansList; // an "ArrayList"

enum Direction {
    North = 1,
    East = 2,
    South = 3,
    West = 4,
};

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    table = ui->tableWidget;
    list = ui->listView;
    srand(time(0));
    initTable();

    // resetTable();

    //generateAnswer();
    //generateAnswer();

    Answer* ans2 = new Answer("TEST",3,0,Direction::West);
    placeAnswer(ans2);
    Answer* ans1 = new Answer("ASDF",1,0,Direction::South);
    placeAnswer(ans1);
    std::cout << "" << ans2->doesOverlap(ans1) << std::endl;
}

MainWindow::~MainWindow()
{
    // Erases and deallocates all letter items in table
    for(short i = 0; i < squares; i++) {
        for(short j = 0; j < squares; j++) {
            deleteItem(i, j);
        }
    }
    // Deallocates all items in ansList (doesn't remove them from the list)
    for(unsigned int i = 0; i < ansList.size(); i++) {
        delete ansList.at(i);
    }
    // Removes just in case
    ansList.clear();
    delete ui;
}

/*
 * Sets up styling and then allocates square Item objects to set
 */
void initTable() {
    table->setRowCount(squares);
    table->setColumnCount(squares);
    table->verticalHeader()->setVisible(false);
    table->horizontalHeader()->setVisible(false);
    table->setFocusPolicy(Qt::NoFocus);
    table->setSelectionMode(QTableWidget::NoSelection);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    short tableCellSize = 30;
    for(short i = 0; i < squares; i++) {
        table->setColumnWidth(i, tableCellSize);
        table->setRowHeight(i, tableCellSize);
        for(short j = 0; j < squares; j++) {
            // In here, we have access to every single square
            table->setItem(i, j, new QTableWidgetItem(""));
            table->item(i, j)->setFont(QFont("Helvetica", 20));
            table->item(i, j)->setTextAlignment(Qt::AlignCenter);
        }
    }
}

std::string getRandomLetter() {
    std::string final(1, 'A' + rand()%26);
    return final;
}

/*
 * Be careful with this. Attempting to set text
 * after deleting an Item will result in a crash
 */
void deleteItem(int x, int y) {
    if(x >= squares || x < 0 || y >= squares || y < 0) {
        std::cout << "Error in deleteItem(): out of bounds" << std::endl;
        return;
    }
    delete table->item(y, x);
}

std::string getItem(int x, int y) {
    if(x >= squares || x < 0 || y >= squares || y < 0) {
        std::cout << "Error in getItem(): out of bounds" << std::endl;
        return "ERROR";
    }
    return table->item(y, x)->text().toStdString();
}

void setItem(int x, int y, std::string str) {
    if(x >= squares || x < 0 || y >= squares || y < 0) {
        std::cout << "Error in setItem(): out of bounds" << std::endl;
        return;
    }
    table->item(y, x)->setText(str.c_str());
}

/**
 * @brief placeAnswer Puts the specific Answer object onto the board
 * @param ans Answer object to place at coords of itself
 * @return true if success, false if failed
 */
bool placeAnswer(Answer* ans) {
    switch(ans->direction) {
        case Direction::North: // as int, 1
            for(unsigned int i = 0; i < ans->baseStr.length(); i++) {
                std::string shortAns = ans->baseStr.substr(ans->baseStr.length() - 1 - i, 1);
                setItem(ans->sX, ans->sY - ans->baseStr.length() + i + 1, shortAns);
            }
            ansList.push_back(ans);
            return true; // Replaces break, does the same thing
        case Direction::South: // as int, 3
            for(unsigned int i = 0; i < ans->baseStr.length(); i++) {
                setItem(ans->sX, i + ans->sY, ans->baseStr.substr(i, 1));
            }
            ansList.push_back(ans);
            return true;
        case Direction::East: // as int, 2
            for(unsigned int i = 0; i < ans->baseStr.length(); i++) {
                setItem(i + ans->sX, ans->sY, ans->baseStr.substr(i, 1));
            }
            ansList.push_back(ans);
            return true;
        case Direction::West: // as int, 4
            for(unsigned int i = 0; i < ans->baseStr.length(); i++) {
                std::string shortAns = ans->baseStr.substr(ans->baseStr.length() - 1 - i, 1);
                setItem(ans->sX - ans->baseStr.length() + i + 1, ans->sY, shortAns);
            }
            ansList.push_back(ans);
            return true;
        default: // Failed for some reason
            std::cout << "Error in placeAnswer()" << std::endl;
            return false;
    }
    // Likely never to be reached, but there for compiler satisfation
    return false;
}

/*
 * Sets all square items to random letters
 * Does not affect list of Answers
 */
void resetTable() {
    for(short i = 0; i < squares; i++) {
        for(short j = 0; j < squares; j++) {
            setItem(i, j, getRandomLetter());
        }
    }
}

bool isValidLocation(int x, int y) {
    return x < squares && y < squares && x >= 0 && y >= 0;
}

void generateAnswer() {
    // Create random string for Answer
    std::string ansStr = ""; // "length 0"
    while (ansStr.length() > (unsigned int) squares || ansStr.length() == 0)
    { // Zero means this will run at least once
        ansStr = Reader::getRandomWord();
    }

    // Create answer (as pointer, for survival beyond scope) with random variables and direction
    Answer* ans_p = new Answer(ansStr,rand()%squares,rand()%squares, (rand()%4) + 1);

    // Fix placement by sliding word placement into place
    while(ans_p->getEndLetterX() < -2) {
        std::cout << "endLetterX is below zero, increasing sX..." << std::endl;
        ans_p->sX++;
    }
    while(ans_p->getEndLetterX() >= squares) {
        std::cout << "endLetterX is equal or above Squares, decreasing sX..." << std::endl;
        ans_p->sX--;
    }
    while(ans_p->getEndLetterY() < -2) {
        std::cout << "endLetterX is below zero, increasing sX..." << std::endl;
        ans_p->sY++;
    }
    while(ans_p->getEndLetterY() >= squares) {
        std::cout << "endLetterX is equal or above Squares, decreasing sX..." << std::endl;
        ans_p->sY--;
    }

    // Actually place things
    placeAnswer(ans_p);
}
