//===========================================
//  Originally written as qsudo by the TrueOS Project
//  Copyright (c) 2016, TrueOS
//  Relicensed with contributor consent from BSD-2 to BSD-3
//  See the LICENSE file for full details
//===========================================
#include <qtranslator.h>
#include <qlocale.h>
#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QTextCodec>
#include <unistd.h>
#include <sys/types.h>
#include "mainwindow.h"

#ifndef PREFIX
#define PREFIX QString("/usr/local")
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if ( argc <= 1 ) {
       qDebug() << "Error: Need to specify argument to run!";
       exit(1);
    }
    //Test that the user needs to provide a password first
    QStringList args; for(int i=1; i<argc; i++){ args << argv[i]; }
    QProcess P;
    P.setProcessEnvironment(QProcessEnvironment::systemEnvironment());
    P.start("sudo", QStringList() << "-n" << args);
    P.waitForFinished();
    int ret = P.exitCode(); //QProcess::execute("sudo", QStringList() << "-n" << args);
    if(ret==0){ return 0; } //all finished. No password needed

    QTranslator translator;
    QLocale mylocale;
    QString langCode = mylocale.name();
    if ( ! QFile::exists(PREFIX + "/share/lumina-desktop/i18n/lum_sudo_" + langCode + ".qm" ) )
        langCode.truncate(langCode.indexOf("_"));

    if ( QFile::exists(PREFIX + "/share/lumina-desktop/i18n/lum_sudo_" + langCode + ".qm" ) ) {
      translator.load( QString("lum_sudo_") + langCode, PREFIX + "/share/lumina-desktop/i18n/" );
      a.installTranslator( &translator );
    }
    QTextCodec::setCodecForLocale( QTextCodec::codecForName("UTF-8") ); //Force Utf-8 compliance

    MainWindow w;
    w.ProgramInit();
    w.show();

    return a.exec();
}
