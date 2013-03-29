/* For test purposes only, each time script is run, drop and create a fresh phonebook DB */
/*
IF EXISTS(SELECT * FROM sys.databases WHERE name='PHONEBOOK')
	DROP DATABASE PHONEBOOK
*/
/* USE phonebook */

USE phonebook

/* create tables */
CREATE TABLE CITIES(ID        int primary key not null,
             REV_NUMB         int             not null,
             CODE      nvarchar(6) not null ,
             NAME      nvarchar(64)not null ,
             AREA      nvarchar(64)not null)			

CREATE TABLE PHONE_TYPES(ID         int primary key not null,
                         REV_NUMB   int             not null,
                         CODE       int             not null,
                         PHONE_TYPE nvarchar(64)    not null )	

CREATE TABLE SUBSCRIBERS(ID          int primary key not null,
                         REV_NUMB    int not null,
                         CODE        int not null,
                         FIRST_NAME  nvarchar(64)  not null,
                         SECOND_NAME nvarchar(64)  not null,
                         THIRD_NAME  nvarchar(64)  not null,
                         IDENT_NUMB	 nvarchar(10)  not null,
                         CITY_ID     int           not null, 
                         CITY_ADDR	 nvarchar(128) not null, 
                         foreign key (CITY_ID) references CITIES (ID))

CREATE TABLE SUBSCRIBER_PHONE_NUMBERS(ID            int primary key not null,
                                      REV_NUMB      int             not null,
                                      SUBSCRIBER_ID int             not null,
                                      PHONE_ID      int             not null,
                                      PHONE_NUMB    nvarchar(64)    not null,
                                      foreign key (SUBSCRIBER_ID) references SUBSCRIBERS (ID),
                                      foreign key (PHONE_ID)      references PHONE_TYPES (ID))			 									


