modded class ActionPlantSeed
{
	override void OnExecuteServer(ActionData action_data)
	{
		GardenBase gardenBase = GardenBase.Cast(action_data.m_Target.GetObject());
		if (gardenBase)
		{
			gardenBase.TerjeSetLastPlantingPlayer(action_data.m_Player);
		}
		
		super.OnExecuteServer(action_data);
		TerjeGrantPlantingExperience(action_data);
	}
	
	protected void TerjeGrantPlantingExperience(ActionData action_data)
	{
		if (!action_data.m_Player || !action_data.m_Player.GetTerjeSkills())
		{
			return;
		}
		
		int expGain = GetTerjeSettingInt(TerjeSettingsCollection.SKILLS_FARMING_SEED_PLANTED_EXP_GAIN);
		if (expGain > 0)
		{
			GardenBase gardenBase = GardenBase.Cast(action_data.m_Target.GetObject());
			if (gardenBase)
			{
				array<string> selections = new array<string>();
				gardenBase.GetActionComponentNameList(action_data.m_Target.GetComponentIndex(), selections);
				
				foreach (string selection : selections)
				{
					Slot slot = gardenBase.GetSlotBySelection(selection);
					if (slot)
					{
						slot.SetPlayer(action_data.m_Player);
						break;
					}
				}
			}
			action_data.m_Player.GetTerjeSkills().AddSkillExperience("farm", expGain);
		}
	}
}
