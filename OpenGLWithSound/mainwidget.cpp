#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QMediaPlayer>
#include <QAudioProbe>
#include <QAudioFormat>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    m_player = new QMediaPlayer;
    connect( m_player, SIGNAL(positionChanged(qint64)), this, SLOT(OnSoundPositionChanged(qint64)) );
    m_player->setMedia(QUrl::fromLocalFile("/Users/simon/Music/iTunes/iTunes Media/Frank Zappa/Hot Rats/02 Willie The Pimp.mp3"));
    m_player->setVolume(50);

    m_audioProbe = new QAudioProbe;
    connect( m_audioProbe, SIGNAL(audioBufferProbed(QAudioBuffer)), this, SLOT(OnProbeAudio(QAudioBuffer)) );
    m_audioProbe->setSource( m_player );
    //bool active = m_audioProbe->isActive();
}

MainWidget::~MainWidget()
{
    delete ui;
    delete m_audioProbe;
    delete m_player;
}

void MainWidget::OnSoundPositionChanged( qint64 pos )
{
    qint64 duration = m_player->duration();
    double percent = (double)pos / m_player->duration();
    ui->positionSlider->setValue( (int)(percent * 100) );
}

#include <iostream>

void MainWidget::OnProbeAudio( const QAudioBuffer & buffer )
{
    std::cout << "Buffer duration: " << buffer.duration() << "ms" << std::endl;
    std::cout << "Buffer frame count: " << buffer.frameCount() << std::endl;
    std::cout << "Number of channels: " << buffer.format().channelCount() << std::endl;
    std::cout << "Sample rate: " << buffer.format().sampleRate() << "hz" << std::endl;
    std::cout << "Nb frames for 83ms (12fps): " << buffer.format().framesForDuration( qint64(83000) ) << std::endl;
}

void MainWidget::on_playButton_clicked()
{
    if( m_player->state() == QMediaPlayer::PlayingState )
    {
        m_player->pause();
        ui->playButton->setText( "Play" );
    }
    else
    {
        m_player->play();
        ui->playButton->setText( "Pause" );
        //bool active = m_audioProbe->isActive();
        //int toto = 0;
    }
}

void MainWidget::on_positionSlider_valueChanged(int value)
{

}
