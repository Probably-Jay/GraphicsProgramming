#include "Spaceship.h"

Spaceship::Spaceship() {
	

}


Spaceship::~Spaceship() {


}

void Spaceship::initialise(ModelManager& modelManager)
{
	//((Object*)this)->initialise(info, modelManager);
	Object::initialise(info, modelManager);
}
