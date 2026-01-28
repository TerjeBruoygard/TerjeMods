class TerjePlayerProfile : TerjePlayerRecordsBase
{
	protected ref set<string> m_serverFlags = new set<string>;
	private int m_BloodType;
	
	bool HasServerFlag(string flag)
	{
		return m_serverFlags.Find(flag) != -1;
	}
	
	void AddServerFlag(string flag)
	{
		m_serverFlags.Insert(flag);
	}
	
	void OnNewProfileCreated()
	{
	
	}
	
	void OnExistProfileLoaded()
	{
	
	}
	
	override void OnInit()
	{
		super.OnInit();
		//RegisterRecordString("core", "1.0.0", true);
		//Add blood type record
		m_BloodType = RegisterRecordInt("c.bt", -1, true);	
	}
	
	void OnStoreSaveFile(string path)
	{
		FileSerializer ctx = new FileSerializer();
		ctx.Open(path + ".temp", FileMode.WRITE);
		if (ctx.IsOpen())
		{
			this.OnStoreSave(ctx);
			ctx.Close();
			CopyFile(path + ".temp", path);
			DeleteFile(path + ".temp");
			ClearDirtyServer();
		}
	}
	
	bool OnStoreLoadFile(string path)
	{
		if (!FileExist(path))
		{
			// Skip when profile is not exist. (New player)
			return true;
		}
		
		FileSerializer ctx = new FileSerializer();
		ctx.Open(path, FileMode.READ);
		if (!ctx.IsOpen())
		{
			return false;
		}
		
		bool result = this.OnStoreLoad(ctx);
		ctx.Close();
		return result;
	}

	void SetBloodType(int bloodType)
	{
		SetIntValue(m_BloodType, bloodType);
	}

	int GetBloodType()
	{
		return GetIntValue(m_BloodType);
	}
}