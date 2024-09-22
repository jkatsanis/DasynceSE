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

void LightFlickering::Update(spe::EngineConfig& cnfg)
{
	if (alltimer > 1.0f)
	{
		alltimer = 0.0f;

		if (light != nullptr)
		{
			this->light->Light.SetRadius(radius);
		}

		this->light = this->lights.at(spe::GameUtils::Random(0, this->lights.size() - 1));
		
		radius = this->light->Light.GetRadius();

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
		light->Light.SetRadius(radius);
		spe::Log::LogString("Fliuck on");
		timer = 0.0f;
		return;
	}

	if (timer > 1.0f)
	{
		madebig = false;
		flick = true;

		spe::Log::LogString("Fliuck");
		light->Light.SetRadius(0);
		timer = 0.0f;
	}
}

