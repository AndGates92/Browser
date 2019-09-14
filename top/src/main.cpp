#include <qt5/QtWidgets/QApplication>
#include <qt5/QtWidgets/QLabel>
#include <qt5/QtWidgets/QWidget>

int main (int argc, char* argv[]) {
	QApplication app(argc, argv);
	QLabel hello("<center>Welcome to Qt</center>");
	hello.setWindowTitle("Test");
	hello.show();
	return app.exec();
}
