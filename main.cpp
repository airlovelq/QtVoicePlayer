#include "stdafx.h"
#include "voiceplayer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	VoicePlayer w;
	QFile fstyle("stylesheet.sht");
	if ( fstyle.open(QFile::ReadOnly|QFile::Text) )
	{
	    QString strStyle = fstyle.readAll();
		w.setStyleSheet(strStyle);
		fstyle.close();
	}
	w.show();
	return a.exec();
}
