#include "SubModuleEditorCamera.h"
#include "ModuleCamera.h"
#include "Application.h"
#include "imgui.h"


SubModuleEditorCamera::SubModuleEditorCamera()
{
}


SubModuleEditorCamera::~SubModuleEditorCamera()
{
}

bool SubModuleEditorCamera::drawSubmodule()
{	
	if (ImGui::CollapsingHeader("Camera"))
	{		
		drawVector3Line(App->camera->forward, "Forward");
		drawVector3Line(App->camera->up, "Up");
		drawVector3Line(App->camera->right, "Right");
		drawVector3Line(App->camera->camPos, "Position");
		ImGui::Separator();
		ImGui::SliderFloat("Vertical FOV", &App->camera->vFov, 10.f, 180.f);

	}
	return true;
}

void SubModuleEditorCamera::drawVector3Line(const math::float3 &vector, const char* text) const
{
	ImVec2 pos = ImGui::GetCursorScreenPos();

	int boxHeight = 16;
	ImGui::Columns(4);

	int boxWidth = ImGui::GetColumnWidth() - 10;

	ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(pos.x - 2, pos.y), ImVec2(pos.x + boxWidth, pos.y + boxHeight), IM_COL32(100, 100, 100, 255));
	ImGui::Text("X: %.3f", vector.x);

	ImGui::NextColumn();

	pos = ImGui::GetCursorScreenPos();
	ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(pos.x - 2, pos.y), ImVec2(pos.x + boxWidth, pos.y + boxHeight), IM_COL32(100, 100, 100, 255));
	ImGui::Text("Y: %.3f", vector.y);

	ImGui::NextColumn();
	pos = ImGui::GetCursorScreenPos();
	ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(pos.x - 2, pos.y), ImVec2(pos.x + boxWidth, pos.y + boxHeight), IM_COL32(100, 100, 100, 255));
	ImGui::Text("Z: %.3f", vector.z);

	ImGui::NextColumn();
	ImGui::Text(text);

	ImGui::Columns(1);
	
}
