modded class ActionFishingNew
{
	override protected EntityAI TrySpawnCatch(FishingActionData action_data)
	{
		float catchChance = 1;
		if (action_data.m_Player && action_data.m_Player.GetTerjeSkills())
		{
			float modifierValue;
			catchChance = Math.Clamp(GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_FISHING_OVERRIDE_BASE_CATCH_CHANCE), 0, 1);
			if (action_data.m_Player.GetTerjeSkills().GetSkillModifierValue("fish", "catchmod", modifierValue))
			{
				modifierValue = Math.Clamp(modifierValue, 0, 1);
				catchChance += (1.0 - catchChance) * modifierValue;
			}
		}
		
		EntityAI result = super.TrySpawnCatch(action_data);
		
		if (catchChance < Math.RandomFloat01())
		{
			if (result) result.Delete(); // cleanup
			return null;
		}
		
		if (action_data.m_Player && result)
		{
			if (TerjeProcessingSpawnCatch(action_data, result))
			{
				vector pos = action_data.m_Player.GetPosition();
				EntityAI extra = EntityAI.Cast(g_Game.CreateObjectEx(result.GetType(), pos, ECE_PLACE_ON_SURFACE));
			}
		}
		return result;
	}
	
	bool TerjeProcessingSpawnCatch(FishingActionData action_data, EntityAI fishItem)
	{
		bool spawnExtraFish = false;
		PlayerBase player = PlayerBase.Cast(action_data.m_Player);
		ItemBase fishingRod = ItemBase.Cast(action_data.m_MainItem);
		ItemBase resultItem = ItemBase.Cast(fishItem);
		
		if (g_Game.IsDedicatedServer())
		{
			int expGainValue;
			if (fishItem)
			{
				expGainValue = GetTerjeSettingInt(TerjeSettingsCollection.SKILLS_FISHING_SUCCESS_CATCH_EXP_GAIN);
				
				if (resultItem && resultItem.IsTerjeWholeFish())
				{
					float perkValue;
					if (g_Game.IsDedicatedServer() && player && player.GetTerjeSkills() && player.GetTerjeSkills().GetPerkValue("fish", "fishmluck", perkValue))
					{
						// Spawn extra fish
						if (Math.RandomFloat01() < (perkValue * 0.5))
						{
							spawnExtraFish = true;
						}
					}
				}
			}
			else
			{
				expGainValue = GetTerjeSettingInt(TerjeSettingsCollection.SKILLS_FISHING_FAILED_CATCH_EXP_GAIN);
			}
			
			if (player && player.GetTerjeSkills())
			{
				if (fishingRod && GetTerjeGameConfig().ConfigIsExisting("CfgVehicles " + fishingRod.GetType() + " terjeFishingExpModifier"))
				{
					expGainValue = (int)(expGainValue * GetTerjeGameConfig().ConfigGetFloat("CfgVehicles " + fishingRod.GetType() + " terjeFishingExpModifier"));
				}
				
				if (expGainValue > 0)
				{
					player.GetTerjeSkills().AddSkillExperience("fish", expGainValue);
				}
			}
		}
		
		return spawnExtraFish;
	}
}

modded class CatchingContextFishingRodAction
{
	override protected void TryDamageItems()
	{
		if (g_Game.IsDedicatedServer() && m_Player && m_Player.GetTerjeSkills() && m_Player.GetTerjeSkills().IsPerkRegistered("fish", "strgarms"))
		{
			float settingValue;
			float perkStrgarms;
			float perkValue = 1.0;
			if (m_Player.GetTerjeSkills().GetPerkValue("fish", "strgarms", perkStrgarms))
			{
				perkValue = Math.Clamp(1.0 + perkStrgarms, 0, 1);
			}
			
			if (m_Hook && !m_Hook.IsSetForDeletion())
			{
				settingValue = GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_FISHING_OVERRIDE_HOOK_DAMAGE);
				m_Hook.AddHealth("", "Health", settingValue * perkValue * -1.0);
			}
			
			if (m_Rod && !m_Rod.IsSetForDeletion())
			{
				settingValue = GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_FISHING_OVERRIDE_ROD_DAMAGE);
				m_Rod.AddHealth("", "Health", settingValue * perkValue * -1.0);
			}
		}
		else
		{
			super.TryDamageItems();
		}
	}
	
	override float GetChanceCoef()
	{
		float result = super.GetChanceCoef();
		if (m_Player && m_Player.GetTerjeSkills())
		{
			float perkValue;
			if (m_Player.GetTerjeSkills().GetPerkValue("fish", "skfishman", perkValue))
			{
				result *= Math.Max(1.0, 1.0 + perkValue);
			}
		}
		
		return result;
	}
	
	override float RandomizeSignalDuration()
	{
		float result = super.RandomizeSignalDuration();
		if (m_Player && m_Player.GetTerjeSkills())
		{
			float perkValue;
			if (m_Player.GetTerjeSkills().GetPerkValue("fish", "skfishman", perkValue))
			{
				result *= Math.Max(1.0, 1.0 + perkValue);
			}
		}
		
		return result;
	}
	
	override float RandomizeSignalStartTime()
	{
		float result = super.RandomizeSignalStartTime();
		if (m_Player && m_Player.GetTerjeSkills())
		{
			float perkValue;
			if (m_Player.GetTerjeSkills().GetPerkValue("fish", "skfishman", perkValue))
			{
				result /= Math.Max(1.0, 1.0 + perkValue);
			}
		}
		
		return result;
	}
	
	override float GetQualityModifier()
	{
		float result = super.GetQualityModifier();
		if (g_Game.IsDedicatedServer() && m_Player && m_Player.GetTerjeSkills() && m_Player.GetTerjeSkills().IsPerkRegistered("fish", "fishmluck"))
		{
			result *= GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_FISHING_FISH_SIZE_MODIFIER);
			
			float perkValue;
			if (m_Player.GetTerjeSkills().GetPerkValue("fish", "fishmluck", perkValue))
			{
				result += Math.Max(0.0, perkValue);
			}
		}
		
		return result;
	}
	
	override float GetHookLossChanceModifierClamped()
	{
		float result = super.GetHookLossChanceModifierClamped();
		if (m_Player && m_Player.GetTerjeSkills())
		{
			float perkValue;
			if (m_Player.GetTerjeSkills().GetPerkValue("fish", "reliabgear", perkValue))
			{
				result *= Math.Clamp(1.0 + perkValue, 0, 1);
			}
		}
		
		return result;
	}
	
	override float GetBaitLossChanceModifierClamped()
	{
		float result = super.GetBaitLossChanceModifierClamped();
		if (m_Player && m_Player.GetTerjeSkills())
		{
			float perkValue;
			if (m_Player.GetTerjeSkills().GetPerkValue("fish", "reliabgear", perkValue))
			{
				result *= Math.Clamp(1.0 + perkValue, 0, 1);
			}
		}
		
		return result;
	}
}