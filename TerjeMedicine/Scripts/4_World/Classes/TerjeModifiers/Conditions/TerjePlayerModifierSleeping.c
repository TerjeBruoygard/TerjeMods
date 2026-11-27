class TerjePlayerModifierSleeping : TerjePlayerModifierBase
{
	private float m_sleepingLastValue = -1;
	private float m_terjeMedicineSleepingSoundTimer = 0;
	private bool m_lastSleepingMarker = false;
	
	override void OnServerFixedTick(PlayerBase player, float deltaTime)
	{
		super.OnServerFixedTick(player, deltaTime);
		
		if (!GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_SLEEPING_ENABLED))
		{
			return;
		}
		
		// Handle tendency and visual stats
		float currentSleepingValue = player.GetTerjeStats().GetSleepingValue();
		if (m_sleepingLastValue < 0)
		{
			m_sleepingLastValue = currentSleepingValue;
		}
		
		float sleepingDiffTend = currentSleepingValue - m_sleepingLastValue;
		int sleepTendency = 0;
		if (sleepingDiffTend < 0)
		{
			if      (sleepingDiffTend > TerjeMedicineConstants.SLEEPING_TENDENCY_MINUS_STAGE1) sleepTendency = -1;
			else if (sleepingDiffTend > TerjeMedicineConstants.SLEEPING_TENDENCY_MINUS_STAGE2) sleepTendency = -2;
			else                                                                               sleepTendency = -3;
		}
		else if (sleepingDiffTend > 0)
		{
			if      (sleepingDiffTend < TerjeMedicineConstants.SLEEPING_TENDENCY_PLUS_STAGE1) sleepTendency = 1;
			else if (sleepingDiffTend < TerjeMedicineConstants.SLEEPING_TENDENCY_PLUS_STAGE2) sleepTendency = 2;
			else                                                                              sleepTendency = 3;
		}
		
		int sleepLevel = 0;
		if      (currentSleepingValue < TerjeMedicineConstants.SLEEPING_LEVEL5) sleepLevel = 5;
		else if (currentSleepingValue < TerjeMedicineConstants.SLEEPING_LEVEL4) sleepLevel = 4;
		else if (currentSleepingValue < TerjeMedicineConstants.SLEEPING_LEVEL3) sleepLevel = 3;
		else if (currentSleepingValue < TerjeMedicineConstants.SLEEPING_LEVEL2) sleepLevel = 2;
		else                                                                    sleepLevel = 1;
		
		// Handle wake-up conditions
		bool isEnergedMarker = false;
		int lastSleepingStateInt = player.GetTerjeStats().GetSleepingState();
		if (GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_SLEEPING_BLOCK_ON_FULL) && sleepLevel == 1 && lastSleepingStateInt <= 0)
		{
			isEnergedMarker = true;
		}
		
		if (GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_SLEEPING_AWAKE_ON_FULL) && m_sleepingLastValue >= TerjeMedicineConstants.SLEEPING_MAX_VALUE)
		{
			isEnergedMarker = true;
		}
		
		// Update sleeping tendency
		player.GetTerjeStats().SetSleepingLevelAndTendency(sleepLevel, sleepTendency);
		m_sleepingLastValue = currentSleepingValue;
		
		// Handle energy-drink effects
		float sleepingIncValue;
		float sleepingIncTimer;
		if (player.GetTerjeStats().GetSleepingIncrement(sleepingIncValue, sleepingIncTimer))
		{
			sleepingIncTimer -= deltaTime;
			if (sleepingIncTimer <= 0)
			{
				sleepingIncValue = 0;
			}
			
			if (sleepingIncValue > 0)
			{
				currentSleepingValue += sleepingIncValue * deltaTime;
				isEnergedMarker = true;
			}
			
			player.GetTerjeStats().SetSleepingIncrement(sleepingIncValue, sleepingIncTimer);
		}
		
		if (player.GetTerjeStats().GetSleepingDecrement(sleepingIncValue, sleepingIncTimer))
		{
			sleepingIncTimer -= deltaTime;
			if (sleepingIncTimer <= 0)
			{
				sleepingIncValue = 0;
			}
			
			if (sleepingIncValue > 0)
			{
				currentSleepingValue -= sleepingIncValue * deltaTime;
			}
			
			player.GetTerjeStats().SetSleepingDecrement(sleepingIncValue, sleepingIncTimer);
		}
		
		// Handle action stats
		float sleepingDiff = 0;
		if (player.GetAllowDamage())
		{
			float sleepingDecPerSec = 0;
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_SLEEPING_DEC_PER_SEC_COMMON, sleepingDecPerSec);
			sleepingDiff -= (sleepingDecPerSec * deltaTime);
		}
		
		TerjeMedicineSleepingLevel sleepingState = TerjeMedicineSleepingLevel.TERJESL_NONE;	
		bool isUnconsciousMarker = player.IsUnconscious();
		bool isSleepingMarker = (player.GetEmoteManager() && player.GetEmoteManager().IsPlayerSleeping());
		bool isFirstSleepingTick = (!m_lastSleepingMarker && isSleepingMarker);
		if (isSleepingMarker || isUnconsciousMarker || isEnergedMarker)
		{
			float perkFsleepMod = 1.0;
			if (player.GetTerjeSkills())
			{
				float perkFsleep;
				if (player.GetTerjeSkills().GetPerkValue("immunity", "fsleep", perkFsleep))
				{
					perkFsleepMod += perkFsleep;
				}
			}
			
			float heatValue = player.GetStatHeatComfort().Get();
			float sleepingIncUncon = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_SLEEPING_INC_UNCONSCION);
			if (isUnconsciousMarker && sleepingIncUncon > 0)
			{
				sleepingState = TerjeMedicineSleepingLevel.TERJESL_NONE;
				sleepingDiff += (sleepingIncUncon * perkFsleepMod * deltaTime);
			}
			else if (player.HasTerjeSicknesOrInjures() && GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_SLEEPING_BLOCK_WITH_WOUNDS))
			{
				sleepingState = TerjeMedicineSleepingLevel.TERJESL_SICK;
				if (isFirstSleepingTick)
				{
					NotificationSystem.SendNotificationToPlayerExtended(player, 5, "#STR_TERJEMED_NOSLEEP_TITLE", "#STR_TERJEMED_NOSLEEP_SICK", "set:TerjeMedicine_icon image:tm_sleeping_3");
				}
			}
			else if (isEnergedMarker)
			{
				sleepingState = TerjeMedicineSleepingLevel.TERJESL_ENERGED;
				if (isFirstSleepingTick)
				{
					NotificationSystem.SendNotificationToPlayerExtended(player, 5, "#STR_TERJEMED_NOSLEEP_TITLE", "#STR_TERJEMED_NOSLEEP_ENERGED", "set:TerjeMedicine_icon image:tm_sleeping_3");
				}
			}
			else if (heatValue < PlayerConstants.THRESHOLD_HEAT_COMFORT_MINUS_WARNING)
			{
				sleepingState = TerjeMedicineSleepingLevel.TERJESL_COLD;
				if (isFirstSleepingTick)
				{
					NotificationSystem.SendNotificationToPlayerExtended(player, 5, "#STR_TERJEMED_NOSLEEP_TITLE", "#STR_TERJEMED_NOSLEEP_COLD", "set:TerjeMedicine_icon image:tm_sleeping_3");
				}
			}
			else if (heatValue > PlayerConstants.THRESHOLD_HEAT_COMFORT_PLUS_CRITICAL)
			{
				sleepingState = TerjeMedicineSleepingLevel.TERJESL_HOT;
				if (isFirstSleepingTick)
				{
					NotificationSystem.SendNotificationToPlayerExtended(player, 5, "#STR_TERJEMED_NOSLEEP_TITLE", "#STR_TERJEMED_NOSLEEP_HOT", "set:TerjeMedicine_icon image:tm_sleeping_3");
				}
			}
			else if (player.GetHeatBufferStage() > 0)
			{
				float sleepingIncComfort = 0;
				GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_SLEEPING_INC_COMFORT, sleepingIncComfort);
				sleepingState = TerjeMedicineSleepingLevel.TERJESL_PERFECT;
				sleepingDiff += (sleepingIncComfort * perkFsleepMod * deltaTime);
			}
			else
			{
				float sleepingIncCommon = 0;
				GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_SLEEPING_INC_COMMON, sleepingIncCommon);
				sleepingState = TerjeMedicineSleepingLevel.TERJESL_COMFORT;
				sleepingDiff += (sleepingIncCommon * perkFsleepMod * deltaTime);
			}
		}
		
		int sleepingStateInt = (int)sleepingState;
		player.GetTerjeStats().SetSleepingState(sleepingStateInt);
		m_lastSleepingMarker = isSleepingMarker;
		
		if (sleepingStateInt > 0 && !isUnconsciousMarker)
		{
			m_terjeMedicineSleepingSoundTimer += deltaTime;
			if (m_terjeMedicineSleepingSoundTimer >= 5)
			{
				m_terjeMedicineSleepingSoundTimer = 0;
				if (GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_SLEEPING_USE_SNORE))
				{
					if (player.IsMale())
					{
						player.TerjeSendSoundEvent("sleepingMaleTerje_SoundSet", TERJE_SOUND_EVENT_TYPE_VOICE, 1.0);
					}
					else
					{
						player.TerjeSendSoundEvent("sleepingFemaleTerje_SoundSet", TERJE_SOUND_EVENT_TYPE_VOICE, 1.0);
					}
				}
			}
			
			float sleepingIncHealth = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_SLEEPING_HEALTH_INC);
			if (sleepingIncHealth > 0)
			{
				AddPlayerHealth(player, sleepingIncHealth * deltaTime);
			}
			
			float sleepingIncBlood = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_SLEEPING_BLOOD_INC);
			if (sleepingIncBlood > 0)
			{
				AddPlayerBlood(player, sleepingIncBlood * deltaTime);
			}
			
			float sleepingIncMind = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_SLEEPING_MIND_INC);
			if (sleepingIncMind > 0)
			{
				player.GetTerjeStats().SetMindValue(player.GetTerjeStats().GetMindValue() + (sleepingIncMind * deltaTime));
			}
		}
		else
		{
			m_terjeMedicineSleepingSoundTimer = -10;
		}
		
		currentSleepingValue += sleepingDiff;
		player.GetTerjeStats().SetSleepingValue(currentSleepingValue);
		
		if (!player.GetAllowDamage())
		{
			return;
		}
		
		if (currentSleepingValue < TerjeMedicineConstants.SLEEPING_UNCONSCIOUS) 
		{
			SetPlayerShock(player, TerjeDamageSource.SLEEPING, 0);
		}
		
		if (currentSleepingValue < TerjeMedicineConstants.SLEEPING_CRITICAL) 
		{
			float sleepingHealthDecCritical = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_SLEEPING_HEALTH_DEC);
			if (sleepingHealthDecCritical > 0)
			{
				DecreasePlayerHealth(player, TerjeDamageSource.SLEEPING, sleepingHealthDecCritical * deltaTime);
			}
			
			float sleepingBloodDecCritical = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_SLEEPING_BLOOD_DEC);
			if (sleepingBloodDecCritical > 0)
			{
				DecreasePlayerBlood(player, TerjeDamageSource.SLEEPING, sleepingBloodDecCritical * deltaTime);
			}
			
			if (!player || !player.IsAlive() || player.GetTerjeStats() == null)
			{
				return;
			}
			
			float sleepingMindDecCritical = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_SLEEPING_MIND_DEC);
			if (sleepingMindDecCritical > 0)
			{
				player.GetTerjeStats().SetMindValue(player.GetTerjeStats().GetMindValue() - (sleepingMindDecCritical * deltaTime));
			}
		}
	}
}
