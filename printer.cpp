#include <stdio.h>
#include <windows.h>
#include <QDebug>
#include <QString>
#include <QtSerialPort/QSerialPort>
#include <QCoreApplication>
#include <QVector>

#include "printer.h"
#include "mydraws.h"

using namespace std;

// To write and read in the bash window
QTextStream inPrinter(stdin);
QTextStream outPrinter(stdout);


/*QVector<char*> theVector {
    "G1X150Y150\n",
    "G1X100Y100\n"
};*/

Printer::Printer()
{
}

void Printer::initSerial(QString portName, qint64 baudRate){
    serial.setPortName(portName);
    serial.setBaudRate(baudRate);
    serial.open(QIODevice::ReadWrite);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::NoFlowControl);

    // Waiting for the printer initialization
    outPrinter << "Waiting for the printer initialization ..." << endl << endl;
    Sleep(6000); // wait six seconds

    // Display the status of the port
    outPrinter << "Port connection status : " << serial.isOpen() << endl << endl;
}

void Printer::closeSerial(void){
   serial.close();

   outPrinter << endl << "Port connection status : " << serial.isOpen() << endl << endl;
}

void Printer::write(char* text){
    serial.write(text);
    serial.waitForBytesWritten(-1);
    serial.write("\n");
    serial.waitForBytesWritten(-1);
}

void Printer::setSpeed18000(void){
    serial.write("G1F18000\n");
    serial.waitForBytesWritten(-1);
}

void Printer::draw(void){
    for (int i = 0; i < helloWorld.size(); i++)
    {
        serial.write(helloWorld[i]);
        serial.waitForBytesWritten(-1);
        Sleep(100);
    }
}

void Printer::goHome(void){
    serial.write("G28\n");
    serial.waitForBytesWritten(-1);

    Sleep(3000);
}
