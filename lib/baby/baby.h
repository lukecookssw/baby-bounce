#ifndef BABY_H
#define BABY_H

#include "../entity/entity.h"

enum BIRTH_TYPE
{
    Natural,
    Caesarean,
    Tongs,
    Vaccuum,
    Angel,
    Other
};

enum GENDER
{
    Boy,
    Girl
};

typedef struct DateOfBirth
{
    int year;
    int month;
    int day;
} DateOfBirth;

typedef struct Baby
{
    enum GENDER gender;
    DateOfBirth dob;
    float weight;
    enum BIRTH_TYPE birth_type;
    Entity *entity;
} Baby;

Baby *baby_create(int id, enum GENDER gender, DateOfBirth dob, float weight, enum BIRTH_TYPE birthType);

#endif
