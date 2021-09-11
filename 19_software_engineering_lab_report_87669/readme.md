# Flask Login Example
This code sample makes use of Flask and Flask-SQLAlchemy, a library that manages User registration, log in, session and logout functionality.

## Requirements.txt
    Flask
    Flask-SQLAlchemy

## Setup Repo
```
virtualenv -p python3 /.
source bin/activate
git clone https://github.com/tolgahanuzun/Flask-Login-Example
cd Flask-Login-Example
pip install -r requirements.txt
python app.py
```

## To view Database
```
1.Type sqlite3 in command prompt.
2.To view the database type the following commands
   .header ON
   SELECT * 
   FROM USER(here table name = user)
   ;
3.For more commands type .help it will show lot of commands, which might be usefull.
``` 
