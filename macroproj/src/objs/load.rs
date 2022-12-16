use crate::objs::base::*;
use std::collections::HashMap;

pub fn load_all() -> HashMap<String, Object> {
    let mut ret = HashMap::<String, Object>::new();
    vec!["detail_crystal", "detail_crystal", "detail_crystal", "detail_crystal", "detail_crystalLarge", "detail_crystalLarge", "detail_crystalLarge", "detail_crystalLarge", "detail_dirt", "detail_dirt", "detail_dirt", "detail_dirt", "detail_dirtLarge", "detail_dirtLarge", "detail_dirtLarge", "detail_dirtLarge", "detail_rocks", "detail_rocks", "detail_rocks", "detail_rocks", "detail_rocksLarge", "detail_rocksLarge", "detail_rocksLarge", "detail_rocksLarge", "detail_tree", "detail_tree", "detail_tree", "detail_tree", "detail_treeLarge", "detail_treeLarge", "detail_treeLarge", "detail_treeLarge", "enemy_ufoGreen", "enemy_ufoGreen", "enemy_ufoGreen", "enemy_ufoGreen", "enemy_ufoGreenWeapon", "enemy_ufoGreenWeapon", "enemy_ufoGreenWeapon", "enemy_ufoGreenWeapon", "enemy_ufoPurple", "enemy_ufoPurple", "enemy_ufoPurple", "enemy_ufoPurple", "enemy_ufoPurpleWeapon", "enemy_ufoPurpleWeapon", "enemy_ufoPurpleWeapon", "enemy_ufoPurpleWeapon", "enemy_ufoRed", "enemy_ufoRed", "enemy_ufoRed", "enemy_ufoRed", "enemy_ufoRedWeapon", "enemy_ufoRedWeapon", "enemy_ufoRedWeapon", "enemy_ufoRedWeapon", "enemy_ufoYellow", "enemy_ufoYellow", "enemy_ufoYellow", "enemy_ufoYellow", "enemy_ufoYellowWeapon", "enemy_ufoYellowWeapon", "enemy_ufoYellowWeapon", "enemy_ufoYellowWeapon", "snow_detail_crystal", "snow_detail_crystal", "snow_detail_crystal", "snow_detail_crystal", "snow_detail_crystalLarge", "snow_detail_crystalLarge", "snow_detail_crystalLarge", "snow_detail_crystalLarge", "snow_detail_dirt", "snow_detail_dirt", "snow_detail_dirt", "snow_detail_dirt", "snow_detail_dirtLarge", "snow_detail_dirtLarge", "snow_detail_dirtLarge", "snow_detail_dirtLarge", "snow_detail_rocks", "snow_detail_rocks", "snow_detail_rocks", "snow_detail_rocks", "snow_detail_rocksLarge", "snow_detail_rocksLarge", "snow_detail_rocksLarge", "snow_detail_rocksLarge", "snow_detail_tree", "snow_detail_tree", "snow_detail_tree", "snow_detail_tree", "snow_detail_treeLarge", "snow_detail_treeLarge", "snow_detail_treeLarge", "snow_detail_treeLarge", "snow_tile_bump", "snow_tile_bump", "snow_tile_bump", "snow_tile_bump", "snow_tile_cornerInner", "snow_tile_cornerInner", "snow_tile_cornerInner", "snow_tile_cornerInner", "snow_tile_cornerLarge", "snow_tile_cornerLarge", "snow_tile_cornerLarge", "snow_tile_cornerLarge", "snow_tile_cornerOuter", "snow_tile_cornerOuter", "snow_tile_cornerOuter", "snow_tile_cornerOuter", "snow_tile_cornerRound", "snow_tile_cornerRound", "snow_tile_cornerRound", "snow_tile_cornerRound", "snow_tile_cornerSquare", "snow_tile_cornerSquare", "snow_tile_cornerSquare", "snow_tile_cornerSquare", "snow_tile_crossing", "snow_tile_crossing", "snow_tile_crossing", "snow_tile_crossing", "snow_tile_crystal", "snow_tile_crystal", "snow_tile_crystal", "snow_tile_crystal", "snow_tile", "snow_tile_end", "snow_tile_end", "snow_tile_end", "snow_tile_end", "snow_tile_endRound", "snow_tile_endRound", "snow_tile_endRound", "snow_tile_endRound", "snow_tile_endRoundSpawn", "snow_tile_endRoundSpawn", "snow_tile_endRoundSpawn", "snow_tile_endRoundSpawn", "snow_tile_hill", "snow_tile_hill", "snow_tile_hill", "snow_tile_hill", "snow_tile", "snow_tile_riverBridge", "snow_tile_riverBridge", "snow_tile_riverBridge", "snow_tile_riverBridge", "snow_tile_riverCorner", "snow_tile_riverCorner", "snow_tile_riverCorner", "snow_tile_riverCorner", "snow_tile_riverFall", "snow_tile_riverFall", "snow_tile_riverFall", "snow_tile_riverFall", "snow_tile_riverSlope", "snow_tile_riverSlope", "snow_tile_riverSlope", "snow_tile_riverSlope", "snow_tile_riverSlopeLarge", "snow_tile_riverSlopeLarge", "snow_tile_riverSlopeLarge", "snow_tile_riverSlopeLarge", "snow_tile_riverStraight", "snow_tile_riverStraight", "snow_tile_riverStraight", "snow_tile_riverStraight", "snow_tile_riverTransition", "snow_tile_riverTransition", "snow_tile_riverTransition", "snow_tile_riverTransition", "snow_tile_rock", "snow_tile_rock", "snow_tile_rock", "snow_tile_rock", "snow_tile", "snow_tile_slope", "snow_tile_slope", "snow_tile_slope", "snow_tile_slope", "snow_tile_spawn", "snow_tile_spawn", "snow_tile_spawn", "snow_tile_spawn", "snow_tile_spawnRound", "snow_tile_spawnRound", "snow_tile_spawnRound", "snow_tile_spawnRound", "snow_tile_split", "snow_tile_split", "snow_tile_split", "snow_tile_split", "snow_tile_straight", "snow_tile_straight", "snow_tile_straight", "snow_tile_straight", "snow_tile_straightHill", "snow_tile_straightHill", "snow_tile_straightHill", "snow_tile_straightHill", "snow_tile_straightHillLarge", "snow_tile_straightHillLarge", "snow_tile_straightHillLarge", "snow_tile_straightHillLarge", "snow_tile_transition", "snow_tile_transition", "snow_tile_transition", "snow_tile_transition", "snow_tile_tree", "snow_tile_tree", "snow_tile_tree", "snow_tile_tree", "snow_tile_treeDouble", "snow_tile_treeDouble", "snow_tile_treeDouble", "snow_tile_treeDouble", "snow_tile_treeQuad", "snow_tile_treeQuad", "snow_tile_treeQuad", "snow_tile_treeQuad", "snow_tile", "snow_tile_wideCorner", "snow_tile_wideCorner", "snow_tile_wideCorner", "snow_tile_wideCorner", "snow_tile_wideSplit", "snow_tile_wideSplit", "snow_tile_wideSplit", "snow_tile_wideSplit", "snow_tile_wideStraight", "snow_tile_wideStraight", "snow_tile_wideStraight", "snow_tile_wideStraight", "snow_tile_wideTransition", "snow_tile_wideTransition", "snow_tile_wideTransition", "snow_tile_wideTransition", "snow_woodStructure", "snow_woodStructure_high", "snow_woodStructure_high", "snow_woodStructure_high", "snow_woodStructure_high", "snow_woodStructure", "snow_woodStructure", "snow_woodStructure", "tile_bump", "tile_bump", "tile_bump", "tile_bump", "tile_cornerInner", "tile_cornerInner", "tile_cornerInner", "tile_cornerInner", "tile_cornerLarge", "tile_cornerLarge", "tile_cornerLarge", "tile_cornerLarge", "tile_cornerOuter", "tile_cornerOuter", "tile_cornerOuter", "tile_cornerOuter", "tile_cornerRound", "tile_cornerRound", "tile_cornerRound", "tile_cornerRound", "tile_cornerSquare", "tile_cornerSquare", "tile_cornerSquare", "tile_cornerSquare", "tile_crossing", "tile_crossing", "tile_crossing", "tile_crossing", "tile_crystal", "tile_crystal", "tile_crystal", "tile_crystal", "tile_dirt", "tile_dirt", "tile_dirt", "tile_dirt", "tile_dirtHigh", "tile_dirtHigh", "tile_dirtHigh", "tile_dirtHigh", "tile", "tile_end", "tile_end", "tile_end", "tile_end", "tile_endRound", "tile_endRound", "tile_endRound", "tile_endRound", "tile_endRoundSpawn", "tile_endRoundSpawn", "tile_endRoundSpawn", "tile_endRoundSpawn", "tile_endSpawn", "tile_endSpawn", "tile_endSpawn", "tile_endSpawn", "tile_hill", "tile_hill", "tile_hill", "tile_hill", "tile", "tile_riverBridge", "tile_riverBridge", "tile_riverBridge", "tile_riverBridge", "tile_riverCorner", "tile_riverCorner", "tile_riverCorner", "tile_riverCorner", "tile_riverFall", "tile_riverFall", "tile_riverFall", "tile_riverFall", "tile_riverSlope", "tile_riverSlope", "tile_riverSlope", "tile_riverSlope", "tile_riverSlopeLarge", "tile_riverSlopeLarge", "tile_riverSlopeLarge", "tile_riverSlopeLarge", "tile_riverStraight", "tile_riverStraight", "tile_riverStraight", "tile_riverStraight", "tile_riverTransition", "tile_riverTransition", "tile_riverTransition", "tile_riverTransition", "tile_rock", "tile_rock", "tile_rock", "tile_rock", "tile", "tile_slope", "tile_slope", "tile_slope", "tile_slope", "tile_spawn", "tile_spawn", "tile_spawn", "tile_spawn", "tile_spawnRound", "tile_spawnRound", "tile_spawnRound", "tile_spawnRound", "tile_split", "tile_split", "tile_split", "tile_split", "tile_straight", "tile_straight", "tile_straight", "tile_straight", "tile_straightHill", "tile_straightHill", "tile_straightHill", "tile_straightHill", "tile_straightHillLarge", "tile_straightHillLarge", "tile_straightHillLarge", "tile_straightHillLarge", "tile_transition", "tile_transition", "tile_transition", "tile_transition", "tile_tree", "tile_tree", "tile_tree", "tile_tree", "tile_treeDouble", "tile_treeDouble", "tile_treeDouble", "tile_treeDouble", "tile_treeQuad", "tile_treeQuad", "tile_treeQuad", "tile_treeQuad", "tile", "tile_wideCorner", "tile_wideCorner", "tile_wideCorner", "tile_wideCorner", "tile_wideSplit", "tile_wideSplit", "tile_wideSplit", "tile_wideSplit", "tile_wideStraight", "tile_wideStraight", "tile_wideStraight", "tile_wideStraight", "tile_wideTransition", "tile_wideTransition", "tile_wideTransition", "tile_wideTransition", "towerRound_base", "towerRound_base", "towerRound_base", "towerRound_base", "towerRound_bottomA", "towerRound_bottomA", "towerRound_bottomA", "towerRound_bottomA", "towerRound_bottomB", "towerRound_bottomB", "towerRound_bottomB", "towerRound_bottomB", "towerRound_bottomC", "towerRound_bottomC", "towerRound_bottomC", "towerRound_bottomC", "towerRound_crystals", "towerRound_crystals", "towerRound_crystals", "towerRound_crystals", "towerRound_middleA", "towerRound_middleA", "towerRound_middleA", "towerRound_middleA", "towerRound_middleB", "towerRound_middleB", "towerRound_middleB", "towerRound_middleB", "towerRound_middleC", "towerRound_middleC", "towerRound_middleC", "towerRound_middleC", "towerRound_roofA", "towerRound_roofA", "towerRound_roofA", "towerRound_roofA", "towerRound_roofB", "towerRound_roofB", "towerRound_roofB", "towerRound_roofB", "towerRound_roofC", "towerRound_roofC", "towerRound_roofC", "towerRound_roofC", "towerRound_sampleA", "towerRound_sampleA", "towerRound_sampleA", "towerRound_sampleA", "towerRound_sampleB", "towerRound_sampleB", "towerRound_sampleB", "towerRound_sampleB", "towerRound_sampleC", "towerRound_sampleC", "towerRound_sampleC", "towerRound_sampleC", "towerRound_sampleD", "towerRound_sampleD", "towerRound_sampleD", "towerRound_sampleD", "towerRound_sampleE", "towerRound_sampleE", "towerRound_sampleE", "towerRound_sampleE", "towerRound_sampleF", "towerRound_sampleF", "towerRound_sampleF", "towerRound_sampleF", "towerRound_topA", "towerRound_topA", "towerRound_topA", "towerRound_topA", "towerRound_topB", "towerRound_topB", "towerRound_topB", "towerRound_topB", "towerRound_topC", "towerRound_topC", "towerRound_topC", "towerRound_topC", "towerSquare_bottomA", "towerSquare_bottomA", "towerSquare_bottomA", "towerSquare_bottomA", "towerSquare_bottomB", "towerSquare_bottomB", "towerSquare_bottomB", "towerSquare_bottomB", "towerSquare_bottomC", "towerSquare_bottomC", "towerSquare_bottomC", "towerSquare_bottomC", "towerSquare_middleA", "towerSquare_middleA", "towerSquare_middleA", "towerSquare_middleA", "towerSquare_middleB", "towerSquare_middleB", "towerSquare_middleB", "towerSquare_middleB", "towerSquare_middleC", "towerSquare_middleC", "towerSquare_middleC", "towerSquare_middleC", "towerSquare_roofA", "towerSquare_roofA", "towerSquare_roofA", "towerSquare_roofA", "towerSquare_roofB", "towerSquare_roofB", "towerSquare_roofB", "towerSquare_roofB", "towerSquare_roofC", "towerSquare_roofC", "towerSquare_roofC", "towerSquare_roofC", "towerSquare_sampleA", "towerSquare_sampleA", "towerSquare_sampleA", "towerSquare_sampleA", "towerSquare_sampleB", "towerSquare_sampleB", "towerSquare_sampleB", "towerSquare_sampleB", "towerSquare_sampleC", "towerSquare_sampleC", "towerSquare_sampleC", "towerSquare_sampleC", "towerSquare_sampleD", "towerSquare_sampleD", "towerSquare_sampleD", "towerSquare_sampleD", "towerSquare_sampleE", "towerSquare_sampleE", "towerSquare_sampleE", "towerSquare_sampleE", "towerSquare_sampleF", "towerSquare_sampleF", "towerSquare_sampleF", "towerSquare_sampleF", "towerSquare_topA", "towerSquare_topA", "towerSquare_topA", "towerSquare_topA", "towerSquare_topB", "towerSquare_topB", "towerSquare_topB", "towerSquare_topB", "towerSquare_topC", "towerSquare_topC", "towerSquare_topC", "towerSquare_topC", "weapon_ballista", "weapon_ballista", "weapon_ballista", "weapon_ballista", "weapon_blaster", "weapon_blaster", "weapon_blaster", "weapon_blaster", "weapon_cannon", "weapon_cannon", "weapon_cannon", "weapon_cannon", "weapon_catapult", "weapon_catapult", "weapon_catapult", "weapon_catapult", "woodStructure", "woodStructure_high", "woodStructure_high", "woodStructure_high", "woodStructure_high", "woodStructure", "woodStructure", "woodStructure"].iter().for_each(|s| { ret.insert((*s).to_string(), Object::new(s)); });
    ret
}