typedef map<int, TerjeScriptableArea> TerjeSAT_Indexed;
typedef map<int, ref TerjeSAT_Indexed> TerjeSAT_AxisY;
typedef map<int, ref TerjeSAT_AxisY> TerjeSAT_AxisXY;
typedef map<string, ref set<string>> TerjeCustomProtectionMap;
typedef array<string> TerjeCustomProtectionTypes;

class PluginTerjeScriptableAreas : PluginBase 
{
	private int m_currentIndex = int.MIN;
	private ref TerjeSAT_General m_scriptableAreas;
	private ref TerjeCustomProtectionMap m_customProtection;
	
	override void OnInit()
	{
		super.OnInit();
		
		m_scriptableAreas = new TerjeSAT_General;
		if (g_Game.IsDedicatedServer())
		{
			string areasXmlDir = "$profile:TerjeSettings\\ScriptableAreas";
			MakeDirectory(areasXmlDir);
			
			TerjeXmlDocument areasXmlDocument();
			string wikiPath = areasXmlDir + "\\README.md";
			string areasXmlPath = areasXmlDir + "\\ScriptableAreasSpawner.xml";
			string templateXmlPath = "TerjeCore\\Templates\\ScriptableAreasSpawner.xml";
			if (FileExist(areasXmlPath))
			{
				areasXmlDocument.DeserializeFromFile(areasXmlPath);
			}
			else
			{
				CopyFile(templateXmlPath, areasXmlPath);
				areasXmlDocument.DeserializeFromFile(templateXmlPath);
			}

			TerjeXmlObject areasXml = areasXmlDocument.GetChildByNodeName("Areas");
			if ((areasXml != null) && (areasXml.IsObjectNode()))
			{
				for (int areaId = 0; areaId < areasXml.GetChildrenCount(); areaId++)
				{
					TerjeXmlObject areaXml = areasXml.GetChild(areaId);
					if ((areaXml != null) && (areaXml.IsObjectNode()))
					{
						SpawnTerjeScriptableArea(areaXml);
					}
				}
			}
			
			if (FileExist(wikiPath))
			{
				DeleteFile(wikiPath);
			}
			
			FileHandle wikiFile = OpenFile(wikiPath, FileMode.WRITE);
			if (wikiFile != 0)
			{
				WriteScriptableAreasWiki(wikiFile);
				CloseFile(wikiFile);
			}
			
			if (GetTerjeSettingBool(TerjeSettingsCollection.CORE_USE_CUSTOM_PROTECTION_CONFIGS))
			{
				m_customProtection = new TerjeCustomProtectionMap;	
				TerjeCustomProtectionTypes customProtectionTypes();
				RegisterCustomProtection(customProtectionTypes);
				
				string customProtectionRoot = "$profile:TerjeSettings\\CustomProtection";
				MakeDirectory(customProtectionRoot);
				
				foreach (string customProtectionType : customProtectionTypes)
				{
					string customProtectionPath = customProtectionRoot + "\\" + customProtectionType + ".txt";
					ref set<string> playerGuids = new set<string>;
					FileHandle customProtectionFile;
					
					if (FileExist(customProtectionPath))
					{
						customProtectionFile = OpenFile(customProtectionPath, FileMode.READ);
						if (customProtectionFile != 0)
						{
							string customProtectionLine;
							while ( FGets( customProtectionFile, customProtectionLine ) != -1 )
							{
								customProtectionLine = customProtectionLine.Trim();
								if (customProtectionLine.Length() > 0 && customProtectionLine.IndexOf("/" + "/") == -1)
								{
									playerGuids.Insert(customProtectionLine);
								}
							}
							CloseFile(customProtectionFile);
						}
					}
					else
					{
						customProtectionFile = OpenFile(customProtectionPath, FileMode.WRITE);
						if (customProtectionFile != 0)
						{
							FPrintln(customProtectionFile, "/" + "/ Add the SteamIDs of players to this file (one per line) for whom you would like them to have absolute immunity against effects of this type.");
							FPrintln(customProtectionFile, "");
							CloseFile(customProtectionFile);
						}
					}
					
					m_customProtection.Insert(customProtectionType, playerGuids);
				}
			}
			else
			{
				m_customProtection = null;
			}
		}
	}
	
