#include <sstream> 
#include <fstream>
#include <shlobj.h>
#include <PathCch.h>
#include <windows.h>
#include <iostream>
#include <Lmcons.h>

#include <maya/MGlobal.h>
#include <maya/MFileIO.h>

#include "TimerTest.h"



std::string GetUserDocumentsFolderPath() {
	TCHAR szPath[MAX_PATH];
	if (SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, 0, szPath) != S_OK) {
		return ""; // Başarısız olduysa boş bir dize döndür
	}
	return std::string(szPath);
}

MString GetCurrentUserDocumentMaxyaLogPath(const MString& logFileName, bool amayacompatible) {
	std::string documentsFolderPath = GetUserDocumentsFolderPath();
	if (documentsFolderPath.empty()) {
		return ""; // Kullanıcı belgeleri klasörü bulunamadı
	}

	std::string username = "";
	TCHAR szUsername[UNLEN + 1];
	DWORD dwSize = UNLEN + 1;
	if (GetUserName(szUsername, &dwSize)) {
		username = szUsername;
	}
	else {
		return ""; // Kullanıcı adı alınamadı
	}

	TCHAR szBuffer[MAX_PATH];
	if (PathCombine(szBuffer, documentsFolderPath.c_str(), "Maxya") == NULL) {
		return ""; // Dosya yolu birleştirilemedi
	}

	// Maxya dizinini oluştur
	if (!CreateDirectory(szBuffer, NULL) && GetLastError() != ERROR_ALREADY_EXISTS) {
		return ""; // Dizin oluşturulamadı
	}

	if (PathCombine(szBuffer, szBuffer, logFileName.asChar()) == NULL) {
		return ""; // Dosya yolu birleştirilemedi
	}

	//cout << szBuffer;

	if (amayacompatible)
	{
		// '\\' karakterlerini Maya uyumlu hale getir
		std::string mayaCompatiblePath = szBuffer;
		for (char& c : mayaCompatiblePath) {
			if (c == '\\') {
				c = '/';
			}
		}
		return MString(mayaCompatiblePath.c_str());
		//////////
	}
	return MString(szBuffer);
}

using namespace std;

bool CTimerTest::FileExists(const char* filename) {

	ifstream file;
	file.open(filename);
	// Check if the file exists
	if (file.is_open() == true) {
		file.close();
		return true;
	}
	return false;
}


void CTimerTest::ReadandExecFile()
{
	/*
   ifstream insert;
	ofstream output;
	string lineread;
	string Fileread;
	insert.open("C:\\test.txt");

	   if(insert.fail())
	   {
		   MGlobal::displayInfo("File failed to open");
	   }

		while(!insert.eof())
	   {
		 getline(insert,lineread);
		 Fileread+=lineread;
	   }

		MString mstr;

		mstr.set(Fileread.c_str());
		MGlobal::executeCommand(mstr);
		*/

		///MStatus MS=MGlobal::sourceFile("C:\\test.txt");
	MStatus MS = MS::kSuccess;
	//MString MCmdResult;


	MString s1_ = MString("source \"" + GetCurrentUserDocumentMaxyaLogPath("inputbatch.mel",true));
	MString s2_ = GetCurrentUserDocumentMaxyaLogPath("inputcmd.mel",false);
	MString s0_ = GetCurrentUserDocumentMaxyaLogPath("inputbatch.mel",false);

	//inputcmd.py
	MString s3_ = GetCurrentUserDocumentMaxyaLogPath("inputcmd.py",false);

	/*
	MGlobal::displayInfo("s1_ " + s1_ + "\n");
	MGlobal::displayInfo("s2_ " + s2_ + "\n");
	MGlobal::displayInfo("s0_ " + s0_ + "\n");
	MGlobal::displayInfo("s3_ " + s3_ + "\n");
	*/

	//if(FileExists("C:\\inputbatch.mel"))
	if (FileExists(s0_.asChar()))
	{
		MStringArray res_;
		//MS=MGlobal::executeCommandOnIdle(MString( "source \"C:/inputbatch.mel\""),true);
	}
	//else if(FileExists("C:\\inputcmd.mel"))
	else if (FileExists(s2_.asChar()))
	{
		std::ifstream t(s2_.asChar());
		std::stringstream buffer;
		buffer << t.rdbuf();
		MString MStrCmd = buffer.str().c_str();
		MStringArray res_;
		const MGlobal::MMayaState mayaState = MGlobal::mayaState();
		//MS=MGlobal::executeCommandOnIdle(MStrCmd,res_);
		MGlobal::executeCommandOnIdle(MStrCmd, true);
		t.close();
		//MGlobal::displayInfo(res_[0]);

		if (MS != MStatus::kSuccess)
		{
			MGlobal::displayError("Maxya > Cannot Execute");
		}
		else if (MS == MStatus::kSuccess)
		{
			//remove("C:\\inputcmd.mel");
			remove(s2_.asChar());
		}

	}
	// else if(FileExists("C:\\inputcmd.py"))
	else if (FileExists(s3_.asChar()))
	{
		std::ifstream t(s3_.asChar());
		std::stringstream buffer;
		buffer << t.rdbuf();
		MString MStrCmd = buffer.str().c_str();
		MStringArray res_;
		const MGlobal::MMayaState mayaState = MGlobal::mayaState();
		MGlobal::executePythonCommandOnIdle(MStrCmd, true);
		t.close();

		if (MS != MStatus::kSuccess)
		{
			MGlobal::displayError("Maxya > Cannot Execute");
		}
		else if (MS == MStatus::kSuccess)
		{
			//remove("C:\\inputcmd.py");
			remove(s3_.asChar());
		}
	}

	// MStatus status = MS::kSuccess;


	 /*

	  //ofstream oStream("C:\\output.log",ios::out);
		//std::string other = MCmdResult.asChar();
		//oStream<<other;
		//oStream.close();


	 MString someStr;
	std::string other = someStr.asChar();
	MString someOtherStr = other.c_str();
	 */


	 //insert.close();

}

void CTimerTest::OnTimedEvent1()
{
	//printf("\r\nTimer 1  Called (count=%i)", timer1.GetCount());
	//ofstream filestr;
	//filestr.open ("deneme123.txt", fstream::in | fstream::out | fstream::app);
	//filestr<<"YAY"<<endl;
	//filestr.close();
	ReadandExecFile();
	/*MString s;
	//char* asd;
	asd="polySphere";

	s=asd;
	MGlobal::executeCommandOnIdle(s);
	*/
}

void CTimerTest::OnTimedEvent2()
{
	//printf("\r\nTimer  2 Called (count=%i)", timer2.GetCount());
}

void CTimerTest::RunTest()
{
	printf("Hit return to start and stop timers");

	//getchar();

	timer1.SetTimedEvent(this, &CTimerTest::OnTimedEvent1);
	timer1.Start(400); // Start timer 1 every 1s

	//timer2.SetTimedEvent(this, &CTimerTest::OnTimedEvent2);
	//timer2.Start(2000); // Start timer 2 every 2s

	// Do something, in this case just wait for user to hit return   
	//getchar();          // Wait for return (stop)

	//timer1.Stop();      // Stop timer 1
	//timer2.Stop();      // Stop timer 2

	printf("\r\nTimers stopped (hit return to exit)");
	//getchar();
}
