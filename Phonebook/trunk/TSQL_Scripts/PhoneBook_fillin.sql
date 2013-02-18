
DECLARE @rev_nmbr int

SET @rev_nmbr = '0'

INSERT INTO [phonebook].[dbo].[cities]
           ([id]
           ,[rev_nmb]
           ,[code]
           ,[name]
           ,[area])
     VALUES
           ('0'
           ,@rev_nmbr
           ,N'052'
           ,N'Варна'
           ,N'Варна')

INSERT INTO [phonebook].[dbo].[cities]
           ([id]
           ,[rev_nmb]           
           ,[code]
           ,[name]
           ,[area])
     VALUES
           ('1'
           ,@rev_nmbr
           ,N'056'
           ,N'Бургас'
           ,N'Бургас')
           
INSERT INTO [phonebook].[dbo].[cities]
           ([id]
           ,[rev_nmb]           
           ,[code]
           ,[name]
           ,[area])
     VALUES
           ('2'
           ,@rev_nmbr
           ,N'02'
           ,N'София'
           ,N'София')

INSERT INTO [phonebook].[dbo].[cities]
           ([id]
           ,[rev_nmb]           
           ,[code]
           ,[name]
           ,[area])
     VALUES
           ('3'
           ,@rev_nmbr
           ,N'032'
           ,N'Пловдив'
           ,N'Пловдив')                                  
           
INSERT INTO [phonebook].[dbo].[phones]
           ([id]
           ,[rev_nmb]           
           ,[code]
           ,phone_type)
     VALUES
           ('0'
           ,@rev_nmbr
           ,'11'
           ,N'Мобилен')    
           
INSERT INTO [phonebook].[dbo].[phones]
           ([id]
           ,[rev_nmb]           
           ,[code]
           ,phone_type)
     VALUES
           ('1'
           ,@rev_nmbr
           ,'22'
           ,N'Офис')
                                               
INSERT INTO [phonebook].[dbo].[phones]
           ([id]
           ,[rev_nmb]           
           ,[code]
           ,phone_type)
     VALUES
           ('2'
           ,@rev_nmbr
           ,'33'
           ,N'Личен')
           
INSERT INTO [phonebook].[dbo].[subscribers]
           ([id]
           ,[rev_nmb]           
           ,[code]
           ,[first_name]
           ,[second_name]
           ,[third_name]
           ,[ident_nmb]
           ,[city_id]
           ,[city_addr])
     VALUES
           ('0'
           ,@rev_nmbr          
           ,'989'
           ,N'Димитър' 
           ,N'Костов'
           ,N'Люцканов' 
           ,'8606070000'
           ,'2'
           ,'Синчец 9')

INSERT INTO [phonebook].[dbo].[subscribers]
           ([id]
           ,[rev_nmb]           
           ,[code]
           ,[first_name]
           ,[second_name]
           ,[third_name]
           ,[ident_nmb]
           ,[city_id]
           ,[city_addr])
     VALUES
           ('1'
           ,@rev_nmbr          
           ,'1203'
           ,N'Иван' 
           ,N'Георгиев'
           ,N'Темелков' 
           ,'8605280000'
           ,'0'
           ,'Младост 3, бл. 32')

           
           
INSERT INTO [phonebook].[dbo].[subscriber_phone_numbers]
           ([id]
           ,[rev_nmb]           
           ,[subscriber_id]
           ,[phone_id]
           ,[phone_number])
     VALUES
           ('0'
           ,@rev_nmbr           
           ,'0'
           ,'2'
           ,N'785209')

INSERT INTO [phonebook].[dbo].[subscriber_phone_numbers]
           ([id]
           ,[rev_nmb]           
           ,[subscriber_id]
           ,[phone_id]
           ,[phone_number])
     VALUES
           ('1'
           ,@rev_nmbr
           ,'1'
           ,'0'
           ,N'0878123456')
                      
GO