	protected void SpawnTerjeScriptableArea(TerjeXmlObject areaXml)
	{
		TerjeXmlObject nodeActive = areaXml.GetChildByNodeName("Active");
		if ((nodeActive != null) && (nodeActive.GetValue() != "1"))
		{
			return;
		}
		
		TerjeXmlObject nodeChance = areaXml.GetChildByNodeName("SpawnChance");
		if ((nodeChance != null) && TerjeEvent(nodeChance.GetValue().ToFloat()))
		{
			return;
		}
		
		TerjeXmlObject nodeClassname = areaXml.GetChildByNodeName("Classname");
		if ((nodeClassname == null) || (nodeClassname.GetValue() == string.Empty))
		{
			TerjeLog_Error("PluginTerjeScriptableAreas::SpawnTerjeScriptableArea Failed to spawn scriptable area. 'Classname' tag required.");
			return;
		}

		TerjeXmlObject nodePosition = areaXml.GetChildByNodeName("Position");
		if ((nodePosition == null) || (nodePosition.GetValue() == string.Empty))
		{
			TerjeLog_Error("PluginTerjeScriptableAreas::SpawnTerjeScriptableArea Failed to spawn scriptable area. 'Position' tag required.");
			return;
		}

		TerjeXmlObject nodeData = areaXml.GetChildByNodeName("Data");
		ref map<string, float> dataParams = new map<string, float>;
		if ((nodeData != null) && (nodeData.IsObjectNode()))
		{
			for (int dataNodeId = 0; dataNodeId < nodeData.GetChildrenCount(); dataNodeId++)
			{
				TerjeXmlObject nodeDataElement = nodeData.GetChild(dataNodeId);
				if ((nodeDataElement != null) && (nodeDataElement.IsObjectNode()))
				{
					dataParams.Set(nodeDataElement.GetName(), nodeDataElement.GetValue().ToFloat());
				}
			}
		}

		string filter = string.Empty;
		TerjeXmlObject nodeFilter = areaXml.GetChildByNodeName("Filter");
		if ((nodeFilter != null) && (nodeFilter.IsObjectNode()))
		{
			filter = nodeFilter.GetValue();
		}
		
		TerjeScriptableArea spawnableObject;
		string classname = nodeClassname.GetValue();
		vector pos = TerjeVectorHelper.StrToVector(nodePosition.GetValue());
		if (pos[1] == 0)
		{
			pos[1] = g_Game.SurfaceRoadY( pos[0], pos[2] );
			Class.CastTo( spawnableObject, g_Game.CreateObjectEx( classname, pos, ECE_PLACE_ON_SURFACE ) );
		}
		else
		{
			Class.CastTo( spawnableObject, g_Game.CreateObjectEx( classname, pos, ECE_NONE ) );
		}
		
		if (spawnableObject)
		{
			spawnableObject.SetTerjeParametersServer(dataParams);
			
			if (filter != string.Empty)
			{
				spawnableObject.SetTerjeFilterServer(filter);
			}
		}
		else
		{
			TerjeLog_Error("PluginTerjeScriptableAreas::OnInit Failed to spawn scriptable area with classname '" + classname + "' at " + pos + ".");
		}
	}
	
	override void OnDestroy()
	{
		m_scriptableAreas = null;
		super.OnDestroy();
	}
	
	void WriteScriptableAreasWiki(FileHandle file)
	{

	}
	
	void RegisterCustomProtection(TerjeCustomProtectionTypes customProtectionTypes)
	{
	
	}
	
	bool HasAbsoluteCustomProtectionOfType(PlayerBase player, string protectionType)
	{
		if (g_Game && g_Game.IsDedicatedServer() && m_customProtection != null)
		{
			ref set<string> registeredIds;
			if (m_customProtection.Find(protectionType, registeredIds))
			{			
				if (player && player.GetIdentity() && registeredIds != null)
				{
					string plainId = player.GetIdentity().GetPlainId();
					if (registeredIds.Find(plainId) != -1)
					{
						return true;
					}
					
					string steamGuid = player.GetIdentity().GetId();
					if (registeredIds.Find(steamGuid) != -1)
					{
						return true;
					}
				}
			}
		}
		
		return false;
	}
	
	int RegisterScriptableArea(TerjeScriptableArea scriptableArea)
	{
		m_currentIndex = m_currentIndex + 1;
		m_scriptableAreas.Insert(m_currentIndex, scriptableArea);
		return m_currentIndex;
	}
	
