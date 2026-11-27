modded class CAContinuousMineWood
{
	override void CreatePrimaryItems(ActionData action_data)
	{
		if (g_Game.IsDedicatedServer() && action_data.m_Player && action_data.m_Player.GetTerjeSkills() && action_data.m_MainItem)
		{
			if (TerjeEvent(GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_STRENGTH_ITEMS_USE_GAIN_CHANCE)))
			{
				int gainExp;
				if (GetTerjeSettingInt(TerjeSettingsCollection.SKILLS_STRENGTH_ITEMS_USE_GAIN_EXP, gainExp))
				{
					action_data.m_Player.GetTerjeSkills().AddSkillExperience("strng", gainExp);
				}
			}
		}
		
		super.CreatePrimaryItems(action_data);
	}
}

modded class ActionSawPlanks
{
	override void OnFinishProgressServer( ActionData action_data )
	{
		super.OnFinishProgressServer(action_data);
		
		if (g_Game.IsDedicatedServer() && action_data.m_Player && action_data.m_Player.GetTerjeSkills())
		{
			if (TerjeEvent(GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_STRENGTH_ITEMS_USE_GAIN_CHANCE)))
			{
				int gainExp;
				if (GetTerjeSettingInt(TerjeSettingsCollection.SKILLS_STRENGTH_ITEMS_USE_GAIN_EXP, gainExp))
				{
					action_data.m_Player.GetTerjeSkills().AddSkillExperience("strng", gainExp);
				}
			}
		}
	}
}