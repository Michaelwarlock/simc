#include "class_modules/apl/apl_death_knight.hpp"

#include "player/action_priority_list.hpp"
#include "player/player.hpp"
#include "dbc/dbc.hpp"

namespace death_knight_apl
{

std::string potion( const player_t* p )
{
  std::string frost_potion = ( p->true_level >= 71 ) ? "tempered_potion_3" : "elemental_potion_of_ultimate_power_3";

  std::string unholy_potion = ( p->true_level >= 71 ) ? "tempered_potion_3" : "elemental_potion_of_ultimate_power_3";

  std::string blood_potion = ( p->true_level >= 71 ) ? "tempered_potion_3" : "elemental_potion_of_ultimate_power_3";

  switch ( p->specialization() )
  {
    case DEATH_KNIGHT_BLOOD:
      return blood_potion;
    case DEATH_KNIGHT_FROST:
      return frost_potion;
    default:
      return unholy_potion;
  }
}

std::string flask( const player_t* p )
{
  std::string frost_flask = ( p->true_level >= 71 ) ? "flask_of_alchemical_chaos_3" : "iced_phial_of_corrupting_rage_3";

  std::string unholy_flask = ( p->true_level >= 71 ) ? "flask_of_tempered_mastery_3" : "iced_phial_of_corrupting_rage_3";

  std::string blood_flask = ( p->true_level >= 71 ) ? "flask_of_alchemical_chaos_3" : "iced_phial_of_corrupting_rage_3";

  switch ( p->specialization() )
  {
    case DEATH_KNIGHT_BLOOD:
      return blood_flask;
    case DEATH_KNIGHT_FROST:
      return frost_flask;
    default:
      return unholy_flask;
  }
}

std::string food( const player_t* p )
{
  std::string frost_food;
  std::string unholy_food;
  std::string blood_food;

  if ( p->true_level >= 71 )
  {
    frost_food = "feast_of_the_divine_day";
    unholy_food = "feast_of_the_divine_day";
    blood_food = "feast_of_the_divine_day";
  }
  else
  {
    frost_food = "sizzling_seafood_medley";
    unholy_food = "sizzling_seafood_medley";
    blood_food = "great_cerulean_sea";
  }

  switch ( p->specialization() )
  {
    case DEATH_KNIGHT_BLOOD:
      return blood_food;
    case DEATH_KNIGHT_FROST:
      return frost_food;

    default:
      return unholy_food;
  }
}

std::string rune( const player_t* p )
{
  return ( p->true_level >= 71 ) ? "crystallized" : "draconic";
}

std::string temporary_enchant( const player_t* p )
{
  std::string frost_temporary_enchant = ( p->true_level >= 71 )
                                            ? "main_hand:algari_mana_oil_3/off_hand:algari_mana_oil_3"
                                            : "main_hand:buzzing_rune_3/off_hand:buzzing_rune_3";

  std::string unholy_temporary_enchant =
      ( p->true_level >= 71 ) ? "main_hand:algari_mana_oil_3" : "main_hand:howling_rune_3";

  std::string blood_temporary_enchant =
      ( p->true_level >= 71 ) ? "main_hand:algari_mana_oil_3" : "main_hand:howling_rune_3";

  switch ( p->specialization() )
  {
    case DEATH_KNIGHT_BLOOD:
      return blood_temporary_enchant;
    case DEATH_KNIGHT_FROST:
      return frost_temporary_enchant;

    default:
      return unholy_temporary_enchant;
  }
}

