#ifndef XEN_TRACK_H
#define XEN_TRACK_H

#include <string>
#include <vector>
#include "MidiEventList.h"
#include "XenNote.h"

#define DEFAULT_BPM 120

class XenTrack
{
public:
    XenTrack(const std::string &trackname);
    XenTrack(const std::string &trackname, MidiEventList &midiTrack, int tpq);

    bool createFromMidi(MidiEventList &midiTrack, int tpq);
    size_t size() const;
    bool error() const;

protected:
    std::string m_name;
    vector<XenNote> m_data;
    bool m_error;

    int tickToCenti(int tick, int tpq, const MidiEvent &event) const;
    void sortEvents(MidiEventList &events);
};

#endif
