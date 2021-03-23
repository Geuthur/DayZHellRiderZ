class HRZ_PPEffects extends PPEffects
{
	
	static int m_RotiBlurKokain;
	static int m_RotiBlurCrystal;
	
	static int m_DynamicKokain;
	static int m_DynamicCrystal;
	
	static int m_ChromAbersKokain;
	static int m_ChromAbersCrystal;
	
	static int m_RadialBlurKokain;
	static int m_RadialBlurCrystal;
	
	static Material m_MatRotiBlur;
	static Material m_MatDynamic;
	static Material m_MatChromAbers;
	static Material m_MatRadialBlur;

	static ref array<int> m_RotiBlurEffects;
	static ref map<int, ref array<float>> m_RotiBlurValues;
	
	static ref array<float>> m_DynamicValues;
	
	static ref array<int> m_ChromAbersEffects;
	static ref map<int, ref array<float>> m_ChromAbersValues;
	
	static ref array<int> m_RadialBlurEffects;
	static ref map<int, ref array<float>> m_RadialBlurValues;
	
	override static void Init()
	{
		if ( m_RotiBlurEffects )
		{
			delete m_RotiBlurEffects;
		}
		if ( m_RotiBlurValues )
		{
			delete m_RotiBlurValues;
		}
		if ( m_DynamicValues )
		{
			delete m_DynamicValues;
		}
		if ( m_ChromAbersEffects )
		{
			delete m_ChromAbersEffects;
		}
		if ( m_ChromAbersValues )
		{
			delete m_ChromAbersValues;
		}
		if ( m_RadialBlurEffects )
		{
			delete m_RadialBlurEffects;
		}
		if ( m_RadialBlurValues )
		{
			delete m_RadialBlurValues;
		}
		
		
		m_MatRotiBlur = GetGame().GetWorld().GetMaterial("graphics/materials/postprocess/rotblur");
		m_MatDynamic = GetGame().GetWorld().GetMaterial("graphics/materials/postprocess/dynamicblur");
		m_MatChromAbers = GetGame().GetWorld().GetMaterial("graphics/materials/postprocess/chromaber");
		m_MatRadialBlur = GetGame().GetWorld().GetMaterial("graphics/materials/postprocess/radialblur");
		
		m_RotiBlurEffects = new array<int>;
		m_RotiBlurValues = new map<int, ref array<float>>;
		
		m_ChromAbersEffects = new array<int>;
		m_ChromAbersValues = new map<int, ref array<float>>;
		
		m_RadialBlurEffects = new array<int>;
		m_RadialBlurValues = new map<int, ref array<float>>;
		
		m_DynamicValues = new array<float>;
		
		m_RotiBlurKokain 		= RegisterRotiBlurEffect();
		m_RotiBlurCrystal 		= RegisterRotiBlurEffect();
		
		m_DynamicKokain 		= RegisterDynamicEffect();
		m_DynamicCrystal 		= RegisterDynamicEffect();
		
		m_ChromAbersKokain 		= RegisterChromAbersEffect();
		m_ChromAbersCrystal 	= RegisterChromAbersEffect();
		
		m_RadialBlurKokain 		= RegisterRadialBlurEffect();
		m_RadialBlurCrystal 	= RegisterRadialBlurEffect();
		
	}

	static int RegisterRotiBlurEffect()
	{
		return m_RotiBlurEffects.Insert(0);
	}

	static void SetKokainRotiBlur(float Power, float MinDepth, float MaxDepth)
	{
		SetRotiBlurEffectValue(m_RotiBlurKokain, Power, MinDepth, MaxDepth);
		UpdateRotiBlur();
	}
	
	static void SetCrystalRotiBlur(float Power, float MinDepth, float MaxDepth)
	{
		SetRotiBlurEffectValue(m_RotiBlurCrystal, Power, MinDepth, MaxDepth);
		UpdateRotiBlur();
	}
	
	/*!
	\ Set Roti Blur
	\ Power 0
	\ MinDepth 2.5
	\ MaxDepth 4.5
	*/
	static void SetRotiBlur(float Power, float MinDepth, float MaxDepth)
	{
		m_MatRotiBlur.SetParam("Power", Power);
		m_MatRotiBlur.SetParam("MinDepth", MinDepth);
		m_MatRotiBlur.SetParam("MaxDepth", MaxDepth);
	}
	
	static void SetRotiBlurEffectValue(int index, float power, float mindepth, float maxdepth)
	{
		if ( index < m_RotiBlurEffects.Count() )
		{
			ref array<float> values = {power,mindepth,maxdepth};
			
			m_RotiBlurValues.Set(index, values);
		}
		else
		{
			Print("Error: HRZ_PPEffects: m_RotiBlurValues with index: "+ index +" is not registered.");
		}
	}
	
	static void ResetRotiBlurs()
	{
		if( m_RotiBlurValues )
		{
			for ( int i = 0; i < m_RotiBlurValues.Count(); ++i )
			{
				ref array<float> values = {0,0,0};
			
				m_RotiBlurValues.Set(i, values);
			}
			UpdateRotiBlur();
		}
	}
	
	static void UpdateRotiBlur()
	{
		float Power;
		float MinDepth
		float MaxDepth
		
		float Power_value_total = 0; //use just the highest?
		float MinDepth_value_total = 0; //use just the highest?
		float MaxDepth_value_total = 0; //use just the highest?
		
		if( m_RotiBlurEffects )
		{
			for ( int i = 0; i < m_RotiBlurEffects.Count(); ++i )
			{
				if (m_RotiBlurValues.Get(i))
				{
					Power = m_RotiBlurValues.Get(i).Get(0);
					Power_value_total += Power;
					
					MinDepth = m_RotiBlurValues.Get(i).Get(0);
					MinDepth_value_total += MinDepth;
					
					MaxDepth = m_RotiBlurValues.Get(i).Get(0);
					MaxDepth_value_total += MaxDepth;
				}
				else
				{
					//Print("no m_RotiBlurValues");
				}
			}
		}
		
		SetRotiBlur( Power_value_total, MinDepth_value_total, MaxDepth_value_total );
	}
	
	//-------------------------------------------------------
	// Roti BLUR END
	//-------------------------------------------------------
	
	static int RegisterDynamicEffect()
	{
		return m_DynamicValues.Insert(0);
	}

	static void SetKokainDynamic(float Power)
	{
		SetDynamicEffectValue(m_DynamicKokain, Power);
		UpdateDynamic();
	}
	
	static void SetCrystalDynamic(float Power)
	{
		SetDynamicEffectValue(m_DynamicCrystal, Power);
		UpdateDynamic();
	}
	
	static void ResetDynamics()
	{
		if( m_DynamicValues )
		{
			for ( int i = 0; i < m_DynamicValues.Count(); ++i )
			{
				m_DynamicValues[i] = 0;
			}
			UpdateDynamic();
		}
	}
	
	static void SetDynamicEffectValue(int index, float value)
	{
		if ( m_DynamicValues && index < m_DynamicValues.Count() )
		{
			m_DynamicValues[index] = value;
		}
		else
		{
			Print("Error: HRZ_PPEffects: m_DynamicValues with index: "+ index +" is not registered.");
		}
	}
	
	/*!
	\ Dynamic Blur
	\ Power 0
	*/
	
	static void SetDynamic(float Power)
	{
		m_MatDynamic.SetParam("Blurriness", Power);
	}
	
	static void UpdateDynamic()
	{
		float Power_value_total = 0;
		if( m_DynamicValues )
		{
			for ( int i = 0; i < m_DynamicValues.Count(); ++i )
			{
				Power_value_total += m_DynamicValues[i];
			}
		}
		
		SetDynamic( Power_value_total);
	}
	
	//-------------------------------------------------------
	// Dynamic BLUR END
	//-------------------------------------------------------
	
	static int RegisterChromAbersEffect()
	{
		return m_ChromAbersEffects.Insert(0);
	}

	static void SetKokainChromAbers(float PowerX, float PowerY)
	{
		SetChromAbersEffectValue(m_ChromAbersKokain, PowerX, PowerY);
		UpdateChromAbers();
	}
	
	static void SetCrystalChromAbers(float PowerX, float PowerY)
	{
		SetChromAbersEffectValue(m_ChromAbersCrystal, PowerX, PowerY);
		UpdateChromAbers();
	}
	
	static void ResetChromAbers()
	{
		if( m_ChromAbersValues )
		{
			for ( int i = 0; i < m_ChromAbersValues.Count(); ++i )
			{
				ref array<float> values = {0,0};
			
				m_ChromAbersValues.Set(i, values);
			}
			UpdateChromAbers();
		}
	}
	
	static void SetChromAbersEffectValue(int index, float powerx, float powery)
	{
		if ( index < m_ChromAbersEffects.Count() )
		{
			ref array<float> values = {powerx,powery};
			
			m_ChromAbersValues.Set(index, values);
		}
		else
		{
			Print("Error: HRZ_PPEffects: m_ChromAbersValues with index: "+ index +" is not registered.");
		}
	}
	
	/*!
	\ Dynamic Blur
	\ Power 0
	*/
	
	static void SetChromAbers(float PowerX, float PowerY)
	{
		m_MatChromAbers.SetParam("PowerX", PowerX);
		m_MatChromAbers.SetParam("PowerY", PowerY);
	}
	
	static void UpdateChromAbers()
	{
		float PowerX;
		float PowerY;
		
		float PowerX_value_total = 0;
		float PowerY_value_total = 0;
		
		if( m_ChromAbersEffects )
		{
			for ( int i = 0; i < m_ChromAbersEffects.Count(); ++i )
			{
				if (m_ChromAbersValues.Get(i))
				{
				PowerX = m_ChromAbersValues.Get(i).Get(0);
				PowerY = m_ChromAbersValues.Get(i).Get(0);
					
				PowerX_value_total += PowerX;
				PowerY_value_total += PowerY;
				}
				else
				{
					//Print("no m_ChromAbersValues");
				}
			}
		}
		
		SetChromAbers( PowerX_value_total, PowerY_value_total);
	}
	
	//-------------------------------------------------------
	// ChromAbbs END
	//-------------------------------------------------------
	
	static int RegisterRadialBlurEffect()
	{
		return m_RadialBlurEffects.Insert(0);
	}

	static void SetKokainRadialBlur(float PowerX, float PowerY, float OffsetX, float OffsetY)
	{
		SetRadialBlurEffectValue(m_RadialBlurKokain, PowerX, PowerY, OffsetX, OffsetY);
		UpdateRadialBlur();
	}
	
	static void SetCrystalRadialBlur(float PowerX, float PowerY, float OffsetX, float OffsetY)
	{
		SetRadialBlurEffectValue(m_RadialBlurCrystal, PowerX, PowerY, OffsetX, OffsetY);
		UpdateRadialBlur();
	}
	
	static void ResetRadialBlur()
	{
		if( m_RadialBlurValues )
		{
			for ( int i = 0; i < m_RadialBlurValues.Count(); ++i )
			{
				ref array<float> values = {0,0,0,0};
			
				m_RadialBlurValues.Set(i, values);
			}
			UpdateRadialBlur();
		}
	}
	
	static void SetRadialBlurEffectValue(int index, float powerx, float powery, float offsetx, float offsety)
	{
		if ( index < m_RadialBlurEffects.Count() )
		{
			ref array<float> values = {powerx,powery,offsetx,offsety};
			
			m_RadialBlurValues.Set(index, values);
		}
		else
		{
			Print("Error: HRZ_PPEffects: m_RadialBlurValues with index: "+ index +" is not registered.");
		}
	}
	
	/*!
	\ Dynamic Blur
	\ Power 0
	*/
	
	static void SetRadialBlur(float PowerX, float PowerY, float OffsetX, float OffsetY)
	{
		m_MatRadialBlur.SetParam("PowerX", PowerX);
		m_MatRadialBlur.SetParam("PowerY", PowerY);
		m_MatRadialBlur.SetParam("OffsetX", OffsetX);
		m_MatRadialBlur.SetParam("OffsetY", OffsetY);
	}
	
	static void UpdateRadialBlur()
	{
		float PowerX;
		float PowerY;
		float OffsetX;
		float OffsetY;
		
		float PowerX_value_total = 0;
		float PowerY_value_total = 0;
		float OffsetX_value_total = 0;
		float OffsetY_value_total = 0;
		
		if( m_RadialBlurEffects )
		{
			for ( int i = 0; i < m_RadialBlurEffects.Count(); ++i )
			{
				if (m_RadialBlurValues.Get(i))
				{
				PowerX = m_RadialBlurValues.Get(i).Get(0);
				PowerY = m_RadialBlurValues.Get(i).Get(0);
				OffsetX = m_RadialBlurValues.Get(i).Get(0);
				OffsetY = m_RadialBlurValues.Get(i).Get(0);
					
				PowerX_value_total += PowerX;
				PowerY_value_total += PowerY;
				OffsetX_value_total += OffsetX;
				OffsetY_value_total += OffsetY;
				}
				else
				{
					//Print("no m_RadialBlurValues");
				}
			}
		}
		
		SetRadialBlur( PowerX_value_total, PowerY_value_total, OffsetX_value_total, OffsetY_value_total);
	}
	
	//-------------------------------------------------------
	// Radial BLUR END
	//-------------------------------------------------------
	
	override static void ResetAll()
	{
		ResetRotiBlurs();
		ResetDynamics();
		ResetChromAbers();
		ResetRadialBlur();
	}
};