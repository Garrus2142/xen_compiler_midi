#ifndef XEN_NOTE_H
#define XEN_NOTE_H

#include <vector>
#include <iostream>
#include <cmath>
#include "MidiEvent.h"

class XenNote
{
public:
    XenNote(int midiNote, int length, int delay = 0);

    std::vector<unsigned char> compile() const;
    void toFlux(std::ostream &flux) const;

    unsigned char getMidiNote() const;
    unsigned char getXenNote() const;
    unsigned char getLength() const;
    unsigned char getDelay() const;

    void setDelay(int delay);

    bool error() const;

private:
    unsigned char m_midiNote;
    unsigned char m_length;
    unsigned char m_delay;
    bool m_error;
};

std::ostream &operator<<(std::ostream &flux, XenNote const& xenNote);

#endif
