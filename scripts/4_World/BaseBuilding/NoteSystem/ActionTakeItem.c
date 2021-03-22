modded class ActionTakeItem
{
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
		if (target && target.GetObject().IsInherited(HRZ_WrittenNote))
			return false;

        return super.ActionCondition(player, target, item);
    }
}