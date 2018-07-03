#include "stdafx.h"
#include "voiceplayer.h"

VoicePlayer::VoicePlayer(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	QFile file("voice.mp3");
    if(!file.open(QIODevice::ReadOnly))
        qDebug() << "Could not open file";
    m_mp.setMedia(QUrl::fromLocalFile("voice.mp3"));
	connect(ui.pushButton_play,&QPushButton::clicked,this,&VoicePlayer::start);
	connect(ui.pushButton_pause,&QPushButton::clicked,this,&VoicePlayer::pause);
	connect(ui.pushButton_stop,&QPushButton::clicked,this,&VoicePlayer::stop);
	
	
	connect(&m_mp,&QMediaPlayer::durationChanged,this,&VoicePlayer::updateRange);
	connect(&m_mp,&QMediaPlayer::positionChanged,this,&VoicePlayer::updatePosition);
	connect(ui.horizontalSlider,&QSlider::sliderMoved,this,&VoicePlayer::updataMediaPositon);
	connect(ui.horizontalSlider,&QSlider::valueChanged,this,&VoicePlayer::updateTime);
}

VoicePlayer::~VoicePlayer()
{

}

void VoicePlayer::pause()
{
	m_mp.pause();
	ui.pushButton_play->setEnabled(true);
	ui.pushButton_pause->setEnabled(false);
	ui.pushButton_stop->setEnabled(true);
}

void VoicePlayer::start()
{
	m_mp.play();
	ui.pushButton_play->setEnabled(false);
	ui.pushButton_pause->setEnabled(true);
	ui.pushButton_stop->setEnabled(true);
}

void VoicePlayer::stop()
{
	m_mp.stop();
	ui.horizontalSlider->setSliderPosition(0);
	ui.pushButton_play->setEnabled(true);
	ui.pushButton_pause->setEnabled(false);
	ui.pushButton_stop->setEnabled(false);
}

void VoicePlayer::updateRange(int pos)
{
	ui.horizontalSlider->setRange(0,pos);
}

void VoicePlayer::updatePosition(int pos)
{
	ui.horizontalSlider->setValue(pos);
}

void VoicePlayer::updataMediaPositon(int pos)
{
	QMediaPlayer::State state = m_mp.state();
	m_mp.blockSignals(true);
	//m_mp.setPosition(pos);
	switch( state )
	{
	case QMediaPlayer::PausedState:
		m_mp.stop();
		m_mp.setPosition(pos);
		break;
	default:
		m_mp.setPosition(pos);
		break;
	}
	m_mp.blockSignals(false);
}

void VoicePlayer::updateTime(int pos)
{
	QTime duration(0, pos / 60000, qRound((pos % 60000) / 1000.0));  
    ui.label_time->setText(duration.toString(tr("mm:ss")));  
}

