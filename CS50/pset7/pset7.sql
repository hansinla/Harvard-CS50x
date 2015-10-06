-- MySQL dump 10.14  Distrib 5.5.32-MariaDB, for Linux (i686)
--
-- Host: localhost    Database: pset7
-- ------------------------------------------------------
-- Server version	5.5.32-MariaDB

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `history`
--

DROP TABLE IF EXISTS `history`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `history` (
  `datetime` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `id` int(10) NOT NULL,
  `symbol` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `transaction` varchar(10) COLLATE utf8_unicode_ci NOT NULL,
  `shares` int(11) NOT NULL,
  `price` double NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `history`
--

LOCK TABLES `history` WRITE;
/*!40000 ALTER TABLE `history` DISABLE KEYS */;
INSERT INTO `history` VALUES ('2014-05-07 00:43:32',8,'AAPL','BUY',1,594.41),('2014-05-07 01:06:36',8,'AAPL','BUY',1,594.41),('2014-05-07 01:07:01',8,'AAPL','SELL',1,594.41),('2014-05-07 01:11:04',8,'PFE','BUY',5,29.43),('2014-05-07 01:15:19',8,'PFE','SELL',5,29.43),('2014-05-07 01:15:33',8,'PFE','BUY',4,29.43),('2014-05-07 01:15:40',8,'PFE','SELL',4,29.43),('2014-05-07 01:16:51',6,'AAPL','BUY',400,594.41),('2014-05-07 01:17:11',6,'PFE','BUY',100,29.43),('2014-05-07 05:20:47',8,'T','BUY',20,35.49),('2014-05-07 05:21:01',8,'COST','BUY',50,112.83),('2014-05-07 05:21:24',8,'AAPL','BUY',5,594.41),('2014-05-07 05:21:52',8,'GM','BUY',5,34.75),('2014-05-07 05:22:12',8,'GM','BUY',8,34.75),('2014-05-07 05:25:36',8,'RFMD','BUY',20,8.77),('2014-05-07 05:26:44',8,'RFMD','BUY',5,8.77),('2014-05-07 05:57:48',8,'AAPL','SELL',5,594.41),('2014-05-07 05:59:09',8,'GM','SELL',13,34.75),('2014-05-07 06:15:59',8,'T','SELL',20,35.49),('2014-05-07 06:18:38',8,'COST','SELL',50,112.83),('2014-05-07 06:20:16',8,'RFMD','SELL',25,8.77),('2014-05-07 06:21:10',8,'T','BUY',100,35.49),('2014-05-07 06:21:15',8,'T','SELL',100,35.49),('2014-05-07 06:22:05',8,'T','BUY',100,35.49),('2014-05-07 06:22:10',8,'T','SELL',100,35.49),('2014-05-07 06:23:24',8,'AAPL','BUY',5,594.41),('2014-05-07 06:23:37',8,'T','BUY',20,35.49),('2014-05-07 06:24:04',8,'AAPL','SELL',5,594.41),('2014-05-07 06:24:15',8,'T','SELL',20,35.49);
/*!40000 ALTER TABLE `history` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `stock`
--

DROP TABLE IF EXISTS `stock`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `stock` (
  `id` int(10) unsigned NOT NULL,
  `symbol` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `shares` int(10) unsigned NOT NULL,
  PRIMARY KEY (`id`,`symbol`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `stock`
--

LOCK TABLES `stock` WRITE;
/*!40000 ALTER TABLE `stock` DISABLE KEYS */;
INSERT INTO `stock` VALUES (1,'AAPL',10),(2,'COST',25),(3,'RTN',8),(6,'AAPL',400),(6,'PFE',100);
/*!40000 ALTER TABLE `stock` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `users`
--

DROP TABLE IF EXISTS `users`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `users` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `username` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `hash` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `cash` decimal(65,4) unsigned NOT NULL DEFAULT '0.0000',
  PRIMARY KEY (`id`),
  UNIQUE KEY `username` (`username`)
) ENGINE=InnoDB AUTO_INCREMENT=16 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `users`
--

LOCK TABLES `users` WRITE;
/*!40000 ALTER TABLE `users` DISABLE KEYS */;
INSERT INTO `users` VALUES (1,'caesar','$1$50$GHABNWBNE/o4VL7QjmQ6x0',10000.0000),(2,'hirschhorn','$1$50$lJS9HiGK6sphej8c4bnbX.',10000.0000),(3,'jharvard','$1$50$RX3wnAMNrGIbgzbRYrxM1/',10000.0000),(4,'malan','$1$HA$azTGIMVlmPi9W9Y12cYSj/',10000.0000),(5,'milo','$1$HA$6DHumQaK4GhpX8QE23C8V1',10000.0000),(6,'skroob','$1$50$euBi4ugiJmbpIbvTTfmfI.',59470.0500),(7,'zamyla','$1$50$uwfqB45ANW.9.6qaQ.DcF.',10000.0000),(8,'Hans','$1$Nm1cjuxI$F178JRUZlaXkf0SmPm.ZW/',10000.0000),(12,'Julian','$1$euTTj68d$U6iclkvMiyifr29vja/qV0',10000.0000),(13,'Daniela','$1$GXt3fwMv$EmuKp4Cq2oGYWp6tGFb0c/',10000.0000),(15,'Alex','$1$hmRqQaud$30FvZqj4Tfvrnky0OYtUS0',10000.0000);
/*!40000 ALTER TABLE `users` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2014-05-07  2:27:32
