modded class ActionWaterGardenSlot
{
	override void OnEndServer(ActionData action_data)
	{
		super.OnEndServer(action_data);
		
		if (!action_data.m_WasActionStarted || !action_data.m_Player || !action_data.m_Player.GetTerjeSkills())
		{
			return;
		}
		
		int expGain = GetTerjeSettingInt(TerjeSettingsCollection.SKILLS_FARMING_WATER_EXP_GAIN);
		if (expGain > 0)
		{
			action_data.m_Player.GetTerjeSkills().AddSkillExperience("farm", expGain);
		}
	}
}

modded class ActionWaterPlant
{
	override void OnEndServer(ActionData action_data)
	{
		super.OnEndServer(action_data);
		
		if (!action_data.m_WasActionStarted || !action_data.m_Player || !action_data.m_Player.GetTerjeSkills())
		{
			return;
		}
		
		int expGain = GetTerjeSettingInt(TerjeSettingsCollection.SKILLS_FARMING_WATER_EXP_GAIN);
		if (expGain > 0)
		{
			action_data.m_Player.GetTerjeSkills().AddSkillExperience("farm", expGain);
		}
	}
}
