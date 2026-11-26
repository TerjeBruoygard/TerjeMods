modded class ActionGiveBloodSelf
{
	override void OnEndServer( ActionData action_data )
	{
		ActionGiveBloodData action_data_b = ActionGiveBloodData.Cast( action_data );
		float blood_obtained = action_data_b.m_BloodAmount - action_data_b.m_MainItem.GetQuantity();
		
		super.OnEndServer(action_data);
		
		PlayerBase operator = PlayerBase.Cast(action_data.m_Player);
		if (operator && operator.GetTerjeSkills() && blood_obtained > 0)
		{
			int skillIncrement = GetTerjeSettingInt(TerjeSettingsCollection.MEDICINE_MEDICINE_GIVE_BLOOD_EXP_GAIN);
			if (skillIncrement > 0)
			{
				float XP_obtained = skillIncrement * blood_obtained / action_data_b.m_MainItem.GetQuantityMax();
				operator.GetTerjeSkills().AddSkillExperience("med", (int)XP_obtained);
			}
		}
	}
}

modded class ActionGiveBloodTarget
{
	override void OnEndServer( ActionData action_data )
	{
		ActionGiveBloodData action_data_b = ActionGiveBloodData.Cast( action_data );
		float blood_obtained = action_data_b.m_BloodAmount - action_data_b.m_MainItem.GetQuantity();
		
		super.OnEndServer(action_data);
		
		PlayerBase operator = PlayerBase.Cast(action_data.m_Player);
		if (operator && operator.GetTerjeSkills() && blood_obtained > 0)
		{
			int skillIncrement = GetTerjeSettingInt(TerjeSettingsCollection.MEDICINE_MEDICINE_GIVE_BLOOD_EXP_GAIN);
			if (skillIncrement > 0)
			{
				float XP_obtained = skillIncrement * blood_obtained / action_data_b.m_MainItem.GetQuantityMax();
				operator.GetTerjeSkills().AddSkillExperience("med", (int)XP_obtained) ;
			}
		}
	}
}