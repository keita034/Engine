#include "Particle.h"
#include"BasicParticle.h"
#include"RainParticle.h"

BasicParticle* Particle::CreateParticle()
{
	BasicParticle* basic = new BasicParticle;
	basic->Initialize();
	return basic;
}

RainParticle* Particle::CreateRainParticle()
{
	RainParticle* rain = new RainParticle;
	rain->Initialize();
	return rain;
}
