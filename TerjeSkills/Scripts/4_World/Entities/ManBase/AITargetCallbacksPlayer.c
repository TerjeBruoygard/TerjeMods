modded class AITargetCallbacksPlayer
{
	override float GetMaxVisionRangeModifier(EntityAI pApplicant)
	{
		float perkValue;
		float settingValue;
		float result = super.GetMaxVisionRangeModifier(pApplicant);

		if (g_Game && g_Game.IsDedicatedServer() && m_Player && pApplicant && m_Player.GetTerjeSkills() != null)
		{
			if (pApplicant.IsZombie())
			{
				ZombieBase zombie = ZombieBase.Cast(pApplicant);
				if (zombie)
				{
					if (GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_STEALTH_ZOMBIES_VISIBLE_MODIFIER, settingValue))
					{
						result *= Math.Max(0, settingValue);
					}
					
					if (!zombie.HasTerjeReceivedDamage() && m_Player.GetTerjeSkills().IsPerkRegistered("stlth", "invisman") && m_Player.GetTerjeSkills().GetPerkValue("stlth", "invisman", perkValue))
					{
						result *= Math.Clamp(1.0 + perkValue, 0, 1);
					}
				}
			}
			else if (pApplicant.IsAnimal())
			{				
				AnimalBase animal = AnimalBase.Cast(pApplicant);
				if (animal)
				{
					if (animal.IsInherited(Animal_CanisLupus) || animal.IsInherited(Animal_CanisFamiliaris_Dobermann_ColorBase) || animal.IsInherited(Animal_CanisFamiliaris_GermanShepherd_ColorBase))
					{
						if (GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_STEALTH_WOLVES_VISIBLE_MODIFIER, settingValue))
						{
							result *= Math.Max(0, settingValue);
						}
						
						if (!animal.HasTerjeReceivedDamage() && m_Player.GetTerjeSkills().IsPerkRegistered("stlth", "wolfinst") && m_Player.GetTerjeSkills().GetPerkValue("stlth", "wolfinst", perkValue))
						{
							result *= Math.Clamp(1.0 + perkValue, 0, 1);
						}
					}
					else if (animal.IsInherited(Animal_UrsusArctos))
					{
						if (GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_STEALTH_BEARS_VISIBLE_MODIFIER, settingValue))
						{
							result *= Math.Max(0, settingValue);
						}
						
						if (!animal.HasTerjeReceivedDamage() && m_Player.GetTerjeSkills().IsPerkRegistered("stlth", "bearfrnd") && m_Player.GetTerjeSkills().GetPerkValue("stlth", "bearfrnd", perkValue))
						{
							result *= Math.Clamp(1.0 + perkValue, 0, 1);
						}
					}
				}
			}
		}
		
		return result;
	}
}