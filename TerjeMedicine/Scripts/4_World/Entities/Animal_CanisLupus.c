modded class Animal_CanisLupus
{
	private bool m_HasTerjeRabies;
	
	override bool HasTerjeRabies()
	{
		return m_HasTerjeRabies;
	}
	
	override void EEInit()
	{
		super.EEInit();
		
		if (g_Game.IsDedicatedServer())
		{
			m_HasTerjeRabies = TerjeEvent(GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_RABIES_WOLF_INFECTED_CHANCE));
		}
	}
}