	void UnregisterScriptableArea(int index, TerjeScriptableArea scriptableArea)
	{
		m_scriptableAreas.Remove(index, scriptableArea);
	}
	
	// Obsolete, use TryCalculateTerjeEffectValue instead
	float CalculateTerjeEffectValue(EntityAI entity, string areaType)
	{
		float result;
		if (TryCalculateTerjeEffectValue(entity, areaType, "", result))
		{
			return result;
		}
		
		return 0;
	}
	
	bool TryCalculateTerjeEffectValue(EntityAI entity, string areaType, string filterEntry, out float result)
	{
		result = 0;
		if (entity != null)
		{
			vector entityPos = entity.GetWorldPosition();
			if (m_scriptableAreas.TryCalculateTerjeEffectValue(entity, entityPos, areaType, filterEntry, result))
			{
				return true;
			}
		}
		
		return false;
	}
	
	void TransferTerjeRadiation(EntityAI from, EntityAI to, float modifier)
	{
		AddTerjeRadiationToEntity(to, GetTerjeRadiationFromEntity(from) * modifier);
	}
	
	void CleanTerjeRadiationFromEntity(EntityAI entity, float power, bool recursive, bool addWet)
	{
		if (power > 0)
		{
			power *= -1;
		}
		
		if (AddTerjeRadiationToEntity(entity, power))
		{
			if (addWet)
			{
				entity.AddWet(entity.GetWetMax() * 0.1);
			}
			
			if (recursive)
			{
				GameInventory inv = entity.GetInventory();
				if (inv)
				{
					int attCount = inv.AttachmentCount();
					for ( int attIdx = 0; attIdx < attCount; attIdx++ )
					{
						EntityAI attachment = inv.GetAttachmentFromIndex( attIdx );
						if ( attachment )
						{
							CleanTerjeRadiationFromEntity(attachment, power, recursive, addWet);
						}
					}
					
					CargoBase cargo = inv.GetCargo();
					if (cargo)
					{
						for ( int ittIdx = 0; ittIdx < cargo.GetItemCount(); ittIdx++ )
						{
							EntityAI item = cargo.GetItem( ittIdx );
							if (item)
							{
								CleanTerjeRadiationFromEntity(item, power, recursive, addWet);
							}
						}
					}
				}
			}
		}
	}
	
	bool AddTerjeRadiationToEntity(EntityAI entity, float rAmount)
	{
		if (entity)
		{
			if (entity.IsInherited(PlayerBase))
			{
				return PlayerBase.Cast(entity).AddTerjeRadiation(rAmount);
			}
			else if (entity.IsInherited(ItemBase))
			{
				return ItemBase.Cast(entity).AddTerjeRadiation(rAmount);
			}
			else if (entity.IsInherited(ZombieBase))
			{
				return ZombieBase.Cast(entity).AddTerjeRadiation(rAmount);
			}
			else if (entity.IsInherited(CarScript))
			{
				return CarScript.Cast(entity).AddTerjeRadiation(rAmount);
			}
			else if (entity.IsInherited(AnimalBase))
			{
				return AnimalBase.Cast(entity).AddTerjeRadiation(rAmount);
			}
		}
		
		return false;
	}
	
	float GetTerjeRadiationFromEntity(EntityAI entity)
	{
		if (entity)
		{
			if (entity.IsInherited(PlayerBase))
			{
				return PlayerBase.Cast(entity).GetTerjeRadiation();
			}
			else if (entity.IsInherited(ItemBase))
			{
				return ItemBase.Cast(entity).GetTerjeRadiation();
			}
			else if (entity.IsInherited(ZombieBase))
			{
				return ZombieBase.Cast(entity).GetTerjeRadiation();
			}
			else if (entity.IsInherited(CarScript))
			{
				return CarScript.Cast(entity).GetTerjeRadiation();
			}
			else if (entity.IsInherited(AnimalBase))
			{
				return AnimalBase.Cast(entity).GetTerjeRadiation();
			}
		}
		
		return 0;
	}
	
	float IsTerjeRadiationSupportedForEntity(EntityAI entity)
	{
		if (entity)
		{
			if (entity.IsInherited(PlayerBase))
			{
				return true;
			}
			else if (entity.IsInherited(ItemBase))
			{
				return true;
			}
			else if (entity.IsInherited(ZombieBase))
			{
				return true;
			}
			else if (entity.IsInherited(CarScript))
			{
				return true;
			}
			else if (entity.IsInherited(AnimalBase))
			{
				return true;
			}
		}
		
		return false;
	}
	
