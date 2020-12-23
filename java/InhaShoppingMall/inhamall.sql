-- MySQL dump 10.13  Distrib 8.0.22, for Win64 (x86_64)
--
-- Host: localhost    Database: inhamall
-- ------------------------------------------------------
-- Server version	5.7.32-log

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `basket_table`
--

DROP TABLE IF EXISTS `basket_table`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `basket_table` (
  `basketidx` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `userid` varchar(20) NOT NULL,
  `productidx` varchar(20) NOT NULL,
  `qty` varchar(10) DEFAULT NULL,
  PRIMARY KEY (`basketidx`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `basket_table`
--

LOCK TABLES `basket_table` WRITE;
/*!40000 ALTER TABLE `basket_table` DISABLE KEYS */;
INSERT INTO `basket_table` VALUES (1,'admin','5','1'),(2,'admin','5','1'),(3,'admin','4','5'),(4,'hk1554','5','5');
/*!40000 ALTER TABLE `basket_table` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `order_table`
--

DROP TABLE IF EXISTS `order_table`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `order_table` (
  `orderidx` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `userid` varchar(20) NOT NULL,
  `productidx` int(10) NOT NULL,
  `qty` int(10) DEFAULT NULL,
  `memo` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`orderidx`)
) ENGINE=InnoDB AUTO_INCREMENT=17 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `order_table`
--

LOCK TABLES `order_table` WRITE;
/*!40000 ALTER TABLE `order_table` DISABLE KEYS */;
INSERT INTO `order_table` VALUES (15,'hk1554',5,1,'빠른 배송 부탁해요');
/*!40000 ALTER TABLE `order_table` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `product_table`
--

DROP TABLE IF EXISTS `product_table`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `product_table` (
  `productidx` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `producttype` int(11) NOT NULL,
  `productname` varchar(100) NOT NULL,
  `img` varchar(300) NOT NULL,
  `explanation` varchar(800) NOT NULL,
  `price` int(11) NOT NULL,
  `qty` int(11) NOT NULL,
  PRIMARY KEY (`productidx`)
) ENGINE=InnoDB AUTO_INCREMENT=27 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `product_table`
--

LOCK TABLES `product_table` WRITE;
/*!40000 ALTER TABLE `product_table` DISABLE KEYS */;
INSERT INTO `product_table` VALUES (4,12,'Apple 맥북 프로 13형 2020년형 256G 스페이스 그레이 (MXK32KH/A)','image\\product\\12_mac.jpg','화면크기 : 13인치(32~35cm) / 무게 : 1.4kg\r\n\r\n종류 : 코어i5 8세대 / 운영체제 : MAC OS\r\n\r\n칩셋 제조사 : 인텔 / 코어종류 : 쿼드코어 / CPU속도 : 1.4GHz\r\n\r\n터보부스트 : 3.9GHz / 램 : 8GB / 메모리 타입 : LPDDR3\r\n\r\n인텔 GPU : Iris Plus 645 / 그래픽 메모리 : 시스템 메모리 공유\r\n\r\n해상도 : 2560x1600(WQXGA) / 패널 : IPS패널(광시야각)\r\n\r\n화면비율 : 16대10 / 밝기 : 슈퍼브라이트(500nit)',1850000,98),(5,11,'삼성전자 갤럭시북 이온 NT950XCR-G58A','image\\product\\11_samsung_ion.jpg','화면크기 : 15인치(37~39cm) / 무게 : 1.26kg\r\n\r\n종류 : 코어i5 10세대 / 운영체제 : 미포함(FreeDos)\r\n\r\nCPU : 코어i5-10210U / 칩셋 제조사 : 인텔코드명 : 코멧레이크\r\n \r\nCPU속도 : 1.6GHz / 터보부스트 : 4.2GHz / 램 : 8GB\r\n\r\n메모리 타입 : DDR4 / NVIDIA GPU : 지포스MX250 / \r\n\r\n그래픽 메모리 : 2GB / 해상도 : 1920x1080(FHD)\r\n\r\n화면비율 : 16대9 / 베젤 : 슬림베젤',1500000,95),(6,11,'LG전자 그램15 15ZD90N-VX50K','image\\product\\11_lg_gram.jpg','화면크기 : 15인치(37~39cm) / 무게 : 1.12kg \r\n\r\n종류 : 코어i5 10세대 / 운영체제 : 미포함(FreeDos)\r\n\r\nCPU : 코어i5-1035G7 / 칩셋 제조사 : 인텔\r\n\r\n코어종류 : 쿼드코어 / 코드명 : 아이스레이크\r\n\r\nCPU속도 : 1.2GHz / 터보부스트 : 3.7GHz\r\n\r\n램 : 8GB / 메모리 타입 : DDR4 / 인텔 GPU : Iris Plus\r\n\r\n그래픽 메모리 : 시스템 메모리 공유 \r\n\r\n해상도 : 1920x1080(FHD) / 패널 : IPS패널(광시야각)',1430000,100),(7,12,'Apple 맥북 프로 13형 2020년형 512G 스페이스 그레이 (MWP42KH/A)','image\\product\\12_mac_MWP42KHA.jpg','화면크기 : 13인치(32~35cm) / 무게 : 1.4kg\r\n\r\n종류 : 코어i5 10세대 / 운영체제 : MAC OS \r\n\r\n칩셋 제조사 : 인텔 / 코어종류 : 쿼드코어\r\n\r\n코드명 : 아이스레이크 / CPU속도 : 2.0GHz / 터보부스트 : 3.9GHz\r\n\r\n램 : 16GB / 메모리 타입 : LPDDR4x / 인텔 GPU : Iris Plus\r\n\r\n해상도 : 2560x1600(WQXGA) / 패널 : IPS패널(광시야각)\r\n\r\n화면비율 : 16대10 / 디스플레이 종류 : LCD\r\n',2280000,100),(8,13,'삼성전자 삼성 DM500T9A-A58A','image\\product\\13_DM500T9AA58A.jpg','품목 : 데스크탑 / 특징 : 사무용CPU / 제조사 : 인텔\r\n\r\nCPU : 코어i5-9400CPU / 종류 : 코어i5 9세대\r\n\r\n코어종류 : 6코어 / 터보부스트 : 4.1GHz / 램용량 : 8GB\r\n\r\nSSD용량 : 256GB / 그래픽 : 인텔UHD630 / 파워 : 350W\r\n\r\n램규격 : DDR4 / 운영체제 : 윈도우10 홈 / 속도 : 2.9GHz\r\n\r\nODD : DVD-Dual / 블루투스 : 블루투스5.0\r\n\r\n랜 : 무선랜ac, 유선랜(기가비트)',860000,100),(9,14,'삼성전자 삼성 SM-T970 갤럭시 탭 S7+ WiFi 256GB','image\\product\\14_SMT970.jpg','화면크기 : 12.4인치(31.5cm) / 형태 : 패드형\r\n\r\n통신규격 : WiFi전용 / 내장메모리 : 256GB / 램 : 8GB\r\n\r\n운영체제 : 안드로이드 / 블루투스 : 블루투스5.0\r\n\r\n무게 : 575g / CPU속도 : 2.4GHz / 패널 : TFT-LCD\r\n\r\n디스플레이 특징 : 터치스크린 / 사용시간 : 14시간\r\n\r\n부가기능 : 조도센서, 가속도센서, 자이로센서 / 코어 : 옥타\r\n\r\n단자 : USB 3.0 x 1 / 모델명(기타) : SM-T970 / 가로 : 285 mm',1050000,100),(10,14,'Apple 아이패드에어 아이패드 에어 4세대 WIFI 64G','image\\product\\14_ipadair4.jpg','화면크기 : 10.9인치(27.6cm) / 형태 : 패드형\r\n\r\n통신규격 : WiFi전용 / 내장메모리 : 64GB / 램 : 4GB\r\n\r\n운영체제 : iPadOS / 블루투스 : 블루투스5.0 / 무게 : 458g\r\n\r\nbit유형 : 64 / 칩셋 제조사 : 애플 / HDD 용량 : 미포함\r\n\r\n패널 : IPS패널(광시야각)\r\n\r\n디스플레이 특징 : 터치스크린, 자동 밝기 조절, LCD 회전\r\n\r\n배터리 타입 : 리튬폴리머 / 부가기능(디스플레이) : 라미네이팅\r\n\r\n사용시간 : 10시간',730000,99),(24,21,'삼성전자 오디세이 G7 C27G75T','image\\product\\21_samsun_odeysey.jpg','화면크기 : 27인치(68~69cm) / 패널 : VA\r\n\r\n최대 해상도 : 2560x1440(QHD) / 최대 주사율 : 240Hz\r\n\r\n화면종류 : LED / 화면비율 : 16:9 / 응답속도 : 1ms\r\n\r\n밝기 : 600CD / 명암비 : 2500 : 1 / 동적명암비 : 무한:1\r\n\r\n픽셀피치 : 0.2331mm / 곡률 : 1000R / HDR : DisplayHDR 600\r\n\r\n단자 : HDMI, DisplayPort(2개)\r\n\r\n게임특화 : 게임모드, 블랙이퀄라이저, FreeSync2, G-Sync(호환)',690000,100),(25,22,'RAZER DeathAdder V2 Pro','image\\product\\22_RAZER_DeathAdder.jpg','연결방식 : 유무선겸용 / 센서방식 : FOCUS+센서PC\r\n\r\n연결방식 : 블루투스, USB, 유무선겸용, HYPERSPEED\r\n\r\n휠 조정 : 상하 / 전원 : 충전(케이블) / 버튼수 : 8버튼\r\n\r\n매크로 : 프로파일저장, 가능 / 최대가속 : 50GB / LED : 커스텀LED\r\n\r\n최대감도 : 200000dpi / 센서종류 : PAW-3399\r\n\r\n전원기능 : 자동절전, 절전기능\r\n\r\n배터리 : 충전식, 충전식(거치대), USB충전\r\n\r\n수신기 : 수납가능, 동글포함',150000,100),(26,23,'로지텍G G413 기계식 게이밍 키보드','image\\product\\23_LogitecG_G413.jpg','연결방식 : 유선  / PC연결방식 : USB / 키방식 : 기계식\r\n\r\n키스위치 : ROMER-G / 부가기능 : 동시입력, 윈도Key잠금\r\n\r\n무게 : 1,105g / 케이블 : 꼬임방지케이블',48000,100);
/*!40000 ALTER TABLE `product_table` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `user_table`
--

DROP TABLE IF EXISTS `user_table`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `user_table` (
  `useridx` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `usertype` int(11) DEFAULT NULL,
  `id` varchar(20) NOT NULL,
  `password` varchar(45) NOT NULL,
  `username` varchar(20) NOT NULL,
  `dob` date DEFAULT NULL,
  `sex` varchar(10) DEFAULT NULL,
  `contact` varchar(20) DEFAULT NULL,
  `address` varchar(120) DEFAULT NULL,
  `email` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`useridx`)
) ENGINE=InnoDB AUTO_INCREMENT=12 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `user_table`
--

LOCK TABLES `user_table` WRITE;
/*!40000 ALTER TABLE `user_table` DISABLE KEYS */;
INSERT INTO `user_table` VALUES (2,5,'admin','admin','운영자','1997-03-29','남자','010-9301-3029','관리자','hk1554@naver.com'),(10,4,'hk1554','970329','김현석','1997-03-29','남자','010-0000-0000','라마바','hk1554@naver.com'),(11,3,'test12345','970329','김현석','1997-03-29','남자','010-9301-3029','사아자','hk1554@naver.com');
/*!40000 ALTER TABLE `user_table` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2020-12-20  4:02:35
