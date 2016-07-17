#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

#include "reader.h" // Brings in <string>
#include "answer.h"

QTableWidget * table;

void initTable();
std::string getRandomLetter();
void deleteItem(int x, int y);
std::string getItem(int x, int y);
void setItem(int x, int y, std::string str);
bool placeAnswer(Answer ans);
short squares;
void resetTable();
void generateAnswer();

enum Direction {
    North = 1,
    Northeast = 2,
    East = 3,
    Southeast = 4,
    South = 5,
    Southwest = 6,
    West = 7,
    Northwest = 8
};

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    table = ui->tableWidget;
    srand(time(0));
    initTable();

    generateAnswer();

    resetTable();
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
 * Sets up styling and then allocates square Item objects to set
 */
void initTable() {
    squares = 14;
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
    delete table->item(y, x);
}

std::string getItem(int x, int y) {
    return table->item(y, x)->text().toStdString();
}

void setItem(int x, int y, std::string str) {
    table->item(y, x)->setText(str.c_str());
}

/**
 * @brief placeAnswer Puts the specific Answer object onto the board
 * @param ans Answer object to place at coords of itself
 * @return true if success, false if failed
 */
bool placeAnswer(Answer ans) {
    switch(ans.direction) {
        case Direction::North:
            for(unsigned int i = 0; i < ans.baseStr.length(); i++) {
                std::string shortAns = ans.baseStr.substr(ans.baseStr.length() - 1 - i, 1);
                setItem(ans.sX, ans.sY - ans.baseStr.length() + i + 1, shortAns);
            }
            return true; // Replaces break, does the same thing
        case Direction::South:
            for(unsigned int i = 0; i < ans.baseStr.length(); i++) {
                setItem(ans.sX, i + ans.sY, ans.baseStr.substr(i, 1));
            }
            return true;
        case Direction::East:
            for(unsigned int i = 0; i < ans.baseStr.length(); i++) {
                setItem(i + ans.sX, ans.sY, ans.baseStr.substr(i, 1));
            }
            return true;
        case Direction::West:
            for(unsigned int i = 0; i < ans.baseStr.length(); i++) {
                std::string shortAns = ans.baseStr.substr(ans.baseStr.length() - 1 - i, 1);
                setItem(ans.sX - ans.baseStr.length() + i + 1, ans.sY, shortAns);
            }
            return true;
        default: // Failed for some reason
            return false;
    }
    // Likely never to be reached, but there for compiler satisfation
    return false;
}

void resetTable() {
    for(short i = 0; i < squares; i++) {
        for(short j = 0; j < squares; j++) {
            setItem(i, j, getRandomLetter());
        }
    }
}

bool isValidLocation(int x, int y) {
    return x < squares && y < squares;
}

void generateAnswer() {
    std::string ansStr = ""; // String to be used in generated Answer, length zero
    while (ansStr.length() > (unsigned int) squares || ansStr.length() == 0) // 0 will make it happen once at least
    { // This will continue getting random words until ansStr is the right length
        ansStr = Reader::getRandomWord(); // This should only happen once for the most part
    }
    Answer ans(ansStr,0,0,rand()%4); // This is destroyed at end of this scope
    placeAnswer(ans); // But another is created for this
}
