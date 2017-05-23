#include <iostream>
#include <vector>
#include <string>
#include "ArgsParser.h"
#include "MidiCompiler.h"

using namespace std;

static void printUsage(const char *name)
{
    cout << "Usage: " << name << " [-hcbd] [file ...]" << endl;
}

static void printHelp(const char *name)
{
    cout << "Xen Compiler MIDI" << endl;
    printUsage(name);
    cout << endl;

    cout << "-h: " << "Affiche l'aide." << endl;
    cout << "-c: " << "Compile le fichier en c." << endl;
    cout << "-b: " << "Compile le fichier en binaire. (Action par défaut)" << endl;
    cout << "-d: " << "Affiche les détails." << endl;
}

static int requestTrack(const ArgsParser &argsParser, const MidiCompiler &midiCompiler, const string &filename)
{
    size_t track(0);

    cout << midiCompiler.getTrackCount() << " piste(s) ont été détecté dans le fichier " << filename << endl;

    if (argsParser.hasOption('d'))
    {
        for (size_t i = 0; i < midiCompiler.getTrackCount(); ++i)
            cout << "Piste " << i + 1 << ": " << midiCompiler.getTrackSize(i) << " note(s)." << endl;
    }
    else
        cout << "(Utilisez l'option -d pour afficher les détails)" << endl;

    do
    {
        cout << "Veuillez séléctionner la piste à compiler: ";
        cin >> track;
    } while (track < 1 || track > midiCompiler.getTrackCount());

    return (track);
}

static void processCompile(const ArgsParser &argsParser)
{
    vector<string> midifiles(argsParser.getOperands());

    for (size_t i = 0; i < midifiles.size(); ++i)
    {
        int trackSelected(0);
        MidiCompiler midiCompiler(midifiles[i]);

        if (!midiCompiler.open()) {
            cerr << "XenCompilerMidi: Impossible d'ouvrir le fichier " << midifiles[i] << endl;
            continue;
        }

        if (!midiCompiler.read()) {
            if (midiCompiler.status() == MidiCompiler::STATUS_ERROR_TRACKNOTE)
                cerr << "XenCompilerMidi: Impossible de lire le fichier " << midifiles[i] << ", note midi inconnue." << endl;
            continue;
        }

        if (midiCompiler.getTrackCount() > 1)
            trackSelected = requestTrack(argsParser, midiCompiler, midifiles[i]) - 1;

        if (argsParser.hasOption('c'))
            midiCompiler.writeTrackC(trackSelected);
        else
            midiCompiler.writeTrackBinary(trackSelected);

        if (midiCompiler.status() == MidiCompiler::STATUS_ERROR_COMPILE)
            cerr << "XenMidiCompiler: Erreur lors de la compilation du fichier " << midifiles[i] << endl;
        else if (midiCompiler.status() == MidiCompiler::STATUS_OK) {
            cout << "Compilation du fichier " << midiCompiler.getName() << (argsParser.hasOption('c') ? ".c" : ".bin")
                << " effectué." << endl;
        }
    }
}

int main(int argc, char **argv)
{
    ArgsParser argsParser(argc, argv, "hcbd");

    if (argsParser.hasError()) {
        printUsage(argv[0]);
        return (EXIT_FAILURE);
    }

    if (argsParser.hasOption('h'))
    {
        printHelp(argv[0]);
        return (EXIT_SUCCESS);
    }

    if (!argsParser.getOperands().size())
    {
        cerr << "XenCompilerMidi: Vous devez spécifier au moin 1 fichier à compiler." << endl;
        return (EXIT_FAILURE);
    }

    processCompile(argsParser);

    return (EXIT_SUCCESS);
}
