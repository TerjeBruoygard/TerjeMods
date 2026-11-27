class TerjePlayerModifierZVirus : TerjePlayerModifierBase
{
	private float m_immunityInterval = 0;
	private float m_zedVoiceTimer = 0;
	
	override float GetTimeout()
	{
		return 0.5;
	}
	
	override void OnServerFixedTick(PlayerBase player, float deltaTime)
	{
		super.OnServerFixedTick(player, deltaTime);
		
		float antidotTime = player.GetTerjeStats().GetZAntidotValue();
		if (antidotTime > 0)
		{
			player.GetTerjeStats().SetZAntidotValue(antidotTime - deltaTime);
		}
		
		float vacineTime = player.GetTerjeStats().GetZVirusVacineValue();
		if (vacineTime > 0)
		{
			player.GetTerjeStats().SetZVirusVacineValue(vacineTime - deltaTime);
		}
		
		if (GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_Z_VIRUS_ENABLED) == false)
		{
			player.GetTerjeStats().SetZVirusValue(0);
			return;
		}
		
		if (m_immunityInterval > 0)
		{
			m_immunityInterval -= deltaTime;
		}
	
		float zombieValue = player.GetTerjeStats().GetZVirusValue();
		if (zombieValue > 0)
		{
			int zombieIntOrig = (int)zombieValue;
			if (vacineTime > 1 && zombieValue < 0.5)
			{
				zombieValue = 0;
			}
			else
			{
				float vacineProgressionMod = 1.0;
				if (vacineTime > 1)
				{
					vacineProgressionMod = 0.5;
				}
				
				float immunityMod = Math.Clamp(1.0 - GetPlayerImmunity(player), 0.35, 1.0);
				float zombieIncPerSec = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_Z_VIRUS_INC_PER_SEC);
				zombieValue += (zombieIncPerSec * immunityMod * vacineProgressionMod * deltaTime);
			}
			
			if (antidotTime > 0)
			{
				float zombieDecPerSec = 1;
				GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_Z_VIRUS_DEC_PER_SEC, zombieDecPerSec);
				zombieValue -= (zombieDecPerSec * deltaTime);
			}
			
			player.GetTerjeStats().SetZVirusValue(zombieValue);
			
			if (!player.GetAllowDamage())
			{
				return;
			}
			
			if (zombieValue > 1)
			{
				if (TerjeEvent(GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_Z_VIRUS_LIGHT_SYMPTOM_CHANCE) * deltaTime))
				{
					float zvirusVomitForceModifier = 0.25;
					GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_Z_VIRUS_VOMIT_FORCE_MODIFIER, zvirusVomitForceModifier);					
					player.CallTerjeVomitSymptom(Math.RandomIntInclusive(3, 5), zvirusVomitForceModifier);
				}
			}
			
			if (zombieValue > 2)
			{
				if (TerjeEvent(GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_Z_VIRUS_HEAVY_SYMPTOM_CHANCE) * deltaTime))
				{
					player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_PAIN_LIGHT);
					player.GetBleedingManagerServer().AttemptAddBleedingSource( Math.RandomIntInclusive(0, 5) );
				}
			}
			
			if (zombieValue > 3)
			{
				float zombieCriticalDmgMultiplier = 1;
				GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_Z_VIRUS_CRITICAL_DMG_MULTIPLIER, zombieCriticalDmgMultiplier);
				float dmgForce = (zombieValue - 3.0) * zombieCriticalDmgMultiplier;
				DecreasePlayerHealth(player, TerjeDamageSource.ZVIRUS, dmgForce * deltaTime);
				
				if (!player || !player.IsAlive() || player.GetTerjeStats() == null)
				{
					return;
				}
				
				m_zedVoiceTimer += deltaTime;
				if (m_zedVoiceTimer > 5)
				{
					if (TerjeEvent(GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_Z_VIRUS_CRITICAL_SYMPTOM_CHANCE) * deltaTime))
					{
						m_zedVoiceTimer = 0;
						
						string soundSet = GetZedSoundset(player.IsMale());
						player.TerjeSendSoundEvent(soundSet, TERJE_SOUND_EVENT_TYPE_VOICE, 1.0);
					}
				}
			}
			
			if (zombieIntOrig > 0 && zombieValue < 1 && m_immunityInterval <= 0)
			{
				float immunityExpGain = 0;
				GetTerjeSettingInt(TerjeSettingsCollection.MEDICINE_IMMUNITY_ZOMBIE_EXP_GAIN, immunityExpGain);
				if (immunityExpGain > 0 && player.GetTerjeSkills())
				{
					player.GetTerjeSkills().AddSkillExperience("immunity", immunityExpGain);
					m_immunityInterval = 1800;
				}
			}
		}
	}
	
	string GetZedSoundset(bool isMale)
	{
		int rand = Math.RandomIntInclusive(0, 1);
		
		if (isMale)
		{
			if (rand == 0) return "ZmbM_HunterOld_Base_DisturbedIdle_Soundset";
			if (rand == 1) return "ZmbM_HunterOld_Base_CalmMove_Soundset";
			return "";
		}
		else
		{
			if (rand == 0) return "ZmbF_CitizenANormal_Base_DisturbedIdle_Soundset";
			if (rand == 1) return "ZmbF_CitizenANormal_Base_CalmMove_Soundset";
			return "";
		}
	}
}
