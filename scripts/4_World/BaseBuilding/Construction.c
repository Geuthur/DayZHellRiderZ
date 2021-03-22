modded class Construction
{
	override bool IsColliding(string part_name)
	{
		if (GetParent().IsInherited(Fence))
			return false;
		
		return super.IsColliding(part_name);
	}
}

modded class Hologram
{

	override void EvaluateCollision(ItemBase action_item = null)
	{
		if (m_Projection.IsInherited(Fence) || m_Projection.IsInherited(FenceKit) || m_Projection.IsInherited(Paper) )
		{
			SetIsColliding(false);
			return;
		}
		super.EvaluateCollision();
	}
}