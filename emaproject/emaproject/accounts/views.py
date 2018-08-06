#!/usr/bin/python
# -*- coding: utf-8 -*-
from django.shortcuts import render
from django.contrib.auth.decorators import login_required
from django.http import JsonResponse
from accounts.models import Buttonresults
from datetime import date, timedelta, datetime, time
from django.db.models import Count
from time import mktime
from django.utils import timezone

# Generates the login view for home.html
@login_required(login_url='login/')
def home(request):
    return render(request, 'home.html')

# Generates the JSON object for the last 7 days for HighCharts
def week(request):
    endDate = timezone.now()
    startDate = timezone.now() - timedelta(days=7)

    # Queries for the date and number of times happy or sad was pressed for the last 7 days in the ButtonResults table

    happyDataset = Buttonresults.objects.filter(moodID=1,
            timestamp__range=(startDate, endDate)).extra({'timestamp': 'date("timeStamp")'
            }).values('timestamp'
            ).annotate(count=Count('moodID'
            )).order_by('timestamp')
    sadDataset = Buttonresults.objects.filter(moodID=2,
            timestamp__range=(startDate, endDate)).extra({'timestamp': 'date("timeStamp")'
            }).values('timestamp'
            ).annotate(count=Count('moodID'
                       )).order_by('timestamp')

    happyData = list()
    sadData = list()

    # Creates a nested list for the data section in the JSON object

    for result in happyDataset:
        # Convert datetime format to UNIX timestamp format
        timestamp = mktime(result['timestamp'].timetuple()) * 1000
        newList = [timestamp, result['count']]
        happyData.append(newList)

    for result in sadDataset:
        timestamp = mktime(result['timestamp'].timetuple()) * 1000
        newList = [timestamp, result['count']]
        sadData.append(newList)

    # JSON object to render the column graph on the dashboard
    data = {
        'chart': {'type': 'column'},
        'title': {'text': 'The Last 7 Days'},
        'xAxis': {'type': 'datetime', 'tickInterval': 1 * 24 * 3600 \
                  * 1000, 'labels': {'format': '{value:%b-%e}'}},
        'yAxis': {'allowDecimals': False},
        'series': [{'name': 'Happy', 'data': happyData, 'color': '#3d72a5'}, {'name': 'Sad'
                   , 'data': sadData, 'color': 'red'}],
        }

    return JsonResponse(data)

# Generates the JSON object for the last 30 days for HighCharts
def month(request):
    endDate = timezone.now()
    startDate = timezone.now() - timedelta(days=30)

    # Queries the date and number of times happy or sad was pressed the last 30 days in the ButtonResults table

    happyDataset = Buttonresults.objects.filter(moodID=1,
            timestamp__range=(startDate, endDate)).extra({'timestamp': 'date("timeStamp")'
            }).values('timestamp'
            ).annotate(count=Count('moodID'
            )).order_by('timestamp')
    sadDataset = Buttonresults.objects.filter(moodID=2,
            timestamp__range=(startDate, endDate)).extra({'timestamp': 'date("timeStamp")'
            }).values('timestamp'
            ).annotate(count=Count('moodID'
            )).order_by('timestamp')

    happyData = list()
    sadData = list()

    # Creates a nested list for the data section in the JSON object

    for result in happyDataset:
        # Convert datetime format to UNIX timestamp format
        timestamp = mktime(result['timestamp'].timetuple()) * 1000
        newList = [timestamp, result['count']]
        happyData.append(newList)

    for result in sadDataset:
        timestamp = mktime(result['timestamp'].timetuple()) * 1000
        newList = [timestamp, result['count']]
        sadData.append(newList)

    # JSON object to render the column graph on the dashboard
    data = {
        'chart': {'type': 'column'},
        'title': {'text': 'The Last 30 Days'},
        'xAxis': {'type': 'datetime', 'tickInterval': 1 * 24 * 3600 \
                  * 1000, 'labels': {'format': '{value:%b-%e}'}},
        'yAxis': {'allowDecimals': False},
        'series': [{'name': 'Happy', 'data': happyData, 'color': '#3d72a5'}, {'name': 'Sad'
                   , 'data': sadData, 'color': 'red'}],
        }

    return JsonResponse(data)

# Generates the JSON object for the last 90 days for HighCharts
def three(request):
    endDate = timezone.now()
    startDate = timezone.now() - timedelta(days=90)

    # Queries the date and number of times happy or sad was pressed for the last 90 days in the ButtonResults table

    happyDataset = Buttonresults.objects.filter(moodID=1,
            timestamp__range=(startDate, endDate)).extra({'timestamp': 'date("timeStamp")'
            }).values('timestamp'
            ).annotate(count=Count('moodID'
            )).order_by('timestamp')
    sadDataset = Buttonresults.objects.filter(moodID=2,
            timestamp__range=(startDate, endDate)).extra({'timestamp': 'date("timeStamp")'
            }).values('timestamp'
            ).annotate(count=Count('moodID'
            )).order_by('timestamp')

    happyData = list()
    sadData = list()

    # Creates a nested list for the data section in the JSON object

    for result in happyDataset:
        # Convert datetime format to UNIX timestamp format
        timestamp = mktime(result['timestamp'].timetuple()) * 1000
        newList = [timestamp, result['count']]
        happyData.append(newList)

    for result in sadDataset:
        timestamp = mktime(result['timestamp'].timetuple()) * 1000
        newList = [timestamp, result['count']]
        sadData.append(newList)

    # JSON object to render the column graph on the dashboard
    data = {
        'chart': {'type': 'column'},
        'title': {'text': 'The Last 3 Months'},
        'xAxis': {'type': 'datetime', 'tickInterval': 1 * 24 * 3600 \
                  * 1000, 'labels': {'format': '{value:%b-%e}'}},
        'yAxis': {'allowDecimals': False},
        'series': [{'name': 'Happy', 'data': happyData, 'color': '#3d72a5'}, {'name': 'Sad'
                   , 'data': sadData, 'color': 'red'}],
        }

    return JsonResponse(data)

# Generates the JSON object for HighCharts
def all(request):
    
    # Queries the date and number of times happy or sad was pressed for all the data in the ButtonResults table

    happyDataset = Buttonresults.objects.filter(moodID=1).extra({'timestamp': 'date("timeStamp")'
            }).values('timestamp').annotate(count=Count('moodID'
            )).order_by('timestamp')
    sadDataset = Buttonresults.objects.filter(moodID=2).extra({'timestamp': 'date("timeStamp")'
            }).values('timestamp').annotate(count=Count('moodID'
            )).order_by('timestamp')

    happyData = list()
    sadData = list()

    # Creates a nested list for the data section in the JSON object

    for result in happyDataset:
        # Convert datetime format to UNIX timestamp format
        timestamp = mktime(result['timestamp'].timetuple()) * 1000
        newList = [timestamp, result['count']]
        happyData.append(newList)

    for result in sadDataset:
        timestamp = mktime(result['timestamp'].timetuple()) * 1000
        newList = [timestamp, result['count']]
        sadData.append(newList)

    # JSON object to render the column graph on the dashboard
    data = {
        'chart': {'type': 'column'},
        'title': {'text': 'All Data'},
        'xAxis': {'type': 'datetime', 'tickInterval': 1 * 24 * 3600 \
                  * 1000, 'labels': {'format': '{value:%b-%e}'}},
        'yAxis': {'allowDecimals': False},
        'series': [{'name': 'Happy', 'data': happyData, 'color': '#3d72a5'}, {'name': 'Sad'
                   , 'data': sadData, 'color': 'red'}],
        }

    return JsonResponse(data)
