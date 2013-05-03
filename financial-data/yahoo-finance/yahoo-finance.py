# -*- coding: utf-8 -*-

# Author: Michael Halls-Moore - QuantStart.com
# Created: 30th April 2013

"""
Library for dealing with Yahoo Finance downloads.

Makes use of the pandas library in order to eliminate most
of the headaches associated with Python data analysis.

Provides functions for downloading Yahoo Finance historic
Open-High-Low-Close (OHLC) data. Will also adjust OHLC based
on the Yahoo Finance adjusted close (dividend/stock-split) 
column. 
"""

import datetime
import numpy as np
import pandas as pd
import urllib2


def get_historic_data(ticker, 
                      start_date=(2000,1,1), 
                      end_date=datetime.date.today().timetuple()[0:3], 
                      adjusted=True):
    """
    Obtains data from Yahoo Finance and adds it to a pandas DataFrame object.

    ticker: Yahoo Finance ticker symbol, e.g. "GOOG" for Google, Inc.
    start_date: Start date in (YYYY, M, D) format
    end_date: End date in (YYYY, M, D) format
    adjusted: Describes whether data should be adjusted or unadjusted for corporate actions
    """

    # Construct the Yahoo URL with the correct integer query parameters
    # for start and end dates. Note that some parameters are zero-based!
    yahoo_url = "http://ichart.finance.yahoo.com/table.csv?s=%s&a=%s&b=%s&c=%s&d=%s&e=%s&f=%s" % (ticker, start_date[1] - 1, start_date[2], start_date[0], end_date[1] - 1, end_date[2], end_date[0])
    
    # Try connecting to Yahoo Finance and obtaining the data
    # On failure, print to stdout
    try:
        yf_data = urllib2.urlopen(yahoo_url).readlines()
    except Exception, e:
        print "Could not download Yahoo data: %s" % e

    # Create the (temporary) Python data structures to store
    # the historical data
    date_list = []
    hist_data = [[] for i in range(6)]

    # Format and copy the raw text data into datetime objects 
    # and floating point values (still in native Python lists)
    for day in yf_data[1:]: # Avoid the header line in the CSV
        headers = day.rstrip().split(',')
        date_list.append(datetime.datetime.strptime(headers[0],'%Y-%m-%d'))
        for i, header in enumerate(headers[1:]):
            hist_data[i].append(float(header))

    # Create a Python dictionary of the lists and then use that to
    # form a sorted Pandas DataFrame of the historical data
    hist_data = dict(zip(['open', 'high', 'low', 'close', 'volume', 'adj_close'], hist_data))
    pdf = pd.DataFrame(hist_data, index=pd.Index(date_list)).sort()

    return pdf
