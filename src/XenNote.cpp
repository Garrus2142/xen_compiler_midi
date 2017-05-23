#include "XenNote.h"

using namespace std;

XenNote::XenNote(int midiNote, int length, int delay)
{
    if (midiNote < 0 || midiNote > 127)
        m_error = true;
    else
    {
        m_midiNote = midiNote;
        m_length = fmin(fmax(length, 0), 255);
        m_delay = fmin(fmax(delay, 0), 255);

        m_error = false;
    }
}

vector<unsigned char> XenNote::compile() const
{
    vector<unsigned char> data;

    data.push_back(getXenNote());
    data.push_back(m_length);
    data.push_back(m_delay);

    return (data);
}

void XenNote::toFlux(ostream &flux) const
{
    flux << "Note: " << (int)m_midiNote << " Length: " << (int)m_length <<
        " Delay: " << (int)m_delay;
}
unsigned char XenNote::getMidiNote() const
{
    return (m_midiNote);
}

unsigned char XenNote::getXenNote() const
{
    return (m_midiNote - 23);
}

unsigned char XenNote::getLength() const
{
    return (m_length);
}

unsigned char XenNote::getDelay() const
{
    return (m_delay);
}

void XenNote::setDelay(int delay)
{
    m_delay = fmin(fmax(0, delay), 255);
}

bool XenNote::error() const
{
    return (m_error);
}

ostream &operator<<(ostream &flux, XenNote const& xenNote)
{
    xenNote.toFlux(flux);
    return (flux);
}
