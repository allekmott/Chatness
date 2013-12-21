Chatness
========

Command-line IRC client


Documentation
=============
Server Args
-----------
+ -a - Add to chat.dat; Runs cdgen.

chat.dat Format
---------------

### Tokens 
+ *$* = user  
    format: ```$[user_name]:[hashed_password]:[access_level]```  

+ *@* = chatroom  
    format: ```@[group_name]:[user_list]```  

+ *#* = comment  
    format: ```#lololol```
  
#### Example:
```
#this is an example chat.dat
$root:413c3016048d1167:0
#^root is default admin, and only root has all authority
#eventhose with same access level are still not all-powerful
$lol:413c3016048d1167:1
```

Commands
--------
+ *mkrm* - create chatroom  
  usage: ```/mkrm <chatroom_name>```
    + If name already exists in chat.dat, will alert with "Chatroom
      '[chatroom_name]' already exists. Please choose another name."
    + Otherwise, password will be prompted from user
+ *join* - join a chatroom  
  usage: ```/join <chatroom_name>```
    + If chat room doesn't exist, user will be alerted with "Chatroom
      '[chatroom_name]' does not exist."
    + Otherwise, chatroom will be joined.
  