  //blood_apl_start
  void blood( player_t* p )
  {
    action_priority_list_t* default_ = p->get_action_priority_list( "default" );
    action_priority_list_t* precombat = p->get_action_priority_list( "precombat" );
    action_priority_list_t* drw_up = p->get_action_priority_list( "drw_up" );
    action_priority_list_t* racials = p->get_action_priority_list( "racials" );
    action_priority_list_t* standard = p->get_action_priority_list( "standard" );
    action_priority_list_t* trinkets = p->get_action_priority_list( "trinkets" );

    precombat->add_action( "flask" );
    precombat->add_action( "food" );
    precombat->add_action( "augmentation" );
    precombat->add_action( "snapshot_stats" );
    precombat->add_action( "variable,name=trinket_1_buffs,value=trinket.1.has_use_buff|(trinket.1.has_buff.strength|trinket.1.has_buff.mastery|trinket.1.has_buff.versatility|trinket.1.has_buff.haste|trinket.1.has_buff.crit)|trinket.1.is.mirror_of_fractured_tomorrows" );
    precombat->add_action( "variable,name=trinket_2_buffs,value=trinket.2.has_use_buff|(trinket.2.has_buff.strength|trinket.2.has_buff.mastery|trinket.2.has_buff.versatility|trinket.2.has_buff.haste|trinket.2.has_buff.crit)|trinket.2.is.mirror_of_fractured_tomorrows" );
    precombat->add_action( "variable,name=trinket_1_exclude,value=trinket.1.is.ruby_whelp_shell|trinket.1.is.whispering_incarnate_icon" );
    precombat->add_action( "variable,name=trinket_2_exclude,value=trinket.2.is.ruby_whelp_shell|trinket.2.is.whispering_incarnate_icon" );
    precombat->add_action( "variable,name=damage_trinket_priority,op=setif,value=2,value_else=1,condition=!variable.trinket_2_buffs&trinket.2.ilvl>=trinket.1.ilvl|variable.trinket_1_buffs" );

    default_->add_action( "auto_attack" );
    default_->add_action( "variable,name=death_strike_dump_amount,value=65" );
    default_->add_action( "variable,name=bone_shield_refresh_value,value=4,op=setif,condition=talent.consumption.enabled|talent.blooddrinker.enabled,value_else=5" );
    default_->add_action( "mind_freeze,if=target.debuff.casting.react" );
    default_->add_action( "invoke_external_buff,name=power_infusion,if=buff.dancing_rune_weapon.up|!talent.dancing_rune_weapon", "Use <a href='https://www.wowhead.com/spell=10060/power-infusion'>Power Infusion</a> while <a href='https://www.wowhead.com/spell=49028/dancing-rune-weapon'>Dancing Rune Weapon</a> is up, or on cooldown if <a href='https://www.wowhead.com/spell=49028/dancing-rune-weapon'>Dancing Rune Weapon</a> is not talented" );
    default_->add_action( "potion,if=buff.dancing_rune_weapon.up" );
    default_->add_action( "call_action_list,name=trinkets" );
    default_->add_action( "raise_dead" );
    default_->add_action( "reapers_mark" );

    default_->add_action( "icebound_fortitude,if=!(buff.dancing_rune_weapon.up|buff.vampiric_blood.up)&(target.cooldown.pause_action.remains>=8|target.cooldown.pause_action.duration>0)" );
    default_->add_action( "vampiric_blood,if=!(buff.dancing_rune_weapon.up|buff.icebound_fortitude.up|buff.vampiric_blood.up)&(target.cooldown.pause_action.remains>=13|target.cooldown.pause_action.duration>0)" );
    default_->add_action( "deaths_caress,if=!buff.bone_shield.up" );
    default_->add_action( "death_and_decay,if=!death_and_decay.ticking&(talent.unholy_ground|talent.sanguine_ground|spell_targets.death_and_decay>3|buff.crimson_scourge.up)" );
    default_->add_action( "death_strike,if=buff.coagulopathy.remains<=gcd|buff.icy_talons.remains<=gcd|runic_power>=variable.death_strike_dump_amount|runic_power.deficit<=variable.heart_strike_rp|target.time_to_die<10" );
    default_->add_action( "blooddrinker,if=!buff.dancing_rune_weapon.up" );
    default_->add_action( "call_action_list,name=racials" );
    default_->add_action( "sacrificial_pact,if=!buff.dancing_rune_weapon.up&(pet.ghoul.remains<2|target.time_to_die<gcd)" );
    default_->add_action( "blood_tap,if=(rune<=2&rune.time_to_4>gcd&charges_fractional>=1.8)|rune.time_to_3>gcd" );
    default_->add_action( "gorefiends_grasp,if=talent.tightening_grasp.enabled" );
    default_->add_action( "empower_rune_weapon,if=rune<6&runic_power.deficit>5" );
    default_->add_action( "abomination_limb" );
    default_->add_action( "dancing_rune_weapon,if=!buff.dancing_rune_weapon.up" );
    default_->add_action( "run_action_list,name=drw_up,if=buff.dancing_rune_weapon.up" );
    default_->add_action( "call_action_list,name=standard" );

    drw_up->add_action( "blood_boil,if=!dot.blood_plague.ticking" );
    drw_up->add_action( "tombstone,if=buff.bone_shield.stack>5&rune>=2&runic_power.deficit>=30&!talent.shattering_bone|(talent.shattering_bone.enabled&death_and_decay.ticking)" );
    drw_up->add_action( "death_strike,if=buff.coagulopathy.remains<=gcd|buff.icy_talons.remains<=gcd" );
    drw_up->add_action( "marrowrend,if=(buff.bone_shield.remains<=4|buff.bone_shield.stack<variable.bone_shield_refresh_value)&runic_power.deficit>20" );
    drw_up->add_action( "soul_reaper,if=active_enemies=1&target.time_to_pct_35<5&target.time_to_die>(dot.soul_reaper.remains+5)" );
    drw_up->add_action( "soul_reaper,target_if=min:dot.soul_reaper.remains,if=target.time_to_pct_35<5&active_enemies>=2&target.time_to_die>(dot.soul_reaper.remains+5)" );
    drw_up->add_action( "death_and_decay,if=!death_and_decay.ticking&(talent.sanguine_ground|talent.unholy_ground)" );
    drw_up->add_action( "blood_boil,if=spell_targets.blood_boil>2&charges_fractional>=1.1" );
    drw_up->add_action( "variable,name=heart_strike_rp_drw,value=(25+spell_targets.heart_strike*talent.heartbreaker.enabled*2)" );
    drw_up->add_action( "death_strike,if=runic_power.deficit<=variable.heart_strike_rp_drw|runic_power>=variable.death_strike_dump_amount" );
    drw_up->add_action( "consumption" );
    drw_up->add_action( "blood_boil,if=charges_fractional>=1.1&buff.hemostasis.stack<5" );
    drw_up->add_action( "heart_strike,if=rune.time_to_2<gcd|runic_power.deficit>=variable.heart_strike_rp_drw" );

    racials->add_action( "blood_fury,if=cooldown.dancing_rune_weapon.ready&(!cooldown.blooddrinker.ready|!talent.blooddrinker.enabled)" );
    racials->add_action( "berserking" );
    racials->add_action( "arcane_pulse,if=active_enemies>=2|rune<1&runic_power.deficit>60" );
    racials->add_action( "lights_judgment,if=buff.unholy_strength.up" );
    racials->add_action( "ancestral_call" );
    racials->add_action( "fireblood" );
    racials->add_action( "bag_of_tricks" );
    racials->add_action( "arcane_torrent,if=runic_power.deficit>20" );

    standard->add_action( "tombstone,if=buff.bone_shield.stack>5&rune>=2&runic_power.deficit>=30&!talent.shattering_bone|(talent.shattering_bone.enabled&death_and_decay.ticking)&cooldown.dancing_rune_weapon.remains>=25" );
    standard->add_action( "variable,name=heart_strike_rp,value=(10+spell_targets.heart_strike*talent.heartbreaker.enabled*2)" );
    standard->add_action( "death_strike,if=buff.coagulopathy.remains<=gcd|buff.icy_talons.remains<=gcd|runic_power>=variable.death_strike_dump_amount|runic_power.deficit<=variable.heart_strike_rp|target.time_to_die<10" );
    standard->add_action( "deaths_caress,if=(buff.bone_shield.remains<=4|(buff.bone_shield.stack<variable.bone_shield_refresh_value+1))&runic_power.deficit>10&!(talent.insatiable_blade&cooldown.dancing_rune_weapon.remains<buff.bone_shield.remains)&!talent.consumption.enabled&!talent.blooddrinker.enabled&rune.time_to_3>gcd" );
    standard->add_action( "marrowrend,if=(buff.bone_shield.remains<=4|buff.bone_shield.stack<variable.bone_shield_refresh_value)&runic_power.deficit>20&!(talent.insatiable_blade&cooldown.dancing_rune_weapon.remains<buff.bone_shield.remains)" );
    standard->add_action( "consumption" );
    standard->add_action( "soul_reaper,if=active_enemies=1&target.time_to_pct_35<5&target.time_to_die>(dot.soul_reaper.remains+5)" );
    standard->add_action( "soul_reaper,target_if=min:dot.soul_reaper.remains,if=target.time_to_pct_35<5&active_enemies>=2&target.time_to_die>(dot.soul_reaper.remains+5)" );
    standard->add_action( "bonestorm,if=buff.bone_shield.stack>=5" );
    standard->add_action( "blood_boil,if=charges_fractional>=1.8&(buff.hemostasis.stack<=(5-spell_targets.blood_boil)|spell_targets.blood_boil>2)" );
    standard->add_action( "heart_strike,if=rune.time_to_4<gcd" );
    standard->add_action( "blood_boil,if=charges_fractional>=1.1" );
    standard->add_action( "heart_strike,if=(rune>1&(rune.time_to_3<gcd|buff.bone_shield.stack>7))" );

    trinkets->add_action( "use_item,name=fyralath_the_dreamrender,if=dot.mark_of_fyralath.ticking", "Trinkets" );
    trinkets->add_action( "use_item,use_off_gcd=1,slot=trinket1,if=!variable.trinket_1_buffs&(variable.damage_trinket_priority=1|trinket.2.cooldown.remains|!trinket.2.has_cooldown)", "Prioritize damage dealing on use trinkets over trinkets that give buffs" );
    trinkets->add_action( "use_item,use_off_gcd=1,slot=trinket2,if=!variable.trinket_2_buffs&(variable.damage_trinket_priority=2|trinket.1.cooldown.remains|!trinket.1.has_cooldown)" );
    trinkets->add_action( "use_item,use_off_gcd=1,slot=main_hand,if=!equipped.fyralath_the_dreamrender&(variable.trinket_1_buffs|trinket.1.cooldown.remains)&(variable.trinket_2_buffs|trinket.2.cooldown.remains)" );
    trinkets->add_action( "use_item,use_off_gcd=1,slot=trinket1,if=variable.trinket_1_buffs&(buff.dancing_rune_weapon.up|!talent.dancing_rune_weapon|cooldown.dancing_rune_weapon.remains>20)&(variable.trinket_2_exclude|trinket.2.cooldown.remains|!trinket.2.has_cooldown|variable.trinket_2_buffs)" );
    trinkets->add_action( "use_item,use_off_gcd=1,slot=trinket2,if=variable.trinket_2_buffs&(buff.dancing_rune_weapon.up|!talent.dancing_rune_weapon|cooldown.dancing_rune_weapon.remains>20)&(variable.trinket_1_exclude|trinket.1.cooldown.remains|!trinket.1.has_cooldown|variable.trinket_1_buffs)" );
  }
  //blood_apl_end

//frost_apl_start
void frost( player_t* p )
{
  action_priority_list_t* default_ = p->get_action_priority_list( "default" );
  action_priority_list_t* precombat = p->get_action_priority_list( "precombat" );
  action_priority_list_t* aoe = p->get_action_priority_list( "aoe" );
  action_priority_list_t* breath = p->get_action_priority_list( "breath" );
  action_priority_list_t* cold_heart = p->get_action_priority_list( "cold_heart" );
  action_priority_list_t* cooldowns = p->get_action_priority_list( "cooldowns" );
  action_priority_list_t* high_prio_actions = p->get_action_priority_list( "high_prio_actions" );
  action_priority_list_t* obliteration = p->get_action_priority_list( "obliteration" );
  action_priority_list_t* racials = p->get_action_priority_list( "racials" );
  action_priority_list_t* single_target = p->get_action_priority_list( "single_target" );
  action_priority_list_t* trinkets = p->get_action_priority_list( "trinkets" );
  action_priority_list_t* variables = p->get_action_priority_list( "variables" );

  precombat->add_action( "flask" );
  precombat->add_action( "food" );
  precombat->add_action( "augmentation" );
  precombat->add_action( "snapshot_stats", "Snapshot raid buffed stats before combat begins and pre-potting is done." );
  precombat->add_action( "variable,name=trinket_1_exclude,value=trinket.1.is.ruby_whelp_shell|trinket.1.is.whispering_incarnate_icon" );
  precombat->add_action( "variable,name=trinket_2_exclude,value=trinket.2.is.ruby_whelp_shell|trinket.2.is.whispering_incarnate_icon" );
  precombat->add_action( "variable,name=trinket_1_sync,op=setif,value=1,value_else=0.5,condition=trinket.1.has_use_buff&(talent.pillar_of_frost&!talent.breath_of_sindragosa&(trinket.1.cooldown.duration%%cooldown.pillar_of_frost.duration=0)|talent.breath_of_sindragosa&(cooldown.breath_of_sindragosa.duration%%trinket.1.cooldown.duration=0))", "Evaluates a trinkets cooldown, divided by pillar of frost, empower rune weapon, or breath of sindragosa's cooldown. If it's value has no remainder return 1, else return 0.5." );
  precombat->add_action( "variable,name=trinket_2_sync,op=setif,value=1,value_else=0.5,condition=trinket.2.has_use_buff&(talent.pillar_of_frost&!talent.breath_of_sindragosa&(trinket.2.cooldown.duration%%cooldown.pillar_of_frost.duration=0)|talent.breath_of_sindragosa&(cooldown.breath_of_sindragosa.duration%%trinket.2.cooldown.duration=0))" );
  precombat->add_action( "variable,name=trinket_1_buffs,value=trinket.1.has_use_buff|(trinket.1.has_buff.strength|trinket.1.has_buff.mastery|trinket.1.has_buff.versatility|trinket.1.has_buff.haste|trinket.1.has_buff.crit&!variable.trinket_1_exclude)" );
  precombat->add_action( "variable,name=trinket_2_buffs,value=trinket.2.has_use_buff|(trinket.2.has_buff.strength|trinket.2.has_buff.mastery|trinket.2.has_buff.versatility|trinket.2.has_buff.haste|trinket.2.has_buff.crit&!variable.trinket_2_exclude)" );
  precombat->add_action( "variable,name=trinket_priority,op=setif,value=2,value_else=1,condition=!variable.trinket_1_buffs&variable.trinket_2_buffs&(trinket.2.has_cooldown&!variable.trinket_2_exclude|!trinket.1.has_cooldown)|variable.trinket_2_buffs&((trinket.2.cooldown.duration%trinket.2.proc.any_dps.duration)*(1.5+trinket.2.has_buff.strength)*(variable.trinket_2_sync))>((trinket.1.cooldown.duration%trinket.1.proc.any_dps.duration)*(1.5+trinket.1.has_buff.strength)*(variable.trinket_1_sync)*(1+((trinket.1.ilvl-trinket.2.ilvl)%100)))" );
  precombat->add_action( "variable,name=damage_trinket_priority,op=setif,value=2,value_else=1,condition=!variable.trinket_1_buffs&!variable.trinket_2_buffs&trinket.2.ilvl>=trinket.1.ilvl" );
  precombat->add_action( "variable,name=trinket_1_manual,value=trinket.1.is.algethar_puzzle_box" );
  precombat->add_action( "variable,name=trinket_2_manual,value=trinket.2.is.algethar_puzzle_box" );
  precombat->add_action( "variable,name=rw_buffs,value=talent.gathering_storm|talent.biting_cold" );
  precombat->add_action( "variable,name=2h_check,value=main_hand.2h" );
  precombat->add_action( "variable,name=static_obliterate_buffs,value=talent.arctic_assault|talent.frigid_executioner|variable.2h_check" );
  precombat->add_action( "variable,name=breath_rp_cost,value=dbc.power.9067.cost_per_tick%10" );
  precombat->add_action( "variable,name=static_rime_buffs,value=talent.rage_of_the_frozen_champion|talent.icebreaker" );
  precombat->add_action( "variable,name=breath_rp_threshold,default=70,op=reset", "APL Variable Option: How much Runic Power to pool before casting Breath of Sindragosa" );
  precombat->add_action( "variable,name=erw_breath_rp_trigger,default=70,op=reset", "APL Variable Option: Used with erw_breath_rune_trigger to determine when resources are low enough to use Empower Rune Weapon" );
  precombat->add_action( "variable,name=erw_breath_rune_trigger,default=3,op=reset", "APL Variable Option: Used with erw_breath_rp_trigger to determine when resources are low enough to use Empower Rune Weapon" );
  precombat->add_action( "variable,name=oblit_rune_pooling,default=4,op=reset", "APL Variable Option: How many Runes the APL will try to pool for Pillar of Frost with Obliteration. It is not a guarantee, just a goal." );
  precombat->add_action( "variable,name=breath_rime_rp_threshold,default=60,op=reset", "APL Variable Option: Amount of Runic Power pooled during Breath of Sindragosa to be able to use Rime" );

  default_->add_action( "auto_attack" );
  default_->add_action( "call_action_list,name=variables", "Choose Action list to run" );
  default_->add_action( "call_action_list,name=trinkets" );
  default_->add_action( "call_action_list,name=high_prio_actions" );
  default_->add_action( "call_action_list,name=cooldowns" );
  default_->add_action( "call_action_list,name=racials" );
  default_->add_action( "call_action_list,name=cold_heart,if=talent.cold_heart&(!buff.killing_machine.up|talent.breath_of_sindragosa)&((debuff.razorice.stack=5|!death_knight.runeforge.razorice&!talent.glacial_advance&!talent.avalanche&!talent.arctic_assault)|fight_remains<=gcd)" );
  default_->add_action( "run_action_list,name=breath,if=buff.breath_of_sindragosa.up" );
  default_->add_action( "run_action_list,name=obliteration,if=talent.obliteration&buff.pillar_of_frost.up&!buff.breath_of_sindragosa.up" );
  default_->add_action( "call_action_list,name=aoe,if=active_enemies>=2" );
  default_->add_action( "call_action_list,name=single_target,if=active_enemies=1" );

  aoe->add_action( "obliterate,if=buff.killing_machine.react&talent.cleaving_strikes&buff.death_and_decay.up", "AoE Action List" );
  aoe->add_action( "howling_blast,if=!dot.frost_fever.ticking" );
  aoe->add_action( "frost_strike,target_if=max:((talent.shattering_blade&debuff.razorice.stack=5)*5)+(debuff.razorice.stack+1)%(debuff.razorice.remains+1)*death_knight.runeforge.razorice,if=!variable.pooling_runic_power&debuff.razorice.stack=5&talent.shattering_blade&(talent.shattered_frost|active_enemies<4)" );
  aoe->add_action( "howling_blast,if=buff.rime.react|!dot.frost_fever.ticking" );
  aoe->add_action( "glacial_advance,target_if=max:(debuff.razorice.stack),if=!variable.pooling_runic_power&(variable.ga_priority|debuff.razorice.stack<5)" );
  aoe->add_action( "obliterate" );
  aoe->add_action( "frost_strike,target_if=max:((talent.shattering_blade&debuff.razorice.stack=5)*5)+(debuff.razorice.stack+1)%(debuff.razorice.remains+1)*death_knight.runeforge.razorice,if=!variable.pooling_runic_power" );
  aoe->add_action( "horn_of_winter,if=rune<2&runic_power.deficit>25" );
  aoe->add_action( "arcane_torrent,if=runic_power.deficit>25" );

  breath->add_action( "howling_blast,if=variable.rime_buffs&runic_power>(variable.breath_rime_rp_threshold-(talent.rage_of_the_frozen_champion*(dbc.effect.842306.base_value%10)))", "Breath Active Rotation" );
  breath->add_action( "horn_of_winter,if=rune<2&runic_power.deficit>30&(!buff.empower_rune_weapon.up|variable.breath_dying)" );
  breath->add_action( "obliterate,target_if=max:(debuff.razorice.stack+1)%(debuff.razorice.remains+1)*death_knight.runeforge.razorice,if=buff.killing_machine.react|runic_power.deficit>20" );
  breath->add_action( "remorseless_winter,if=variable.breath_dying" );
  breath->add_action( "death_and_decay,if=!buff.mograines_might.up&variable.st_planning&talent.unholy_ground&!buff.death_and_decay.up&runic_power.deficit>=10&!talent.obliteration|variable.breath_dying" );
  breath->add_action( "howling_blast,if=variable.breath_dying" );
  breath->add_action( "arcane_torrent,if=runic_power<60" );
  breath->add_action( "howling_blast,if=buff.rime.react" );

  cold_heart->add_action( "chains_of_ice,if=fight_remains<gcd&(rune<2|!buff.killing_machine.up&(!variable.2h_check&buff.cold_heart.stack>=4|variable.2h_check&buff.cold_heart.stack>8)|buff.killing_machine.up&(!variable.2h_check&buff.cold_heart.stack>8|variable.2h_check&buff.cold_heart.stack>10))", "Cold Heart" );
  cold_heart->add_action( "chains_of_ice,if=!talent.obliteration&buff.pillar_of_frost.up&buff.cold_heart.stack>=10&(buff.pillar_of_frost.remains<gcd*(1+(talent.frostwyrms_fury&cooldown.frostwyrms_fury.ready))|buff.unholy_strength.up&buff.unholy_strength.remains<gcd)" );
  cold_heart->add_action( "chains_of_ice,if=!talent.obliteration&death_knight.runeforge.fallen_crusader&!buff.pillar_of_frost.up&cooldown.pillar_of_frost.remains_expected>15&(buff.cold_heart.stack>=10&buff.unholy_strength.up|buff.cold_heart.stack>=13)" );
  cold_heart->add_action( "chains_of_ice,if=!talent.obliteration&!death_knight.runeforge.fallen_crusader&buff.cold_heart.stack>=10&!buff.pillar_of_frost.up&cooldown.pillar_of_frost.remains_expected>20" );
  cold_heart->add_action( "chains_of_ice,if=talent.obliteration&!buff.pillar_of_frost.up&(buff.cold_heart.stack>=14&buff.unholy_strength.up|buff.cold_heart.stack>=19|cooldown.pillar_of_frost.remains_expected<3&buff.cold_heart.stack>=14)" );

  cooldowns->add_action( "potion,if=(talent.pillar_of_frost&buff.pillar_of_frost.up|!talent.pillar_of_frost&buff.empower_rune_weapon.up|!talent.pillar_of_frost&!talent.empower_rune_weapon|active_enemies>=2&buff.pillar_of_frost.up)|fight_remains<25", "Cooldowns" );
  cooldowns->add_action( "abomination_limb,if=talent.obliteration&!buff.pillar_of_frost.up&variable.sending_cds|fight_remains<15" );
  cooldowns->add_action( "abomination_limb,if=!talent.obliteration&variable.sending_cds" );
  cooldowns->add_action( "remorseless_winter,if=variable.rw_buffs&variable.sending_cds&(!talent.arctic_assault|!buff.pillar_of_frost.up)" );
  cooldowns->add_action( "chill_streak,if=variable.sending_cds&(!talent.arctic_assault|!buff.pillar_of_frost.up)" );
  cooldowns->add_action( "reapers_mark,target_if=first:!debuff.reapers_mark_debuff.up" );
  cooldowns->add_action( "empower_rune_weapon,if=talent.obliteration&!talent.breath_of_sindragosa&buff.pillar_of_frost.up|fight_remains<20" );
  cooldowns->add_action( "empower_rune_weapon,if=buff.breath_of_sindragosa.up&runic_power<variable.erw_breath_rp_trigger&rune<variable.erw_breath_rune_trigger|fight_remains<20" );
  cooldowns->add_action( "empower_rune_weapon,if=!talent.breath_of_sindragosa&!talent.obliteration&!buff.empower_rune_weapon.up&rune<5&(cooldown.pillar_of_frost.remains_expected<7|buff.pillar_of_frost.up|!talent.pillar_of_frost)" );
  cooldowns->add_action( "pillar_of_frost,if=talent.obliteration&!talent.breath_of_sindragosa&variable.sending_cds|fight_remains<12" );
  cooldowns->add_action( "pillar_of_frost,if=talent.breath_of_sindragosa&variable.sending_cds&(buff.breath_of_sindragosa.up|cooldown.breath_of_sindragosa.remains>cooldown.pillar_of_frost.duration-20)|fight_remains<12" );
  cooldowns->add_action( "pillar_of_frost,if=!talent.obliteration&!talent.breath_of_sindragosa&variable.sending_cds" );
  cooldowns->add_action( "breath_of_sindragosa,if=!buff.breath_of_sindragosa.up&cooldown.empower_rune_weapon.remains_expected<15&runic_power>variable.breath_rp_threshold&(variable.adds_remain|variable.st_planning|fight_remains<30)|(time<10&rune<1)" );
  cooldowns->add_action( "frostwyrms_fury,if=hero_tree.rider_of_the_apocalypse&talent.apocalypse_now&(!talent.breath_of_sindragosa&variable.sending_cds|buff.breath_of_sindragosa.up&buff.pillar_of_frost.up)|fight_remains<20" );
  cooldowns->add_action( "frostwyrms_fury,if=!talent.apocalypse_now&active_enemies=1&(talent.pillar_of_frost&buff.pillar_of_frost.up&!talent.obliteration|!talent.pillar_of_frost)&(!raid_event.adds.exists|(raid_event.adds.in>15+raid_event.adds.duration|talent.absolute_zero&raid_event.adds.in>15+raid_event.adds.duration))|fight_remains<3" );
  cooldowns->add_action( "frostwyrms_fury,if=!talent.apocalypse_now&active_enemies>=2&(talent.pillar_of_frost&buff.pillar_of_frost.up|raid_event.adds.exists&raid_event.adds.up&raid_event.adds.in>cooldown.pillar_of_frost.remains_expected-raid_event.adds.in-raid_event.adds.duration)" );
  cooldowns->add_action( "frostwyrms_fury,if=!talent.apocalypse_now&talent.obliteration&(talent.pillar_of_frost&buff.pillar_of_frost.up&!variable.2h_check|!buff.pillar_of_frost.up&variable.2h_check&cooldown.pillar_of_frost.remains|!talent.pillar_of_frost)&((buff.pillar_of_frost.remains<gcd|buff.unholy_strength.up)&(debuff.razorice.stack=5|!death_knight.runeforge.razorice&!talent.glacial_advance))" );
  cooldowns->add_action( "raise_dead" );
  cooldowns->add_action( "soul_reaper,if=fight_remains>5&target.time_to_pct_35<5&target.time_to_pct_0>5&active_enemies<=2&(talent.obliteration&(buff.pillar_of_frost.up&!buff.killing_machine.react&rune>2|!buff.pillar_of_frost.up)|talent.breath_of_sindragosa&(buff.breath_of_sindragosa.up&runic_power>50|!buff.breath_of_sindragosa.up)|!talent.breath_of_sindragosa&!talent.obliteration)" );
  cooldowns->add_action( "frostscythe,if=!buff.killing_machine.up&(!talent.arctic_assault|!buff.pillar_of_frost.up)" );
  cooldowns->add_action( "any_dnd,if=!buff.death_and_decay.up&!buff.mograines_might.up&variable.adds_remain&(buff.pillar_of_frost.up&buff.killing_machine.react&(talent.enduring_strength|buff.pillar_of_frost.remains>5)|!buff.pillar_of_frost.up&(cooldown.death_and_decay.charges=2|cooldown.pillar_of_frost.remains>cooldown.death_and_decay.duration)|!talent.the_long_winter&cooldown.pillar_of_frost.remains<gcd.max*2|fight_remains<11)&(active_enemies>5|talent.cleaving_strikes&active_enemies>=2)" );

  high_prio_actions->add_action( "invoke_external_buff,name=power_infusion,if=(buff.pillar_of_frost.up|!talent.pillar_of_frost)&(talent.obliteration|talent.breath_of_sindragosa&buff.breath_of_sindragosa.up|!talent.breath_of_sindragosa&!talent.obliteration)", "High Priority Actions Use <a href='https://www.wowhead.com/spell=10060/power-infusion'>Power Infusion</a> while <a href='https://www.wowhead.com/spell=51271/pillar-of-frost'>Pillar of Frost</a> is up, as well as <a href='https://www.wowhead.com/spell=152279/breath-of-sindragosa'>Breath of Sindragosa</a> or on cooldown if <a href='https://www.wowhead.com/spell=51271/pillar-of-frost'>Pillar of Frost</a> and <a href='https://www.wowhead.com/spell=152279/breath-of-sindragosa'>Breath of Sindragosa</a> are not talented" );
  high_prio_actions->add_action( "mind_freeze,if=target.debuff.casting.react", "Interrupt" );
  high_prio_actions->add_action( "antimagic_shell,if=runic_power.deficit>40&death_knight.first_ams_cast<time&(!talent.breath_of_sindragosa|talent.breath_of_sindragosa&cooldown.breath_of_sindragosa.remains>cooldown.antimagic_shell.duration)" );
  high_prio_actions->add_action( "howling_blast,if=!dot.frost_fever.ticking&active_enemies>=2&((!talent.obliteration|talent.obliteration&(!cooldown.pillar_of_frost.ready|buff.pillar_of_frost.up&!buff.killing_machine.react))|(equipped.fyralath_the_dreamrender&!dot.mark_of_fyralath.ticking))", "Maintain Frost Fever, Icy Talons and Unleashed Frenzy" );
  high_prio_actions->add_action( "glacial_advance,if=variable.ga_priority&variable.rp_buffs&talent.obliteration&talent.breath_of_sindragosa&!buff.pillar_of_frost.up&!buff.breath_of_sindragosa.up&cooldown.breath_of_sindragosa.remains>variable.breath_pooling_time" );
  high_prio_actions->add_action( "glacial_advance,if=variable.ga_priority&variable.rp_buffs&talent.breath_of_sindragosa&!buff.breath_of_sindragosa.up&cooldown.breath_of_sindragosa.remains>variable.breath_pooling_time" );
  high_prio_actions->add_action( "glacial_advance,if=variable.ga_priority&variable.rp_buffs&!talent.breath_of_sindragosa&talent.obliteration&!buff.pillar_of_frost.up&!talent.shattered_frost" );
  high_prio_actions->add_action( "frost_strike,target_if=max:((talent.shattering_blade&debuff.razorice.stack=5)*5)+(debuff.razorice.stack+1)%(debuff.razorice.remains+1)*death_knight.runeforge.razorice,if=active_enemies=1&variable.rp_buffs&talent.obliteration&talent.breath_of_sindragosa&!buff.pillar_of_frost.up&!buff.breath_of_sindragosa.up&cooldown.breath_of_sindragosa.remains>variable.breath_pooling_time" );
  high_prio_actions->add_action( "frost_strike,target_if=max:((talent.shattering_blade&debuff.razorice.stack=5)*5)+(debuff.razorice.stack+1)%(debuff.razorice.remains+1)*death_knight.runeforge.razorice,if=active_enemies=1&variable.rp_buffs&talent.breath_of_sindragosa&!buff.breath_of_sindragosa.up&cooldown.breath_of_sindragosa.remains>variable.breath_pooling_time" );
  high_prio_actions->add_action( "frost_strike,target_if=max:((talent.shattering_blade&debuff.razorice.stack=5)*5)+(debuff.razorice.stack+1)%(debuff.razorice.remains+1)*death_knight.runeforge.razorice,if=active_enemies=1&variable.rp_buffs&!talent.breath_of_sindragosa&talent.obliteration&!buff.pillar_of_frost.up" );

  obliteration->add_action( "howling_blast,if=buff.killing_machine.stack<2&buff.pillar_of_frost.remains<gcd&variable.rime_buffs", "Obliteration Active Rotation" );
  obliteration->add_action( "glacial_advance,if=buff.killing_machine.react<2&buff.pillar_of_frost.remains<gcd&!buff.death_and_decay.up&variable.ga_priority" );
  obliteration->add_action( "frost_strike,target_if=max:((talent.shattering_blade&debuff.razorice.stack=5)*5)+(debuff.razorice.stack+1)%(debuff.razorice.remains+1)*death_knight.runeforge.razorice,if=buff.killing_machine.react<2&buff.pillar_of_frost.remains<gcd&!buff.death_and_decay.up" );
  obliteration->add_action( "frost_strike,target_if=max:((talent.shattering_blade&debuff.razorice.stack=5)*5)+(debuff.razorice.stack+1)%(debuff.razorice.remains+1)*death_knight.runeforge.razorice,if=debuff.razorice.stack=5&talent.shattering_blade&talent.a_feast_of_souls&buff.a_feast_of_souls.up&!talent.arctic_assault" );
  obliteration->add_action( "obliterate,target_if=max:(debuff.razorice.stack+1)%(debuff.razorice.remains+1)*death_knight.runeforge.razorice,if=buff.killing_machine.react" );
  obliteration->add_action( "howling_blast,if=!buff.killing_machine.react&(!dot.frost_fever.ticking)" );
  obliteration->add_action( "glacial_advance,target_if=max:(debuff.razorice.stack),if=(variable.ga_priority|debuff.razorice.stack<5)&(!death_knight.runeforge.razorice&(debuff.razorice.stack<5|debuff.razorice.remains<gcd*3)|((variable.rp_buffs|rune<2)&active_enemies>1))" );
  obliteration->add_action( "frost_strike,target_if=max:((talent.shattering_blade&debuff.razorice.stack=5)*5)+(debuff.razorice.stack+1)%(debuff.razorice.remains+1)*death_knight.runeforge.razorice,if=(rune<2|variable.rp_buffs|debuff.razorice.stack=5&talent.shattering_blade)&!variable.pooling_runic_power&(!talent.glacial_advance|active_enemies=1|talent.shattered_frost)" );
  obliteration->add_action( "howling_blast,if=buff.rime.react" );
  obliteration->add_action( "frost_strike,target_if=max:((talent.shattering_blade&debuff.razorice.stack=5)*5)+(debuff.razorice.stack+1)%(debuff.razorice.remains+1)*death_knight.runeforge.razorice,if=!variable.pooling_runic_power&(!talent.glacial_advance|active_enemies=1|talent.shattered_frost)" );
  obliteration->add_action( "glacial_advance,target_if=max:(debuff.razorice.stack),if=!variable.pooling_runic_power&variable.ga_priority" );
  obliteration->add_action( "frost_strike,target_if=max:((talent.shattering_blade&debuff.razorice.stack=5)*5)+(debuff.razorice.stack+1)%(debuff.razorice.remains+1)*death_knight.runeforge.razorice,if=!variable.pooling_runic_power" );
  obliteration->add_action( "horn_of_winter,if=rune<3" );
  obliteration->add_action( "arcane_torrent,if=rune<1&runic_power<30" );
  obliteration->add_action( "howling_blast,if=!buff.killing_machine.up" );

  racials->add_action( "blood_fury,if=variable.cooldown_check", "Racial Abilities" );
  racials->add_action( "berserking,if=variable.cooldown_check" );
  racials->add_action( "arcane_pulse,if=variable.cooldown_check" );
  racials->add_action( "lights_judgment,if=variable.cooldown_check" );
  racials->add_action( "ancestral_call,if=variable.cooldown_check" );
  racials->add_action( "fireblood,if=variable.cooldown_check" );
  racials->add_action( "bag_of_tricks,if=talent.obliteration&!buff.pillar_of_frost.up&buff.unholy_strength.up" );
  racials->add_action( "bag_of_tricks,if=!talent.obliteration&buff.pillar_of_frost.up&(buff.unholy_strength.up&buff.unholy_strength.remains<gcd*3|buff.pillar_of_frost.remains<gcd*3)" );

  single_target->add_action( "frost_strike,if=debuff.razorice.stack=5&talent.shattering_blade&talent.a_feast_of_souls&buff.a_feast_of_souls.up", "Single Target Rotation" );
  single_target->add_action( "obliterate,if=buff.killing_machine.react&variable.static_obliterate_buffs" );
  single_target->add_action( "frost_strike,if=(debuff.razorice.stack=5&talent.shattering_blade)|(buff.killing_machine.up&rune<2&!talent.icebreaker)" );
  single_target->add_action( "howling_blast,if=variable.rime_buffs" );
  single_target->add_action( "obliterate,if=buff.killing_machine.react&(!variable.pooling_runes|buff.killing_machine.react=2)" );
  single_target->add_action( "glacial_advance,if=!variable.pooling_runic_power&!death_knight.runeforge.razorice&(debuff.razorice.stack<5|debuff.razorice.remains<gcd*3)" );
  single_target->add_action( "frost_strike,if=!variable.pooling_runic_power&(variable.rp_buffs|(!talent.shattering_blade&runic_power.deficit<20)|debuff.razorice.stack=5&talent.shattering_blade)" );
  single_target->add_action( "howling_blast,if=buff.rime.react" );
  single_target->add_action( "frost_strike,if=!variable.pooling_runic_power&!(variable.2h_check|talent.shattering_blade)" );
  single_target->add_action( "obliterate,if=!variable.pooling_runes" );
  single_target->add_action( "frost_strike,if=!variable.pooling_runic_power" );
  single_target->add_action( "howling_blast,if=!dot.frost_fever.ticking" );
  single_target->add_action( "any_dnd,if=talent.breath_of_sindragosa&!buff.breath_of_sindragosa.up&!cooldown.breath_of_sindragosa.remains&rune<2&!buff.death_and_decay.up" );
  single_target->add_action( "horn_of_winter,if=rune<2&runic_power.deficit>25&(!talent.breath_of_sindragosa|cooldown.breath_of_sindragosa.remains>cooldown.horn_of_winter.duration-15)" );
  single_target->add_action( "arcane_torrent,if=!talent.breath_of_sindragosa&runic_power.deficit>20" );

  trinkets->add_action( "use_item,name=fyralath_the_dreamrender,if=dot.mark_of_fyralath.ticking&!buff.pillar_of_frost.up&!buff.empower_rune_weapon.up&!buff.death_and_decay.up&(active_enemies<2|dot.frost_fever.ticking)", "Trinkets" );
  trinkets->add_action( "use_item,use_off_gcd=1,name=algethar_puzzle_box,if=!buff.pillar_of_frost.up&cooldown.pillar_of_frost.remains<2&(!talent.breath_of_sindragosa|runic_power>60&(buff.breath_of_sindragosa.up|cooldown.breath_of_sindragosa.remains<2))" );
  trinkets->add_action( "use_item,use_off_gcd=1,slot=trinket1,if=variable.trinket_1_buffs&!variable.trinket_1_manual&(!talent.breath_of_sindragosa&buff.pillar_of_frost.remains>10|talent.breath_of_sindragosa)&(!buff.pillar_of_frost.up&trinket.1.cast_time>0|!trinket.1.cast_time>0)&(buff.breath_of_sindragosa.up&buff.pillar_of_frost.up|!talent.breath_of_sindragosa)&(variable.trinket_2_exclude|!trinket.2.has_cooldown|trinket.2.cooldown.remains|variable.trinket_priority=1)|trinket.1.proc.any_dps.duration>=fight_remains", "Trinkets The trinket with the highest estimated value, will be used first and paired with Pillar of Frost." );
  trinkets->add_action( "use_item,use_off_gcd=1,slot=trinket2,if=variable.trinket_2_buffs&!variable.trinket_2_manual&(!talent.breath_of_sindragosa&buff.pillar_of_frost.remains>10|talent.breath_of_sindragosa)&(!buff.pillar_of_frost.up&trinket.2.cast_time>0|!trinket.2.cast_time>0)&(buff.breath_of_sindragosa.up&buff.pillar_of_frost.up|!talent.breath_of_sindragosa)&(variable.trinket_1_exclude|!trinket.1.has_cooldown|trinket.1.cooldown.remains|variable.trinket_priority=2)|trinket.2.proc.any_dps.duration>=fight_remains" );
  trinkets->add_action( "use_item,use_off_gcd=1,slot=trinket1,if=!variable.trinket_1_buffs&!variable.trinket_1_manual&((variable.damage_trinket_priority=1|trinket.2.cooldown.remains)|(trinket.1.cast_time>0&!buff.pillar_of_frost.up|!trinket.1.cast_time>0&cooldown.pillar_of_frost.remains>20)|talent.pillar_of_frost&cooldown.pillar_of_frost.remains_expected>20|!talent.pillar_of_frost)", "If only one on use trinket provides a buff, use the other on cooldown. Or if neither trinket provides a buff, use both on cooldown." );
  trinkets->add_action( "use_item,use_off_gcd=1,slot=trinket2,if=!variable.trinket_2_buffs&!variable.trinket_2_manual&((variable.damage_trinket_priority=2|trinket.1.cooldown.remains)|(trinket.2.cast_time>0&!buff.pillar_of_frost.up|!trinket.2.cast_time>0&cooldown.pillar_of_frost.remains>20)|talent.pillar_of_frost&cooldown.pillar_of_frost.remains_expected>20|!talent.pillar_of_frost)" );
  trinkets->add_action( "use_item,use_off_gcd=1,slot=main_hand,if=!equipped.fyralath_the_dreamrender&(!variable.trinket_1_buffs|trinket.1.cooldown.remains)&(!variable.trinket_2_buffs|trinket.2.cooldown.remains)" );

  variables->add_action( "variable,name=st_planning,value=active_enemies=1&(raid_event.adds.in>15|!raid_event.adds.exists)", "Variables" );
  variables->add_action( "variable,name=adds_remain,value=active_enemies>=2&(!raid_event.adds.exists|raid_event.adds.exists&raid_event.adds.remains>5)" );
  variables->add_action( "variable,name=sending_cds,value=(variable.st_planning|variable.adds_remain)" );
  variables->add_action( "variable,name=rime_buffs,value=buff.rime.react&(variable.static_rime_buffs|talent.avalanche&!talent.arctic_assault&debuff.razorice.stack<5)" );
  variables->add_action( "variable,name=rp_buffs,value=talent.unleashed_frenzy&(buff.unleashed_frenzy.remains<gcd.max*3|buff.unleashed_frenzy.stack<3)|talent.icy_talons&(buff.icy_talons.remains<gcd.max*3|buff.icy_talons.stack<(3+(2*talent.smothering_offense)+(2*talent.dark_talons)))" );
  variables->add_action( "variable,name=cooldown_check,value=talent.pillar_of_frost&buff.pillar_of_frost.up&(talent.obliteration&buff.pillar_of_frost.remains>10|!talent.obliteration)|!talent.pillar_of_frost&buff.empower_rune_weapon.up|!talent.pillar_of_frost&!talent.empower_rune_weapon|active_enemies>=2&buff.pillar_of_frost.up" );
  variables->add_action( "variable,name=oblit_pooling_time,op=setif,value=((cooldown.pillar_of_frost.remains_expected+1)%gcd.max)%((rune+3)*(runic_power+5))*100,value_else=3,condition=runic_power<35&rune<2&cooldown.pillar_of_frost.remains_expected<10", "Formulaic approach to determine the time before these abilities come off cooldown that the simulation should star to pool resources. Capped at 15s in the run_action_list call." );
  variables->add_action( "variable,name=breath_pooling_time,op=setif,value=((cooldown.breath_of_sindragosa.remains+1)%gcd.max)%((rune+1)*(runic_power+20))*100,value_else=2,condition=runic_power.deficit>10&cooldown.breath_of_sindragosa.remains<10" );
  variables->add_action( "variable,name=pooling_runes,value=rune<variable.oblit_rune_pooling&talent.obliteration&(!talent.breath_of_sindragosa|cooldown.breath_of_sindragosa.remains)&cooldown.pillar_of_frost.remains_expected<variable.oblit_pooling_time" );
  variables->add_action( "variable,name=pooling_runic_power,value=talent.breath_of_sindragosa&cooldown.breath_of_sindragosa.remains<variable.breath_pooling_time|talent.obliteration&runic_power<35&cooldown.pillar_of_frost.remains_expected<variable.oblit_pooling_time" );
  variables->add_action( "variable,name=ga_priority,value=(talent.shattered_frost&active_enemies>=2)|(!talent.shattered_frost&talent.shattering_blade&active_enemies>=4)|(!talent.shattered_frost&!talent.shattering_blade&active_enemies>=2)" );
  variables->add_action( "variable,name=breath_dying,value=runic_power<variable.breath_rp_cost*2&rune.time_to_2>runic_power%variable.breath_rp_cost" );
}
//frost_apl_end

//unholy_apl_start
void unholy( player_t* p )
{
  action_priority_list_t* default_ = p->get_action_priority_list( "default" );
  action_priority_list_t* precombat = p->get_action_priority_list( "precombat" );
  action_priority_list_t* aoe = p->get_action_priority_list( "aoe" );
  action_priority_list_t* aoe_burst = p->get_action_priority_list( "aoe_burst" );
  action_priority_list_t* cds = p->get_action_priority_list( "cds" );
  action_priority_list_t* cds_san = p->get_action_priority_list( "cds_san" );
  action_priority_list_t* cds_shared = p->get_action_priority_list( "cds_shared" );
  action_priority_list_t* cleave = p->get_action_priority_list( "cleave" );
  action_priority_list_t* racials = p->get_action_priority_list( "racials" );
  action_priority_list_t* san_fishing = p->get_action_priority_list( "san_fishing" );
  action_priority_list_t* san_st = p->get_action_priority_list( "san_st" );
  action_priority_list_t* san_trinkets = p->get_action_priority_list( "san_trinkets" );
  action_priority_list_t* st = p->get_action_priority_list( "st" );
  action_priority_list_t* trinkets = p->get_action_priority_list( "trinkets" );
  action_priority_list_t* variables = p->get_action_priority_list( "variables" );

  precombat->add_action( "flask" );
  precombat->add_action( "food" );
  precombat->add_action( "augmentation" );
  precombat->add_action( "snapshot_stats" );
  precombat->add_action( "raise_dead" );
  precombat->add_action( "army_of_the_dead,precombat_time=2" );
  precombat->add_action( "variable,name=trinket_1_buffs,value=trinket.1.has_use_buff|trinket.1.is.mirror_of_fractured_tomorrows" );
  precombat->add_action( "variable,name=trinket_2_buffs,value=trinket.2.has_use_buff|trinket.2.is.mirror_of_fractured_tomorrows" );
  precombat->add_action( "variable,name=trinket_1_duration,op=setif,value=20,value_else=trinket.1.proc.any_dps.duration,condition=trinket.1.is.mirror_of_fractured_tomorrows" );
  precombat->add_action( "variable,name=trinket_2_duration,op=setif,value=20,value_else=trinket.2.proc.any_dps.duration,condition=trinket.2.is.mirror_of_fractured_tomorrows" );
  precombat->add_action( "variable,name=trinket_1_sync,op=setif,value=1,value_else=0.5,condition=variable.trinket_1_buffs&(talent.apocalypse&trinket.1.cooldown.duration%%cooldown.apocalypse.duration=0|talent.dark_transformation&trinket.1.cooldown.duration%%cooldown.dark_transformation.duration=0)|trinket.1.is.treacherous_transmitter" );
  precombat->add_action( "variable,name=trinket_2_sync,op=setif,value=1,value_else=0.5,condition=variable.trinket_2_buffs&(talent.apocalypse&trinket.2.cooldown.duration%%cooldown.apocalypse.duration=0|talent.dark_transformation&trinket.2.cooldown.duration%%cooldown.dark_transformation.duration=0)|trinket.2.is.treacherous_transmitter" );
  precombat->add_action( "variable,name=trinket_priority,op=setif,value=2,value_else=1,condition=!variable.trinket_1_buffs&variable.trinket_2_buffs&(trinket.2.has_cooldown|!trinket.1.has_cooldown)|variable.trinket_2_buffs&((trinket.2.cooldown.duration%trinket.2.proc.any_dps.duration)*(1.5+trinket.2.has_buff.strength)*(variable.trinket_2_sync))>((trinket.1.cooldown.duration%trinket.1.proc.any_dps.duration)*(1.5+trinket.1.has_buff.strength)*(variable.trinket_1_sync)*(1+((trinket.1.ilvl-trinket.2.ilvl)%100)))" );
  precombat->add_action( "variable,name=damage_trinket_priority,op=setif,value=2,value_else=1,condition=!variable.trinket_1_buffs&!variable.trinket_2_buffs&trinket.2.ilvl>=trinket.1.ilvl" );

  default_->add_action( "auto_attack" );
  default_->add_action( "call_action_list,name=variables", "Call Action Lists" );
  default_->add_action( "call_action_list,name=san_trinkets,if=talent.vampiric_strike" );
  default_->add_action( "call_action_list,name=trinkets,if=!talent.vampiric_strike" );
  default_->add_action( "call_action_list,name=racials" );
  default_->add_action( "call_action_list,name=cds_shared" );
  default_->add_action( "call_action_list,name=cds,if=!talent.vampiric_strike" );
  default_->add_action( "call_action_list,name=cds_san,if=talent.vampiric_strike" );
  default_->add_action( "call_action_list,name=cleave,if=active_enemies<4&active_enemies>=2" );
  default_->add_action( "call_action_list,name=aoe_burst,if=active_enemies>=4&buff.death_and_decay.up" );
  default_->add_action( "call_action_list,name=aoe,if=active_enemies>=4&!buff.death_and_decay.up" );
  default_->add_action( "run_action_list,name=san_fishing,if=talent.gift_of_the_sanlayn&!buff.gift_of_the_sanlayn.up&buff.essence_of_the_blood_queen.remains<cooldown.dark_transformation.remains+2" );
  default_->add_action( "call_action_list,name=san_st,if=active_enemies=1&talent.vampiric_strike" );
  default_->add_action( "call_action_list,name=st,if=active_enemies=1&!talent.vampiric_strike" );

  aoe->add_action( "any_dnd,if=!buff.death_and_decay.up&(!talent.bursting_sores|death_knight.fwounded_targets=active_enemies|death_knight.fwounded_targets>=8|raid_event.adds.exists&raid_event.adds.remains<=11&raid_event.adds.remains>5)", "AOE" );
  aoe->add_action( "epidemic,if=!variable.pooling_runic_power" );
  aoe->add_action( "festering_strike,target_if=min:debuff.festering_wound.stack,if=cooldown.apocalypse.remains<gcd&debuff.festering_wound.stack=0|buff.festering_scythe.react" );
  aoe->add_action( "wound_spender,target_if=max:debuff.festering_wound.stack,if=debuff.festering_wound.stack>=1&cooldown.apocalypse.remains>gcd" );
  aoe->add_action( "festering_strike,target_if=min:debuff.festering_wound.stack,if=debuff.festering_wound.stack<4" );

  aoe_burst->add_action( "defile,if=!defile.ticking", "AoE Burst" );
  aoe_burst->add_action( "epidemic,if=!variable.pooling_runic_power&(active_enemies>=6&!talent.bursting_sores|talent.bursting_sores&death_knight.fwounded_targets!=active_enemies&death_knight.fwounded_targets<6|!talent.bursting_sores&runic_power.deficit<30|buff.sudden_doom.react)" );
  aoe_burst->add_action( "wound_spender,target_if=max:debuff.festering_wound.stack,if=debuff.festering_wound.stack>=1" );
  aoe_burst->add_action( "festering_strike,if=buff.festering_scythe.react" );
  aoe_burst->add_action( "epidemic,if=!variable.pooling_runic_power" );
  aoe_burst->add_action( "wound_spender" );

  cds->add_action( "dark_transformation,if=(variable.st_planning|variable.adds_remain)&(cooldown.apocalypse.remains<8|!talent.apocalypse|active_enemies>=1)", "Non-San'layn Cooldowns" );
  cds->add_action( "unholy_assault,if=(variable.st_planning|variable.adds_remain)&(cooldown.apocalypse.remains<gcd*2|!talent.apocalypse|active_enemies>=2&buff.dark_transformation.up)" );
  cds->add_action( "apocalypse,if=(variable.st_planning|variable.adds_remain)" );
  cds->add_action( "outbreak,target_if=target.time_to_die>dot.virulent_plague.remains,if=(dot.virulent_plague.refreshable|talent.superstrain&(dot.frost_fever.refreshable|dot.blood_plague.refreshable))&(!talent.unholy_blight|talent.unholy_blight&cooldown.dark_transformation.remains>15%((3*talent.superstrain)+(2*talent.ebon_fever)+(2*talent.plaguebringer)))&(!talent.raise_abomination|talent.raise_abomination&cooldown.raise_abomination.remains>15%((3*talent.superstrain)+(2*talent.ebon_fever)+(2*talent.plaguebringer)))" );
  cds->add_action( "abomination_limb,if=(variable.st_planning|variable.adds_remain)&(active_enemies>=2|!buff.sudden_doom.react&buff.festermight.up&debuff.festering_wound.stack<=2)" );

  cds_san->add_action( "dark_transformation,if=active_enemies>=1&(variable.st_planning|variable.adds_remain)&(talent.apocalypse&(pet.apoc_ghoul.active|active_enemies>=2)|!talent.apocalypse)", "San'layn Cooldowns" );
  cds_san->add_action( "unholy_assault,if=(variable.st_planning|variable.adds_remain)&(buff.dark_transformation.up&buff.dark_transformation.remains<12)" );
  cds_san->add_action( "apocalypse,if=(variable.st_planning|variable.adds_remain)&(debuff.festering_wound.stack>=3|active_enemies>=2)" );
  cds_san->add_action( "outbreak,target_if=target.time_to_die>dot.virulent_plague.remains,if=(pet.abomination.remains<15&dot.virulent_plague.refreshable|talent.morbidity&buff.infliction_of_sorrow.up&talent.superstrain&dot.frost_fever.refreshable&dot.blood_plague.refreshable)&(!talent.unholy_blight|talent.unholy_blight&cooldown.dark_transformation.remains>15%((3*talent.superstrain)+(2*talent.ebon_fever)+(2*talent.plaguebringer)))&(!talent.raise_abomination|talent.raise_abomination&cooldown.raise_abomination.remains>15%((3*talent.superstrain)+(2*talent.ebon_fever)+(2*talent.plaguebringer)))" );
  cds_san->add_action( "abomination_limb,if=active_enemies>=1&(variable.st_planning|variable.adds_remain)&(active_enemies>=2|!buff.dark_transformation.up&!buff.sudden_doom.react&buff.festermight.up&debuff.festering_wound.stack<=2)" );

  cds_shared->add_action( "potion,if=active_enemies>=1&(!talent.summon_gargoyle|cooldown.summon_gargoyle.remains>60)&(buff.dark_transformation.up&30>=buff.dark_transformation.remains|pet.army_ghoul.active&pet.army_ghoul.remains<=30|pet.apoc_ghoul.active&pet.apoc_ghoul.remains<=30|pet.abomination.active&pet.abomination.remains<=30)|fight_remains<=30", "Shared Cooldowns" );
  cds_shared->add_action( "invoke_external_buff,name=power_infusion,if=active_enemies>=1&(variable.st_planning|variable.adds_remain)&(pet.gargoyle.active&pet.gargoyle.remains<=22|!talent.summon_gargoyle&talent.army_of_the_dead&(talent.raise_abomination&pet.abomination.active&pet.abomination.remains<18|!talent.raise_abomination&pet.army_ghoul.active&pet.army_ghoul.remains<=18)|!talent.summon_gargoyle&!talent.army_of_the_dead&buff.dark_transformation.up|!talent.summon_gargoyle&buff.dark_transformation.up|!pet.gargoyle.active&cooldown.summon_gargoyle.remains+10>cooldown.invoke_external_buff_power_infusion.duration|active_enemies>=3&(buff.dark_transformation.up|death_and_decay.ticking))", "Use <a href='https://www.wowhead.com/spell=10060/power-infusion'>Power Infusion</a> while <a href='https://www.wowhead.com/spell=49206/summon-gargoyle'>Gargoyle</a> is up, as well as <a href='https://www.wowhead.com/spell=275699/apocalypse'>Apocalypse</a> or with <a href='https://www.wowhead.com/spell=63560/dark-transformation'>Dark Transformation</a> if <a href='https://www.wowhead.com/spell=275699/apocalypse'>Apocalypse</a> or <a href='https://www.wowhead.com/spell=49206/summon-gargoyle'>Gargoyle</a> are not talented" );
  cds_shared->add_action( "army_of_the_dead,if=(variable.st_planning|variable.adds_remain)&(talent.commander_of_the_dead&cooldown.dark_transformation.remains<5|!talent.commander_of_the_dead&active_enemies>=1)|fight_remains<35" );
  cds_shared->add_action( "raise_abomination,if=(variable.st_planning|variable.adds_remain)&(talent.commander_of_the_dead&cooldown.dark_transformation.remains<gcd*2|!talent.commander_of_the_dead&active_enemies>=1)|fight_remains<30" );
  cds_shared->add_action( "summon_gargoyle,use_off_gcd=1,if=(variable.st_planning|variable.adds_remain)&(buff.commander_of_the_dead.up|!talent.commander_of_the_dead&active_enemies>=1)" );
  cds_shared->add_action( "vile_contagion,target_if=max:debuff.festering_wound.stack,if=variable.adds_remain&(debuff.festering_wound.stack=6&(defile.ticking|death_and_decay.ticking|cooldown.any_dnd.remains<3)|raid_event.adds.exists&raid_event.adds.remains<=11&raid_event.adds.remains>5|buff.death_and_decay.up&debuff.festering_wound.stack>=4|cooldown.any_dnd.remains<3&debuff.festering_wound.stack>=4)" );

  cleave->add_action( "any_dnd,if=!buff.death_and_decay.up", "Cleave" );
  cleave->add_action( "death_coil,if=!variable.pooling_runic_power&talent.improved_death_coil" );
  cleave->add_action( "festering_strike,if=!variable.pop_wounds&debuff.festering_wound.stack<4|buff.festering_scythe.react" );
  cleave->add_action( "wound_spender,if=variable.pop_wounds" );
  cleave->add_action( "epidemic,if=!variable.pooling_runic_power" );

  racials->add_action( "arcane_torrent,if=runic_power<20&rune<2", "Racials" );
  racials->add_action( "blood_fury,if=(buff.blood_fury.duration+3>=pet.gargoyle.remains&pet.gargoyle.active)|(!talent.summon_gargoyle|cooldown.summon_gargoyle.remains>60)&(pet.army_ghoul.active&pet.army_ghoul.remains<=buff.blood_fury.duration+3|pet.apoc_ghoul.active&pet.apoc_ghoul.remains<=buff.blood_fury.duration+3|active_enemies>=2&death_and_decay.ticking)|fight_remains<=buff.blood_fury.duration+3" );
  racials->add_action( "berserking,if=(buff.berserking.duration+3>=pet.gargoyle.remains&pet.gargoyle.active)|(!talent.summon_gargoyle|cooldown.summon_gargoyle.remains>60)&(pet.army_ghoul.active&pet.army_ghoul.remains<=buff.berserking.duration+3|pet.apoc_ghoul.active&pet.apoc_ghoul.remains<=buff.berserking.duration+3|active_enemies>=2&death_and_decay.ticking)|fight_remains<=buff.berserking.duration+3" );
  racials->add_action( "lights_judgment,if=buff.unholy_strength.up&(!talent.festermight|buff.festermight.remains<target.time_to_die|buff.unholy_strength.remains<target.time_to_die)" );
  racials->add_action( "ancestral_call,if=(18>=pet.gargoyle.remains&pet.gargoyle.active)|(!talent.summon_gargoyle|cooldown.summon_gargoyle.remains>60)&(pet.army_ghoul.active&pet.army_ghoul.remains<=18|pet.apoc_ghoul.active&pet.apoc_ghoul.remains<=18|active_enemies>=2&death_and_decay.ticking)|fight_remains<=18" );
  racials->add_action( "arcane_pulse,if=active_enemies>=2|(rune.deficit>=5&runic_power.deficit>=60)" );
  racials->add_action( "fireblood,if=(buff.fireblood.duration+3>=pet.gargoyle.remains&pet.gargoyle.active)|(!talent.summon_gargoyle|cooldown.summon_gargoyle.remains>60)&(pet.army_ghoul.active&pet.army_ghoul.remains<=buff.fireblood.duration+3|pet.apoc_ghoul.active&pet.apoc_ghoul.remains<=buff.fireblood.duration+3|active_enemies>=2&death_and_decay.ticking)|fight_remains<=buff.fireblood.duration+3" );
  racials->add_action( "bag_of_tricks,if=active_enemies=1&(buff.unholy_strength.up|fight_remains<5)" );

  san_fishing->add_action( "antimagic_shell,if=death_knight.ams_absorb_percent>0&runic_power<40", "San'layn Fishing" );
  san_fishing->add_action( "any_dnd,if=!buff.death_and_decay.up&!buff.vampiric_strike.react" );
  san_fishing->add_action( "death_coil,if=buff.sudden_doom.react&talent.doomed_bidding" );
  san_fishing->add_action( "soul_reaper,if=target.health.pct<=35&fight_remains>5" );
  san_fishing->add_action( "death_coil,if=!buff.vampiric_strike.react" );
  san_fishing->add_action( "wound_spender,if=(debuff.festering_wound.stack>=3-pet.abomination.active&cooldown.apocalypse.remains>variable.apoc_timing)|buff.vampiric_strike.react" );
  san_fishing->add_action( "festering_strike,if=debuff.festering_wound.stack<3-pet.abomination.active" );

  san_st->add_action( "wound_spender,if=buff.essence_of_the_blood_queen.remains<3&buff.vampiric_strike.react|talent.gift_of_the_sanlayn&buff.dark_transformation.up&buff.dark_transformation.remains<gcd", "Single Target San'layn" );
  san_st->add_action( "death_coil,if=buff.sudden_doom.react&buff.gift_of_the_sanlayn.remains&buff.essence_of_the_blood_queen.stack>=3&(talent.doomed_bidding|talent.rotten_touch)|rune<2&!buff.runic_corruption.up" );
  san_st->add_action( "soul_reaper,if=target.health.pct<=35&!buff.gift_of_the_sanlayn.up&fight_remains>5" );
  san_st->add_action( "festering_strike,if=(debuff.festering_wound.stack<4&cooldown.apocalypse.remains<variable.apoc_timing)|(talent.gift_of_the_sanlayn&!buff.gift_of_the_sanlayn.up|!talent.gift_of_the_sanlayn)&(buff.festering_scythe.react|debuff.festering_wound.stack<=1-pet.abomination.active)" );
  san_st->add_action( "wound_spender,if=(debuff.festering_wound.stack>=3-pet.abomination.active&cooldown.apocalypse.remains>variable.apoc_timing)|buff.vampiric_strike.react&cooldown.apocalypse.remains>variable.apoc_timing" );
  san_st->add_action( "death_coil,if=!variable.pooling_runic_power&debuff.death_rot.remains<gcd|(buff.sudden_doom.react&debuff.festering_wound.stack>=1|rune<2)" );
  san_st->add_action( "wound_spender,if=debuff.festering_wound.stack>4" );
  san_st->add_action( "death_coil,if=!variable.pooling_runic_power" );

  san_trinkets->add_action( "use_item,name=fyralath_the_dreamrender,if=dot.mark_of_fyralath.ticking&(active_enemies<5|active_enemies>21|fight_remains<4)&(pet.abomination.active|pet.army_ghoul.active|!talent.raise_abomination&!talent.army_of_the_dead|time>15)", "Trinkets San'layn" );
  san_trinkets->add_action( "do_treacherous_transmitter_task,use_off_gcd=1,if=buff.errant_manaforge_emission.up&buff.dark_transformation.up|buff.cryptic_instructions.up&buff.dark_transformation.up|buff.realigning_nexus_convergence_divergence.up&buff.dark_transformation.up" );
  san_trinkets->add_action( "use_item,use_off_gcd=1,slot=trinket1,if=(variable.trinket_1_buffs|trinket.1.is.treacherous_transmitter)&(buff.dark_transformation.up&buff.dark_transformation.remains<variable.trinket_1_duration*0.73&(variable.trinket_priority=1|trinket.2.cooldown.remains|!trinket.2.has_cooldown))|variable.trinket_1_duration>=fight_remains" );
  san_trinkets->add_action( "use_item,use_off_gcd=1,slot=trinket2,if=(variable.trinket_2_buffs|trinket.2.is.treacherous_transmitter)&(buff.dark_transformation.up&buff.dark_transformation.remains<variable.trinket_2_duration*0.73&(variable.trinket_priority=2|trinket.1.cooldown.remains|!trinket.1.has_cooldown))|variable.trinket_2_duration>=fight_remains" );
  san_trinkets->add_action( "use_item,use_off_gcd=1,slot=trinket1,if=!variable.trinket_1_buffs&(variable.damage_trinket_priority=1|trinket.2.cooldown.remains|!trinket.2.has_cooldown|!talent.summon_gargoyle&!talent.army_of_the_dead&!talent.raise_abomination|!talent.summon_gargoyle&talent.army_of_the_dead&(!talent.raise_abomination&cooldown.army_of_the_dead.remains>20|talent.raise_abomination&cooldown.raise_abomination.remains>20)|!talent.summon_gargoyle&!talent.army_of_the_dead&!talent.raise_abomination&cooldown.dark_transformation.remains>20|talent.summon_gargoyle&cooldown.summon_gargoyle.remains>20&!pet.gargoyle.active)|fight_remains<15" );
  san_trinkets->add_action( "use_item,use_off_gcd=1,slot=trinket2,if=!variable.trinket_2_buffs&(variable.damage_trinket_priority=2|trinket.1.cooldown.remains|!trinket.1.has_cooldown|!talent.summon_gargoyle&!talent.army_of_the_dead&!talent.raise_abomination|!talent.summon_gargoyle&talent.army_of_the_dead&(!talent.raise_abomination&cooldown.army_of_the_dead.remains>20|talent.raise_abomination&cooldown.raise_abomination.remains>20)|!talent.summon_gargoyle&!talent.army_of_the_dead&!talent.raise_abomination&cooldown.dark_transformation.remains>20|talent.summon_gargoyle&cooldown.summon_gargoyle.remains>20&!pet.gargoyle.active)|fight_remains<15" );

  st->add_action( "soul_reaper,if=target.health.pct<=35&fight_remains>5", "Single Taget Non-San'layn" );
  st->add_action( "death_coil,if=!variable.pooling_runic_power&variable.spend_rp|fight_remains<10" );
  st->add_action( "festering_strike,if=!variable.pop_wounds&debuff.festering_wound.stack<4" );
  st->add_action( "wound_spender,if=variable.pop_wounds" );
  st->add_action( "death_coil,if=!variable.pooling_runic_power" );
  st->add_action( "wound_spender,if=!variable.pop_wounds&debuff.festering_wound.stack>=4" );

  trinkets->add_action( "use_item,name=fyralath_the_dreamrender,if=dot.mark_of_fyralath.ticking&(active_enemies<5|active_enemies>21|fight_remains<4)&(pet.abomination.active|pet.army_ghoul.active|!talent.raise_abomination&!talent.army_of_the_dead|time>15)", "Trinkets Non-San'layn" );
  trinkets->add_action( "do_treacherous_transmitter_task,use_off_gcd=1,if=buff.errant_manaforge_emission.up&buff.dark_transformation.up|buff.cryptic_instructions.up&buff.dark_transformation.up|buff.realigning_nexus_convergence_divergence.up&buff.dark_transformation.up" );
  trinkets->add_action( "use_item,use_off_gcd=1,slot=trinket1,if=(variable.trinket_1_buffs|trinket.1.is.treacherous_transmitter)&((!talent.summon_gargoyle&((!talent.army_of_the_dead|talent.army_of_the_dead&cooldown.army_of_the_dead.remains>trinket.1.cooldown.duration*0.51|death_knight.disable_aotd|talent.raise_abomination&cooldown.raise_abomination.remains>trinket.1.cooldown.duration*0.51)&((20>variable.trinket_1_duration&pet.apoc_ghoul.active&pet.apoc_ghoul.remains<=variable.trinket_1_duration*1.2|20<=variable.trinket_1_duration&cooldown.apocalypse.remains<gcd&buff.dark_transformation.up)|(!talent.apocalypse|active_enemies>=2)&buff.dark_transformation.up)|pet.army_ghoul.active&pet.army_ghoul.remains<variable.trinket_1_duration*1.2|pet.abomination.active&pet.abomination.remains<variable.trinket_1_duration*1.2)|talent.summon_gargoyle&pet.gargoyle.active&pet.gargoyle.remains<variable.trinket_1_duration*1.2|cooldown.summon_gargoyle.remains>80)&(variable.trinket_priority=1|trinket.2.cooldown.remains|!trinket.2.has_cooldown))|variable.trinket_1_duration>=fight_remains" );
  trinkets->add_action( "use_item,use_off_gcd=1,slot=trinket2,if=(variable.trinket_2_buffs|trinket.2.is.treacherous_transmitter)&((!talent.summon_gargoyle&((!talent.army_of_the_dead|talent.army_of_the_dead&cooldown.army_of_the_dead.remains>trinket.2.cooldown.duration*0.51|death_knight.disable_aotd|talent.raise_abomination&cooldown.raise_abomination.remains>trinket.2.cooldown.duration*0.51)&((20>variable.trinket_2_duration&pet.apoc_ghoul.active&pet.apoc_ghoul.remains<=variable.trinket_2_duration*1.2|20<=variable.trinket_2_duration&cooldown.apocalypse.remains<gcd&buff.dark_transformation.up)|(!talent.apocalypse|active_enemies>=2)&buff.dark_transformation.up)|pet.army_ghoul.active&pet.army_ghoul.remains<variable.trinket_2_duration*1.2|pet.abomination.active&pet.abomination.remains<variable.trinket_2_duration*1.2)|talent.summon_gargoyle&pet.gargoyle.active&pet.gargoyle.remains<variable.trinket_2_duration*1.2|cooldown.summon_gargoyle.remains>80)&(variable.trinket_priority=2|trinket.1.cooldown.remains|!trinket.1.has_cooldown))|variable.trinket_2_duration>=fight_remains" );
  trinkets->add_action( "use_item,use_off_gcd=1,slot=trinket1,if=!variable.trinket_1_buffs&(variable.damage_trinket_priority=1|trinket.2.cooldown.remains|!trinket.2.has_cooldown|!talent.summon_gargoyle&!talent.army_of_the_dead&!talent.raise_abomination|!talent.summon_gargoyle&talent.army_of_the_dead&(!talent.raise_abomination&cooldown.army_of_the_dead.remains>20|talent.raise_abomination&cooldown.raise_abomination.remains>20)|!talent.summon_gargoyle&!talent.army_of_the_dead&!talent.raise_abomination&cooldown.dark_transformation.remains>20|talent.summon_gargoyle&cooldown.summon_gargoyle.remains>20&!pet.gargoyle.active)|fight_remains<15" );
  trinkets->add_action( "use_item,use_off_gcd=1,slot=trinket2,if=!variable.trinket_2_buffs&(variable.damage_trinket_priority=2|trinket.1.cooldown.remains|!trinket.1.has_cooldown|!talent.summon_gargoyle&!talent.army_of_the_dead&!talent.raise_abomination|!talent.summon_gargoyle&talent.army_of_the_dead&(!talent.raise_abomination&cooldown.army_of_the_dead.remains>20|talent.raise_abomination&cooldown.raise_abomination.remains>20)|!talent.summon_gargoyle&!talent.army_of_the_dead&!talent.raise_abomination&cooldown.dark_transformation.remains>20|talent.summon_gargoyle&cooldown.summon_gargoyle.remains>20&!pet.gargoyle.active)|fight_remains<15" );

  variables->add_action( "variable,name=st_planning,op=setif,value=1,value_else=0,condition=active_enemies=1&(!raid_event.adds.exists|raid_event.adds.in>15)", "Variables" );
  variables->add_action( "variable,name=adds_remain,op=setif,value=1,value_else=0,condition=active_enemies>=2&(!raid_event.adds.exists|raid_event.adds.exists&raid_event.adds.remains>6)" );
  variables->add_action( "variable,name=apoc_timing,op=setif,value=7,value_else=3,condition=cooldown.apocalypse.remains<10&debuff.festering_wound.stack<=4&cooldown.unholy_assault.remains>10" );
  variables->add_action( "variable,name=pop_wounds,op=setif,value=1,value_else=0,condition=(cooldown.apocalypse.remains>variable.apoc_timing|!talent.apocalypse)&(debuff.festering_wound.stack>=1&cooldown.unholy_assault.remains<20&talent.unholy_assault&variable.st_planning|debuff.rotten_touch.up&debuff.festering_wound.stack>=1|debuff.festering_wound.stack>=4-pet.abomination.active)|fight_remains<5&debuff.festering_wound.stack>=1" );
  variables->add_action( "variable,name=pooling_runic_power,op=setif,value=1,value_else=0,condition=talent.vile_contagion&cooldown.vile_contagion.remains<3&runic_power<60&!variable.st_planning" );
  variables->add_action( "variable,name=spend_rp,op=setif,value=1,value_else=0,condition=(!talent.rotten_touch|talent.rotten_touch&!debuff.rotten_touch.up|runic_power.deficit<20)&((talent.improved_death_coil&(active_enemies=2|talent.coil_of_devastation)|rune<3|pet.gargoyle.active|buff.sudden_doom.react|!variable.pop_wounds&debuff.festering_wound.stack>=4))" );
}
//unholy_apl_end

}  // namespace death_knight_apl
