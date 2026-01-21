class PluginTerjeClientAnimalsCore : PluginBase 
{
	private int m_currentIndex = int.MIN;
	private float m_currentUpdateTimer = 0;
	private ref map<int, AnimalBase> m_updatableClientAnimals;
	
	override void OnInit()
	{
		super.OnInit();
		m_updatableClientAnimals = new map<int, AnimalBase>;
	}
	
	override void OnUpdate(float delta_time)
	{
		super.OnUpdate(delta_time);
		
		m_currentUpdateTimer += delta_time;
		if (m_currentUpdateTimer >= 2)
		{
			foreach (int index, AnimalBase animal : m_updatableClientAnimals)
			{
				animal.OnTerjeClientUpdate(m_currentUpdateTimer);
			}
			
			m_currentUpdateTimer = 0;
		}
	}
	
	override void OnDestroy()
	{
		super.OnDestroy();
		m_updatableClientAnimals.Clear();
	}
	
	int RegisterAnimal(AnimalBase animal)
	{
		m_currentIndex = m_currentIndex + 1;
		m_updatableClientAnimals.Insert(m_currentIndex, animal);
		return m_currentIndex;
	}
	
	void UnregisterAnimal(int index)
	{
		m_updatableClientAnimals.Remove(index);
	}
}

PluginTerjeClientAnimalsCore GetTerjeClientAnimalsCore() 
{
	return PluginTerjeClientAnimalsCore.Cast(GetPlugin(PluginTerjeClientAnimalsCore));
}
