#include <stdio.h>
#include <windows.h>
#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include <QCoreApplication>

#include "printer.h"
#include "menu.h"

using namespace std;

// To write and read in the bash window
QTextStream in(stdin);
QTextStream out(stdout);

int main(int argc, char *argv[])
{
    // To avoid timer error message (qt application without GUI)
    QCoreApplication a(argc, argv);
    out << "The application juste started" << endl << endl;

    // Declaration
    Printer printer;
    Menu menu;

    QString myLine;
    BOOLEAN exit = false;
    QByteArray ba;
    char *myCharLine;

    // Configuration of the serial port
    printer.initSerial("COM18", (quint32)250000);

    // Setting the speed
    printer.setSpeed18000();

    // Go home
    printer.goHome();

    menu.printInfo();

    do
    {
        myLine = menu.getSelection();
        if (myLine == "exit")
        {
            exit = true;
        }
        else if (myLine == "draw")
        {
            printer.draw();
        }
        else
        {
            ba = myLine.toLatin1();
            myCharLine = ba.data();
            printer.write(myCharLine);
            out << endl;
        }

    }while (!exit);

    // Put at origin before closing the app and the communication
    printer.goHome();

    // Close communication
    printer.closeSerial();

    out << "The application juste ended" << endl << endl;
    return 0;
}
