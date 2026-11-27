modded class AnimalBase
{
	override void EEKilled(Object killer)
	{
		super.EEKilled(killer);
		
		if (GetTerjeSettingBool(TerjeSettingsCollection.STARTSCREEN_SOULS_ENABLED))
		{
			EntityAI killerEntity = EntityAI.Cast(killer);
			if (killerEntity)
			{
				PlayerBase killerPlayer = PlayerBase.Cast(killerEntity);
				if (!killerPlayer)
				{
					killerPlayer = PlayerBase.Cast(killerEntity.GetHierarchyRootPlayer());
				}
				
				if (killerPlayer && killerPlayer.IsAlive() && killerPlayer.GetTerjeSouls() != null)
				{
					int soulsCount = GetTerjeGameConfig().ConfigGetInt("CfgVehicles " + GetType() + " terjeOnKillSoulsCount");
					float soulsChance = GetTerjeGameConfig().ConfigGetFloat("CfgVehicles " + GetType() + " terjeOnKillSoulsChance");
					if (soulsCount == 0)
					{
						soulsCount = GetTerjeSettingInt(TerjeSettingsCollection.STARTSCREEN_SOULS_KILLANI_COUNT);
						soulsChance = GetTerjeSettingFloat(TerjeSettingsCollection.STARTSCREEN_SOULS_KILLANI_CHANCE);
					}
					
					if (TerjeEvent(soulsChance) && soulsCount > 0)
					{
						killerPlayer.GetTerjeSouls().AddCount(soulsCount);
					}
				}
			}
		}
	}
}
