class TerjeStartScreenContextFace : TerjeStartScreenContextBase
{
	ref TerjeXmlObject m_inputFacesXml = new TerjeXmlObject;
	ref TerjeXmlObject m_selectedFaceXml = new TerjeXmlObject;
	
	override string GetPageName()
	{
		return "face";
	}
	
	override bool Serialize(Serializer ctx)
	{
		if (!super.Serialize(ctx))
			return false;
		
		if (!m_inputFacesXml.Binarize(ctx))
			return false;
		
		if (!m_selectedFaceXml.Binarize(ctx))
			return false;
		
		return true;
	}
	
	override bool Deserialize(Serializer ctx)
	{
		if (!super.Deserialize(ctx))
			return false;
		
		if (!m_inputFacesXml.Unbinarize(ctx))
			return false;
		
		if (!m_selectedFaceXml.Unbinarize(ctx))
			return false;
		
		return true;
	}
	
	override void Build(PlayerBase player)
	{
		super.Build(player);
		
		GetPluginTerjeStartScreen().BuildFacesForPlayer(player, m_inputFacesXml);
	}
	
	override void Apply(PlayerBase player)
	{
		super.Apply(player);
		
		string classname;
		if (!m_selectedFaceXml.FindAttribute("classname", classname))
		{
			return;
		}

		string beardEnabledRaw = "false";
		string beardDefaultRaw = "0";
		string beardMaxRaw = "3";
		string beardSelectedRaw = string.Empty;
		m_selectedFaceXml.FindAttribute("$beardEnabled", beardEnabledRaw);
		m_selectedFaceXml.FindAttribute("$beardDefault", beardDefaultRaw);
		m_selectedFaceXml.FindAttribute("$beardMax", beardMaxRaw);
		m_selectedFaceXml.FindAttribute("beardSelected", beardSelectedRaw);
		
		TerjeXmlObject conditionsXml = m_selectedFaceXml.GetChildByNodeName("Conditions");
		if (conditionsXml != null)
		{
			TerjePlayerConditions playerConds = TerjePlayerConditions.GetInstance();
			for (int condId = 0; condId < conditionsXml.GetChildrenCount(); condId++)
			{
				TerjeXmlObject condXml = conditionsXml.GetChild(condId);
				if (condXml != null && condXml.IsObjectNode())
				{
					playerConds.ApplyCondition(player, condXml);
				}
			}
		}
		
		if (player && player.GetTerjeProfile() != null)
		{
			player.GetTerjeProfile().SetCharacterClassname(classname);

			int beardSelected = TerjeMathHelper.ClampInt(beardDefaultRaw.ToInt(), 0, 3);
			if (beardSelectedRaw != string.Empty) beardSelected = TerjeMathHelper.ClampInt(beardSelectedRaw.ToInt(), 0, 3);

			int beardMax = TerjeMathHelper.ClampInt(beardMaxRaw.ToInt(), 0, 3);
			if (beardSelected > beardMax) beardSelected = beardMax;

			if (beardEnabledRaw.ToInt() == 1)
			{
				player.GetTerjeProfile().SetPersistentBeardLevelSelected(beardSelected);
				player.GetTerjeProfile().SetPersistentBeardLevelDeath(-1);
			}
			else
			{
				player.GetTerjeProfile().SetPersistentBeardLevelSelected(0);
				player.GetTerjeProfile().SetPersistentBeardLevelDeath(-1);
			}

			player.m_terjeStartScreenParams = null;
			player.SetTerjeServerStartScreenImmunity(false);
			player.SetTerjeMaintenanceMode(true);
			player.SetHealth("", "", 0);
		}
	}
}