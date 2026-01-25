class TerjeSkillsContainer : CollapsibleContainer
{
	void TerjeSkillsContainer( LayoutHolder parent, int sort = -1 )
	{
		m_CollapsibleHeader.SetName( "#STR_TERJESKILL_HEADER" );
	}
	
	void InitializeSkills(PlayerBase player)
	{
		
		int settingKey;
		bool settingValue;
		array<ref TerjeSkillCfg> hiddenSkills();
		GetTerjeSkillsRegistry().GetSkills(hiddenSkills);
		
		// Insert spacer
		Insert(new TerjeSkillBlankSpacer(this));
		
		// Insert skills
		ref array<ref TerjeSkillCfg> skills = new array<ref TerjeSkillCfg>;
		GetTerjeSkillsRegistry().GetSkills(skills);
		foreach (ref TerjeSkillCfg skill : skills)
		{
			TerjeSkillWidget widget = new TerjeSkillWidget(this);
			widget.InitializeSkill(skill, player);
			
			// Check if skill need to be hidden
			if (TerjeSettingsCollection.SKILLS_HIDDEN_SKILLS.Find(skill.GetId(), settingKey) && GetTerjeSettingBool(settingKey, settingValue) && settingValue)
			{
				widget.GetMainWidget().Show(false);
			}
			Insert(widget);
		}
	}
}

class TerjeSkillBlankSpacer : Container
{
	override void SetLayoutName()
	{
		m_LayoutName = "TerjeSkills/Layouts/TerjeBlankLayout.layout";
	}
}