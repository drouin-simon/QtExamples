#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QMediaPlayer>
#include "openglwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    m_player = new QMediaPlayer;
    connect( m_player, SIGNAL(positionChanged(qint64)), this, SLOT(OnSoundPositionChanged(qint64)) );
    m_player->setMedia(QUrl::fromLocalFile("/Users/simon/DropBox/test-Purple-Haze.mp3"));
    m_player->setVolume(50);

    ui->graphicsWidget->SetCurrentFrame( 0 );
}

MainWidget::~MainWidget()
{
    delete ui;
    delete m_player;
}

void MainWidget::OnSoundPositionChanged( qint64 pos )
{
    qint64 duration = m_player->duration();
    double percent = (double)pos / m_player->duration();
    ui->positionSlider->setValue( (int)(percent * 100) );
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
    }
}

void MainWidget::on_positionSlider_valueChanged(int value)
{

}
