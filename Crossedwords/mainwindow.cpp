#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <string>
#include <random>
#include "reader.h"

QTableWidget * table;

void initTable();
std::string getRandomLetter();
void deleteItem(int x, int y);
std::string getItem(int x, int y);
void setItem(int x, int y, std::string str);

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    table = ui->tableWidget;
    initTable();
    std::cout << Reader::getRandomWord() << std::endl;
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
        }
    }
}

std::string getRandomLetter() {
    std::string final(1, 'A' + random()%24);
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
