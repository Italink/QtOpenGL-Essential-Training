#include "Widget.h"
#include <QApplication>
#include <QHBoxLayout>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget openglWidget;
    openglWidget.show();
    return a.exec();
}
