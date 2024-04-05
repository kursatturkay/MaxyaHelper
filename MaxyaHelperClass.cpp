#include <maya/MIOStream.h>
#include <maya/MFnPlugin.h>
#include <maya/MSimple.h>
#include <maya/MGlobal.h>
#include "TimerTest.h"


CTimerTest timerTest;




//!!!DeclareSimpleCommand( helloWorld, PLUGIN_COMPANY, "2011");

//MGlobal::executeCommandOnIdle("source \"C:\\input.mel\"");

// All we need to do is supply the doIt method
// which in this case is only a Hello World example
//

/*!!!
MStatus helloWorld::doIt( const MArgList& )
{
	timerTest.RunTest();
	cout<<"Hello World"<<endl;
	return MS::kSuccess;
}
*/





MStatus initializePlugin(MObject obj)
{

	MFnPlugin plugin(obj, "Maya Helper Plugin", "1.0", "Any");

	MString maxyaoutput = "maxyaoutput.log";
	MString logFilePath = GetCurrentUserDocumentMaxyaLogPath(maxyaoutput,true);


	MString hf("scriptEditorInfo -e -hfn \"" + logFilePath + "\" - wh 1; ");

	MGlobal::displayInfo(hf);


	MString hf2("scriptEditorInfo -e -chf;");

	MStatus hfOK = MGlobal::executeCommand(hf);

	MGlobal::executeCommand(hf2);

	MStringArray res_;
	//MGlobal::executeCommand(MString("polySphere;"),res_);

	if (hfOK != MS::kSuccess)
	{
		MGlobal::displayInfo("Maxya Helper Plugin Error:history file could not be initialized");
		return MS::kFailure;
	}

	else
	{
		

		MGlobal::displayInfo("Maxya Helper Plugin Loaded");
		timerTest.RunTest();
		return MS::kSuccess;
	}
}

MStatus uninitializePlugin(MObject obj)
{
	remove(GetCurrentUserDocumentMaxyaLogPath("inputcmd.mel",false).asChar());
	remove(GetCurrentUserDocumentMaxyaLogPath("inputcmd.py",false).asChar());
	
	remove(GetCurrentUserDocumentMaxyaLogPath("inputbatch.mel",false).asChar());

	remove(GetCurrentUserDocumentMaxyaLogPath("inputbatch.py",false).asChar());

	remove(GetCurrentUserDocumentMaxyaLogPath("maxyaoutput.log",false).asChar());
	

	MFnPlugin plugin(obj);
	MGlobal::displayInfo("Maxya Helper Plugin Unloaded");
	return MS::kSuccess;
}

