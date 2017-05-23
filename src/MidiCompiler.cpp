#include "MidiCompiler.h"
#include <iostream>

using namespace std;

MidiCompiler::MidiCompiler(string const &filename) : m_filename(filename),
    m_name(filename), m_status(STATUS_OK)
{
    size_t nameExtPos(m_name.find_last_of('.'));

    if (nameExtPos != string::npos)
        m_name = m_name.substr(0, nameExtPos);
}

bool MidiCompiler::open()
{
    if (m_midiFile.read(m_filename)) {
        m_midiFile.absoluteTicks();
        m_status = STATUS_OK;
        return (true);
    }
    else {
        m_status = STATUS_ERROR_OPENFILE;
        return (false);
    }
}

bool MidiCompiler::read()
{
    for (int track = 0; track < m_midiFile.getTrackCount(); ++track)
    {
        if (m_midiFile[track].size())
        {
            XenWriter xenTrack(m_name, m_midiFile[track], m_midiFile.getTPQ());
            if (xenTrack.error())
            {
                m_status = STATUS_ERROR_TRACKNOTE;
                return (false);
            }
            else if (xenTrack.size())
                m_tracks.push_back(xenTrack);
        }
    }
    return (true);
}

char MidiCompiler::status() const
{
    return (m_status);
}

size_t MidiCompiler::getTrackCount() const
{
    return (m_tracks.size());
}

size_t MidiCompiler::getTrackSize(size_t track) const
{
    if (track >= m_tracks.size())
        return (0);

    return (m_tracks[track].size());
}

string MidiCompiler::getName() const
{
    return (m_name);
}

bool MidiCompiler::writeTrackBinary(size_t track)
{
    if (track >= m_tracks.size())
        return (false);

    if (!m_tracks[track].writeBinary())
    {
        m_status = STATUS_ERROR_COMPILE;
        return (false);
    }

    return (true);
}

bool MidiCompiler::writeTrackC(size_t track)
{
    if (track >= m_tracks.size())
        return (false);

        if (!m_tracks[track].writeC())
        {
            m_status = STATUS_ERROR_COMPILE;
            return (false);
        }

    return (true);
}
