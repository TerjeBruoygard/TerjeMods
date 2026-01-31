modded class JMPlayerInstance
{
	private ref map<string, float> m_TerjeStats = new map<string, float>;
	
	override void Update()
	{
		if ( GetGame().IsDedicatedServer() && ( GetGame().GetTime() - m_DataLastUpdated ) >= 100 )
		{
			if ( PlayerObject )
			{
				array<ref TerjeAdmintoolSupport_PlayerStat> registeredStats = new array<ref TerjeAdmintoolSupport_PlayerStat>;
				GetTerjeAdmintoolSupport().GetPlayerStats(registeredStats);
				foreach (ref TerjeAdmintoolSupport_PlayerStat stat : registeredStats)
				{
					m_TerjeStats[stat.GetId()] = stat.GetValue(PlayerObject);
				}
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
	}

	override void OnRecieve( ParamsReadContext ctx )
	{
		super.OnRecieve(ctx);
		
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
}