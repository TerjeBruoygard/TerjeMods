modded class CoughSymptom
{
	override bool IsContaminationActive()
	{
		if (m_Player.GetTerjeStats().GetBiohazardValue() > 0)
			return true;
		return false;
	}
}
