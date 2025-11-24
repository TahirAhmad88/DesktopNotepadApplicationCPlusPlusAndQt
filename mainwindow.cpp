#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>                   //I have added this

#include <QFile>                         //I have added this
#include <QTextStream>                   //I have added this
#include <QFileDialog>                   //I have added this

#include <QFontDialog>                   //I have added this
#include <QFont>                         //I have added this

#include <QColorDialog>                  //I have added this
#include <QColor>                        //I have added this

#include <QtPrintSupport/QPrinter>       //I have added this
#include <QtPrintSupport/QPrintDialog>   //I have added this
#include <QMenu>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //This is for to convert cursor while hover on menus to pointer.
    QMenuBar *fileMenu= menuBar();
    fileMenu->setCursor(Qt::PointingHandCursor);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString currentFile;  //This is Globle varible
void MainWindow::on_textEdit_cursorPositionChanged()
{
    //It will store cursor position
    QTextCursor cursor = ui->textEdit->textCursor();

    int line = cursor.blockNumber() + 1;        //It will store lines of the text
    int column = cursor.positionInBlock() + 1;  //It will store columns of the text

    QString status = QString("Line: %1 | Column: %2").arg(line).arg(column);
    ui->statusbar->showMessage(status);         //It will show the lines & col on status bar.
}

void MainWindow::on_actionNew_triggered()
{
    currentFile = "";
    ui->textEdit->setText("");
}

void MainWindow::on_actionSave_triggered()
{
    if(currentFile.isEmpty()){  //It will first check is it empty?
        on_actionSave_As_triggered();
        return;
    }

    QFile file(currentFile);

    if(file.open(QIODevice::WriteOnly | QIODevice::Text)){ //if not empty then it will write & save.
        QTextStream out(&file);
        out<<ui->textEdit->toPlainText();   //From here it will write into the currentFile.
        file.close();

        setWindowTitle(currentFile + "- NotePad");
        ui->statusbar->showMessage("File Saved", 3000); //It will show this on the status bar.
    }else{
        QMessageBox::warning(this,"Error", "Could not open file for writing");  //If you haven't open file.
    }
}

void MainWindow::on_actionOpen_triggered()
{
    bool isModified = false;

    if(!currentFile.isEmpty()){  //It will check the currentFile is it empty?
                                //if yes then it will read all text & will store in saveContent string.
        QFile file(currentFile);

        if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
            QTextStream in(&file);
            QString saveContent = in.readAll();
            file.close();

            //It will compare both current text which is store in saveContent
            //& the existing text in textEdit.if not equal then isModified will become true.
            isModified = (saveContent != ui->textEdit->toPlainText());
        }
    }else{
        //If isModified still false means saveContent & textEdit text are equal
        //then empty the textEdit.
        isModified = !ui->textEdit->toPlainText().isEmpty();
    }

    if(isModified){ //It modidification true then it will show these three options.
        QMessageBox::StandardButton reply = QMessageBox::question(this,
        "Unsaved changes", "You have unsaved changes. Do you want to save?",
        QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

        if(reply == QMessageBox::Cancel) return;
        if(reply == QMessageBox::Yes){
            on_actionSave_triggered();
        }

        QString fileName = QFileDialog::getOpenFileName(this, "Open File", "", "All File (*.*) ;; Text File(*.txt) ;; XML File (*.xml)");

        if(!fileName.isEmpty()){
            QFile file(fileName);

            if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
                QTextStream in(&file);
                QString content = in.readAll();

                ui->textEdit->setPlainText(content);
                file.close();

                currentFile = fileName;  //It will modified the currentFile.

                setWindowTitle(currentFile + "- NotePad"); //It will show the title as currentFile name with NotePad.
                ui->statusbar->showMessage(QFileInfo(currentFile).fileName(),3000);
            }
        }else {
            QMessageBox::warning(this, "Error", "Could not open file");
        }
    }

    if(isModified == false){
        QString fileName = QFileDialog::getOpenFileName(this, "Open File", "", "All File (*.*) ;; Text File(*.txt) ;; XML File (*.xml)");

        if(!fileName.isEmpty()){
            QFile file(fileName);

            if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
                QTextStream in(&file);
                QString content = in.readAll();

                ui->textEdit->setPlainText(content);
                file.close();

                currentFile = fileName;  //It will modified the currentFile.

                setWindowTitle(currentFile + "- NotePad"); //It will show the title as currentFile name with NotePad.
                ui->statusbar->showMessage(QFileInfo(currentFile).fileName(),3000);
            }
        }else {
            QMessageBox::warning(this, "Error", "Could not open file");
        }
    }
}

void MainWindow::on_actionClose_triggered()
{
    bool isModified = false;

    if(!currentFile.isEmpty()){  //It will check the currentFile is it empty?
        //if yes then it will read all text & will store in saveContent string.
        QFile file(currentFile);

        if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
            QTextStream in(&file);
            QString saveContent = in.readAll();
            file.close();

            //It will compare both current text which is store in saveContent
            //& the existing text in textEdit.if not equal then isModified will become true.
            isModified = (saveContent != ui->textEdit->toPlainText());
        }
    }else{
        //If isModified still false means saveContent & textEdit text are equal
        //then empty the textEdit.
        isModified = !ui->textEdit->toPlainText().isEmpty();
    }

    if(isModified){ //It modidification true then it will show these three options.
        QMessageBox::StandardButton reply = QMessageBox::question(this,
         "Unsaved changes", "You have unsaved changes. Do you want to save?",
         QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

        if(reply == QMessageBox::Cancel) return;
        if(reply == QMessageBox::Yes){
            on_actionSave_triggered();
        };
        if(reply == QMessageBox::No) close();
    }

    if(isModified == false){
        close();
    }
}

void MainWindow::on_actionSave_As_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save File AS", "", "Text Files (*.txt) ;; All Files(*)");
    if(!fileName.isEmpty()){
        currentFile = fileName;
        on_actionSave_triggered();
    }
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionFont_triggered()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, this);

    if(ok){
        ui->textEdit->setFont(font);
    }else{
        return;
    }
}

void MainWindow::on_actionFont_Color_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Choose color");

    if(color.isValid()){
        ui->textEdit->setTextColor(color);
    }
}

void MainWindow::on_actionBG_Color_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Choose color");

    if(color.isValid()){
        ui->textEdit->setTextBackgroundColor(color);
    }
}


void MainWindow::on_actionAbout_triggered()
{
    QString aboutText;
    aboutText =  "Author :  Code by Tahir Ahmad (Akash Dawar)\n";
    aboutText += "Place   :  North Waziristan, FATA, Pak\n";
    aboutText += "Date    :  17/08/2025\n";

    aboutText += "\n\t\t© NotePad ®";

    QMessageBox::about(this,"About NotePad",aboutText);
}

void MainWindow::on_actionPrint_triggered()
{
    QPrinter printer;

    QPrintDialog dialog(&printer,this);

    if(dialog.exec() == QDialog::Rejected) return;
    ui->textEdit->print(&printer);
}

