modded class ActionFertilizeSlot
{
	override void OnEndServer(ActionData action_data)
	{
		super.OnEndServer(action_data);
		
		if (!action_data.m_WasActionStarted || !action_data.m_Player || !action_data.m_Player.GetTerjeSkills())
		{
			return;
		}
		
		int expGain = GetTerjeSettingInt(TerjeSettingsCollection.SKILLS_FARMING_FERTILIZE_EXP_GAIN);
		if (expGain > 0)
		{
			action_data.m_Player.GetTerjeSkills().AddSkillExperience("farm", expGain);
		}
	}
}

modded class CAContinuousFertilizeGardenSlot
{
	protected PlayerBase m_TerjeFertilizingPlayer;
	
	override void Setup(ActionData action_data)
	{
		super.Setup(action_data);
		
		m_TerjeFertilizingPlayer = action_data.m_Player;
	}
	
	override void FertilizeSlot(ItemBase item, GardenBase gardenBase, float consumedQuantity)
	{
		float usageMult = GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_FARMING_OVERRIDE_FERTILIZE_USAGE_MULT);
		float terjeConsumedQuantity = consumedQuantity * usageMult;
		
		if (m_TerjeFertilizingPlayer && m_TerjeFertilizingPlayer.GetTerjeSkills())
		{
			float richSoilValue;
			if (m_TerjeFertilizingPlayer.GetTerjeSkills().GetPerkValue("farm", "richsoil", richSoilValue))
			{
				terjeConsumedQuantity = terjeConsumedQuantity * (1.0 + richSoilValue);
			}
		}
		
		super.FertilizeSlot(item, gardenBase, terjeConsumedQuantity);
	}
}
