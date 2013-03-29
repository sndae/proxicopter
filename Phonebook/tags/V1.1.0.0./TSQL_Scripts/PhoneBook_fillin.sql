
DECLARE @REV_NUMB int

SET @REV_NUMB = '0'

INSERT INTO [phonebook].[dbo].[CITIES]
           ([ID]
           ,[REV_NUMB]
           ,[CODE]
           ,[NAME]
           ,[AREA])
     VALUES
           ('0'
           ,@REV_NUMB
           ,N'052'
           ,N'Варна'
           ,N'Варна')

INSERT INTO [phonebook].[dbo].[CITIES]
           ([ID]
           ,[REV_NUMB]
           ,[CODE]
           ,[NAME]
           ,[AREA])
     VALUES
           ('1'
           ,@REV_NUMB
           ,N'056'
           ,N'Бургас'
           ,N'Бургас')
           
INSERT INTO [phonebook].[dbo].[CITIES]
           ([ID]
           ,[REV_NUMB]
           ,[CODE]
           ,[NAME]
           ,[AREA])
     VALUES
           ('2'
           ,@REV_NUMB
           ,N'02'
           ,N'София'
           ,N'София')

INSERT INTO [phonebook].[dbo].[CITIES]
           ([ID]
           ,[REV_NUMB]
           ,[CODE]
           ,[NAME]
           ,[AREA])
     VALUES
           ('3'
           ,@REV_NUMB
           ,N'032'
           ,N'Пловдив'
           ,N'Пловдив')                                  
           
INSERT INTO [phonebook].[dbo].[PHONE_TYPES]
           ([ID]
           ,[REV_NUMB]           
           ,[CODE]
           ,[PHONE_TYPE])
     VALUES
           ('0'
           ,@REV_NUMB
           ,'11'
           ,N'Мобилен')    
           
INSERT INTO [phonebook].[dbo].[PHONE_TYPES]
           ([ID]
           ,[REV_NUMB]           
           ,[CODE]
           ,[PHONE_TYPE])
     VALUES
           ('1'
           ,@REV_NUMB
           ,'22'
           ,N'Офис')
                                               
INSERT INTO [phonebook].[dbo].[PHONE_TYPES]
           ([ID]
           ,[REV_NUMB]           
           ,[CODE]
           ,[PHONE_TYPE])
     VALUES
           ('2'
           ,@REV_NUMB
           ,'33'
           ,N'Личен')
           
INSERT INTO [phonebook].[dbo].[SUBSCRIBERS]
           ([ID]
           ,[REV_NUMB]           
           ,[CODE]
           ,[FIRST_NAME]
           ,[SECOND_NAME]
           ,[THIRD_NAME]
           ,[IDENT_NUMB]
           ,[CITY_ID] 
           ,[CITY_ADDR])
     VALUES
           ('0'
           ,@REV_NUMB          
           ,'989'
           ,N'Димитър' 
           ,N'Костов'
           ,N'Люцканов' 
           ,N'8606070000'
           ,'0'
           ,'Синчец 9')

INSERT INTO [phonebook].[dbo].[SUBSCRIBERS]
           ([ID]
           ,[REV_NUMB]           
           ,[CODE]
           ,[FIRST_NAME]
           ,[SECOND_NAME]
           ,[THIRD_NAME]
           ,[IDENT_NUMB]
           ,[CITY_ID] 
           ,[CITY_ADDR])
     VALUES
           ('1'
           ,@REV_NUMB          
           ,'1203'
           ,N'Иван' 
           ,N'Георгиев'
           ,N'Темелков' 
           ,N'8605280000'
           ,'2'
           ,'Младост 3, бл. 32')

           
           
INSERT INTO [phonebook].[dbo].[SUBSCRIBER_PHONE_NUMBERS] 
           ([ID] 
           ,[REV_NUMB]            
           ,[SUBSCRIBER_ID] 
           ,[PHONE_ID] 
           ,[PHONE_NUMB] )
     VALUES
           ('0'
           ,@REV_NUMB           
           ,'0'
           ,'2'
           ,N'785209')

INSERT INTO [phonebook].[dbo].[SUBSCRIBER_PHONE_NUMBERS] 
           ([ID] 
           ,[REV_NUMB]            
           ,[SUBSCRIBER_ID] 
           ,[PHONE_ID] 
           ,[PHONE_NUMB] )
     VALUES
           ('1'
           ,@REV_NUMB
           ,'1'
           ,'0'
           ,N'0878123456')
                      
GO


