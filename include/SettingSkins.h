#pragma once

#include <PlayerSkin.h>
#include <EnemySkin.h>

class SettingSkins
{
 public:
 SettingSkins(): current_player_skin(PS_SKIN1), current_enemy_skin(ES_SKIN1)
  {
    owned_player_skins.push_back(PS_SKIN1);
    owned_enemy_skins.push_back(ES_SKIN1);
  } 

  PLAYERSKINS getCurrentPlayerSkin() { return this->current_player_skin; }
  ENEMYSKINS getCurrentEnemySkin() { return this->current_enemy_skin; }

  void setPlayerSkin(PLAYERSKINS type) { if(isOwnedPlayerSkin(type)) this->current_player_skin = type; }
  void setEnemySkin(ENEMYSKINS type) { if(isOwnedEnemySkin(type)) this->current_enemy_skin = type; }

  bool isOwnedPlayerSkin(PLAYERSKINS type)
  {
    bool owned = false;
    for(std::size_t i = 0; i < owned_player_skins.size(); i++)
      {
	if(owned_player_skins[i] == type)
	  {
	    owned = true;
	    break;
	  }
      }
    return owned;
  }
  bool isOwnedEnemySkin(ENEMYSKINS type)
  {
    bool owned = false;
    for(std::size_t i = 0; i < owned_enemy_skins.size(); i++)
      {
	if(owned_enemy_skins[i] == type)
	  {
	    owned = true;
	    break;
	  }
      }
    return owned;
  }

  void addPlayerSkin(PLAYERSKINS type)
  {
    if(!isOwnedPlayerSkin(type))
      {
	owned_player_skins.push_back(type);
      }
  }
  void addEnemySkin(ENEMYSKINS type)
  {
    if(!isOwnedEnemySkin(type))
      {
	owned_enemy_skins.push_back(type);
      }
  }

 private:
  std::vector<PLAYERSKINS> owned_player_skins;
  std::vector<ENEMYSKINS> owned_enemy_skins;

  PLAYERSKINS current_player_skin;
  ENEMYSKINS current_enemy_skin;
};
