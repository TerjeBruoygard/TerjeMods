modded class TerjeSettingsCollection
{
	static int STARTSCREEN_ONACTIVE_GOD_MODE;
	static int STARTSCREEN_ONACTIVE_INDESTRUCTIBLE;
	static int STARTSCREEN_ONACTIVE_IGNORE_DAMAGE;
	static int STARTSCREEN_ONACTIVE_INVISIBLE;
	static int STARTSCREEN_ONACTIVE_NOCLIP;
	static int STARTSCREEN_ONACTIVE_NOTARGETING;
	static int STARTSCREEN_ONACTIVE_FREEZE;
	static int STARTSCREEN_ONACTIVE_NOSIM;
	static int STARTSCREEN_ONACTIVE_NOHEATCOMF;
	static int STARTSCREEN_ONACTIVE_SAFEPOS;
	static int STARTSCREEN_TELEPORT_SAFEPOS;
	static int STARTSCREEN_RULES_PAGE_ENABLED;
	static int STARTSCREEN_RULES_SHOW_ALWAYS;
	static int STARTSCREEN_RULES_SCROLL;
	static int STARTSCREEN_RULES_TIMEOUT;
	static int STARTSCREEN_NAME_PAGE_ENABLED;
	static int STARTSCREEN_FACE_PAGE_ENABLED;
	static int STARTSCREEN_PBEARD_ENABLED;
	static int STARTSCREEN_PBEARD_ALLOWSHAVE;
	static int STARTSCREEN_PBEARD_FACESELECT;
	static int STARTSCREEN_SKILLS_PAGE_ENABLED;
	static int STARTSCREEN_LOADOUT_PAGE_ENABLED;
	static int STARTSCREEN_MAP_PAGE_ENABLED;
	static int STARTSCREEN_OVERVIEW_PAGE_ENABLED;
	static int STARTSCREEN_DISPLAY_PLAYER_NAMES_MODE;
	static int STARTSCREEN_NAME_PAGE_LENGTH_MIN;
	static int STARTSCREEN_NAME_PAGE_LENGTH_MAX;
	static int STARTSCREEN_LAST_NAME_ENABLED;
	static int STARTSCREEN_UNIQ_NAME_CHECKS;
	static int STARTSCREEN_SKILLS_PAGE_POINTS;
	static int STARTSCREEN_MAP_PAGE_ATTEMPTS;
	static int STARTSCREEN_OVERVIEW_PAGE_DEL;
	static int STARTSCREEN_SOULS_ENABLED;
	static int STARTSCREEN_SOULS_MAXCOUNT;
	static int STARTSCREEN_SOULS_AUTODEL;
	static int STARTSCREEN_SOULS_NOTIFY;
	static int STARTSCREEN_SOULS_BADGE;
	static int STARTSCREEN_SOULS_INIT_COUNT;
	static int STARTSCREEN_SOULS_KILLPLAYER_COUNT;
	static int STARTSCREEN_SOULS_KILLPLAYER_CHANCE;
	static int STARTSCREEN_SOULS_KILLAI_COUNT;
	static int STARTSCREEN_SOULS_KILLAI_CHANCE;
	static int STARTSCREEN_SOULS_KILLZMB_COUNT;
	static int STARTSCREEN_SOULS_KILLZMB_CHANCE;
	static int STARTSCREEN_SOULS_KILLANI_COUNT;
	static int STARTSCREEN_SOULS_KILLANI_CHANCE;
	static int STARTSCREEN_SOULS_SURVT_POW;
	static int STARTSCREEN_SOULS_SURVT_TIME;
	static int STARTSCREEN_SOULS_SURVT_COUNT;
	static int STARTSCREEN_SOULS_SURVT_CHANCE;
	static int STARTSCREEN_SOULS_GAIN_TIMEOUT;
	static int STARTSCREEN_PASSPORT_SPAWN;
	static int STARTSCREEN_PASSPORT_SPAWN_ONCE;
	static int STARTSCREEN_PASSPORT_UNIQ_NUMBER;
	static int STARTSCREEN_PASSPORT_SHOW_NUMBER;
	static int STARTSCREEN_PASSPORT_SHOW_GENDER;
	
	override void OnInit()
	{
		super.OnInit();
		
		RegisterRegion("StartScreen", "General settings");
		STARTSCREEN_ONACTIVE_GOD_MODE = RegisterSettingBool("StartScreen.OnActiveGodMode", "StartScreen", "Use god mode when the player has an active start screen. DISABLED BY DEFAULT DUE TO CONFILCTS WITH SOME ADMIN TOOLS like COT.", false, true);
		STARTSCREEN_ONACTIVE_INDESTRUCTIBLE = RegisterSettingBool("StartScreen.OnActiveIndestructible", "StartScreen", "Same as StartScreen.OnActiveGodMode but did not conflict with the custom admin tools.", true, true);
		STARTSCREEN_ONACTIVE_IGNORE_DAMAGE = RegisterSettingBool("StartScreen.OnActiveIgnoreDamage", "StartScreen", "Ignore damage while the player has an active start screen.", true, true);
		STARTSCREEN_ONACTIVE_INVISIBLE = RegisterSettingBool("StartScreen.OnActiveInvisible", "StartScreen", "Make player invisible while the player has an active start screen.", true, true);
		STARTSCREEN_ONACTIVE_NOCLIP = RegisterSettingBool("StartScreen.OnActiveNoClip", "StartScreen", "Disable collision while the player has an active start screen.", true, true);
		STARTSCREEN_ONACTIVE_NOTARGETING = RegisterSettingBool("StartScreen.OnActiveNoTargeting", "StartScreen", "Disable player targeting by AI while the player has an active start screen.", true, true);
		STARTSCREEN_ONACTIVE_FREEZE = RegisterSettingBool("StartScreen.OnActiveFreezePos", "StartScreen", "Freeze player movement and position while the player has an active start screen.", true, true);
		STARTSCREEN_ONACTIVE_NOSIM = RegisterSettingBool("StartScreen.OnActiveDisableSimulation", "StartScreen", "Disable player simulation while the player has an active start screen.", true, true);
		STARTSCREEN_ONACTIVE_NOHEATCOMF = RegisterSettingBool("StartScreen.OnActiveDisableTemperature", "StartScreen", "Disable player temperature while the player has an active start screen.", true, true);
		STARTSCREEN_ONACTIVE_SAFEPOS = RegisterSettingBool("StartScreen.OnActiveSafePos", "StartScreen", "Teleport player to safe position while the player has an active start screen.", true, true);
		STARTSCREEN_TELEPORT_SAFEPOS = RegisterSettingString("StartScreen.TeleportSafePos", "StartScreen", "Sets safe position coordinates while the player has an active start screen (when StartScreen.OnActiveSafePos enabled).", "0 1000 0", true);
		
		RegisterRegion("StartScreen", "Server rules page");
		STARTSCREEN_RULES_PAGE_ENABLED = RegisterSettingBool("StartScreen.RulesPageEnabled", "StartScreen", "Use server rules page on first character creation.", true, true);
		STARTSCREEN_RULES_SHOW_ALWAYS = RegisterSettingBool("StartScreen.RulesPageShowAlways", "StartScreen", "When true, the server rules will be displayed every time on the start screen. When false, then only at the first character creation.", false, true);
		STARTSCREEN_RULES_SCROLL = RegisterSettingBool("StartScreen.RulesPageScrollToEnd", "StartScreen", "When enabled user must scroll to the end of the rules to have ability move to the next page.", true, true);
		STARTSCREEN_RULES_TIMEOUT = RegisterSettingFloat("StartScreen.RulesPageTimeout", "StartScreen", "Sets the time in seconds during which the button to go to the next page will be disabled.", 5, true);
		
		RegisterRegion("StartScreen", "Name selection page");
		STARTSCREEN_NAME_PAGE_ENABLED = RegisterSettingBool("StartScreen.NamePageEnabled", "StartScreen", "Use first and last name page when creating a new character.", true, true);
		STARTSCREEN_DISPLAY_PLAYER_NAMES_MODE = RegisterSettingInt("StartScreen.DisplayPlayerNamesMode", "StartScreen", "Displays player names when hover cursor over them. Modes: (-1) - disabled, (0) - always, (1) - dead only, (2) - when face is visible, (3) - dead only when face is visible", 0, false);
		STARTSCREEN_NAME_PAGE_LENGTH_MIN = RegisterSettingInt("StartScreen.NamePageLengthMin", "StartScreen", "Minimum string length that are used as a input validator for first and last names.", 3, true);
		STARTSCREEN_NAME_PAGE_LENGTH_MAX = RegisterSettingInt("StartScreen.NamePageLengthMax", "StartScreen", "Maximum string length that are used as a input validator for first and last names.", 16, true);
		STARTSCREEN_LAST_NAME_ENABLED = RegisterSettingBool("StartScreen.LastNameEnabled", "StartScreen", "When true in addition to the first name the player will be required to enter a last name.", true, true);
		STARTSCREEN_UNIQ_NAME_CHECKS = RegisterSettingBool("StartScreen.UniqNameChecks", "StartScreen", "Checks the input characters name for uniqueness when entered to avoid characters with the same name on the server.", true, true);
		
		RegisterRegion("StartScreen", "Face selection page");
		STARTSCREEN_FACE_PAGE_ENABLED = RegisterSettingBool("StartScreen.FacePageEnabled", "StartScreen", "Use face selection page when creating a new character.", true, true);
		STARTSCREEN_PBEARD_ENABLED = RegisterSettingBool("StartScreen.PersistentBeardEnabled", "StartScreen", "Enable persistent beard system for selected character face.", false, true);
		STARTSCREEN_PBEARD_ALLOWSHAVE = RegisterSettingBool("StartScreen.PersistentBeardAllowShave", "StartScreen", "Allow shaving when persistent beard is enabled. Beard regrows up to max level.", true, true);
		STARTSCREEN_PBEARD_FACESELECT = RegisterSettingBool("StartScreen.PersistentBeardFaceSelect", "StartScreen", "Allow selecting beard level on face selection page.", true, true);
		
		RegisterRegion("StartScreen", "Skills selection page");
		STARTSCREEN_SKILLS_PAGE_ENABLED = RegisterSettingBool("StartScreen.SkillsPageEnabled", "StartScreen", "Use start skills selection page when creating a new character (only for TerjeSkills mod).", true, true);
		STARTSCREEN_SKILLS_PAGE_POINTS = RegisterSettingInt("StartScreen.SkillsPagePoints", "StartScreen", "The number of points that player can allocate to select skill levels.", 10, true);
		
		RegisterRegion("StartScreen", "Loadout selection page");
		STARTSCREEN_LOADOUT_PAGE_ENABLED = RegisterSettingBool("StartScreen.LoadoutPageEnabled", "StartScreen", "Use loadout selection page when character respawning.", true, true);
		
		RegisterRegion("StartScreen", "Respawn selection page");
		STARTSCREEN_MAP_PAGE_ENABLED = RegisterSettingBool("StartScreen.MapPageEnabled", "StartScreen", "Use map respawn point selection page when character respawning.", true, true);
		STARTSCREEN_MAP_PAGE_ATTEMPTS = RegisterSettingInt("StartScreen.MapPageAttempts", "StartScreen", "The number of attempts to found safe position for a player after reaching which the any random spawn point will be used.", 8, true);
		
		RegisterRegion("StartScreen", "Overview character page");
		STARTSCREEN_OVERVIEW_PAGE_ENABLED = RegisterSettingBool("StartScreen.OverviewPageEnabled", "StartScreen", "Use character management screen page when character respawning.", true, true);
		STARTSCREEN_OVERVIEW_PAGE_DEL = RegisterSettingBool("StartScreen.OverviewPageAllowDeletion", "StartScreen", "Allow character profile manual deletion from overview page.", true, true);
		STARTSCREEN_SOULS_ENABLED = RegisterSettingBool("StartScreen.SoulsEnabled", "StartScreen", "Whether is characters soul system is enabled.", true, false);
		STARTSCREEN_SOULS_MAXCOUNT = RegisterSettingInt("StartScreen.SoulsMaxCount", "StartScreen", "Maximum number of souls a player can accumulate.", 7, false);
		STARTSCREEN_SOULS_AUTODEL = RegisterSettingBool("StartScreen.SoulsAutoDelete", "StartScreen", "Delete a character automatically when their amount of souls reaches zero.", true, true);
		STARTSCREEN_SOULS_NOTIFY = RegisterSettingBool("StartScreen.SoulsNotifications", "StartScreen", "Show notifications to player when souls count was changed.", true, true);
		STARTSCREEN_SOULS_BADGE = RegisterSettingBool("StartScreen.SoulsDisplayBadge", "StartScreen", "Show badge icon on HUD with souls count.", false, false);
		STARTSCREEN_SOULS_INIT_COUNT = RegisterSettingInt("StartScreen.SoulsInitCount", "StartScreen", "The number of initial souls when player respawning for the first time.", 3, true);
		STARTSCREEN_SOULS_KILLPLAYER_COUNT = RegisterSettingInt("StartScreen.SoulsOnKillPlayerCount", "StartScreen", "The number of souls you get for killing a player.", 1, true);
		STARTSCREEN_SOULS_KILLPLAYER_CHANCE = RegisterSettingFloat("StartScreen.SoulsOnKillPlayerChance", "StartScreen", "The chance at which you will get souls for killing a player. Value from 0 to 1", 1, true);
		STARTSCREEN_SOULS_KILLAI_COUNT = RegisterSettingInt("StartScreen.SoulsOnKillAiCount", "StartScreen", "The number of souls you get for killing an AI player.", 1, true);
		STARTSCREEN_SOULS_KILLAI_CHANCE = RegisterSettingFloat("StartScreen.SoulsOnKillAiChance", "StartScreen", "The chance at which you will get souls for killing an AI player. Value from 0 to 1", 0.25, true);
		STARTSCREEN_SOULS_KILLZMB_COUNT = RegisterSettingInt("StartScreen.SoulsOnKillZombieCount", "StartScreen", "The number of souls you get for killing a zombie.", 1, true);
		STARTSCREEN_SOULS_KILLZMB_CHANCE = RegisterSettingFloat("StartScreen.SoulsOnKillZombieChance", "StartScreen", "The chance at which you will get souls for killing a zombie. Value from 0 to 1", 0.01, true);
		STARTSCREEN_SOULS_KILLANI_COUNT = RegisterSettingInt("StartScreen.SoulsOnKillAnimalCount", "StartScreen", "The number of souls you get for killing an animal.", 1, true);
		STARTSCREEN_SOULS_KILLANI_CHANCE = RegisterSettingFloat("StartScreen.SoulsOnKillAnimalChance", "StartScreen", "The chance at which you will get souls for killing an animal. Value from 0 to 1", 0.05, true);
		STARTSCREEN_SOULS_SURVT_TIME = RegisterSettingInt("StartScreen.SoulsLongSurviveTime", "StartScreen", "The amount of continuous survival time (in seconds) after which the player will receive additional souls.", 14400, true);
		STARTSCREEN_SOULS_SURVT_POW = RegisterSettingFloat("StartScreen.SoulsLongSurvivePow", "StartScreen", "The calculation of souls obtained during the survived time is based on the degree formula StartScreen.SoulsLongSurviveTime. This ensures that each next stage will be longer than the previous one by a multiple of this degree. Use 1 for linear function.", 1.5, true);
		STARTSCREEN_SOULS_SURVT_COUNT = RegisterSettingInt("StartScreen.SoulsLongSurviveCount", "StartScreen", "The number of souls you get for continuous survival.", 1, true);
		STARTSCREEN_SOULS_SURVT_CHANCE = RegisterSettingFloat("StartScreen.SoulsLongSurviveChance", "StartScreen", "The chance at which you will get souls for continuous survival. Value from 0 to 1", 1, true);
		STARTSCREEN_SOULS_GAIN_TIMEOUT = RegisterSettingInt("StartScreen.SoulsGainTimeout", "StartScreen", "Sets the timeout (in seconds) for a player to obtain new souls to prevent souls farming. Disabled by default (-1)", -1, true);
		
		RegisterRegion("StartScreen", "Passport settings");
		STARTSCREEN_PASSPORT_SPAWN = RegisterSettingBool("StartScreen.PassportSpawn", "StartScreen", "Spawn player passport on respawn.", false, true);
		STARTSCREEN_PASSPORT_SPAWN_ONCE = RegisterSettingBool("StartScreen.PassportSpawnOnce", "StartScreen", "When enabled passport will be spawn in the players inventory only once after the character was created.", false, true);
		STARTSCREEN_PASSPORT_UNIQ_NUMBER = RegisterSettingBool("StartScreen.PassportUniqNumber", "StartScreen", "Generate unique number for each individual passport item when enabled, otherwise steam profile hash.", false, true);
		STARTSCREEN_PASSPORT_SHOW_NUMBER = RegisterSettingBool("StartScreen.PassportShowNumber", "StartScreen", "Show passport number on passport view.", true, true);
		STARTSCREEN_PASSPORT_SHOW_GENDER = RegisterSettingBool("StartScreen.PassportShowGender", "StartScreen", "Show player gender on passport view.", true, true);
	}
}
