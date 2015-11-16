#include "openglwidget.h"
#include "audiodecoder.h"
#include <QPainter>
#include <iostream>

const int NUM_CHANNELS = 2;
const double frameDuration = 0.083333333;

OpenGLWidget::OpenGLWidget( QWidget * parent ) : QOpenGLWidget(parent)
{
    std::string filename = "/Users/simon/DropBox/test-Purple-Haze.mp3";
    m_audioDecoder = new AudioDecoder(filename);

    if( m_audioDecoder->open() != AUDIODECODER_OK )
    {
        std::cerr << "Failed to open " << filename << std::endl;
    }

    m_frameData = 0;
}

void OpenGLWidget::SetCurrentFrame( int frame )
{
    int nbSamplesPerFrame = (int)( frameDuration * m_audioDecoder->sampleRate() );
    int sample = (int)( frameDuration * frame * m_audioDecoder->sampleRate() );
    m_audioDecoder->seek( sample );

    if( !m_frameData )
        m_frameData = new SAMPLE[ nbSamplesPerFrame * NUM_CHANNELS ];

    int samplesRead = m_audioDecoder->read( nbSamplesPerFrame * NUM_CHANNELS, static_cast<SAMPLE*>(m_frameData) );
}

int OpenGLWidget::GetNumberOfFrames()
{
    double duration = m_audioDecoder->duration();
    int nbFrames = (int)ceil( duration / frameDuration );
    return nbFrames;
}

void OpenGLWidget::initializeGL()
{

}

void OpenGLWidget::paintGL()
{
    glClearColor( 1.0, 0.0, 0.0, 1.0 );
    glClear( GL_COLOR_BUFFER_BIT );

    int nbSamplesPerFrame = (int)( frameDuration * m_audioDecoder->sampleRate() );
    double nbSamplesPerLine = (double)height() / nbSamplesPerFrame;
    int intNbSamplesPerLine = (int)ceil( nbSamplesPerLine );

    QPainter painter;
    painter.begin( this );

    double middlePixels = 200.0;

    for( int i = 0; i < height(); ++i )
    {
        int index = (int)(i * nbSamplesPerLine);
        SAMPLE * samplePtr = m_frameData + index;
        double sum = 0.0;
        for( int s = 0; s < intNbSamplesPerLine; ++s )
        {
            sum += *samplePtr;
            samplePtr += NUM_CHANNELS;
        }
        sum /= intNbSamplesPerLine;
        double s = middlePixels + 10.0 * sum;
        double e = middlePixels - 10.0 * sum;
        painter.drawLine( s, i, e, i );
    }

    painter.end();

}

void OpenGLWidget::resizeGL(int w, int h)
{

}
