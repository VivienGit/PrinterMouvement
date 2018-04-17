#ifndef PRINTER_H
#define PRINTER_H

class Printer
{
private:
    QSerialPort serial;

public:
    Printer();
    void initSerial(QString portName, qint64 baudRate);
    void closeSerial(void);
    void setSpeed18000(void);
    void write(char* text);
    void draw(void);
    void goHome(void);
};

#endif // PRINTER_H
