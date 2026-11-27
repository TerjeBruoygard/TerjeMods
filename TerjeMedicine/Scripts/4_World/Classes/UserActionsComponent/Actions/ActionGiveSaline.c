modded class ActionGiveSalineSelf
{
	override void OnFinishProgressServer( ActionData action_data )
	{
		super.OnFinishProgressServer(action_data);
		OnTerjeFinishApplyMedExperience(action_data);
	}
	
	void OnTerjeFinishApplyMedExperience(ActionData action_data)
	{
		PlayerBase operator = PlayerBase.Cast(action_data.m_Player);
		if (operator && operator.GetTerjeSkills())
		{
			int skillIncrement = GetTerjeSettingInt(TerjeSettingsCollection.MEDICINE_MEDICINE_GIVE_SALINE_EXP_GAIN);
			if (skillIncrement > 0)
			{
				operator.GetTerjeSkills().AddSkillExperience("med", (int)skillIncrement);
			}
		}
	}
}

modded class ActionGiveSalineTarget
{
	override void OnFinishProgressServer( ActionData action_data )
	{
		super.OnFinishProgressServer(action_data);
		OnTerjeFinishApplyMedExperience(action_data);
	}
	
	void OnTerjeFinishApplyMedExperience(ActionData action_data)
	{
		PlayerBase player_target = PlayerBase.Cast(action_data.m_Target.GetObject());
		
		if (player_target && !player_target.TerjeIsNPC())
		{
			PlayerBase operator = PlayerBase.Cast(action_data.m_Player);
			if (operator && operator.GetTerjeSkills())
			{
				int skillIncrement = GetTerjeSettingInt(TerjeSettingsCollection.MEDICINE_MEDICINE_GIVE_SALINE_EXP_GAIN);
				if (skillIncrement > 0)
				{
					operator.GetTerjeSkills().AddSkillExperience("med", (int)skillIncrement);
				}
			}
		}
	}
}
