#include "menu.h"
#include <QDebug>

using namespace std;

// To write and read in the bash window
QTextStream inMenu(stdin);
QTextStream outMenu(stdout);

Menu::Menu()
{
}

void Menu::printInfo(void){
    outMenu << "   - Type \"exit\" to exit" << endl;
    outMenu << "   - The command you want"  << endl;
    outMenu << "   - Or \"draw\" to draw somthing" << endl << endl;
}

QString Menu::getSelection(void){
    QString theSelection;
    outMenu << "Type the command you want to send : " << endl;
    inMenu >> theSelection;
    return theSelection;
}
