// DisableCriticalProcesses.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"
#include "Header.h"

 
int ThreadCallback(ulonglong ThreadId)
{
	HANDLE hThread = OpenThread(THREAD_SET_INFORMATION,FALSE,ThreadId);
	if(hThread)
	{
		ulong Set_Unset = 0;
		int ret = ZwSetInformationThread(hThread,ThreadBreakOnTermination,&Set_Unset,0x4);
		printf("(TID: %I64X) ZwSetInformationThread, ret: %X\r\n",ThreadId,ret);
		//getchar();
		CloseHandle(hThread);
		if(ret < 0) return ret;
		return 0;
	}
	return -1;
}


int ProcessCallback(ulonglong ProcessId)
{
	HANDLE hProcess = OpenProcess(PROCESS_SET_INFORMATION ,FALSE,ProcessId);
	if(hProcess)
	{
		ulong Set_Unset = 0;
		int ret = ZwSetInformationProcess(hProcess,ProcessBreakOnTermination,&Set_Unset,0x4);
		printf("(PID: %I64X) ZwSetInformationProcess, ret: %X\r\n",ProcessId,ret);
		//getchar();
		CloseHandle(hProcess);
		if(ret < 0) return ret;
		return 0;
	}
	return -1;
}

int _tmain(int argc, _TCHAR* argv[])
{
	bool bRet = Acquire_Debug();
	if(!bRet)
	{
		printf("Can't acquire SeDebugPrvilege\r\n");
		return -1;
	}

	while(1)
	{
		EnumThreads(ProcessCallback,ThreadCallback);
		//getchar();
	}
	return 0;
}

