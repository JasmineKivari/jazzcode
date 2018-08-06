# accounts/urls.py
from django.conf.urls import patterns, url
from . import views

urlpatterns = [
    url(r'^$', views.home, name='home'),
    url(r'^week/', views.week, name='week'),
    url(r'^month/', views.month, name='month'),
    url(r'^three/', views.three, name='three'),
    url(r'^all/', views.all, name='all'),
]
