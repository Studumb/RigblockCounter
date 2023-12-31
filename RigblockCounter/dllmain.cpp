// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "AddCounter.h"
#include "UpdateValue.h"

void Initialize()
{
	//We will have two message listener for two different purposes
	//This one is used to add the counter to the current editor
	MessageManager.AddListener(new AddCounter(), App::kMsgOnModeEnter);
	//This one is used to count the total rigblock and update the value shown on the counter
	MessageManager.AddListener(new UpdateValue(), App::kMsgAppUpdate);
}

void Dispose()
{
	// This method is called when the game is closing
}

void AttachDetours()
{
	// Call the attach() method on any detours you want to add
	// For example: cViewer_SetRenderType_detour::attach(GetAddress(cViewer, SetRenderType));
}


// Generally, you don't need to touch any code here
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		ModAPI::AddPostInitFunction(Initialize);
		ModAPI::AddDisposeFunction(Dispose);

		PrepareDetours(hModule);
		AttachDetours();
		CommitDetours();
		break;

	case DLL_PROCESS_DETACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	}
	return TRUE;
}

