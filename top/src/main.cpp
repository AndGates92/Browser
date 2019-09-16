#include <qt5/QtWidgets/QApplication>
#include <qt5/QtWidgets/QLabel>
#include <qt5/QtWidgets/QWidget>
#include <qt5/QtCore/QSize>

int main (int argc, char* argv[]) {
	QApplication app(argc, argv);
	QSize winSize(320,400);
	QWidget window;
	window.setWindowTitle("Test");
	window.resize(winSize);
	window.show();
	QLabel hello("Welcome to Qt", &window);
	hello.setAlignment(Qt::AlignCenter);
	hello.resize(winSize);
	hello.show();
	return app.exec();
}
