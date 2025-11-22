#include "baby.h"
#include "../entity/entity.h"

// prototypes

Baby *baby_create(int id, enum GENDER gender, DateOfBirth dob, float weight, enum BIRTH_TYPE birthType)
{
    Baby* baby = malloc(sizeof(Baby));
    baby->entity = entity_create(id, weight * 10);
    baby->dob = dob;
    baby->gender = gender;
    baby->weight = weight;
    baby->birth_type = birthType;

    return baby;
}
