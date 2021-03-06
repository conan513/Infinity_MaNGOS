-- --------------------------------------------------------
-- Host:                         127.0.0.1
-- Server version:               5.0.45-community-nt - MySQL Community Edition (GPL)
-- Server OS:                    Win32
-- HeidiSQL Version:             8.3.0.4694
-- --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

-- Dumping structure for table mangos.spell_loot_template
CREATE TABLE IF NOT EXISTS `spell_loot_template` (
  `entry` mediumint(8) unsigned NOT NULL default '0',
  `item` mediumint(8) unsigned NOT NULL default '0',
  `ChanceOrQuestChance` float NOT NULL default '100',
  `groupid` tinyint(3) unsigned NOT NULL default '0',
  `mincountOrRef` mediumint(9) NOT NULL default '1',
  `maxcount` tinyint(3) unsigned NOT NULL default '1',
  `condition_id` mediumint(8) unsigned NOT NULL default '0',
  PRIMARY KEY  (`entry`,`item`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED COMMENT='Loot System';

-- Dumping data for table mangos.spell_loot_template: 322 rows
DELETE FROM `spell_loot_template`;
/*!40000 ALTER TABLE `spell_loot_template` DISABLE KEYS */;
INSERT INTO `spell_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `groupid`, `mincountOrRef`, `maxcount`, `condition_id`) VALUES
	(64051, 45854, 100, 0, 1, 1, 0),
	(59502, 19227, 0, 1, 1, 1, 0),
	(59502, 19230, 0, 1, 1, 1, 0),
	(59502, 19231, 0, 1, 1, 1, 0),
	(59502, 19232, 0, 1, 1, 1, 0),
	(59502, 19233, 0, 1, 1, 1, 0),
	(59502, 19234, 0, 1, 1, 1, 0),
	(59502, 19235, 0, 1, 1, 1, 0),
	(59502, 19236, 0, 1, 1, 1, 0),
	(59502, 19268, 0, 1, 1, 1, 0),
	(59502, 19269, 0, 1, 1, 1, 0),
	(59502, 19270, 0, 1, 1, 1, 0),
	(59502, 19271, 0, 1, 1, 1, 0),
	(59502, 19272, 0, 1, 1, 1, 0),
	(59502, 19273, 0, 1, 1, 1, 0),
	(59502, 19274, 0, 1, 1, 1, 0),
	(59502, 19275, 0, 1, 1, 1, 0),
	(59502, 19276, 0, 1, 1, 1, 0),
	(59502, 19278, 0, 1, 1, 1, 0),
	(59502, 19279, 0, 1, 1, 1, 0),
	(59502, 19280, 0, 1, 1, 1, 0),
	(59502, 19281, 0, 1, 1, 1, 0),
	(59502, 19282, 0, 1, 1, 1, 0),
	(59502, 19283, 0, 1, 1, 1, 0),
	(59502, 19284, 0, 1, 1, 1, 0),
	(59502, 19258, 0, 1, 1, 1, 0),
	(59502, 19259, 0, 1, 1, 1, 0),
	(59502, 19260, 0, 1, 1, 1, 0),
	(59502, 19261, 0, 1, 1, 1, 0),
	(59502, 19262, 0, 1, 1, 1, 0),
	(59502, 19263, 0, 1, 1, 1, 0),
	(59502, 19264, 0, 1, 1, 1, 0),
	(59502, 19265, 0, 1, 1, 1, 0),
	(59503, 31882, 0, 1, 1, 1, 0),
	(59503, 31889, 0, 1, 1, 1, 0),
	(59503, 31888, 0, 1, 1, 1, 0),
	(59503, 31885, 0, 1, 1, 1, 0),
	(59503, 31884, 0, 1, 1, 1, 0),
	(59503, 31887, 0, 1, 1, 1, 0),
	(59503, 31886, 0, 1, 1, 1, 0),
	(59503, 31883, 0, 1, 1, 1, 0),
	(59503, 31901, 0, 1, 1, 1, 0),
	(59503, 31909, 0, 1, 1, 1, 0),
	(59503, 31908, 0, 1, 1, 1, 0),
	(59503, 31904, 0, 1, 1, 1, 0),
	(59503, 31903, 0, 1, 1, 1, 0),
	(59503, 31906, 0, 1, 1, 1, 0),
	(59503, 31905, 0, 1, 1, 1, 0),
	(59503, 31902, 0, 1, 1, 1, 0),
	(59503, 31910, 0, 1, 1, 1, 0),
	(59503, 31918, 0, 1, 1, 1, 0),
	(59503, 31917, 0, 1, 1, 1, 0),
	(59503, 31913, 0, 1, 1, 1, 0),
	(59503, 31912, 0, 1, 1, 1, 0),
	(59503, 31916, 0, 1, 1, 1, 0),
	(59503, 31915, 0, 1, 1, 1, 0),
	(59503, 31911, 0, 1, 1, 1, 0),
	(59503, 31892, 0, 1, 1, 1, 0),
	(59503, 31900, 0, 1, 1, 1, 0),
	(59503, 31899, 0, 1, 1, 1, 0),
	(59503, 31895, 0, 1, 1, 1, 0),
	(59503, 31894, 0, 1, 1, 1, 0),
	(59503, 31898, 0, 1, 1, 1, 0),
	(59503, 31896, 0, 1, 1, 1, 0),
	(59503, 31893, 0, 1, 1, 1, 0),
	(59504, 44277, 0, 1, 1, 1, 0),
	(59504, 44278, 0, 1, 1, 1, 0),
	(59504, 44279, 0, 1, 1, 1, 0),
	(59504, 44280, 0, 1, 1, 1, 0),
	(59504, 44281, 0, 1, 1, 1, 0),
	(59504, 44282, 0, 1, 1, 1, 0),
	(59504, 44284, 0, 1, 1, 1, 0),
	(59504, 44285, 0, 1, 1, 1, 0),
	(59504, 44268, 0, 1, 1, 1, 0),
	(59504, 44269, 0, 1, 1, 1, 0),
	(59504, 44270, 0, 1, 1, 1, 0),
	(59504, 44271, 0, 1, 1, 1, 0),
	(59504, 44272, 0, 1, 1, 1, 0),
	(59504, 44273, 0, 1, 1, 1, 0),
	(59504, 44274, 0, 1, 1, 1, 0),
	(59504, 44275, 0, 1, 1, 1, 0),
	(59504, 44260, 0, 1, 1, 1, 0),
	(59504, 44261, 0, 1, 1, 1, 0),
	(59504, 44262, 0, 1, 1, 1, 0),
	(59504, 44263, 0, 1, 1, 1, 0),
	(59504, 44264, 0, 1, 1, 1, 0),
	(59504, 44265, 0, 1, 1, 1, 0),
	(59504, 44266, 0, 1, 1, 1, 0),
	(59504, 44267, 0, 1, 1, 1, 0),
	(59504, 44286, 0, 1, 1, 1, 0),
	(59504, 44287, 0, 1, 1, 1, 0),
	(59504, 44288, 0, 1, 1, 1, 0),
	(59504, 44289, 0, 1, 1, 1, 0),
	(59504, 44290, 0, 1, 1, 1, 0),
	(59504, 44291, 0, 1, 1, 1, 0),
	(59504, 44292, 0, 1, 1, 1, 0),
	(59504, 44293, 0, 1, 1, 1, 0),
	(59491, 44163, 100, 0, 1, 1, 0),
	(59487, 44161, 100, 0, 1, 1, 0),
	(59480, 44142, 100, 0, 1, 1, 0),
	(48247, 37168, 100, 0, 1, 1, 0),
	(57844, 36782, 100, 0, 1, 1, 0),
	(60445, 43722, 100, 0, -43722, 1, 0),
	(61177, 43533, 0, 1, 1, 1, 0),
	(61177, 43537, 0, 1, 1, 1, 0),
	(61177, 43547, 0, 1, 1, 1, 0),
	(61177, 43550, 0, 1, 1, 1, 0),
	(61177, 43534, 0, 1, 1, 1, 0),
	(61177, 43545, 0, 1, 1, 1, 0),
	(61177, 43542, 0, 1, 1, 1, 0),
	(61177, 43538, 0, 1, 1, 1, 0),
	(60893, 40211, 0, 1, 1, 3, 0),
	(60893, 40083, 0, 1, 1, 1, 0),
	(60893, 44331, 0, 1, 1, 3, 0),
	(60893, 44327, 0, 1, 1, 3, 0),
	(60893, 40212, 0, 1, 1, 3, 0),
	(60893, 40072, 0, 1, 1, 1, 0),
	(60893, 44330, 0, 1, 1, 3, 0),
	(60893, 44325, 0, 1, 1, 3, 0),
	(60893, 40097, 0, 1, 1, 3, 0),
	(60893, 40076, 0, 1, 1, 1, 0),
	(60893, 40109, 0, 1, 1, 3, 0),
	(60893, 40068, 0, 1, 1, 1, 0),
	(60893, 40087, 0, 1, 1, 3, 0),
	(60893, 22854, 0, 1, 1, 1, 0),
	(61288, 43535, 0, 1, 1, 1, 0),
	(61288, 43671, 0, 1, 1, 1, 0),
	(61288, 43539, 0, 1, 1, 1, 0),
	(61288, 43544, 0, 1, 1, 1, 0),
	(61288, 43672, 0, 1, 1, 1, 0),
	(61288, 43673, 0, 1, 1, 1, 0),
	(61288, 44432, 0, 1, 1, 1, 0),
	(60445, 43723, 100, 0, -43723, 1, 0),
	(64202, 36782, 100, 0, 1, 5, 0),
	(64202, 36783, 50, 0, 1, 1, 0),
	(64202, 36784, 5, 0, 1, 1, 0),
	(60893, 44508, 0, 1, 1, 1, 0),
	(61177, 43429, 0, 1, 1, 1, 0),
	(61288, 43400, 0, 1, 1, 1, 0),
	(61288, 43399, 0, 1, 1, 1, 0),
	(61288, 43397, 0, 1, 1, 1, 0),
	(61288, 43395, 0, 1, 1, 1, 0),
	(61288, 43398, 0, 1, 1, 1, 0),
	(61288, 43396, 0, 1, 1, 1, 0),
	(61288, 44922, 0, 1, 1, 1, 0),
	(61288, 43335, 0, 1, 1, 1, 0),
	(61288, 43332, 0, 1, 1, 1, 0),
	(61288, 43674, 0, 1, 1, 1, 0),
	(61288, 43331, 0, 1, 1, 1, 0),
	(61288, 43316, 0, 1, 1, 1, 0),
	(61288, 43334, 0, 1, 1, 1, 0),
	(61288, 43374, 0, 1, 1, 1, 0),
	(61288, 43371, 0, 1, 1, 1, 0),
	(61288, 43342, 0, 1, 1, 1, 0),
	(61288, 43373, 0, 1, 1, 1, 0),
	(61288, 43372, 0, 1, 1, 1, 0),
	(61288, 43370, 0, 1, 1, 1, 0),
	(61288, 44920, 0, 1, 1, 1, 0),
	(61288, 43339, 0, 1, 1, 1, 0),
	(61288, 43359, 0, 1, 1, 1, 0),
	(61288, 43361, 0, 1, 1, 1, 0),
	(61288, 43362, 0, 1, 1, 1, 0),
	(61288, 43364, 0, 1, 1, 1, 0),
	(61288, 43360, 0, 1, 1, 1, 0),
	(61288, 43357, 0, 1, 1, 1, 0),
	(61288, 43350, 0, 1, 1, 1, 0),
	(61288, 43354, 0, 1, 1, 1, 0),
	(61288, 43356, 0, 1, 1, 1, 0),
	(61288, 43355, 0, 1, 1, 1, 0),
	(61288, 43338, 0, 1, 1, 1, 0),
	(61288, 43351, 0, 1, 1, 1, 0),
	(61288, 43340, 0, 1, 1, 1, 0),
	(61288, 43367, 0, 1, 1, 1, 0),
	(61288, 43366, 0, 1, 1, 1, 0),
	(61288, 43365, 0, 1, 1, 1, 0),
	(61288, 43368, 0, 1, 1, 1, 0),
	(61288, 43369, 0, 1, 1, 1, 0),
	(61288, 43343, 0, 1, 1, 1, 0),
	(61288, 43377, 0, 1, 1, 1, 0),
	(61288, 43379, 0, 1, 1, 1, 0),
	(61288, 43376, 0, 1, 1, 1, 0),
	(61288, 43380, 0, 1, 1, 1, 0),
	(61288, 43378, 0, 1, 1, 1, 0),
	(61288, 43389, 0, 1, 1, 1, 0),
	(61288, 43390, 0, 1, 1, 1, 0),
	(61288, 43393, 0, 1, 1, 1, 0),
	(61288, 43391, 0, 1, 1, 1, 0),
	(61288, 43394, 0, 1, 1, 1, 0),
	(61288, 43392, 0, 1, 1, 1, 0),
	(61288, 43388, 0, 1, 1, 1, 0),
	(61288, 43381, 0, 1, 1, 1, 0),
	(61288, 43386, 0, 1, 1, 1, 0),
	(61288, 44923, 0, 1, 1, 1, 0),
	(61288, 43385, 0, 1, 1, 1, 0),
	(61288, 43725, 0, 1, 1, 1, 0),
	(61288, 43344, 0, 1, 1, 1, 0),
	(61177, 43426, 0, 1, 1, 1, 0),
	(61177, 43430, 0, 1, 1, 1, 0),
	(61177, 43425, 0, 1, 1, 1, 0),
	(61177, 43415, 0, 1, 1, 1, 0),
	(61177, 43412, 0, 1, 1, 1, 0),
	(61177, 43421, 0, 1, 1, 1, 0),
	(61177, 43431, 0, 1, 1, 1, 0),
	(61177, 43419, 0, 1, 1, 1, 0),
	(61177, 40900, 0, 1, 1, 1, 0),
	(61177, 40908, 0, 1, 1, 1, 0),
	(61177, 40921, 0, 1, 1, 1, 0),
	(61177, 40915, 0, 1, 1, 1, 0),
	(61177, 40912, 0, 1, 1, 1, 0),
	(61177, 40920, 0, 1, 1, 1, 0),
	(61177, 40899, 0, 1, 1, 1, 0),
	(61177, 40906, 0, 1, 1, 1, 0),
	(61177, 42409, 0, 1, 1, 1, 0),
	(61177, 42407, 0, 1, 1, 1, 0),
	(61177, 42414, 0, 1, 1, 1, 0),
	(61177, 42417, 0, 1, 1, 1, 0),
	(61177, 42404, 0, 1, 1, 1, 0),
	(61177, 42396, 0, 1, 1, 1, 0),
	(61177, 42405, 0, 1, 1, 1, 0),
	(61177, 42403, 0, 1, 1, 1, 0),
	(61177, 42739, 0, 1, 1, 1, 0),
	(61177, 42751, 0, 1, 1, 1, 0),
	(61177, 42754, 0, 1, 1, 1, 0),
	(61177, 44684, 0, 1, 1, 1, 0),
	(61177, 42753, 0, 1, 1, 1, 0),
	(61177, 42748, 0, 1, 1, 1, 0),
	(61177, 42742, 0, 1, 1, 1, 0),
	(61177, 42740, 0, 1, 1, 1, 0),
	(61177, 42902, 0, 1, 1, 1, 0),
	(61177, 42914, 0, 1, 1, 1, 0),
	(61177, 42915, 0, 1, 1, 1, 0),
	(61177, 42917, 0, 1, 1, 1, 0),
	(61177, 42899, 0, 1, 1, 1, 0),
	(61177, 42916, 0, 1, 1, 1, 0),
	(61177, 42913, 0, 1, 1, 1, 0),
	(61177, 42901, 0, 1, 1, 1, 0),
	(61177, 43868, 0, 1, 1, 1, 0),
	(61177, 43867, 0, 1, 1, 1, 0),
	(61177, 43869, 0, 1, 1, 1, 0),
	(61177, 41109, 0, 1, 1, 1, 0),
	(61177, 41097, 0, 1, 1, 1, 0),
	(61177, 41107, 0, 1, 1, 1, 0),
	(61177, 41101, 0, 1, 1, 1, 0),
	(61177, 41110, 0, 1, 1, 1, 0),
	(61177, 42954, 0, 1, 1, 1, 0),
	(61177, 42971, 0, 1, 1, 1, 0),
	(61177, 42968, 0, 1, 1, 1, 0),
	(61177, 42965, 0, 1, 1, 1, 0),
	(61177, 42967, 0, 1, 1, 1, 0),
	(61177, 42969, 0, 1, 1, 1, 0),
	(61177, 42957, 0, 1, 1, 1, 0),
	(61177, 42959, 0, 1, 1, 1, 0),
	(61177, 42958, 0, 1, 1, 1, 0),
	(61177, 42469, 0, 1, 1, 1, 0),
	(61177, 42463, 0, 1, 1, 1, 0),
	(61177, 42472, 0, 1, 1, 1, 0),
	(61177, 42460, 0, 1, 1, 1, 0),
	(61177, 42454, 0, 1, 1, 1, 0),
	(61177, 42456, 0, 1, 1, 1, 0),
	(61177, 42459, 0, 1, 1, 1, 0),
	(61177, 42457, 0, 1, 1, 1, 0),
	(61177, 42464, 0, 1, 1, 1, 0),
	(61177, 41517, 0, 1, 1, 1, 0),
	(61177, 41534, 0, 1, 1, 1, 0),
	(61177, 41524, 0, 1, 1, 1, 0),
	(61177, 41538, 0, 1, 1, 1, 0),
	(61177, 41526, 0, 1, 1, 1, 0),
	(61177, 41552, 0, 1, 1, 1, 0),
	(61177, 41529, 0, 1, 1, 1, 0),
	(61177, 41518, 0, 1, 1, 1, 0),
	(58165, 7974, 100, 0, 1, 1, 0),
	(57844, 36783, 50, 0, 1, 1, 0),
	(57844, 36784, 5, 0, 1, 1, 0),
	(58160, 13926, 5, 0, 1, 1, 0),
	(58160, 24477, 100, 0, 1, 3, 0),
	(58160, 24478, 15, 0, 1, 1, 0),
	(58160, 24479, 1, 0, 1, 1, 0),
	(58165, 5500, 3, 0, 1, 1, 0),
	(58165, 7971, 5, 0, 1, 1, 0),
	(58165, 13926, 0.5, 0, 1, 1, 0),
	(58168, 5498, 5, 0, 1, 1, 0),
	(58168, 5500, 2.5, 0, 1, 1, 0),
	(58168, 5504, 100, 0, 1, 2, 0),
	(58172, 5498, 5, 0, 1, 1, 0),
	(58172, 5503, 100, 0, 1, 1, 0),
	(60893, 40077, 0, 1, 1, 3, 0),
	(60893, 44328, 0, 1, 1, 3, 0),
	(60893, 44329, 0, 1, 1, 3, 0),
	(61177, 37092, 0, 1, 1, 3, 0),
	(61177, 37094, 0, 1, 1, 3, 0),
	(61177, 37098, 0, 1, 1, 3, 0),
	(61177, 43145, 0, 1, 1, 1, 0),
	(61177, 43146, 0, 1, 1, 1, 0),
	(61177, 43464, 0, 1, 1, 3, 0),
	(61177, 43466, 0, 1, 1, 3, 0),
	(61177, 44315, 0, 1, 1, 1, 0),
	(61288, 1477, 0, 1, 1, 3, 0),
	(61288, 1478, 0, 1, 1, 3, 0),
	(61288, 1711, 0, 1, 1, 3, 0),
	(61288, 1712, 0, 1, 1, 3, 0),
	(61288, 2289, 0, 1, 1, 3, 0),
	(61288, 2290, 0, 1, 1, 3, 0),
	(61288, 37118, 0, 1, 1, 1, 0),
	(61288, 38682, 0, 1, 1, 1, 0),
	(61288, 39349, 0, 1, 1, 1, 0),
	(61898, 15924, -100, 0, 1, 1, 0),
	(58165, 5498, 1, 0, 1, 1, 0),
	(69412, 34054, 0, 1, 7, 19, 0),
	(69412, 34055, 0, 1, 2, 9, 0),
	(61500, 36909, 100, 0, 1, 1, 0),
	(62941, 23094, 0, 1, 1, 1, 0),
	(62941, 23095, 0, 1, 1, 1, 0),
	(62941, 28595, 0, 1, 1, 1, 0),
	(62941, 23116, 0, 1, 1, 1, 0),
	(62941, 23118, 0, 1, 1, 1, 0),
	(62941, 23119, 0, 1, 1, 1, 0),
	(62941, 23120, 0, 1, 1, 1, 0),
	(62941, 23114, 0, 1, 1, 1, 0),
	(62941, 23115, 0, 1, 1, 1, 0),
	(62941, 23121, 0, 1, 1, 1, 0),
	(62941, 23097, 0, 1, 1, 1, 0),
	(62941, 23113, 0, 1, 1, 1, 0);
/*!40000 ALTER TABLE `spell_loot_template` ENABLE KEYS */;
/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
