class HRZ_PPEffects extends PPEffects
{
	static Material m_MatRotiBlur;
	static Material m_MatDynamic;
	static Material m_MatChromAbers;
	static Material m_MatRadialBlur;

	static ref array<int> m_Effects;
	static ref map<int, ref array<float>> m_EffectsValues;
	
	static ref map<int, ref array<float>> m_RadialBlurValues;
	static ref map<int, ref array<float>> m_ChromAbersValues;
	static ref map<int, ref array<float>> m_RotiBlurValues;
	static ref map<int, ref array<float>> m_DynamicValues;
	
	override static void Init()
	{
		if ( m_Effects )
		{
			delete m_Effects;
		}
		if ( m_DynamicValues )
		{
			delete m_DynamicValues;
		}
		if ( m_RotiBlurValues )
		{
			delete m_RotiBlurValues;
		}
		if ( m_ChromAbersValues )
		{
			delete m_ChromAbersValues;
		}
		if ( m_RadialBlurValues )
		{
			delete m_RadialBlurValues;
		}
		
		
		m_MatRotiBlur = GetGame().GetWorld().GetMaterial("graphics/materials/postprocess/rotblur");
		m_MatDynamic = GetGame().GetWorld().GetMaterial("graphics/materials/postprocess/dynamicblur");
		m_MatChromAbers = GetGame().GetWorld().GetMaterial("graphics/materials/postprocess/chromaber");
		m_MatRadialBlur = GetGame().GetWorld().GetMaterial("graphics/materials/postprocess/radialblur");
		
		m_RotiBlurValues = new map<int, ref array<float>>;
		m_ChromAbersValues = new map<int, ref array<float>>;
		m_RadialBlurValues = new map<int, ref array<float>>;
		m_DynamicValues = new map<int, ref array<float>>;
		
		m_Effects = new array<int>;
		m_EffectsValues = new map<int, ref array<float>>;
		
		RegisterEffect(HRZ_EffectID.Kokain);
		RegisterEffect(HRZ_EffectID.Crystal);
		RegisterEffect(HRZ_EffectID.Cannabis);
		RegisterEffect(HRZ_EffectID.Blur);
	}
	
	//-------------------------------------------------------
	// Pulsing Effect
	//-------------------------------------------------------
	
	
	static void PulsingRadialEffect(int effectID, float deltatime)
	{
		const float 					PULSE_PERIOD = 0.1; //The time it takes for pulse to do a full cycle
		const float 					PULSE_AMPLITUDE = 0.2; //This is a multiplier, keep below 1 or expect the unexpected
		float 							m_Pulse; //Lerp result
		
		m_Pulse = Bobbing(PULSE_PERIOD, PULSE_AMPLITUDE, deltatime);
		
		SetRadialBlurEffectValue(effectID, m_Pulse, m_Pulse, 0, 0);
		UpdateRadialBlur();
	}	

	static void RegisterEffect(int neweffect)
	{
		if( m_EffectsValues.Contains(neweffect) )
		{
			Print("EffectManager" + neweffect + "already registered !");
			Print (m_Effects.Count());
			//Error("EffectManager" + neweffect + "already registered !");
			return;
		}
		Print (m_Effects.Count());
		m_Effects.Insert(neweffect);
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
		if ( index < m_Effects.Count() )
		{
			ref array<float> values = {power,mindepth,maxdepth};
			
			m_RotiBlurValues.Set(index, values);
		}
		else
		{
			Print("Error: HRZ_PPEffects: m_RotiBlurValues with index: "+ index +" is not registered.");
		}
		UpdateRotiBlur();
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
		
		if( m_Effects )
		{
			for ( int i = 0; i < m_Effects.Count(); ++i )
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
	
	static void ResetDynamics()
	{
		if( m_DynamicValues )
		{
			for ( int i = 0; i < m_DynamicValues.Count(); ++i )
			{
				ref array<float> values = {0};
				
				m_DynamicValues.Set(i, values);
			}
			UpdateDynamic();
		}
	}
	
	static void SetDynamicEffectValue(int index, float value)
	{
		if ( index < m_Effects.Count() )
		{
			ref array<float> values = {value};
			
			m_DynamicValues.Set(index, values);
		}
		else
		{
			Print("Error: HRZ_PPEffects: m_DynamicValues with index: "+ index +" is not registered.");
		}
	UpdateDynamic();
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
		float Power;
		
		float Power_value_total = 0;
		if( m_DynamicValues )
		{
			for ( int i = 0; i < m_Effects.Count(); ++i )
			{
				if (m_DynamicValues.Get(i))
				{
				Power = m_DynamicValues.Get(i).Get(0);
				Power_value_total += Power;
				}
				else
				{
					//Print("no m_DynamicValues");
				}
			}
		}
		
		SetDynamic( Power_value_total);
	}
	
	//-------------------------------------------------------
	// Dynamic BLUR END
	//-------------------------------------------------------
		
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
		if ( index < m_Effects.Count() )
		{
			ref array<float> values = {powerx,powery};
			
			m_ChromAbersValues.Set(index, values);
		}
		else
		{
			Print("Error: HRZ_PPEffects: m_ChromAbersValues with index: "+ index +" is not registered.");
		}
	UpdateChromAbers();
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
		
		if( m_Effects )
		{
			for ( int i = 0; i < m_Effects.Count(); ++i )
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
		//Print (m_Effects.Count());
		if ( index < m_Effects.Count() )
		{
			ref array<float> values = {powerx,powery,offsetx,offsety};
			
			m_RadialBlurValues.Set(index, values);
		}
		else
		{
			Print("Error: HRZ_PPEffects: m_RadialBlurValues with index: "+ index +" is not registered.");
		}
	UpdateRadialBlur();
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
	
	static float Bobbing(float period, float amplitude, float elapsedTime)
	{
		//Prevent division by 0
		if ( period == 0 )
			period = 1;
		
		elapsedTime /= period;
		
		float cycle;
		cycle += elapsedTime;
		cycle = FModulus(cycle, 360);
		cycle = Math.Sin(cycle) * amplitude;
		
		return cycle;
	}
	
	static float FModulus(float x, float y)
	{
		float res;
		//Prevent division by 0
		if (y == 0)
			y = 1;
		
		int n = Math.Floor(x/y);
		res = x - n * y;
		return res;
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
		
		if( m_Effects )
		{
			for ( int i = 0; i < m_Effects.Count(); ++i )
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