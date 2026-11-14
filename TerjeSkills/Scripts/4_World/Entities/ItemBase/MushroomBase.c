modded class MushroomBase
{
	private Particle m_terjeHighlightParticle;
	
	override bool IsTerjeClientUpdateRequired()
	{
		return true;
	}
	
	override void EEDelete(EntityAI parent)
	{
		super.EEDelete(parent);
		
		if (g_Game.IsClient() && m_terjeHighlightParticle)
		{
			m_terjeHighlightParticle.Stop();
		}
	}
	
	override void OnTerjeClientUpdate(float deltaTime)
	{
		super.OnTerjeClientUpdate(deltaTime);
		
		if (g_Game.IsClient())
		{
			bool showParticles = false;
			if (GetFoodStage() && GetHierarchyParent() == null)
			{
				FoodStageType foodStageType = GetFoodStageType();
				if (foodStageType == FoodStageType.RAW || foodStageType == FoodStageType.ROTTEN || foodStageType == FoodStageType.DRIED)
				{
					PlayerBase localPlayer = PlayerBase.Cast(g_Game.GetPlayer());
					if (localPlayer && localPlayer.GetTerjeSkills() && localPlayer.GetTerjeSkills().GetPerkLevel("surv", "mushprem") > 0)
					{
						showParticles = true;
					}
				}
			}
			
			if (showParticles)
			{
				if (!m_terjeHighlightParticle)
				{
					m_terjeHighlightParticle = ParticleManager.GetInstance().PlayOnObject(ParticleList.TERJE_SKILLS_MUSHROOMS_HIGHLIGHT, this);
				}
			}
			else
			{
				if (m_terjeHighlightParticle)
				{
					m_terjeHighlightParticle.Stop();
					m_terjeHighlightParticle = null;
				}
			}
		}
	}
}