	bool GetTerjeRadiationZonePowerToRadLimit(out float result)
	{
		return false;
	}
	
	float CalculateTerjeRadiationFromNearestEntities(EntityAI owner, float radius, bool ignoreOwnerRadioactivity)
	{
		float result = 0;
		float divider = 0;
		if (owner && radius > 0 && GetTerjeRadiationZonePowerToRadLimit(divider) && divider > 0)
		{
			PlayerBase playerObj;
			ItemBase itemObj;
			ZombieBase zombieObj;
			CarScript vehicleObj;
			AnimalBase animalObj;
			vector ownerPos = owner.GetWorldPosition();
			ref array<Object> nearestObjects = new array<Object>;
			g_Game.GetObjectsAtPosition3D(ownerPos, radius, nearestObjects, null);
			foreach (Object obj : nearestObjects)
			{
				if (owner == obj && ignoreOwnerRadioactivity)
				{
					continue;
				}
				
				// Sorry for that shitty if-else spagettie.
				// I can't make interface for GetTerjeRadiation inside EntityAI because Bohemia won't let me mod this class.
				if (PlayerBase.CastTo(playerObj, obj))
				{
					result = Math.Max( result, playerObj.GetTerjeRadiationAdvanced(true, true, true) * CalculateDistanceModToPlayer(playerObj, ownerPos, radius) );
				}
				else if (ItemBase.CastTo(itemObj, obj))
				{
					result = Math.Max( result, itemObj.GetTerjeRadiation() * CalculateDistanceModToObject(obj, ownerPos, radius) );
				}
				else if (ZombieBase.CastTo(zombieObj, obj))
				{
					result = Math.Max( result, zombieObj.GetTerjeRadiation() * CalculateDistanceModToZombie(zombieObj, ownerPos, radius) );
				}
				else if (CarScript.CastTo(vehicleObj, obj))
				{
					result = Math.Max( result, vehicleObj.GetTerjeRadiation() * CalculateDistanceModToObject(obj, ownerPos, radius) );
				}
				else if (AnimalBase.CastTo(animalObj, obj))
				{
					result = Math.Max( result, animalObj.GetTerjeRadiation() * CalculateDistanceModToObject(obj, ownerPos, radius) );
				}
			}
			
			return result / divider;
		}
		
		return 0;
	}
	
	float CalculatePlayerBodyProtection(PlayerBase player, string protectionType, float power)
	{
		ref TerjeScriptableProtection tsp = TerjeScriptableProtection.GetInstance();
		float feetWeight = tsp.GetWeight(protectionType, "Feet");
		float legsWeight = tsp.GetWeight(protectionType, "Legs");
		float bodyWeight = tsp.GetWeight(protectionType, "Body");
		float glovesWeight = tsp.GetWeight(protectionType, "Gloves");
		float headgearWeight = tsp.GetWeight(protectionType, "Headgear");
		float armbandWeight = tsp.GetWeight(protectionType, "Armband");
		float backpackWeight = tsp.GetWeight(protectionType, "Back");
		float maskWeight = tsp.GetWeight(protectionType, "Mask");
		float eyewearWeight = tsp.GetWeight(protectionType, "Eyewear");
		float totalWeight = Math.Max(1.0, feetWeight + legsWeight + bodyWeight + glovesWeight + headgearWeight + armbandWeight + backpackWeight + maskWeight + eyewearWeight);

		float totalProtection = 0;
		totalProtection += CalculatePlayerPartProtection(player, InventorySlots.FEET, protectionType, "Feet", power) * feetWeight;
		totalProtection += CalculatePlayerPartProtection(player, InventorySlots.LEGS, protectionType, "Legs", power) * legsWeight;
		totalProtection += CalculatePlayerPartProtection(player, InventorySlots.BODY, protectionType, "Body", power) * bodyWeight;
		totalProtection += CalculatePlayerPartProtection(player, InventorySlots.GLOVES, protectionType, "Gloves", power) * glovesWeight;
		totalProtection += CalculatePlayerPartProtection(player, InventorySlots.HEADGEAR, protectionType, "Headgear", power) * headgearWeight;
		totalProtection += CalculatePlayerPartProtection(player, InventorySlots.ARMBAND, protectionType, "Armband", power) * armbandWeight;
		totalProtection += CalculatePlayerPartProtection(player, InventorySlots.BACK, protectionType, "Back", power) * backpackWeight;
		totalProtection += CalculatePlayerPartProtection(player, InventorySlots.MASK, protectionType, "Mask", power) * maskWeight;
		totalProtection += CalculatePlayerPartProtection(player, InventorySlots.EYEWEAR, protectionType, "Eyewear", power) * eyewearWeight;
		
		return Math.Clamp(totalProtection / totalWeight, 0, 1);
	}
	
