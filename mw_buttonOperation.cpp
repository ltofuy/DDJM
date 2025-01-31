#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::buttonOperation(int a)
{
    switch (a) {
    case 0:
        //Sayori
    {
        wordDialog->last_count_tab = 1;
        wordDialog->last_name[0] = "Sayori";
        wordDialog->last_words[0] = wordList.getWords("Sayori");

        wordDialog->setWord("Sayori", wordDialog->last_words[0]);
        wordDialog->show();
    }
        break;
    case 1:
        //Yuri
    {
        wordDialog->last_count_tab = 2;
        wordDialog->last_name[0] = "Yuri-1";
        wordDialog->last_name[1] = "Yuri-2";
        wordDialog->last_words[0] = wordList.getWords("Yuri", 1);
        wordDialog->last_words[1] = wordList.getWords("Yuri", 2);

        //考虑 Act-1&2
        wordDialog->setWord("Yuri-1", wordDialog->last_words[0], "Yuri-2", wordDialog->last_words[1]);
        wordDialog->show();
    }
        break;
    case 2:
        //Natsuki
    {
        wordDialog->last_count_tab = 2;
        wordDialog->last_name[0] = "Natsuki-1";
        wordDialog->last_name[1] = "Natsuki-2";
        wordDialog->last_words[0] = wordList.getWords("Natsuki", 1);
        wordDialog->last_words[1] = wordList.getWords("Natsuki", 2);

        //考虑 Act-1&2
        wordDialog->setWord("Natsuki-1", wordDialog->last_words[0], "Natsuki-2", wordDialog->last_words[1]);
        wordDialog->show();
    }
        break;
    case 3:
        //Monika
    {
        wordDialog->last_count_tab = 1;
        wordDialog->last_name[0] = "Monika";
        wordDialog->last_words[0] = wordList.getWords("Monika");

        wordDialog->setWord("Monika", wordDialog->last_words[0]);
        wordDialog->show();
    }
        break;
    case 10:
        //quickSearch
        quickSearch();
        break;
    }
}
