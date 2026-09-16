modded class ActionHarvestCrops
{
	override void OnFinishProgressServer(ActionData action_data)
	{
		super.OnFinishProgressServer(action_data);
		
		if (!m_Plant || !action_data.m_Player || !action_data.m_Player.GetTerjeSkills())
		{
			return;
		}
		
		int expGain = GetTerjeSettingInt(TerjeSettingsCollection.SKILLS_FARMING_HARVEST_EXP_GAIN);
		if (expGain > 0)
		{
			action_data.m_Player.GetTerjeSkills().AddSkillExperience("farm", expGain);
		}
	}
}
