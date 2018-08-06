# Employee Morale Application

The application will use two mood buttons, one for happy and one for sad, to collect Rooof’s employees’ moods at a specific moment in time. The buttons will be installed in a communal location, such as the lunchroom, to allow employees to click a mood button freely and anonymously. The data will then be transferred to the database so that human resources will be able to analyze the collected information.

## Getting Started

### Using Mac OS
```
* git clone https://gitlab.camosun.bc.ca/roooftop/emaproject.git
* virtualenv venv // create virtual environment named venv if not done; Mac OS command
* source venv/bin/activate
* cd emaproject
* pip install -r requirements.txt
* cd emaproject
* python manage.py migrate
* python manage.py createsuperuser //creates user account
* python manage.py runserver // starts the server 
* Open browser type IP address 127.0.0.1:8000
```
### Using Windows
```
* git clone https://gitlab.camosun.bc.ca/roooftop/emaproject.git
* py -m venv venv // create virtual environment named venv if not done
* cmd
* venv\Scripts\activate
* cd emaproject
* cd emaproject
* pip install -r requirements.txt
* python manage.py migrate
* winpty python manage.py createsuperuser //create user account to login - follow prompts
* python manage.py runserver // starts the server 
* Open browser type IP address 127.0.0.1:8000 
```

### Deploying to Elastic Beanstalk
```
* Pull the latest version from gitlab
* Make own branch and make the necessary changes
* pip freeze > requirements.txt // to ensure requirements.txt is up to date since elastic beanstalk will use it to deploy
* Push the changes to gitlab
* eb deploy // deploys project to elastic beanstalk
* eb open or go to http://django.vs4vxvdy2z.us-west-2.elasticbeanstalk.com/ in the browser to open the link 
```

### Prerequisites

What things you need to install the software and how to install them

```
pip
Python3
Django
virtualenv
```

### Folder Directory

Elastic Beanstalk is finiky with how the files are ordered. This is how the directory should look like

```

- .git
- .gitignore
- emaproject
    -- .ebextensions
        -- django.config
    -- .elasticbeanstalk
        -- config.yml
    -- accounts
        -- __init__.py
        -- __pycache__
        -- admin.py
        -- apps.py
        -- forms.py
        -- migrations
        -- models.py
        -- tests.py
        -- urls.py
        -- views.py
    -- emaproject
        -- __init__.py
        -- __pycache__
        -- settings.py
        -- urls.py
        -- wsgi.py
    -- manage.py
    -- requirements.txt
    -- static
        -- admin
        -- css
        -- js
    -- templates
        -- base.html
        -- getData.php
        -- home.html
        -- login.html
        -- registration
            -- login.html
- README.md
- venv

```

## Running the tests

Explain how to run the automated tests for this system

## Deployment

Add additional notes about how to deploy this on a live system


## Authors

* Fiona Siu - [GitHub](https://github.com/FiSiu10)
* Jasmine Kivari - [GitHub](https://github.com/starcatjazz)
* Kerensa Mattison - [GitHub](https://github.com/ICScapstone2018)
* Zackary Bowman - [GitHub](https://github.com/zbowman1994)


## Acknowledgments

* Our faculty supervisor - Jason Cumiskey
* Our project sponsors - Matt and Cassandra

