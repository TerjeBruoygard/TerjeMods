modded class ActionDigGardenPlotCB
{
	override void CreateActionComponent()
	{
		super.CreateActionComponent();
		
		float timeMult = 1.0;
		if (!GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_FARMING_OVERRIDE_DIG_TIME_MULT, timeMult) || timeMult <= 0)
		{
			timeMult = 1.0;
		}
		
		float quickDiggerValue;
		if (m_ActionData.m_Player && m_ActionData.m_Player.GetTerjeSkills() && m_ActionData.m_Player.GetTerjeSkills().GetPerkValue("farm", "quickdig", quickDiggerValue))
		{
			timeMult = timeMult * Math.Clamp(1.0 + quickDiggerValue, 0.15, 1.0);
		}
		
		m_ActionData.m_ActionComponent = new CAContinuousTime(UATimeSpent.DIG_GARDEN * timeMult);
	}
}

modded class ActionDigGardenPlot
{
	override void OnFinishProgressServer(ActionData action_data)
	{
		float toolHealthBefore = 0;
		bool trackDamage = action_data.m_MainItem != null;
		if (trackDamage)
		{
			toolHealthBefore = action_data.m_MainItem.GetHealth("", "Health");
		}
		
		super.OnFinishProgressServer(action_data);
		
		if (trackDamage)
		{
			TerjeAdjustDigToolDamage(action_data, toolHealthBefore);
		}
		
		TerjeGrantDigExperience(action_data);
	}
	
	protected void TerjeAdjustDigToolDamage(ActionData action_data, float toolHealthBefore)
	{
		float actualSpent = toolHealthBefore - action_data.m_MainItem.GetHealth("", "Health");
		float desiredDamage = GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_FARMING_OVERRIDE_TILL_DAMAGE);
		
		float quickDiggerValue;
		if (action_data.m_Player && action_data.m_Player.GetTerjeSkills() && action_data.m_Player.GetTerjeSkills().GetPerkValue("farm", "quickdig", quickDiggerValue))
		{
			desiredDamage = desiredDamage * Math.Clamp(1.0 + quickDiggerValue, 0.15, 1.0);
		}
		
		float adjustment = actualSpent - desiredDamage;
		if (adjustment != 0)
		{
			action_data.m_MainItem.AddHealth("", "Health", adjustment);
		}
	}
	
	protected void TerjeGrantDigExperience(ActionData action_data)
	{
		if (!action_data.m_Player || !action_data.m_Player.GetTerjeSkills())
		{
			return;
		}
		
		int expGain = GetTerjeSettingInt(TerjeSettingsCollection.SKILLS_FARMING_GARDEN_PLOT_EXP_GAIN);
		if (expGain > 0)
		{
			action_data.m_Player.GetTerjeSkills().AddSkillExperience("farm", expGain);
		}
	}
}

modded class ActionCreateGreenhouseGardenPlotCB
{
	override void CreateActionComponent()
	{
		super.CreateActionComponent();
		
		float timeMult = 1.0;
		if (!GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_FARMING_OVERRIDE_DIG_TIME_MULT, timeMult) || timeMult <= 0)
		{
			timeMult = 1.0;
		}
		
		float quickDiggerValue;
		if (m_ActionData.m_Player && m_ActionData.m_Player.GetTerjeSkills() && m_ActionData.m_Player.GetTerjeSkills().GetPerkValue("farm", "quickdig", quickDiggerValue))
		{
			timeMult = timeMult * Math.Clamp(1.0 + quickDiggerValue, 0.15, 1.0);
		}
		
		m_ActionData.m_ActionComponent = new CAContinuousTime(UATimeSpent.DIG_GARDEN * timeMult);
	}
}

modded class ActionCreateGreenhouseGardenPlot
{
	override void OnFinishProgressServer(ActionData action_data)
	{
		float toolHealthBefore = 0;
		bool trackDamage = action_data.m_MainItem != null;
		if (trackDamage)
		{
			toolHealthBefore = action_data.m_MainItem.GetHealth("", "Health");
		}
		
		super.OnFinishProgressServer(action_data);
		
		if (trackDamage)
		{
			float actualSpent = toolHealthBefore - action_data.m_MainItem.GetHealth("", "Health");
			float desiredDamage = GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_FARMING_OVERRIDE_TILL_DAMAGE);
			
			float quickDiggerValue;
			if (action_data.m_Player && action_data.m_Player.GetTerjeSkills() && action_data.m_Player.GetTerjeSkills().GetPerkValue("farm", "quickdig", quickDiggerValue))
			{
				desiredDamage = desiredDamage * Math.Clamp(1.0 + quickDiggerValue, 0.15, 1.0);
			}
			
			float adjustment = actualSpent - desiredDamage;
			if (adjustment != 0)
			{
				action_data.m_MainItem.AddHealth("", "Health", adjustment);
			}
		}
		
		if (!action_data.m_Player || !action_data.m_Player.GetTerjeSkills())
		{
			return;
		}
		
		int expGain = GetTerjeSettingInt(TerjeSettingsCollection.SKILLS_FARMING_GARDEN_PLOT_EXP_GAIN);
		if (expGain > 0)
		{
			action_data.m_Player.GetTerjeSkills().AddSkillExperience("farm", expGain);
		}
	}
}

