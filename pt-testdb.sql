BEGIN TRANSACTION;

CREATE TABLE JoinTypes ("id" INTEGER NOT NULL, "name" TEXT NOT NULL, UNIQUE ("id"));
INSERT INTO "JoinTypes" VALUES(1,'None');
INSERT INTO "JoinTypes" VALUES(2,'Admin');
INSERT INTO "JoinTypes" VALUES(3,'Leader');
INSERT INTO "JoinTypes" VALUES(4,'Invite');
INSERT INTO "JoinTypes" VALUES(5,'User');
INSERT INTO "JoinTypes" VALUES(6,'Auto');


CREATE TABLE ChannelTypes ("id" INTEGER NOT NULL, "create_id" INTEGER NOT NULL REFERENCES "JoinTypes" ("id"), "admin_id" INTEGER NOT NULL REFERENCES "JoinTypes" ("id"), "join_id" INTEGER NOT NULL REFERENCES "JoinTypes" ("id"), "invite_id" INTEGER NOT NULL REFERENCES "JoinTypes" ("id"), "visibilityChannel" BOOLEAN NOT NULL, "visibilityMembers" BOOLEAN NOT NULL, UNIQUE ("id"));


CREATE TABLE DefaultChannels ("name" TEXT NOT NULL, "permanent" BOOLEAN NOT NULL, UNIQUE ("name"));
INSERT INTO "DefaultChannels" VALUES('#general',1);


CREATE TABLE Channels ("name" TEXT NOT NULL, UNIQUE ("name"));


CREATE TABLE EntityChannels ("entity_id" INTEGER NOT NULL REFERENCES "Entities" ("id"), "channel_id" INTEGER NOT NULL REFERENCES "Channels" ("id"), UNIQUE ("entity_id"));


CREATE TABLE Users ("login" TEXT NOT NULL, "passwordHash" TEXT NOT NULL, UNIQUE ("login"));

CREATE TABLE Permissions ("users_login" TEXT NOT NULL REFERENCES "Users" ("login"), "type" TEXT NOT NULL, "level" INTEGER NOT NULL, UNIQUE ("users_login", "type"));

CREATE TABLE EntityTypes ("id" INTEGER NOT NULL, "name" TEXT NOT NULL, UNIQUE ("id"));
INSERT INTO "EntityTypes" VALUES(1,'PCEntityType');
INSERT INTO "EntityTypes" VALUES(2,'NPCEntityType');
INSERT INTO "EntityTypes" VALUES(3,'DoorEntityType');
INSERT INTO "EntityTypes" VALUES(4,'ItemEntityType');
INSERT INTO "EntityTypes" VALUES(5,'MountEntityType');


CREATE TABLE Entities ("id" INTEGER NOT NULL, "EntityTypes_id" INTEGER NOT NULL REFERENCES "EntityTypes" ("id"), UNIQUE ("id"));


CREATE TABLE EntityPositions ("entity_id" INTEGER NOT NULL REFERENCES "Entities" ("id"), "position" TEXT NOT NULL, "rotation" TEXT NOT NULL, UNIQUE ("entity_id"));


CREATE TABLE Characters ("entity_id" INTEGER NOT NULL, "name" TEXT NOT NULL, "meshes_id" INTEGER NOT NULL REFERENCES "Meshes" ("id"), "hairColor" TEXT NOT NULL, "skinColor" TEXT NOT NULL, "decalColor" TEXT NOT NULL, "species_id" INTEGER NOT NULL REFERENCES "Species" ("id"), "age" FLOAT NOT NULL, UNIQUE ("entity_id"));

CREATE TABLE PcEntities ("entity_id" INTEGER NOT NULL REFERENCES "Entities" ("id"), "users_login" TEXT NOT NULL REFERENCES "Users" ("login"), UNIQUE ("entity_id"));


CREATE TABLE NpcEntities ("entity_id" INTEGER NOT NULL REFERENCES "Entities" ("id"), "ainame" TEXT NOT NULL, UNIQUE ("entity_id"));


