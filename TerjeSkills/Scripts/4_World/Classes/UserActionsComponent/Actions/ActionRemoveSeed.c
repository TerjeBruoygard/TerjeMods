modded class ActionRemoveSeed
{
	override void OnExecuteServer(ActionData action_data)
	{
		super.OnExecuteServer(action_data);
		TerjeRemovePlantingExperience(action_data);
	}
	
	protected void TerjeRemovePlantingExperience(ActionData action_data)
	{
		if (!action_data.m_Player || !action_data.m_Player.GetTerjeSkills())
		{
			return;
		}
		
		int expGain = GetTerjeSettingInt(TerjeSettingsCollection.SKILLS_FARMING_SEED_PLANTED_EXP_GAIN);
		if (expGain > 0)
		{
			action_data.m_Player.GetTerjeSkills().AddSkillExperience("farm", expGain * -1);
		}
	}
}
