#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "il.h"
#include "ilut.h"
#include "ilu.h"

using namespace std;

ModuleTextures::ModuleTextures()
{
	ilInit();
	iluInit();
	ilutInit();
}

// Destructor
ModuleTextures::~ModuleTextures()
{
}

// Called before render is available
bool ModuleTextures::Init()
{
	bool ret = true;

	return ret;
}

// Called before quitting
bool ModuleTextures::CleanUp()
{
	return true;
}

// Load new texture from file path
unsigned char * ModuleTextures::Load(const char* path, int &xSize, int &ySize)
{
	ILuint ImageName;
	ilGenImages(1, &ImageName);

	ilBindImage(ImageName);
	ilLoadImage(path);

	ILinfo ImageInfo;
	iluGetImageInfo(&ImageInfo);
	if (ImageInfo.Origin == IL_ORIGIN_UPPER_LEFT)
	{
		iluFlipImage();
	}
	xSize = ImageInfo.Width;
	ySize = ImageInfo.Height;
	return ilGetData();
}