CREATE TABLE Items ("entity_id" INTEGER NOT NULL REFERENCES "Entities" ("id"), "itemTemplates_id" INTEGER NOT NULL REFERENCES "ItemTemplates" ("id"), UNIQUE ("entity_id"));


CREATE TABLE Doors ("entity_id" INTEGER NOT NULL REFERENCES "Entities" ("id"), "name" TEXT NOT NULL, "meshes_id" INTEGER NOT NULL REFERENCES "Meshes" ("id"), "isLocked" BOOLEAN NOT NULL, "isOpen" BOOLEAN NOT NULL, "animationName" TEXT NOT NULL, UNIQUE ("entity_id"));


CREATE TABLE EquipTypes ("id" INTEGER NOT NULL, "name" TEXT NOT NULL, "slotName" TEXT NOT NULL, UNIQUE ("id"));
INSERT INTO "EquipTypes" VALUES(1,'None','non-equipable');
INSERT INTO "EquipTypes" VALUES(2,'Right Hand','righthand');


CREATE TABLE ItemTemplateAttributes ("ItemTemplates_id" INTEGER NOT NULL REFERENCES "ItemTemplates" ("id"), "AttributeTypes_id" INTEGER NOT NULL REFERENCES "AttributeTypes" ("id"), "value" INTEGER NOT NULL, UNIQUE ("ItemTemplates_id", "AttributeTypes_id"));


CREATE TABLE AttributeTypes ("id" INTEGER NOT NULL, "name" TEXT NOT NULL, UNIQUE ("id"));
INSERT INTO "AttributeTypes" VALUES(1,'Quality');
INSERT INTO "AttributeTypes" VALUES(2,'Durability');
INSERT INTO "AttributeTypes" VALUES(3,'Weight');
INSERT INTO "AttributeTypes" VALUES(4,'Reach');
INSERT INTO "AttributeTypes" VALUES(5,'Damage');
INSERT INTO "AttributeTypes" VALUES(6,'Heft');
INSERT INTO "AttributeTypes" VALUES(7,'Pull');
INSERT INTO "AttributeTypes" VALUES(8,'Range');
INSERT INTO "AttributeTypes" VALUES(9,'Mobility');
INSERT INTO "AttributeTypes" VALUES(10,'Hardness');
INSERT INTO "AttributeTypes" VALUES(11,'Bulk');
INSERT INTO "AttributeTypes" VALUES(12,'Toughness');


CREATE TABLE Attributes ("entity_id" INTEGER NOT NULL REFERENCES "Entities" ("id"), "AttributeTypes_id" INTEGER NOT NULL REFERENCES "AttributeTypes" ("id"), "value" INTEGER NOT NULL, UNIQUE ("entity_id", "AttributeTypes_id"));


CREATE TABLE Inventory ("entity_id" INTEGER NOT NULL REFERENCES "Entities" ("id"), "slot" INTEGER NOT NULL, "item_id" INTEGER NOT NULL REFERENCES "Entities" ("id"), UNIQUE ("entity_id", "slot"));


CREATE TABLE Equipment ("entity_id" INTEGER NOT NULL REFERENCES "Entities" ("id"), "equipType_id" INTEGER NOT NULL REFERENCES "EquipTypes" ("id"), "item_id" INTEGER NOT NULL REFERENCES "Entities" ("id"), UNIQUE ("entity_id", "equipType_id"));


CREATE TABLE ReputationTypes ("id" INTEGER NOT NULL, "name" TEXT NOT NULL, UNIQUE ("id"));
INSERT INTO "ReputationTypes" VALUES(1,'Por''taem');
INSERT INTO "ReputationTypes" VALUES(2,'Far''taem');


CREATE TABLE Reputations ("entity_id" INTEGER NOT NULL REFERENCES "Entities" ("id"), "ReputationTypes_id" INTEGER NOT NULL REFERENCES "ReputationTypes" ("id"), "level" INTEGER NOT NULL, UNIQUE ("entity_id", "ReputationTypes_id"));


