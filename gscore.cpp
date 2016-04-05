#include "gscore.h"

GSCore::GSCore(int &argc, char* argv[]) : QApplication(argc, argv)
{
    MainWindow::instance();
    MainWindow::instance()->show();
}

