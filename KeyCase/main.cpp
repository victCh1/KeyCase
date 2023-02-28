
#include <QApplication>
#include <QStyleFactory>
#include <QTranslator>
#include <QLibraryInfo>
#include <QLibraryInfo>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setStyle(QStyleFactory::create("Fusion"));

    QTranslator translator, translatorQtLib;
    if(translator.load(QLocale(), "KeyCase_", "", ":/"))
        a.installTranslator(&translator);

    if(translatorQtLib.load(QLocale::system(), "qtbase_", "", QLibraryInfo::path(QLibraryInfo::TranslationsPath)))
        a.installTranslator(&translatorQtLib);

    MainWindow w;
    w.show();
    return a.exec();
}
