#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include <QCoreApplication>

#include "mydraws.h"

// To write and read in the bash window
QTextStream in(stdin);
QTextStream out(stdout);

int main(int argc, char *argv[])
{
    // To avoid timer error message (qt application without GUI)
    QCoreApplication a(argc, argv);

    out << "The application juste started" << endl << endl;

    // Configuration of the serial port
    QSerialPort serial;
    serial.setPortName("COM18");
    serial.setBaudRate((quint32)250000);
    serial.open(QIODevice::ReadWrite);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::NoFlowControl);

    // Waiting for the printer initialization
    out << "Waiting for the printer initialization ..." << endl << endl;
    Sleep(7000); // wait five second

    out << "Port connection status : " << serial.isOpen() << endl << endl;

    QString myLine;
    out << "Type \"exit\" to exit" << endl << endl;
    BOOLEAN exit = false;
    QByteArray ba;
    char *myCharLine;


    // Setting the speed
    const char* setSpeed18000 = "G1F18000";
    serial.write(setSpeed18000);
    serial.waitForBytesWritten(-1);
    serial.write("\n");
    serial.waitForBytesWritten(-1);

    // Put at origin
    serial.write("G28\n");
    serial.waitForBytesWritten(-1);

    Sleep(3000);

//    // Setting to relative
//    const char* setRelative = "G91";
//    serial.write(setRelative);
//    serial.waitForBytesWritten(-1);
//    serial.write("\n");
//    serial.waitForBytesWritten(-1);

    do
    {
        out << "Type the command you wanna send : " << endl;
        in >> myLine;
        if (myLine == "exit")
        {
            exit = true;
        }
        else if (myLine == "draw")
        {
           for (int i = 0; i<25; i++)
           {
               serial.write(helloWorld[i]);
               serial.waitForBytesWritten(-1);
               serial.write("\n");
               serial.waitForBytesWritten(-1);
               Sleep(1000);
           }
        }
        else
        {
            ba = myLine.toLatin1();
            myCharLine = ba.data();
            serial.write(myCharLine);
            serial.waitForBytesWritten(-1);
            serial.write("\n");
            serial.waitForBytesWritten(-1);
            out << endl;
        }

    }while (!exit);

    // Put at origin before closing the app and the communication
    serial.write("G28\n");
    serial.waitForBytesWritten(-1);

    serial.close();

    out << endl << "Port connection status : " << serial.isOpen() << endl << endl;
    out << "The application juste ended" << endl << endl;

    return 0;
}
