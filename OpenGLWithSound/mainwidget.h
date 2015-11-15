#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

class QMediaPlayer;
class QAudioBuffer;
class QAudioProbe;

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

private slots:

    void OnSoundPositionChanged( qint64 pos );
    void OnProbeAudio( const QAudioBuffer & buffer );
    void on_playButton_clicked();
    void on_positionSlider_valueChanged(int value);

private:

    Ui::MainWidget *ui;

    QMediaPlayer * m_player;
    QAudioProbe * m_audioProbe;
};

#endif
