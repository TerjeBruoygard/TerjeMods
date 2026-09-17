modded class ItemBase
{
	private int m_terjeClientIndex;
	private int m_terjeLiquidType;
	private int m_terjeDbgLocalId = 0;
	
	override void InitItemVariables()
	{
		super.InitItemVariables();
		if (IsLiquidContainer() && GetQuantity() > 0)
		{
			m_terjeLiquidType = GetTerjeCustomLiquidTypeInit();
			if (m_terjeLiquidType > 0)
			{
				m_VarLiquidType = LIQUID_TERJE_CUSTOM;
			}
		}
		
		RegisterNetSyncVariableInt("m_terjeLiquidType");
	}
	
	override void EEInit()
	{
		super.EEInit();
		
		if (g_Game.IsClient())
		{
			if (IsTerjeClientUpdateRequired())
			{
				m_terjeClientIndex = GetTerjeClientItemsCore().RegisterItem(this);
			}
		}
	}
	
	override void EEDelete(EntityAI parent)
	{
		super.EEDelete(parent);
		
		if (g_Game.IsClient())
		{
			if (IsTerjeClientUpdateRequired())
			{
				GetTerjeClientItemsCore().UnregisterItem(m_terjeClientIndex);
			}
		}
	}
	
	// Calls every second on the client side only when IsTerjeClientUpdateRequired() is true
	void OnTerjeClientUpdate(float deltaTime)
	{
	
	}
	
	bool IsTerjeClientUpdateRequired()
	{
		return false;
	}
	
	bool IsDisinfected()
	{
#ifdef DAYZ_1_29
		return m_Cleanness > m_CleannessMin && m_Cleanness <= m_CleannessMax;
#else
		ItemBaseType itemBaseType = ItemBaseType.Cast(GetEntityType());
		if (!itemBaseType)
			return false;
		
		return m_Cleanness > itemBaseType.m_CleannessMin && m_Cleanness <= itemBaseType.m_CleannessMax;
#endif
	}
	
	bool AddTerjeRadiation(float rAmount)
	{
		// Universal interface to insert radiation agents into the item.
		// Implemented in TerjeRadiation mod.
		return false;
	}
	
	float GetTerjeRadiation()
	{
		// Universal interface to get radiation agents from the item.
		// Implemented in TerjeRadiation mod.
		return 0;
	}
	
	bool IsTerjeRadiationAccumulated()
	{
		// Can item accumulate radiation inside
		return false;
	}
	
	float GetTerjeRadiationInventoryIsolation()
	{
		// Value from 0 to 1
		// Determines what percentage of radiation will be isolated when transfering to/from inventory.
		return 0;
	}
	
	void SetTerjeLiquidClassname(string terjeLiquidClassName, bool allow_client = false)
	{
		SetTerjeLiquidType(TerjeCustomLiquids.GetInstance().GetLiquidIndexByType(terjeLiquidClassName), allow_client);
	}
	
	void SetTerjeLiquidType(int terjeLiquidType, bool allow_client = false)
	{
		if (!IsServerCheck(allow_client))
			return;
		
		if (GetLiquidType() != LIQUID_TERJE_CUSTOM)
		{
			SetLiquidType(LIQUID_TERJE_CUSTOM, allow_client);
		}

		int oldLiquidType = m_terjeLiquidType;
		m_terjeLiquidType = terjeLiquidType;
		if (oldLiquidType != terjeLiquidType)
		{
			OnTerjeLiquidTypeChanged(oldLiquidType, terjeLiquidType);
		}
		
		SetSynchDirty();
	}
	
	override int GetLiquidTypeInit()
	{
		if (GetTerjeCustomLiquidTypeInit() > 0)
		{
			return LIQUID_TERJE_CUSTOM;
		}
		
		return super.GetLiquidTypeInit();
	}
	
	int GetTerjeCustomLiquidTypeInit()
	{
		return TerjeCustomLiquids.GetInstance().GetLiquidIndexByType(GetTerjeGameConfig().ConfigGetString("CfgVehicles " + GetType() + " varTerjeCustomLiquidTypeInit"));
	}
	
	int GetTerjeLiquidType()
	{
		if (GetLiquidType() == LIQUID_TERJE_CUSTOM)
		{
			return m_terjeLiquidType;
		}
		else
		{
			return 0;
		}
	}
	
	string GetTerjeLiquidClassname()
	{
		return TerjeCustomLiquids.GetInstance().GetLiquidClassname(GetTerjeLiquidType());
	}
	
	override void SetLiquidType(int value, bool allow_client = false)
	{
		int old = m_VarLiquidType;
		super.SetLiquidType(value, allow_client);
		
		if (value != LIQUID_TERJE_CUSTOM && old == LIQUID_TERJE_CUSTOM)
		{
			m_terjeLiquidType = 0; // Reset
		}
	}
	
	override float GetTemperatureFreezeThreshold()
	{
		if (IsLiquidContainer())
		{
			if (GetTerjeLiquidType() > 0)
			{
				return TerjeCustomLiquids.GetInstance().GetFreezeThreshold(GetTerjeLiquidType());
			}
			
			if ((GetLiquidType() != LIQUID_NONE) && (Liquid.GetLiquidClassname(GetLiquidType()) == string.Empty))
			{
				return 0; // Prevent vanilla error, return default value
			}
		}
		
		return super.GetTemperatureFreezeThreshold();
	}
	
	override float GetTemperatureThawThreshold()
	{
		if (IsLiquidContainer())
		{
			if (GetTerjeLiquidType() > 0)
			{
				return TerjeCustomLiquids.GetInstance().GetThawThreshold(GetTerjeLiquidType());
			}
			
			if ((GetLiquidType() != LIQUID_NONE) && (Liquid.GetLiquidClassname(GetLiquidType()) == string.Empty))
			{
				return 0; // Prevent vanilla error, return default value
			}
		}
		
		return super.GetTemperatureThawThreshold();
	}
	
	override float GetItemOverheatThreshold()
	{
		if (IsLiquidContainer())
		{
			if (GetTerjeLiquidType() > 0)
			{
				return TerjeCustomLiquids.GetInstance().GetBoilThreshold(GetTerjeLiquidType());
			}
			
			if ((GetLiquidType() != LIQUID_NONE) && (Liquid.GetLiquidClassname(GetLiquidType()) == string.Empty))
			{
				return 100; // Prevent vanilla error, return default value
			}
		}
		
		return super.GetItemOverheatThreshold();
	}
	
	ItemBase GetTerjeProtectionElement(string protectionType)
	{
		if (!g_Game || IsDamageDestroyed() || (HasQuantity() && GetQuantity() <= 0))
		{
			return null;
		}
		
		MaskBase mask = MaskBase.Cast(this);
		if (mask)
		{
			if (!mask.HasValidFilter())
			{
				return null;
			}
			
			ItemBase filter = ItemBase.Cast(mask.GetExternalFilter());
			if (filter)
			{
				return filter;
			}
		}
		
		return this;
	}
	
	float GetTerjeProtectionLevel(string protectionType)
	{
		ItemBase item = GetTerjeProtectionElement(protectionType);
		if (item)
		{
			return GetTerjeGameConfig().ConfigGetFloat("CfgVehicles " + item.GetType() + " Protection " + protectionType);
		}
		
		return 0;
	}
	
	float GetTerjeProtectionAdvanced(string protectionType, float power)
	{
		ItemBase item = GetTerjeProtectionElement(protectionType);
		if (item)
		{
			string configPath = "CfgVehicles " + item.GetType() + " Protection " + protectionType;
			if (GetTerjeGameConfig().ConfigIsExisting(configPath + "Values") && GetTerjeGameConfig().ConfigIsExisting(configPath + "Thresholds"))
			{
				array<float> protectionValues();
				GetTerjeGameConfig().ConfigGetFloatArray(configPath + "Values", protectionValues);
				
				array<float> protectionThresholds();
				GetTerjeGameConfig().ConfigGetFloatArray(configPath + "Thresholds", protectionThresholds);
				
				for (int i = 0; i < protectionThresholds.Count(); i++)
				{
					if (power < protectionThresholds.Get(i))
					{
						return protectionValues.Get(i);
					}
				}
				
				return 0;
			}
			else
			{
				return GetTerjeGameConfig().ConfigGetFloat(configPath);
			}
		}
		
		return 0;
	}
	
	protected void OnTerjeLiquidTypeChanged(int oldType, int newType)
	{
	
	}
	
	InventoryLocationType GetTerjeCurrentInventoryLocationType()
	{
		InventoryLocation il = new InventoryLocation();
		GetInventory().GetCurrentInventoryLocation( il );
		return il.GetType();
	}
	
	void ApplyTerjeConsumableEffects(PlayerBase player, float amount)
	{
		if (g_Game.IsDedicatedServer())
		{
			TerjeConsumableEffects medEffects = new TerjeConsumableEffects();
			if (IsLiquidContainer())
			{
				int liquid_type = GetLiquidType();
				if (liquid_type == LIQUID_TERJE_CUSTOM)
				{
					string customLiquidClassName = GetTerjeLiquidClassname();
					medEffects.Apply(null, "CfgTerjeCustomLiquids " + customLiquidClassName, player, amount);
				}
				else
				{
					string vanillaLiquidClassName = Liquid.GetLiquidClassname(liquid_type);
					medEffects.Apply(null, "CfgLiquidDefinitions " + vanillaLiquidClassName, player, amount);
				}
			}
			else
			{
				medEffects.Apply(this, "CfgVehicles " + GetType(), player, amount);
			}
		}
	}
	
	// 0 - Do not override
	// 1 - Override with consumable effect
	// 2 - Override with default description + consumable effect
	int TerjeOverrideDescriptionByConsumableEffects()
	{
		return 0;
	}
	
	override bool DescriptionOverride(out string output)
	{
		int overrideType = TerjeOverrideDescriptionByConsumableEffects();
		if (overrideType > 0)
		{
			if (overrideType == 2)
			{
				output = ConfigGetString("descriptionShort") + "<br/>";
			}
			else
			{
				output = "";
			}
			
			TerjeConsumableEffects medEffects = new TerjeConsumableEffects;
			if (IsLiquidContainer())
			{
				int liquid_type = GetLiquidType();
				string liquidClassName = Liquid.GetLiquidClassname(liquid_type);
				output += medEffects.Describe(null, "CfgLiquidDefinitions " + liquidClassName);
			}
			else
			{
				output += medEffects.Describe(this, "CfgVehicles " + GetType());
			}
			
			return true;
		}
		
		return super.DescriptionOverride(output);
	}
	
	void OnTerjeStoreSave(TerjeStorageWritingContext ctx)
	{
		string terjeLiquidClassname = GetTerjeLiquidClassname();
		if (terjeLiquidClassname != "")
		{
			ctx.WriteString("liquid", terjeLiquidClassname);
		}
	}
	
	void OnTerjeStoreLoad(TerjeStorageReadingContext ctx)
	{
		string terjeLiquidClassname;
		if (ctx.ReadString("liquid", terjeLiquidClassname))
		{
			m_terjeLiquidType = TerjeCustomLiquids.GetInstance().GetLiquidIndexByType(terjeLiquidClassname);
		}
		else
		{
			m_terjeLiquidType = 0;
		}
	}
	
	override void OnStoreSave(ParamsWriteContext ctx)
	{
		TerjeStorageHelpers.SetActualTerjeStorageVersion();
		if (TerjeStorageHelpers.GetTerjeStorageVersion() == 1)
		{
			TerjeStorageWritingContext terjeStorageCtx();
			OnTerjeStoreSave(terjeStorageCtx);
			terjeStorageCtx.OnStoreSave(ctx);
		}
		
		super.OnStoreSave(ctx);
	}
	
	override bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
		int terjeStorageVersion = TerjeStorageHelpers.GetTerjeStorageVersion();
		if (terjeStorageVersion == 1)
		{
			TerjeStorageReadingContext terjeStorageCtx();
			if (!terjeStorageCtx.OnStoreLoad(ctx))
			{
				return false;
			}
			
			OnTerjeStoreLoad(terjeStorageCtx);
		}
		
		return super.OnStoreLoad(ctx, version);
	}
	
	override void AfterStoreLoad()
	{	
		super.AfterStoreLoad();
		
		if (m_terjeLiquidType > 0)
		{
			SetTerjeLiquidType(m_terjeLiquidType);
		}
	}

	
	bool IsTerjeWholeFish()
	{
		return GetTerjeGameConfig().ConfigGetBool("CfgVehicles " + GetType() + " wholeFish");
	}
	
	override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
	{
		super.OnRPC(sender, rpc_type, ctx);
		if (rpc_type == TerjeERPC.TerjeRPC_CUSTOM_CALL)
		{
			Param1<string> metaData;
			if (!ctx.Read(metaData))
			{
				return;
			}
			
			OnTerjeRPC(sender, metaData.param1, ctx);
		}
	}
	
	void OnTerjeRPC(PlayerIdentity sender, string id, ParamsReadContext ctx)
	{
		
	}
	
	void TerjeSendToClient(string id, PlayerIdentity recipient, Param params)
	{
		if (g_Game && g_Game.IsDedicatedServer())
		{
			array<ref Param> sendData();
			sendData.Insert(new Param1<string>(id));
			if (params != null)
			{
				sendData.Insert(params);
			}
			
			this.RPC(TerjeERPC.TerjeRPC_CUSTOM_CALL, sendData, true, recipient);
		}
	}
	
	void TerjeStreamToClient(string id, PlayerIdentity recipient, out TerjeStreamRpc stream)
	{
		if (g_Game && g_Game.IsDedicatedServer())
		{
			stream = new TerjeStreamRpc();
			stream.InitTerjeRpcEx(id, recipient, TerjeStreamRpc_Target.TO_CLIENT, this, (int)TerjeERPC.TerjeRPC_CUSTOM_CALL);
		}
	}
		
	void TerjeSendToServer(string id, Param params)
	{
		if (g_Game && g_Game.IsClient())
		{
			array<ref Param> sendData();
			sendData.Insert(new Param1<string>(id));
			if (params != null)
			{
				sendData.Insert(params);
			}
			
			this.RPC(TerjeERPC.TerjeRPC_CUSTOM_CALL, sendData, true, null);
		}
	}
	
	void TerjeStreamToServer(string id, out TerjeStreamRpc stream)
	{
		if (g_Game && g_Game.IsClient())
		{
			stream = new TerjeStreamRpc();
			stream.InitTerjeRpcEx(id, null, TerjeStreamRpc_Target.TO_SERVER, this, (int)TerjeERPC.TerjeRPC_CUSTOM_CALL);
		}
	}
	
	void TerjeSendToAll(string id, Param params)
	{
		if (g_Game && g_Game.IsDedicatedServer())
		{
			array<ref Param> sendData();
			sendData.Insert(new Param1<string>(id));
			if (params != null)
			{
				sendData.Insert(params);
			}
			
			this.RPC(TerjeERPC.TerjeRPC_CUSTOM_CALL, sendData, true, null);
		}
	}
	
	void TerjeStreamToAll(string id, out TerjeStreamRpc stream)
	{
		if (g_Game && g_Game.IsDedicatedServer())
		{
			stream = new TerjeStreamRpc();
			stream.InitTerjeRpcEx(id, null, TerjeStreamRpc_Target.TO_ALL, this, (int)TerjeERPC.TerjeRPC_CUSTOM_CALL);
		}
	}
}
