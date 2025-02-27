action_priority_list_t* precombat = get_action_priority_list( "precombat" );
action_priority_list_t* def = get_action_priority_list( "default" );
action_priority_list_t* cat = get_action_priority_list( "cat" );
action_priority_list_t* healing = get_action_priority_list( "healing" );

precombat->add_action( "heart_of_the_wild","Snapshot raid buffed stats before combat begins and pre-potting is done." );
precombat->add_action( "cat_form,if=talent.rake.enabled" );
precombat->add_action( "prowl,if=talent.rake.enabled" );

def->add_action( "berserking","Executed every time the actor is available." );
def->add_action( "natures_vigil,if=!buff.prowl.up&!buff.shadowmeld.up" );
def->add_action( "run_action_list,name=healing,if=!buff.prowl.up&!buff.shadowmeld.up&druid.time_spend_healing,line_cd=20" );
def->add_action( "heart_of_the_wild,if=!buff.prowl.up&!buff.shadowmeld.up" );
def->add_action( "use_items,if=!buff.prowl.up&!buff.shadowmeld.up" );
def->add_action( "potion,if=!buff.prowl.up&!buff.shadowmeld.up" );
def->add_action( "run_action_list,name=cat,if=talent.rake.enabled" );
def->add_action( "cat_form,if=talent.rake.enabled" );
def->add_action( "convoke_the_spirits,if=(buff.heart_of_the_wild.up|cooldown.heart_of_the_wild.remains>60-30*talent.cenarius_guidance.enabled|!talent.heart_of_the_wild.enabled)" );
def->add_action( "sunfire,target_if=refreshable&target.time_to_die>5&talent.improved_sunfire.enabled" );
def->add_action( "moonfire,target_if=refreshable&time_to_die>12" );
def->add_action( "starsurge,if=active_enemies<8" );
def->add_action( "sunfire,target_if=refreshable&target.time_to_die>7&active_enemies<7" );
def->add_action( "starfire,if=spell_targets.starfire>1|buff.heart_of_the_wild.up" );
def->add_action( "wrath" );

cat->add_action( "rake,if=buff.shadowmeld.up|buff.prowl.up|buff.sudden_ambush.up" );
cat->add_action( "auto_attack,if=!buff.prowl.up&!buff.shadowmeld.up" );
cat->add_action( "heart_of_the_wild,if=(cooldown.convoke_the_spirits.remains<40|!talent.convoke_the_spirits.enabled)|fight_remains<46" );
cat->add_action( "rip,target_if=((refreshable|energy>90&remains<=10)&(combo_points=5&time_to_die>remains+24|(remains+combo_points*4<time_to_die&remains+4+combo_points*4>time_to_die))|!ticking&combo_points>2+spell_targets.swipe_cat*2)" );
cat->add_action( "pool_resource,for_next=1" );
cat->add_action( "thrash_cat,target_if=refreshable&target.time_to_die>7&spell_targets.thrash_cat>2" );
cat->add_action( "sunfire,target_if=(refreshable&target.time_to_die>5)&!prev_gcd.1.cat_form&(active_enemies=1|talent.improved_sunfire.enabled)" );
cat->add_action( "rake,target_if=refreshable&time_to_die>10&spell_targets.swipe_cat<10" );
cat->add_action( "cat_form,if=!buff.cat_form.up&energy>50&(dot.rake.refreshable&spell_targets.thrash_cat>3&spell_targets.thrash_cat<7&talent.thrash.enabled)&(cooldown.healing.remains>(gcd.max*2)|!druid.time_spend_healing)" );
cat->add_action( "moonfire,target_if=(refreshable&time_to_die>12&!ticking|(prev_gcd.1.sunfire&remains<duration*0.8&spell_targets.sunfire=1))&!prev_gcd.1.cat_form&spell_targets.swipe_cat<6" );
cat->add_action( "sunfire,if=prev_gcd.1.moonfire&remains<duration*0.8" );
cat->add_action( "starsurge,if=active_enemies=1|(active_enemies<8&!buff.cat_form.up)" );
cat->add_action( "cat_form,if=!buff.cat_form.up&energy>50" );
cat->add_action( "pool_resource,for_next=1" );
cat->add_action( "ferocious_bite,target_if=(combo_points>3&target.time_to_die<3)|(combo_points=5&energy>=50&dot.rip.remains>10)&spell_targets.swipe_cat<4" );
cat->add_action( "thrash_cat,target_if=refreshable&target.time_to_die>6&(spell_targets.thrash_cat>1|talent.liveliness.enabled)" );
cat->add_action( "swipe_cat,if=active_enemies>3&combo_points<5&talent.improved_swipe.enabled" );
cat->add_action( "sunfire,target_if=refreshable&target.time_to_die>5&active_enemies<7&!talent.improved_sunfire.enabled" );
cat->add_action( "pool_resource,for_next=1" );
cat->add_action( "shred,if=energy>60&combo_points<5" );

healing->add_action( "strict_sequence,name=heal:regrowth:regrowth:regrowth:regrowth" );
