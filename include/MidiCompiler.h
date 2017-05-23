#ifndef MIDI_COMPILER_H
#define MIDI_COMPILER_H

#include <string>
#include <vector>
#include "MidiFile.h"
#include "XenWriter.h"

class MidiCompiler
{
public:
    static const char STATUS_OK = 0;
    static const char STATUS_ERROR_OPENFILE  = 1;
    static const char STATUS_ERROR_TRACKNOTE = 2;
    static const char STATUS_ERROR_COMPILE = 3;

    MidiCompiler(const std::string &filename);

    bool open();
    bool read();
    char status() const;

    size_t getTrackCount() const;
    size_t getTrackSize(size_t track) const;

    std::string getName() const;
    bool writeTrackBinary(size_t track);
    bool writeTrackC(size_t track);


private:
    std::string m_filename;
    std::string m_name;
    MidiFile m_midiFile;
    char m_status;
    std::vector<XenWriter> m_tracks;
};

#endif
