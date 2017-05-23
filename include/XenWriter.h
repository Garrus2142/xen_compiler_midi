#ifndef XEN_WRITER_H
#define XEN_WRITER_H

#include <string>
#include <fstream>
#include <vector>
#include "XenTrack.h"

class XenWriter : public XenTrack
{
public:
    XenWriter(const std::string &trackname);
    XenWriter(const std::string &trackname, MidiEventList &midiTrack, int tpq);

    bool writeBinary(const std::string &path = "");
    bool writeBinary(const std::string &filename, const std::string &path);

    bool writeC(const std::string &path = "");
    bool writeC(const std::string &filename, const std::string &path);

private:
    std::string getFullPath(const std::string &filename, const std::string &path) const;
};

#endif
