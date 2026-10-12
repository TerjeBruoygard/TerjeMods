modded class TerjePlayerProfile
{
	private int m_FirstName;
	private int m_LastName;
	private int m_CharacterClassname;
	private int m_PersistentBeardLevelSelected;
	private int m_PersistentBeardLevelDeath;
	private int m_SoulsCount;
	private int m_LastLoadoutId;
	private int m_LastLoadoutSelections;
	private int m_SkillsSelectedFlag;
	private int m_LastRespawnId;
	private int m_RespawnObjectsClassname;
	private int m_RespawnObjectsPosition;
	private int m_RespawnObjectsMetadata;
	private int m_RespawnObjectsPlayerPos;
	private int m_RespawnObjectsPlayerOri;
	private int m_RespawnLastDeathPoint;
	private int m_ServerRulesAccepted;
	private int m_PassportSpawnOnceMarker;
	
	override void OnInit()
	{
		super.OnInit();

		m_FirstName = RegisterRecordString("tp.fname", "", true);
		m_LastName = RegisterRecordString("tp.lname", "", true);
		m_CharacterClassname = RegisterRecordString("tp.cname", "", true);
		m_PersistentBeardLevelSelected = RegisterRecordInt("tp.pbls", 0, true);
		m_PersistentBeardLevelDeath = RegisterRecordInt("tp.pbld", -1, true);
		m_SoulsCount = RegisterRecordInt("tp.slc", -1, false);
		m_LastLoadoutId = RegisterRecordString("tp.llid", "", true);
		m_LastLoadoutSelections = RegisterRecordString("tp.llsel", "", true);
		m_SkillsSelectedFlag = RegisterRecordInt("tp.ssf", 0, true);
		m_LastRespawnId = RegisterRecordString("tp.lrid", "", true);
		m_RespawnObjectsClassname = RegisterRecordStringMap("tp.rsoc", true);
		m_RespawnObjectsPosition = RegisterRecordStringMap("tp.rsop", true);
		m_RespawnObjectsMetadata = RegisterRecordStringMap("tp.rsom", true);
		m_RespawnObjectsPlayerPos = RegisterRecordStringMap("tp.rspp", true);
		m_RespawnObjectsPlayerOri = RegisterRecordStringMap("tp.rspo", true);
		m_RespawnLastDeathPoint = RegisterRecordString("tp.rldp", "", true);
		m_ServerRulesAccepted = RegisterRecordBool("tp.sra", false, true);
		m_PassportSpawnOnceMarker = RegisterRecordBool("tp.psom", false, true);
	}
	
	override void OnNewProfileCreated()
	{
		super.OnNewProfileCreated();
		
		if (g_Game && g_Game.IsDedicatedServer())
		{
			if (GetTerjeSettingBool(TerjeSettingsCollection.STARTSCREEN_SKILLS_PAGE_ENABLED))
			{
				SetSkillsSelectedFlag(1);
			}
			
			SetSoulsCount(GetTerjeSettingInt(TerjeSettingsCollection.STARTSCREEN_SOULS_INIT_COUNT));
			
			if (GetTerjeSettingBool(TerjeSettingsCollection.STARTSCREEN_PASSPORT_SPAWN_ONCE))
			{
				SetPassportSpawnOnceMarker(true);
			}
		}
	}
	
	override void OnExistProfileLoaded()
	{
		super.OnExistProfileLoaded();
		
		if (g_Game && g_Game.IsDedicatedServer())
		{
			if (GetIntValue(m_SoulsCount) == -1)
			{
				SetSoulsCount(GetTerjeSettingInt(TerjeSettingsCollection.STARTSCREEN_SOULS_INIT_COUNT));
			}
		}
	}
	
	void SetFirstName(string firstName)
	{
		SetStringValue(m_FirstName, firstName);
	}
	
	string GetFirstName()
	{
		return GetStringValue(m_FirstName);
	}
	
	void SetLastName(string lastName)
	{
		SetStringValue(m_LastName, lastName);
	}
	
	string GetLastName()
	{
		return GetStringValue(m_LastName);
	}
	
	void SetCharacterClassname(string className)
	{
		SetStringValue(m_CharacterClassname, className);
	}
	
	string GetCharacterClassname()
	{
		return GetStringValue(m_CharacterClassname);
	}

	void SetPersistentBeardLevelSelected(int value)
	{
		SetIntValue(m_PersistentBeardLevelSelected, TerjeMathHelper.ClampInt(value, 0, 3));
	}

	int GetPersistentBeardLevelSelected()
	{
		return TerjeMathHelper.ClampInt(GetIntValue(m_PersistentBeardLevelSelected), 0, 3);
	}

	void SetPersistentBeardLevelDeath(int value)
	{
		SetIntValue(m_PersistentBeardLevelDeath, TerjeMathHelper.ClampInt(value, -1, 3));
	}

	int GetPersistentBeardLevelDeath()
	{
		return TerjeMathHelper.ClampInt(GetIntValue(m_PersistentBeardLevelDeath), -1, 3);
	}

	void SetSoulsCount(int value)
	{
		int max = GetTerjeSettingInt(TerjeSettingsCollection.STARTSCREEN_SOULS_MAXCOUNT);
		if (max < 1)
		{
			max = 1;
		}
		
		SetIntValue(m_SoulsCount, TerjeMathHelper.ClampInt(value, 0, max));
	}
	
	int GetSoulsCount()
	{
		int max = GetTerjeSettingInt(TerjeSettingsCollection.STARTSCREEN_SOULS_MAXCOUNT);
		if (max < 1)
		{
			max = 1;
		}
		
		return TerjeMathHelper.ClampInt(GetIntValue(m_SoulsCount), 0, max);
	}
	
	void SetLastLoadout(string loadoutId, string selections)
	{
		SetStringValue(m_LastLoadoutId, loadoutId);
		SetStringValue(m_LastLoadoutSelections, selections);
	}
	
	void GetLastLoadout(out string loadoutId, out string selections)
	{
		loadoutId = GetStringValue(m_LastLoadoutId);
		selections = GetStringValue(m_LastLoadoutSelections);
	}
	
	void SetSkillsSelectedFlag(int flag)
	{
		SetIntValue(m_SkillsSelectedFlag, flag);
	}
	
	int GetSkillsSelectedFlag()
	{
		return GetIntValue(m_SkillsSelectedFlag);
	}
	
	void SetLastRespawnId(string respawnId)
	{
		SetStringValue(m_LastRespawnId, respawnId);
	}
	
	string GetLastRespawnId()
	{
		return GetStringValue(m_LastRespawnId);
	}
	
	bool HasRespawnObjectData(string respawnId)
	{
		return ContainsMapKey(m_RespawnObjectsClassname, respawnId);
	}
	
	void SetRespawnObjectData(string respawnId, string classname, string metadata, vector objectPos, vector playerPos, vector playerOri)
	{
		SetStringMapValue(m_RespawnObjectsClassname, respawnId, classname);
		SetStringMapValue(m_RespawnObjectsMetadata, respawnId, metadata);
		SetStringMapValue(m_RespawnObjectsPosition, respawnId, objectPos.ToString(false));
		SetStringMapValue(m_RespawnObjectsPlayerPos, respawnId, playerPos.ToString(false));
		SetStringMapValue(m_RespawnObjectsPlayerOri, respawnId, playerOri.ToString(false));
	}
	
	bool FindRespawnObjectData(string respawnId, out string classname, out string metadata, out vector objectPos, out vector playerPos, out vector playerOri)
	{
		string value;
		if (!FindStringMapValue(m_RespawnObjectsClassname, respawnId, value))
			return false;
		
		classname = value;
		if (!FindStringMapValue(m_RespawnObjectsMetadata, respawnId, value))
			return false;
		
		metadata = value;
		if (!FindStringMapValue(m_RespawnObjectsPosition, respawnId, value))
			return false;
		
		objectPos = value.ToVector();
		if (!FindStringMapValue(m_RespawnObjectsPlayerPos, respawnId, value))
			return false;
		
		playerPos = value.ToVector();
		if (!FindStringMapValue(m_RespawnObjectsPlayerOri, respawnId, value))
			return false;
		
		playerOri = value.ToVector();
		return true;
	}
	
	void DeleteRespawnObjectData(string respawnId)
	{
		RemoveMapValue(m_RespawnObjectsClassname, respawnId);
		RemoveMapValue(m_RespawnObjectsMetadata, respawnId);
		RemoveMapValue(m_RespawnObjectsPosition, respawnId);
		RemoveMapValue(m_RespawnObjectsPlayerPos, respawnId);
		RemoveMapValue(m_RespawnObjectsPlayerOri, respawnId);
	}
	
	void SetRespawnLastDeathPoint(vector value)
	{
		SetStringValue(m_RespawnLastDeathPoint, value.ToString(false));
	}
	
	bool GetRespawnLastDeathPoint(out vector result)
	{
		string resultStr = GetStringValue(m_RespawnLastDeathPoint);
		if (resultStr != string.Empty)
		{
			result = resultStr.ToVector();
			return true;
		}
		
		return false;
	}
	
	void SetServerRulesAccepted(bool value)
	{
		SetBoolValue(m_ServerRulesAccepted, value);
	}
	
	bool GetServerRulesAccepted()
	{
		return GetBoolValue(m_ServerRulesAccepted);
	}
	
	void SetPassportSpawnOnceMarker(bool value)
	{
		SetBoolValue(m_PassportSpawnOnceMarker, value);
	}
	
	bool GetPassportSpawnOnceMarker()
	{
		return GetBoolValue(m_PassportSpawnOnceMarker);
	}
}