modded class RightArea
{
	protected ref TerjeSkillsContainer m_terjeSkillsContainer = null;
	
	override void Refresh()
	{
		super.Refresh();
		
		if (m_terjeSkillsContainer != null)
		{
			m_terjeSkillsContainer.Refresh();
		}
	}
	
	override void UpdateInterval()
	{
		super.UpdateInterval();
		
		if (m_terjeSkillsContainer != null)
		{
			m_terjeSkillsContainer.UpdateInterval();
		}
		else if (m_terjeSkillsContainer == null && GetTerjeSkillsRegistry().IsReadyToDisplay())
		{
			int settingKey;
			bool settingValue;
			array<ref TerjeSkillCfg> registeredSkills();
			GetTerjeSkillsRegistry().GetSkills(registeredSkills);
			int registeredSkillsCount = registeredSkills.Count();

			// Count hidden skills
			foreach (ref TerjeSkillCfg skill : registeredSkills)
			{
				if (TerjeSettingsCollection.SKILLS_HIDDEN_SKILLS.Find(skill.GetId(), settingKey) && GetTerjeSettingBool(settingKey, settingValue) && settingValue)
				{
					registeredSkillsCount--;
				}
			}

			PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
			if (player)
			{
				m_terjeSkillsContainer = new TerjeSkillsContainer(this);
				m_terjeSkillsContainer.InitializeSkills(player);
				
				// If no skills to show, return
				if (registeredSkillsCount <= 0)
					m_terjeSkillsContainer.GetMainWidget().Show(false);
				m_Body.Insert( m_terjeSkillsContainer );
				RecomputeOpenedContainers();
			}
		}
	}
}