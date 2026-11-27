class TerjePlayerModifierWounds : TerjePlayerModifierBase
{
	private float m_visceraSymptom = 0;
	private float m_lastBrokenLegsExpGain = 0;
	private eBrokenLegs m_lastBrokenLegsState = eBrokenLegs.NO_BROKEN_LEGS;
	
	override float GetTimeout()
	{
		return 1;
	}
	
	override void OnServerFixedTick(PlayerBase player, float deltaTime)
	{
		super.OnServerFixedTick(player, deltaTime);
		
		if (!player.GetAllowDamage())
		{
			return;
		}
		
		float perkWhealingMod = 1.0;
		float perkSepsisresMod = 1.0;
		float perkThkbloodMod = 1.0;
		if (player.GetTerjeSkills())
		{
			float perkWhealing;
			if (player.GetTerjeSkills().GetPerkValue("immunity", "whealing", perkWhealing))
			{
				perkWhealingMod += perkWhealing;
			}
			float perkSepsisres;
			if (player.GetTerjeSkills().GetPerkValue("immunity", "sepsisres", perkSepsisres))
			{
				perkSepsisresMod -= Math.Clamp(perkSepsisres, 0, 1);
			}
			float perkThkblood;
			if (player.GetTerjeSkills().GetPerkValue("immunity", "thkblood", perkThkblood))
			{
				perkThkbloodMod += perkThkblood;
				perkThkbloodMod = Math.Clamp(perkThkbloodMod, 0.1, 1);
			}
		}
		
		// Hemostatic Effect
		float hemostaticModifier = 1;
		float hemostaticValue = 0;
		float hemostaticTimer = 0;
		if (player && player.IsAlive() && player.GetTerjeStats().GetHemostatic(hemostaticValue, hemostaticTimer) && hemostaticValue > 0)
		{
			hemostaticModifier /= (hemostaticValue + 1);
		}
		
		// Wounds
		int bulletsCount = player.GetTerjeStats().GetBulletWounds();
		int stubsCount = player.GetTerjeStats().GetStubWounds();
		bool viscera = player.GetTerjeStats().GetViscera();
		if (viscera && GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_VISCERA_ENABLED))
		{
			float visceraHealthLose = 0;
			float visceraBloodLose = 0;
			float visceraSymptonPeriod = 3;
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_VISCERA_HEALTH_LOSE, visceraHealthLose);
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_VISCERA_BLOOD_LOSE, visceraBloodLose);
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_VISCERA_SYMPTON_PERIOD, visceraSymptonPeriod);
			if (visceraHealthLose > 0)
			{
				DecreasePlayerHealth(player, TerjeDamageSource.WOUND_VISCERA, visceraHealthLose * deltaTime);
			}
			
			if (visceraBloodLose > 0)
			{
				DecreasePlayerBlood(player, TerjeDamageSource.WOUND_VISCERA, visceraBloodLose * perkThkbloodMod * hemostaticModifier * deltaTime);
			}
			
			if (!player || !player.IsAlive() || player.GetTerjeStats() == null)
			{
				return;
			}
			
			m_visceraSymptom += deltaTime;
			if (m_visceraSymptom > visceraSymptonPeriod)
			{
				m_visceraSymptom = 0;
				player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_COUGH);
			}
		}
		
		if (stubsCount > 0 && GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_STUBS_ENABLED))
		{
			float stubsHealthLose = 0;
			float stubsBloodLose = 0;
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_STUBS_HEALTH_LOSE, stubsHealthLose);
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_STUBS_BLOOD_LOSE, stubsBloodLose);
			if (stubsHealthLose > 0)
			{
				DecreasePlayerHealth(player, TerjeDamageSource.WOUND_STUB, stubsHealthLose * stubsCount * deltaTime);
			}
			
			if (stubsBloodLose > 0)
			{
				DecreasePlayerBlood(player, TerjeDamageSource.WOUND_STUB, stubsBloodLose * perkThkbloodMod * hemostaticModifier * stubsCount * deltaTime);
			}
			
			if (!player || !player.IsAlive() || player.GetTerjeStats() == null)
			{
				return;
			}
		}
		
		if (bulletsCount > 0 && GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_BULLETS_ENABLED))
		{
			float bulletsHealthLose = 0;
			float bulletsBloodLose = 0;
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_BULLETS_HEALTH_LOSE, bulletsHealthLose);
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_BULLETS_BLOOD_LOSE, bulletsBloodLose);
			if (bulletsHealthLose > 0)
			{
				DecreasePlayerHealth(player, TerjeDamageSource.WOUND_BULLET, bulletsHealthLose * bulletsCount * deltaTime);
			}
			
			if (bulletsBloodLose > 0)
			{
				DecreasePlayerBlood(player, TerjeDamageSource.WOUND_BULLET, bulletsBloodLose * perkThkbloodMod * hemostaticModifier * bulletsCount * deltaTime);
			}
			
			if (!player || !player.IsAlive() || player.GetTerjeStats() == null)
			{
				return;
			}
		}
		
		// Bandages
		float bandageHealTimeStat = player.GetTerjeStats().GetBandagesHealtime();
		int cleanBandages = player.GetTerjeStats().GetBandagesClean();
		int dirtyBandages = player.GetTerjeStats().GetBandagesDirty();
		if (cleanBandages > 0)
		{
			float cleanToDirtyBandageTime = 0;
			float cleanBandagedHealthLose = 0;
			float cleanBandagedBloodLose = 0;
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_CLEAN_TO_DIRTY_BANDAGE_TIME, cleanToDirtyBandageTime);
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_CLEAN_BANDAGED_WOUNDS_HEALTH_LOSE, cleanBandagedHealthLose);
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_CLEAN_BANDAGED_WOUNDS_BLOOD_LOSE, cleanBandagedBloodLose);
			if (cleanBandagedHealthLose > 0)
			{
				DecreasePlayerHealth(player, TerjeDamageSource.WOUND_BANDAGED, cleanBandagedHealthLose * cleanBandages * deltaTime);
			}
			
			if (cleanBandagedBloodLose > 0)
			{
				DecreasePlayerBlood(player, TerjeDamageSource.WOUND_BANDAGED, cleanBandagedBloodLose * perkThkbloodMod * hemostaticModifier * cleanBandages * deltaTime);
			}
			
			if (!player || !player.IsAlive() || player.GetTerjeStats() == null)
			{
				return;
			}
			
			if (cleanToDirtyBandageTime > 0)
			{
				float bandagesProgress = player.GetTerjeStats().GetBandagesProgress() + deltaTime;
				if (bandagesProgress > cleanToDirtyBandageTime)
				{
					cleanBandages -= 1;
					dirtyBandages += 1;
					
					player.GetTerjeStats().SetBandagesProgress(0);
					player.GetTerjeStats().SetBandagesClean(cleanBandages);
					player.GetTerjeStats().SetBandagesDirty(dirtyBandages);
				}
				else
				{
					player.GetTerjeStats().SetBandagesProgress(bandagesProgress);
				}
			}
		}
		
		if (dirtyBandages > 0)
		{
			float dirtyBandagedHealthLose = 0;
			float dirtyBandagedBloodLose = 0;
			float dirtyBandageInfectionChance = 0;
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_DIRTY_BANDAGED_WOUNDS_HEALTH_LOSE, dirtyBandagedHealthLose);
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_DIRTY_BANDAGED_WOUNDS_BLOOD_LOSE, dirtyBandagedBloodLose);
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_DIRTY_BANDAGE_INFECTION_CHANCE, dirtyBandageInfectionChance);
			if (dirtyBandagedHealthLose > 0)
			{
				DecreasePlayerHealth(player, TerjeDamageSource.WOUND_BANDAGED, dirtyBandagedHealthLose * dirtyBandages * deltaTime);
			}
			
			if (dirtyBandagedBloodLose > 0)
			{
				DecreasePlayerBlood(player, TerjeDamageSource.WOUND_BANDAGED, dirtyBandagedBloodLose * perkThkbloodMod * hemostaticModifier * dirtyBandages * deltaTime);
			}
			
			if (!player || !player.IsAlive() || player.GetTerjeStats() == null)
			{
				return;
			}
			
			float dirtyBandageSepsisTimer = player.GetTerjeStats().GetBandagesSepsisTimer();
			if (dirtyBandageSepsisTimer > GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_DIRTY_BANDAGE_INFECTION_TIMEOUT))
			{
				if (TerjeEvent(dirtyBandageInfectionChance * perkSepsisresMod * dirtyBandages * deltaTime))
				{
					player.GetTerjeStats().SetSepsisValue(player.GetTerjeStats().GetSepsisValue() + 0.1);
				}
			}
			
			player.GetTerjeStats().SetBandagesSepsisTimer(dirtyBandageSepsisTimer + deltaTime);
		}
		else
		{
			player.GetTerjeStats().SetBandagesSepsisTimer(0);
		}
		
		float bandagedWoundsHealTime = 0;
		if (cleanBandages > 0)
		{
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_BANDAGED_WOUNDS_HEAL_TIME, bandagedWoundsHealTime);
			bandageHealTimeStat += (perkWhealingMod * deltaTime);
			if (bandageHealTimeStat > bandagedWoundsHealTime)
			{
				cleanBandages -= 1;
				player.GetTerjeStats().SetBandagesClean(cleanBandages);
			}
		}
		else if (dirtyBandages > 0)
		{
			float dirtyBandageWoundsHealModifier = 1;
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_DIRTY_BANDAGE_WOUNDS_HEAL_MODIFIER, dirtyBandageWoundsHealModifier);
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_BANDAGED_WOUNDS_HEAL_TIME, bandagedWoundsHealTime);
			bandageHealTimeStat += (perkWhealingMod * deltaTime * dirtyBandageWoundsHealModifier);
			if (bandageHealTimeStat > bandagedWoundsHealTime)
			{
				dirtyBandages -= 1;
				player.GetTerjeStats().SetBandagesDirty(dirtyBandages);
			}
		}
		else
		{
			bandageHealTimeStat = 0;
		}
		
		player.GetTerjeStats().SetBandagesHealtime(bandageHealTimeStat);
		
		// Sutures
		bool isSuturesEnabled = GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_SUTURES_ENABLED);
		float suturesHealTimeStat = player.GetTerjeStats().GetSuturesHealtime();
		int suturesClean = player.GetTerjeStats().GetSuturesClean();
		int suturesDirty = player.GetTerjeStats().GetSuturesDirty();
		if (suturesClean > 0 && isSuturesEnabled)
		{
			float cleanToDirtySutureTime = 0;
			float cleanSutureHealthLose = 0;
			float cleanSutureBloodLose = 0;
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_CLEAN_TO_DIRTY_SUTURE_TIME, cleanToDirtySutureTime);
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_CLEAN_SUTURE_WOUNDS_HEALTH_LOSE, cleanSutureHealthLose);
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_CLEAN_SUTURE_WOUNDS_BLOOD_LOSE, cleanSutureBloodLose);
			if (cleanSutureHealthLose > 0)
			{
				DecreasePlayerHealth(player, TerjeDamageSource.WOUND_SUTURED, cleanSutureHealthLose * suturesClean * deltaTime);
			}
			
			if (cleanSutureBloodLose > 0)
			{
				DecreasePlayerBlood(player, TerjeDamageSource.WOUND_SUTURED, cleanSutureBloodLose * perkThkbloodMod * hemostaticModifier * suturesClean * deltaTime);
			}
			
			if (!player || !player.IsAlive() || player.GetTerjeStats() == null)
			{
				return;
			}
			
			if (cleanToDirtySutureTime > 0)
			{
				float saturesProgress = player.GetTerjeStats().GetSuturesProgress() + deltaTime;
				if (saturesProgress > cleanToDirtySutureTime)
				{
					suturesClean -= 1;
					suturesDirty += 1;
					
					player.GetTerjeStats().SetSuturesProgress(0);
					player.GetTerjeStats().SetSuturesClean(suturesClean);
					player.GetTerjeStats().SetSuturesDirty(suturesDirty);
				}
				else
				{
					player.GetTerjeStats().SetSuturesProgress(saturesProgress);
				}
			}
		}
		
		if (suturesDirty > 0 && isSuturesEnabled)
		{
			float dirtySutureHealthLose = 0;
			float dirtySutureBloodLose = 0;
			float dirtySutureInfectionChance = 0;
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_DIRTY_SUTURE_WOUNDS_HEALTH_LOSE, dirtySutureHealthLose);
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_DIRTY_SUTURE_WOUNDS_BLOOD_LOSE, dirtySutureBloodLose);
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_DIRTY_SUTURE_INFECTION_CHANCE, dirtySutureInfectionChance);
			if (dirtySutureHealthLose > 0)
			{
				DecreasePlayerHealth(player, TerjeDamageSource.WOUND_SUTURED, dirtySutureHealthLose * suturesDirty * deltaTime);
			}
			
			if (dirtySutureBloodLose > 0)
			{
				DecreasePlayerBlood(player, TerjeDamageSource.WOUND_SUTURED, dirtySutureBloodLose * perkThkbloodMod * hemostaticModifier * suturesDirty * deltaTime);
			}
			
			if (!player || !player.IsAlive() || player.GetTerjeStats() == null)
			{
				return;
			}
			
			float dirtySutureSepsisTimer = player.GetTerjeStats().GetSuturesSepsisTimer();
			if (dirtySutureSepsisTimer > GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_DIRTY_SUTURE_INFECTION_TIMEOUT))
			{
				if (TerjeEvent(dirtySutureInfectionChance * perkSepsisresMod * suturesDirty * deltaTime))
				{
					player.GetTerjeStats().SetSepsisValue(player.GetTerjeStats().GetSepsisValue() + 0.05);
				}
			}
			
			player.GetTerjeStats().SetSuturesSepsisTimer(dirtySutureSepsisTimer + deltaTime);
		}
		else
		{
			player.GetTerjeStats().SetSuturesSepsisTimer(0);
		}
		
		float suturedWoundsHealTime = 0;
		if (suturesClean > 0 && isSuturesEnabled)
		{
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_SUTURE_WOUNDS_HEAL_TIME, suturedWoundsHealTime);
			suturesHealTimeStat += (perkWhealingMod * deltaTime);
			if (suturesHealTimeStat > suturedWoundsHealTime)
			{
				suturesClean -= 1;
				player.GetTerjeStats().SetSuturesClean(suturesClean);
			}
		}
		else if (suturesDirty > 0 && isSuturesEnabled)
		{
			float dirtySutureWoundsHealModifier = 1;
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_DIRTY_SUTURE_WOUNDS_HEAL_MODIFIER, dirtySutureWoundsHealModifier);
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_SUTURE_WOUNDS_HEAL_TIME, suturedWoundsHealTime);
			suturesHealTimeStat += (perkWhealingMod * deltaTime * dirtySutureWoundsHealModifier);
			if (suturesHealTimeStat > suturedWoundsHealTime)
			{
				suturesDirty -= 1;
				player.GetTerjeStats().SetSuturesDirty(suturesDirty);
			}
		}
		else
		{
			suturesHealTimeStat = 0;
		}
		
		player.GetTerjeStats().SetSuturesHealtime(suturesHealTimeStat);
		
		// Bandaged Sutures
		float suturesBandagedHealTimeStat = player.GetTerjeStats().GetSuturesBandagedHealtime();
		int suturesBandagedClean = player.GetTerjeStats().GetSuturesBandagedClean();
		int suturesBandagedDirty = player.GetTerjeStats().GetSuturesBandagedDirty();
		if (suturesBandagedClean > 0 && isSuturesEnabled)
		{
			float cleanToDirtySutureBandagedTime = 0;
			float cleanSutureBandagedHealthLose = 0;
			float cleanSutureBandagedBloodLose = 0;
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_CLEAN_TO_DIRTY_SUTURE_BANDAGED_TIME, cleanToDirtySutureBandagedTime);
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_CLEAN_SUTURE_BANDAGED_WOUNDS_HEALTH_LOSE, cleanSutureBandagedHealthLose);
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_CLEAN_SUTURE_BANDAGED_WOUNDS_BLOOD_LOSE, cleanSutureBandagedBloodLose);
			if (cleanSutureBandagedHealthLose > 0)
			{
				DecreasePlayerHealth(player, TerjeDamageSource.WOUND_BANDAGED_SUTURED, cleanSutureBandagedHealthLose * suturesBandagedClean * deltaTime);
			}
			if (cleanSutureBandagedBloodLose > 0)
			{
				DecreasePlayerBlood(player, TerjeDamageSource.WOUND_BANDAGED_SUTURED, cleanSutureBandagedBloodLose * perkThkbloodMod * hemostaticModifier * suturesBandagedClean * deltaTime);
			}
			
			if (!player || !player.IsAlive() || player.GetTerjeStats() == null)
			{
				return;
			}
			
			if (cleanToDirtySutureBandagedTime > 0)
			{
				float saturesBandagedProgress = player.GetTerjeStats().GetSuturesBandagedProgress() + deltaTime;
				if (saturesBandagedProgress > cleanToDirtySutureBandagedTime)
				{
					suturesBandagedClean -= 1;
					suturesBandagedDirty += 1;
					
					player.GetTerjeStats().SetSuturesBandagedProgress(0);
					player.GetTerjeStats().SetSuturesBandagedClean(suturesBandagedClean);
					player.GetTerjeStats().SetSuturesBandagedDirty(suturesBandagedDirty);
				}
				else
				{
					player.GetTerjeStats().SetSuturesBandagedProgress(saturesBandagedProgress);
				}
			}
		}
		
		if (suturesBandagedDirty > 0 && isSuturesEnabled)
		{
			float dirtySutureBandagedHealthLose = 0;
			float dirtySutureBandagedBloodLose = 0;
			float dirtySutureBandagedInfectionChance = 0;
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_DIRTY_SUTURE_BANDAGED_WOUNDS_HEALTH_LOSE, dirtySutureBandagedHealthLose);
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_DIRTY_SUTURE_BANDAGED_WOUNDS_BLOOD_LOSE, dirtySutureBandagedBloodLose);
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_DIRTY_SUTURE_BANDAGED_INFECTION_CHANCE, dirtySutureBandagedInfectionChance);
			if (dirtySutureBandagedHealthLose > 0)
			{
				DecreasePlayerHealth(player, TerjeDamageSource.WOUND_BANDAGED_SUTURED, dirtySutureBandagedHealthLose * suturesBandagedDirty * deltaTime);
			}
			
			if (dirtySutureBandagedBloodLose > 0)
			{
				DecreasePlayerBlood(player, TerjeDamageSource.WOUND_BANDAGED_SUTURED, dirtySutureBandagedBloodLose * perkThkbloodMod * hemostaticModifier * suturesBandagedDirty * deltaTime);
			}
			
			if (!player || !player.IsAlive() || player.GetTerjeStats() == null)
			{
				return;
			}
			
			float dirtySutureBandagedSepsisTimer = player.GetTerjeStats().GetSuturesBandagedSepsisTimer();
			if (dirtySutureBandagedSepsisTimer > GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_DIRTY_SUTURE_BANDAGED_INFECTION_TIMEOUT))
			{
				if (TerjeEvent(dirtySutureBandagedInfectionChance * perkSepsisresMod * suturesBandagedDirty * deltaTime))
				{
					player.GetTerjeStats().SetSepsisValue(player.GetTerjeStats().GetSepsisValue() + 0.05);
				}
			}
			
			player.GetTerjeStats().SetSuturesBandagedSepsisTimer(dirtySutureBandagedSepsisTimer + deltaTime);
		}
		else
		{
			player.GetTerjeStats().SetSuturesBandagedSepsisTimer(0);
		}
		
		float suturedBandagedWoundsHealTime = 0;
		if (suturesBandagedClean > 0 && isSuturesEnabled)
		{
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_SUTURE_BANDAGED_WOUNDS_HEAL_TIME, suturedBandagedWoundsHealTime);
			suturesBandagedHealTimeStat += (perkWhealingMod * deltaTime);
			if (suturesBandagedHealTimeStat > suturedBandagedWoundsHealTime)
			{
				suturesBandagedClean -= 1;
				player.GetTerjeStats().SetSuturesBandagedClean(suturesBandagedClean);
			}
		}
		else if (suturesBandagedDirty > 0 && isSuturesEnabled)
		{
			float dirtySutureBandagedWoundsHealModifier = 1;
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_DIRTY_SUTURE_BANDAGED_WOUNDS_HEAL_MODIFIER, dirtySutureBandagedWoundsHealModifier);
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_SUTURE_BANDAGED_WOUNDS_HEAL_TIME, suturedBandagedWoundsHealTime);
			suturesBandagedHealTimeStat += (perkWhealingMod * deltaTime * dirtySutureBandagedWoundsHealModifier);
			if (suturesBandagedHealTimeStat > suturedBandagedWoundsHealTime)
			{
				suturesBandagedDirty -= 1;
				player.GetTerjeStats().SetSuturesBandagedDirty(suturesBandagedDirty);
			}
		}
		else
		{
			suturesBandagedHealTimeStat = 0;
		}
		
		player.GetTerjeStats().SetSuturesBandagedHealtime(suturesBandagedHealTimeStat);
		
		if (!player || !player.IsAlive() || player.GetTerjeStats() == null)
		{
			return;
		}
		
		// Sync wounds bitmask
		player.UpdateTerjeWoundsBitmask();
		
		// Handle experience for broken legs healing
		eBrokenLegs currentBrokenLegs = player.GetBrokenLegs();
		if (!player.IsUnconscious() && m_lastBrokenLegsState == eBrokenLegs.BROKEN_LEGS_SPLINT && currentBrokenLegs == eBrokenLegs.NO_BROKEN_LEGS)
		{
			if (player.GetTerjeSkills())
			{
				float immunityExpGain = GetTerjeSettingInt(TerjeSettingsCollection.MEDICINE_IMMUNITY_FIX_LEGS_EXP_GAIN);
				if (immunityExpGain > 0 && m_lastBrokenLegsExpGain <= 0)
				{
					player.GetTerjeSkills().AddSkillExperience("immunity", immunityExpGain);
					m_lastBrokenLegsExpGain = 1800; // exp gain delay to prevent exp farming
				}
			}
		}
		
		m_lastBrokenLegsState = currentBrokenLegs;
		
		if (m_lastBrokenLegsExpGain > 0)
		{
			m_lastBrokenLegsExpGain -= deltaTime;
		}
	}
}
