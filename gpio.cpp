#include "gpio.h"

#include <lgpio.h>

Gpio::Gpio(QObject *parent) : QObject(parent)
{
    m_handle = lgGpiochipOpen(CHIP);
    int init_state = 0;
    for(int pin : LEDS)
        lgGpioClaimOutput(m_handle, FLAGS, pin, init_state);
}

Gpio::~Gpio()
{
    int init_state = 0;
    for(int pin : LEDS)
        lgGpioWrite(m_handle, pin, init_state);

    lgGpiochipClose(m_handle);

}

void Gpio::set(int pin, bool state)
{
    lgGpioWrite(m_handle, pin, state);
}

void Gpio::set(unsigned int pattern)
{
    int a = 0;
    bool state;
    unsigned int check = 0b0001;
    for(auto pin : LEDS)
    {

        state = check & pattern >> a;
        lgGpioWrite(m_handle, pin, state);
        a++;
    }
}
