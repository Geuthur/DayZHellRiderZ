modded class Cannabis
{
  override void SetActions()
  {
  super.SetActions();
  
  RemoveAction(ActionForceFeed);
  RemoveAction(ActionEatSmall);
  }
}