CREATE TABLE SkillTypes ("id" INTEGER NOT NULL, "type" TEXT NOT NULL, "name" TEXT NOT NULL, UNIQUE ("id"));
INSERT INTO "SkillTypes" VALUES(0,'N','None');
INSERT INTO "SkillTypes" VALUES(1,'O','One Handed Axe');
INSERT INTO "SkillTypes" VALUES(2,'O','One Handed Blunt');
INSERT INTO "SkillTypes" VALUES(3,'O','One Handed Flail');
INSERT INTO "SkillTypes" VALUES(4,'O','One Handed Sword');
INSERT INTO "SkillTypes" VALUES(5,'O','One Handed Unarmed');
INSERT INTO "SkillTypes" VALUES(6,'T','Two Handed Axe');
INSERT INTO "SkillTypes" VALUES(7,'T','Two Handed Blunt');
INSERT INTO "SkillTypes" VALUES(8,'T','Two Handed Flail');
INSERT INTO "SkillTypes" VALUES(9,'T','Two Handed Sword');
INSERT INTO "SkillTypes" VALUES(10,'T','Two Handed Unarmed');
INSERT INTO "SkillTypes" VALUES(11,'R','Bow');
INSERT INTO "SkillTypes" VALUES(12,'R','Crossbow');
INSERT INTO "SkillTypes" VALUES(13,'D','Armor Proficiency');
INSERT INTO "SkillTypes" VALUES(14,'D','Block');
INSERT INTO "SkillTypes" VALUES(15,'D','Dodge');
INSERT INTO "SkillTypes" VALUES(16,'D','Parry');
INSERT INTO "SkillTypes" VALUES(17,'RO','Sneak');
INSERT INTO "SkillTypes" VALUES(18,'RO','Pick Lock');
INSERT INTO "SkillTypes" VALUES(19,'RO','Pick Pocket');
INSERT INTO "SkillTypes" VALUES(20,'RO','Perception');
INSERT INTO "SkillTypes" VALUES(21,'P','Farmer');
INSERT INTO "SkillTypes" VALUES(22,'P','Fisher');
INSERT INTO "SkillTypes" VALUES(23,'P','Herbalist');
INSERT INTO "SkillTypes" VALUES(24,'P','Miner');
INSERT INTO "SkillTypes" VALUES(25,'P','Skinner');
INSERT INTO "SkillTypes" VALUES(26,'C','Apothecary');
INSERT INTO "SkillTypes" VALUES(27,'C','Blacksmith');
INSERT INTO "SkillTypes" VALUES(28,'C','Carpenter');
INSERT INTO "SkillTypes" VALUES(29,'C','Cook');
INSERT INTO "SkillTypes" VALUES(30,'C','Mason');
INSERT INTO "SkillTypes" VALUES(31,'C','Tailor');
INSERT INTO "SkillTypes" VALUES(32,'S','Bard');
INSERT INTO "SkillTypes" VALUES(33,'S','Merchant');
INSERT INTO "SkillTypes" VALUES(34,'S','Sage');
INSERT INTO "SkillTypes" VALUES(35,'S','Teacher');
INSERT INTO "SkillTypes" VALUES(36,'OT','Healer');
INSERT INTO "SkillTypes" VALUES(37,'OT','Trainer');


CREATE TABLE Skills ("entity_id" INTEGER NOT NULL REFERENCES "Entities" ("id"), "SkillTypes_id" INTEGER NOT NULL REFERENCES "SkillTypes" ("id"), "xp" FLOAT NOT NULL, UNIQUE ("entity_id", "SkillTypes_id"));


