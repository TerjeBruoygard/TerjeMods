modded class DayZPlayerMeleeFightLogic_LightHeavy
{
	int TerjeSkills_BlockAttackExtended()
	{
		if (!IsInBlock())
		{
			return 1;
		}
		
		if (m_Player && m_Player.GetTerjeSkills() && m_Player.CanConsumeStamina(EStaminaConsumers.MELEE_EVADE))
		{
			m_Player.DepleteStaminaEx(EStaminaModifiers.MELEE_EVADE);
			
			float successBlockPerkModifier;
			m_Player.GetTerjeSkills().GetPerkValue("strng", "mrevasion", successBlockPerkModifier)
			if (TerjeEvent(successBlockPerkModifier))
			{
				return 2;
			}
			
			return 1;
		}
		
		return 0;
	}
	
	override void EvaluateHit_Common(InventoryItem weapon, Object target, bool forcedDummy=false, int forcedWeaponMode = -1)
	{
		if (target)
		{
			PlayerBase targetPlayer = PlayerBase.Cast(target);
			if (targetPlayer && targetPlayer.GetMeleeFightLogic())
			{
				int blockResponse = targetPlayer.GetMeleeFightLogic().TerjeSkills_BlockAttackExtended();
				if (blockResponse == 2)
				{
					// Evoid attack
					forcedDummy = true;
				}
				else if (blockResponse == 0)
				{
					// Escalate attack
					forcedDummy = false;
				}
			}
		}
		
		super.EvaluateHit_Common(weapon, target, forcedDummy, forcedWeaponMode);
	}
	
	override bool EvaluateFinisherAttack(InventoryItem weapon, Object target)
	{
		if (super.EvaluateFinisherAttack(weapon, target))
		{
			if (g_Game && g_Game.IsDedicatedServer() && m_Player && m_Player.GetTerjeSkills())
			{
				if (TerjeEvent(GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_STEALTH_FINISHER_GAIN_CHANCE)))
				{
					int stealthFinisherGainExp;
					if (GetTerjeSettingInt(TerjeSettingsCollection.SKILLS_STEALTH_FINISHER_GAIN_EXP, stealthFinisherGainExp))
					{
						m_Player.GetTerjeSkills().AddSkillExperience("stlth", stealthFinisherGainExp);
					}
				}
			}
			
			return true;
		}
		
		return false;
	}
}