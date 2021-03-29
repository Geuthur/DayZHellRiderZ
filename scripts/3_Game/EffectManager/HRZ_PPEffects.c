/**
 * HRZ_PPEffects.c
 *
 * DayZ Hell-RiderZ Mod
 * www.hell-rider.de
 * © 2021 DayZ Hell-RiderZ Team
 *
 * This work is licensed under the Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-nd/4.0/.
 *
*/

class HRZ_PPEffects extends PPEffects
{
	// COLORIZE IDs
	//static const int COLORIZE_FG = 100;
	
	static Material m_MatRotiBlur;
	static Material m_MatDynamic;
	static Material m_MatChromAbers;
	static Material m_MatRadialBlur;
	static Material m_matHDR;
	static Material m_glow;

	static ref array<int> m_Effects;
	static ref map<int, ref array<float>> m_EffectsValues;
	
	static ref map<int, ref array<float>> m_RadialBlurValues;
	static ref map<int, ref array<float>> m_ChromAbersValues;
	static ref map<int, ref array<float>> m_RotiBlurValues;
	static ref map<int, ref array<float>> m_DynamicValues;
	static ref map<int, ref array<float>> m_HRZVignetteValues;
	static ref map<int, ref array<float>> m_GrainValues;
	
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
		if ( m_HRZVignetteValues )
		{
			delete m_HRZVignetteValues;
		}
		if ( m_GrainValues )
		{
			delete m_GrainValues;
		}
		
		m_MatColors = GetGame().GetWorld().GetMaterial("graphics/materials/postprocess/glow");
		m_MatRotiBlur = GetGame().GetWorld().GetMaterial("graphics/materials/postprocess/rotblur");
		m_MatDynamic = GetGame().GetWorld().GetMaterial("graphics/materials/postprocess/dynamicblur");
		m_MatChromAbers = GetGame().GetWorld().GetMaterial("graphics/materials/postprocess/chromaber");
		m_MatRadialBlur = GetGame().GetWorld().GetMaterial("graphics/materials/postprocess/radialblur");
		m_matHDR = GetGame().GetWorld().GetMaterial("graphics/materials/postprocess/filmgrainNV");
		
		m_RotiBlurValues = new map<int, ref array<float>>;
		m_ChromAbersValues = new map<int, ref array<float>>;
		m_RadialBlurValues = new map<int, ref array<float>>;
		m_DynamicValues = new map<int, ref array<float>>;
		m_HRZVignetteValues = new map<int, ref array<float>>;
		m_GrainValues = new map<int, ref array<float>>;
		
		m_Effects = new array<int>;
		m_EffectsValues = new map<int, ref array<float>>;
		
