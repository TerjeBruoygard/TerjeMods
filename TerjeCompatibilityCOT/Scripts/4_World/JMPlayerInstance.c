modded class JMPlayerInstance
{
	private ref map<string, float> m_TerjeStats = new map<string, float>;
	private ref map<string, ref TerjePerkSync> m_TerjePerkStatus = new map<string, ref TerjePerkSync>;
	
	override void Update()
	{
		if ( g_Game.IsDedicatedServer() && ( g_Game.GetTime() - m_DataLastUpdated ) >= 100 )
		{
			if ( PlayerObject )
			{
				array<ref TerjeAdmintoolSupport_PlayerStat> registeredStats = new array<ref TerjeAdmintoolSupport_PlayerStat>;
				GetTerjeAdmintoolSupport().GetPlayerStats(registeredStats);
				foreach (ref TerjeAdmintoolSupport_PlayerStat stat : registeredStats)
				{
					m_TerjeStats[stat.GetId()] = stat.GetValue(PlayerObject);
				}

#ifdef TERJE_SKILLS_MOD
				PlayerBase player = PlayerBase.Cast(PlayerObject);
				if (player && player.GetTerjeSkills())
				{
					m_TerjePerkStatus.Clear();
					array<ref TerjeSkillCfg> skills = new array<ref TerjeSkillCfg>;
					GetTerjeSkillsRegistry().GetSkills(skills);
					foreach (ref TerjeSkillCfg skillCfg : skills)
					{
						array<ref TerjePerkCfg> perks = new array<ref TerjePerkCfg>;
						skillCfg.GetPerks(perks);
						foreach (ref TerjePerkCfg perkCfg : perks)
						{
							if (!perkCfg)
								continue;

							int perkLevel = 0;
							int perkActiveLevel = 0;
							bool canBeUpgraded = false;
							player.GetTerjeSkills().GetPerkStatus(skillCfg.GetId(), perkCfg.GetId(), perkLevel, perkActiveLevel, canBeUpgraded);
							string compositeId = skillCfg.GetId() + ":" + perkCfg.GetId();
							m_TerjePerkStatus.Insert(compositeId, new TerjePerkSync(perkLevel, perkActiveLevel, canBeUpgraded));
						}
					}
				}
#endif
			}
		}
		
		super.Update();
	}
	
	override void OnSend( ParamsWriteContext ctx, string sendToGUID = JMConstants.OFFLINE_GUID )
	{
		super.OnSend(ctx, sendToGUID);
		
		ctx.Write( m_TerjeStats.Count() );
		foreach (string id, float value : m_TerjeStats)
		{
			ctx.Write( id );
			ctx.Write( value );
		}

		ctx.Write( m_TerjePerkStatus.Count() );
		foreach (string perkId, ref TerjePerkSync perkSync : m_TerjePerkStatus)
		{
			ctx.Write(perkId);
			ctx.Write(perkSync.m_Level);
			ctx.Write(perkSync.m_ActiveLevel);
			int canUpgradeInt = 0;
			if (perkSync.m_CanUpgrade) canUpgradeInt = 1;
			else canUpgradeInt = 0;
			ctx.Write(canUpgradeInt);
		}
	}

	override bool OnReceive( ParamsReadContext ctx )
	{
		if (!super.OnReceive(ctx))
			return false;
		
		int count;
		ctx.Read( count );
		for (int i = 0; i < count; i++)
		{
			string id;
			float value;
			ctx.Read( id );
			ctx.Read( value );
			m_TerjeStats[id] = value;
		}

		int perkCount;
		ctx.Read(perkCount);
		m_TerjePerkStatus.Clear();
		for (int j = 0; j < perkCount; j++)
		{
			string perkId;
			int perkLevel;
			int perkActiveLevel;
			int canUpgradeInt;
			ctx.Read(perkId);
			ctx.Read(perkLevel);
			ctx.Read(perkActiveLevel);
			ctx.Read(canUpgradeInt);
			bool canBeUpgraded = false;
			if (canUpgradeInt != 0) canBeUpgraded = true;
			else canBeUpgraded = false;
			m_TerjePerkStatus.Insert(perkId, new TerjePerkSync(perkLevel, perkActiveLevel, canBeUpgraded));
		}
		
		return true;
	}
	
	float GetTerjeStat(string id)
	{
		float result;
		if (m_TerjeStats.Find(id, result))
		{
			return result;
		}
		
		ref TerjeAdmintoolSupport_PlayerStat stat;
		if (GetTerjeAdmintoolSupport().FindPlayerStat(id, stat))
		{
			return stat.GetMin();
		}
		
		return 0;
	}

	bool GetTerjePerkStatus(string skillId, string perkId, out int perkLevel, out int perkActiveLevel, out bool canBeUpgraded)
	{
		string compositeId = skillId + ":" + perkId;
		ref TerjePerkSync perkSync;
		if (m_TerjePerkStatus.Find(compositeId, perkSync) && perkSync)
		{
			perkLevel = perkSync.m_Level;
			perkActiveLevel = perkSync.m_ActiveLevel;
			canBeUpgraded = perkSync.m_CanUpgrade;
			return true;
		}

		perkLevel = 0;
		perkActiveLevel = 0;
		canBeUpgraded = false;
		return false;
	}
}

class TerjePerkSync
{
	int m_Level;
	int m_ActiveLevel;
	bool m_CanUpgrade;

	void TerjePerkSync(int level, int activeLevel, bool canUpgrade)
	{
		m_Level = level;
		m_ActiveLevel = activeLevel;
		m_CanUpgrade = canUpgrade;
	}
}