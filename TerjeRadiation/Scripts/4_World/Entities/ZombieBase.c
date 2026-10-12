modded class ZombieBase
{
	private float m_terjeRadiationUpdate = 0;
	private float m_terjeRadiationServer = 0;
	private int m_terjeRadiationSynch = 0;
	
	void ZombieBase()
	{
		RegisterNetSyncVariableInt("m_terjeRadiationSynch", 0, TerjeRadiationConstants.RADIATION_ZOMBIE_ACCUMULATOR_SYNCH_MAX);
	}
	
	override bool AddTerjeRadiation(float rAmount)
	{
		if (g_Game.IsDedicatedServer() && IsTerjeRadiationAccumulated())
		{
			if (ConfigIsExisting("terjeStaticRadiationValue"))
			{
				return false; // Disable radiation increment/decrement for items with a static radiation value.
			}
			
			m_terjeRadiationServer = Math.Clamp(m_terjeRadiationServer + rAmount, 0, TerjeRadiationConstants.RADIATION_ZOMBIE_ACCUMULATOR_SERVER_MAX);
			
			int newRadiationSynchValue = (int)Math.Round(m_terjeRadiationServer / TerjeRadiationConstants.RADIATION_ZOMBIE_ACCUMULATOR_SYNCH_DIVIDER);
			if (newRadiationSynchValue != m_terjeRadiationSynch)
			{
				m_terjeRadiationSynch = newRadiationSynchValue;
				SetSynchDirty();
			}
			
			return true;
		}

		return false;
	}
	
	override float GetTerjeRadiation()
	{
		if (GetTerjeGameConfig().ConfigIsExisting("CfgVehicles " + GetType() + " terjeStaticRadiationValue"))
		{
			return GetTerjeGameConfig().ConfigGetFloat("CfgVehicles " + GetType() + " terjeStaticRadiationValue");
		}
		
		if (g_Game.IsDedicatedServer())
		{
			return m_terjeRadiationServer;
		}
		else
		{
			return m_terjeRadiationSynch * TerjeRadiationConstants.RADIATION_ZOMBIE_ACCUMULATOR_SYNCH_DIVIDER;
		}
	}
	
	override bool IsTerjeRadiationAccumulated()
	{
		return GetTerjeSettingBool(TerjeSettingsCollection.RADIATION_DO_ZOMBIES_ACCUMULATE);
	}
	
	override void CommandHandler(float pDt, int pCurrentCommandID, bool pCurrentCommandFinished)
	{
		super.CommandHandler(pDt, pCurrentCommandID, pCurrentCommandFinished);
		
		if (g_Game.IsDedicatedServer())
		{
			TerjeRadiationUpdate(pDt);
		}
	}
	
	void TerjeRadiationUpdate(float pDt)
	{
		m_terjeRadiationUpdate += pDt;
		if (m_terjeRadiationUpdate > 30)
		{
			PluginTerjeScriptableAreas plugin = GetTerjeScriptableAreas();
			if (plugin)
			{
				float currentRadiation = GetTerjeRadiation();
				float radioactiveGlobalModifier = GetTerjeSettingFloat(TerjeSettingsCollection.RADIATION_AREAS_POWER_MOD);
				float rAmount = plugin.CalculateTerjeEffectValue(this, "rad") * radioactiveGlobalModifier;
				rAmount -= GetTerjeSettingFloat(TerjeSettingsCollection.RADIATION_ITEM_LOSE_PER_SEC);
				
				if (rAmount > 0)
				{
					float maxAccumulatedRadLimit = rAmount * GetTerjeSettingFloat(TerjeSettingsCollection.RADIATION_ZONE_POWER_TO_RAD_LIMIT);
					if (currentRadiation < maxAccumulatedRadLimit)
					{
						AddTerjeRadiation(Math.Clamp(rAmount * m_terjeRadiationUpdate, 0, maxAccumulatedRadLimit - currentRadiation));
					}
				}
				else
				{
					AddTerjeRadiation(rAmount * m_terjeRadiationUpdate);
				}
			}
			
			m_terjeRadiationUpdate = 0;
		}
		
		if (m_terjeRadiationServer > TerjeRadiationConstants.RADIATION_ZOMBIE_DAMAGE_THRESHOLD && GetTerjeSettingBool(TerjeSettingsCollection.RADIATION_DAMAGE_ZOMBIES))
		{
			DecreaseHealth("", "", TerjeRadiationConstants.RADIATION_ZOMBIE_DAMAGE_PER_SEC * pDt);
		}
	}
	override void OnTerjeStoreSave(TerjeStorageWritingContext ctx)
	{
		super.OnTerjeStoreSave(ctx);
		ctx.WriteFloat("rad", m_terjeRadiationServer);
	}
	
	override void OnTerjeStoreLoad(TerjeStorageReadingContext ctx)
	{
		super.OnTerjeStoreLoad(ctx);
		ctx.ReadFloat("rad", m_terjeRadiationServer);
	}
	
	override void AfterStoreLoad()
	{	
		super.AfterStoreLoad();
		
		int newRadiationSynchValue = (int)Math.Round(m_terjeRadiationServer / TerjeRadiationConstants.RADIATION_ZOMBIE_ACCUMULATOR_SYNCH_DIVIDER);
		if (newRadiationSynchValue != m_terjeRadiationSynch)
		{
			m_terjeRadiationSynch = newRadiationSynchValue;
			SetSynchDirty();
		}
	}
}