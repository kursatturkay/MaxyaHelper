#pragma once
#include "TemplateTimer.h"

std::string GetUserDocumentsFolderPath();
MString GetCurrentUserDocumentMaxyaLogPath(const MString& logFileName, bool amayacompatible);


class TextDocument
{
public:
    bool  init(char *filename);


ULONG getline(ULONG lineno, char *buf, size_t len);
ULONG linecount();

private:
bool init_linebuffer();

char *buffer;
int length;
};

class CTimerTest
{
public:
    void RunTest();
	void ReadandExecFile();
	bool FileExists(const char* filename);

private:
    void OnTimedEvent1();
    void OnTimedEvent2();

    TTimer<CTimerTest> timer1 ;
    TTimer<CTimerTest> timer2 ;
};
