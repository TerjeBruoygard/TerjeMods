class PluginTerjeStartScreen : PluginBase 
{
	private const string SETTINGS_DIR = "$profile:TerjeSettings\\StartScreen";
	private const string NAMES_STORAGE_DIR = "$mission:terje_storage\\names_index";
	
	private ref TerjeXmlObject m_generalXml = new TerjeXmlObject;
	private ref TerjeXmlObject m_facesXml = new TerjeXmlObject;
	private ref TerjeXmlObject m_loadoutsList = new TerjeXmlObject;
	private ref map<string, int> m_loadoutsSearch = new map<string, int>;
	private ref array<int> m_loadoutsOrdered = new array<int>;
	
	private ref TerjeXmlObject m_respawnsList = new TerjeXmlObject;
	private ref map<string, int> m_respawnsSearch = new map<string, int>;
	private ref array<int> m_respawnsOrdered = new array<int>;
	private ref array<string> m_rulesMarkdownContent = new array<string>;
	
	private ref TerjeEntitySpawner m_entitySpawner = new TerjeEntitySpawner;
	
	override void OnInit()
	{
		if (g_Game.IsDedicatedServer())
		{
			MakeDirectory(SETTINGS_DIR);
			MakeDirectory(NAMES_STORAGE_DIR);
			LoadGeneralXml();
			LoadRulesMarkdown();
			LoadFacesList();
			LoadLoadoutsList();
			LoadRespawnsList();
			GetTerjeRPC().RegisterHandler("startscreen.apply", this, "OnTerjeStartScreenContextApply");
			GetTerjeRPC().RegisterHandler("startscreen.name.verify", this, "OnTerjeStartScreenNameVerify");
			GetTerjeRPC().RegisterHandler("startscreen.loadout.equip", this, "OnTerjeStartScreenLoadoutEquip");
			GetTerjeRPC().RegisterHandler("startscreen.overview.del", this, "OnTerjeStartScreenOverviewDel");
		}
	}
	
	string GetGeneralXmlValue(string name, string defaultValue)
	{
		if (m_generalXml != null)
		{
			string attrValue;
			TerjeXmlObject node = m_generalXml.GetChildByNodeName(name);
			
			if ((node != null) && (node.FindAttribute("value", attrValue)))
			{
				return attrValue;
			}
		}
		
		return defaultValue;
	}
	
	void GetRulesMarkdownContent(array<string> result)
	{
		if (result != null)
		{
			result.Clear();
			result.Copy(m_rulesMarkdownContent);
		}
	}
	
	void DeleteCharacterNameIndex(string fullName)
	{
		if (!GetTerjeSettingBool(TerjeSettingsCollection.STARTSCREEN_UNIQ_NAME_CHECKS))
		{
			return;
		}
		
		string path = NAMES_STORAGE_DIR + "\\" + TerjeStringHelper.EncodeToHex(fullName);
		if (FileExist(path))
		{
			DeleteFile(path);
		}
	}
	
	bool HasCharacterWithName(string fullName)
	{
		return FileExist(NAMES_STORAGE_DIR + "\\" + TerjeStringHelper.EncodeToHex(fullName));
	}
	
	bool FindCharacterByName(string fullName, out string steamGUID)
	{
		string path = NAMES_STORAGE_DIR + "\\" + TerjeStringHelper.EncodeToHex(fullName);
		
		steamGUID = string.Empty;
		if (FileExist(path))
		{
			FileHandle file = OpenFile(path, FileMode.READ);
			if (file != 0)
			{
				FGets(file, steamGUID);
				CloseFile(file);
			}
			
			return steamGUID.Length() > 0;
		}
		
		return false;
	}
	
	bool CreateCharacterNameIndex(string fullName, string steamGUID)
	{
		if (!GetTerjeSettingBool(TerjeSettingsCollection.STARTSCREEN_UNIQ_NAME_CHECKS))
		{
			return true;
		}
		
		string path = NAMES_STORAGE_DIR + "\\" + TerjeStringHelper.EncodeToHex(fullName);
		FileHandle file = OpenFile(path, FileMode.WRITE);
		if (file != 0)
		{
			FPrint(file, steamGUID);
			CloseFile(file);
			return true;
		}
		
		return false;
	}
	
	bool DeleteCharacterNameIndex(string fullName, string steamGUID)
	{
		if (!GetTerjeSettingBool(TerjeSettingsCollection.STARTSCREEN_UNIQ_NAME_CHECKS))
		{
			return true;
		}
		
		return DeleteFile(NAMES_STORAGE_DIR + "\\" + TerjeStringHelper.EncodeToHex(fullName));
	}
	
	bool FindCharacterIconByClassname(string classname, out string texturePath)
	{
		TerjeXmlObject faceXml = m_facesXml.GetChildByAttrPair("Face", "classname", classname);
		return (faceXml != null) && (faceXml.FindAttribute("icon", texturePath));
	}
	
	void BuildFacesForPlayer(PlayerBase player, out TerjeXmlObject result)
	{
		bool beardEnabled = GetTerjeSettingBool(TerjeSettingsCollection.STARTSCREEN_PBEARD_ENABLED);
		bool beardSelectable = GetTerjeSettingBool(TerjeSettingsCollection.STARTSCREEN_PBEARD_FACESELECT);

		result = new TerjeXmlObject;
		result.SetName("Faces");
		for (int i = 0; i < m_facesXml.GetChildrenCount(); i++)
		{
			TerjeXmlObject faceXml = m_facesXml.GetChild(i);
			if ((faceXml.GetName() == "Face") && (faceXml.HasAttribute("classname")) && (faceXml.HasAttribute("icon")))
			{
				bool isValid;
				TerjeXmlObject faceCopy = result.CreateChild("");
				faceXml.DeepCopy(faceCopy, true, false);
				
				TerjeXmlObject conditions = faceCopy.GetChildByNodeName("Conditions");
				if (ProcessConditions(player, conditions, isValid))
				{
					string beardAttrValue = string.Empty;
					int faceMask = BuildFaceBeardMask(faceCopy);
					int faceMax = FindLastAllowedBeardLevel(faceMask);
					if (faceMax < 0) faceMax = 0;

					int faceDefault = FindFirstAllowedBeardLevel(faceMask, 3);
					if (faceCopy.FindAttribute("beardDefault", beardAttrValue)) faceDefault = TerjeMathHelper.ClampInt(beardAttrValue.ToInt(), 0, 3);
					if ((faceMask & (1 << faceDefault)) == 0) faceDefault = FindFirstAllowedBeardLevel(faceMask, 3);

					bool faceBeardEnabled = beardEnabled && (faceMask != 0);
					bool faceBeardSelectable = beardSelectable && (faceMask != 0);
					if (faceBeardEnabled) faceCopy.SetAttribute("$beardEnabled", "1");
					else faceCopy.SetAttribute("$beardEnabled", "0");

					if (faceBeardSelectable) faceCopy.SetAttribute("$beardSelectable", "1");
					else faceCopy.SetAttribute("$beardSelectable", "0");
					faceCopy.SetAttribute("$beardMax", faceMax.ToString());
					faceCopy.SetAttribute("$beardMask", faceMask.ToString());
					faceCopy.SetAttribute("$beardDefault", faceDefault.ToString());

					if (isValid)
					{
						faceCopy.SetAttribute("$valid", "1");
					}
					else
					{
						faceCopy.SetAttribute("$valid", "0");
					}
				}
				else
				{
					result.RemoveChild(result.GetChildrenCount() - 1);
				}
			}
		}
	}

	private int FindFirstAllowedBeardLevel(int mask, int maxLevel)
	{
		for (int i = 0; i <= maxLevel; i++)
		{
			if ((mask & (1 << i)) != 0) return i;
		}

		return 0;
	}

	private int FindLastAllowedBeardLevel(int mask)
	{
		for (int i = 3; i >= 0; i--)
		{
			if ((mask & (1 << i)) != 0) return i;
		}

		return -1;
	}

	private int BuildFaceBeardMask(TerjeXmlObject faceXml)
	{
		int resultMask = 0;
		string beardLevelsRaw = string.Empty;
		if (faceXml == null) return resultMask;

		if (faceXml.FindAttribute("beardLevels", beardLevelsRaw))
		{
			array<string> rawLevels = new array<string>;
			beardLevelsRaw.Split(",", rawLevels);
			for (int ii = 0; ii < rawLevels.Count(); ii++)
			{
				int level = TerjeMathHelper.ClampInt(rawLevels.Get(ii).ToInt(), 0, 3);
				resultMask = resultMask | (1 << level);
			}
		}

		return resultMask;
	}
	
	void BuildLoadoutsForPlayer(PlayerBase player, out TerjeXmlObject result)
	{
		if (!player || player.GetTerjeProfile() == null)
		{
			return;
		}
		
		string lastLoadoutId;
		string lastLoadoutSelections;
		player.GetTerjeProfile().GetLastLoadout(lastLoadoutId, lastLoadoutSelections);
		
		result = new TerjeXmlObject;
		result.SetName("Loadouts");
		
		bool defaultSelectionSet = false;
		foreach (int searchId : m_loadoutsOrdered)
		{
			TerjeXmlObject loadoutCopy = null;
			TerjeXmlObject loadoutRoot = m_loadoutsList.GetChild(searchId);
			if (ValidateLoadoutNode(loadoutRoot))
			{
				bool isValid;
				string loadoutId;
				loadoutCopy = result.CreateChild("");
				loadoutRoot.DeepCopy(loadoutCopy, true, false);
				loadoutCopy.FindAttribute("id", loadoutId);
				if (ProcessConditions(player, loadoutCopy.GetChildByNodeName("Conditions"), isValid))
				{
					if (isValid)
					{
						loadoutCopy.SetAttribute("$valid", "1");
					}
					else
					{
						loadoutCopy.SetAttribute("$valid", "0");
					}
					
					if (!defaultSelectionSet && (lastLoadoutId == loadoutId))
					{
						loadoutCopy.SetAttribute("$selected", "1");
						ProcessLoadoutSelections(player, loadoutId, loadoutCopy, lastLoadoutSelections);
						defaultSelectionSet = true;
					}
					else
					{
						loadoutCopy.SetAttribute("$selected", "0");
						ProcessLoadoutSelections(player, loadoutId, loadoutCopy, string.Empty);
					}
				}
				else
				{
					loadoutCopy = null;
					result.RemoveChild(result.GetChildrenCount() - 1);
				}
			}
			
			if (loadoutCopy != null)
			{
				TerjeXmlObject loadoutItems = loadoutCopy.GetChildByNodeName("Items");
				if (loadoutItems != null)
				{
					for (int itemId = 0; itemId < loadoutItems.GetChildrenCount(); itemId++)
					{
						m_entitySpawner.BakeXml(loadoutItems.GetChild(itemId), true);
					}
				}
			}
		}
		
		if (!defaultSelectionSet)
		{
			for (int i = 0; i < result.GetChildrenCount(); i++)
			{
				if (result.GetChild(i).EqualAttribute("$valid", "1"))
				{
					result.GetChild(i).SetAttribute("$selected", "1");
					break;
				}
			}
		}
	}
	
	void BuildRespawnsForPlayer(PlayerBase player, out TerjeXmlObject result)
	{
		if (!player || player.GetTerjeProfile() == null)
		{
			return;
		}
		
		string lastRespawnId = player.GetTerjeProfile().GetLastRespawnId();
		
		result = new TerjeXmlObject;
		result.SetName("Respawns");
		
		bool defaultSelectionSet = false;
		foreach (int searchId : m_respawnsOrdered)
		{
			TerjeXmlObject respawnCopy;
			TerjeXmlObject respawnRoot = m_respawnsList.GetChild(searchId);
			
			if (ValidateRespawnNode(respawnRoot))
			{
				bool isValid;
				string respawnId;
				respawnCopy = result.CreateChild("");
				respawnRoot.DeepCopy(respawnCopy, true, false);
				
				respawnCopy.FindAttribute("id", respawnId);
				
				int deathPointNodeIndex = respawnCopy.FindChildIndexByNodeName("DeathPoint");
				if (deathPointNodeIndex != -1)
				{
					vector lastDeathPos;
					string lastDeathError = string.Empty;
					TerjeXmlObject deathPointXml = respawnCopy.GetChild(deathPointNodeIndex);
					bool requireBody = deathPointXml.EqualAttribute("requireBody", "1");
					respawnCopy.RemoveChild(deathPointNodeIndex);
					
					if (!player.GetTerjeProfile().GetRespawnLastDeathPoint(lastDeathPos))
					{
						lastDeathError = "#STR_TERJESTARTSCREEN_RESP_DEATH1";
					}
					else if (requireBody && !CheckRespawnDeadBodyExist(player, lastDeathPos))
					{
						lastDeathError = "#STR_TERJESTARTSCREEN_RESP_DEATH2";
					}
		
					if (lastDeathError == string.Empty)
					{
						TerjeXmlObject respawnDeathPoints = respawnCopy.CreateChildAt("Points", 0);
						TerjeXmlObject respawnDeathPoint = respawnDeathPoints.CreateChild("Point");
						respawnDeathPoint.SetAttribute("pos", lastDeathPos.ToString(false));
						
						TerjeXmlObject respawnDeathOpts = respawnCopy.GetChildByNodeName("Options");
						if (respawnDeathOpts != null)
						{
							TerjeXmlObject respawnDeathOptsMap = respawnDeathOpts.GetChildByNodeName("MapRender");
							if (respawnDeathOptsMap != null)
							{
								respawnDeathOptsMap.SetAttribute("pos", lastDeathPos.ToString(false));
							}
						}
					}
					else
					{
						TerjeXmlObject respawnDeathConds = respawnCopy.GetChildByNodeName("Conditions");
						if (!respawnDeathConds)
						{
							respawnDeathConds = respawnCopy.CreateChild("Conditions");
						}
						
						TerjeXmlObject respawnDeathFail = respawnDeathConds.CreateChild("Fail");
						respawnDeathFail.SetAttribute("message", lastDeathError);
					}
				}
				
				int objectsNodeIndex = respawnCopy.FindChildIndexByNodeName("Objects");
				if (objectsNodeIndex != -1)
				{
					vector objectToPlayerPos;
					vector objectToPlayerRot;
					respawnCopy.RemoveChild(objectsNodeIndex);
					if (GetPluginTerjeRespawnObjects().FindAndValidateRespawnObject(player, respawnId, objectToPlayerPos, objectToPlayerRot))
					{
						TerjeXmlObject respawnObjPoints = respawnCopy.CreateChildAt("Points", 0);
						TerjeXmlObject respawnObjPoint = respawnObjPoints.CreateChild("Point");
						respawnObjPoint.SetAttribute("pos", objectToPlayerPos.ToString(false));
						respawnObjPoint.SetAttribute("angle", (objectToPlayerRot[0]).ToString());
						
						TerjeXmlObject respawnObjOpts = respawnCopy.GetChildByNodeName("Options");
						if (respawnObjOpts != null)
						{
							TerjeXmlObject respawnObjOptsMap = respawnObjOpts.GetChildByNodeName("MapRender");
							if (respawnObjOptsMap != null)
							{
								respawnObjOptsMap.SetAttribute("pos", objectToPlayerPos.ToString(false));
							}
						}
					}
					else
					{
						TerjeXmlObject respawnObjConds = respawnCopy.GetChildByNodeName("Conditions");
						if (!respawnObjConds)
						{
							respawnObjConds = respawnCopy.CreateChild("Conditions");
						}
						
						TerjeXmlObject respawnObjFail = respawnObjConds.CreateChild("Fail");
						respawnObjFail.SetAttribute("message", "#STR_TERJESTARTSCREEN_SETRESP_FAIL");
					}
				}
				
				if (ProcessConditions(player, respawnCopy.GetChildByNodeName("Conditions"), isValid))
				{
					if (isValid)
					{
						respawnCopy.SetAttribute("$valid", "1");
					}
					else
					{
						respawnCopy.SetAttribute("$valid", "0");
					}
					
					if (!defaultSelectionSet && (lastRespawnId == respawnId))
					{
						respawnCopy.SetAttribute("$selected", "1");
						defaultSelectionSet = true;
					}
					else
					{
						respawnCopy.SetAttribute("$selected", "0");
					}
				}
				else
				{
					respawnCopy = null;
					result.RemoveChild(result.GetChildrenCount() - 1);
				}
			}
		}
		
		if (!defaultSelectionSet)
		{
			for (int i = 0; i < result.GetChildrenCount(); i++)
			{
				if (result.GetChild(i).EqualAttribute("$valid", "1"))
				{
					result.GetChild(i).SetAttribute("$selected", "1");
					break;
				}
			}
		}
	}
	
	TerjeXmlObject GetLoadoutById(string id)
	{
		int result;
		if (m_loadoutsSearch.Find(id, result))
		{
			return m_loadoutsList.GetChild(result);
		}
		
		return null;
	}
	
	TerjeXmlObject GetRespawnById(string id)
	{
		int result;
		if (m_respawnsSearch.Find(id, result))
		{
			return m_respawnsList.GetChild(result);
		}
		
		return null;
	}
	
	private bool CheckRespawnDeadBodyExist(PlayerBase player, vector deadBodyPos)
	{
		if (!g_Game || !player || !player.GetIdentity())
			return false;
		
		array<Object> nearestObjects();
		string guid = player.GetIdentity().GetId();
		g_Game.GetObjectsAtPosition3D(deadBodyPos, 2.5, nearestObjects, null);
		foreach (Object obj : nearestObjects)
		{
			PlayerBase body = PlayerBase.Cast(obj);
			if (body && (!body.IsAlive()) && (body.GetCachedID() == guid))
			{
				return true;
			}
		}
		
		return false;
	}
	
	private void ProcessLoadoutSelections(PlayerBase player, string loadoutId, TerjeXmlObject loadout, string lastLoadoutSelections)
	{
		int partIndex = 0;
		array<string> parts();
		
		TerjeXmlObject loadoutItems = loadout.GetChildByNodeName("Items");
		if (loadoutItems == null)
			return;
		
		if (lastLoadoutSelections.Length() > 0)
		{
			lastLoadoutSelections.Split("|", parts);
		}
		
		for (int i = 0; i < loadoutItems.GetChildrenCount(); i++)
		{
			TerjeXmlObject selectorXml = loadoutItems.GetChild(i);
			if (selectorXml != null && selectorXml.IsObjectNode() && (selectorXml.GetName() == "Selector") && (selectorXml.GetChildrenCount() > 0))
			{
				string selectionPart = string.Empty;
				if (partIndex >= 0 && partIndex < parts.Count())
				{
					selectionPart = parts.Get(partIndex);
				}
				
				if (ProcessLoadoutSelection(player, loadoutId, partIndex, selectorXml, selectionPart))
				{
					partIndex++;
				}
			}
		}
	}
	
	private bool ProcessLoadoutSelection(PlayerBase player, string loadoutId, int selectionIndex, TerjeXmlObject selector, string selectionPart)
	{
		if (selector.EqualAttribute("type", "SINGLE"))
		{
			int singlePartId = Math.RandomInt(0, selector.GetChildrenCount());
			if (selectionPart.Length() > 0)
			{
				singlePartId = selectionPart.ToInt();
			}
			
			if (singlePartId < 0 || singlePartId >= selector.GetChildrenCount())
			{
				singlePartId = Math.RandomInt(0, selector.GetChildrenCount());
			}
			
			selector.GetChild(singlePartId).SetAttribute("$selected", "1");
			
			int singleSelections = 0;
			for (int singleIndex = 0; singleIndex < selector.GetChildrenCount(); singleIndex++)
			{
				if (ProcessLoadoutSelectionItem(player, loadoutId, selector, selector.GetChild(singleIndex)))
				{
					singleSelections++;
				}
			}
		
			if (singleSelections > 0)
			{
				selector.SetAttribute("$visible", "1");
				return true;
			}
			else
			{
				selector.SetAttribute("$visible", "0");
				return false;
			}
		}
		else if (selector.EqualAttribute("type", "MULTIPLE"))
		{
			array<string> subparts();
			if (selectionPart.Length() > 0)
			{
				selectionPart.Split("+", subparts);
				foreach (string subpart : subparts)
				{
					int subpartId = subpart.ToInt();
					if (subpartId >= 0 && subpartId < selector.GetChildrenCount())
					{
						selector.GetChild(subpartId).SetAttribute("$selected", "1");
					}
				}
			}
			
			ProcessLoadoutSelectionPoints(player, loadoutId, selectionIndex, selector);
			
			int multipleSelections = 0;
			for (int multipleIndex = 0; multipleIndex < selector.GetChildrenCount(); multipleIndex++)
			{
				if (ProcessLoadoutSelectionItem(player, loadoutId, selector, selector.GetChild(multipleIndex)))
				{
					multipleSelections++;
				}
			}
			
			if (multipleSelections > 0)
			{
				selector.SetAttribute("$visible", "1");
				return true;
			}
			else
			{
				selector.SetAttribute("$visible", "0");
				return false;
			}
		}
		
		selector.GetChild(Math.RandomInt(0, selector.GetChildrenCount())).SetAttribute("$selected", "1");
		return false;
	}
	
	private void ProcessLoadoutSelectionPoints(PlayerBase player, string loadoutId, int selectionIndex, TerjeXmlObject selector)
	{
		string attrValue;
		if (selector.FindAttribute("pointsCount", attrValue))
		{
			int pointsValue = attrValue.ToInt();
			if (pointsValue >= 0)
			{
				selector.SetAttribute("$points", pointsValue.ToString());
			}
		}
		else if (selector.FindAttribute("pointsHandler", attrValue))
		{
			typename attrValueType = attrValue.ToType();
			if (attrValueType && attrValueType.IsInherited(TerjeCustomPointsHandler))
			{
				TerjeCustomPointsHandler handler = TerjeCustomPointsHandler.Cast(attrValueType.Spawn());
				if (handler)
				{
					int pointsResult = handler.GetPoints(player, loadoutId, selectionIndex);
					if (pointsResult < 0)
					{
						pointsResult = handler.GetPointsEx(player, loadoutId, selectionIndex, selector);
					}
		
					if (pointsResult >= 0)
					{
						selector.SetAttribute("$points", pointsResult.ToString());
					}
				}
				else
				{
					TerjeLog_Warning("Class '" + attrValue + "' is not an instance of 'TerjeCustomPointsHandler'.");
				}
			}
			else
			{
				TerjeLog_Warning("Class '" + attrValue + "' not found or not inherited TerjeCustomPointsHandler.");
			}
		}
	}
		
	private bool ProcessLoadoutSelectionItem(PlayerBase player, string loadoutId, TerjeXmlObject selectorRoot, TerjeXmlObject selectorItem)
	{
		string handlerClassname;
		if (selectorItem.FindAttribute("handler", handlerClassname) && (handlerClassname != string.Empty))
		{
			typename handlerType = handlerClassname.ToType();
			if (handlerType && handlerType.IsInherited(TerjeLoadoutSelectorHandler))
			{
				TerjeLoadoutSelectorHandler handlerInstance = TerjeLoadoutSelectorHandler.Cast(handlerType.Spawn());
				if (handlerInstance != null)
				{
					if (!handlerInstance.IsVisible(player, loadoutId, selectorRoot, selectorItem))
					{
						selectorItem.SetAttribute("$visible", "0");
						return false;
					}
		
					if (handlerInstance.IsValid(player, loadoutId, selectorRoot, selectorItem))
					{
						selectorItem.SetAttribute("$valid", "1");
					}
					else
					{
						selectorItem.SetAttribute("$valid", "0");
					}
					
					string displayText = handlerInstance.GetText(player, loadoutId, selectorRoot, selectorItem);
					if (displayText != string.Empty)
					{
						selectorItem.SetAttribute("$handlerMessage", displayText);
					}
				}
				else
				{
					TerjeLog_Warning("Handler class '" + handlerClassname + "' cannot be created.");
				}
			}
			else
			{
				TerjeLog_Warning("Handler class '" + handlerClassname + "' not found or not inherited TerjeLoadoutSelectorHandler.");
			}
		}
		
		selectorItem.SetAttribute("$visible", "1");
		return true;
	}
	
	private bool ValidateLoadoutNode(TerjeXmlObject loadout)
	{
		if (loadout == null)
		{
			return false;
		}
		
		if (!loadout.IsObjectNode())
		{
			return false;
		}
		
		if (loadout.GetName() != "Loadout")
		{
			return false;
		}
		
		if (!loadout.HasAttribute("id") || loadout.EqualAttribute("id", string.Empty))
		{
			TerjeLog_Error("Loadout 'id' attribute is missing.");
			return false;
		}
		
		if (!loadout.HasAttribute("displayName") || loadout.EqualAttribute("displayName", string.Empty))
		{
			TerjeLog_Error("Loadout 'displayName' attribute is missing.");
			return false;
		}
		
		return true;
	}
	
	private bool ValidateRespawnNode(TerjeXmlObject respawn)
	{
		if (respawn == null)
		{
			return false;
		}
		
		if (!respawn.IsObjectNode())
		{
			return false;
		}
		
		if (respawn.GetName() != "Respawn")
		{
			return false;
		}
		
		if (!respawn.HasAttribute("id") || respawn.EqualAttribute("id", string.Empty))
		{
			TerjeLog_Error("Respawn 'id' attribute is missing.");
			return false;
		}
		
		if (!respawn.HasAttribute("displayName") || respawn.EqualAttribute("displayName", string.Empty))
		{
			TerjeLog_Error("Respawn 'displayName' attribute is missing.");
			return false;
		}
		
		TerjeXmlObject deathPoint = respawn.GetChildByNodeName("DeathPoint");
		if (deathPoint != null)
		{
			return true;
		}
		
		TerjeXmlObject objects = respawn.GetChildByNodeName("Objects");
		if (objects != null)
		{
			if (objects.GetChildrenCount() > 0)
			{
				return true;
			}
			else
			{
				TerjeLog_Error("'Objects' node cannot be empty.");
				return false;
			}
		}
		
		TerjeXmlObject points = respawn.GetChildByNodeName("Points");
		if (points != null)
		{
			if (points.GetChildrenCount() > 0)
			{
				return true;
			}
			else
			{
				TerjeLog_Error("'Points' node cannot be empty.");
				return false;
			}
		}
		
		TerjeLog_Error("Respawn must contain 'Points', 'Objects' or 'DeathPoint' node to determine respawn position.");
		return false;
	}
	
	private bool ProcessConditions(PlayerBase player, TerjeXmlObject conditions, out bool valid)
	{
		valid = true;
		if (conditions != null)
		{
			TerjePlayerConditions filter = TerjePlayerConditions.GetInstance();
			for (int condId = 0; condId < conditions.GetChildrenCount(); condId++)
			{
				TerjeXmlObject condition = conditions.GetChild(condId);
				if (condition.IsObjectNode())
				{
					int status = 0;
					string displayText = string.Empty;
					if (filter.ProcessCondition(player, condition, displayText))
					{
						status = 1;
					}
					else
					{
						valid = false;
						if (condition.EqualAttribute("hideOwnerWhenFalse", "1"))
						{
							return false;
						}
					}
					
					condition.SetAttribute("$valid", status.ToString());
					condition.SetAttribute("$text", displayText);
				}
			}
		}
		
		return true;
	}
	
	private void OnTerjeStartScreenNameVerify(ParamsReadContext ctx, PlayerIdentity sender)
	{
		Param1<string> received;
		if (!ctx.Read(received))
			return;
		
		string fullName = received.param1;
		bool result = (!GetTerjeSettingBool(TerjeSettingsCollection.STARTSCREEN_UNIQ_NAME_CHECKS)) || (!HasCharacterWithName(fullName));
		
		Param1<bool> payload = new Param1<bool>(result);
		GetTerjeRPC().SendToClient("startscreen.name.verify", sender, payload);
	}
	
	private void OnTerjeStartScreenOverviewDel(ParamsReadContext ctx, PlayerIdentity sender)
	{
		if (!sender)
			return;
		
		PlayerBase player = FindPlayerByIdentity(sender);
		if (!player)
			return;
		
		player.m_terjeStartScreenParams = null;
		player.SetTerjeServerStartScreenImmunity(false);
		player.SetTerjeMaintenanceMode(true);
		player.SetHealth("", "", 0);
		GetTerjeDatabase().DeletePlayerProfile(sender.GetId());
	}
	
	private void OnTerjeStartScreenLoadoutEquip(ParamsReadContext ctx, PlayerIdentity sender)
	{
		PlayerBase player = FindPlayerByIdentity(sender);
		if (!player)
			return;
		
		if (!player.m_terjeStartScreenParams)
			return;
		
		TerjeStartScreenContextLoadout loadoutContext = TerjeStartScreenContextLoadout.Cast(player.m_terjeStartScreenParams.GetActualContext());
		if (!loadoutContext)
			return;
		
		if (!loadoutContext.m_inputLoadouts)
			return;
		
		TerjeXmlObject clientLoadout();
		if (!clientLoadout.Unbinarize(ctx))
			return;
		
		string loadoutId;
		if (!clientLoadout.FindAttribute("id", loadoutId))
			return;
		
		TerjeXmlObject serverLoadout = loadoutContext.m_inputLoadouts.GetChildByAttrPair("Loadout", "id", loadoutId);
		if (!serverLoadout)
			return;
		
		if (!CompareClientAndServerLoadoutObjects(clientLoadout, serverLoadout))
		{
			TerjeLog_Warning("Server and client loadouts missmatch. Possible hacker: " + sender.GetId());
			g_Game.DisconnectPlayer(sender, sender.GetId());
			return;
		}
		
		TerjeXmlObject clientItems = clientLoadout.GetChildByNodeName("Items");
		if (!clientItems)
			return;
		
		TerjeXmlObject serverItems = serverLoadout.GetChildByNodeName("Items");
		if (!serverItems)
			return;
		
		clientItems.DeepCopy(serverItems, true, false);
		StartLoadoutItemsEquip(player, sender, serverItems);
	}
	
	private bool CompareClientAndServerLoadoutObjects(TerjeXmlObject clientLoadout, TerjeXmlObject serverLoadout)
	{
		if (clientLoadout.GetName() != serverLoadout.GetName())
		{
			return false;
		}
		
		if (!CompareClientAndServerXmlAttribute(clientLoadout, serverLoadout, "classname"))
		{
			return false;
		}
		
		if (!CompareClientAndServerXmlAttribute(clientLoadout, serverLoadout, "type"))
		{
			return false;
		}
		
		if (!CompareClientAndServerXmlAttribute(clientLoadout, serverLoadout, "cost"))
		{
			return false;
		}
		
		if (!CompareClientAndServerXmlAttribute(clientLoadout, serverLoadout, "$points"))
		{
			return false;
		}
		
		if (clientLoadout.GetChildrenCount() != serverLoadout.GetChildrenCount())
		{
			return false;
		}
		
		for (int i = 0; i < clientLoadout.GetChildrenCount(); i++)
		{
			if (!CompareClientAndServerLoadoutObjects(clientLoadout.GetChild(i), serverLoadout.GetChild(i)))
			{
				return false;
			}
		}
		
		return true;
	}
	
	private bool CompareClientAndServerXmlAttribute(TerjeXmlObject clientXml, TerjeXmlObject serverXml, string attrName)
	{
		string serverValue;
		if (serverXml.FindAttribute(attrName, serverValue))
		{
			string clientValue;
			if (!clientXml.FindAttribute(attrName, clientValue))
			{
				return false;
			}
			
			if (serverValue != clientValue)
			{
				return false;
			}
		}
		
		return true;
	}
	
	private void OnTerjeStartScreenContextApply(ParamsReadContext ctx, PlayerIdentity sender)
	{
		PlayerBase player = FindPlayerByIdentity(sender);
		if (!player)
			return;
		
		if (player.m_terjeStartScreenParams == null)
			return;
		
		TerjeStartScreenContextBase context = player.m_terjeStartScreenParams.GetActualContext();
		if (context == null)
			return;
		
		if (!context.Deserialize(ctx))
			return;
		
		player.m_terjeStartScreenParams.ApplyServerContext(player);
		
		if (player.m_terjeStartScreenParams != null)
		{
			player.m_terjeStartScreenParams.NextServerContext(player);
			
			if (player.m_terjeStartScreenParams.GetActualContext() != null)
			{
				TerjeStreamRpc stream;
				GetTerjeRPC().StreamToClient("startscreen.apply.callback", sender, stream);
				player.m_terjeStartScreenParams.Serialize(stream);
				stream.Flush();
			}
			else
			{
				OnTerjeStartScreenContextDone(player, sender);
			}
		}
	}
	
	private void OnTerjeStartScreenContextDone(PlayerBase player, PlayerIdentity sender)
	{
		player.SetTerjeServerStartScreenImmunity(false);
		if (player.m_terjeStartScreenParams != null)
		{
			player.m_terjeStartScreenParams.OnServerDone(player);
		}
		
		player.m_terjeStartScreenParams = null;
		player.SetSynchDirty();
		
		if (player.GetTerjeStats() != null)
		{
			player.GetTerjeStats().SetStartScreenInProgress(false);
		}
		
		if (player.IsAlive())
		{
			TerjeStreamRpc stream;
			GetTerjeRPC().StreamToClient("startscreen.close", sender, stream);
			WriteTerjeStartScreenContextDone(player, stream);
			stream.Flush();
		}
	}
	
	private void WriteTerjeStartScreenContextDone(PlayerBase player, TerjeStreamRpc stream)
	{
		stream.Write(player.GetPosition());
		stream.Write(player.GetOrientation());
	}
	
	private PlayerBase FindPlayerByIdentity(PlayerIdentity identity)
	{
		array<Man> players();
		g_Game.GetPlayers(players);
		foreach (Man man : players)
		{
			if (man && man.GetIdentity() && man.GetIdentity().GetId() == identity.GetId())
			{
				return PlayerBase.Cast(man);
			}
		}
		
		return null;
	}
	
	private void LoadRulesMarkdown()
	{
		string rulesPath = SETTINGS_DIR + "\\ServerRules.md";
		if (!FileExist(rulesPath))
		{
			CopyFile("TerjeStartScreen\\Templates\\ServerRules.md", rulesPath);
		}
		
		FileHandle file = OpenFile(rulesPath, FileMode.READ);
		if (file != 0)
		{
			string lineContent;
			m_rulesMarkdownContent.Clear();
			while (FGets(file, lineContent) != -1)
			{
				m_rulesMarkdownContent.Insert(lineContent);
			}
			
			CloseFile(file);
		}
	}
	
	private void LoadGeneralXml()
	{
		string generalXmlPath = SETTINGS_DIR + "\\General.xml";
		if (!FileExist(generalXmlPath))
		{
			CopyFile("TerjeStartScreen\\Templates\\General.xml", generalXmlPath);
		}
		
		TerjeXmlDocument generalXmlDoc();
		if (generalXmlDoc.DeserializeFromFile(generalXmlPath))
		{
			generalXmlDoc.DeleteComments();
			
			int generalNodeIndex = generalXmlDoc.FindChildIndexByNodeName("General");
			if (generalNodeIndex != -1)
			{
				m_generalXml = generalXmlDoc.GetChild(generalNodeIndex);
			}
		}
	}
	
	private void LoadFacesList()
	{
		string facesXmlPath = SETTINGS_DIR + "\\Faces.xml";
		if (!FileExist(facesXmlPath))
		{
			CopyFile("TerjeStartScreen\\Templates\\Faces.xml", facesXmlPath);
		}
		
		TerjeXmlDocument facesXmlDoc();
		if (facesXmlDoc.DeserializeFromFile(facesXmlPath))
		{
			facesXmlDoc.DeleteComments();
			
			int facesNodeIndex = facesXmlDoc.FindChildIndexByNodeName("Faces");
			if (facesNodeIndex != -1)
			{
				m_facesXml = facesXmlDoc.GetChild(facesNodeIndex);
			}
			else
			{
				TerjeLog_Error("Failed to find 'Faces' root tag in " + facesXmlPath);
			}
		}
		else
		{
			TerjeLog_Error("Failed to load " + facesXmlPath);
		}
	}
	
	private void LoadLoadoutsList()
	{
		string loadoutsXmlPath = SETTINGS_DIR + "\\Loadouts.xml";
		if (!FileExist(loadoutsXmlPath))
		{
			CopyFile("TerjeStartScreen\\Templates\\Loadouts.xml", loadoutsXmlPath);
		}
		
		m_loadoutsSearch.Clear();
		m_loadoutsOrdered.Clear();
		TerjeXmlDocument loadoutsXmlDoc();
		if (loadoutsXmlDoc.DeserializeFromFile(loadoutsXmlPath))
		{
			loadoutsXmlDoc.DeleteComments();
			
			int nodeIndex = loadoutsXmlDoc.FindChildIndexByNodeName("Loadouts");
			if (nodeIndex != -1)
			{
				m_loadoutsList = loadoutsXmlDoc.GetChild(nodeIndex);
				
				for (int i = 0; i < m_loadoutsList.GetChildrenCount(); i++)
				{
					TerjeXmlObject loadoutObj = m_loadoutsList.GetChild(i);
					if (ValidateLoadoutNode(loadoutObj))
					{
						string loadoutId;
						if (loadoutObj.FindAttribute("id", loadoutId) && !m_loadoutsSearch.Contains(loadoutId))
						{
							m_loadoutsSearch.Insert(loadoutId, i);
							m_loadoutsOrdered.Insert(i);
						}
						else
						{
							TerjeLog_Error("Loadout id '" + loadoutId + "' duplicated.");
						}
					}
				}
			}
			else
			{
				TerjeLog_Error("Failed to find 'Loadouts' root tag in " + loadoutsXmlPath);
			}
		}
		else
		{
			TerjeLog_Error("Failed to load " + loadoutsXmlPath);
		}
	}
	
	private void LoadRespawnsList()
	{
		string respawnsXmlPath = SETTINGS_DIR + "\\Respawns.xml";
		if (!FileExist(respawnsXmlPath))
		{
			string worldName = g_Game.GetWorldName();
			if (FileExist("TerjeStartScreen\\Templates\\Respawns_" + worldName + ".xml"))
			{
				CopyFile("TerjeStartScreen\\Templates\\Respawns_" + worldName + ".xml", respawnsXmlPath);
			}
			else
			{
				CopyFile("TerjeStartScreen\\Templates\\Respawns_chernarusplus.xml", respawnsXmlPath);
			}
		}
		
		m_respawnsSearch.Clear();
		m_respawnsOrdered.Clear();
		TerjeXmlDocument respawnsXmlDoc();
		if (respawnsXmlDoc.DeserializeFromFile(respawnsXmlPath))
		{
			respawnsXmlDoc.DeleteComments();
			
			int nodeIndex = respawnsXmlDoc.FindChildIndexByNodeName("Respawns");
			if (nodeIndex != -1)
			{
				m_respawnsList = respawnsXmlDoc.GetChild(nodeIndex);
				
				for (int i = 0; i < m_respawnsList.GetChildrenCount(); i++)
				{
					TerjeXmlObject respawnObj = m_respawnsList.GetChild(i);
					if (ValidateRespawnNode(respawnObj))
					{
						string respawnId;
						if (respawnObj.FindAttribute("id", respawnId) && !m_respawnsSearch.Contains(respawnId))
						{
							m_respawnsSearch.Insert(respawnId, i);
							m_respawnsOrdered.Insert(i);
							
							TerjeXmlObject objects = respawnObj.GetChildByNodeName("Objects");
							if (objects != null)
							{
								GetPluginTerjeRespawnObjects().RegisterRespawnObjects(respawnId, objects);
							}
						}
						else
						{
							TerjeLog_Error("Respawn id '" + respawnId + "' duplicated.");
						}
					}
				}
			}
			else
			{
				TerjeLog_Error("Failed to find 'Respawns' root tag in " + respawnsXmlPath);
			}
		}
		else
		{
			TerjeLog_Error("Failed to load " + respawnsXmlPath);
		}
	}
	
	private void StartLoadoutItemsEquip(PlayerBase player, PlayerIdentity sender, TerjeXmlObject itemsObject)
	{
		if (!sender || !player || !player.IsAlive())
			return;
		
		if (itemsObject == null)
			return;
		
		if (player.m_terjeLoadoutProcessing)
			return;
		
		player.m_terjeLoadoutProcessing = true;
		ClearLoadoutItemsEquip(player);
		g_Game.GetCallQueue(CALL_CATEGORY_SYSTEM).Call(EndLoadoutItemsEquip, player, sender, itemsObject);
	}
	
	private void ClearLoadoutItemsEquip(PlayerBase player)
	{
		if (g_Game && g_Game.IsDedicatedServer())
		{
			array<EntityAI> items();
			player.GetInventory().EnumerateInventory(InventoryTraversalType.INORDER, items);
			for (int i = 0; i < items.Count(); i++)
			{
				ItemBase item = ItemBase.Cast(items.Get(i));
				if (item)
				{
					DeleteLoadoutItemEquip(item);
				}
			}
	
			ItemBase itemInHands = ItemBase.Cast(player.GetEntityInHands());
			if (itemInHands)
			{
				player.LocalDestroyEntityInHands();
			}
		}
	}
	
	private void DeleteLoadoutItemEquip(ItemBase item)
	{
		g_Game.ObjectDelete(item);
	}
	
	private void EndLoadoutItemsEquip(PlayerBase player, PlayerIdentity sender, TerjeXmlObject itemsObject)
	{
		if (!sender || !player || !player.IsAlive())
			return;
		
		if (itemsObject == null)
			return;
		
		for (int i = 0; i < itemsObject.GetChildrenCount(); i++)
		{
			ProcessLoadoutItemEquip(itemsObject.GetChild(i), player, 0);
		}
		
		player.SetSynchDirty();
		player.m_terjeLoadoutProcessing = false;
		Param1<int> payload = new Param1<int>(0);
		GetTerjeRPC().SendToClient("startscreen.loadout.ready", sender, payload);
	}
	
	private bool ProcessLoadoutItemEquip(TerjeXmlObject xmlObject, EntityAI target, bool depth)
	{
		if ((xmlObject != null) && (xmlObject.IsObjectNode()))
		{
			if (xmlObject.GetName() == "Item")
			{
				return (m_entitySpawner.SpawnInInventoryFromXml(xmlObject, target) != null);
			}
			else if (xmlObject.GetName() == "Selector")
			{
				if ((xmlObject.GetChildrenCount() > 0) && (depth == 0))
				{
					return ProcessLoadoutSelectorEquip(xmlObject, target, depth + 1);
				}
			}
			else if (xmlObject.GetName() == "Group")
			{
				bool result = true;
				for (int groupChildId = 0; groupChildId < xmlObject.GetChildrenCount(); groupChildId++)
				{
					if (!ProcessLoadoutItemEquip(xmlObject.GetChild(groupChildId), target, depth + 1))
					{
						result = false;
					}
				}
				
				return result;
			}
		}
		
		return false;
	}
	
	private bool ProcessLoadoutSelectorEquip(TerjeXmlObject xmlObject, EntityAI target, bool depth)
	{
		if (xmlObject.EqualAttribute("type", "MULTIPLE"))
		{
			string pointsStr;
			bool hasPoints = false;
			int pointsCount = 0;
			if (xmlObject.FindAttribute("$points", pointsStr))
			{
				pointsCount = pointsStr.ToInt();
				hasPoints = true;
			}
			
			for (int multId = 0; multId < xmlObject.GetChildrenCount(); multId++)
			{
				TerjeXmlObject multChild = xmlObject.GetChild(multId);
				if ((multChild != null) && multChild.EqualAttribute("$selected", "1"))
				{
					int costInt = 0;
					string costStr;
					if (multChild.FindAttribute("cost", costStr))
					{
						costInt = costStr.ToInt();
					}
					
					if (!hasPoints)
					{
						ProcessLoadoutItemEquip(multChild, target, depth + 1);
					}
					else if (costInt >= 0)
					{
						pointsCount -= costInt;
						if (pointsCount >= 0)
						{
							ProcessLoadoutItemEquip(multChild, target, depth + 1);
						}
					}
				}
			}
			
			return true;
		}
		
		for (int singleId = 0; singleId < xmlObject.GetChildrenCount(); singleId++)
		{
			TerjeXmlObject singleChild = xmlObject.GetChild(singleId);
			if ((singleChild != null) && singleChild.EqualAttribute("$selected", "1"))
			{
				return ProcessLoadoutItemEquip(singleChild, target, depth + 1);
			}
		}
		
		return false;
	}
}

PluginTerjeStartScreen GetPluginTerjeStartScreen() 
{
	return PluginTerjeStartScreen.Cast(GetPlugin(PluginTerjeStartScreen));
}