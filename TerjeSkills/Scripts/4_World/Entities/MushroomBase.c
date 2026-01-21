modded class MushroomBase
{
	private Particle m_terjeHighlightParticle;
	
	override bool IsTerjeClientUpdateRequired()
	{
		// Only update if player is nearby and has mushroom premium perk to reduce performance impact
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		if (!player || !player.GetTerjeSkills())
			return false;

		// Check if player has mushroom premium perk
		if (player.GetTerjeSkills().GetPerkLevel("surv", "mushprem") <= 0)
			return false;

		// Only update mushrooms within reasonable distance
		float distance = vector.Distance(player.GetWorldPosition(), GetWorldPosition());
		return distance <= 50.0; // 50m range for mushroom foraging
	}
	
	override void EEDelete(EntityAI parent)
	{
		super.EEDelete(parent);
		
		if (GetGame().IsClient() && m_terjeHighlightParticle)
		{
			m_terjeHighlightParticle.Stop();
		}
	}
	
	override void OnTerjeClientUpdate(float deltaTime)
	{
		super.OnTerjeClientUpdate(deltaTime);
		
		if (GetGame().IsClient())
		{
			bool showParticles = false;
			if (GetFoodStage() && GetHierarchyParent() == null)
			{
				FoodStageType foodStageType = GetFoodStageType();
				if (foodStageType == FoodStageType.RAW || foodStageType == FoodStageType.ROTTEN || foodStageType == FoodStageType.DRIED)
				{
					PlayerBase localPlayer = PlayerBase.Cast(GetGame().GetPlayer());
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
