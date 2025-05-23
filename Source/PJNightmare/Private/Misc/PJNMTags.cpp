// Fill out your copyright notice in the Description page of Project Settings.


#include "Misc/PJNMTags.h"



namespace PJNMGamplayTags
{
	/** input Tags **/
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move, "InputTag.Move")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Look, "InputTag.Look")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Attack, "InputTag.Attack")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Zoom, "InputTag.Zoom")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Dash, "InputTag.Dash")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Sprint, "InputTag.Sprint")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Action, "InputTag.Action") 

	/** Player tags **/
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Primary, "Player.Weapon.Primary")
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Primary_Equipped, "Player.Weapon.Primary.Equipped")
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Secondary, "Player.Weapon.Secondary")
}
