#include <app.h>


void App::initTexts()
{
  ShakingText btn_start("Play", font);
  btn_start.text().setPosition(sf::Vector2f(100, 100));
  texts.addText("btn_start", btn_start);

  ShakingText btn_credits("Credits", font);
  btn_credits.text().setPosition(sf::Vector2f(100, 200));
  texts.addText("btn_credits", btn_credits);

  ShakingText btn_exit("Exit", font);
  btn_exit.text().setPosition(sf::Vector2f(100, 250));
  texts.addText("btn_exit", btn_exit);

  ShakingText btn_back("Go to menu", font);
  btn_back.text().setPosition(sf::Vector2f(500,500));
  texts.addText("btn_back", btn_back);

  ShakingText btn_menu("Menu", font);
  btn_menu.text().setPosition(sf::Vector2f(100,150));
  texts.addText("btn_menu", btn_menu);

  ShakingText btn_resume("Resume", font);
  btn_resume.text().setPosition(sf::Vector2f(100,100));
  texts.addText("btn_resume", btn_resume);

  ShakingText btn_restart("Restart", font);
  btn_restart.text().setPosition(500,450);
  texts.addText("btn_restart", btn_restart);

  ShakingText btn_shop("Shop", font);
  btn_shop.text().setPosition(sf::Vector2f(100,150));
  texts.addText("btn_shop", btn_shop);

  ShakingText t_credits("", font1);
  t_credits.text().setString(L"Credits:\nPatryk Szczygło\n\nI hope it helps to promote\nBitcoins.\n\n\
If you can, tell about\nBitcoins to sombody.");
  t_credits.text().setPosition(sf::Vector2f(50,100));
  texts.addText("txt_credits", t_credits);

  ShakingText t_btc("BITCOINS", font, 56);
  t_btc.text().setPosition(sf::Vector2f(400,300));
  texts.addText("txt_btc_falling", t_btc);
  texts.getText("txt_btc_falling").text().setOrigin(texts.getText("txt_btc_falling").getCenterOfText());
  texts.getText("txt_btc_falling").setShaking(true);
  texts.getText("txt_btc_falling").hide();

  ShakingText t_enemy("Wololololo", font, 56);
  t_enemy.text().setPosition(sf::Vector2f(400,300));
  texts.addText("txt_enemy_falling", t_enemy);
  texts.getText("txt_enemy_falling").text().setOrigin(texts.getText("txt_enemy_falling").getCenterOfText());
  texts.getText("txt_enemy_falling").setShaking(true);
  texts.getText("txt_enemy_falling").hide();

  ShakingText t_explosion("EXPLOSION", font, 56);
  t_explosion.text().setPosition(sf::Vector2f(400,300));
  texts.addText("txt_explosion", t_explosion);
  texts.getText("txt_explosion").text().setOrigin(texts.getText("txt_explosion").getCenterOfText());
  texts.getText("txt_explosion").setShaking(true);
  texts.getText("txt_explosion").hide();

  ShakingText t_keys("INVERTED KEYS", font, 56);
  t_keys.text().setPosition(sf::Vector2f(400,300));
  texts.addText("txt_inverted_keys", t_keys);
  texts.getText("txt_inverted_keys").text().setOrigin(texts.getText("txt_inverted_keys").getCenterOfText());
  texts.getText("txt_inverted_keys").setShaking(true);
  texts.getText("txt_inverted_keys").hide();

  ShakingText t_darkness("DARKNESS", font, 56);
  t_darkness.text().setPosition(sf::Vector2f(400,300));
  texts.addText("txt_darkness", t_darkness);
  texts.getText("txt_darkness").text().setOrigin(texts.getText("txt_darkness").getCenterOfText());
  texts.getText("txt_darkness").setShaking(true);
  texts.getText("txt_darkness").hide();

  ShakingText t_score("", font);
  texts.addText("score", t_score);

  ShakingText t_random_tip("Avoid shurikens!", font1);
  t_random_tip.text().setPosition(400,580);
  t_random_tip.text().setCharacterSize(18);
  texts.addText("tip", t_random_tip);
  texts.getText("tip").text().setOrigin(texts.getText("tip").getCenterOfText());

  ShakingText t_tip("Tip:", font1);
  t_tip.text().setPosition(400,550);
  t_tip.text().setCharacterSize(20);
  texts.addText("tip_text", t_tip);
  texts.getText("tip_text").text().setOrigin(texts.getText("tip_text").getCenterOfText());
  texts.getText("tip_text").setShaking(true);

  ShakingText t_die("You DIE !", font, 56);
  t_die.text().setPosition(400,300);
  texts.addText("t_die", t_die);
  texts.getText("t_die").text().setOrigin(texts.getText("t_die").getCenterOfText());
  texts.getText("t_die").setShaking(true);
  texts.getText("t_die").hide();

  ShakingText t_game_score("", font1);
  texts.addText("game_score", t_game_score);

  game_score += player.getScore();
  std::ostringstream _score_string;
  _score_string << game_score;
  texts.getText("game_score").text().setString("Bitcoins: " + _score_string.str());
  texts.getText("game_score").text().setOrigin(texts.getText("game_score").getCenterOfText());


  //////////////////
  //Shop components
  //////////////////
  createPlayerSkin("skin1", "Basic", "Simple wallet.", PS_SKIN1);
  shop_texts.getText("ps_name_skin1").text().setPosition(100,120);
  shop_texts.getText("ps_des_skin1").text().setPosition(100,150);

  createPlayerSkin("skin2", "Happy Wallet", "Happy wallet\nwith nice smile.\nCost:20", PS_SKIN2);
  shop_texts.getText("ps_name_skin2").text().setPosition(250,120);
  shop_texts.getText("ps_des_skin2").text().setPosition(250,150);

  createPlayerSkin("skin3", "Kitty Wallet", "Wallet looks\nlike a cat.\nCost: 30", PS_SKIN3);
  shop_texts.getText("ps_name_skin3").text().setPosition(400,120);
  shop_texts.getText("ps_des_skin3").text().setPosition(400,150);

  createPlayerSkin("skin4", "Ninja Wallet", "Wallet\nmade only\nfor ninja.\nCost: 40", PS_SKIN4);
  shop_texts.getText("ps_name_skin4").text().setPosition(550,120);
  shop_texts.getText("ps_des_skin4").text().setPosition(550,150);

  createPlayerSkin("skin5", "Vampire Wallet", "Vampire\nwants\nmore bitcoins.\nCost: 50", PS_SKIN5);
  shop_texts.getText("ps_name_skin5").text().setPosition(100,390);
  shop_texts.getText("ps_des_skin5").text().setPosition(100,420);

  createPlayerSkin("skin6", "Pirat Wallet", "Pirates\nflow on\nbitcoins.\nCost: 60", PS_SKIN6);
  shop_texts.getText("ps_name_skin6").text().setPosition(250,390);
  shop_texts.getText("ps_des_skin6").text().setPosition(250,420);

  createPlayerSkin("skin7", "Creazy Wallet", "Creazy!\nI want more\nbitcoins!.\nCost: 70", PS_SKIN7);
  shop_texts.getText("ps_name_skin7").text().setPosition(400,390);
  shop_texts.getText("ps_des_skin7").text().setPosition(400,420);

  createPlayerSkin("skin8", "Smart Wallet", "Wallet\nfull of\nknowledge.\nCost: 80", PS_SKIN8);
  shop_texts.getText("ps_name_skin8").text().setPosition(550,390);
  shop_texts.getText("ps_des_skin8").text().setPosition(550,420);

  createEnemySkin("skin1", "Stone", "Stones come\nfrom heaven.", ES_SKIN1);
  shop_texts.getText("es_name_skin1").text().setPosition(100,120);
  shop_texts.getText("es_des_skin1").text().setPosition(100,150);

  createEnemySkin("skin2", "Shuriken", "Deadly shurkiens\nare attacking.\nCost: 20", ES_SKIN2);
  shop_texts.getText("es_name_skin2").text().setPosition(250,120);
  shop_texts.getText("es_des_skin2").text().setPosition(250,150);

  createEnemySkin("skin3", "Chest", "Careful!\nChests\nfalling down.\nCost: 30", ES_SKIN3);
  shop_texts.getText("es_name_skin3").text().setPosition(400,120);
  shop_texts.getText("es_des_skin3").text().setPosition(400,150);

  createEnemySkin("skin4", "Flowerpot", "Angry man\nthrows\nflowerpots.\nCost: 40", ES_SKIN4);
  shop_texts.getText("es_name_skin4").text().setPosition(550,120);
  shop_texts.getText("es_des_skin4").text().setPosition(550,150);

  createEnemySkin("skin5", "Deadly ball", "Ball which\nkill\neverybody.\nCost: 50", ES_SKIN5);
  shop_texts.getText("es_name_skin5").text().setPosition(100,420);
  shop_texts.getText("es_des_skin5").text().setPosition(100,450);

  createEnemySkin("skin6", "Stalagmite", "Stalagmites\nare in caves.\nCareful!\nCost: 60", ES_SKIN6);
  shop_texts.getText("es_name_skin6").text().setPosition(250,420);
  shop_texts.getText("es_des_skin6").text().setPosition(250,450);

  createEnemySkin("skin7", "Hammer", "Hammers\nare very\ndangerous!\nCost: 70", ES_SKIN7);
  shop_texts.getText("es_name_skin7").text().setPosition(400,420);
  shop_texts.getText("es_des_skin7").text().setPosition(400,450);

  createEnemySkin("skin8", "Meteorite", "Meteorites\nare comming\nfrom space!\nCost: 80", ES_SKIN8);
  shop_texts.getText("es_name_skin8").text().setPosition(550,420);
  shop_texts.getText("es_des_skin8").text().setPosition(550,450);

  select_rectangle.setSize(sf::Vector2f(150, 260));
  select_rectangle.setFillColor(sf::Color::Transparent);
  select_rectangle.setOutlineColor(sf::Color::Transparent);
  select_rectangle.setOutlineThickness(5);
  select_rectangle.setPosition(80, 10);

  ShakingText t_back("Back", font1);
  t_back.text().setPosition(700,550);
  shop_texts.addText("btn_back", t_back);

  ShakingText t_buy("Buy", font1);
  t_buy.text().setPosition(25,550);
  shop_texts.addText("btn_buy", t_buy);

  ShakingText t_equip("Equip", font1);
  t_equip.text().setPosition(25,550);
  shop_texts.addText("btn_equip", t_equip);

  ShakingText t_playerskin("Player Skins", font1);
  t_playerskin.text().setPosition(200,200);
  shop_texts.addText("btn_playerskins", t_playerskin);

  ShakingText t_enemyskin("Enemy Skins", font1);
  t_enemyskin.text().setPosition(200,250);
  shop_texts.addText("btn_enemyskins", t_enemyskin);

  shop_state = MAINSHOP;
  select_player_skin = PS_SKIN1;
  select_enemy_skin = ES_SKIN1;
  ////////////
  //end shop
  ////////////

}
