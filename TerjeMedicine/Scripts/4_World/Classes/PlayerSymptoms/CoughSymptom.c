modded class CoughSymptom
{
	override bool IsContaminationActive()
	{
		return m_Player.GetTerjeStats().GetBiohazardLevel() >= 1;
	}
}
