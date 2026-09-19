class TerjeMedicineConstants
{
	const int MIND_MAX_VALUE = 100;
	const int MIND_CRITICAL = 5;
	const int MIND_LEVEL5 = 10;
	const int MIND_LEVEL4 = 20;
	const int MIND_LEVEL3 = 50;
	const int MIND_LEVEL2 = 80;
	const float MIND_TENDENCY_MINUS_STAGE1 = -0.5;
	const float MIND_TENDENCY_MINUS_STAGE2 = -1.5;
	const float MIND_TENDENCY_PLUS_STAGE1 = 0.5;
	const float MIND_TENDENCY_PLUS_STAGE2 = 1.5;
	
	const int SLEEPING_MAX_VALUE = 14000;
	const int SLEEPING_CRITICAL = 10;
	const int SLEEPING_UNCONSCIOUS = 50;
	const int SLEEPING_LEVEL5 = 250;
	const int SLEEPING_LEVEL4 = 1000;
	const int SLEEPING_LEVEL3 = 5000;
	const int SLEEPING_LEVEL2 = 10000;
	const float SLEEPING_TENDENCY_MINUS_STAGE1 = -5;
	const float SLEEPING_TENDENCY_MINUS_STAGE2 = -15;
	const float SLEEPING_TENDENCY_PLUS_STAGE1 = 5;
	const float SLEEPING_TENDENCY_PLUS_STAGE2 = 15;
	
	const float HEMATOMAS_PAIN_COUNT = 4;
	const float HEMATOMAS_BAD_COUNT = 8;
	const float HEMATOMAS_CRITICAL_COUNT = 16;
	const float HEMATOMAS_MAX_VALUE = 99;
	const float STUBWOUND_MAX_VALUE = 9;
	const float BULLETWOUND_MAX_VALUE = 9;
	const float BANDAGES_MAX_VALUE = 9;
	const float SUTURES_MAX_VALUE = 9;
	
	const float ZOMBIE_VIRUS_MAX_VALUE = 10;
	const float SEPSIS_MAX_VALUE = 5;
	const float PAIN_MAX_VALUE = 5;
	const float INFLUENZA_MAX_VALUE = 5;
	const float OVERDOSE_MAX_VALUE = 5;
	const float POISON_MAX_VALUE = 5;
	const float CONTUSION_MAX_VALUE = 3;
	const float CONTUSION_LIGHT = 1.5;
	const float CONTUSION_HEAVY = 3.0;
	const float BIOHAZARD_MAX_VALUE = 5;
	const float RABIES_MAX_VALUE = 5;
	const float BURN_MAX_VALUE = 5;
	const float FROSTBITE_MAX_VALUE = 5;
}

enum TerjeMedicineSleepingLevel {
	TERJESL_ENERGED = -4,
	TERJESL_SICK = -3,
	TERJESL_COLD = -2,
	TERJESL_HOT = -1,
	TERJESL_NONE = 0,
	TERJESL_COMFORT = 1,
	TERJESL_PERFECT = 2
}