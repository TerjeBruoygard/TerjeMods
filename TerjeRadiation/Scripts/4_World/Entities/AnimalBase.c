modded class AnimalBase
{
	private float m_terjeRadiationUpdate = 0;
	private float m_terjeRadiationServer = 0;
	private int m_terjeRadiationSynch = 0;
	
	void AnimalBase()
	{
		RegisterNetSyncVariableInt("m_terjeRadiationSynch", 0, TerjeRadiationConstants.RADIATION_ANIMALS_ACCUMULATOR_SYNCH_MAX);
	}
	
	override bool AddTerjeRadiation(float rAmount)
	{
		if (g_Game.IsDedicatedServer() && IsTerjeRadiationAccumulated())
		{
			if (ConfigIsExisting("terjeStaticRadiationValue"))
			{
				return false; // Disable radiation increment/decrement for items with a static radiation value.
			}
			
			m_terjeRadiationServer = Math.Clamp(m_terjeRadiationServer + rAmount, 0, TerjeRadiationConstants.RADIATION_ANIMALS_ACCUMULATOR_SERVER_MAX);
			
			int newRadiationSynchValue = (int)Math.Round(m_terjeRadiationServer / TerjeRadiationConstants.RADIATION_ANIMALS_ACCUMULATOR_SYNCH_DIVIDER);
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
			return m_terjeRadiationSynch * TerjeRadiationConstants.RADIATION_ANIMALS_ACCUMULATOR_SYNCH_DIVIDER;
		}
	}
	
	override bool IsTerjeRadiationAccumulated()
	{
		return GetTerjeSettingBool(TerjeSettingsCollection.RADIATION_DO_ANIMALS_ACCUMULATE);
	}
	
	override void CommandHandler(float dt, int currentCommandID, bool currentCommandFinished)
	{
		super.CommandHandler(dt, currentCommandID, currentCommandFinished);
		
		if (g_Game.IsDedicatedServer())
		{
			TerjeRadiationUpdate(dt);
		}
	}

	void TerjeRadiationUpdate(float dt)
	{
		m_terjeRadiationUpdate += dt;
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
		
		if (m_terjeRadiationServer > TerjeRadiationConstants.RADIATION_ANIMALS_DAMAGE_THRESHOLD && GetTerjeSettingBool(TerjeSettingsCollection.RADIATION_DAMAGE_ANIMALS))
		{
			DecreaseHealth("", "", TerjeRadiationConstants.RADIATION_ANIMALS_DAMAGE_PER_SEC * dt);
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
		
		int newRadiationSynchValue = (int)Math.Round(m_terjeRadiationServer / TerjeRadiationConstants.RADIATION_ANIMALS_ACCUMULATOR_SYNCH_DIVIDER);
		if (newRadiationSynchValue != m_terjeRadiationSynch)
		{
			m_terjeRadiationSynch = newRadiationSynchValue;
			SetSynchDirty();
		}
	}
}