CREATE TABLE AbilityTypes ("id" INTEGER NOT NULL, "name" TEXT NOT NULL, UNIQUE ("id"));
INSERT INTO "AbilityTypes" VALUES(1,'Agility');
INSERT INTO "AbilityTypes" VALUES(2,'Endurance');
INSERT INTO "AbilityTypes" VALUES(3,'Speed');
INSERT INTO "AbilityTypes" VALUES(4,'Strength');
INSERT INTO "AbilityTypes" VALUES(5,'Resolve');
INSERT INTO "AbilityTypes" VALUES(6,'Sapience');


CREATE TABLE Abilities ("entity_id" INTEGER NOT NULL REFERENCES "Entities" ("id"), "AbilityTypes_id" INTEGER NOT NULL REFERENCES "AbilityTypes" ("id"), "xp" FLOAT NOT NULL, UNIQUE ("entity_id", "AbilityTypes_id"));
CREATE TABLE HobbyTypes ("id" INTEGER NOT NULL, "name" TEXT NOT NULL, UNIQUE ("id"));
INSERT INTO "HobbyTypes" VALUES(1,'Fishing');
INSERT INTO "HobbyTypes" VALUES(2,'Spinning');
INSERT INTO "HobbyTypes" VALUES(3,'Calligraphy');
INSERT INTO "HobbyTypes" VALUES(4,'Brewing');
INSERT INTO "HobbyTypes" VALUES(5,'Costuming');


CREATE TABLE Hobbies ("entity_id" INTEGER NOT NULL REFERENCES "Entities" ("id"), "HobbyTypes_id" INTEGER NOT NULL REFERENCES "HobbyTypes" ("id"), "order" INTEGER NOT NULL, "xp" FLOAT NOT NULL, UNIQUE ("entity_id", "HobbyTypes_id"));


CREATE TABLE ResourceTypes ("id" INTEGER NOT NULL, "name" TEXT NOT NULL, "abilityType_id" INTEGER NOT NULL REFERENCES "AbilityTypes" ("id"), "multiplier" INTEGER NOT NULL, UNIQUE ("id"));
INSERT INTO "ResourceTypes" VALUES(1,'Hit Points',2,1);
INSERT INTO "ResourceTypes" VALUES(2,'Stamina',2,10);
INSERT INTO "ResourceTypes" VALUES(3,'Willpower',5,10);


CREATE TABLE Resources ("entity_id" INTEGER NOT NULL REFERENCES "Entities" ("id"), "resourceType_id" INTEGER NOT NULL REFERENCES "ResourcesTypes" ("id"), "value" FLOAT NOT NULL, UNIQUE ("entity_id", "resourceType_id"));


CREATE TABLE VulnerabilityTypes ("id" INTEGER NOT NULL, "name" TEXT NOT NULL, UNIQUE ("id"));
INSERT INTO "VulnerabilityTypes" VALUES(1,'Slash');
INSERT INTO "VulnerabilityTypes" VALUES(2,'Pierce');
INSERT INTO "VulnerabilityTypes" VALUES(3,'Blunt');
INSERT INTO "VulnerabilityTypes" VALUES(4,'Fire');


CREATE TABLE Vulnerabilities ("entity_id" INTEGER NOT NULL REFERENCES "Entities" ("id"), "VulnerabilityTypes_id" INTEGER NOT NULL REFERENCES "AbilityTypes" ("id"), "value" INTEGER NOT NULL, UNIQUE ("entity_id", "VulnerabilityTypes_id"));


CREATE TABLE NpcAiSetting ("entity_id" INTEGER NOT NULL REFERENCES "Entities" ("id"), "name" TEXT NOT NULL, "value" TEXT NOT NULL, UNIQUE ("entity_id", "name"));

CREATE TABLE NpcDialogs ("entity_id" INTEGER NOT NULL REFERENCES "Entities" ("id"), "id" INTEGER NOT NULL, "text" TEXT NOT NULL, "action" TEXT NOT NULL, UNIQUE ("entity_id", "id"));

