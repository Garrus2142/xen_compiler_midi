#include "XenTrack.h"
#include <iostream>

using namespace std;

// Constructeurs

XenTrack::XenTrack(const string &trackname) : m_name(trackname), m_error(false)
{

}

XenTrack::XenTrack(const string &trackname, MidiEventList &midiTrack, int tpq) :
    m_name(trackname), m_error(false)
{
    createFromMidi(midiTrack, tpq);
}

// Fonctions publique

bool XenTrack::createFromMidi(MidiEventList &midiTrack, int tpq)
{
    m_data.clear();

    midiTrack.linkNotePairs();
    sortEvents(midiTrack);

    // Parcours de tout les messages midi (NoteOn et NoteOff)
    size_t nEvents(midiTrack.size());
    MidiEvent *currentOn(NULL);

    for (size_t i = 0; i < nEvents; ++i)
    {
        if (midiTrack[i].isNoteOn() && midiTrack[i].isLinked() && !currentOn)
        {
            // Find next NoteOn for delay
            MidiEvent *nextOn(NULL);
            for (size_t u = i + 1; u < nEvents; ++u)
            {
                if (midiTrack[u].isNoteOn())
                {
                    nextOn = &(midiTrack[u]);
                    break;
                }
            }

            // Création de la note
            XenNote xenNote(midiTrack[i][1], tickToCenti(midiTrack[i].getTickDuration(), tpq, midiTrack[i]),
                nextOn ? tickToCenti(nextOn->tick - (midiTrack[i].tick + midiTrack[i].getTickDuration()),
                tpq, midiTrack[i]) : 0);

            // Enregistre la note
            if (!xenNote.error() && xenNote.getLength() > 1)
            {
                currentOn = &(midiTrack[i]);
                m_data.push_back(xenNote);
            }
            else if (xenNote.error()) {
                m_error = true;
                return (false);
            }
        }
        else if (midiTrack[i].isNoteOff() && midiTrack[i].isLinked() &&
            currentOn && (*currentOn)[1] == midiTrack[i][1])
        {
            currentOn = NULL;
        }
    }

    // Supprimer le delay de la dernière note
    if (m_data.size() > 0)
        m_data[m_data.size() - 1].setDelay(0);

    return (true);
}

size_t XenTrack::size() const
{
    return (m_data.size());
}

bool XenTrack::error() const
{
    return (m_error);
}

// Private function

int XenTrack::tickToCenti(int tick, int tpq, const MidiEvent &event) const
{
    return (tick * 6000 / (tpq * (event.isTempo() ? event.getTempoBPM() : DEFAULT_BPM)));
}

void XenTrack::sortEvents(MidiEventList &events)
{
    size_t nEvents(events.size());
    MidiEvent *currentOn(NULL);

    for (size_t i = 0; i < nEvents; ++i)
    {
        if (events[i].isNoteOn() && !currentOn)
            currentOn = &(events[i]);
        else if (events[i].isNoteOff() && currentOn && (*currentOn)[1] == events[i][1])
            currentOn = NULL;
        else if (events[i].isNoteOn() && currentOn)
        {
            if (i + 1 < nEvents && events[i + 1].isNoteOff() && events[i + 1].tick == events[i].tick
                && events[i + 1][1] == (*currentOn)[1])
            {
                events[i].swap(events[i + 1]);
                currentOn = NULL;
            }
        }
    }
}
