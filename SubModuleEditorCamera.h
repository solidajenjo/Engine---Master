#ifndef __SUB_MODULE_EDITOR_CAMERA_H
#define __SUB_MODULE_EDITOR_CAMERA_H

#include "SubModuleEditor.h"
#include "MathGeoLib.h"


class SubModuleEditorCamera :
	public SubModuleEditor
{
public:
	SubModuleEditorCamera();
	~SubModuleEditorCamera();
	
	bool drawSubmodule();

	void drawVector3Line(const math::float3 & vector, const char * text) const;

};

#endif // !