CREATE TABLE NpcDialogAnswers ("entity_id" INTEGER NOT NULL REFERENCES "Entities" ("id"), "dialog_id" INTEGER NOT NULL REFERENCES "NpcDialogs" ("id"), "id" INTEGER NOT NULL, "text" TEXT NOT NULL, "isEnd" BOOLEAN NOT NULL, "nextDialog_id" INTEGER NOT NULL REFERENCES "NpcDialogs" ("id"), UNIQUE ("entity_id", "dialog_id", "id"));


CREATE TABLE SpawnPoints ("id" INTEGER NOT NULL, "ItemTemplate_id" INTEGER NOT NULL REFERENCES "ItemTemplates" ("id"), "position" TEXT NOT NULL, "interval" INTEGER NOT NULL, UNIQUE ("id"));
CREATE TABLE Books ("entity_id" INTEGER NOT NULL REFERENCES "Entities" ("id"), "name" TEXT NOT NULL, "text" TEXT NOT NULL, UNIQUE ("entity_id"));
CREATE TABLE Meshes ("id" INTEGER NOT NULL, "revision" INTEGER NOT NULL, "factoryName" TEXT NOT NULL, "fileName" TEXT NOT NULL, UNIQUE ("id"));


CREATE TABLE ItemTemplates ("id" INTEGER NOT NULL, "name" TEXT NOT NULL, "meshes_id" INTEGER NOT NULL REFERENCES "Meshes" ("id"), "iconFile" TEXT NOT NULL, "description" TEXT NOT NULL, "equipType_id" INTEGER NOT NULL REFERENCES "EquipTypes" ("id"), "SkillTypes_id" INTEGER NOT NULL REFERENCES "SkillTypes" ("id"), UNIQUE ("id"));

CREATE TABLE Config ("name" TEXT NOT NULL, "value" TEXT NOT NULL, UNIQUE ("name"));
INSERT INTO "Config" VALUES('port','12345');


CREATE TABLE Zones ("id" INTEGER NOT NULL, "type" TEXT NOT NULL, UNIQUE ("id"));


CREATE TABLE ZoneNodes ("zone_id" INTEGER NOT NULL REFERENCES "Zones" ("id"), "coordinate" TEXT NOT NULL, UNIQUE ("zone_id", "coordinate"));


CREATE TABLE Species ("id" INTEGER NOT NULL, "name" TEXT NOT NULL, "meshes_id" INTEGER NOT NULL REFERENCES "Meshes" ("id"), "maxAge" FLOAT NOT NULL, UNIQUE ("id"));
INSERT INTO "Species" VALUES(1,'Human',101,60.0);
INSERT INTO "Species" VALUES(2,'Horse',201,60.0);

CREATE TABLE SpeciesAbilities ("species_id" INTEGER NOT NULL REFERENCES "Species" ("id"), "AbilityTypes_id" INTEGER NOT NULL REFERENCES "AbilityTypes" ("id"), "minXP" FLOAT NOT NULL, "maxXP" FLOAT NOT NULL, UNIQUE ("species_id", "AbilityTypes_id"));


CREATE TABLE SpeciesSkills ("species_id" INTEGER NOT NULL REFERENCES "Species" ("id"), "SkillTypes_id" INTEGER NOT NULL REFERENCES "SkillTypes" ("id"), "minXP" FLOAT NOT NULL, "maxXP" FLOAT NOT NULL, UNIQUE ("species_id", "SkillTypes_id"));


CREATE TABLE SpeciesReputations ("species_id" INTEGER NOT NULL REFERENCES "Species" ("id"), "ReputationTypes_id" INTEGER NOT NULL REFERENCES "ReputationTypes" ("id"), "minLevel" INTEGER NOT NULL, "maxLevel" INTEGER NOT NULL, UNIQUE ("species_id", "ReputationTypes_id"));


CREATE TABLE SpeciesInventory ("species_id" INTEGER NOT NULL REFERENCES "Species" ("id"), "slot" INTEGER NOT NULL, "itemTemplates_id" INTEGER NOT NULL REFERENCES "ItemTemplates" ("id"), "chance" INTEGER NOT NULL, UNIQUE ("species_id", "slot"));


