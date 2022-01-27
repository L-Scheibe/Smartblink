#include "gui.h"

Gui::Gui(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    m_leds = new Gpio(this);
    m_state = 0;
    m_timer = new QTimer();
    connect(m_timer, &QTimer::timeout, this, &Gui::toggle); // verbindung Timer -> Gui Label
    m_timer->start(TIMEOUT);
}

void Gui::on_speedSlider_valueChanged(int value)
{
    m_timer->start(1000/value);
}

void Gui::on_blinkButton_clicked()
{
    m_blink = 1;
}

void Gui::on_lauflichtButton_clicked()
{
    m_blink = 0;
    n = 1;
}

void Gui::toggle()
{
    m_state = !m_state;

    if (m_blink == 1)
    {
        if (m_state == 1)
        {
            n = 15;
        } else
        {
            n = 0;
        }
        m_leds->set(n);
    }
    if (m_blink == 0)
    {
        m_leds->set(n);
        if(n < 8)
        {
            n *= 2;
        }
        else
        {
            n = 1;
        }
    }
}
