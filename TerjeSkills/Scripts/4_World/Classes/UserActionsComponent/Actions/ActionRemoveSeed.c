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
			PlayerBase player;
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
						player = slot.GetPlayer();
						break;
					}
				}
			}
			if (player) player.GetTerjeSkills().AddSkillExperience("farm", expGain * -1);
		}
	}
}