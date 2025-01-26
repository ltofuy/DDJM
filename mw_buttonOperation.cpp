#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::buttonOperation(int a)
{
    switch (a) {
    case 0:
        //Sayori
    {
        wordDialog->setWord("Sayori", wordList.getWords("Sayori"));
        wordDialog->show();
    }
        break;
    case 1:
        //Yuri
    {
        //考虑 Act-1&2
        wordDialog->setWord("Yuri-1", wordList.getWords("Yuri", 1), "Yuri-2", wordList.getWords("Yuri", 2));
        wordDialog->show();
    }
        break;
    case 2:
        //Natsuki
    {
        //考虑 Act-1&2
        wordDialog->setWord("Natsuki-1", wordList.getWords("Natsuki", 1), "Natsuki-2", wordList.getWords("Natsuki", 2));
        wordDialog->show();
    }
        break;
    case 3:
        //Monika
    {
        wordDialog->setWord("Monika", wordList.getWords("Monika"));
        wordDialog->show();
    }
        break;
    case 10:
        //quickSearch
        quickSearch();
        break;
    }
}