		RegisterEffect(HRZ_EffectID.Kokain);
		RegisterEffect(HRZ_EffectID.Crystal);
		RegisterEffect(HRZ_EffectID.Cannabis);
		RegisterEffect(HRZ_EffectID.Blur);
		RegisterEffect(HRZ_EffectID.Test);
	}
	
	static void RegisterEffect(int neweffect)
	{
		if( m_EffectsValues.Contains(neweffect) )
		{
			Print("EffectManager" + neweffect + "already registered !");
			return;
		}
		Print (m_Effects.Count());
		m_Effects.Insert(neweffect);
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
		if (y == 0)
			y = 1;
		
		int n = Math.Floor(x/y);
		res = x - n * y;
		return res;
	}
	
	//-------------------------------------------------------
	// Pulsing Effects
	//-------------------------------------------------------
	private static float					m_PulseTimer; // Speed of Pulsing Between 0-1
	private static bool 					m_PulseActive;
	private static float 					m_CrazyPulseTimer; // Speed of Pulsing Between 0-1
	private static bool 					m_CrazyPulseActive;
	
	static void PulsingRadialEffect(int effectID, float deltatime)
	{
		private const float 					PULSE_PERIOD = 0.1; //The time it takes for pulse to do a full cycle
		private const float 					PULSE_AMPLITUDE = 0.2; //This is a multiplier, keep below 1 or expect the unexpected
		private float 							m_Pulse; //Lerp result
		m_PulseActive = true;
		
		if (deltatime > 1)
		deltatime = 1;
		
		m_PulseTimer += deltatime;
		
		m_Pulse = Bobbing(PULSE_PERIOD, PULSE_AMPLITUDE, (m_PulseTimer * 0.01));
		
		SetRadialBlurEffectValue(effectID, m_Pulse, m_Pulse, 0, 0);
		UpdateRadialBlur();
	}	
	
	static void CrazyPulsingRadialEffect(int effectID, float deltatime, float bobbing)
	{
		private const float 					PULSE_PERIOD = 0.1; //The time it takes for pulse to do a full cycle
		private const float 					PULSE_AMPLITUDE = 0.2; //This is a multiplier, keep below 1 or expect the unexpected
		private float 							m_Pulse; //Pulse result
		m_CrazyPulseActive = true;
		
		if (deltatime > 1)
		deltatime = 1;
		
		m_CrazyPulseTimer += deltatime;
		
		m_Pulse = Bobbing(PULSE_PERIOD, PULSE_AMPLITUDE, (m_CrazyPulseTimer * 0.01) * bobbing);
		
		SetRadialBlurEffectValue(effectID, m_Pulse, m_Pulse, 0, 0);
		
		UpdateRadialBlur();
		
		PPEffects.SetBloodSaturation(5);
		HRZ_PPEffects.SetColorizationNV(m_Pulse,m_Pulse,m_Pulse);
	}
	
	//-------------------------------------------------------
	// Abstract Effects Beta - Known Bugs - Jump & Boxing will reset the Effect
	//-------------------------------------------------------
	
	private static float 					m_DarkPulseTimer; // Speed of Pulsing Between 0-1
	private static bool 					m_DarkPulseActive;
	private static float 					m_WabblePulseTimer; // Speed of Pulsing Between 0-1
	private static bool 					m_WabblePulseActive;
	
	static void DarkWorldEffect()
	{
		PPEffects.SetBloodSaturation(5);
		HRZ_PPEffects.SetColorizationNV(-1,-1,-1);
	}
	
	static void WabbleEffect(float bobbing, float size)
	{
		/*
		private const float 					PULSE_PERIOD = 1; //The time it takes for pulse to do a full cycle
		private const float 					PULSE_AMPLITUDE = 0.5; //This is a multiplier, keep below 1 or expect the unexpected
		private float 							m_Pulse; //Pulse result
		m_WabblePulseActive = true;
		
		if (deltatime > 1)
		deltatime = 1;
		
		m_WabblePulseTimer += deltatime;
		
		//m_Pulse = Bobbing(PULSE_PERIOD, PULSE_AMPLITUDE, (m_WabblePulseTimer * 0.01)) * 1;
		//m_Pulse = Math.Lerp(0.1, 0.9, m_WabblePulseTimer);
		//Print (m_Pulse);
		*/
		HRZ_PPEffects.SetFilmGrain(0,0.1,bobbing,size);
	}
	
	//-------------------------------------------------------
	// Camera Effects
	//-------------------------------------------------------
	private static float 						m_CameraPulseTimer; // Speed of Pulsing Between 0-1
	
	static void CameraEffect(float strength, float smoothness, float bobbing)
	{
		private const float 					PULSE_PERIOD = 0.1; //The time it takes for pulse to do a full cycle
		private const float 					PULSE_AMPLITUDE = 1; //This is a multiplier, keep below 1 or expect the unexpected
		private float 							m_Pulse; //Pulse result
		
		if (smoothness > 1)
		smoothness = 1;
		if (m_CameraPulseTimer > 1000)
		m_CameraPulseTimer = 0;
		
		m_CameraPulseTimer += smoothness;
		
		m_Pulse = Bobbing(PULSE_PERIOD, PULSE_AMPLITUDE, (m_CameraPulseTimer * Math.PI_HALF)) * bobbing;
		
		GetGame().GetPlayer().GetCurrentCamera().SpawnCameraShake(m_Pulse,strength,10,1);
	}
	
	/*!
	set vignette
	\param intensity <0, 1>, intensity of effect, 0 = disable
	\param R
	\param G
	\param B
	*/
	
	static void HRZ_SetVignette(float intensity, float R, float G, float B, float A)
	{
		float color[4];
		color[0] = R;
		color[1] = G;
		color[2] = B;
		color[3] = A;

		m_MatColors.SetParam("Vignette", intensity);
		m_MatColors.SetParam("VignetteColor", color);
	}
	
	static void HRZ_SetVignetteEffectValue(int effectID, float intensity, float r, float g, float b, float a)
	{
		if ( effectID < m_Effects.Count() )
		{
			ref array<float> values = {intensity,r,g,b,a};
			
			m_HRZVignetteValues.Set(effectID, values);
		}
		else
		{
			Print("Error: PPEffects: m_EffectsValues with index: "+ effectID +" is not registered.");
		}
		HRZ_UpdateVignette();
	}
	
	static void HRZ_ResetVignettes(int effectID)
	{
		if( m_HRZVignetteValues )
		{
				ref array<float> values = {0,0,0,0,0};
			
				m_HRZVignetteValues.Set(effectID, values);
			
			HRZ_UpdateVignette();
		}
	}
	
	static void HRZ_UpdateVignette()
	{
		float color[4];
		float intesity;
		
		float intensity_value_total = 0;
		if( m_Effects )
		{
			for ( int i = 0; i < m_Effects.Count(); ++i )
			{
				if (m_HRZVignetteValues.Get(i))
				{
					color[0] = m_HRZVignetteValues.Get(i).Get(1); //red
					color[1] = m_HRZVignetteValues.Get(i).Get(2); //green
					color[2] = m_HRZVignetteValues.Get(i).Get(3); //blue
					color[3] = m_HRZVignetteValues.Get(i).Get(4); //alpha
					
					intesity = m_HRZVignetteValues.Get(i).Get(0);
					intensity_value_total += intesity;
				}
				else
				{
					//Print("no m_HRZVignetteValues");
				}
			}
		}
		
		HRZ_SetVignette( intensity_value_total, color[0], color[1], color[2], color[3] );
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
	
	
	static void SetRotiBlurEffectValue(int effectID, float power, float mindepth, float maxdepth)
	{
		if ( effectID < m_Effects.Count() )
		{
			ref array<float> values = {power,mindepth,maxdepth};
			
			m_RotiBlurValues.Set(effectID, values);
		}
		else
		{
			Print("Error: HRZ_PPEffects: m_RotiBlurValues with effectID: "+ effectID +" is not registered.");
		}
		UpdateRotiBlur();
	}
	
	static void ResetRotiBlurs(int effectID)
	{
		if( m_RotiBlurValues )
		{
				ref array<float> values = {0,0,0};
			
				m_RotiBlurValues.Set(effectID, values);
			UpdateRotiBlur();
		}
	}
	
	static void UpdateRotiBlur()
	{
		float Power;
		float MinDepth
		float MaxDepth
		
		float Power_value_total = 0;
		float MinDepth_value_total = 0;
		float MaxDepth_value_total = 0;
		
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
	
	static void ResetDynamics(int effectID)
	{
		if( m_DynamicValues )
		{
				ref array<float> values = {0};
				
				m_DynamicValues.Set(effectID, values);
			UpdateDynamic();
		}
	}
	
	static void SetDynamicEffectValue(int effectID, float Power)
	{
		if ( effectID < m_Effects.Count() )
		{
			ref array<float> values = {Power};
			
			m_DynamicValues.Set(effectID, values);
		}
		else
		{
			Print("Error: HRZ_PPEffects: m_DynamicValues with effectID: "+ effectID +" is not registered.");
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
		
	static void ResetChromAbers(int effectID)
	{
		if( m_ChromAbersValues )
		{
				ref array<float> values = {0,0};
			
				m_ChromAbersValues.Set(effectID, values);
			
			UpdateChromAbers();
		}
	}
	
	static void SetChromAbersEffectValue(int effectID, float powerx, float powery)
	{
		if ( effectID < m_Effects.Count() )
		{
			ref array<float> values = {powerx,powery};
			
			m_ChromAbersValues.Set(effectID, values);
		}
		else
		{
			Print("Error: HRZ_PPEffects: m_ChromAbersValues with effectID: "+ effectID +" is not registered.");
		}
	UpdateChromAbers();
	}
	
	/*!
	\ Chrom Abers
	\ PowerX 0
	\ PowerY 0
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
				Print (m_ChromAbersValues.Get(i));
				PowerX = m_ChromAbersValues.Get(i).Get(0);
				PowerY = m_ChromAbersValues.Get(i).Get(0);
					
				PowerX_value_total += PowerX;
				PowerY_value_total += PowerY;
				Print (PowerY_value_total);
				Print (PowerX_value_total);
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
	
	static void ResetRadialBlur(int effectID)
	{
		if( m_RadialBlurValues )
		{
				ref array<float> values = {0,0,0,0};
			
				m_RadialBlurValues.Set(effectID, values);
			
			UpdateRadialBlur();
			if (m_PulseActive)
			{
				m_PulseActive = false;
				m_PulseTimer = 0;
			} else if (m_CrazyPulseActive) 
			{
				m_CrazyPulseActive = false;
				m_CrazyPulseTimer = 0;
			}
		}
	}
	
	static void SetRadialBlurEffectValue(int effectID, float powerx, float powery, float offsetx, float offsety)
	{
		if ( effectID < m_Effects.Count() )
		{
			ref array<float> values = {powerx,powery,offsetx,offsety};
			
			m_RadialBlurValues.Set(effectID, values);
		}
		else
		{
			Print("Error: HRZ_PPEffects: m_RadialBlurValues with effectID: "+ effectID +" is not registered.");
		}
	UpdateRadialBlur();
	}
	
	/*!
	\ Radial Blur
	\ PowerX 0
	\ PowerY 0
	\ OffsetX 0
	\ OffsetY 0
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

	/*
	// appropriate parts of the code will call these functions
	static void SetColorizationFG(float R, float G, float B, float A)
	{
		float color[4];
		color[0] = R;
		color[1] = G;
		color[2] = B;
		color[3] = A;
		
		Print(color);
		m_MatColors.SetParam("ColorizationColor", color);
		UpdateColorFG();
	}

	static void SetGrainEffectValue(int index, float r, float g, float b)
	{
		if ( index < m_Effects.Count() )
		{
			ref array<float> values = {r,g,b};
			
			m_GrainValues.Set(index, values);
		}
		else
		{
			Print("Error: PPEffects: m_GrainValues with index: "+ index +" is not registered.");
		}
		UpdateColorFG();
	}
	
	static void UpdateColorFG()
	{
		float color[4];
		
		if( m_Effects )
		{
			for ( int i = 0; i < m_Effects.Count(); ++i )
			{
				if (m_GrainValues.Get(i))
				{
					color[0] = m_GrainValues.Get(i).Get(1); //red
					color[1] = m_GrainValues.Get(i).Get(2); //green
					color[2] = m_GrainValues.Get(i).Get(3); //blue
					color[3] = 0;
				}
				else
				{
					//Print("no m_HRZVignetteValues");
				}
			}
		}
		
		m_MatColors.SetParam("ColorizationColor", color);
	}
	
	static void ResetColor()
	{
		float color[4];
		color[0] = 1.0;
		color[1] = 1.0;
		color[2] = 1.0;
		color[3] = 0;
        m_MatColors.SetParam("ColorizationColor", color);
		if (m_DarkPulseActive)
			{
				m_DarkPulseActive = false;
				m_DarkPulseTimer = 0;
		}
	}
	*/
	// light multiplier and noise intensity (using filmgrainNV.emat!) for nvg
	// added other parameters for filmgrainNV.emat, sharpness and grain size
	static void SetFilmGrain(float light_mult, float noise_intensity, float sharpness, float grain_size)
	{
		
		g_Game.NightVissionLightParams(light_mult, noise_intensity);
		m_matHDR.SetParam("Sharpness", sharpness);
		m_matHDR.SetParam("GrainSize", grain_size);
	}
	
	static void ResetFilmGrain()
	{
		g_Game.NightVissionLightParams(0, 0);
		m_matHDR.SetParam("Sharpness", 0);
		m_matHDR.SetParam("GrainSize", 0);
		if (m_WabblePulseActive)
			{
				m_WabblePulseActive = false;
				m_WabblePulseTimer = 0;
		}
	}
	
	static void ResetAllEffects(int effectID)
	{
		ResetRotiBlurs(effectID);
		ResetDynamics(effectID);
		ResetChromAbers(effectID);
		ResetRadialBlur(effectID);
		HRZ_ResetVignettes(effectID);
		ResetColorize();
		//ResetColor();
		ResetFilmGrain();
		SetBloodSaturation(1);
	}
};