#include <app.h>

void App::createPlayerSkin(const std::string& id,
			   const std::string& name, const std::string& des, PLAYERSKINS type)
{
  PlayerSkin ps_skin;
  ps_skin.setName(name);
  ps_skin.setDescription(des);
  ps_skin.setType(type);
  skins.push_back(&ps_skin);

  ShakingText t_name(skins.back()->getName(), font1, 18);
  shop_texts.addText("ps_name_" + id, t_name);

  ShakingText t_des(skins.back()->getDescription(), font1, 16);
  shop_texts.addText("ps_des_" + id, t_des);
}

void App::createEnemySkin(const std::string& id,
			  const std::string& name, const std::string& des, ENEMYSKINS type)
{
  EnemySkin es_skin;
  es_skin.setName(name);
  es_skin.setDescription(des);
  es_skin.setType(type);
  skins.push_back(&es_skin);

  ShakingText t_name(skins.back()->getName(), font1, 18);
  shop_texts.addText("es_name_" + id, t_name);

  ShakingText t_des(skins.back()->getDescription(), font1, 16);
  shop_texts.addText("es_des_" + id, t_des);
}
