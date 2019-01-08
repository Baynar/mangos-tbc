/* Delete default user and its privileges (require MYSQL 5.7, MARIADB 10.1.3) */
DROP USER IF EXISTS `mangos`@`localhost`;

<<<<<<< HEAD
/* Delete default tables */
DROP DATABASE IF EXISTS `tbcmangos`;
DROP DATABASE IF EXISTS `tbccharacters`;
DROP DATABASE IF EXISTS `tbcrealmd`;
=======
REVOKE ALL PRIVILEGES ON `mangos` . * FROM 'mangos'@'localhost';

REVOKE GRANT OPTION ON `mangos` . * FROM 'mangos'@'localhost';

REVOKE ALL PRIVILEGES ON `characters` . * FROM 'mangos'@'localhost';

REVOKE GRANT OPTION ON `characters` . * FROM 'mangos'@'localhost';

REVOKE ALL PRIVILEGES ON `realmd` . * FROM 'mangos'@'localhost';

REVOKE GRANT OPTION ON `realmd` . * FROM 'mangos'@'localhost';

DELETE FROM `user` WHERE CONVERT( User USING utf8 ) = CONVERT( 'mangos' USING utf8 ) AND CONVERT( Host USING utf8 ) = CONVERT( 'localhost' USING utf8 ) ;

DROP DATABASE IF EXISTS `mangos` ;

DROP DATABASE IF EXISTS `characters` ;

DROP DATABASE IF EXISTS `realmd` ;
>>>>>>> master
