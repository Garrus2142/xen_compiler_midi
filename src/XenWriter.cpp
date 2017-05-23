#include "XenWriter.h"

using namespace std;

// Constructors

XenWriter::XenWriter(const string &trackname) : XenTrack(trackname)
{

}

XenWriter::XenWriter(const string &trackname, MidiEventList &midiTrack, int tpq) :
    XenTrack(trackname, midiTrack, tpq)
{

}

// Public functions

bool XenWriter::writeBinary(const string &path)
{
    return (writeBinary(m_name + ".bin", path));
}

bool XenWriter::writeBinary(const string &filename, const string &path)
{
    ofstream file(getFullPath(filename, path), ofstream::out | ofstream::binary);

    if (file)
    {
        for (size_t note = 0; note < size(); ++note)
        {
            vector<unsigned char> bytes(m_data[note].compile());

            for (size_t byte = 0; byte < bytes.size(); ++byte)
                file << bytes[byte];
        }
        return (true);
    }
    else {
        m_error = true;
        return (false);
    }
}

bool XenWriter::writeC(const string &path)
{
    return (writeC(m_name + ".c", path));
}

bool XenWriter::writeC(const string &filename, const string &path)
{
    ofstream file(getFullPath(filename, path), ofstream::out);

    if (file)
    {
        size_t totalSize(0);

        file << "/*" << endl << "** Music: " << m_name << endl << "*/" << endl;
        file << "unsigned char data[] = {" << endl;

        for (size_t note = 0; note < size(); ++note)
        {
            vector<unsigned char> bytes(m_data[note].compile());

            file << "\t";
            for (size_t byte = 0; byte < bytes.size(); ++byte)
            {
                file << (int)bytes[byte];
                if (byte < bytes.size() - 1)
                    file << ", ";
                else if (note < size() - 1)
                    file << ",";
                    ++totalSize;
            }
            file << endl;
        }
        file << "};" << endl;

        // Write size
        file << "unsigned int length = " << totalSize << ";" << endl;

        return (true);
    }
    else {
        m_error = true;
        return (false);
    }
}

// Private functions
string XenWriter::getFullPath(const string &filename, const string &path) const
{
    string fullpath(path);

    if (path.size() > 0 && path[path.size() - 1] != '/')
        fullpath += "/";
    fullpath += filename;

    return (fullpath);
}
