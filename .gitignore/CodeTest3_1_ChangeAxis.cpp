// CodeTest3_1_ChangeAxis.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fbxsdk.h>
#include <fbxsdk/fileio/fbxiosettings.h> 


int _tmain(int argc, _TCHAR* argv[])
{
	FbxManager* mySdkManager = FbxManager::Create();

	FbxIOSettings* ios = FbxIOSettings::Create((FbxManager *) mySdkManager, IOSROOT);
	mySdkManager->SetIOSettings(ios);

	FbxImporter* myImporter = FbxImporter::Create(mySdkManager, "");

	const char* myFbxFile = "oa_vanille_anim.fbx";
	bool myImporterStatus = myImporter->Initialize(myFbxFile);

	if (!myImporterStatus) {
		printf("FbxImporter Initialize failed \n");
		printf("Error: %s \n", myImporter->GetStatus().GetErrorString());
		printf("Error: %i \n", myImporter->GetStatus().GetCode());
		exit(EXIT_FAILURE);
	}
	
	FbxScene* myScene = FbxScene::Create(mySdkManager, "");

	myImporter->Import(myScene);
	printf("File %s imported \n", myFbxFile);
	myImporter->Destroy();

	int upSign;
	int upDir = myScene->GetGlobalSettings().GetAxisSystem().GetUpVector(upSign);

	printf("%s intial up vector is %i \n 1 - X Up		 2 - Y Up		3 - Z Up \n", myFbxFile, upDir);

	FbxAxisSystem myAxis = FbxAxisSystem(fbxsdk::FbxAxisSystem::EPreDefinedAxisSystem::eMayaYUp);
	
	myAxis.ConvertScene(myScene);

	upDir = myScene->GetGlobalSettings().GetAxisSystem().GetUpVector(upSign);
	printf("%s new up vector is %i \n 1 - X Up		 2 - Y Up		3 - Z Up \n", myFbxFile, upDir);
 
	FbxExporter * myExporter = FbxExporter::Create(mySdkManager, "");
	const char *myNewFile = "ed_oa_vanille_anim.fbx";

	bool myExporterStatus = myExporter->Initialize(myNewFile, -1, ios);

	if (!myExporterStatus) {
		printf("FbxImporter Initialize failed \n");
		printf("Error: %s \n", myImporter->GetStatus().GetErrorString());
		printf("Error: %i \n", myImporter->GetStatus().GetCode());
		exit(EXIT_FAILURE);
	}

	myExporter->Export(myScene);
	printf("File %s exported \n", myNewFile);
	myExporter->Destroy();

	return 0;
}