CREATE TABLE SpeciesEquipment ("species_id" INTEGER NOT NULL REFERENCES "Species" ("id"), "equipType_id" INTEGER NOT NULL REFERENCES "EquipTypes" ("id"), "itemTemplates_id" INTEGER NOT NULL REFERENCES "ItemTemplates" ("id"), "chance" FLOAT NOT NULL, UNIQUE ("species_id", "equipType_id"));


CREATE TABLE SpeciesZones ("species_id" INTEGER NOT NULL REFERENCES "Species" ("id"), "zone_id" INTEGER NOT NULL REFERENCES "Zones" ("id"), "maxPopulation" INTEGER NOT NULL, UNIQUE ("species_id", "zone_id"));


CREATE TABLE SpeciesVulnerabilities ("species_id" INTEGER NOT NULL REFERENCES "Species" ("id"), "VulnerabilityTypes_id" INTEGER NOT NULL REFERENCES "AbilityTypes" ("id"), "minValue" INTEGER NOT NULL, "maxValue" INTEGER NOT NULL, UNIQUE ("species_id", "VulnerabilityTypes_id"));

CREATE TABLE Locations ("id" INTEGER NOT NULL, "name" TEXT NOT NULL, "location" TEXT NOT NULL, UNIQUE ("id"));
INSERT INTO "Locations" VALUES(1,'default','(900.765,8.26531,12.1211)');
INSERT INTO "Locations" VALUES(2,'relocate','(900.765,8.26531,12.1211)');


-------------------------------------------------------------------------------------------------------------------------------------------------------
-- Game Start Settings
-------------------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------------------
-- Locations of interest 
-----------------------------------------------------------------------------------------------------------------------------------------------------
INSERT INTO "Locations" VALUES(3,'smithy','(906.737,8.78586,41.4721)');
INSERT INTO "Locations" VALUES(4,'site1','(2351.67,44.3489,655.91)');

-----------------------------------------------------------------------------------------------------------------------------------------------------
-- Charater Meshes
----------------------------------------------------------------------------------------------------------------------------------------------------- 
INSERT INTO "Meshes" VALUES(101,1,'male','/peragro/art/3d_art/characters/male01/male01');
--INSERT INTO "Meshes" VALUES(102,1,'MaleBase','/peragro/art/3d_art/characters/MaleBase/library');
--INSERT INTO "Meshes" VALUES(103,1,'pesant','/peragro/art/3d_art/characters/pesant/library');
--INSERT INTO "Meshes" VALUES(13,1,'MaleBase','/peragro/art/3d_art/characters/Pesant/library');

-- Mount Meshes
INSERT INTO "Meshes" VALUES(201,1,'horse','/peragro/art/3d_art/animals/horse/horse.xml');
--INSERT INTO "Meshes" VALUES(12,1,'horse','/peragro/art/3d_art/animals/horse/library');

-----------------------------------------------------------------------------------------------------------------------------------------------------
-- Item Meshes and Templates
-----------------------------------------------------------------------------------------------------------------------------------------------------
-- Apple
INSERT INTO "Meshes" VALUES(1001,1,'apple','/peragro/art/3d_art/props/others/apple01/apple.xml');
INSERT INTO "ItemTemplates" VALUES(1001, 'Apple', 1001, 'set:Inventory image:apple', 'An tasty looking apple.', 1, 0);

-- Book
INSERT INTO "Meshes" VALUES(1002,1,'book','/peragro/art/3d_art/props/books/book01/book.xml');
INSERT INTO "ItemTemplates" VALUES(1002, 'Book', 1002, 'set:Inventory image:oldbook', 'An old book.', 1, 0 );

-- Daedalian Claymore
INSERT INTO "Meshes" VALUES(1003,1,'genbastardsword01','/peragro/art/3d_art/props/weapons/swords/bastardsword01/library');
INSERT INTO "ItemTemplates" VALUES(1003, 'Daedalian Claymore', 1003, 'set:Inventory image:fancyclaymore', 'A masterful sword for those born out of wedlock.', 1, 1);

