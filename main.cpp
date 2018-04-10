#include <stdio.h>

#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include <QCoreApplication>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTextStream in(stdin);
    QTextStream out(stdout);

    QSerialPort serial;
    out << "The application juste started" << endl;

    serial.setPortName("COM18");
    serial.setBaudRate((quint32)250000);
    serial.open(QIODevice::ReadWrite);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::NoFlowControl);


    QString line;
    in >> line;

    out << "Is the port open ?" << serial.isOpen() << endl;

    serial.write("G");
    serial.waitForBytesWritten(-1);
    serial.write("2");
    serial.waitForBytesWritten(-1);
    serial.write("8");
    serial.waitForBytesWritten(-1);
    serial.write("\n");
    serial.waitForBytesWritten(-1);

    serial.close();

    out << "Is the port open ?" << serial.isOpen() << endl;

    return 0;
}
