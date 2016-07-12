#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include "reader.h"
#include "answer.h"

QTableWidget * table;

void initTable();
std::string getRandomLetter();
void deleteItem(int x, int y);
std::string getItem(int x, int y);
void setItem(int x, int y, std::string str);

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

    Answer* ans1 = new Answer("Dix", 1, 1, Direction::East);
    std::cout << "x: " << ans1->getEndLetterX();
    std::cout << " y: " << ans1->getEndLetterY() << std::endl;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void initTable() {
    short int squares = 14;
    table->setRowCount(squares);
    table->setColumnCount(squares);
    table->verticalHeader()->setVisible(false);
    table->horizontalHeader()->setVisible(false);
    table->setFocusPolicy(Qt::NoFocus);
    table->setSelectionMode(QTableWidget::NoSelection);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    short int tableCellSize = 30;
    for(short int i = 0; i < squares; i++) {
        table->setColumnWidth(i, tableCellSize);
        table->setRowHeight(i, tableCellSize);
        std::string str;
        for(short int j = 0; j < squares; j++) {
            // In here, we have access to every single square
            str = getRandomLetter();
            table->setItem(i, j, new QTableWidgetItem(""));
            table->item(i, j)->setFont(QFont("Helvetica", 32));
            table->item(i, j)->setTextAlignment(Qt::AlignCenter);
            // table->item(i, j)->setText(Reader::getRandomWord().substr(0,1).c_str());
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
