modded class TerjePlayerStats
{
	private int m_TerjeMed_SleepingValue;
	private int m_TerjeMed_SleepingLevel;
	private int m_TerjeMed_SleepingTendency;
	private int m_TerjeMed_SleepingState;
	private int m_TerjeMed_SleepingIncValue;
	private int m_TerjeMed_SleepingIncTimer;
	private int m_TerjeMed_SleepingDecValue;
	private int m_TerjeMed_SleepingDecTimer;
	private int m_TerjeMed_MindValue;
	private int m_TerjeMed_MindLevel;
	private int m_TerjeMed_MindTendency;
	private int m_TerjeMed_MindDegValue;
	private int m_TerjeMed_MindDegTimer;
	private int m_TerjeMed_HematomasCount;
	private int m_TerjeMed_HematomasValue;
	private int m_TerjeMed_Bullets;
	private int m_TerjeMed_Stubs;
	private int m_TerjeMed_Viscera;
	private int m_TerjeMed_ContusionState;
	private int m_TerjeMed_ContusionValue;
	private int m_TerjeMed_ZVirusLevel;
	private int m_TerjeMed_ZVirusValue;
	private int m_TerjeMed_SepsisLevel;
	private int m_TerjeMed_SepsisValue;
	private int m_TerjeMed_PainLevel;
	private int m_TerjeMed_PainValue;
	private int m_TerjeMed_InfluenzaLevel;
	private int m_TerjeMed_InfluenzaValue;
	private int m_TerjeMed_OverdoseLevel;
	private int m_TerjeMed_OverdoseValue;
	private int m_TerjeMed_PoisonLevel;
	private int m_TerjeMed_PoisonValue;
	private int m_TerjeMed_BiohazardLevel;
	private int m_TerjeMed_BiohazardValue;
	private int m_TerjeMed_AntipoisonLevel;
	private int m_TerjeMed_AntipoisonValue;
	private int m_TerjeMed_AntibiohazardLevel;
	private int m_TerjeMed_AntibiohazardValue;
	private int m_TerjeMed_HealHematomasState;
	private int m_TerjeMed_HealHematomasValue;
	private int m_TerjeMed_PainkillerLevel;
	private int m_TerjeMed_PainkillerValue;
	private int m_TerjeMed_HemostaticLevel;
	private int m_TerjeMed_HemostaticTimer;
	private int m_TerjeMed_HemostaticValue;
	private int m_TerjeMed_BloodRegenLevel;
	private int m_TerjeMed_BloodRegenTimer;
	private int m_TerjeMed_BloodRegenValue;
	private int m_TerjeMed_DisinfectLevel;
	private int m_TerjeMed_DisinfectValue;
	private int m_TerjeMed_SutureBandagedClean;
	private int m_TerjeMed_SutureBandagedDirty;
	private int m_TerjeMed_SutureBandagedProgress;
	private int m_TerjeMed_SutureBandagedTimer;
	private int m_TerjeMed_SutureBandagedSepsisTime;
	private int m_TerjeMed_SuturesClean;
	private int m_TerjeMed_SuturesDirty;
	private int m_TerjeMed_SuturesProgress;
	private int m_TerjeMed_SuturesTimer;
	private int m_TerjeMed_SuturesSepsisTime;
	private int m_TerjeMed_BandagesClean;
	private int m_TerjeMed_BandagesDirty;
	private int m_TerjeMed_BandagesProgress;
	private int m_TerjeMed_BandagesTimer;
	private int m_TerjeMed_BandagesSepsisTime;
	private int m_TerjeMed_AntidepresantLevel;
	private int m_TerjeMed_AntidepresantValue;
	private int m_TerjeMed_AntibioticLevel;
	private int m_TerjeMed_AntibioticValue;
	private int m_TerjeMed_AntisepsisLevel;
	private int m_TerjeMed_AntisepsisValue;
	private int m_TerjeMed_ZAntidotLevel;
	private int m_TerjeMed_ZAntidotValue;
	private int m_TerjeMed_AdrenalinLevel;
	private int m_TerjeMed_AdrenalinTime;
	private int m_TerjeMed_HealContusionLevel;
	private int m_TerjeMed_HealContusionTimer;
	private int m_TerjeMed_VaccineA_State;
	private int m_TerjeMed_VaccineA_Timer;
	private int m_TerjeMed_VaccineB_State;
	private int m_TerjeMed_VaccineB_Timer;
	private int m_TerjeMed_RabiesLevel;
	private int m_TerjeMed_RabiesValue;
	private int m_TerjeMed_AntirabiesLevel;
	private int m_TerjeMed_AntirabiesValue;
	private int m_TerjeMed_VaccineC_State;
	private int m_TerjeMed_VaccineC_Timer;
	private int m_TerjeMed_ImmunityGainState;
	private int m_TerjeMed_ImmunityGainForce;
	private int m_TerjeMed_ImmunityGainTimer;
	private int m_TerjeMed_InternalImmunity;
	private int m_TerjeMed_KnockoutTimer;
	private int m_TerjeMed_KnockoutDelay;
	private int m_TerjeMed_KnockoutFinisher;
	private int m_TerjeMed_KnockoutIndicator;
	private int m_TerjeMed_HealthgainTime;
	private int m_TerjeMed_HealthgainIndicator;
	private int m_TerjeMed_HandValue;
	private int m_TerjeMed_HandLevel;
	private int m_TerjeMed_HandTendency;
	
	override void OnInit()
	{
		super.OnInit();
		
		m_TerjeMed_SleepingValue = RegisterRecordFloat("tm.slp_v", TerjeMedicineConstants.SLEEPING_MAX_VALUE, true); // Sleeping value
		m_TerjeMed_SleepingLevel = RegisterRecordInt("tm.slp_l", 1, false); // Sleeping level
		m_TerjeMed_SleepingTendency = RegisterRecordInt("tm.slp_t", 0, false); // Sleeping tendency
		m_TerjeMed_SleepingState = RegisterRecordInt("tm.slp_s", 0, false); // Sleeping state
		m_TerjeMed_SleepingIncValue = RegisterRecordFloat("tm.slp_iv", 0, true); // Sleeping increment value
		m_TerjeMed_SleepingIncTimer = RegisterRecordFloat("tm.slp_it", 0, true); // Sleeping increment time
		m_TerjeMed_SleepingDecValue = RegisterRecordFloat("tm.slp_dv", 0, true); // Sleeping decrement value
		m_TerjeMed_SleepingDecTimer = RegisterRecordFloat("tm.slp_dt", 0, true); // Sleeping decrement time
		
		m_TerjeMed_MindValue = RegisterRecordFloat("tm.mnd_v", TerjeMedicineConstants.MIND_MAX_VALUE, true); // Mind value
		m_TerjeMed_MindLevel = RegisterRecordInt("tm.mnd_l", 1, false); // Mind level
		m_TerjeMed_MindTendency = RegisterRecordInt("tm.mnd_t", 0, false); // Mind tendency
		m_TerjeMed_MindDegValue = RegisterRecordFloat("tm.mnd_dv", 0, true); // Mind degradation value
		m_TerjeMed_MindDegTimer = RegisterRecordFloat("tm.mnd_dt", 0, true); // Mind degradation time
		
		m_TerjeMed_HandValue = RegisterRecordFloat("tm.hnd_v", TerjeMedicineConstants.HAND_MAX_VALUE, true); // Hand value
		m_TerjeMed_HandLevel = RegisterRecordInt("tm.hnd_l", 1, false); // Hand level
		
		m_TerjeMed_HematomasCount = RegisterRecordInt("tm.hmt_c", 0, false); // Hematomas count
		m_TerjeMed_HematomasValue = RegisterRecordFloat("tm.hmt_v", 0, true); // Hematomas value
		
		m_TerjeMed_Bullets = RegisterRecordInt("tm.blt_c", 0, false); // Bullet wounds
		m_TerjeMed_Stubs = RegisterRecordInt("tm.stb_c", 0, false); // Stub wounds
		m_TerjeMed_Viscera = RegisterRecordBool("tm.vis", false, false); // Viscera
		
		m_TerjeMed_ContusionState = RegisterRecordBool("tm.cnc_i", false, false); // Contusion indicator
		m_TerjeMed_ContusionValue = RegisterRecordFloat("tm.cnc_v", 0, true); // Contusion value
		
		m_TerjeMed_ZVirusLevel = RegisterRecordInt("tm.zmb_l", 0, false); // Zombie Virus level
		m_TerjeMed_ZVirusValue = RegisterRecordFloat("tm.zmb_v", 0, true); // Zombie Virus value

		m_TerjeMed_SepsisLevel = RegisterRecordInt("tm.sep_l", 0, false); // Sepsis level
		m_TerjeMed_SepsisValue = RegisterRecordFloat("tm.sep_v", 0, true); // Sepsis value
		
		m_TerjeMed_PainLevel = RegisterRecordInt("tm.pain_l", 0, false); // Pain level
		m_TerjeMed_PainValue = RegisterRecordFloat("tm.pain_v", 0, true); // Pain value
		
		m_TerjeMed_InfluenzaLevel = RegisterRecordInt("tm.inf_l", 0, false); // Influenza level
		m_TerjeMed_InfluenzaValue = RegisterRecordFloat("tm.inf_v", 0, true); // Influenza value
		
		m_TerjeMed_OverdoseLevel = RegisterRecordInt("tm.ovd_l", 0, false); // Overdose level
		m_TerjeMed_OverdoseValue = RegisterRecordFloat("tm.ovd_v", 0, true); // Overdose value
		
		m_TerjeMed_PoisonLevel = RegisterRecordInt("tm.tox_l", 0, false); // Poison (toxic) Level
		m_TerjeMed_PoisonValue = RegisterRecordFloat("tm.tox_v", 0, true); // Poison (toxic) Value
		
		m_TerjeMed_BiohazardLevel = RegisterRecordInt("tm.bio_l", 0, false); // Biohazard Level
		m_TerjeMed_BiohazardValue = RegisterRecordFloat("tm.bio_v", 0, true); // Biohazard Value
		
		m_TerjeMed_AntipoisonLevel = RegisterRecordInt("tm.tox+hl", 0, false); // Antipoison level
		m_TerjeMed_AntipoisonValue = RegisterRecordFloat("tm.tox+ht", 0, true); // Antipoison timer
		
		m_TerjeMed_AntibiohazardLevel = RegisterRecordInt("tm.bio+hl", 0, false); // Anti biohazard level
		m_TerjeMed_AntibiohazardValue = RegisterRecordFloat("tm.bio+ht", 0, true); // Anti biohazard timer
		
		m_TerjeMed_HealHematomasState = RegisterRecordBool("tm.hmt+hl", false, false); // Salve indicator
		m_TerjeMed_HealHematomasValue = RegisterRecordFloat("tm.hmt+ht", 0, true); // Salve timer
		
		m_TerjeMed_PainkillerLevel = RegisterRecordInt("tm.pain+hl", 0, false); // Painkiller level
		m_TerjeMed_PainkillerValue = RegisterRecordFloat("tm.pain+ht", 0, true); // Painkiller timer
		
		m_TerjeMed_HemostaticLevel = RegisterRecordBool("tm.hms+hl", false, false); // Hemostatic indicator
		m_TerjeMed_HemostaticTimer = RegisterRecordFloat("tm.hms+ht", 0, true); // Hemostatic timer
		m_TerjeMed_HemostaticValue = RegisterRecordFloat("tm.hms+hv", 0, true); // Hemostatic value
		
		m_TerjeMed_BloodRegenLevel = RegisterRecordBool("tm.blr+hl", 0, false); // Blood regen indicator
		m_TerjeMed_BloodRegenTimer = RegisterRecordFloat("tm.blr+ht", 0, true); // Blood regen timer
		m_TerjeMed_BloodRegenValue = RegisterRecordFloat("tm.blr+hv", 0, true); // Blood regen value
		
		m_TerjeMed_DisinfectLevel = RegisterRecordBool("tm.disinf_l", false, false); // Disinfected indicator
		m_TerjeMed_DisinfectValue = RegisterRecordFloat("tm.disinf_t", 0, true); // Disinfected hands timer
		
		m_TerjeMed_SutureBandagedClean = RegisterRecordInt("tm.sutb_c", 0, false); // Sutures bandaged clean
		m_TerjeMed_SutureBandagedDirty = RegisterRecordInt("tm.sutb_d", 0, false); // Sutures bandaged dirty
		m_TerjeMed_SutureBandagedProgress = RegisterRecordFloat("tm.sutb_p", 0, true); // Sutures bandaged progress
		m_TerjeMed_SutureBandagedTimer = RegisterRecordFloat("tm.sutb_t", 0, true); // Sutures bandaged healtime
		m_TerjeMed_SutureBandagedSepsisTime = RegisterRecordFloat("tm.sutb_s", 0, true); // Sutures bandaged sepsis time
		
		m_TerjeMed_SuturesClean = RegisterRecordInt("tm.sut_c", 0, false); // Sutures clean
		m_TerjeMed_SuturesDirty = RegisterRecordInt("tm.sut_d", 0, false); // Sutures dirty
		m_TerjeMed_SuturesProgress = RegisterRecordFloat("tm.sut_p", 0, true); // Sutures progress
		m_TerjeMed_SuturesTimer = RegisterRecordFloat("tm.sut_t", 0, true); // Sutures healtime
		m_TerjeMed_SuturesSepsisTime = RegisterRecordFloat("tm.sut_s", 0, true); // Sutures sepsis timer
		
		m_TerjeMed_BandagesClean = RegisterRecordInt("tm.bndg_c", 0, false); // Clean bandage count
		m_TerjeMed_BandagesDirty = RegisterRecordInt("tm.bndg_d", 0, false); // Dirty bandage count
		m_TerjeMed_BandagesProgress = RegisterRecordFloat("tm.bndg_p", 0, true); // Bandage progress
		m_TerjeMed_BandagesTimer = RegisterRecordFloat("tm.bndg_t", 0, true); // Bandage healtime
		m_TerjeMed_BandagesSepsisTime = RegisterRecordFloat("tm.bndg_s", 0, true); // Bandage dirty sepsis timer
		
		m_TerjeMed_AntidepresantLevel = RegisterRecordInt("tm.mnd+hl", 0, false); // Antidepresant level
		m_TerjeMed_AntidepresantValue = RegisterRecordFloat("tm.mnd+ht", 0, true); // Antidepresant timer
		
		m_TerjeMed_AntibioticLevel = RegisterRecordInt("tm.inf+hl", 0, false); // Antibiotic level
		m_TerjeMed_AntibioticValue = RegisterRecordFloat("tm.inf+ht", 0, true); // Antibiotic timer
		
		m_TerjeMed_AntisepsisLevel = RegisterRecordBool("tm.sep+hl", false, false); // Anti-Sepsis level
		m_TerjeMed_AntisepsisValue = RegisterRecordFloat("tm.sep+ht", 0, true); // Anti-Sepsis timer
		
		m_TerjeMed_ZAntidotLevel = RegisterRecordBool("tm.zmv+hl", false, false); // Zomvie virus antidot level
		m_TerjeMed_ZAntidotValue = RegisterRecordFloat("tm.zmv+ht", 0, true); // Zomvie virus antidot timer
		
		m_TerjeMed_AdrenalinLevel = RegisterRecordBool("tm.adr_l", false, false); // Adrenalin indicator
		m_TerjeMed_AdrenalinTime = RegisterRecordFloat("tm.adr_t", 0, true); // Adrenalin timer
		
		m_TerjeMed_HealContusionLevel = RegisterRecordBool("tm.cnc+hl", false, false); // Contusion heal indicator
		m_TerjeMed_HealContusionTimer = RegisterRecordFloat("tm.cnc+ht", 0, true); // Contusion heal timer
		
		m_TerjeMed_VaccineA_State = RegisterRecordBool("tm.vac_ai", false, false); // Influenza vacine indicator
		m_TerjeMed_VaccineA_Timer = RegisterRecordFloat("tm.vac_at", 0, true); // Influenza vacine timer
		
		m_TerjeMed_VaccineB_State = RegisterRecordBool("tm.vac_bi", false, false); // ZVirus vacine indicator
		m_TerjeMed_VaccineB_Timer = RegisterRecordFloat("tm.vac_bt", 0, true); // ZVirus vacine timer
		
		m_TerjeMed_RabiesLevel = RegisterRecordInt("tm.rab_l", 0, false); // Rabies level
		m_TerjeMed_RabiesValue = RegisterRecordFloat("tm.rab_v", 0, true); // Rabies value
		m_TerjeMed_AntirabiesLevel = RegisterRecordInt("tm.rab+hl", 0, false); // Rabies cure level
		m_TerjeMed_AntirabiesValue = RegisterRecordFloat("tm.rab+ht", 0, true); // Rabies cure timer
		m_TerjeMed_VaccineC_State = RegisterRecordBool("tm.vac_ci", false, false); // Rabies vacine indicator
		m_TerjeMed_VaccineC_Timer = RegisterRecordFloat("tm.vac_ct", 0, true); // Rabies vacine timer
		
		m_TerjeMed_ImmunityGainState = RegisterRecordBool("tm.immgs", false, false); // Immunity gain state
		m_TerjeMed_ImmunityGainForce = RegisterRecordFloat("tm.immgf", 0, true); // Immunity gain force
		m_TerjeMed_ImmunityGainTimer = RegisterRecordFloat("tm.immgt", 0, true); // Immunity gain timer
		m_TerjeMed_InternalImmunity = RegisterRecordFloat("tm.immi", 0, true); // Immunity internal
		
		m_TerjeMed_KnockoutTimer = RegisterRecordFloat("tm.knkt", -1, true); // Knockout timer
		m_TerjeMed_KnockoutDelay = RegisterRecordFloat("tm.knkd", -1, true); // Knockout delay
		m_TerjeMed_KnockoutFinisher = RegisterRecordInt("tm.knkf", 0, true); // Knockout finishers counter
		m_TerjeMed_KnockoutIndicator = RegisterRecordBool("tm.knki", false, false); // Knockout client indicator
		
		m_TerjeMed_HealthgainTime = RegisterRecordFloat("tm.hegt", 0, true); // Health extra regeneration timer
		m_TerjeMed_HealthgainIndicator = RegisterRecordBool("tm.hegi", false, false); // Health extra regeneration indicator
	}
	
	// Hematomas
	int GetHematomasCount()
	{
		return TerjeMathHelper.ClampInt(GetIntValue(this.m_TerjeMed_HematomasCount), 0, GetTerjeSettingInt(TerjeSettingsCollection.MEDICINE_HEMATOMAS_MAX_COUNT));
	}
	float GetHematomas()
	{
		return Math.Clamp(GetFloatValue(this.m_TerjeMed_HematomasValue), 0, GetTerjeSettingInt(TerjeSettingsCollection.MEDICINE_HEMATOMAS_MAX_COUNT));
	}
	void SetHematomas(float value)
	{
		if (GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_HEMATOMAS_ENABLED) == false)
		{
			value = 0;
		}
		
		value = Math.Clamp(value, 0, GetTerjeSettingInt(TerjeSettingsCollection.MEDICINE_HEMATOMAS_MAX_COUNT));
		SetFloatValue(this.m_TerjeMed_HematomasValue, value);
		SetIntValue(this.m_TerjeMed_HematomasCount, Math.Ceil(value));
	}
	
	// Bullet wounds
	int GetBulletWounds()
	{
		return TerjeMathHelper.ClampInt(GetIntValue(this.m_TerjeMed_Bullets), 0, TerjeMedicineConstants.BULLETWOUND_MAX_VALUE);
	}
	void SetBulletWounds(int value)
	{
		if (GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_BULLETS_ENABLED) == false)
		{
			value = 0;
		}
		
		SetIntValue(this.m_TerjeMed_Bullets, TerjeMathHelper.ClampInt(value, 0, TerjeMedicineConstants.BULLETWOUND_MAX_VALUE));
	}
	
	// Stub wounds
	int GetStubWounds()
	{
		return TerjeMathHelper.ClampInt(GetIntValue(this.m_TerjeMed_Stubs), 0, TerjeMedicineConstants.STUBWOUND_MAX_VALUE);
	}
	void SetStubWounds(int value)
	{
		if (GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_STUBS_ENABLED) == false)
		{
			value = 0;
		}
		
		SetIntValue(this.m_TerjeMed_Stubs, TerjeMathHelper.ClampInt(value, 0, TerjeMedicineConstants.STUBWOUND_MAX_VALUE));
	}
	
	// Contusion
	bool GetContusion()
	{
		return GetBoolValue(this.m_TerjeMed_ContusionState);
	}
	float GetContusionValue()
	{
		return Math.Clamp(GetFloatValue(this.m_TerjeMed_ContusionValue), 0, TerjeMedicineConstants.CONTUSION_MAX_VALUE);
	}
	void SetContusionValue(float value)
	{
		if (GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_CONTUSION_ENABLED) == false)
		{
			value = 0;
		}
		
		value = Math.Clamp(value, 0, TerjeMedicineConstants.CONTUSION_MAX_VALUE);
		SetFloatValue(this.m_TerjeMed_ContusionValue, value);
		SetBoolValue(this.m_TerjeMed_ContusionState, value > 1);
	}
	
	// Zombie virus
	int GetZVirusLevel()
	{
		return TerjeMathHelper.ClampInt(GetIntValue(this.m_TerjeMed_ZVirusLevel), 0, 3);
	}
	float GetZVirusValue()
	{
		return Math.Clamp(GetFloatValue(this.m_TerjeMed_ZVirusValue), 0, TerjeMedicineConstants.ZOMBIE_VIRUS_MAX_VALUE);
	}
	void SetZVirusValue(float value)
	{
		if (GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_Z_VIRUS_ENABLED) == false)
		{
			value = 0;
		}
		
		value = Math.Clamp(value, 0, TerjeMedicineConstants.ZOMBIE_VIRUS_MAX_VALUE);
		SetFloatValue(this.m_TerjeMed_ZVirusValue, value);
		SetIntValue(this.m_TerjeMed_ZVirusLevel, TerjeMathHelper.ClampInt(value, 0, 3));
	}
	
	// Viscera
	bool GetViscera()
	{
		return GetBoolValue(this.m_TerjeMed_Viscera);
	}
	void SetViscera(bool value)
	{
		if (!GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_VISCERA_ENABLED))
		{
			value = false;
		}
		
		SetBoolValue(this.m_TerjeMed_Viscera, value);
	}
	
	// Pain level
	void SetPainLevel(int level)
	{
		SetIntValue(this.m_TerjeMed_PainLevel, TerjeMathHelper.ClampInt(level, 0, 3));
	}
	int GetPainLevel()
	{
		int result = TerjeMathHelper.ClampInt(GetIntValue(this.m_TerjeMed_PainLevel), 0, 3);
		
		if (GetPainkillerLevel() >= result)
		{
			result = 0;
		}
		
		return result;
	}
	float GetPainValue()
	{
		return Math.Clamp(GetFloatValue(this.m_TerjeMed_PainValue), 0, TerjeMedicineConstants.PAIN_MAX_VALUE);
	}
	void SetPainValue(float value)
	{
		if (GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_PAIN_ENABLED) == false)
		{
			value = 0;
		}
		
		value = Math.Clamp(value, 0, TerjeMedicineConstants.PAIN_MAX_VALUE);
		SetFloatValue(this.m_TerjeMed_PainValue, value);
	}
	
	// Influenza level
	int GetInfluenzaLevel()
	{
		return TerjeMathHelper.ClampInt(GetIntValue(this.m_TerjeMed_InfluenzaLevel), 0, 3);
	}
	float GetInfluenzaValue()
	{
		return Math.Clamp(GetFloatValue(this.m_TerjeMed_InfluenzaValue), 0, TerjeMedicineConstants.INFLUENZA_MAX_VALUE);
	}
	void SetInfluenzaValue(float value)
	{
		if (GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_INFLUENZA_ENABLED) == false)
		{
			value = 0;
		}
		
		value = Math.Clamp(value, 0, TerjeMedicineConstants.INFLUENZA_MAX_VALUE);
		SetFloatValue(this.m_TerjeMed_InfluenzaValue, value);
		SetIntValue(this.m_TerjeMed_InfluenzaLevel, TerjeMathHelper.ClampInt((int)value, 0, 3));
	}
		
	// Sepsis level
	int GetSepsisLevel()
	{
		return TerjeMathHelper.ClampInt(GetIntValue(this.m_TerjeMed_SepsisLevel), 0, 3);
	}
	float GetSepsisValue()
	{
		return Math.Clamp(GetFloatValue(this.m_TerjeMed_SepsisValue), 0, TerjeMedicineConstants.SEPSIS_MAX_VALUE);
	}
	void SetSepsisValue(float value)
	{
		if (GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_SEPSIS_ENABLED) == false)
		{
			value = 0;
		}
		
		value = Math.Clamp(value, 0, TerjeMedicineConstants.SEPSIS_MAX_VALUE);
		SetFloatValue(this.m_TerjeMed_SepsisValue, value);
		SetIntValue(this.m_TerjeMed_SepsisLevel, TerjeMathHelper.ClampInt((int)value, 0, 3));
	}
	
	// Overdose level
	int GetOverdoseLevel()
	{
		return TerjeMathHelper.ClampInt(GetIntValue(this.m_TerjeMed_OverdoseLevel), 0, 3);
	}
	float GetOverdoseValue()
	{
		return Math.Clamp(GetFloatValue(this.m_TerjeMed_OverdoseValue), 0, TerjeMedicineConstants.OVERDOSE_MAX_VALUE);
	}
	void SetOverdoseValue(float value)
	{
		if (GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_OVERDOSE_ENABLED) == false)
		{
			value = 0;
		}
		
		value = Math.Clamp(value, 0, TerjeMedicineConstants.OVERDOSE_MAX_VALUE);
		SetFloatValue(this.m_TerjeMed_OverdoseValue, value);
		SetIntValue(this.m_TerjeMed_OverdoseLevel, TerjeMathHelper.ClampInt((int)value, 0, 3));
	}
	
	// Poison (toxic)
	int GetPoisonLevel()
	{
		return TerjeMathHelper.ClampInt(GetIntValue(this.m_TerjeMed_PoisonLevel), 0, 3);
	}
	float GetPoisonValue()
	{
		return Math.Clamp(GetFloatValue(this.m_TerjeMed_PoisonValue), 0, TerjeMedicineConstants.POISON_MAX_VALUE);
	}
	void SetPoisonValue(float value)
	{
		if (GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_POSION_ENABLED) == false)
		{
			value = 0;
		}
		
		value = Math.Clamp(value, 0, TerjeMedicineConstants.POISON_MAX_VALUE);
		SetFloatValue(this.m_TerjeMed_PoisonValue, value);
		SetIntValue(this.m_TerjeMed_PoisonLevel, TerjeMathHelper.ClampInt((int)value, 0, 3));
	}
	
	// Biohazard
	int GetBiohazardLevel()
	{
		return TerjeMathHelper.ClampInt(GetIntValue(this.m_TerjeMed_BiohazardLevel), 0, 3);
	}
	float GetBiohazardValue()
	{
		return Math.Clamp(GetFloatValue(this.m_TerjeMed_BiohazardValue), 0, TerjeMedicineConstants.BIOHAZARD_MAX_VALUE);
	}
	void SetBiohazardValue(float value)
	{
		if (GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_BIOHAZARD_ENABLED) == false)
		{
			value = 0;
		}
		
		value = Math.Clamp(value, 0, TerjeMedicineConstants.BIOHAZARD_MAX_VALUE);
		SetFloatValue(this.m_TerjeMed_BiohazardValue, value);
		SetIntValue(this.m_TerjeMed_BiohazardLevel, TerjeMathHelper.ClampInt((int)value, 0, 3));
	}
	
	// Detailed Disinfected
	void SetHandLevelAndTendency(int handLevel, int handTendency)
	{
		SetIntValue(this.m_TerjeMed_HandLevel, TerjeMathHelper.ClampInt(handLevel, 1, 4));
	//	SetIntValue(this.m_TerjeMed_HandTendency, TerjeMathHelper.ClampInt(handTendency, -3, 3));
	}
	int GetHandLevel()
	{
		return TerjeMathHelper.ClampInt(GetIntValue(this.m_TerjeMed_HandLevel), 1, 4);
	}
	int GetHandTendency()
	{
		return TerjeMathHelper.ClampInt(GetIntValue(this.m_TerjeMed_HandTendency), -3, 3);
	}
	float GetHandValue()
	{
		return Math.Clamp(GetFloatValue(this.m_TerjeMed_HandValue), 0, TerjeMedicineConstants.HAND_MAX_VALUE);
	}
	void SetHandValue(float value)
	{
		if (!GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_ENABLE_DETAILED_SANITARY_DISPLAY))
		{
			return;
		}
		
		SetFloatValue(this.m_TerjeMed_HandValue, Math.Clamp(value, 0, TerjeMedicineConstants.HAND_MAX_VALUE));
	}
	
	// Mind
	void SetMindLevelAndTendency(int mindLevel, int mindTendency)
	{
		SetIntValue(this.m_TerjeMed_MindLevel, TerjeMathHelper.ClampInt(mindLevel, 1, 5));
		SetIntValue(this.m_TerjeMed_MindTendency, TerjeMathHelper.ClampInt(mindTendency, -3, 3));
	}
	int GetMindLevel()
	{
		return TerjeMathHelper.ClampInt(GetIntValue(this.m_TerjeMed_MindLevel), 1, 5);
	}
	int GetMindTendency()
	{
		return TerjeMathHelper.ClampInt(GetIntValue(this.m_TerjeMed_MindTendency), -3, 3);
	}
	float GetMindValue()
	{
		return Math.Clamp(GetFloatValue(this.m_TerjeMed_MindValue), 0, TerjeMedicineConstants.MIND_MAX_VALUE);
	}
	void SetMindValue(float value)
	{
		if (!GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_MIND_ENABLED))
		{
			return;
		}
		
		SetFloatValue(this.m_TerjeMed_MindValue, Math.Clamp(value, 0, TerjeMedicineConstants.MIND_MAX_VALUE));
	}
	void AddMindDegradation(float value, float time)
	{
		if (!GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_MIND_ENABLED))
		{
			return;
		}
		
		float v = 0;
		float t = 0;
		if (GetMindDegradation(v ,t))
		{
			if (value > v)
			{
				SetFloatValue(this.m_TerjeMed_MindDegValue, Math.Max(0, value));
				SetFloatValue(this.m_TerjeMed_MindDegTimer, Math.Max(0, time));
			}
			else if (value == v)
			{
				SetFloatValue(this.m_TerjeMed_MindDegTimer, Math.Clamp(t + time, 0, 300));
			}
		}
	}
	bool GetMindDegradation(out float value, out float time)
	{
		value = GetFloatValue(this.m_TerjeMed_MindDegValue);
		time = GetFloatValue(this.m_TerjeMed_MindDegTimer);
		return true;
	}
	void SetMindDegradation(float value, float time)
	{
		if (!GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_MIND_ENABLED))
		{
			return;
		}
		
		SetFloatValue(this.m_TerjeMed_MindDegValue, value);
		SetFloatValue(this.m_TerjeMed_MindDegTimer, time);
	}
	
	// Sleeping
	void SetSleepingState(int state)
	{
		SetIntValue(this.m_TerjeMed_SleepingState, TerjeMathHelper.ClampInt(state, (int)TerjeMedicineSleepingLevel.TERJESL_ENERGED, (int)TerjeMedicineSleepingLevel.TERJESL_PERFECT));
	}
	int GetSleepingState()
	{
		return TerjeMathHelper.ClampInt(GetIntValue(this.m_TerjeMed_SleepingState), (int)TerjeMedicineSleepingLevel.TERJESL_ENERGED, (int)TerjeMedicineSleepingLevel.TERJESL_PERFECT);
	}
	int GetSleepingLevel()
	{
		return TerjeMathHelper.ClampInt(GetIntValue(this.m_TerjeMed_SleepingLevel), 1, 5);
	}
	int GetSleepingTendency()
	{
		return TerjeMathHelper.ClampInt(GetIntValue(this.m_TerjeMed_SleepingTendency), -3, 3);
	}
	float GetSleepingValue()
	{
		return Math.Clamp(GetFloatValue(this.m_TerjeMed_SleepingValue), 0, TerjeMedicineConstants.SLEEPING_MAX_VALUE);
	}
	void SetSleepingValue(float value)
	{
		if (!GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_SLEEPING_ENABLED))
		{
			return;
		}
		
		SetFloatValue(this.m_TerjeMed_SleepingValue, Math.Clamp(value, 0, TerjeMedicineConstants.SLEEPING_MAX_VALUE));
	}
	void SetSleepingLevelAndTendency(int sleepLevel, int sleepTendency)
	{
		SetIntValue(this.m_TerjeMed_SleepingLevel, TerjeMathHelper.ClampInt(sleepLevel, 1, 5));
		SetIntValue(this.m_TerjeMed_SleepingTendency, TerjeMathHelper.ClampInt(sleepTendency, -3, 3));
	}
	void AddSleepingIncrement(float value, float time)
	{
		if (!GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_SLEEPING_ENABLED))
		{
			return;
		}
		
		float v = 0;
		float t = 0;
		if (GetSleepingIncrement(v, t))
		{
			if (value > v)
			{
				SetFloatValue(this.m_TerjeMed_SleepingIncValue, value);
				SetFloatValue(this.m_TerjeMed_SleepingIncTimer, time);
			}
			else if (value == v)
			{
				SetFloatValue(this.m_TerjeMed_SleepingIncTimer, t + time);
			}
		}
	}
	bool GetSleepingIncrement(out float value, out float time)
	{
		value = GetFloatValue(this.m_TerjeMed_SleepingIncValue);
		time = GetFloatValue(this.m_TerjeMed_SleepingIncTimer);
		return true;
	}
	void SetSleepingIncrement(float value, float time)
	{
		SetFloatValue(this.m_TerjeMed_SleepingIncValue, value);
		SetFloatValue(this.m_TerjeMed_SleepingIncTimer, time);
	}
	void AddSleepingDecrement(float value, float time)
	{
		if (!GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_SLEEPING_ENABLED))
		{
			return;
		}
		
		float v = 0;
		float t = 0;
		if (GetSleepingDecrement(v, t))
		{
			if (value > v)
			{
				SetFloatValue(this.m_TerjeMed_SleepingDecValue, value);
				SetFloatValue(this.m_TerjeMed_SleepingDecTimer, time);
			}
			else if (value == v)
			{
				SetFloatValue(this.m_TerjeMed_SleepingDecTimer, t + time);
			}
		}
	}
	bool GetSleepingDecrement(out float value, out float time)
	{
		value = GetFloatValue(this.m_TerjeMed_SleepingDecValue);
		time = GetFloatValue(this.m_TerjeMed_SleepingDecTimer);
		return true;
	}
	void SetSleepingDecrement(float value, float time)
	{
		SetFloatValue(this.m_TerjeMed_SleepingDecValue, value);
		SetFloatValue(this.m_TerjeMed_SleepingDecTimer, time);
	}
	
	
	// Anti-Poison (toxic)
	int GetAntipoisonLevel()
	{
		return TerjeMathHelper.ClampInt(GetIntValue(this.m_TerjeMed_AntipoisonLevel), 0, 3);
	}
	bool GetAntipoison(out int level, out float timer)
	{
		level = GetIntValue(this.m_TerjeMed_AntipoisonLevel);
		timer = GetFloatValue(this.m_TerjeMed_AntipoisonValue);
		return true;
	}
	void SetAntipoison(int level, float timer)
	{
		SetIntValue(this.m_TerjeMed_AntipoisonLevel, TerjeMathHelper.ClampInt(level, 0, 3));
		SetFloatValue(this.m_TerjeMed_AntipoisonValue, Math.Max(timer, 0));
	}
	
	// Anti-Biohazard
	int GetAntibiohazardLevel()
	{
		return TerjeMathHelper.ClampInt(GetIntValue(this.m_TerjeMed_AntibiohazardLevel), 0, 3);
	}
	bool GetAntibiohazard(out int level, out float timer)
	{
		level = GetIntValue(this.m_TerjeMed_AntibiohazardLevel);
		timer = GetFloatValue(this.m_TerjeMed_AntibiohazardValue);
		return true;
	}
	void SetAntibiohazard(int level, float timer)
	{
		SetIntValue(this.m_TerjeMed_AntibiohazardLevel, TerjeMathHelper.ClampInt(level, 0, 3));
		SetFloatValue(this.m_TerjeMed_AntibiohazardValue, Math.Max(timer, 0));
	}
	
	// Salve
	bool GetSalve()
	{
		return GetBoolValue(this.m_TerjeMed_HealHematomasState);
	}
	float GetSalveValue()
	{
		return GetFloatValue(this.m_TerjeMed_HealHematomasValue);
	}
	void SetSalveValue(float value)
	{
		value = Math.Max(value, 0);
		SetFloatValue(this.m_TerjeMed_HealHematomasValue, value);
		SetBoolValue(this.m_TerjeMed_HealHematomasState, value > 0);
	}
	
	// Painkiller
	int GetPainkillerLevel()
	{
		return TerjeMathHelper.ClampInt(GetIntValue(this.m_TerjeMed_PainkillerLevel), 0, 3);
	}
	bool GetPainkiller(out int level, out float timer)
	{
		level = GetIntValue(this.m_TerjeMed_PainkillerLevel);
		timer = GetFloatValue(this.m_TerjeMed_PainkillerValue);
		return true;
	}
	void SetPainkiller(int level, float timer)
	{
		SetIntValue(this.m_TerjeMed_PainkillerLevel, TerjeMathHelper.ClampInt(level, 0, 3));
		SetFloatValue(this.m_TerjeMed_PainkillerValue, Math.Max(timer, 0));
	}
	
	// Hemostatic
	bool GetHemostatic()
	{
		return GetBoolValue(this.m_TerjeMed_HemostaticLevel);
	}
	bool GetHemostatic(out float value, out float timer)
	{
		value = GetFloatValue(this.m_TerjeMed_HemostaticValue);
		timer = GetFloatValue(this.m_TerjeMed_HemostaticTimer);
		return true;
	}
	void SetHemostatic(float value, float timer)
	{
		if (value > 0 && timer > 0)
		{
			SetFloatValue(this.m_TerjeMed_HemostaticTimer, Math.Max(timer, 0));
			SetFloatValue(this.m_TerjeMed_HemostaticValue, Math.Clamp(value, 0, 1));
			SetBoolValue(this.m_TerjeMed_HemostaticLevel, true);
		}
		else
		{
			SetFloatValue(this.m_TerjeMed_HemostaticTimer, 0);
			SetFloatValue(this.m_TerjeMed_HemostaticValue, 0);
			SetBoolValue(this.m_TerjeMed_HemostaticLevel, false);
		}
	}
	
	// Blood regen
	bool GetBloodRegen()
	{
		return GetBoolValue(this.m_TerjeMed_BloodRegenLevel);
	}
	bool GetBloodRegen(out float value, out float timer)
	{
		value = GetFloatValue(this.m_TerjeMed_BloodRegenValue);
		timer = GetFloatValue(this.m_TerjeMed_BloodRegenTimer);
		return true;
	}
	void SetBloodRegen(float value, float timer)
	{
		if (value > 0 && timer > 0)
		{
			SetFloatValue(this.m_TerjeMed_BloodRegenTimer, Math.Max(timer, 0));
			SetFloatValue(this.m_TerjeMed_BloodRegenValue, Math.Max(value, 0));
			SetBoolValue(this.m_TerjeMed_BloodRegenLevel, true);
		}
		else
		{
			SetFloatValue(this.m_TerjeMed_BloodRegenTimer, 0);
			SetFloatValue(this.m_TerjeMed_BloodRegenValue, 0);
			SetBoolValue(this.m_TerjeMed_BloodRegenLevel, false);
		}
	}
	
	// Disinfected
	bool GetDisinfected()
	{
		return GetBoolValue(this.m_TerjeMed_DisinfectLevel);
	}
	void SetDisinfected(bool value)
	{
		SetBoolValue(this.m_TerjeMed_DisinfectLevel, value);
	}
	float GetDisinfectedHands()
	{
		return Math.Max(GetFloatValue(this.m_TerjeMed_DisinfectValue), 0);
	}
	void SetDisinfectedHands(float value)
	{
		SetFloatValue(this.m_TerjeMed_DisinfectValue, Math.Max(value, 0));
	}
	
	// Sutures (open)
	int GetSuturesTotal()
	{
		return GetSuturesClean() + GetSuturesDirty();
	}
	int GetSuturesClean()
	{
		return TerjeMathHelper.ClampInt(GetIntValue(this.m_TerjeMed_SuturesClean), 0, TerjeMedicineConstants.SUTURES_MAX_VALUE);
	}
	void SetSuturesClean(int value)
	{
		if (GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_SUTURES_ENABLED) == false)
		{
			value = 0;
		}
		
		SetIntValue(this.m_TerjeMed_SuturesClean, TerjeMathHelper.ClampInt(value, 0, TerjeMedicineConstants.SUTURES_MAX_VALUE));
	}
	int GetSuturesDirty()
	{
		return TerjeMathHelper.ClampInt(GetIntValue(this.m_TerjeMed_SuturesDirty), 0, TerjeMedicineConstants.SUTURES_MAX_VALUE);
	}
	void SetSuturesDirty(int value)
	{
		if (GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_SUTURES_ENABLED) == false)
		{
			value = 0;
		}
		
		SetIntValue(this.m_TerjeMed_SuturesDirty, TerjeMathHelper.ClampInt(value, 0, TerjeMedicineConstants.SUTURES_MAX_VALUE));
	}
	float GetSuturesProgress()
	{
		return Math.Max(GetFloatValue(this.m_TerjeMed_SuturesProgress), 0);
	}
	void SetSuturesProgress(float value)
	{
		SetFloatValue(this.m_TerjeMed_SuturesProgress, Math.Max(value, 0));
	}
	float GetSuturesHealtime()
	{
		return Math.Max(GetFloatValue(this.m_TerjeMed_SuturesTimer), 0);
	}
	void SetSuturesHealtime(float value)
	{
		SetFloatValue(this.m_TerjeMed_SuturesTimer, Math.Max(value, 0));
	}
	float GetSuturesSepsisTimer()
	{
		return Math.Max(GetFloatValue(this.m_TerjeMed_SuturesSepsisTime), 0);
	}
	void SetSuturesSepsisTimer(float value)
	{
		SetFloatValue(this.m_TerjeMed_SuturesSepsisTime, Math.Max(value, 0));
	}
	
	// Sutures (bandaged)
	int GetSuturesBandagedTotal()
	{
		return GetSuturesBandagedClean() + GetSuturesBandagedDirty();
	}
	int GetSuturesBandagedClean()
	{
		return TerjeMathHelper.ClampInt(GetIntValue(this.m_TerjeMed_SutureBandagedClean), 0, TerjeMedicineConstants.BANDAGES_MAX_VALUE);
	}
	void SetSuturesBandagedClean(int value)
	{
		SetIntValue(this.m_TerjeMed_SutureBandagedClean, TerjeMathHelper.ClampInt(value, 0, TerjeMedicineConstants.BANDAGES_MAX_VALUE));
	}
	int GetSuturesBandagedDirty()
	{
		return TerjeMathHelper.ClampInt(GetIntValue(this.m_TerjeMed_SutureBandagedDirty), 0, TerjeMedicineConstants.BANDAGES_MAX_VALUE);
	}
	void SetSuturesBandagedDirty(int value)
	{
		SetIntValue(this.m_TerjeMed_SutureBandagedDirty, TerjeMathHelper.ClampInt(value, 0, TerjeMedicineConstants.BANDAGES_MAX_VALUE));
	}
	float GetSuturesBandagedProgress()
	{
		return Math.Max(GetFloatValue(this.m_TerjeMed_SutureBandagedProgress), 0);
	}
	void SetSuturesBandagedProgress(float value)
	{
		SetFloatValue(this.m_TerjeMed_SutureBandagedProgress, Math.Max(value, 0));
	}
	float GetSuturesBandagedHealtime()
	{
		return Math.Max(GetFloatValue(this.m_TerjeMed_SutureBandagedTimer), 0);
	}
	void SetSuturesBandagedHealtime(float value)
	{
		SetFloatValue(this.m_TerjeMed_SutureBandagedTimer, Math.Max(value, 0));
	}
	float GetSuturesBandagedSepsisTimer()
	{
		return Math.Max(GetFloatValue(this.m_TerjeMed_SutureBandagedSepsisTime), 0);
	}
	void SetSuturesBandagedSepsisTimer(float value)
	{
		SetFloatValue(this.m_TerjeMed_SutureBandagedSepsisTime, Math.Max(value, 0));
	}
	
	// Bandages
	int GetBandagesTotal()
	{
		return GetBandagesClean() + GetBandagesDirty();
	}
	int GetBandagesClean()
	{
		return TerjeMathHelper.ClampInt(GetIntValue(this.m_TerjeMed_BandagesClean), 0, TerjeMedicineConstants.BANDAGES_MAX_VALUE);
	}
	void SetBandagesClean(int value)
	{
		SetIntValue(this.m_TerjeMed_BandagesClean, TerjeMathHelper.ClampInt(value, 0, TerjeMedicineConstants.BANDAGES_MAX_VALUE));
	}
	int GetBandagesDirty()
	{
		return TerjeMathHelper.ClampInt(GetIntValue(this.m_TerjeMed_BandagesDirty), 0, TerjeMedicineConstants.BANDAGES_MAX_VALUE);
	}
	void SetBandagesDirty(int value)
	{
		SetIntValue(this.m_TerjeMed_BandagesDirty, TerjeMathHelper.ClampInt(value, 0, TerjeMedicineConstants.BANDAGES_MAX_VALUE));
	}
	float GetBandagesProgress()
	{
		return Math.Max(GetFloatValue(this.m_TerjeMed_BandagesProgress), 0);
	}
	void SetBandagesProgress(float value)
	{
		SetFloatValue(this.m_TerjeMed_BandagesProgress, Math.Max(value, 0));
	}
	float GetBandagesHealtime()
	{
		return Math.Max(GetFloatValue(this.m_TerjeMed_BandagesTimer), 0);
	}
	void SetBandagesHealtime(float value)
	{
		SetFloatValue(this.m_TerjeMed_BandagesTimer, Math.Max(value, 0));
	}
	float GetBandagesSepsisTimer()
	{
		return Math.Max(GetFloatValue(this.m_TerjeMed_BandagesSepsisTime), 0);
	}
	void SetBandagesSepsisTimer(float value)
	{
		SetFloatValue(this.m_TerjeMed_BandagesSepsisTime, Math.Max(value, 0));
	}
	
	// Antidepresant
	int GetAntidepresantLevel()
	{
		return TerjeMathHelper.ClampInt(GetIntValue(this.m_TerjeMed_AntidepresantLevel), 0, 3);
	}
	bool GetAntidepresant(out int level, out float timer)
	{
		level = GetIntValue(this.m_TerjeMed_AntidepresantLevel);
		timer = GetFloatValue(this.m_TerjeMed_AntidepresantValue);
		return true;
	}
	void SetAntidepresant(int level, float timer)
	{
		SetIntValue(this.m_TerjeMed_AntidepresantLevel, TerjeMathHelper.ClampInt(level, 0, 3));
		SetFloatValue(this.m_TerjeMed_AntidepresantValue, Math.Max(timer, 0));
	}
	
	// Antibiotic
	int GetAntibioticLevel()
	{
		return TerjeMathHelper.ClampInt(GetIntValue(this.m_TerjeMed_AntibioticLevel), 0, 3);
	}
	bool GetAntibiotic(out int level, out float timer)
	{
		level = GetIntValue(this.m_TerjeMed_AntibioticLevel);
		timer = GetFloatValue(this.m_TerjeMed_AntibioticValue);
		return true;
	}
	void SetAntibiotic(int level, float timer)
	{
		SetIntValue(this.m_TerjeMed_AntibioticLevel, TerjeMathHelper.ClampInt(level, 0, 3));
		SetFloatValue(this.m_TerjeMed_AntibioticValue, Math.Max(timer, 0));
	}
	
	// Anti-Sepsis
	bool GetAntisepsis()
	{
		return GetBoolValue(this.m_TerjeMed_AntisepsisLevel);
	}
	float GetAntisepsisValue()
	{
		return GetFloatValue(this.m_TerjeMed_AntisepsisValue);
	}
	void SetAntisepsisValue(float value)
	{
		SetBoolValue(this.m_TerjeMed_AntisepsisLevel, value > 0);
		SetFloatValue(this.m_TerjeMed_AntisepsisValue, Math.Max(value, 0));
	}
	
	// Zombie virus antidot
	bool GetZAntidot()
	{
		return GetBoolValue(this.m_TerjeMed_ZAntidotLevel);
	}
	float GetZAntidotValue()
	{
		return GetFloatValue(this.m_TerjeMed_ZAntidotValue);
	}
	void SetZAntidotValue(float value)
	{
		SetBoolValue(this.m_TerjeMed_ZAntidotLevel, value > 0);
		SetFloatValue(this.m_TerjeMed_ZAntidotValue, Math.Max(value, 0));
	}
	
	// Adrenalin
	bool GetAdrenalin()
	{
		return GetBoolValue(this.m_TerjeMed_AdrenalinLevel);
	}
	float GetAdrenalinValue()
	{
		return GetFloatValue(this.m_TerjeMed_AdrenalinTime);
	}
	void SetAdrenalinValue(float value)
	{
		value = Math.Max(value, 0);
		SetFloatValue(this.m_TerjeMed_AdrenalinTime, value);
		SetBoolValue(this.m_TerjeMed_AdrenalinLevel, value > 0);
	}
	
	// Contusion heal
	bool GetContusionHeal()
	{
		return GetBoolValue(this.m_TerjeMed_HealContusionLevel);
	}
	float GetContusionHealValue()
	{
		return GetFloatValue(this.m_TerjeMed_HealContusionTimer);
	}
	void SetContusionHealValue(float value)
	{
		value = Math.Max(value, 0);
		SetFloatValue(this.m_TerjeMed_HealContusionTimer, value);
		SetBoolValue(this.m_TerjeMed_HealContusionLevel, value > 0);
	}
	
	// Influenza vacine
	bool GetInfluenzaVacine()
	{
		return GetBoolValue(this.m_TerjeMed_VaccineA_State);
	}
	float GetInfluenzaVacineValue()
	{
		return GetFloatValue(this.m_TerjeMed_VaccineA_Timer);
	}
	void SetInfluenzaVacineValue(float value)
	{
		value = Math.Max(value, 0);
		SetFloatValue(this.m_TerjeMed_VaccineA_Timer, value);
		SetBoolValue(this.m_TerjeMed_VaccineA_State, value > 0);
	}
	
	// ZVirus vacine
	bool GetZVirusVacine()
	{
		return GetBoolValue(this.m_TerjeMed_VaccineB_State);
	}
	float GetZVirusVacineValue()
	{
		return GetFloatValue(this.m_TerjeMed_VaccineB_Timer);
	}
	void SetZVirusVacineValue(float value)
	{
		value = Math.Max(value, 0);
		SetFloatValue(this.m_TerjeMed_VaccineB_Timer, value);
		SetBoolValue(this.m_TerjeMed_VaccineB_State, value > 0);
	}
	
	// Rabies level
	int GetRabiesLevel()
	{
		return TerjeMathHelper.ClampInt(GetIntValue(this.m_TerjeMed_RabiesLevel), 0, 3);
	}
	float GetRabiesValue()
	{
		return Math.Clamp(GetFloatValue(this.m_TerjeMed_RabiesValue), 0, TerjeMedicineConstants.RABIES_MAX_VALUE);
	}
	void SetRabiesValue(float value)
	{
		if (GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_RABIES_ENABLED) == false)
		{
			value = 0;
		}
		
		value = Math.Clamp(value, 0, TerjeMedicineConstants.RABIES_MAX_VALUE);
		SetFloatValue(this.m_TerjeMed_RabiesValue, value);
		SetIntValue(this.m_TerjeMed_RabiesLevel, TerjeMathHelper.ClampInt((int)value, 0, 3));
	}
	
	// Rabies cure
	int GetRabiesCureLevel()
	{
		return TerjeMathHelper.ClampInt(GetIntValue(this.m_TerjeMed_AntirabiesLevel), 0, 3);
	}
	bool GetRabiesCure(out int level, out float timer)
	{
		level = GetIntValue(this.m_TerjeMed_AntirabiesLevel);
		timer = GetFloatValue(this.m_TerjeMed_AntirabiesValue);
		return true;
	}
	void SetRabiesCure(int level, float timer)
	{
		SetIntValue(this.m_TerjeMed_AntirabiesLevel, TerjeMathHelper.ClampInt(level, 0, 3));
		SetFloatValue(this.m_TerjeMed_AntirabiesValue, Math.Max(timer, 0));
	}
	
	// Rabies vacine
	bool GetRabiesVacine()
	{
		return GetBoolValue(this.m_TerjeMed_VaccineC_State);
	}
	float GetRabiesVacineValue()
	{
		return GetFloatValue(this.m_TerjeMed_VaccineC_Timer);
	}
	void SetRabiesVacineValue(float value)
	{
		value = Math.Max(value, 0);
		SetFloatValue(this.m_TerjeMed_VaccineC_Timer, value);
		SetBoolValue(this.m_TerjeMed_VaccineC_State, value > 0);
	}
	
	// Immunity gain
	bool GetImmunityGain()
	{
		return GetBoolValue(this.m_TerjeMed_ImmunityGainState);
	}
	
	void GetImmunityGainValue(out float force, out float timer)
	{
		force = GetFloatValue(this.m_TerjeMed_ImmunityGainForce);
		timer = GetFloatValue(this.m_TerjeMed_ImmunityGainTimer);
	}
	
	void SetImmunityGainValue(float force, float timer)
	{
		SetFloatValue(this.m_TerjeMed_ImmunityGainForce, force);
		SetFloatValue(this.m_TerjeMed_ImmunityGainTimer, timer);
		SetBoolValue(this.m_TerjeMed_ImmunityGainState, ((timer > 0) && (force > 0)));
	}
	
	// Internal immunity
	void SetInternalImmunity(float value)
	{
		SetFloatValue(m_TerjeMed_InternalImmunity, Math.Clamp(value, 0, 1));
	}
	
	float GetInternalImmunity()
	{
		return Math.Clamp(GetFloatValue(m_TerjeMed_InternalImmunity), 0, 1);
	}
	
	// Knockout
	void SetKnockoutTimer(float value)
	{
		SetFloatValue(m_TerjeMed_KnockoutTimer, value);
		SetBoolValue(m_TerjeMed_KnockoutIndicator, (value > 0));
	}
	
	float GetKnockoutTimer()
	{
		return GetFloatValue(m_TerjeMed_KnockoutTimer);
	}
	
	bool IsInKnockout()
	{
		return GetBoolValue(m_TerjeMed_KnockoutIndicator);
	}
	
	void SetKnockoutDelay(float value)
	{
		SetFloatValue(m_TerjeMed_KnockoutDelay, value);
	}
	
	float GetKnockoutDelay()
	{
		return GetFloatValue(m_TerjeMed_KnockoutDelay);
	}
	
	void IncrementKnockoutFinisher()
	{
		SetIntValue(m_TerjeMed_KnockoutFinisher, GetIntValue(m_TerjeMed_KnockoutFinisher) + 1);
	}
	
	void ResetKnockoutFinisher()
	{
		SetIntValue(m_TerjeMed_KnockoutFinisher, 0);
	}
	
	int GetKnockoutFinisher()
	{
		return GetIntValue(m_TerjeMed_KnockoutFinisher);
	}
	
	// Health extra regen
	void SetHealthExtraRegenTimer(float value)
	{
		SetFloatValue(m_TerjeMed_HealthgainTime, value);
		SetBoolValue(m_TerjeMed_HealthgainIndicator, value > 0);
	}
	
	float GetHealthExtraRegenTimer()
	{
		return GetFloatValue(m_TerjeMed_HealthgainTime);
	}
	
	bool GetHealthExtraRegen()
	{
		return GetBoolValue(m_TerjeMed_HealthgainIndicator);
	}
}