-- Flaming Dragon Edge Sword
--INSERT INTO "Meshes" VALUES(4,1,'swordfact','/peragro/art/3d_art/props/weapons/swords/sword/sword.lib');
--INSERT INTO "ItemTemplates" VALUES(4, 'Flaming Dragon Edge Sword', 4, 'set:Inventory image:DragonEdgeSword', '	Passed on from generation to generation of Tibet Monks who mastered the movement of the Mighty Dragon and could swing this sword soo fast it would actually caught fire, inflicting extra damage on the foe.', 1, 1);


-- Mighty Helmet of the Holy Monkey
--INSERT INTO "Meshes" VALUES(5,1,'helmet','/peragro/art/armor/helmets/bogus.xml');
--INSERT INTO "ItemTemplates" VALUES(5, 'Mighty Helmet of the Holy Monkey', '5', 'set:Helmet image:Helmet', 'The Sweet Mother of the Holy Monkey used this helmet as a drinking bucket.', 1, 0);

-- Key
--INSERT INTO "Meshes" VALUES(6,1,'Stuff001_tinyballpot_84_pot','/peragro/art/3d_art/props/others/stuff001/tinyballpot_84_pot.xml');
--INSERT INTO "ItemTemplates" VALUES(6, 'Key', 6, 'set:Inventory image:Key01', 'A small gold key.', 1, 0);

-- Prima Buckler
INSERT INTO "Meshes" VALUES(1007,1,'buckler1','/peragro/art/3d_art/props/shields/primabuckler/buckler1.xml');
INSERT INTO "ItemTemplates" VALUES(1007, 'Prima Buckler', 1007, 'set:Inventory image:primabuckler', 'A small buckler style shield.', 1, 0)

-- Scythe
INSERT INTO "Meshes" VALUES(1008,1,'genscythe001','/peragro/art/3d_art/props/others/scythes/scythe001/library.xml');
INSERT INTO "ItemTemplates" VALUES(1008, 'Scythe', 1008, '/peragro/art/3d_art/props/others/scythes/scythe001/icon_scythe001.png', 'A peaceful tool for farming or a deadly weapon in sociopaths hands.', 1, 1)

-- Small Plate
INSERT INTO "Meshes" VALUES(1009,1,'Stuff001_smallplate_64_plates','/peragro/art/3d_art/props/others/stuff001/tinyballpot_84_pot.xml');
INSERT INTO "ItemTemplates" VALUES(1009, 'Small Plate', 1009, 'set:Inventory image:smallplate', 'A small plate.', 1, 0)

-- Tiny Ballpot
INSERT INTO "Meshes" VALUES(1010,1,'Stuff001_tinyballpot_84_pot','/peragro/art/3d_art/props/others/stuff001/tinyballpot_84_pot.xml');
INSERT INTO "ItemTemplates" VALUES(10, 'Tiny Ballpot', 1010, 'set:Inventory image:tinyballpot', 'A Tiny Ballpot.', 1, 0)

-- Tunic
INSERT INTO "Meshes" VALUES(1011,1,'tunic','/peragro/art/3d_art/props/clothes/tunic/library');
INSERT INTO "ItemTemplates" VALUES(1011, 'Simple Tunic', 1011, 'set:Inventory image:tinyballpot', 'A simple tunic.', 1, 0)

-----------------------------------------------------------------------------------------------------------------------------------------------------
-- My account stuff
-----------------------------------------------------------------------------------------------------------------------------------------------------
INSERT INTO "Users" VALUES('admin','admin');
INSERT INTO "Permissions" VALUES('admin','Admin',2);

