#include "Waterflow.h"

void Waterflow::Start(spe::EngineConfig& cnfg, const std::string& scene)
{
	if (scene == "scene 1")
	{
		std::vector<spe::Sprite*> waterSprites;
		cnfg.ptr_Sprites->GetSpritesByTag("water", waterSprites);
		for (size_t i = 0; i < waterSprites.size(); i++)
		{
			waterSprites[i]->Animator.Play("WaterFlow");
		}
	}
}

void Waterflow::Update()
{

}

