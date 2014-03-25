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

-- Dumping structure for table mangos.playercreateinfo_action
CREATE TABLE IF NOT EXISTS `playercreateinfo_action` (
  `race` tinyint(3) unsigned NOT NULL default '0',
  `class` tinyint(3) unsigned NOT NULL default '0',
  `button` smallint(5) unsigned NOT NULL default '0',
  `action` int(11) unsigned NOT NULL default '0',
  `type` smallint(5) unsigned NOT NULL default '0',
  PRIMARY KEY  (`race`,`class`,`button`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- Dumping data for table mangos.playercreateinfo_action: 355 rows
DELETE FROM `playercreateinfo_action`;
/*!40000 ALTER TABLE `playercreateinfo_action` DISABLE KEYS */;
INSERT INTO `playercreateinfo_action` (`race`, `class`, `button`, `action`, `type`) VALUES
	(1, 1, 0, 6603, 0),
	(1, 1, 72, 6603, 0),
	(1, 1, 73, 78, 0),
	(1, 1, 82, 59752, 0),
	(1, 1, 84, 6603, 0),
	(1, 1, 96, 6603, 0),
	(1, 1, 108, 6603, 0),
	(1, 2, 0, 6603, 0),
	(1, 2, 2, 635, 0),
	(1, 2, 9, 59752, 0),
	(1, 4, 0, 6603, 0),
	(1, 4, 1, 1752, 0),
	(1, 4, 2, 2098, 0),
	(1, 4, 3, 2764, 0),
	(1, 4, 10, 59752, 0),
	(3, 1, 3, 2481, 0),
	(1, 5, 1, 2050, 0),
	(1, 5, 0, 585, 0),
	(1, 5, 9, 59752, 0),
	(1, 6, 0, 6603, 0),
	(1, 6, 1, 49576, 0),
	(1, 6, 2, 45477, 0),
	(1, 6, 3, 45462, 0),
	(1, 6, 4, 45902, 0),
	(1, 6, 5, 47541, 0),
	(1, 6, 11, 59752, 0),
	(2, 1, 2, 20572, 0),
	(1, 8, 1, 168, 0),
	(1, 8, 0, 133, 0),
	(1, 8, 9, 59752, 0),
	(2, 1, 1, 78, 0),
	(1, 9, 1, 687, 0),
	(1, 9, 0, 686, 0),
	(1, 9, 9, 59752, 0),
	(1, 9, 11, 4604, 128),
	(2, 1, 0, 6603, 0),
	(2, 1, 72, 6603, 0),
	(2, 1, 73, 78, 0),
	(2, 1, 74, 20572, 0),
	(2, 1, 84, 6603, 0),
	(2, 1, 96, 6603, 0),
	(2, 1, 108, 6603, 0),
	(2, 3, 0, 6603, 0),
	(2, 3, 1, 2973, 0),
	(2, 3, 2, 75, 0),
	(2, 3, 9, 20572, 0),
	(2, 4, 0, 6603, 0),
	(2, 4, 1, 1752, 0),
	(2, 4, 2, 2098, 0),
	(2, 4, 3, 2764, 0),
	(2, 4, 4, 20572, 0),
	(2, 6, 0, 6603, 0),
	(2, 6, 1, 49576, 0),
	(2, 6, 2, 45477, 0),
	(2, 6, 3, 45462, 0),
	(2, 6, 4, 45902, 0),
	(2, 6, 5, 47541, 0),
	(2, 6, 10, 20572, 0),
	(2, 7, 0, 6603, 0),
	(2, 7, 1, 403, 0),
	(2, 7, 2, 331, 0),
	(2, 7, 3, 33697, 0),
	(3, 1, 2, 20594, 0),
	(2, 9, 2, 33702, 0),
	(2, 9, 1, 687, 0),
	(2, 9, 0, 686, 0),
	(3, 1, 0, 6603, 0),
	(3, 1, 1, 78, 0),
	(3, 1, 72, 6603, 0),
	(3, 1, 73, 78, 0),
	(3, 1, 74, 20594, 0),
	(3, 1, 75, 2481, 0),
	(3, 1, 84, 6603, 0),
	(3, 1, 96, 6603, 0),
	(3, 1, 108, 6603, 0),
	(3, 2, 0, 6603, 0),
	(3, 2, 2, 635, 0),
	(3, 2, 3, 20594, 0),
	(3, 2, 4, 2481, 0),
	(3, 3, 0, 6603, 0),
	(3, 3, 1, 2973, 0),
	(3, 3, 2, 75, 0),
	(3, 3, 3, 20594, 0),
	(3, 3, 4, 2481, 0),
	(3, 3, 75, 20594, 0),
	(3, 3, 76, 2481, 0),
	(3, 4, 0, 6603, 0),
	(3, 4, 1, 1752, 0),
	(3, 4, 2, 2098, 0),
	(3, 4, 3, 2764, 0),
	(3, 4, 4, 20594, 0),
	(3, 4, 5, 2481, 0),
	(4, 1, 74, 58984, 0),
	(3, 5, 3, 2481, 0),
	(3, 5, 2, 20594, 0),
	(3, 5, 1, 2050, 0),
	(3, 5, 0, 585, 0),
	(3, 6, 0, 6603, 0),
	(3, 6, 1, 49576, 0),
	(3, 6, 2, 45477, 0),
	(3, 6, 3, 45462, 0),
	(3, 6, 4, 45902, 0),
	(3, 6, 5, 47541, 0),
	(3, 6, 10, 2481, 0),
	(4, 1, 73, 78, 0),
	(4, 4, 82, 58984, 0),
	(4, 1, 72, 6603, 0),
	(4, 1, 2, 58984, 0),
	(4, 1, 108, 6603, 0),
	(4, 1, 1, 78, 0),
	(4, 1, 0, 6603, 0),
	(4, 3, 0, 6603, 0),
	(4, 3, 1, 2973, 0),
	(4, 3, 2, 75, 0),
	(4, 3, 3, 58984, 0),
	(4, 4, 0, 6603, 0),
	(4, 4, 1, 1752, 0),
	(4, 4, 2, 2098, 0),
	(4, 4, 3, 2764, 0),
	(4, 4, 4, 58984, 0),
	(4, 5, 81, 58984, 0),
	(4, 5, 2, 58984, 0),
	(4, 5, 1, 2050, 0),
	(4, 5, 0, 585, 0),
	(4, 6, 0, 6603, 0),
	(4, 6, 1, 49576, 0),
	(4, 6, 2, 45477, 0),
	(4, 6, 3, 45462, 0),
	(4, 6, 4, 45902, 0),
	(4, 6, 5, 47541, 0),
	(4, 6, 10, 58984, 0),
	(4, 6, 83, 58984, 0),
	(4, 11, 72, 6603, 0),
	(4, 11, 2, 58984, 0),
	(4, 11, 108, 6603, 0),
	(4, 11, 1, 5185, 0),
	(4, 11, 0, 5176, 0),
	(5, 1, 0, 6603, 0),
	(5, 1, 72, 6603, 0),
	(5, 1, 73, 78, 0),
	(5, 1, 74, 20577, 0),
	(5, 1, 83, 4604, 128),
	(5, 1, 84, 6603, 0),
	(5, 1, 96, 6603, 0),
	(5, 1, 108, 6603, 0),
	(5, 4, 0, 6603, 0),
	(5, 4, 1, 1752, 0),
	(5, 4, 2, 2098, 0),
	(5, 4, 3, 2764, 0),
	(5, 4, 4, 20577, 0),
	(5, 4, 11, 4604, 128),
	(5, 5, 2, 20577, 0),
	(5, 5, 1, 2050, 0),
	(5, 5, 0, 585, 0),
	(5, 6, 0, 6603, 0),
	(5, 6, 1, 49576, 0),
	(5, 6, 2, 45477, 0),
	(5, 6, 3, 45462, 0),
	(5, 6, 4, 45902, 0),
	(5, 6, 5, 47541, 0),
	(5, 6, 10, 20577, 0),
	(5, 8, 2, 20577, 0),
	(5, 8, 1, 168, 0),
	(5, 8, 0, 133, 0),
	(5, 9, 2, 20577, 0),
	(5, 9, 1, 687, 0),
	(5, 9, 0, 686, 0),
	(6, 1, 0, 6603, 0),
	(6, 1, 1, 78, 0),
	(6, 1, 2, 20549, 0),
	(6, 1, 72, 6603, 0),
	(6, 1, 73, 78, 0),
	(6, 1, 74, 20549, 0),
	(6, 1, 84, 6603, 0),
	(6, 1, 96, 6603, 0),
	(6, 1, 108, 6603, 0),
	(6, 3, 0, 6603, 0),
	(6, 3, 1, 2973, 0),
	(6, 3, 2, 75, 0),
	(6, 3, 3, 20549, 0),
	(6, 3, 75, 20549, 0),
	(6, 6, 0, 6603, 0),
	(6, 6, 1, 49576, 0),
	(6, 6, 2, 45477, 0),
	(6, 6, 3, 45462, 0),
	(6, 6, 4, 45902, 0),
	(6, 6, 5, 47541, 0),
	(6, 6, 10, 20549, 0),
	(6, 6, 75, 20549, 0),
	(6, 7, 0, 6603, 0),
	(6, 7, 1, 403, 0),
	(6, 7, 2, 331, 0),
	(6, 7, 3, 20549, 0),
	(6, 7, 11, 4604, 128),
	(6, 7, 75, 20549, 0),
	(6, 11, 96, 6603, 0),
	(6, 11, 84, 6603, 0),
	(6, 11, 75, 20549, 0),
	(6, 11, 72, 6603, 0),
	(6, 11, 2, 20549, 0),
	(6, 11, 108, 6603, 0),
	(6, 11, 1, 5185, 0),
	(6, 11, 0, 5176, 0),
	(7, 1, 0, 6603, 0),
	(7, 1, 1, 78, 0),
	(7, 1, 72, 6603, 0),
	(7, 1, 73, 78, 0),
	(7, 1, 84, 6603, 0),
	(7, 1, 96, 6603, 0),
	(7, 1, 108, 6603, 0),
	(7, 4, 0, 6603, 0),
	(7, 4, 1, 1752, 0),
	(7, 4, 2, 2098, 0),
	(7, 4, 3, 2764, 0),
	(7, 6, 0, 6603, 0),
	(7, 6, 1, 49576, 0),
	(7, 6, 2, 45477, 0),
	(7, 6, 3, 45462, 0),
	(7, 6, 4, 45902, 0),
	(7, 6, 5, 47541, 0),
	(7, 6, 10, 20589, 0),
	(7, 6, 83, 41751, 128),
	(7, 6, 72, 6603, 0),
	(7, 6, 11, 41751, 128),
	(7, 6, 84, 6603, 0),
	(7, 6, 96, 6603, 0),
	(7, 6, 108, 6603, 0),
	(7, 8, 1, 168, 0),
	(7, 8, 0, 133, 0),
	(8, 4, 76, 26297, 0),
	(8, 1, 2, 26297, 0),
	(8, 1, 1, 78, 0),
	(7, 9, 1, 687, 0),
	(7, 9, 0, 686, 0),
	(8, 1, 0, 6603, 0),
	(8, 1, 72, 6603, 0),
	(8, 1, 73, 78, 0),
	(8, 1, 74, 2764, 0),
	(8, 1, 75, 26297, 0),
	(8, 1, 84, 6603, 0),
	(8, 1, 96, 6603, 0),
	(8, 1, 108, 6603, 0),
	(8, 3, 0, 6603, 0),
	(8, 3, 1, 2973, 0),
	(8, 3, 2, 75, 0),
	(8, 3, 11, 4604, 128),
	(8, 4, 0, 6603, 0),
	(8, 4, 1, 1752, 0),
	(8, 4, 2, 2098, 0),
	(8, 4, 3, 2764, 0),
	(8, 4, 4, 26297, 0),
	(8, 5, 2, 26297, 0),
	(8, 5, 1, 2050, 0),
	(8, 7, 3, 26297, 0),
	(8, 6, 0, 6603, 0),
	(8, 6, 1, 49576, 0),
	(8, 6, 2, 45477, 0),
	(8, 6, 3, 45462, 0),
	(8, 6, 4, 45902, 0),
	(8, 6, 5, 47541, 0),
	(8, 6, 10, 26297, 0),
	(8, 7, 0, 6603, 0),
	(8, 7, 1, 403, 0),
	(8, 7, 2, 331, 0),
	(8, 5, 0, 585, 0),
	(8, 8, 2, 26297, 0),
	(8, 8, 1, 168, 0),
	(8, 8, 0, 133, 0),
	(8, 3, 3, 26297, 0),
	(10, 2, 0, 6603, 0),
	(10, 2, 2, 635, 0),
	(10, 2, 3, 28730, 0),
	(10, 2, 11, 20857, 128),
	(10, 3, 0, 6603, 0),
	(10, 3, 1, 2973, 0),
	(10, 3, 2, 75, 0),
	(10, 3, 3, 28730, 0),
	(10, 3, 11, 20857, 128),
	(10, 4, 0, 6603, 0),
	(10, 4, 1, 1752, 0),
	(10, 4, 2, 2098, 0),
	(10, 4, 3, 2764, 0),
	(10, 4, 4, 25046, 0),
	(10, 4, 11, 20857, 128),
	(10, 5, 0, 6603, 0),
	(10, 5, 1, 585, 0),
	(10, 5, 2, 2050, 0),
	(10, 5, 3, 28730, 0),
	(10, 5, 11, 20857, 128),
	(10, 6, 0, 6603, 0),
	(10, 6, 1, 49576, 0),
	(10, 6, 2, 45477, 0),
	(10, 6, 3, 45462, 0),
	(10, 6, 4, 45902, 0),
	(10, 6, 5, 47541, 0),
	(10, 6, 6, 50613, 0),
	(10, 8, 0, 6603, 0),
	(10, 8, 1, 133, 0),
	(10, 8, 2, 168, 0),
	(10, 8, 3, 28730, 0),
	(10, 8, 11, 20857, 128),
	(10, 9, 0, 6603, 0),
	(10, 9, 1, 686, 0),
	(10, 9, 2, 687, 0),
	(10, 9, 3, 28730, 0),
	(10, 9, 11, 20857, 128),
	(11, 1, 0, 6603, 0),
	(11, 1, 72, 6603, 0),
	(11, 1, 73, 78, 0),
	(11, 1, 74, 28880, 0),
	(11, 1, 84, 6603, 0),
	(11, 1, 96, 6603, 0),
	(11, 1, 108, 6603, 0),
	(11, 2, 0, 6603, 0),
	(11, 2, 2, 635, 0),
	(11, 2, 3, 59542, 0),
	(11, 3, 0, 6603, 0),
	(11, 3, 1, 2973, 0),
	(11, 3, 2, 75, 0),
	(11, 3, 3, 59543, 0),
	(5, 1, 2, 20577, 0),
	(5, 1, 1, 78, 0),
	(11, 3, 72, 6603, 0),
	(11, 3, 73, 2973, 0),
	(11, 3, 74, 75, 0),
	(4, 11, 96, 6603, 0),
	(4, 11, 84, 6603, 0),
	(11, 5, 0, 6603, 0),
	(11, 5, 1, 585, 0),
	(11, 5, 2, 2050, 0),
	(11, 5, 3, 59544, 0),
	(4, 11, 74, 58984, 0),
	(4, 3, 81, 58984, 0),
	(4, 1, 96, 6603, 0),
	(11, 6, 0, 6603, 0),
	(11, 6, 1, 49576, 0),
	(11, 6, 2, 45477, 0),
	(11, 6, 3, 45462, 0),
	(11, 6, 4, 45902, 0),
	(11, 6, 5, 47541, 0),
	(11, 6, 10, 59545, 0),
	(11, 7, 0, 6603, 0),
	(11, 7, 1, 403, 0),
	(11, 7, 2, 331, 0),
	(11, 7, 3, 59547, 0),
	(4, 1, 84, 6603, 0),
	(3, 2, 1, 20154, 0),
	(11, 8, 0, 6603, 0),
	(11, 8, 1, 133, 0),
	(11, 8, 2, 168, 0),
	(11, 8, 3, 59548, 0),
	(1, 2, 1, 20154, 0),
	(1, 1, 9, 59752, 0),
	(1, 1, 1, 78, 0),
	(11, 6, 11, 41751, 128);
/*!40000 ALTER TABLE `playercreateinfo_action` ENABLE KEYS */;
/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;