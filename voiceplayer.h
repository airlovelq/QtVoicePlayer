#ifndef VOICEPLAYER_H
#define VOICEPLAYER_H

#include <QtWidgets/QMainWindow>
#include "ui_voiceplayer.h"

class VoicePlayer : public QMainWindow
{
	Q_OBJECT

public:
	VoicePlayer(QWidget *parent = 0);
	~VoicePlayer();

private:
	Ui::VoicePlayerClass ui;

protected:
	QMediaPlayer m_mp;

protected slots:
	void pause();
	void start();
	void stop();
	void updateRange(int pos);
	void updatePosition(int pos);

	void updataMediaPositon(int pos);
	void updateTime(int pos);
};

#endif // VOICEPLAYER_H
