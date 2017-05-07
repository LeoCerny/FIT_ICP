/** 
 * @file main.cpp
 * @author Lukáš Černý <xcerny63@stud.fit.vutbr.cz>
 * @author Ondřej Čech <xcecho03@stud.fit.vutbr.cz>
 * 
 * @date April 25, 2017, 1:32 PM
 */

#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
