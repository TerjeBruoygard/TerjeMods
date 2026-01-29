modded class TerjeSettingsCollection
{
	static int SKILLS_ALLOW_SKILLS_RESET;
	static int SKILLS_RESET_ALL_ON_DEATH;
	static int SKILLS_EXPERIENCE_GAIN_MODIFIER;
	static int SKILLS_EXPERIENCE_LOSE_MODIFIER;
	static int SKILLS_EXPERIENCE_LOSE_PERCENTAGE;
	static int SKILLS_EXPERIENCE_LOSE_ON_RESET_PERKS;
	static int SKILLS_MELEE_EVOID_STAMINA_MIN;
	static int SKILLS_MELEE_EVOID_STAMINA_MAX;
	static int SKILLS_ALLOW_CRAFTING_WITHOUT_PERKS;
	static int SKILLS_CRAFTING_EXPERIENCE_GAIN;
	static int SKILLS_SINGLE_SKILLBOOK_READING;
	static int SKILLS_DELETE_SKILLBOOK_READING;
	static int SKILLS_SKILLBOOK_EXP_MOD;
	
	static int SKILLS_ATHLETIC_CHECK_DISTANCE;
	static int SKILLS_ATHLETIC_EXP_GAIN;
	static int SKILLS_ATHLETIC_COOLDOWN_MODIFIER;
	
	static int SKILLS_STRENGTH_MELEE_LIGHT_GAIN_CHANCE;
	static int SKILLS_STRENGTH_MELEE_LIGHT_GAIN_EXP;
	static int SKILLS_STRENGTH_MELEE_HEAVY_GAIN_CHANCE;
	static int SKILLS_STRENGTH_MELEE_HEAVY_GAIN_EXP;
	static int SKILLS_STRENGTH_ITEMS_USE_GAIN_CHANCE;
	static int SKILLS_STRENGTH_ITEMS_USE_GAIN_EXP;
	static int SKILLS_STRENGTH_STRONG_HANDS_THRESHOLD;
	
	static int SKILLS_METABOLISM_CONSUME_FOOD_EXP_MOD;
	static int SKILLS_METABOLISM_CONSUME_WATER_EXP_MOD;
	
	static int SKILLS_STEALTH_CAT_VISION_POWER;
	static int SKILLS_STEALTH_CHECK_DISTANCE;
	static int SKILLS_STEALTH_EXP_GAIN;
	static int SKILLS_STEALTH_ZOMBIES_VISIBLE_MODIFIER;
	static int SKILLS_STEALTH_WOLVES_VISIBLE_MODIFIER;
	static int SKILLS_STEALTH_BEARS_VISIBLE_MODIFIER;
	static int SKILLS_STEALTH_PLAYER_NOISE_MODIFIER;
	static int SKILLS_STEALTH_FINISHER_GAIN_CHANCE;
	static int SKILLS_STEALTH_FINISHER_GAIN_EXP;
	
	static int SKILLS_SURV_TEMPERATURE_MODIFIER;
	static int SKILLS_SURV_IGNITE_FIRE_BASE_CHANCE;
	static int SKILLS_SURV_MAKE_FIRE_SUCCESS_GAIN_EXP;
	static int SKILLS_SURV_MAKE_FIRE_FAIL_GAIN_EXP;
	static int SKILLS_SURV_KILL_ZOMBIE_GAIN_EXP;
	static int SKILLS_SURV_LIFETIME_GAIN_EXP;
	static int SKILLS_SURV_LIFETIME_OFFSET;
	static int SKILLS_SURV_OVERRIDE_START_FIRE_TIME;
	static int SKILLS_SURV_COOKING_ON_STICK_EXP_GAIN;
	
	static int SKILLS_HUNTING_KILL_ANIMAL_EXP_GAIN_MODIFIER;
	static int SKILLS_HUNTING_HEADSHOT_ANIMAL_EXP_GAIN_MODIFIER;
	static int SKILLS_HUNTING_BUTCH_ANIMAL_EXP_GAIN_MODIFIER;
	static int SKILLS_HUNTING_TRAP_ANIMAL_EXP_GAIN_MODIFIER;
	static int SKILLS_HUNTING_OVERRIDE_SKINNING_TIME;
	static int SKILLS_HUNTING_OVERRIDE_KNIFE_DAMAGE;
	static int SKILLS_HUNTING_OVERRIDE_MEAT_INIT_QUANTITY;
	static int SKILLS_HUNTING_OVERRIDE_MEAT_MIN_QUANTITY;
	static int SKILLS_HUNTING_OVERRIDE_BONES_INIT_HP;
	static int SKILLS_HUNTING_SMALL_SKINNING_MOD;

	static int SKILLS_FISHING_SUCCESS_CATCH_EXP_GAIN;
	static int SKILLS_FISHING_FAILED_CATCH_EXP_GAIN;
	static int SKILLS_FISHING_OVERRIDE_FILLET_MIN_QUANTITY;
	static int SKILLS_FISHING_OVERRIDE_ROD_DAMAGE;
	static int SKILLS_FISHING_OVERRIDE_HOOK_DAMAGE;
	static int SKILLS_FISHING_OVERRIDE_KNIFE_DAMAGE;
	static int SKILLS_FISHING_FISH_SIZE_MODIFIER;
	static int SKILLS_FISHING_BUTCH_EXP_GAIN_MODIFIER;
	static int SKILLS_FISHING_OVERRIDE_SKINNING_TIME;
	static int SKILLS_FISHING_OVERRIDE_BASE_CATCH_CHANCE;
	
	static ref map<string, int> SKILLS_INITIAL_EXP = new map<string, int>;
	static ref map<string, int> SKILLS_ACTIVE_SKILLS = new map<string, int>;
	// Add hidden abbility to hide skills/perks from UI
	static ref map<string, int> SKILLS_HIDDEN_SKILLS = new map<string, int>;
	static ref map<string, int> SKILLS_ACTIVE_PERKS = new map<string, int>;
	
	override void OnInit()
	{
		super.OnInit();
		
		RegisterRegion("Skills", "General settings");
		SKILLS_ALLOW_SKILLS_RESET = RegisterSettingBool("Skills.AllowSkillsReset", "Skills", "If this setting is enabled, the player can reset their perks in the UI.", true, false);
		SKILLS_RESET_ALL_ON_DEATH = RegisterSettingBool("Skills.ResetAllOnDeath", "Skills", "If this setting is enabled, all skills and perks of the character will be reset to 0 after death. If this setting is disabled - skills will be reduced by the modifier defined in Skills.ExperienceLoseModifier.", false, true);
		SKILLS_EXPERIENCE_GAIN_MODIFIER = RegisterSettingFloat("Skills.ExperienceGainModifier", "Skills", "Modifier of gaining skill experience. Set to 2.5 to take 2.5 times more skill experience.", 1.0, false);
		SKILLS_EXPERIENCE_LOSE_MODIFIER = RegisterSettingFloat("Skills.ExperienceLoseModifier", "Skills", "Modifier of losing skill experience when died. Set to 0 to disable experience lose on death.", 1.0, false);
		SKILLS_EXPERIENCE_LOSE_PERCENTAGE = RegisterSettingFloat("Skills.ExperienceLosePercentage", "Skills", "If this value is greater than zero - the player will lose a percentage of experience on death, instead of a fixed value from the config. This value can be -1 when disabled (by default) and in the range from 0 to 1 when enabled (where 1 is 100%)", -1.0, true);
		SKILLS_EXPERIENCE_LOSE_ON_RESET_PERKS = RegisterSettingFloat("Skills.ExperienceLoseOnResetPerks", "Skills", "Sets the percentage of experience that the player will get back after resetting skill perks where 0.5 is 50% of experience. Set to 1.0 to take all experience back after reset.", 0.5, false);
		SKILLS_MELEE_EVOID_STAMINA_MIN = RegisterSettingFloat("Skills.MeleeEvoidStaminaMin", "Skills", "Sets the minimum value of stamina consumption when successfully blocking a hit. A random value between the minimum and maximum is selected while blocking a hit.", 1, true);
		SKILLS_MELEE_EVOID_STAMINA_MAX = RegisterSettingFloat("Skills.MeleeEvoidStaminaMax", "Skills", "Sets the maximum value of stamina consumption when successfully blocking a hit. A random value between the minimum and maximum is selected while blocking a hit.", 3, true);
		SKILLS_ALLOW_CRAFTING_WITHOUT_PERKS = RegisterSettingBool("Skills.AllowCraftingWithoutPerks", "Skills", "If this setting is disabled - then crafting recipes requiring a specific perk will not be available until the player has acquired first level of the required perk. If this setting is enabled - crafts are always available, but the quality of the result item will be bad.", false, false);
		SKILLS_CRAFTING_EXPERIENCE_GAIN = RegisterSettingInt("Skills.CraftingExpGain", "Skills", "Sets the value of experience that the player will gain by crafting skill-based items. This parameter is also affected by ExperienceGainModifier.", 10, true);
		SKILLS_SINGLE_SKILLBOOK_READING = RegisterSettingBool("Skills.SingleSkillbookReading", "Skills", "If this option is enabled - the player can read a book that gives experience to a skill only once.", true, true);
		SKILLS_DELETE_SKILLBOOK_READING = RegisterSettingBool("Skills.DeleteSkillbookAfterReading", "Skills", "If this option is enabled - skill book will be deleted after the reading by player.", true, true);
		SKILLS_SKILLBOOK_EXP_MOD = RegisterSettingFloat("Skills.SkillbookExpModifier", "Skills", "Sets modifier for skills experience gained after reading a book.", 1.0, true);
		
		RegisterRegion("Skills", "Athletic");
		SKILLS_ATHLETIC_CHECK_DISTANCE = RegisterSettingInt("Skills.AthleticCheckDistance", "Skills", "Sets the distance a player must run to gain athletic experience.", 100, true);
		SKILLS_ATHLETIC_EXP_GAIN = RegisterSettingInt("Skills.AthleticExpGain", "Skills", "Sets the value of experience points that the player will gain by running. This parameter is also affected by ExperienceGainModifier.", 10, true);
		SKILLS_ATHLETIC_COOLDOWN_MODIFIER = RegisterSettingFloat("Skills.AthleticCooldownModifier", "Skills", "Sets a modifier for the stamina recovery cooldown. Use 1.0 to back vanilla cooldown value.", 10, false);
		
		RegisterRegion("Skills", "Strength");
		SKILLS_STRENGTH_MELEE_LIGHT_GAIN_CHANCE = RegisterSettingFloat("Skills.StrengthMeleeLightGainChance", "Skills", "Sets the chance the player will gain experience for a successful light melee attack.", 0.1, true);
		SKILLS_STRENGTH_MELEE_LIGHT_GAIN_EXP = RegisterSettingInt("Skills.StrengthMeleeLightGainExp", "Skills", "Sets the value of experience points that the player will gain for a successful light melee attack. This parameter is also affected by ExperienceGainModifier.", 15, true);
		SKILLS_STRENGTH_MELEE_HEAVY_GAIN_CHANCE = RegisterSettingFloat("Skills.StrengthMeleeHeavyGainChance", "Skills", "Sets the chance the player will gain experience for a successful heavy melee attack.", 0.5, true);
		SKILLS_STRENGTH_MELEE_HEAVY_GAIN_EXP = RegisterSettingInt("Skills.StrengthMeleeHeavyGainExp", "Skills", "Sets the value of experience points that the player will gain for a successful heavy melee attack. This parameter is also affected by ExperienceGainModifier.", 30, true);
		SKILLS_STRENGTH_ITEMS_USE_GAIN_CHANCE = RegisterSettingFloat("Skills.StrengthItemsUseGainChance", "Skills", "Sets the chance the player will gain experience for the use of tools (chopping firewood, extracting stones, etc).", 0.2, true);
		SKILLS_STRENGTH_ITEMS_USE_GAIN_EXP = RegisterSettingInt("Skills.StrengthItemsUseGainExp", "Skills", "Sets the value of experience points that the player will gain for the use of tools (chopping firewood, extracting stones, etc). This parameter is also affected by ExperienceGainModifier.", 10, true);
		SKILLS_STRENGTH_STRONG_HANDS_THRESHOLD = RegisterSettingFloat("Skills.StrengthHandsPerkThreshold", "Skills", "Sets the maximum weight of the object that the player can take in his hands without the Sturdy Hands perk. (in kilograms)", 20, true);
		
		RegisterRegion("Skills", "Metabolism");
		SKILLS_METABOLISM_CONSUME_FOOD_EXP_MOD = RegisterSettingFloat("Skills.MetabolismConsumeFoodExpMod", "Skills", "Sets the modifier for gained metabolism skill experience when player is eating a food.", 1.0, true);
		SKILLS_METABOLISM_CONSUME_WATER_EXP_MOD = RegisterSettingFloat("Skills.MetabolismConsumeWaterExpMod", "Skills", "Sets the modifier for gained metabolism skill experience when player is drinking a water.", 1.0, true);
		
		RegisterRegion("Skills", "Stealth");
		SKILLS_STEALTH_CAT_VISION_POWER = RegisterSettingFloat("Skills.StealthCatVisionPower", "Skills", "Sets the modifier of power for the CatVision perk.", 1.0, false);
		SKILLS_STEALTH_CHECK_DISTANCE = RegisterSettingInt("Skills.StealthCheckDistance", "Skills", "Sets the distance a player must crouch to gain stealth experience.", 30, true);
		SKILLS_STEALTH_EXP_GAIN = RegisterSettingInt("Skills.StealthExpGain", "Skills", "Sets the value of experience points that the player will gain by crouching. This parameter is also affected by ExperienceGainModifier.", 10, true);
		SKILLS_STEALTH_ZOMBIES_VISIBLE_MODIFIER = RegisterSettingFloat("Skills.StealthZombiesVisibilityModifier", "Skills", "Sets global player visibility modifier for targeting by zombies.", 1.5, true);
		SKILLS_STEALTH_WOLVES_VISIBLE_MODIFIER = RegisterSettingFloat("Skills.StealthWolvesVisibilityModifier", "Skills", "Sets global player visibility modifier for targeting by wolves.", 1.0, true);
		SKILLS_STEALTH_BEARS_VISIBLE_MODIFIER = RegisterSettingFloat("Skills.StealthBearsVisibilityModifier", "Skills", "Sets global player visibility modifier for targeting by bears.", 1.0, true);
		SKILLS_STEALTH_PLAYER_NOISE_MODIFIER = RegisterSettingFloat("Skills.StealthPlayerNoiseModifier", "Skills", "Sets global player modifier for noise system.", 1.5, true);
		SKILLS_STEALTH_FINISHER_GAIN_CHANCE = RegisterSettingFloat("Skills.StealthFinisherGainChance", "Skills", "Sets the chance the player will gain experience for a successful silence kill.", 1.0, true);
		SKILLS_STEALTH_FINISHER_GAIN_EXP = RegisterSettingInt("Skills.StealthFinisherGainExp", "Skills", "Sets the value of experience points that the player will gain for a successful silence kill. This parameter is also affected by ExperienceGainModifier.", 10, true);
		
		RegisterRegion("Skills", "Survival");
		SKILLS_SURV_TEMPERATURE_MODIFIER = RegisterSettingFloat("Skills.SurvTemperatureModifier", "Skills", "Sets the modifier value that is multiplied by the environment temperature modifier calculated from ReducedTempModifier of the survival skill.", 0.5, true);
		SKILLS_SURV_IGNITE_FIRE_BASE_CHANCE = RegisterSettingFloat("Skills.SurvIgniteFireBaseChance", "Skills", "Sets the base chance of starting fire in additional to the StartingFire perk chance.", 0.2, true);
		SKILLS_SURV_MAKE_FIRE_SUCCESS_GAIN_EXP = RegisterSettingInt("Skills.SurvMakeFireSuccessGainExp", "Skills", "Sets the value of experience points that the player will gain for successfully making a fire. This parameter is also affected by ExperienceGainModifier.", 50, true);
		SKILLS_SURV_MAKE_FIRE_FAIL_GAIN_EXP = RegisterSettingInt("Skills.SurvMakeFireFailGainExp", "Skills", "Sets the value of experience points that the player will gain for trying to making a fire. This parameter is also affected by ExperienceGainModifier.", 10, true);
		SKILLS_SURV_KILL_ZOMBIE_GAIN_EXP = RegisterSettingInt("Skills.SurvKillZombieGainExp", "Skills", "Sets the value of experience points that the player will gain when kill a zombie. This parameter is also affected by ExperienceGainModifier.", 5, true);
		SKILLS_SURV_LIFETIME_GAIN_EXP = RegisterSettingInt("Skills.SurvLifetimeGainExp", "Skills", "Sets the value of experience points that the player will gain when survived for a long time. This parameter is also affected by ExperienceGainModifier.", 100, true);
		SKILLS_SURV_LIFETIME_OFFSET = RegisterSettingInt("Skills.SurvLifetimeOffset", "Skills", "Sets the cyclic time interval in seconds after which the player will be awarded additional experience points for the survival skill.", 3600, true);
		SKILLS_SURV_OVERRIDE_START_FIRE_TIME = RegisterSettingFloat("Skills.SurvOverrideStartFireTime", "Skills", "Overrides the time for starting the fire. If the value is -1, the default value will be used instead.", 15.0, false);
		SKILLS_SURV_COOKING_ON_STICK_EXP_GAIN = RegisterSettingInt("Skills.SurvCookingOnStickExpGain", "Skills", "Sets the value of experience points that the player will gain for successfully cooking a food on stick. This parameter is also affected by ExperienceGainModifier.", 5, true);
		
		RegisterRegion("Skills", "Hunting");
		SKILLS_HUNTING_KILL_ANIMAL_EXP_GAIN_MODIFIER = RegisterSettingFloat("Skills.HuntingKillAnimalExpGainModifier", "Skills", "Sets the value of the experience modifier that the player will get after killing an animal. This modifier is multiplied by the parameter terjeOnKillHuntingExp from the animals config.", 1.0, true);
		SKILLS_HUNTING_HEADSHOT_ANIMAL_EXP_GAIN_MODIFIER = RegisterSettingFloat("Skills.HuntingHeadshotAnimalExpGainModifier", "Skills", "Sets the value of the experience modifier that the player will get after killing an animal with headshot in additional to HuntingKillAnimalExpGainModifier. This modifier is multiplied by the parameter terjeOnHeadshotHuntingExp from the animals config.", 1.0, true);
		SKILLS_HUNTING_BUTCH_ANIMAL_EXP_GAIN_MODIFIER = RegisterSettingFloat("Skills.HuntingButchAnimalExpGainModifier", "Skills", "Sets the value of the experience modifier that the player will get after butchering an animal. This modifier is multiplied by the parameter terjeOnButchHuntingExp from the animals config.", 1.0, true);
		SKILLS_HUNTING_TRAP_ANIMAL_EXP_GAIN_MODIFIER = RegisterSettingFloat("Skills.HuntingTrapAnimalExpGainModifier", "Skills", "Sets the value of the experience modifier that the player will get after cathing an animal by the trap. This modifier is multiplied by the parameter terjeOnCatchAnimalHuntingExp from the traps config.", 1.0, true);
		SKILLS_HUNTING_OVERRIDE_SKINNING_TIME = RegisterSettingFloat("Skills.HuntingOverrideSkinningTime", "Skills", "Sets the time of skinning animal carcasses for use with the QuickSkinning perk. If the value is -1, the default value will be used instead.", 60.0, false);
		SKILLS_HUNTING_OVERRIDE_KNIFE_DAMAGE = RegisterSettingFloat("Skills.HuntingOverrideKnifeDamage", "Skills", "Sets the absolute damage value for a knife when skinning animal carcasses. Affected by MasterKnife perk.", 100.0, true);
		SKILLS_HUNTING_OVERRIDE_MEAT_INIT_QUANTITY = RegisterSettingFloat("Skills.HuntingOverrideMeatInitQuantity", "Skills", "Sets the maximum initial random quantity for the one peace of meat that can be produced during the skinning without skills. The MeatHunter modifier will be added to this value. Value range from 0 (0%) to 1 (100%).", 0.25, true);
		SKILLS_HUNTING_OVERRIDE_MEAT_MIN_QUANTITY = RegisterSettingFloat("Skills.HuntingOverrideMeatMinQuantity", "Skills", "Sets the minimum quantity for the one peace of meat that can be produced during the skinning without skills. Value range from 0 (0%) to 1 (100%).", 0.25, true);
		SKILLS_HUNTING_OVERRIDE_BONES_INIT_HP = RegisterSettingFloat("Skills.HuntingOverrideBonesInitHp", "Skills", "Sets the minimum health for the bones that can be produced during the skinning without skills. Value range from 0 (0%) to 1 (100%).", 0.0, true);
		SKILLS_HUNTING_SMALL_SKINNING_MOD = RegisterSettingFloat("Skills.HuntingSmallSkinningMod", "Skills", "Sets the skinning time modifier for small animals like rabits or chickens via crafting.", 0.25, false);
		
		RegisterRegion("Skills", "Fishing");
		SKILLS_FISHING_SUCCESS_CATCH_EXP_GAIN = RegisterSettingInt("Skills.FishingSuccessCatchGainExp", "Skills", "Sets the experience value that the player will receive if the catch is successful. This parameter is also affected by ExperienceGainModifier.", 50, true);
		SKILLS_FISHING_FAILED_CATCH_EXP_GAIN = RegisterSettingInt("Skills.FishingFailedCatchGainExp", "Skills", "Sets the experience value that the player will receive if the catch is failed. This parameter is also affected by ExperienceGainModifier.", 10, true);
		SKILLS_FISHING_OVERRIDE_FILLET_MIN_QUANTITY = RegisterSettingFloat("Skills.FishingOverrideFilletMinQuantity", "Skills", "Sets the minimum quantity for the one peace of fish fillet that can be produced during the skinning without skills. Value range from 0 (0%) to 1 (100%).", 0.2, true);
		SKILLS_FISHING_OVERRIDE_ROD_DAMAGE = RegisterSettingFloat("Skills.FishingOverrideRodDamage", "Skills", "Sets the absolute damage value for a fishing rod after a fishing action. Affected by StraightArms perk.", 5, true);
		SKILLS_FISHING_OVERRIDE_HOOK_DAMAGE = RegisterSettingFloat("Skills.FishingOverrideHookDamage", "Skills", "Sets the absolute damage value for a fishing hook after a fishing action. Affected by StraightArms perk.", 5, true);
		SKILLS_FISHING_OVERRIDE_KNIFE_DAMAGE = RegisterSettingFloat("Skills.FishingOverrideKnifeDamage", "Skills", "Sets the absolute damage value for a knife when skinning fishes. Affected by StraightArms perk.", 50.0, true);
		SKILLS_FISHING_FISH_SIZE_MODIFIER = RegisterSettingFloat("Skills.FishingFishSizeModifier", "Skills", "Sets the fish size modifier. It is used for the player to catch fish of different sizes for correct work of FishermanLuck skill.", 0.2, true);
		SKILLS_FISHING_BUTCH_EXP_GAIN_MODIFIER = RegisterSettingFloat("Skills.FishingButchExpGainModifier", "Skills", "Sets the value of the experience modifier that the player will get after butchering (cleaning) an fish. This modifier is multiplied by the parameter terjeOnButchHuntingExp from the fishs config.", 1.0, true);
		SKILLS_FISHING_OVERRIDE_SKINNING_TIME = RegisterSettingFloat("Skills.FishingOverrideSkinningTime", "Skills", "Sets the time in secconds for skinning fish for use with the perk. If the value is -1, the default value will be used instead.", 30.0, false);
		SKILLS_FISHING_OVERRIDE_BASE_CATCH_CHANCE = RegisterSettingFloat("Skills.FishingOverrideBaseCatchChance", "Skills", "Sets the base chance of catching fish before skill modifiers are applied.", 0.25, true);
		
		RegisterRegion("Skills", "Initial experience");
		array<ref TerjeSkillCfg> registeredSkills();
		GetTerjeSkillsRegistry().GetSkills(registeredSkills);
		foreach (ref TerjeSkillCfg skill_1 : registeredSkills)
		{
			SKILLS_INITIAL_EXP.Set(skill_1.GetId(), RegisterSettingInt("Skills.InitialExpSkill_" + skill_1.GetId(), "Skills", "Sets the initial value of " + skill_1.GetId() + " skill experience for new player (for the first respawn only).", 0, true));
		}
		
		RegisterRegion("Skills", "Enabled skills");
		foreach (ref TerjeSkillCfg skill_2 : registeredSkills)
		{
			SKILLS_ACTIVE_SKILLS.Set(skill_2.GetId(), RegisterSettingBool("Skills.EnableSkill_" + skill_2.GetId(), "Skills", "Sets is " + skill_2.GetId() + " skill enabled on the server.", true, false));
		}

		
		RegisterRegion("Skills", "Enabled perks");
		foreach (ref TerjeSkillCfg skill_3 : registeredSkills)
		{
			array<ref TerjePerkCfg> registeredSkillPerks();
			skill_3.GetPerks(registeredSkillPerks);
			foreach (ref TerjePerkCfg perk : registeredSkillPerks)
			{
				SKILLS_ACTIVE_PERKS.Set(skill_3.GetId() + ":" + perk.GetId(), RegisterSettingBool("Skills.EnablePerk_" + skill_3.GetId() + "_" + perk.GetId(), "Skills", "Sets is perk " + perk.GetId() + " enabled for skill " + skill_3.GetId() + ".", true, false));
			}
		}

		// Add hidden abbility to hide skills from UI
		RegisterRegion("Skills", "Hide skills");
		foreach (ref TerjeSkillCfg skill_4 : registeredSkills)
		{
			SKILLS_HIDDEN_SKILLS.Set(skill_4.GetId(), RegisterSettingBool("Skills.HideSkill_" + skill_4.GetId(), "Skills", "Sets is " + skill_4.GetId() + " skill hidden on the server.", false, false));
		}
	}
	
	override void AfterServerSettingsLoaded()
	{
		super.AfterServerSettingsLoaded();
		
		GetTerjeSkillsRegistry().OnTerjeSettingsLoaded();
	}
}