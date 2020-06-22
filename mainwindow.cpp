#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->removeToolBar(ui->mainToolBar);
    this->statusBar()->setVisible(false);
    mainPalette = new QPalette;
    this->setWindowTitle("Social Network Analysis");
    mainPalette->setColor(QPalette::Active,QPalette::Window,Qt::white);
    this->setPalette(*mainPalette);
    //this->setFixedSize(400,100);
    InitUI();
}

void MainWindow::InitUI()
{


       //init input layout
       inputLayout = new QHBoxLayout;
       InitFisrtPage();
       mainLayout = new QHBoxLayout;
       mainLayout->addItem(inputLayout);



       //adding main layout to central widget of window
       centralWidget = new QWidget(this);
       centralWidget->setLayout(mainLayout);
       setCentralWidget(centralWidget);
}

void MainWindow::InitFisrtPage(){

    QFont font("Volkhov",11,QFont::Light,true);


    browseButton = new QPushButton;
    browseButton->setText("Browse Input File");
    browseButton->setMinimumHeight(30);
    browseButton->setFont(font);

    RunButton = new QPushButton;
    RunButton->setText("Run Algorithm");
    RunButton->setMinimumHeight(30);
    RunButton->setFont(font);


    fileName = new QLineEdit;
    fileName->setDisabled(true);
    fileName->setFont(font);
    fileName->setMinimumHeight(30);

    inputPage = new QFormLayout;
    inputPage->addRow(fileName,browseButton);
    inputPage->addRow(RunButton);

    inputPage->setContentsMargins(10,10,10,10);
    inputPage->setSpacing(10);
    inputLayout->addItem(inputPage);
    QObject::connect(browseButton,SIGNAL(clicked()),this,SLOT(browseButtonPressed()));
    QObject::connect(RunButton,SIGNAL(clicked()),this,SLOT(runAlgorithmPressed()));


}

void MainWindow::browseButtonPressed()
{
    tokens.clear();
    QString file_name = QFileDialog::getOpenFileName(this,"Choose input file","c://",tr("Text Files (*.txt)"));
    QFile file(file_name);
    fileName->setText(file_name);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::warning(this,"Input File Error","Please Select A Valid Input Text File");
        return;
    }
    else{
        QTextStream input(&file);
        QString inputLine = "";
        while (!input.atEnd())
        {
            inputLine = input.readLine();
            inputLine = inputLine.simplified();
            inputLine.replace( " ", "" );
            if(inputLine=="")
                continue;
            QStringList myStringList = inputLine.split(',');
            Token token(myStringList.first(),myStringList.last());
            tokens.push_back(token);
        }

    }
    file.close();

}

void MainWindow::runAlgorithmPressed(){

    if(tokens.size() > 0){
        root = Expression::RunAlgorithm(tokens);
        QString Error_Message= Expression::Check_Error();
        if (Error_Message=="")
        {
        graphics = new Graphics(0);
        graphics->show();
        graphics->drawNodes(root);
        }
        else {
            QMessageBox::warning(this,"No Syntax Tree",Error_Message);
        }

    }
}


MainWindow::~MainWindow()
{
    delete ui;
}
