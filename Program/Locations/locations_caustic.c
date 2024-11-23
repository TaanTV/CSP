
// 18.01.2023-24.01.2023
// Mett: скрипт каустики в локациях для CSP
// скрипт подключать в locations.c
// через #include "Locations\locations_caustic.c"

#event_handler(EVENT_LOCATION_LOAD, "LoadLocationCausticEvent");

#define LOCATION_CAUSTIC_MODEL              "caustic"
#define LOCATION_CAUSTIC_TECH               "LocationCaustic"
#define LOCATION_CAUSTIC_LEVEL              50

void LoadLocationCausticEvent()
{
	ref mainCharacter = GetMainCharacter();
    ref loc = &Locations[FindLocation(mainCharacter.location)];

    if (IsLocationForCaustic(loc))
    {
        if (CheckLocationCaustic(loc)) return;
        SetCausticToLocation(loc, LOCATION_CAUSTIC_MODEL, LOCATION_CAUSTIC_TECH, LOCATION_CAUSTIC_LEVEL);
    }
}

void SetCausticToLocation(ref loc, string model, string tech, int level)
{
	float u0 = 0.0;
	float v0 = 0.0;
	float u1 = 0.0;
	float v1 = 0.0;
    SetCausticSpeed(&u0, &v0, &u1, &v1);

    aref aLoc;
	makearef(aLoc, loc.models.always);

	aLoc.caustic = model;
	aLoc.caustic.uvslide.u0 = u0;
	aLoc.caustic.uvslide.v0 = v0;
	aLoc.caustic.uvslide.u1 = u1;
	aLoc.caustic.uvslide.v1 = v1;
	aLoc.caustic.tech = tech;
	aLoc.caustic.level = level;
    aLoc.caustic.showstate = 1;

    string attr = "models.always.caustic";
    LocLoadModel(loc, attr, "");
}

void SetCausticSpeed(ref u0, ref v0, ref u1, ref v1)
{
	u0 = 0.05;
	v0 = -0.05;
	u1 = -0.05;
	v1 = 0.05;
}

bool IsLocationForCaustic(ref loc)
{
    if (loc.type == "grotto" || loc.type == "cave" || loc.type == "deck" || loc.type == "deck_fight") //здесь дополнить условия при необходимости
    {
        return false;
    }

    if (CheckAttribute(loc, "environment.sea"))
    {
        if (loc.environment.sea == "true" || loc.environment.sea == true) //кто знает, какие чудеса могут быть в корсаровских скриптах
        {
            return true;
        }  
    }

    return false;
}

bool CheckLocationCaustic(ref loc)
{
    if (CheckAttribute(loc, "models.always.caustic"))
    {
        return true;
    }

    return false;
}