	float CalculatePlayerPartProtection(PlayerBase player, int slot, string protectionType, string partType, float power)
	{
		float bodyProtection = TerjeScriptableProtection.GetInstance().GetBodyProtection(protectionType, partType, power);
		ItemBase attachment = ItemBase.Cast(player.GetInventory().FindAttachment(slot));
		if (attachment)
		{
			bodyProtection += attachment.GetTerjeProtectionAdvanced(protectionType, power);
		}
		
		return Math.Clamp(bodyProtection, 0, 1);
	}
	
	private float CalculateDistanceModToObject(Object obj, vector ownerPos, float radius)
	{
		return 1.0 - Math.Clamp(vector.Distance(obj.GetWorldPosition(), ownerPos) / radius, 0, 1);
	}
	
	private float CalculateDistanceModToZombie(ZombieBase zombie, vector ownerPos, float radius)
	{
		vector zombiePos = zombie.GetWorldPosition();
		zombiePos[1] = zombiePos[1] + 1.5;
		return 1.0 - Math.Clamp(vector.Distance(zombiePos, ownerPos) / radius, 0, 1);
	}
	
	private float CalculateDistanceModToPlayer(PlayerBase player, vector ownerPos, float radius)
	{
		vector headBonePos;
		MiscGameplayFunctions.GetHeadBonePos(player, headBonePos);
		return 1.0 - Math.Clamp(vector.Distance(headBonePos, ownerPos) / radius, 0, 1);
	}
}

class PluginTerjeScriptableAreas_Config
{
	ref array<ref PluginTerjeScriptableAreas_ConfigEntry> Areas;
}

class PluginTerjeScriptableAreas_ConfigEntry
{
	int Active;
	string Classname;
	vector Position;
	float SpawnChance;
	string Filter;
	ref map<string, float> Data;
}

class TerjeSAT_General
{
	private ref map<string, ref TerjeSAT_TypedTree> m_tree = new map<string, ref TerjeSAT_TypedTree>;
	void Insert(int id, TerjeScriptableArea area)
	{
		string areaType = area.GetTerjeScriptableAreaType();
		ref TerjeSAT_TypedTree typedTree;
		if (!m_tree.Find(areaType, typedTree))
		{
			typedTree = new TerjeSAT_TypedTree;
			m_tree.Set(areaType, typedTree);
		}
		
		typedTree.Insert(id, area);
	}
	
	void Remove(int id, TerjeScriptableArea area)
	{
		ref TerjeSAT_TypedTree typedTree;
		if (m_tree.Find(area.GetTerjeScriptableAreaType(), typedTree))
		{
			typedTree.Remove(id, area);
		}
	}
	
	bool TryCalculateTerjeEffectValue(EntityAI entity, vector pos, string areaType, string filterEntry, out float result)
	{
		result = 0;
		ref TerjeSAT_TypedTree typedTree;
		if (m_tree.Find(areaType, typedTree))
		{
			return typedTree.TryCalculateTerjeEffectValue(entity, pos, filterEntry, result);
		}
		
		return false;
	}
}

class TerjeSAT_TypedTree
{
	private ref TerjeSAT_Indexed m_flatTree;
	private ref TerjeSAT_GridTree m_gridTree;
	
	void TerjeSAT_TypedTree()
	{
		m_flatTree = new TerjeSAT_Indexed;
		
		if (g_Game && g_Game.IsDedicatedServer())
		{
			float gridSize = Math.Max(100, GetTerjeSettingInt(TerjeSettingsCollection.CORE_SAT_BINARY_TREE_GRID_SIZE));
			m_gridTree = new TerjeSAT_GridTree(gridSize);
		}
		else
		{
			m_gridTree = null;
		}
	}
	
