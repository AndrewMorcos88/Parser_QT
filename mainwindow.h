#ifndef MAINWINDOW_H
#define MAINWINDOW_H



#include <QMainWindow>
#include <QString>
#include <QPalette>
#include <QGraphicsScene>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QFileDialog>
#include <QFile>
#include <QVector>
#include <QMessageBox>
#include <QTextStream>

#include "node.h"
#include "token.h"
#include "graphics.h"
#include "expersion.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void InitUI();
    void InitFisrtPage();

public slots:
    void browseButtonPressed();
    void runAlgorithmPressed();

private:
    Ui::MainWindow *ui;
    QWidget *centralWidget;

    //colors and pallete
    QPalette *mainPalette;

    //layout
    QFormLayout *inputPage;
    QHBoxLayout *mainLayout;
    QHBoxLayout *inputLayout;
    QHBoxLayout *outputLayout;

    // buttons
    QPushButton *browseButton;
    QPushButton *RunButton;

    //text
    QLineEdit *fileName;
    QLineEdit * First_Line;
    QLineEdit * Second_Line;

    QVector<Token> tokens;
    Graphics *graphics;
    Node* root;

};

#endif // MAINWINDOW_H
