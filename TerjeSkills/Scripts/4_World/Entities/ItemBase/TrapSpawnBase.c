modded class TrapSpawnBase
{
	private bool m_terjeSkillCanCatchIndicator = true;
	
	override void SetupTrapPlayer( PlayerBase player, bool set_position = true )
	{
		super.SetupTrapPlayer(player, set_position);
		
		if ( g_Game.IsDedicatedServer() )
		{
			string terjeSkillName = "hunt";
			string terjePerkName = "trapexp";
			
			if (IsSurfaceWater( GetWorldPosition() ))
			{
				terjeSkillName = "fish";
				terjePerkName = "mastrap";
			}
			
			if (player && player.IsAlive() && player.GetTerjeSkills())
			{
				if (player.GetTerjeSkills().IsPerkRegistered(terjeSkillName, terjePerkName))
				{
					float perkValue;
					player.GetTerjeSkills().GetPerkValue(terjeSkillName, terjePerkName, perkValue);
					m_terjeSkillCanCatchIndicator = (Math.RandomFloat01() < perkValue);
				}
			}
		}
	}
	
	override bool SetCanCatch( out EntityAI bait )
	{
		return super.SetCanCatch(bait) && m_terjeSkillCanCatchIndicator;
	}
}