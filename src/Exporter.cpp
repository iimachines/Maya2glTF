#include "externals.h"

#include "Arguments.h"
#include "ExportableAsset.h"
#include "Exporter.h"
#include "MayaException.h"
#include "OutputWindow.h"

Exporter::Exporter() = default;

Exporter::~Exporter() = default;

void *Exporter::createInstance() { return new Exporter(); }

void Exporter::printFatalError() {
    std::stringstream ss;
    ss << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
          "!"
       << endl;
    ss << "Ouch something went really wrong (an access violation occurred) :-( "
          " "
       << endl;
    ss << "Your Maya scene might be corrupt! Save to a *temp* file, and "
          "restart "
       << endl;
    ss << "We're sorry for the inconvenience. Please file a bug report at:     "
          " "
       << endl;
    ss << "https://github.com/Ziriax/maya2glTF/issues                          "
          " "
       << endl;
    ss << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
          "!"
       << endl;

    const auto message = ss.str();
    cerr << message << endl;

    const auto command = MString("print ") + escaped(message).c_str();
    MGlobal::executeCommand(command);
}

#ifdef _MSC_VER

#include <excpt.h>
#include <windows.h>

int filter(const unsigned int code, struct _EXCEPTION_POINTERS *ep) {
    return code == EXCEPTION_ACCESS_VIOLATION ? EXCEPTION_EXECUTE_HANDLER
                                              : EXCEPTION_CONTINUE_SEARCH;
}

MStatus Exporter::doIt(const MArgList &args) {
    __try {
        // https://forums.autodesk.com/t5/maya-programming/c-api-not-printing-to-output-window/td-p/4260798/page/2
        cout.set_rdbuf(MStreamUtils::stdOutStream().rdbuf());
        cerr.set_rdbuf(MStreamUtils::stdErrorStream().rdbuf());

        auto status = run(args);
        return status;
    } __except (filter(GetExceptionCode(), GetExceptionInformation())) {
        printFatalError();

        assert(false);
        return MStatus::kFailure;
    }
}

#else

MStatus Exporter::doIt(const MArgList &args) {
    auto status = run(args);
    return status;
}

#endif

bool Exporter::isUndoable() const { return false; }

bool Exporter::hasSyntax() const { return true; }

void Exporter::exportScene(const Arguments &args) {
    ExportableAsset exportableAsset(args);
    exportableAsset.save();
}

MStatus Exporter::run(const MArgList &args) const {
    try {
        std::cout << prefix << "Parsing arguments..." << endl;
        const Arguments arguments(args, syntax());

        if (arguments.clearOutputWindow) {
            OutputWindow().clear();
        }

        std::cout << prefix << "Starting export..." << endl;
        exportScene(arguments);

        std::cout << prefix << "Finished export :-)" << endl;
        std::cout << "---------------------------------------------------------"
                     "-----------------------"
                  << endl;

        return MStatus::kSuccess;
    } catch (const MayaException &ex) {
        MayaException::printError(ex.what(), ex.status);
    } catch (const std::exception &ex) {
        MayaException::printError(ex.what());
    } catch (...) {
        MayaException::printError("Unexpected fatal error!");
    }

    return MStatus::kFailure;
}
