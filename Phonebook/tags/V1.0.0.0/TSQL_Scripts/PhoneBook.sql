/* For test purposes only, each time script is run, drop and create a fresh phonebook DB */
USE Test

IF EXISTS(SELECT * FROM sys.databases WHERE name='phonebook')
	DROP DATABASE phonebook

CREATE  DATABASE phonebook

/* USE phonebook */
USE phonebook
/* create tables */
CREATE TABLE cities(id      int primary key not null,
					          rev_nmb	int             not null,
					          code    nvarchar(6)	not null ,
					          name    nvarchar(64)not null ,
					          area    nvarchar(64)not null)
PRINT '"cities" table was created'					

CREATE TABLE phones(id         int primary key not null,
					          rev_nmb	   int             not null,
					          code       nvarchar(5) not null,
				            phone_type nvarchar(64)not null )
PRINT '"phones" table was created'					

CREATE TABLE subscribers(id          int primary key not null,
	  					           rev_nmb	   int not null,
						             code        dec not null,
						             first_name  nvarchar(64)  not null,
						             second_name nvarchar(64)  not null,
						             third_name  nvarchar(64)  not null,
						             ident_nmb	 nvarchar(10)  not null,
						             city_id	   int           not null, 
						             city_addr	 nvarchar(128) not null, 
						             foreign key (city_id) references cities (id))
PRINT '"subscribers" table was created'

CREATE TABLE subscriber_phone_numbers(id  int primary key    not null,
									                    rev_nmb	    int        not null,
									                    subscriber_id int          not null,
								 	                    phone_id	    int          not null,
								 	                    phone_number  nvarchar(64) not null,
		   						                    foreign key (subscriber_id) references subscribers (id),
									                    foreign key (phone_id)      references phones (id)					 									
									  )

