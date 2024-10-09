#include "LightFlickering.h"

void LightFlickering::Start(spe::EngineConfig& cnfg)
{
	alltimer = 2.0f;
	bigtimer = 0.0f;
	madebig = false;
	this->timer = 0.0f;
	this->light = nullptr;

	cnfg.ptr_Sprites->GetSpritesByTag("Light", this->lights);
}

void LightFlickering::Update()
{
	if (alltimer > 1.0f)
	{
		alltimer = 0.0f;

		if (light != nullptr)
		{
			this->light->Light.SetRadius((float)radius);
		}

		this->light = this->lights.at((size_t)spe::GameUtils::Random(0, int32_t(this->lights.size() - 1)));
		
		radius = (int)this->light->Light.GetRadius();

	}

	alltimer += spe::Time::s_DeltaTime;
	timer += spe::Time::s_DeltaTime;

	if (flick && !madebig)
	{
		bigtimer += spe::Time::s_DeltaTime;
		if (bigtimer > 0.1f)
		{
			bigtimer = 0.0f;
			madebig = false;
			flick = false;
			timer = 0.0f;
		}
		return;
	}

	if (timer < 1.0f && !madebig)
	{
		madebig = true;
		light->Light.SetRadius((float)radius);
		timer = 0.0f;
		return;
	}

	if (timer > 1.0f)
	{
		madebig = false;
		flick = true;

		light->Light.SetRadius(0);
		timer = 0.0f;
	}
}

