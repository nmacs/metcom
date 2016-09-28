#include "mainwindow.h"
#include <QApplication>
#include <QHBoxLayout>

#include "zcommlogdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	//QMainWindow logWindow;
	//logWindow.setLayout(new QHBoxLayout());
	//logWindow.layout()->addWidget(&logDlg);
	//logWindow.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	//logWindow.setCentralWidget(&logDlg);
	//logWindow.show();

    MainWindow w;
    w.show();

    return a.exec();
}
