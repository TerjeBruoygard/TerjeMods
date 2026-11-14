modded class FireplaceBase
{
	private float m_terjeSurvSkillBasedModifier = 1.0;
	
	void SetTerjeSkillSurvFuelModifier(float value)
	{
		m_terjeSurvSkillBasedModifier = value;
	}
	
	override protected float GetFuelBurnRateMP()
	{
		if (m_terjeSurvSkillBasedModifier > 1)
		{
			return super.GetFuelBurnRateMP() / m_terjeSurvSkillBasedModifier;
		}
		
		return super.GetFuelBurnRateMP();
	}
}