-- My character stuff
INSERT INTO "Characters" VALUES(1,'recon',101,'(0,0,0)','(0,0,0)','(0,0,0)',1,0.0);
--INSERT INTO "Characters" VALUES(1,'recon',103,'(0,0,0)','(0,0,0)','(0,0,0)',1,0.0);
INSERT INTO "Abilities" VALUES(1,2,10.0);
INSERT INTO "Abilities" VALUES(1,3,10.0);
INSERT INTO "Abilities" VALUES(1,5,10.0);
INSERT INTO "Resources" VALUES(1,1,1.0);
INSERT INTO "Resources" VALUES(1,2,10.0);
INSERT INTO "Resources" VALUES(1,3,10.0);

INSERT INTO "PcEntities" VALUES(1,'mec');
INSERT INTO "EntityPositions" VALUES(1,'(900.765,8.29213,12.1211)','(0,3.51598,0)');

-----------------------------------------------------------------------------------------------------------------------------------------------------
-- Add 'Ilmarine' blacksmith NPC 
-----------------------------------------------------------------------------------------------------------------------------------------------------
INSERT INTO "Characters" VALUES(2,'Ilmarine',101,'(0,0,0)','(0,0,0)','(0,0,0)',1,0.0);
INSERT INTO "Abilities" VALUES(2,2,10.0);
INSERT INTO "Abilities" VALUES(2,3,10.0);
INSERT INTO "Abilities" VALUES(2,5,10.0);
INSERT INTO "Resources" VALUES(2,1,1.0);
INSERT INTO "Resources" VALUES(2,2,10.0);
INSERT INTO "Resources" VALUES(2,3,10.0);

INSERT INTO "Entities" VALUES(2,2);
INSERT INTO "EntityPositions" VALUES(2,'(906.737,8.78586,41.4721)','(0,0.861332,0)');
INSERT INTO "NpcEntities" VALUES(2,'idle');


INSERT INTO "NpcDialogs" VALUES(2,1,"Hello.","text");
  INSERT INTO "NpcDialogAnswers" VALUES(2,1,1,"Who are you?",0,2); --'
    INSERT INTO "NpcDialogs" VALUES(2,2, "Hi, my name is Ilmarine, I am the blacksmith of Por'Taem.","text"); --'
--      INSERT INTO "NpcDialogAnswers" VALUES(2,2,1,"How do you do this fine day?",0,3);
--      INSERT INTO "NpcDialogAnswers" VALUES(2,2,2,"Show me your goods.",0,4);  
--      INSERT INTO "NpcDialogAnswers" VALUES(2,2,3,"Sell Inventory.",0,5); 

  INSERT INTO "NpcDialogAnswers" VALUES(2,1,2,"How do you do this fine day?",0,3); 
    INSERT INTO "NpcDialogs" VALUES(2,3,"I'm am doing very good, thank you for asking.","text"); --'
      INSERT INTO "NpcDialogAnswers" VALUES(2,3,1,"Who are you?",0,2); --'
      INSERT INTO "NpcDialogAnswers" VALUES(2,3,2,"Show me your goods.",0,4);  
      INSERT INTO "NpcDialogAnswers" VALUES(2,3,3,"Sell Inventory.",0,5); 

  INSERT INTO "NpcDialogAnswers" VALUES(2,1,3,"Show me your goods.",0,4); 
    INSERT INTO "NpcDialogs" VALUES(2,4,"I can offer a fine pickaxe for one gold coin.","buy"); 

  INSERT INTO "NpcDialogAnswers" VALUES(2,1,4,"Sell Inventory.",0,5); 
    INSERT INTO "NpcDialogs" VALUES(2,5,"Show me your goods and i'll make an offer.","sell"); --'

-----------------------------------------------------------------------------------------------------------------------------------------------------
-- A mount called 'silver'
-----------------------------------------------------------------------------------------------------------------------------------------------------
INSERT INTO "Characters" VALUES(3,'Silver',201,'(0,0,0)','(0,0,0)','(0,0,0)',2,0.0);
INSERT INTO "Entities" VALUES(3,5);
INSERT INTO "EntityPositions" VALUES(3,'(898.258,6.21756,60.9568)','(0,2.72429,0)');



COMMIT;