	void Insert(int id, TerjeScriptableArea area)
	{
		m_flatTree.Set(id, area);
		if (m_gridTree != null)
		{
			m_gridTree.Insert(id, area);
		}
	}
	
	void Remove(int id, TerjeScriptableArea area)
	{
		m_flatTree.Remove(id);
		if (m_gridTree != null)
		{
			m_gridTree.Remove(id, area);
		}
	}
	
	bool TryCalculateTerjeEffectValue(EntityAI entity, vector pos, string filterEntry, out float result)
	{
		result = 0;
		float effectAreaResult;
		bool isIntersected = false;
		if (m_gridTree != null)
		{
			ref TerjeSAT_Indexed indexedTree;
			if (m_gridTree.Find(pos, indexedTree))
			{
				foreach (int index0, TerjeScriptableArea scriptableArea0 : indexedTree)
				{
					effectAreaResult = 0;
					if (scriptableArea0 && scriptableArea0.TryCalculateTerjeEffectValue(entity, pos, filterEntry, effectAreaResult) && effectAreaResult > result)
					{
						result = effectAreaResult;
						isIntersected = true;
					}
				}
			}
		}
		else
		{
			foreach (int index1, TerjeScriptableArea scriptableArea1 : m_flatTree)
			{
				effectAreaResult = 0;
				if (scriptableArea1 && scriptableArea1.TryCalculateTerjeEffectValue(entity, pos, filterEntry, effectAreaResult) && effectAreaResult > result)
				{
					result = effectAreaResult;
					isIntersected = true;
				}
			}
		}
		
		return isIntersected;
	}
}

class TerjeSAT_GridTree
{
	private float m_gridSize;
	private ref TerjeSAT_AxisXY m_axisXY;
	
	void TerjeSAT_GridTree(float gridSize)
	{
		m_axisXY = new TerjeSAT_AxisXY;
		m_gridSize = gridSize;
	}
	
	void Insert(int id, TerjeScriptableArea area)
	{
		vector pos = area.GetWorldPosition();
		float radius = area.GetTerjeRadius();
		int xmin = (int)((pos[0] - radius) / m_gridSize);
		int xmax = (int)((pos[0] + radius) / m_gridSize);
		int ymin = (int)((pos[2] - radius) / m_gridSize);
		int ymax = (int)((pos[2] + radius) / m_gridSize);
		
		for (int x = xmin; x <= xmax; x++)
		{
			ref TerjeSAT_AxisY axisY;
			if (!m_axisXY.Find(x, axisY))
			{
				axisY = new TerjeSAT_AxisY;
				m_axisXY.Set(x, axisY);
			}
			
			for (int y = ymin; y <= ymax; y++)
			{
				ref TerjeSAT_Indexed tree;
				if (!axisY.Find(y, tree))
				{
					tree = new TerjeSAT_Indexed;
					axisY.Set(y, tree);
				}
				
				tree.Set(id, area);
			}
		}
	}
	
	void Remove(int id, TerjeScriptableArea area)
	{
		vector pos = area.GetWorldPosition();
		float radius = area.GetTerjeRadius();
		int xmin = (int)((pos[0] - radius) / m_gridSize);
		int xmax = (int)((pos[0] + radius) / m_gridSize);
		int ymin = (int)((pos[2] - radius) / m_gridSize);
		int ymax = (int)((pos[2] + radius) / m_gridSize);
		
		for (int x = xmin; x <= xmax; x++)
		{
			ref TerjeSAT_AxisY axisY;
			if (m_axisXY.Find(x, axisY))
			{
				for (int y = ymin; y <= ymax; y++)
				{
					ref TerjeSAT_Indexed tree;
					if (axisY.Find(y, tree))
					{
						tree.Remove(id);
					}
				}	
			}
		}
	}
	
	bool Find(vector pos, out TerjeSAT_Indexed result)
	{
		int x = (int)(pos[0] / m_gridSize);
		int y = (int)(pos[2] / m_gridSize);
		
		ref TerjeSAT_AxisY axisY;
		if (m_axisXY.Find(x, axisY))
		{
			return axisY.Find(y, result);
		}
		
		result = null;
		return false;
	}
}

PluginTerjeScriptableAreas GetTerjeScriptableAreas() 
{
	return PluginTerjeScriptableAreas.Cast(GetPlugin(PluginTerjeScriptableAreas));
}